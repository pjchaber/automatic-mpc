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
profiler_start(4);
    new_output(&ad,__measureOutput());
profiler_end(4);
}
void controls(){
profiler_start(3);
    __setControlValue(last_control(&ad));
profiler_end(3);
}
void hardware_setup(){
profiler_start(1);
    low_lvl_main();
profiler_end(1);
}

void controller(ArchiveData * ad, CurrentControl * c){
	static float** control_value;
	static float** du;
	static float** e;
	static float** er;
	static long n;
	static float** tmpu;
	static long j;
	static long k;
	static float** r;
	static float** dumax;
	static float** dumin;
	static float** umax;
	static float** umin;
	if(ad == NULL){
		e = darray(1,2,1,3);
		tmpu = darray(1,2,1,1);
		er = darray(1,2,1,3);
		du = darray(1,2,1,1);
		control_value = darray(1,1,1,2);
		r = darray(1,3,1,2);
		r[1][1] = 0.000000e+00f;
		r[1][2] = 0.000000e+00f;
		r[2][1] = -9.500000e-02f;
		r[2][2] = -2.500000e-02f;
		r[3][1] = 1.050000e-01f;
		r[3][2] = 7.500000e-02f;
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
	for(j=1;j<=2;++j) for(k=1;k<=3;++k) e[j][k] = 0;
	for(j=1;j<=2;++j) for(k=1;k<=1;++k) tmpu[j][k] = 0;
	for(j=1;j<=2;++j) for(k=1;k<=3;++k) er[j][k] = 0;
	for(j=1;j<=2;++j) for(k=1;k<=1;++k) du[j][k] = 0;
	for(j=1;j<=1;++j) for(k=1;k<=2;++k) control_value[j][k] = 0;
	for(n=1;n<=2;++n){
		e[n][1]=ad->z[n-1]-ad->y[ad->k-0][n-1];
		e[n][2]=ad->z[n-1]-ad->y[ad->k-1][n-1];
		e[n][3]=ad->z[n-1]-ad->y[ad->k-2][n-1];
		er[n][1]=e[n][1]*r[1][n];
		er[n][2]=e[n][2]*r[2][n];
		er[n][3]=e[n][3]*r[3][n];
		du[n][1]=du[n][1]+er[n][1];
		du[n][1]=du[n][1]+er[n][2];
		du[n][1]=du[n][1]+er[n][3];
		if(du[n][1]>dumax[1][n]){
			du[n][1]=dumax[1][n];
		}
		if(du[n][1]<dumin[1][n]){
			du[n][1]=dumin[1][n];
		}
		tmpu[n][1]=ad->u[ad->k-1][n-1]+du[n][1];
		if(tmpu[n][1]>umax[1][n]){
			tmpu[n][1]=umax[1][n];
		}
		if(tmpu[n][1]<umin[1][n]){
			tmpu[n][1]=umin[1][n];
		}
		du[n][1]=tmpu[n][1]-ad->u[ad->k-1][n-1];
	}
	for(n=1;n<=2;++n){
		control_value[1][n]=du[n][1];
	}

	set_current_control_increment(c,&(control_value[1][1])); // du is indexed starting with 1, therefore to maintain compatibility it is required to refer to first element of an actual array
}

void controller_setup(){
profiler_start(2);
    init_archive_data(&ad, 200, 200, 2, 2, 0, 0, 0.01);
    init_current_control(&cc,&ad);
    controller(NULL,NULL);
profiler_end(2);
}

void idle(){
profiler_start(13);
    const int k = 0;
	static int i = 0;
	static char str[1000] = {0};

    sprintf(str, "x = [%f,%f,",ad.y[k][0], ad.y[k][1]);    write_string(str);
    sprintf(str,      "%f,%f,",ad.z[0], ad.z[1]);          write_string(str);
    sprintf(str,      "%f,%f,",ad.u[k-1][0],ad.u[k-1][1]); write_string(str);
    write_string("];\n\r");
	if(++i > 1000) profiler_print();
profiler_end(13);
}

void loop(){
profiler_start(10);
    static int i = 0;
	     if(i< 100){ ad.z[0] = -0.1f; ad.z[1] = +0.2f; }
	else if(i< 150){ ad.z[0] = -0.1f; ad.z[1] = -0.2f; }
	else if(i< 250){ ad.z[0] = +0.1f; ad.z[1] = -0.2f; }
	else           { ad.z[0] = +0.1f; ad.z[1] = +0.2f; }
	if(++i > 300) i = 0;
	
profiler_start(50);
	controller(&ad,&cc);
profiler_end(50);
	
	push_current_controls_to_archive_data(&cc,&ad);	
profiler_end(10);
}

void timeout(){
    while(1);
}
