/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * dmc_a_coder.h
 *
 * Code generation for function 'dmc_a_coder'
 *
 */

#ifndef DMC_A_CODER_H
#define DMC_A_CODER_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "dmc_a_coder_types.h"

/* Function Declarations */
extern void dmc_a_coder(const emxArray_real32_T *AD_Y, const emxArray_real32_T
  *AD_U, const emxArray_real32_T *AD_DU, const emxArray_real32_T *AD_Z, int AD_K,
  float umin, float umax, float dumin, float dumax, double control_value[2]);

#endif

/* End of code generation (dmc_a_coder.h) */
