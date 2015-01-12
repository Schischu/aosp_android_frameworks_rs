#include "rsCpuScriptGroup2.h"

#ifndef RS_COMPATIBILITY_LIB
#include "bcc/BCCContext.h"
#include "bcc/Config/Config.h"
#include "bcc/Renderscript/RSCompilerDriver.h"
#include "bcc/Source.h"
#include "bcc/Support/InputFile.h"

#include <sys/wait.h>
#endif

#include "bcc/Renderscript/RSExecutable.h"
#include "cpu_ref/rsCpuCore.h"
#include "rsClosure.h"
#include "rsContext.h"
#include "rsCpuCore.h"
#include "rsCpuScript.h"
#include "rsScript.h"
#include "rsScriptGroup2.h"
#include "rsScriptIntrinsic.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace android {
namespace renderscript {

namespace {

const size_t DefaultKernelArgCount = 2;

void groupRoot(const RsExpandKernelParams *kparams, uint32_t xstart,
               uint32_t xend, uint32_t outstep) {
  const list<CPUClosure*>& closures = *(list<CPUClosure*>*)kparams->usr;
  RsExpandKernelParams *mutable_kparams = (RsExpandKernelParams *)kparams;
  const void **oldIns  = kparams->ins;
  uint32_t *oldStrides = kparams->inEStrides;

  std::vector<const void*> ins(DefaultKernelArgCount);
  std::vector<uint32_t> strides(DefaultKernelArgCount);

  for (CPUClosure* cpuClosure : closures) {
    const Closure* closure = cpuClosure->mClosure;

    auto in_iter = ins.begin();
    auto stride_iter = strides.begin();

    for (const auto& arg : closure->mArgs) {
      const Allocation* a = (const Allocation*)arg;
      const uint32_t eStride = a->mHal.state.elementSizeBytes;
      const uint8_t* ptr = (uint8_t*)(a->mHal.drvState.lod[0].mallocPtr) +
          eStride * xstart;
      if (kparams->dimY > 1) {
        ptr += a->mHal.drvState.lod[0].stride * kparams->y;
      }
      *in_iter++ = ptr;
      *stride_iter++ = eStride;
    }

    mutable_kparams->ins = &ins[0];
    mutable_kparams->inEStrides = &strides[0];

    const Allocation* out = closure->mReturnValue;
    const uint32_t ostep = out->mHal.state.elementSizeBytes;
    const uint8_t* ptr = (uint8_t *)(out->mHal.drvState.lod[0].mallocPtr) +
           ostep * xstart;
    if (kparams->dimY > 1) {
      ptr += out->mHal.drvState.lod[0].stride * kparams->y;
    }

    mutable_kparams->out = (void*)ptr;

    mutable_kparams->usr = cpuClosure->mUsrPtr;

    cpuClosure->mFunc(kparams, xstart, xend, ostep);
  }

  mutable_kparams->ins        = oldIns;
  mutable_kparams->inEStrides = oldStrides;
  mutable_kparams->usr        = &closures;
}

}  // namespace

bool Batch::conflict(CPUClosure* closure) const {
  if (mClosures.empty()) {
    return false;
  }

  if (closure->mClosure->mKernelID.get() == nullptr ||
      mClosures.front()->mClosure->mKernelID.get() == nullptr) {
    // An invoke should be in a batch by itself, so it conflicts with any other
    // closure.
    return true;
  }

  for (const auto &p : closure->mClosure->mGlobalDeps) {
    const Closure* dep = p.first;
    for (CPUClosure* c : mClosures) {
      if (c->mClosure == dep) {
        ALOGV("ScriptGroup2: closure %p conflicting with closure %p via its global", closure, dep);
        return true;
      }
    }
  }
  for (const auto &p : closure->mClosure->mArgDeps) {
    const Closure* dep = p.first;
    for (CPUClosure* c : mClosures) {
      if (c->mClosure == dep) {
        for (const auto &p1 : *p.second) {
          if (p1.second->get() != nullptr) {
            ALOGV("ScriptGroup2: closure %p conflicting with closure %p via its arg", closure, dep);
            return true;
          }
        }
      }
    }
  }
  return false;
}

CpuScriptGroup2Impl::CpuScriptGroup2Impl(RsdCpuReferenceImpl *cpuRefImpl,
                                         const ScriptGroupBase *sg) :
    mCpuRefImpl(cpuRefImpl), mGroup((const ScriptGroup2*)(sg)) {
  Batch* batch = new Batch(this);
  for (Closure* closure: mGroup->mClosures) {
    const ScriptKernelID* kernelID = closure->mKernelID.get();
    RsdCpuScriptImpl* si =
        (RsdCpuScriptImpl *)mCpuRefImpl->lookupScript(kernelID->mScript);

    MTLaunchStruct mtls;
    si->forEachKernelSetup(kernelID->mSlot, &mtls);
    // TODO: Is mtls.fep.usrLen ever used?
    CPUClosure* cc = new CPUClosure(closure, si, (ExpandFuncTy)mtls.kernel,
                                    mtls.fep.usr, mtls.fep.usrLen);
    if (batch->conflict(cc)) {
      mBatches.push_back(batch);
      batch = new Batch(this);
    }

    batch->mClosures.push_back(cc);
  }

  mBatches.push_back(batch);

#ifndef RS_COMPATIBILITY_LIB
  for (Batch* batch : mBatches) {
    batch->tryToCreateFusedKernel(mGroup->mCacheDir.c_str());
  }
#endif
}

CpuScriptGroup2Impl::~CpuScriptGroup2Impl() {
  for (Batch* batch : mBatches) {
    delete batch;
  }
}

namespace {

#ifndef RS_COMPATIBILITY_LIB

void setupCompileArguments(
    const vector<string>& inputs, const vector<int>& kernels,
    const string& output, const string& rsLib,
    vector<const char*>* args) {
  args->push_back(RsdCpuScriptImpl::BCC_EXE_PATH);
  args->push_back("-mtriple");
  args->push_back(DEFAULT_TARGET_TRIPLE_STRING);
  args->push_back("-bclib");
  args->push_back(rsLib.c_str());
  for (const string& input : inputs) {
    args->push_back(input.c_str());
  }
  for (int kernel : kernels) {
    args->push_back("-k");
    string strKernel = std::to_string(kernel);
    args->push_back(strKernel.c_str());
  }
  unsigned found = output.find_last_of("/\\");
  string outdir = output.substr(0, found);
  string filename = output.substr(found + 1);
  args->push_back("-output_path");
  args->push_back(outdir.c_str());
  args->push_back("-o");
  args->push_back(filename.c_str());
  args->push_back(nullptr);
}

bool fuseAndCompile(const char** arguments,
                    const string& commandLine) {
  const pid_t pid = fork();

  if (pid == -1) {
    ALOGE("Couldn't fork for bcc execution");
    return false;
  }

  if (pid == 0) {
    // Child process
    ALOGV("Invoking BCC with: %s", commandLine.c_str());
    execv(RsdCpuScriptImpl::BCC_EXE_PATH, (char* const*)arguments);

    ALOGE("execv() failed: %s", strerror(errno));
    abort();
    return false;
  }

  // Parent process
  int status = 0;
  const pid_t w = waitpid(pid, &status, 0);
  if (w == -1) {
    return false;
  }

  if (!WIFEXITED(status) || WEXITSTATUS(status) != 0 ) {
    ALOGE("bcc terminated unexpectedly");
    return false;
  }

  return true;
}
#endif

}  // anonymous namespace

void Batch::tryToCreateFusedKernel(const char *cacheDir) {
#ifndef RS_COMPATIBILITY_LIB
  if (mClosures.size() < 2) {
    ALOGV("Compiler kernel fusion skipped due to only one or zero kernel in"
          " a script group batch.");
    return;
  }

  //===--------------------------------------------------------------------===//
  // Fuse the input kernels and generate native code in an object file
  //===--------------------------------------------------------------------===//

  std::vector<string> inputFiles;
  std::vector<int> slots;

  for (CPUClosure* cpuClosure : mClosures) {
    const Closure* closure = cpuClosure->mClosure;
    const ScriptKernelID* kernelID = closure->mKernelID.get();
    const Script* script = kernelID->mScript;

    if (script->isIntrinsic()) {
      return;
    }

    const RsdCpuScriptImpl *cpuScript =
        (const RsdCpuScriptImpl*)script->mHal.drv;

    const string& bitcodeFilename = cpuScript->getBitcodeFilePath();

    inputFiles.push_back(bitcodeFilename);
    slots.push_back(kernelID->mSlot);
  }

  string outputPath(tempnam(cacheDir, "fused"));
  string objFilePath(outputPath);
  objFilePath.append(".o");
  string rsLibPath(SYSLIBPATH"/libclcore.bc");
  vector<const char*> arguments;
  setupCompileArguments(inputFiles, slots, outputPath, rsLibPath, &arguments);
  string commandLine =
      bcc::getCommandLine(arguments.size() - 1, arguments.data());

  if (!fuseAndCompile(arguments.data(), commandLine)) {
    return;
  }

  //===--------------------------------------------------------------------===//
  // Load the object file
  //===--------------------------------------------------------------------===//

  std::string infoPath = bcc::RSInfo::GetPath(objFilePath.c_str());
  bcc::InputFile infoFile(infoPath.c_str());
  const std::unique_ptr<bcc::RSInfo> info(bcc::RSInfo::ReadFromFile(infoFile));

  bcc::InputFile objFile(objFilePath.c_str());

  bcc::CompilerRTSymbolResolver compilerRuntime;
  bcc::LookupFunctionSymbolResolver<void *> RSRuntime;
  bcc::SymbolResolverProxy resolver;
  RSRuntime.setLookupFunction(RsdCpuScriptImpl::lookupRuntimeStub);
  RSRuntime.setContext(mClosures.front()->mClosure->mKernelID->mScript);

  resolver.chainResolver(compilerRuntime);
  resolver.chainResolver(RSRuntime);

  mExecutable = RSExecutable::Create(*info, objFile, resolver);
#endif
}

void CpuScriptGroup2Impl::execute() {
  for (auto batch : mBatches) {
    batch->setGlobalsForBatch();
    batch->run();
  }
}

void Batch::setGlobalsForBatch() {
  for (CPUClosure* cpuClosure : mClosures) {
    const Closure* closure = cpuClosure->mClosure;
    const ScriptKernelID* kernelID = closure->mKernelID.get();
    Script* s = kernelID->mScript;
    for (const auto& p : closure->mGlobals) {
      const void* value = p.second.first;
      int size = p.second.second;
      // We use -1 size to indicate an ObjectBase rather than a primitive type
      if (size < 0) {
        s->setVarObj(p.first->mSlot, (ObjectBase*)value);
      } else {
        s->setVar(p.first->mSlot, (const void*)&value, size);
      }
    }
  }
}

void Batch::run() {
  if (mExecutable != nullptr) {
    MTLaunchStruct mtls;
    const CPUClosure* firstCpuClosure = mClosures.front();
    const CPUClosure* lastCpuClosure = mClosures.back();

    firstCpuClosure->mSi->forEachMtlsSetup(
        (const Allocation**)&firstCpuClosure->mClosure->mArgs[0],
        firstCpuClosure->mClosure->mArgs.size(),
        lastCpuClosure->mClosure->mReturnValue,
        nullptr, 0, nullptr, &mtls);

    mtls.script = nullptr;
    mtls.fep.usr = nullptr;
    mtls.kernel = reinterpret_cast<ForEachFunc_t>(
        mExecutable->getExportForeachFuncAddrs()[0]);

    mGroup->getCpuRefImpl()->launchThreads(
        (const Allocation**)&firstCpuClosure->mClosure->mArgs[0],
        firstCpuClosure->mClosure->mArgs.size(),
        lastCpuClosure->mClosure->mReturnValue,
        nullptr, &mtls);

    return;
  }

  for (CPUClosure* cpuClosure : mClosures) {
    const Closure* closure = cpuClosure->mClosure;
    const ScriptKernelID* kernelID = closure->mKernelID.get();
    cpuClosure->mSi->preLaunch(kernelID->mSlot,
                               (const Allocation**)&closure->mArgs[0],
                               closure->mArgs.size(), closure->mReturnValue,
                               cpuClosure->mUsrPtr, cpuClosure->mUsrSize,
                               nullptr);
  }

  const CPUClosure* cpuClosure = mClosures.front();
  const Closure* closure = cpuClosure->mClosure;
  MTLaunchStruct mtls;

  cpuClosure->mSi->forEachMtlsSetup((const Allocation**)&closure->mArgs[0],
                                    closure->mArgs.size(),
                                    closure->mReturnValue,
                                    nullptr, 0, nullptr, &mtls);

  mtls.script = nullptr;
  mtls.kernel = (void (*)())&groupRoot;
  mtls.fep.usr = &mClosures;

  mGroup->getCpuRefImpl()->launchThreads(nullptr, 0, nullptr, nullptr, &mtls);

  for (CPUClosure* cpuClosure : mClosures) {
    const Closure* closure = cpuClosure->mClosure;
    const ScriptKernelID* kernelID = closure->mKernelID.get();
    cpuClosure->mSi->postLaunch(kernelID->mSlot,
                                (const Allocation**)&closure->mArgs[0],
                                closure->mArgs.size(), closure->mReturnValue,
                                nullptr, 0, nullptr);
  }
}

}  // namespace renderscript
}  // namespace android
