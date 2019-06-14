#include "stm32f7xx_hal.h"
#include <string.h>
#include "low_lvl_main.h"
#include "mat_lib.h"
#include "rt_nonfinite.h"
#include "dmc_a_coder.h"
#include "dmc_a_coder_terminate.h"
#include "dmc_a_coder_emxAPI.h"
#include "dmc_a_coder_initialize.h"

/* Function Declarations */
static emxArray_real32_T *argInit_1xUnbounded_real32_T(void);
static float argInit_real32_T(void);
static emxArray_real32_T *c_argInit_UnboundedxUnbounded_r(void);

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


char str[100];
int alg = 0;
int ready = 0;

extern ADC_HandleTypeDef hadc3;
extern DMA_HandleTypeDef hdma_adc3;

extern DAC_HandleTypeDef hdac;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim5;

extern UART_HandleTypeDef huart1;

extern void timer_loop(void);

emxArray_real32_T *AD_Y;
emxArray_real32_T *AD_U;
emxArray_real32_T *AD_DU;
emxArray_real32_T *AD_Z;
int iteration = 0;
double control_value[2];
float f_control_value[2];

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    if (htim->Instance == TIM2) {
        ready = 1;
    }
}

long get_time(){
    return HAL_GetTick();
}

float* measureOutput(){
    return __measureOutput(); // values from -1 to 1
}

void set_control_value(float* value){ // values from -1 to 1
    __setControlValue(value);
}

void hardware_setup(){
    low_lvl_main();
}

void measurements(){
    int i = 0;
    float* o = measureOutput();
    for(i=0;i<2;++i){
        AD_Y->data[iteration*2+i] = o[i];
    }
}

void controller_setup(){
    dmc_a_coder_initialize();
}

void idle(){
    sprintf(str, "x = [%f,%f;", (float)(AD_Y->data[iteration*2+0]), (float)(AD_Y->data[iteration*2+1]));
    write_string(str);
    sprintf(str,      "%f,%f;", (float)(AD_Z->data[0]),(float)(AD_Z->data[1]));
    write_string(str);
    sprintf(str,      "%f,%f];\n\r", (float)(AD_U->data[iteration*2+0]),(float)(AD_U->data[iteration*2+1]));
    write_string(str);
}

void loop(){
    // 0: 225-525, 500-600
    // 1: 0-225, 425-500; 
         if(iteration< 50){ AD_Z->data[0] =  0.1; AD_Z->data[1] =  0.2; }
    else if(iteration<100){ AD_Z->data[0] = -0.1; AD_Z->data[1] =  0.2; }
    else if(iteration<150){ AD_Z->data[0] = -0.1; AD_Z->data[1] = -0.2; }
    else if(iteration<200){ AD_Z->data[0] =  0.1; AD_Z->data[1] = -0.2; }
    else if(iteration<250){ AD_Z->data[0] =  0.1; AD_Z->data[1] =  0.2; }
    else if(iteration<300){ AD_Z->data[0] = -0.1; AD_Z->data[1] =  0.2; }
    else if(iteration<350){ AD_Z->data[0] = -0.1; AD_Z->data[1] = -0.2; }
    else if(iteration<400){ AD_Z->data[0] =  0.1; AD_Z->data[1] = -0.2; }
    else if(iteration<450){ AD_Z->data[0] =  0.1; AD_Z->data[1] =  0.2; }
    else if(iteration<500){ AD_Z->data[0] = -0.1; AD_Z->data[1] =  0.2; }
    else if(iteration<550){ AD_Z->data[0] = -0.1; AD_Z->data[1] = -0.2; }
    else if(iteration<600){ AD_Z->data[0] =  0.1; AD_Z->data[1] = -0.2; }
}

void controls(){
    int i = 0;
    for(i=0;i<2;++i){
				f_control_value[i] = control_value[i];
        AD_DU->data[iteration*2+i] = f_control_value[i];
        AD_U->data[iteration*2+i] = AD_U->data[(iteration-1)*2+i]+f_control_value[i];
    }
    set_control_value(&(AD_U->data[iteration*2]));
}

int main(int argc, char const *argv[])
{
    hardware_setup();
    controller_setup();

    /* Call the entry-point 'dmc_a_coder'. */
    /* Initialize function 'dmc_a_coder' input arguments. */
  /* Initialize function 'dmc_a_coder' input arguments. */
  /* Initialize function input argument 'AD_Y'. */
  AD_Y = c_argInit_UnboundedxUnbounded_r();

  /* Initialize function input argument 'AD_U'. */
  AD_U = c_argInit_UnboundedxUnbounded_r();

  /* Initialize function input argument 'AD_DU'. */
  AD_DU = c_argInit_UnboundedxUnbounded_r();

  /* Initialize function input argument 'AD_Z'. */
  AD_Z = argInit_1xUnbounded_real32_T();

    for(iteration=50; iteration < 1000; ++iteration){
        measurements();
        dmc_a_coder(AD_Y, AD_U, AD_DU, AD_Z, iteration, -1.0, 1.0, -0.1, 0.1, control_value);
        loop();
        controls();
        idle();
        ready = 0;

        while(!ready);
    }
//    emxDestroyArray_real_T(AD_Z);

//    emxDestroyArray_real_T(AD_DU);
//    emxDestroyArray_real_T(AD_U);

//    emxDestroyArray_real_T(AD_Y);

//    dmc_a_coder_terminate();
//		
		while(1);
		return 0;
}
