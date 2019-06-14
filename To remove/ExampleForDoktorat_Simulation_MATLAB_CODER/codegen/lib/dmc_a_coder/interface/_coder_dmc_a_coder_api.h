/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_dmc_a_coder_api.h
 *
 * Code generation for function '_coder_dmc_a_coder_api'
 *
 */

#ifndef _CODER_DMC_A_CODER_API_H
#define _CODER_DMC_A_CODER_API_H

/* Include files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_dmc_a_coder_api.h"

/* Type Definitions */
#ifndef struct_emxArray_real32_T
#define struct_emxArray_real32_T

struct emxArray_real32_T
{
  real32_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_real32_T*/

#ifndef typedef_emxArray_real32_T
#define typedef_emxArray_real32_T

typedef struct emxArray_real32_T emxArray_real32_T;

#endif                                 /*typedef_emxArray_real32_T*/

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void dmc_a_coder(emxArray_real32_T *AD_Y, emxArray_real32_T *AD_U,
  emxArray_real32_T *AD_DU, emxArray_real32_T *AD_Z, int32_T AD_K, real32_T umin,
  real32_T umax, real32_T dumin, real32_T dumax, real_T control_value[2]);
extern void dmc_a_coder_api(const mxArray * const prhs[9], const mxArray *plhs[1]);
extern void dmc_a_coder_atexit(void);
extern void dmc_a_coder_initialize(void);
extern void dmc_a_coder_terminate(void);
extern void dmc_a_coder_xil_terminate(void);

#endif

/* End of code generation (_coder_dmc_a_coder_api.h) */
