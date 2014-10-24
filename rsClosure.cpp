#include "rsClosure.h"

#include "rsContext.h" // XXX: necessary to avoid compiler error on rsScript.h below
#include "rsScript.h"
#include "rsType.h"

namespace android {
namespace renderscript {

RsClosure rsi_ClosureCreate(Context* context, RsScriptKernelID kernelID,
                            RsAllocation returnValue,
                            RsScriptFieldID* fieldIDs, size_t fieldIDs_length,
                            uintptr_t* values, size_t values_length,
                            int* sizes, size_t sizes_length,
                            RsClosure* depClosures, size_t depClosures_length,
                            RsScriptFieldID* depFieldIDs,
                            size_t depFieldIDs_length) {
  rsAssert(fieldIDs_length == values_length && values_length == sizes_length &&
           sizes_length == depClosures_length &&
           depClosures_length == depFieldIDs_length);

  return (RsClosure)(new Closure(
      context, (const ScriptKernelID*)kernelID, (Allocation*)returnValue,
      fieldIDs_length, (const ScriptFieldID**)fieldIDs, (const void**)values,
      (const int*)sizes, (const Closure**)depClosures,
      (const ScriptFieldID**)depFieldIDs));
}

void rsi_ClosureEval(Context* rsc, RsClosure closure) {
  ((Closure*)closure)->eval();
}

void rsi_ClosureSetArg(Context* rsc, RsClosure closure, int index,
                       uintptr_t value, int size) {
  ((Closure*)closure)->setArg(index, (const void*)value, size);
}

void rsi_ClosureSetGlobal(Context* rsc, RsClosure closure,
                          RsScriptFieldID fieldID, uintptr_t value,
                          int size) {
  ((Closure*)closure)->setGlobal((const ScriptFieldID*)fieldID,
                                 (const void*)value, size);
}

Closure::Closure(Context* context,
                 const ScriptKernelID* kernelID,
                 Allocation* returnValue,
                 const int numValues,
                 const ScriptFieldID** fieldIDs,
                 const void** values,
                 const int* sizes,
                 const Closure** depClosures,
                 const ScriptFieldID** depFieldIDs) :
    mContext(context), mKernelID(kernelID),
    mReturnValue(returnValue) {
  size_t i;

  for (i = 0; i < (size_t)numValues && fieldIDs[i] == nullptr; i++);

  vector<const void*> args(values, values + i);
  mArgs.swap(args);

  for (; i < (size_t)numValues; i++) {
    mGlobals[fieldIDs[i]] = std::make_pair(values[i], sizes[i]);
  }

  mDependences.insert(depClosures, depClosures + numValues);

  for (i = 0; i < mArgs.size(); i++) {
    const Closure* dep = depClosures[i];
    if (dep != nullptr) {
      auto mapping = mArgDeps[dep];
      if (mapping == nullptr) {
        mapping = new map<int, const ScriptFieldID*>();
        mArgDeps[dep] = mapping;
      }
      (*mapping)[i] = depFieldIDs[i];
    }
  }

  for (; i < (size_t)numValues; i++) {
    const Closure* dep = depClosures[i];
    if (dep != nullptr) {
      auto mapping = mGlobalDeps[dep];
      if (mapping == nullptr) {
        mapping = new map<const ScriptFieldID*, const ScriptFieldID*>();
        mGlobalDeps[dep] = mapping;
      }
      (*mapping)[fieldIDs[i]] = depFieldIDs[i];
    }
  }
}

Closure::~Closure() {
  for (const auto& p : mArgDeps) {
    delete p.second;
  }

  for (const auto& p : mGlobalDeps) {
    delete p.second;
  }
}

void Closure::eval() {
  Script *s = mKernelID->mScript;

  for (const auto& p : mGlobals) {
    const void* value = p.second.first;
    int size = p.second.second;
    // We use -1 size to indicate an ObjectBase rather than a primitive type
    if (size < 0) {
      s->setVarObj(p.first->mSlot, (ObjectBase*)value);
    } else {
      s->setVar(p.first->mSlot, (const void*)&value, size);
    }
  }

  s->runForEach(mContext, mKernelID->mSlot, (const Allocation **)(&mArgs[0]),
                mArgs.size(), mReturnValue, nullptr, 0, nullptr);
}

void Closure::setArg(const int index, const void* value, const int size) {
  mArgs[index] = value;
}

void Closure::setGlobal(const ScriptFieldID* fieldID, const void* value,
                        const int size) {
  mGlobals[fieldID] = std::make_pair(value, size);
}

}  // namespace renderscript
}  // namespace android
