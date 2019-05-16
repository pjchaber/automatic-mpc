#include "stm32f7xx_hal.h"
#include <string.h>
#include "low_lvl_main.h"
#include "controller.c" // dirty solution!!!
#include <stdio.h>

char str[1];
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
double U[MPT_RANGE];
double X[MPT_DOMAIN];
	
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
	for(i=0;i<2;++i) X[i] = o[i];
}

void controller_setup(){
}

void idle(){
	int i;
  sprintf(str, "x = [%d,", iteration);
  write_string(str);
  sprintf(str, "%f,%f,", X[0],X[1]);
  write_string(str);
//  sprintf(str, "%f,%f,", set_point[0]  , set_point[1]);
	sprintf(str, "%f,%f,", X[2]  , X[3]);	
  write_string(str);
  sprintf(str, "%f,%f,", U[0]  , U[1]);
  write_string(str);
	sprintf(str, "%f,%f];\n\r", fb_time  , prep_time);
	write_string(str);
}

void change_setpoint(float y1, float y2){
	int i;
	X[2] = y1;
	X[3] = y2;
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
    for(i=0;i<2;++i) control_value[i] = U[i]; 
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
		htim5.Instance->CNT = 0; // get timer counter			
		controller(X,U);
		fb_time = (htim5.Instance->CNT)/108.0f; // get timer counter			
		controls();
		loop();
		idle();

		ready = 0;

		while(!ready);
	}
	while(1);
	return 0;
}

