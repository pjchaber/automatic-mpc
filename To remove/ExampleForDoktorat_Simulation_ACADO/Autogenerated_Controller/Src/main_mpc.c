#include "stm32f7xx_hal.h"
#include <string.h>
#include "low_lvl_main.h"
#include "acado_common.h"
#include <stdio.h>

/* Some convenient definitions. */
#define NX          ACADO_NX  // 2 /* Number of differential state variables.  */
#define NXA         ACADO_NXA // 0 /* Number of algebraic variables. */
#define NU          ACADO_NU  // 2 /* Number of control inputs. */
#define NOD         ACADO_NOD // 0 /* Number of online data values. */   
#define NY          ACADO_NY  // 4 /* Number of measurements/references on nodes 0..N - 1. */
#define NYN         ACADO_NYN // 2 /* Number of measurements/references on node N. */
#define N           ACADO_N   //10 /* Number of intervals in the horizon. */

/* Global variables used by the solver. */
ACADOvariables acadoVariables;
ACADOworkspace acadoWorkspace;

char str[1000];
int ready = 0;

extern ADC_HandleTypeDef hadc3;
extern DMA_HandleTypeDef hdma_adc3;

extern DAC_HandleTypeDef hdac;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim5;

extern UART_HandleTypeDef huart1;

float fb_time = 0.0f;
float prep_time = 0.0f;
int iteration = 0;
float control_value[2];
double measured_values[2];
double set_point[2];
	
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
	float * o = measureOutput();
	for(i=0;i<2;++i) measured_values[i] = o[i];
}

void controller_setup(){
	int i = 0;
	/* Initialize the solver. */
	acado_initializeSolver();

	/* Initialize the states and controls. */
	for (i = 0; i < NX * (N + 1); ++i)  acadoVariables.x[ i ] = 0.0;
	for (i = 0; i < NU * N; ++i)        acadoVariables.u[ i ] = 0.0;

	/* Initialize the measurements/reference. */
	for (i = 0; i < NY * N; ++i)  acadoVariables.y[ i ] = 0.0;
	for (i = 0; i < NYN; ++i)     acadoVariables.yN[ i ] = 0.0;

	/* Prepare first step */
	acado_preparationStep();
}

void idle(){
	int i;
//	write_string("cu=[");
//	for (i = 0; i < NU * N; ++i) {
//		sprintf(str, "%.3f, ", acadoVariables.u[i]);
//		write_string(str);
//	}
//	write_string("];");
//	write_string("cx=[");
//	for (i = 0; i < NX * N; ++i) {
//		sprintf(str, "%.3f, ", acadoVariables.x[i]);
//		write_string(str);
//	}
//	write_string("];");
//	write_string("cy=[");
//	for (i = 0; i < NY * N; ++i) {
//		sprintf(str, "%.3f, ", acadoVariables.y[i]);
//		write_string(str);
//	}
//	write_string("];");
//	write_string("cyn=[");
//	for (i = 0; i < NYN; ++i) {
//		sprintf(str, "%.3f, ", acadoVariables.yN[i]);
//		write_string(str);
//	}
//	write_string("];");
  sprintf(str, "x = [%d,", iteration);
  write_string(str);
  sprintf(str, "%f,%f,", measured_values[0],measured_values[1]);
  write_string(str);
//  sprintf(str, "%f,%f,", set_point[0]  , set_point[1]);
	sprintf(str, "%f,%f,", acadoVariables.y[0]  , acadoVariables.y[1]);	
  write_string(str);
  sprintf(str, "     %f,%f,", control_value[0]  , control_value[1]);
  write_string(str);
}

void change_setpoint(float y1, float y2){
	int i;
	for (i = 0; i < (N-1); ++i){
		acadoVariables.y[ 4*i+0 ] = acadoVariables.y[4*(i+1)+0];
		acadoVariables.y[ 4*i+1 ] = acadoVariables.y[4*(i+1)+1];
	}
	acadoVariables.y[ 4*(N-1)+0 ] = y1;
	acadoVariables.y[ 4*(N-1)+1 ] = y2;
	acadoVariables.yN[ 0 ] = y1;
	acadoVariables.yN[ 1 ] = y2;
	set_point[0] = y1;
	set_point[1] = y2;
}
	

void loop(){
			 if(iteration< 50) change_setpoint( 0.1, 0.2);
	else if(iteration<100) change_setpoint(-0.1, 0.2);
	else if(iteration<150) change_setpoint(-0.1,-0.2);
	else if(iteration<200) change_setpoint( 0.1,-0.2);
	else if(iteration<250) change_setpoint( 0.1, 0.2);
	else if(iteration<300) change_setpoint(-0.1, 0.2);
	else if(iteration<350) change_setpoint(-0.1,-0.2);
	else if(iteration<400) change_setpoint( 0.1,-0.2);
	else if(iteration<450) change_setpoint( 0.1, 0.2);
	else if(iteration<500) change_setpoint(-0.1, 0.2);
	else if(iteration<550) change_setpoint(-0.1,-0.2);
	else if(iteration<600) change_setpoint( 0.1,-0.2);
}

void controls(){
    int i = 0;
    for(i=0;i<2;++i) control_value[i] = acadoVariables.u[0+i];
    set_control_value(control_value);
}

int main(int argc, char const *argv[])
{
	int i,j;
	hardware_setup();
	controller_setup();

	/* The "real-time iterations" loop. */
	for(iteration=0; iteration < 300; ++iteration)
	{
		measurements();	
		for (i = 0; i < NX; ++i)
			acadoVariables.x0[ i ] = measured_values[i];
		
//		for (i = 0; i < NX; ++i)
//			acadoVariables.x0[ i ] = acadoVariables.x[NX + i];
		
//		for (j = 0; j < NY; ++j)
//			acadoVariables.y[i * NY + j] = measured_values[ j ];
//		
//		for (j = 0; j < NYN; ++j)
//			acadoVariables.yN[j] = measured_values[ j ];

		//
		/* Perform the feedback step. */
		htim5.Instance->CNT = 0; // get timer counter			
		acado_feedbackStep( );
		fb_time = (htim5.Instance->CNT)/108.0f; // get timer counter			
		
//		for (i = 0; i < NX; ++i)
//			acadoVariables.x0[ i ] = acadoVariables.x[NX + i];

		/* Apply the new control immediately to the process, first NU components. */
		controls();
		loop();
		
		/* Optional: shift the initialization (look at acado_common.h). */
		acado_shiftStates(2, 0, 0);
		acado_shiftControls( 0 );
		idle();

		/* Prepare for the next step. */
		htim5.Instance->CNT = 0; // get timer counter			
		acado_preparationStep();
		prep_time = (htim5.Instance->CNT)/108.0f; // get timer counter		
		
  sprintf(str, "%f,%f];\n\r", fb_time  , prep_time);
	write_string(str);
		ready = 0;

		while(!ready);
	}
	while(1);
	return 0;
}

