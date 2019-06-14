/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * dmc_a_coder.c
 *
 * Code generation for function 'dmc_a_coder'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "dmc_a_coder.h"

/* Function Definitions */
void dmc_a_coder(const emxArray_real32_T *AD_Y, const emxArray_real32_T *AD_U,
                 const emxArray_real32_T *AD_DU, const emxArray_real32_T *AD_Z,
                 int AD_K, float umin, float umax, float dumin, float dumax,
                 double control_value[2])
{
  float AutoMATiC_DMC_dUp[40];
  int AutoMATiC_DMC_itmp;
  int AutoMATiC_DMC_i;
  int AutoMATiC_DMC_j;
  int q1;
  double AutoMATiC_DMC_e[2];
  float a[2];
  float AutoMATiC_DMC_du;
  float b_AutoMATiC_DMC_du[2];
  float b_a[2];
  static const float c_a[4] = { 0.67987144F, 0.015735535F, -0.0424543F,
    0.702137053F };

  static const float d_a[80] = { 0.626397073F, 0.025853971F, 0.025853971F,
    0.586871147F, 0.230438605F, 0.00951114483F, 0.00951114483F, 0.215897843F,
    0.0847736225F, 0.0034989547F, 0.0034989547F, 0.0794243738F, 0.0311864745F,
    0.0012871935F, 0.0012871935F, 0.0292185955F, 0.0114728622F, 0.000473532F,
    0.000473532F, 0.01074892F, 0.00422063F, 0.000174202694F, 0.000174202694F,
    0.00395430671F, 0.00155268307F, 6.40855869E-5F, 6.40855869E-5F,
    0.00145470817F, 0.000571200217F, 2.35757707E-5F, 2.35757707E-5F,
    0.000535157218F, 0.000210132814F, 8.67304152E-6F, 8.67304152E-6F,
    0.000196873341F, 7.73035426E-5F, 3.19063361E-6F, 3.19063361E-6F,
    7.24256533E-5F, 2.84383823E-5F, 1.17376851E-6F, 1.17376851E-6F,
    2.66439092E-5F, 1.04618975E-5F, 4.31805347E-7F, 4.31805347E-7F,
    9.80174718E-6F, 3.84871873E-6F, 1.58852728E-7F, 1.58852728E-7F,
    3.6058625E-6F, 1.41586645E-6F, 5.84400581E-8F, 5.84400581E-8F,
    1.32652247E-6F, 5.20865967E-7F, 2.15024087E-8F, 2.15024087E-8F,
    4.87992793E-7F, 1.91594779E-7F, 7.91717891E-9F, 7.91717891E-9F,
    1.79490897E-7F, 7.04042691E-8F, 2.92277669E-9F, 2.92277669E-9F,
    6.59358861E-8F, 2.56773252E-8F, 1.08392451E-9F, 1.08392451E-9F,
    2.40202063E-8F, 8.9419272E-9F, 3.92144928E-10F, 3.92144928E-10F, 8.34241E-9F,
    2.40485454E-9F, 1.05464019E-10F, 1.05464019E-10F, 2.24361973E-9F };

  /*  TRANSLATE -- variables created in this section will be declared from scratch */
  memset(&AutoMATiC_DMC_dUp[0], 0, 40U * sizeof(float));

  /* Y0tmp1 = zeros(ny*N,1); */
  /* Y0   = zeros(ny*N,1); */
  AutoMATiC_DMC_itmp = 0;
  for (AutoMATiC_DMC_i = 0; AutoMATiC_DMC_i < 20; AutoMATiC_DMC_i++) {
    for (AutoMATiC_DMC_j = 0; AutoMATiC_DMC_j < 2; AutoMATiC_DMC_j++) {
      AutoMATiC_DMC_dUp[AutoMATiC_DMC_itmp] = AD_DU->data[(AD_K-AutoMATiC_DMC_i)*2 + AutoMATiC_DMC_j];
      AutoMATiC_DMC_itmp++;
    }
  }

  /*  wyznaczenie du (optymalnie) */
  for (AutoMATiC_DMC_i = 0; AutoMATiC_DMC_i < 2; AutoMATiC_DMC_i++) {
    AutoMATiC_DMC_e[AutoMATiC_DMC_i] = AD_Z->data[AutoMATiC_DMC_i] - AD_Y->data[AD_K*2+AutoMATiC_DMC_i];
  }

  for (AutoMATiC_DMC_itmp = 0; AutoMATiC_DMC_itmp < 2; AutoMATiC_DMC_itmp++) {
    a[AutoMATiC_DMC_itmp] = 0.0F;
    for (q1 = 0; q1 < 2; q1++) {
      a[AutoMATiC_DMC_itmp] += c_a[AutoMATiC_DMC_itmp + q1*2] * (float)AutoMATiC_DMC_e[q1];
    }

    b_a[AutoMATiC_DMC_itmp] = 0.0F;
    for (q1 = 0; q1 < 40; q1++) {
      b_a[AutoMATiC_DMC_itmp] += d_a[AutoMATiC_DMC_itmp + q1*2] * AutoMATiC_DMC_dUp[q1];
    }

    b_AutoMATiC_DMC_du[AutoMATiC_DMC_itmp] = a[AutoMATiC_DMC_itmp] - b_a[AutoMATiC_DMC_itmp];
  }

  for (AutoMATiC_DMC_itmp = 0; AutoMATiC_DMC_itmp < 2; AutoMATiC_DMC_itmp++) {
    AutoMATiC_DMC_du = b_AutoMATiC_DMC_du[AutoMATiC_DMC_itmp];
    if (AutoMATiC_DMC_du > dumax) {
      AutoMATiC_DMC_du = dumax;
    }
    if (AutoMATiC_DMC_du < dumin) {
      AutoMATiC_DMC_du = dumin;
    }
		q1 = AD_K - 1;

    AutoMATiC_DMC_du += AD_U->data[q1 + AutoMATiC_DMC_itmp];
    if (AutoMATiC_DMC_du > umax) {
      AutoMATiC_DMC_du = umax;
    }
    if (AutoMATiC_DMC_du < umin) {
      AutoMATiC_DMC_du = umin;
    }

		q1 = AD_K - 1;
    AutoMATiC_DMC_du -= AD_U->data[q1 + AutoMATiC_DMC_itmp];
    b_AutoMATiC_DMC_du[AutoMATiC_DMC_itmp] = AutoMATiC_DMC_du;
  }

  for (AutoMATiC_DMC_itmp = 0; AutoMATiC_DMC_itmp < 2; AutoMATiC_DMC_itmp++) {
    control_value[AutoMATiC_DMC_itmp] = b_AutoMATiC_DMC_du[AutoMATiC_DMC_itmp];
  }

  /*  STOP */
}

/* End of code generation (dmc_a_coder.c) */
