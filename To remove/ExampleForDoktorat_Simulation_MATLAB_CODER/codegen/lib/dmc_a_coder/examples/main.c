/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * main.c
 *
 * Code generation for function 'main'
 *
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/
/* Include files */
#include "rt_nonfinite.h"
#include "dmc_a_coder.h"
#include "main.h"
#include "dmc_a_coder_terminate.h"
#include "dmc_a_coder_emxAPI.h"
#include "dmc_a_coder_initialize.h"

/* Function Declarations */
static emxArray_real32_T *argInit_1xUnbounded_real32_T(void);
static int argInit_int32_T(void);
static float argInit_real32_T(void);
static emxArray_real32_T *c_argInit_UnboundedxUnbounded_r(void);
static void main_dmc_a_coder(void);

/* Function Definitions */
static emxArray_real32_T *argInit_1xUnbounded_real32_T(void)
{
  emxArray_real32_T *result;
  static int iv1[2] = { 1, 2 };

  int idx1;

  /* Set the size of the array.
     Change this size to the value that the application requires. */
  result = emxCreateND_real32_T(2, iv1);

  /* Loop over the array to initialize each element. */
  for (idx1 = 0; idx1 < result->size[1U]; idx1++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result->data[result->size[0] * idx1] = argInit_real32_T();
  }

  return result;
}

static int argInit_int32_T(void)
{
  return 0;
}

static float argInit_real32_T(void)
{
  return 0.0F;
}

static emxArray_real32_T *c_argInit_UnboundedxUnbounded_r(void)
{
  emxArray_real32_T *result;
  static int iv0[2] = { 2, 2 };

  int idx0;
  int idx1;

  /* Set the size of the array.
     Change this size to the value that the application requires. */
  result = emxCreateND_real32_T(2, iv0);

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
    for (idx1 = 0; idx1 < result->size[1U]; idx1++) {
      /* Set the value of the array element.
         Change this value to the value that the application requires. */
      result->data[idx0 + result->size[0] * idx1] = argInit_real32_T();
    }
  }

  return result;
}

static void main_dmc_a_coder(void)
{
  emxArray_real32_T *AD_Y;
  emxArray_real32_T *AD_U;
  emxArray_real32_T *AD_DU;
  emxArray_real32_T *AD_Z;
  double control_value[2];

  /* Initialize function 'dmc_a_coder' input arguments. */
  /* Initialize function input argument 'AD_Y'. */
  AD_Y = c_argInit_UnboundedxUnbounded_r();

  /* Initialize function input argument 'AD_U'. */
  AD_U = c_argInit_UnboundedxUnbounded_r();

  /* Initialize function input argument 'AD_DU'. */
  AD_DU = c_argInit_UnboundedxUnbounded_r();

  /* Initialize function input argument 'AD_Z'. */
  AD_Z = argInit_1xUnbounded_real32_T();

  /* Call the entry-point 'dmc_a_coder'. */
  dmc_a_coder(AD_Y, AD_U, AD_DU, AD_Z, argInit_int32_T(), argInit_real32_T(),
              argInit_real32_T(), argInit_real32_T(), argInit_real32_T(),
              control_value);
  emxDestroyArray_real32_T(AD_Z);
  emxDestroyArray_real32_T(AD_DU);
  emxDestroyArray_real32_T(AD_U);
  emxDestroyArray_real32_T(AD_Y);
}

int main(int argc, const char * const argv[])
{
  (void)argc;
  (void)argv;

  /* Initialize the application.
     You do not need to do this more than one time. */
  dmc_a_coder_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_dmc_a_coder();

  /* Terminate the application.
     You do not need to do this more than one time. */
  dmc_a_coder_terminate();
  return 0;
}

/* End of code generation (main.c) */
