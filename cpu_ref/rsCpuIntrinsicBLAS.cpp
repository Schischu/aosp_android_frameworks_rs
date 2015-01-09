/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include "rsCpuIntrinsic.h"
#include "rsCpuIntrinsicInlines.h"
#include "cblas.h"

using namespace android;
using namespace android::renderscript;

namespace android {
namespace renderscript {


class RsdCpuScriptIntrinsicBLAS : public RsdCpuScriptIntrinsic {
public:
    virtual void invokeForEach(uint32_t slot,
                               const Allocation ** ain,
                               uint32_t inLen,
                               Allocation * aout,
                               const void * usr,
                               uint32_t usrLen,
                               const RsScriptCall *sc);

    virtual void populateScript(Script *);
    virtual ~RsdCpuScriptIntrinsicBLAS();
    RsdCpuScriptIntrinsicBLAS(RsdCpuReferenceImpl *ctx, const Script *s);

protected:


};

}
}

void RsdCpuScriptIntrinsicBLAS::populateScript(Script *s) {
    s->mHal.info.exportedVariableCount = 0;
}

/*static void initA(const Allocation ** ain,
                   void** A,
                  int* lda)
{
    *A = ain[0]->mHal.drvState.lod[0].mallocPtr;
    *lda = (int)ain[0]->mHal.drvState.lod[0].stride;
}*/

static void initAB(const Allocation ** ain,
                   size_t size,
                   void** A,
                   void** B,
                   int* lda,
                   int* ldb)
{
    *A = ain[0]->mHal.drvState.lod[0].mallocPtr;
    *B = ain[1]->mHal.drvState.lod[0].mallocPtr;
    
    *lda = (int)(ain[0]->mHal.drvState.lod[0].stride/size);
    *ldb = (int)(ain[1]->mHal.drvState.lod[0].stride/size);
}

static void initABC(const Allocation ** ain,
                    size_t size,
                    void** A,
                    void** B,
                    void** C,
                    int* lda,
                    int* ldb,
                    int* ldc)
{
    *A = ain[0]->mHal.drvState.lod[0].mallocPtr;
    *B = ain[1]->mHal.drvState.lod[0].mallocPtr;
    *C = ain[2]->mHal.drvState.lod[0].mallocPtr;

    *lda = (int)(ain[0]->mHal.drvState.lod[0].stride/size);
    *ldb = (int)(ain[1]->mHal.drvState.lod[0].stride/size);
    *ldc = (int)(ain[2]->mHal.drvState.lod[0].stride/size);
}

void RsdCpuScriptIntrinsicBLAS::invokeForEach(uint32_t slot,
                                              const Allocation ** ain,
                                              uint32_t inLen,
                                              Allocation * aout,
                                              const void * usr,
                                              uint32_t usrLen,
                                              const RsScriptCall *sc) {
    RsBlasCall* call = (RsBlasCall*) usr;
    // setup BLAS enum args
    enum CBLAS_TRANSPOSE TransA = (enum CBLAS_TRANSPOSE)call->transA;
    enum CBLAS_TRANSPOSE TransB = (enum CBLAS_TRANSPOSE)call->transB;
    enum CBLAS_UPLO Uplo = (enum CBLAS_UPLO)call->uplo;
    enum CBLAS_DIAG Diag = (enum CBLAS_DIAG)call->diag;
    enum CBLAS_SIDE Side = (enum CBLAS_SIDE)call->side;

    void *A = nullptr;
    void *B = nullptr;
    void *C = nullptr;
    void *X = nullptr;
    void *Y = nullptr;

    int lda = 0, ldb = 0, ldc = 0;

    switch (call->func) {

    // Level 1 BLAS: returns into a 1D Allocation
    

    // Level 2 BLAS
    case (RsBlas_sgemv):
        initABC(ain, sizeof(float), &A, &X, &C, &lda, &ldb, &ldc);
        cblas_sgemv(CblasRowMajor, TransA, call->M, call->N, call->alpha.f, (float*)A,
                    lda, (float*)X, call->incX, call->beta.f, (float*)Y, call->incY);
        break;
    case (RsBlas_sgbmv):
        initABC(ain, sizeof(float), &A, &X, &C, &lda, &ldb, &ldc);
        cblas_sgbmv(CblasRowMajor, TransA, call->M, call->N, call->KL, call->KU,
                    call->alpha.f, (float*)A, lda, (float*)X, call->incX,
                    call->beta.f, (float*)Y, call->incY);
        break;
    case (RsBlas_strmv):
        initAB(ain, sizeof(float), &A, &X, &lda, &ldb);
        cblas_strmv(CblasRowMajor, Uplo, TransA, Diag, call->N, (float*)A,
                    lda, (float*)X, call->incX);
        break;
    case (RsBlas_stbmv):
        initAB(ain, sizeof(float), &A, &X, &lda, &ldb);
        cblas_stbmv(CblasRowMajor, Uplo, TransA, Diag, call->N, call->K, (float*)A,
                    lda, (float*)X, call->incX);
        break;
    // stpmv takes a packed 1D Allocation only
    case (RsBlas_stpmv):
        initAB(ain, sizeof(float), &A, &X, &lda, &ldb);
        cblas_stpmv(CblasRowMajor, Uplo, TransA, Diag, call->N, (float*)A,
                    (float*)X, call->incX);
        break;
    case (RsBlas_strsv):
        initAB(ain, sizeof(float), &A, &X, &lda, &ldb);
        cblas_strsv(CblasRowMajor, Uplo, TransA, Diag, call->N, (float*)A, lda,
                    (float*)X, call->incX);
        break;
    case (RsBlas_stbsv):
        initAB(ain, sizeof(float), &A, &X, &lda, &ldb);
        cblas_stbsv(CblasRowMajor, Uplo, TransA, Diag, call->N, call->K, (float*)A,
                    lda, (float*)X, call->incX);
        break;
    case (RsBlas_stpsv):
        initAB(ain, sizeof(float), &A, &X, &lda, &ldb);
        cblas_stpsv(CblasRowMajor, Uplo, TransA, Diag, call->N, (float*)A,
                    (float*)X, call->incX);
        break;
    case (RsBlas_dgemv):
        initABC(ain, sizeof(double), &A, &X, &C, &lda, &ldb, &ldc);
        cblas_dgemv(CblasRowMajor, TransA, call->M, call->N, call->alpha.d, (double*)A,
                    lda, (double*)X, call->incX, call->beta.d, (double*)Y, call->incY);
        break;
    case (RsBlas_dgbmv):
        initABC(ain, sizeof(double), &A, &X, &C, &lda, &ldb, &ldc);
        cblas_dgbmv(CblasRowMajor, TransA, call->M, call->N, call->KL, call->KU,
                    call->alpha.d, (double*)A, lda, (double*)X, call->incX,
                    call->beta.d, (double*)Y, call->incY);
        break;
    case (RsBlas_dtrmv):
        initAB(ain, sizeof(double), &A, &X, &lda, &ldb);
        cblas_dtrmv(CblasRowMajor, Uplo, TransA, Diag, call->N, (double*)A,
                    lda, (double*)X, call->incX);
        break;
    case (RsBlas_dtbmv):
        initAB(ain, sizeof(double), &A, &X, &lda, &ldb);
        cblas_dtbmv(CblasRowMajor, Uplo, TransA, Diag, call->N, call->K, (double*)A,
                    lda, (double*)X, call->incX);
        break;
    // stpmv takes a packed 1D Allocation only
    case (RsBlas_dtpmv):
        initAB(ain, sizeof(double), &A, &X, &lda, &ldb);
        cblas_dtpmv(CblasRowMajor, Uplo, TransA, Diag, call->N, (double*)A,
                    (double*)X, call->incX);
        break;
    case (RsBlas_dtrsv):
        initAB(ain, sizeof(double), &A, &X, &lda, &ldb);
        cblas_dtrsv(CblasRowMajor, Uplo, TransA, Diag, call->N, (double*)A, lda,
                    (double*)X, call->incX);
        break;
    case (RsBlas_dtbsv):
        initAB(ain, sizeof(double), &A, &X, &lda, &ldb);
        cblas_dtbsv(CblasRowMajor, Uplo, TransA, Diag, call->N, call->K, (double*)A,
                    lda, (double*)X, call->incX);
        break;
    case (RsBlas_dtpsv):
        initAB(ain, sizeof(double), &A, &X, &lda, &ldb);
        cblas_dtpsv(CblasRowMajor, Uplo, TransA, Diag, call->N, (double*)A,
                    (double*)X, call->incX);
        break;
    case (RsBlas_cgemv):
        initABC(ain, sizeof(float _Complex), &A, &X, &C, &lda, &ldb, &ldc);
        cblas_cgemv(CblasRowMajor, TransA, call->M, call->N, (void*)&call->alpha.c, (void*)A,
                    lda, (void*)X, call->incX, (void*)&call->beta.c, (void*)Y, call->incY);
        break;
    case (RsBlas_cgbmv):
        initABC(ain, sizeof(float _Complex), &A, &X, &C, &lda, &ldb, &ldc);
        cblas_cgbmv(CblasRowMajor, TransA, call->M, call->N, call->KL, call->KU,
                    (void*)&call->alpha.c, (void*)A, lda, (void*)X, call->incX,
                    (void*)&call->beta.c, (void*)Y, call->incY);
        break;
    case (RsBlas_ctrmv):
        initAB(ain, sizeof(float _Complex), &A, &X, &lda, &ldb);
        cblas_ctrmv(CblasRowMajor, Uplo, TransA, Diag, call->N, (void*)A,
                    lda, (void*)X, call->incX);
        break;
    case (RsBlas_ctbmv):
        initAB(ain, sizeof(float _Complex), &A, &X, &lda, &ldb);
        cblas_ctbmv(CblasRowMajor, Uplo, TransA, Diag, call->N, call->K, (void*)A,
                    lda, (void*)X, call->incX);
        break;
    // stpmv takes a packed 1D Allocation only
    case (RsBlas_ctpmv):
        initAB(ain, sizeof(float _Complex), &A, &X, &lda, &ldb);
        cblas_ctpmv(CblasRowMajor, Uplo, TransA, Diag, call->N, (void*)A,
                    (void*)X, call->incX);
        break;
    case (RsBlas_ctrsv):
        initAB(ain, sizeof(float _Complex), &A, &X, &lda, &ldb);
        cblas_ctrsv(CblasRowMajor, Uplo, TransA, Diag, call->N, (void*)A, lda,
                    (void*)X, call->incX);
        break;
    case (RsBlas_ctbsv):
        initAB(ain, sizeof(float _Complex), &A, &X, &lda, &ldb);
        cblas_ctbsv(CblasRowMajor, Uplo, TransA, Diag, call->N, call->K, (void*)A,
                    lda, (void*)X, call->incX);
        break;
    case (RsBlas_ctpsv):
        initAB(ain, sizeof(float _Complex), &A, &X, &lda, &ldb);
        cblas_ctpsv(CblasRowMajor, Uplo, TransA, Diag, call->N, (void*)A,
                    (void*)X, call->incX);
        break;
    case (RsBlas_zgemv):
        initABC(ain, sizeof(double _Complex), &A, &X, &C, &lda, &ldb, &ldc);
        cblas_zgemv(CblasRowMajor, TransA, call->M, call->N, (void*)&call->alpha.z, (void*)A,
                    lda, (void*)X, call->incX, (void*)&call->beta.z, (void*)Y, call->incY);
        break;
    case (RsBlas_zgbmv):
        initABC(ain, sizeof(double _Complex), &A, &X, &C, &lda, &ldb, &ldc);
        cblas_zgbmv(CblasRowMajor, TransA, call->M, call->N, call->KL, call->KU,
                    (void*)&call->alpha.z, (void*)A, lda, (void*)X, call->incX,
                    (void*)&call->beta.z, (void*)Y, call->incY);
        break;
    case (RsBlas_ztrmv):
        initAB(ain, sizeof(double _Complex), &A, &X, &lda, &ldb);
        cblas_ztrmv(CblasRowMajor, Uplo, TransA, Diag, call->N, (void*)A,
                    lda, (void*)X, call->incX);
        break;
    case (RsBlas_ztbmv):
        initAB(ain, sizeof(double _Complex), &A, &X, &lda, &ldb);
        cblas_ztbmv(CblasRowMajor, Uplo, TransA, Diag, call->N, call->K, (void*)A,
                    lda, (void*)X, call->incX);
        break;
    // stpmv takes a packed 1D Allocation only
    case (RsBlas_ztpmv):
        initAB(ain, sizeof(double _Complex), &A, &X, &lda, &ldb);
        cblas_ztpmv(CblasRowMajor, Uplo, TransA, Diag, call->N, (void*)A,
                    (void*)X, call->incX);
        break;
    case (RsBlas_ztrsv):
        initAB(ain, sizeof(double _Complex), &A, &X, &lda, &ldb);
        cblas_ztrsv(CblasRowMajor, Uplo, TransA, Diag, call->N, (void*)A, lda,
                    (void*)X, call->incX);
        break;
    case (RsBlas_ztbsv):
        initAB(ain, sizeof(double _Complex), &A, &X, &lda, &ldb);
        cblas_ztbsv(CblasRowMajor, Uplo, TransA, Diag, call->N, call->K, (void*)A,
                    lda, (void*)X, call->incX);
        break;
    case (RsBlas_ztpsv):
        initAB(ain, sizeof(double _Complex), &A, &X, &lda, &ldb);
        cblas_ztpsv(CblasRowMajor, Uplo, TransA, Diag, call->N, (void*)A,
                    (void*)X, call->incX);
        break;


    // S and D only
    case (RsBlas_ssymv):
        initABC(ain, sizeof(float), &A, &X, &Y, &lda, &ldb, &ldc);
        cblas_ssymv(CblasRowMajor, Uplo, call->N, call->alpha.f, (float*)A, lda,
                    (float*)X, call->incX, call->beta.f, (float*)Y, call->incY);
        break;
    case (RsBlas_ssbmv):
        initABC(ain, sizeof(float), &A, &X, &Y, &lda, &ldb, &ldc);
        cblas_ssbmv(CblasRowMajor, Uplo, call->N, call->K, call->alpha.f,
                    (float*)A, lda, (float*)X, call->incX, call->beta.f,
                    (float*)Y, call->incY);
        break;
    //sspmv requires a packed 1D Allocation
    case (RsBlas_sspmv):
        initABC(ain, sizeof(float), &A, &X, &Y, &lda, &ldb, &ldc);
        cblas_sspmv(CblasRowMajor, Uplo, call->N, call->alpha.f, (float*)A,
                    (float*)X, call->incX, call->beta.f, (float*)Y, call->incY);
        break;
    // following calls have init reordered because A is output matrix
    case (RsBlas_sger):
        initABC(ain, sizeof(float), &X, &Y, &A, &ldb, &ldc, &lda);
        cblas_sger(CblasRowMajor, call->M, call->N, call->alpha.f, (float*)X,
                   call->incX, (float*)Y, call->incY, (float*)A, lda);
        break;
    case (RsBlas_ssyr):
        initAB(ain, sizeof(float), &X, &A, &ldb, &lda);
        cblas_ssyr(CblasRowMajor, Uplo, call->N, call->alpha.f, (float*)X, call->incX,
                   (float*)A, lda);        
        break;
    // sspr is packed 1D Allocation A only
    case (RsBlas_sspr):
        initAB(ain, sizeof(float), &X, &A, &ldb, &lda);
        cblas_sspr(CblasRowMajor, Uplo, call->N, call->alpha.f, (float*)X, call->incX,
                   (float*)A);        
        break;    
    case (RsBlas_ssyr2):
        initABC(ain, sizeof(float), &X, &Y, &A, &ldb, &ldc, &lda);
        cblas_ssyr2(CblasRowMajor, Uplo, call->N, call->alpha.f, (float*)X, call->incX, 
                    (float*)Y, call->incY, (float*)A, lda);        
        break;
    // sspr2 is packed 1D Allocation A only
    case (RsBlas_sspr2):
        initABC(ain, sizeof(float), &X, &Y, &A, &ldb, &ldc, &lda);
        cblas_sspr2(CblasRowMajor, Uplo, call->N, call->alpha.f, (float*)X, call->incX,
                    (float*)Y, call->incY, (float*)A);        
        break;
    case (RsBlas_dsymv):
        initABC(ain, sizeof(double), &A, &X, &Y, &lda, &ldb, &ldc);
        cblas_dsymv(CblasRowMajor, Uplo, call->N, call->alpha.d, (double*)A, lda,
                    (double*)X, call->incX, call->beta.d, (double*)Y, call->incY);
        break;
    case (RsBlas_dsbmv):
        initABC(ain, sizeof(double), &A, &X, &Y, &lda, &ldb, &ldc);
        cblas_dsbmv(CblasRowMajor, Uplo, call->N, call->K, call->alpha.d,
                    (double*)A, lda, (double*)X, call->incX, call->beta.d,
                    (double*)Y, call->incY);
        break;
    // dspmv requires a packed 1D Allocation
    case (RsBlas_dspmv):
        initABC(ain, sizeof(double), &A, &X, &Y, &lda, &ldb, &ldc);
        cblas_dspmv(CblasRowMajor, Uplo, call->N, call->alpha.d, (double*)A,
                    (double*)X, call->incX, call->beta.d, (double*)Y, call->incY);
        break;
    // following calls have init reordered because A is output matrix
    case (RsBlas_dger):
        initABC(ain, sizeof(double), &X, &Y, &A, &ldb, &ldc, &lda);
        cblas_dger(CblasRowMajor, call->M, call->N, call->alpha.d, (double*)X,
                   call->incX, (double*)Y, call->incY, (double*)A, lda);
        break;
    case (RsBlas_dsyr):
        initAB(ain, sizeof(double), &X, &A, &ldb, &lda);
        cblas_dsyr(CblasRowMajor, Uplo, call->N, call->alpha.d, (double*)X, call->incX,
                   (double*)A, lda);        
        break;
    // dspr is packed 1D Allocation A only
    case (RsBlas_dspr):
        initAB(ain, sizeof(double), &X, &A, &ldb, &lda);
        cblas_dspr(CblasRowMajor, Uplo, call->N, call->alpha.d, (double*)X, call->incX,
                   (double*)A);        
        break;    
    case (RsBlas_dsyr2):
        initABC(ain, sizeof(double), &X, &Y, &A, &ldb, &ldc, &lda);
        cblas_dsyr2(CblasRowMajor, Uplo, call->N, call->alpha.d, (double*)X, call->incX, 
                    (double*)Y, call->incY, (double*)A, lda);        
        break;
    // dspr2 is packed 1D Allocation A only
    case (RsBlas_dspr2):
        initABC(ain, sizeof(double), &X, &Y, &A, &ldb, &ldc, &lda);
        cblas_dspr2(CblasRowMajor, Uplo, call->N, call->alpha.d, (double*)X, call->incX,
                    (double*)Y, call->incY, (double*)A);        
        break;

    // C and Z only
    case (RsBlas_chemv):
        initABC(ain, sizeof(float _Complex), &A, &X, &Y, &lda, &ldb, &ldc);
        cblas_chemv(CblasRowMajor, Uplo, call->N, (void*)&call->alpha.c, A, lda,
                    X, call->incX, (void*)&call->beta.c, Y, call->incY);        
        break;
    case (RsBlas_chbmv):
        initABC(ain, sizeof(float _Complex), &A, &X, &Y, &lda, &ldb, &ldc);
        cblas_chbmv(CblasRowMajor, Uplo, call->N, call->K, (void*)&call->alpha.c,
                    A, lda, X, call->incX, (void*)&call->beta.c, Y, call->incY);        
        break;
    case (RsBlas_chpmv):
        initABC(ain, sizeof(float _Complex), &A, &X, &Y, &lda, &ldb, &ldc);
        cblas_chpmv(CblasRowMajor, Uplo, call->N, (void*)&call->alpha.c, A,
                    X, call->incX, (void*)&call->beta.c, Y, call->incY);        
        break;
    case (RsBlas_cgeru):
        initABC(ain, sizeof(float _Complex), &X, &Y, &A, &ldb, &ldc, &lda);
        cblas_cgeru(CblasRowMajor, call->M, call->N, (void*)&call->alpha.c, 
                    X, call->incX, Y, call->incY, A, lda);        
        break;
    case (RsBlas_cgerc):
        initABC(ain, sizeof(float _Complex), &X, &Y, &A, &ldb, &ldc, &lda);
        cblas_cgerc(CblasRowMajor, call->M, call->N, (void*)&call->alpha.c, 
                    X, call->incX, Y, call->incY, A, lda);        
        break;
    case (RsBlas_cher):
        initAB(ain, sizeof(float _Complex), &X, &A, &ldb, &lda);
        cblas_cher(CblasRowMajor, Uplo, call->N, call->alpha.f, 
                   X, call->incX, A, lda);        
        break;
    // packed 1D Allocations only
    case (RsBlas_chpr):
        initAB(ain, sizeof(float _Complex), &X, &A, &ldb, &lda);
        cblas_chpr(CblasRowMajor, Uplo, call->N, call->alpha.f, X,
                   call->incX, A);        
        break;
    case (RsBlas_cher2):
        initABC(ain, sizeof(float _Complex), &X, &Y, &A, &ldb, &ldc, &lda);
        cblas_cher2(CblasRowMajor, Uplo, call->N, (void*)&call->alpha.c, 
                   X, call->incX, Y, call->incY, A, lda);        
        break;
    // packed 1D Allocations only
    case (RsBlas_chpr2):
        initABC(ain, sizeof(float _Complex), &X, &Y, &A, &ldb, &ldc, &lda);
        cblas_chpr2(CblasRowMajor, Uplo, call->N, (void*)&call->alpha.c, X,
                   call->incX, Y, call->incY, A);        
        break;
    case (RsBlas_zhemv):
        initABC(ain, sizeof(double _Complex), &A, &X, &Y, &lda, &ldb, &ldc);
        cblas_zhemv(CblasRowMajor, Uplo, call->N, (void*)&call->alpha.z, A, lda,
                    X, call->incX, (void*)&call->beta.z, Y, call->incY);        
        break;
    case (RsBlas_zhbmv):
        initABC(ain, sizeof(double _Complex), &A, &X, &Y, &lda, &ldb, &ldc);
        cblas_zhbmv(CblasRowMajor, Uplo, call->N, call->K, (void*)&call->alpha.z,
                    A, lda, X, call->incX, (void*)&call->beta.z, Y, call->incY);        
        break;
    case (RsBlas_zhpmv):
        initABC(ain, sizeof(double _Complex), &A, &X, &Y, &lda, &ldb, &ldc);
        cblas_zhpmv(CblasRowMajor, Uplo, call->N, (void*)&call->alpha.z, A,
                    X, call->incX, (void*)&call->beta.z, Y, call->incY);        
        break;
    case (RsBlas_zgeru):
        initABC(ain, sizeof(double _Complex), &X, &Y, &A, &ldb, &ldc, &lda);
        cblas_zgeru(CblasRowMajor, call->M, call->N, (void*)&call->alpha.z, 
                    X, call->incX, Y, call->incY, A, lda);        
        break;
    case (RsBlas_zgerc):
        initABC(ain, sizeof(double _Complex), &X, &Y, &A, &ldb, &ldc, &lda);
        cblas_zgerc(CblasRowMajor, call->M, call->N, (void*)&call->alpha.z, 
                    X, call->incX, Y, call->incY, A, lda);        
        break;
    case (RsBlas_zher):
        initAB(ain, sizeof(double _Complex), &X, &A, &ldb, &lda);
        cblas_zher(CblasRowMajor, Uplo, call->N, call->alpha.d, 
                   X, call->incX, A, lda);        
        break;
    // packed 1D Allocations only
    case (RsBlas_zhpr):
        initAB(ain, sizeof(double _Complex), &X, &A, &ldb, &lda);
        cblas_zhpr(CblasRowMajor, Uplo, call->N, call->alpha.d, X,
                   call->incX, A);        
        break;
    case (RsBlas_zher2):
        initABC(ain, sizeof(double _Complex), &X, &Y, &A, &ldb, &ldc, &lda);
        cblas_zher2(CblasRowMajor, Uplo, call->N, (void*)&call->alpha.z, 
                   X, call->incX, Y, call->incY, A, lda);        
        break;
    // packed 1D Allocations only
    case (RsBlas_zhpr2):
        initABC(ain, sizeof(double _Complex), &X, &Y, &A, &ldb, &ldc, &lda);
        cblas_zhpr2(CblasRowMajor, Uplo, call->N, (void*)&call->alpha.z, X,
                   call->incX, Y, call->incY, A);        
        break;        

    // Level 3 BLAS
    case (RsBlas_sgemm):
        initABC(ain, sizeof(float), &A, &B, &C, &lda, &ldb, &ldc);
        cblas_sgemm(CblasRowMajor, TransA, TransB, call->M, call->N, call->K, call->alpha.f,
                    (float*)A, lda, (float*)B, ldb, call->beta.f, (float*)C, ldc);
        break;
    case (RsBlas_ssymm):
        initABC(ain, sizeof(float), &A, &B, &C, &lda, &ldb, &ldc);
        cblas_ssymm(CblasRowMajor, Side, Uplo, call->M, call->N, call->alpha.f, (float*)A,
                    lda, (float*)B, ldb, call->beta.f, (float*)C, ldc);
        break;
    case (RsBlas_ssyrk):
        // C is stored in the second Allocation for syrk
        initAB(ain, sizeof(float), &A, &C, &lda, &ldc);
        cblas_ssyrk(CblasRowMajor, Uplo, TransA, call->N, call->K, call->alpha.f, (float*)A,
                    lda, call->beta.f, (float*)C, ldc);
        break;
    case (RsBlas_ssyr2k):
        initABC(ain, sizeof(float), &A, &B, &C, &lda, &ldb, &ldc);
        cblas_ssyr2k(CblasRowMajor, Uplo, TransA, call->N, call->K, call->alpha.f, (float*)A,
                     lda, (float*)B, ldb, call->beta.f, (float*)C, ldc);
        break;
    case (RsBlas_strmm):
        initAB(ain, sizeof(float), &A, &B, &lda, &ldb);
        cblas_strmm(CblasRowMajor, Side, Uplo, TransA, Diag, call->M, call->N, call->alpha.f,
                    (float*)A, lda, (float*)B, ldb);
        break;
    case (RsBlas_strsm):
        initAB(ain, sizeof(float), &A, &B, &lda, &ldb);
        cblas_strsm(CblasRowMajor, Side, Uplo, TransA, Diag, call->M, call->N, call->alpha.f,
                    (float*)A, lda, (float*)B, ldb);
        break;


    case (RsBlas_dgemm):
        initABC(ain, sizeof(double), &A, &B, &C, &lda, &ldb, &ldc);
        cblas_dgemm(CblasRowMajor, TransA, TransB, call->M, call->N, call->K, call->alpha.d,
                    (double*)A, lda, (double*)B, ldb, call->beta.d, (double*)C, ldc);
        break;
    case (RsBlas_dsymm):
        initABC(ain, sizeof(double), &A, &B, &C, &lda, &ldb, &ldc);
        cblas_dsymm(CblasRowMajor, Side, Uplo, call->M, call->N, call->alpha.d, (double*)A,
                    lda, (double*)B, ldb, call->beta.d, (double*)C, ldc);
        break;
    case (RsBlas_dsyrk):
        // C is stored in the second Allocation for syrk
        initAB(ain, sizeof(double), &A, &C, &lda, &ldc);
        cblas_dsyrk(CblasRowMajor, Uplo, TransA, call->N, call->K, call->alpha.d, (double*)A,
                    lda, call->beta.d, (double*)C, ldc);
        break;
    case (RsBlas_dsyr2k):
        initABC(ain, sizeof(double), &A, &B, &C, &lda, &ldb, &ldc);
        cblas_dsyr2k(CblasRowMajor, Uplo, TransA, call->N, call->K, call->alpha.d, (double*)A,
                     lda, (double*)B, ldb, call->beta.d, (double*)C, ldc);
        break;
    case (RsBlas_dtrmm):
        initAB(ain, sizeof(double), &A, &B, &lda, &ldb);
        cblas_dtrmm(CblasRowMajor, Side, Uplo, TransA, Diag, call->M, call->N, call->alpha.d,
                    (double*)A, lda, (double*)B, ldb);
        break;
    case (RsBlas_dtrsm):
        initAB(ain, sizeof(double), &A, &B, &lda, &ldb);
        cblas_dtrsm(CblasRowMajor, Side, Uplo, TransA, Diag, call->M, call->N, call->alpha.d,
                    (double*)A, lda, (double*)B, ldb);
        break;

    case (RsBlas_cgemm):
        initABC(ain, sizeof(float _Complex), &A, &B, &C, &lda, &ldb, &ldc);
        cblas_cgemm(CblasRowMajor, TransA, TransB, call->M, call->N, call->K, (void*)&call->alpha.c,
                    A, lda, B, ldb, (void*)&call->beta.c, C, ldc);
        break;
    case (RsBlas_csymm):
        initABC(ain, sizeof(float _Complex), &A, &B, &C, &lda, &ldb, &ldc);
        cblas_csymm(CblasRowMajor, Side, Uplo, call->M, call->N, (void*)&call->alpha.c, A,
                    lda, B, ldb, (void*)&call->beta.c, C, ldc);
        break;
    case (RsBlas_csyrk):
        // C is stored in the second Allocation for syrk
        initAB(ain, sizeof(float _Complex), &A, &C, &lda, &ldc);
        cblas_csyrk(CblasRowMajor, Uplo, TransA, call->N, call->K, (void*)&call->alpha.c, A,
                    lda, (void*)&call->beta.c, C, ldc);
        break;
    case (RsBlas_csyr2k):
        initABC(ain, sizeof(float _Complex), &A, &B, &C, &lda, &ldb, &ldc);
        cblas_csyr2k(CblasRowMajor, Uplo, TransA, call->N, call->K, (void*)&call->alpha.c, A,
                     lda, B, ldb, (void*)&call->beta.c, C, ldc);
        break;
    case (RsBlas_ctrmm):
        initAB(ain, sizeof(float _Complex), &A, &B, &lda, &ldb);
        cblas_ctrmm(CblasRowMajor, Side, Uplo, TransA, Diag, call->M, call->N, (void*)&call->alpha.c,
                    A, lda, B, ldb);
        break;
    case (RsBlas_ctrsm):
        initAB(ain, sizeof(float _Complex), &A, &B, &lda, &ldb);
        cblas_ctrsm(CblasRowMajor, Side, Uplo, TransA, Diag, call->M, call->N, (void*)&call->alpha.c,
                    A, lda, B, ldb);
        break;

    case (RsBlas_zgemm):
        initABC(ain, sizeof(double _Complex), &A, &B, &C, &lda, &ldb, &ldc);
        cblas_zgemm(CblasRowMajor, TransA, TransB, call->M, call->N, call->K, (void*)&call->alpha.z,
                    A, lda, B, ldb, (void*)&call->beta.z, C, ldc);
        break;
    case (RsBlas_zsymm):
        initABC(ain, sizeof(double _Complex), &A, &B, &C, &lda, &ldb, &ldc);
        cblas_zsymm(CblasRowMajor, Side, Uplo, call->M, call->N, (void*)&call->alpha.z, A,
                    lda, B, ldb, (void*)&call->beta.z, C, ldc);
        break;
    case (RsBlas_zsyrk):
        // C is stored in the second Allocation for syrk
        initAB(ain, sizeof(double _Complex), &A, &C, &lda, &ldc);
        cblas_zsyrk(CblasRowMajor, Uplo, TransA, call->N, call->K, (void*)&call->alpha.z, A,
                    lda, (void*)&call->beta.z, C, ldc);
        break;
    case (RsBlas_zsyr2k):
        initABC(ain, sizeof(double _Complex), &A, &B, &C, &lda, &ldb, &ldc);
        cblas_zsyr2k(CblasRowMajor, Uplo, TransA, call->N, call->K, (void*)&call->alpha.z, A,
                     lda, B, ldb, (void*)&call->beta.z, C, ldc);
        break;
    case (RsBlas_ztrmm):
        initAB(ain, sizeof(double _Complex), &A, &B, &lda, &ldb);
        cblas_ztrmm(CblasRowMajor, Side, Uplo, TransA, Diag, call->M, call->N, (void*)&call->alpha.z,
                    A, lda, B, ldb);
        break;
    case (RsBlas_ztrsm):
        initAB(ain, sizeof(double _Complex), &A, &B, &lda, &ldb);
        cblas_ztrsm(CblasRowMajor, Side, Uplo, TransA, Diag, call->M, call->N, (void*)&call->alpha.z,
                    A, lda, B, ldb);
        break;

    // Level 3 C and Z only
    case (RsBlas_chemm):
        initABC(ain, sizeof(float _Complex), &A, &B, &C, &lda, &ldb, &ldc);
        cblas_chemm(CblasRowMajor, Side, Uplo, call->M, call->N, (void*)&call->alpha.c, A, lda,
                    B, ldb, (void*)&call->beta.c, C, ldc);
        break;
    case (RsBlas_cherk):
        // C is stored in the second Allocation for herk
        initAB(ain, sizeof(float _Complex), &A, &C, &lda, &ldc);
        cblas_cherk(CblasRowMajor, Uplo, TransA, call->N, call->K, call->alpha.f, A, lda,
                    call->beta.f, C, ldc);
        break;
    case (RsBlas_cher2k):
        initABC(ain, sizeof(float _Complex), &A, &B, &C, &lda, &ldb, &ldc);
        cblas_cher2k(CblasRowMajor, Uplo, TransA, call->N, call->K, (void*)&call->alpha.c, A, lda,
                     B, ldb, call->beta.f, C, ldc);
        break;

    case (RsBlas_zhemm):
        initABC(ain, sizeof(double _Complex), &A, &B, &C, &lda, &ldb, &ldc);
        cblas_zhemm(CblasRowMajor, Side, Uplo, call->M, call->N, (void*)&call->alpha.z, A, lda,
                    B, ldb, (void*)&call->beta.z, C, ldc);
        break;
    case (RsBlas_zherk):
        // C is stored in the second Allocation for herk
        initAB(ain, sizeof(double _Complex), &A, &C, &lda, &ldc);
        cblas_zherk(CblasRowMajor, Uplo, TransA, call->N, call->K, call->alpha.d, A, lda,
                    call->beta.d, C, ldc);
        break;
    case (RsBlas_zher2k):
        initABC(ain, sizeof(double _Complex), &A, &B, &C, &lda, &ldb, &ldc);
        cblas_zher2k(CblasRowMajor, Uplo, TransA, call->N, call->K, (void*)&call->alpha.z, A, lda,
                     B, ldb, call->beta.d, C, ldc);
        break;

    default:
        ALOGE("unimplemented\n");
    }


}


RsdCpuScriptIntrinsicBLAS::RsdCpuScriptIntrinsicBLAS(RsdCpuReferenceImpl *ctx,
                                                   const Script *s)
            : RsdCpuScriptIntrinsic(ctx, s, nullptr, RS_SCRIPT_INTRINSIC_ID_BLAS) {


}

RsdCpuScriptIntrinsicBLAS::~RsdCpuScriptIntrinsicBLAS() {
}





RsdCpuScriptImpl * rsdIntrinsic_BLAS(RsdCpuReferenceImpl *ctx,
                                    const Script *s, const Element *e) {

    return new RsdCpuScriptIntrinsicBLAS(ctx, s);
}
