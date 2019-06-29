#include "C:\Users\Admin\Documents\GitHub\AutoMATiC\Libs\C\defines.h"
#include "C:\Users\Admin\Documents\GitHub\AutoMATiC\Libs\C\profiler.h"
#include "C:\Users\Admin\Documents\GitHub\AutoMATiC\Libs\C\mpctools.h"
#include "C:\Users\Admin\Documents\GitHub\AutoMATiC\Libs\C\simulated_signals.h"
#include "C:\Users\Admin\Documents\GitHub\AutoMATiC\Libs\C\matrix_cal.h"
#include "C:\Users\Admin\Documents\GitHub\AutoMATiC\Libs\C\allocation_nr.h"
#include "osqp.h"
#include "util.h"
#include "stm32f7xx_hal.h"
#include <string.h>
#include "main.h"

ArchiveData ad;
CurrentControl cc;

long get_time(){ return HAL_GetTick(); }

extern void timer_loop(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    if (htim->Instance == TIM2) {
        timer_loop();
    }
}
void measurements(){
profiler_start(4,"measurements");
    new_output(&ad,__measureOutput());
profiler_end(4);
}
void controls(){
profiler_start(3,"controls' application");
    __setControlValue(last_control(&ad));
profiler_end(3);
}
void hardware_setup(){
profiler_start(1,"hardware setup");
    low_lvl_main();
profiler_end(1);
}

void controller(ArchiveData * ad, CurrentControl * c){
	static float** AutoMATiC_GPC_du;
	static long AutoMATiC_GPC_j;
	static long AutoMATiC_GPC_m;
	static long AutoMATiC_GPC_n;
	static long AutoMATiC_GPC_r;
	static float** AutoMATiC_GPC_tmpu;
	static float** control_value;
	static long j;
	static long k;
	static float** AutoMATiC_GPC_Kyzad;
	static float*** AutoMATiC_GPC_Ku;
	static float*** AutoMATiC_GPC_Ky;
	static float** dumax;
	static float** dumin;
	static float** umax;
	static float** umin;
	if(ad == NULL){
		AutoMATiC_GPC_du = darray(1,2,1,1);
		AutoMATiC_GPC_tmpu = darray(1,2,1,1);
		control_value = darray(1,1,1,2);
		AutoMATiC_GPC_Kyzad = darray(1,2,1,2);
		AutoMATiC_GPC_Kyzad[1][1] = 3.373006e-01f;
		AutoMATiC_GPC_Kyzad[1][2] = -8.539666e-02f;
		AutoMATiC_GPC_Kyzad[2][1] = -1.016548e-01f;
		AutoMATiC_GPC_Kyzad[2][2] = 5.115693e-01f;
		AutoMATiC_GPC_Ku = darray3(1,2,1,2,1,4);
		AutoMATiC_GPC_Ku[1][1][1] = -1.246174e+00f;
		AutoMATiC_GPC_Ku[1][1][2] = 1.843347e+00f;
		AutoMATiC_GPC_Ku[1][1][3] = -5.971733e-01f;
		AutoMATiC_GPC_Ku[1][1][4] = 0.000000e+00f;
		AutoMATiC_GPC_Ku[1][2][1] = -1.325670e-01f;
		AutoMATiC_GPC_Ku[1][2][2] = 3.024850e-01f;
		AutoMATiC_GPC_Ku[1][2][3] = -1.699180e-01f;
		AutoMATiC_GPC_Ku[1][2][4] = 0.000000e+00f;
		AutoMATiC_GPC_Ku[2][1][1] = -5.999027e-02f;
		AutoMATiC_GPC_Ku[2][1][2] = 2.028332e-02f;
		AutoMATiC_GPC_Ku[2][1][3] = 3.970695e-02f;
		AutoMATiC_GPC_Ku[2][1][4] = 0.000000e+00f;
		AutoMATiC_GPC_Ku[2][2][1] = -8.674656e-01f;
		AutoMATiC_GPC_Ku[2][2][2] = 1.006652e+00f;
		AutoMATiC_GPC_Ku[2][2][3] = -1.391867e-01f;
		AutoMATiC_GPC_Ku[2][2][4] = 0.000000e+00f;
		AutoMATiC_GPC_Ky = darray3(1,2,1,2,1,3);
		AutoMATiC_GPC_Ky[1][1][1] = -8.392055e-01f;
		AutoMATiC_GPC_Ky[1][1][2] = 6.226592e-01f;
		AutoMATiC_GPC_Ky[1][1][3] = -1.207543e-01f;
		AutoMATiC_GPC_Ky[1][2][1] = 1.450209e-01f;
		AutoMATiC_GPC_Ky[1][2][2] = -6.716780e-02f;
		AutoMATiC_GPC_Ky[1][2][3] = 7.543518e-03f;
		AutoMATiC_GPC_Ky[2][1][1] = 2.732700e-01f;
		AutoMATiC_GPC_Ky[2][1][2] = -2.144111e-01f;
		AutoMATiC_GPC_Ky[2][1][3] = 4.279587e-02f;
		AutoMATiC_GPC_Ky[2][2][1] = -8.538780e-01f;
		AutoMATiC_GPC_Ky[2][2][2] = 3.850181e-01f;
		AutoMATiC_GPC_Ky[2][2][3] = -4.270940e-02f;
		dumax = darray(1,1,1,2);
		dumax[1][1] = 1.000000e-02f;
		dumax[1][2] = 1.000000e-02f;
		dumin = darray(1,1,1,2);
		dumin[1][1] = -1.000000e-02f;
		dumin[1][2] = -1.000000e-02f;
		umax = darray(1,1,1,2);
		umax[1][1] = 1.000000e+00f;
		umax[1][2] = 1.000000e+00f;
		umin = darray(1,1,1,2);
		umin[1][1] = -1.000000e+00f;
		umin[1][2] = -1.000000e+00f;
		return;
	}
	for(j=1;j<=2;++j) for(k=1;k<=1;++k) AutoMATiC_GPC_du[j][k] = 0;
	for(j=1;j<=2;++j) for(k=1;k<=1;++k) AutoMATiC_GPC_tmpu[j][k] = 0;
	for(AutoMATiC_GPC_r=1;AutoMATiC_GPC_r<=2;++AutoMATiC_GPC_r){
		for(AutoMATiC_GPC_m=1;AutoMATiC_GPC_m<=2;++AutoMATiC_GPC_m){
			AutoMATiC_GPC_du[AutoMATiC_GPC_r][1]=AutoMATiC_GPC_du[AutoMATiC_GPC_r][1]+AutoMATiC_GPC_Kyzad[AutoMATiC_GPC_r][AutoMATiC_GPC_m]*ad->z[AutoMATiC_GPC_m-1];
		}
		for(AutoMATiC_GPC_n=1;AutoMATiC_GPC_n<=2;++AutoMATiC_GPC_n){
			for(AutoMATiC_GPC_j=1;AutoMATiC_GPC_j<=4;++AutoMATiC_GPC_j){
				AutoMATiC_GPC_du[AutoMATiC_GPC_r][1]=AutoMATiC_GPC_du[AutoMATiC_GPC_r][1]+AutoMATiC_GPC_Ku[AutoMATiC_GPC_r][AutoMATiC_GPC_n][AutoMATiC_GPC_j]*ad->u[ad->k-AutoMATiC_GPC_j][AutoMATiC_GPC_n-1];
			}
		}
		for(AutoMATiC_GPC_m=1;AutoMATiC_GPC_m<=2;++AutoMATiC_GPC_m){
			for(AutoMATiC_GPC_j=0;AutoMATiC_GPC_j<=2;++AutoMATiC_GPC_j){
				AutoMATiC_GPC_du[AutoMATiC_GPC_r][1]=AutoMATiC_GPC_du[AutoMATiC_GPC_r][1]+AutoMATiC_GPC_Ky[AutoMATiC_GPC_r][AutoMATiC_GPC_m][AutoMATiC_GPC_j+1]*ad->y[ad->k-AutoMATiC_GPC_j][AutoMATiC_GPC_m-1];
			}
		}
	}
	for(AutoMATiC_GPC_n=1;AutoMATiC_GPC_n<=2;++AutoMATiC_GPC_n){
		if(AutoMATiC_GPC_du[AutoMATiC_GPC_n][1]>dumax[1][AutoMATiC_GPC_n]){
			AutoMATiC_GPC_du[AutoMATiC_GPC_n][1]=dumax[1][AutoMATiC_GPC_n];
		}
		if(AutoMATiC_GPC_du[AutoMATiC_GPC_n][1]<dumin[1][AutoMATiC_GPC_n]){
			AutoMATiC_GPC_du[AutoMATiC_GPC_n][1]=dumin[1][AutoMATiC_GPC_n];
		}
		AutoMATiC_GPC_tmpu[AutoMATiC_GPC_n][1]=ad->u[ad->k-1][AutoMATiC_GPC_n-1]+AutoMATiC_GPC_du[AutoMATiC_GPC_n][1];
		if(AutoMATiC_GPC_tmpu[AutoMATiC_GPC_n][1]>umax[1][AutoMATiC_GPC_n]){
			AutoMATiC_GPC_tmpu[AutoMATiC_GPC_n][1]=umax[1][AutoMATiC_GPC_n];
		}
		if(AutoMATiC_GPC_tmpu[AutoMATiC_GPC_n][1]<umin[1][AutoMATiC_GPC_n]){
			AutoMATiC_GPC_tmpu[AutoMATiC_GPC_n][1]=umin[1][AutoMATiC_GPC_n];
		}
		AutoMATiC_GPC_du[AutoMATiC_GPC_n][1]=AutoMATiC_GPC_tmpu[AutoMATiC_GPC_n][1]-ad->u[ad->k-1][AutoMATiC_GPC_n-1];
	}
	for(j=1;j<=1;++j) for(k=1;k<=2;++k) control_value[j][k] = 0;
	for(AutoMATiC_GPC_n=1;AutoMATiC_GPC_n<=2;++AutoMATiC_GPC_n){
		control_value[1][AutoMATiC_GPC_n]=AutoMATiC_GPC_du[AutoMATiC_GPC_n][1];
	}

	set_current_control_increment(c,&(control_value[1][1])); // du is indexed starting with 1, therefore to maintain compatibility it is required to refer to first element of an actual array
}

void controller_setup(){
profiler_start(2,"software setup");
    init_archive_data(&ad, 200, 200, 2, 2, 0, 0, 0.01);
    init_current_control(&cc,&ad);
    controller(NULL,NULL);
profiler_end(2);
}

void idle(){
profiler_start(13,"other procedures");
    const int k = 0;
	static int i = 0;
	static char str[1000] = {0};

    sprintf(str, "x = [%f,%f,",ad.y[k][0], ad.y[k][1]);    write_string(str);
    sprintf(str,      "%f,%f,",ad.z[0], ad.z[1]);          write_string(str);
    sprintf(str,      "%f,%f,",ad.u[k-1][0],ad.u[k-1][1]); write_string(str);
    write_string("];\n\r");
	if(++i > 1000) {
profiler_print();
	}
profiler_end(13);
}

void loop(){
profiler_start(10,"controls' calculation");
    static int i = 0;
	     if(i< 100){ ad.z[0] = -0.1f; ad.z[1] = +0.2f; }
	else if(i< 150){ ad.z[0] = -0.1f; ad.z[1] = -0.2f; }
	else if(i< 250){ ad.z[0] = +0.1f; ad.z[1] = -0.2f; }
	else           { ad.z[0] = +0.1f; ad.z[1] = +0.2f; }
	if(++i > 300) i = 0;
	
profiler_start(50,"control algorithm");
	controller(&ad,&cc);
profiler_end(50);
	
	push_current_controls_to_archive_data(&cc,&ad);	
profiler_end(10);
}

void timeout(){
    while(1);
}