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
	static float** AutoMATiC_DMC_Y;
	static float** AutoMATiC_DMC_Yzad;
	static float** AutoMATiC_DMC_dUp;
	static float** AutoMATiC_DMC_du;
	static float** AutoMATiC_DMC_dutmp1;
	static float** AutoMATiC_DMC_dutmp2;
	static float** AutoMATiC_DMC_e;
	static long AutoMATiC_DMC_i;
	static long AutoMATiC_DMC_itmp;
	static long AutoMATiC_DMC_j;
	static long AutoMATiC_DMC_n;
	static float** AutoMATiC_DMC_tmpu;
	static float** control_value;
	static long j;
	static long k;
	static float** AutoMATiC_DMC_Ke;
	static float** AutoMATiC_DMC_Ku;
	static float** dumax;
	static float** dumin;
	static float** umax;
	static float** umin;
	if(ad == NULL){
		AutoMATiC_DMC_dUp = darray(1,8,1,1);
		AutoMATiC_DMC_Yzad = darray(1,10,1,1);
		AutoMATiC_DMC_Y = darray(1,10,1,1);
		AutoMATiC_DMC_tmpu = darray(1,2,1,1);
		AutoMATiC_DMC_e = darray(1,2,1,1);
		control_value = darray(1,1,1,2);
		AutoMATiC_DMC_dutmp1 = darray(1,2,1,1);
		AutoMATiC_DMC_Ke = darray(1,2,1,2);
		AutoMATiC_DMC_Ke[1][1] = 3.373006e-01f;
		AutoMATiC_DMC_Ke[1][2] = -8.539666e-02f;
		AutoMATiC_DMC_Ke[2][1] = -1.016548e-01f;
		AutoMATiC_DMC_Ke[2][2] = 5.115693e-01f;
		AutoMATiC_DMC_dutmp2 = darray(1,2,1,1);
		AutoMATiC_DMC_Ku = darray(1,2,1,8);
		AutoMATiC_DMC_Ku[1][1] = 1.246690e+00f;
		AutoMATiC_DMC_Ku[1][2] = 1.325999e-01f;
		AutoMATiC_DMC_Ku[1][3] = 6.350099e-01f;
		AutoMATiC_DMC_Ku[1][4] = 6.239113e-02f;
		AutoMATiC_DMC_Ku[1][5] = 3.043741e-01f;
		AutoMATiC_DMC_Ku[1][6] = 2.660202e-02f;
		AutoMATiC_DMC_Ku[1][7] = 1.005321e-01f;
		AutoMATiC_DMC_Ku[1][8] = 7.749453e-03f;
		AutoMATiC_DMC_Ku[2][1] = 6.013931e-02f;
		AutoMATiC_DMC_Ku[2][2] = 8.674500e-01f;
		AutoMATiC_DMC_Ku[2][3] = -1.172849e-01f;
		AutoMATiC_DMC_Ku[2][4] = 2.406519e-01f;
		AutoMATiC_DMC_Ku[2][5] = -7.501822e-02f;
		AutoMATiC_DMC_Ku[2][6] = 6.519486e-02f;
		AutoMATiC_DMC_Ku[2][7] = -2.764289e-02f;
		AutoMATiC_DMC_Ku[2][8] = 1.396884e-02f;
		AutoMATiC_DMC_du = darray(1,2,1,1);
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
	for(j=1;j<=8;++j) for(k=1;k<=1;++k) AutoMATiC_DMC_dUp[j][k] = 0;
	for(j=1;j<=10;++j) for(k=1;k<=1;++k) AutoMATiC_DMC_Yzad[j][k] = 0;
	for(j=1;j<=10;++j) for(k=1;k<=1;++k) AutoMATiC_DMC_Y[j][k] = 0;
	for(j=1;j<=2;++j) for(k=1;k<=1;++k) AutoMATiC_DMC_tmpu[j][k] = 0;
	AutoMATiC_DMC_itmp=1;
	for(AutoMATiC_DMC_i=1;AutoMATiC_DMC_i<=4;++AutoMATiC_DMC_i){
		for(AutoMATiC_DMC_j=1;AutoMATiC_DMC_j<=2;++AutoMATiC_DMC_j){
			AutoMATiC_DMC_dUp[AutoMATiC_DMC_itmp][1]=ad->du[ad->k-AutoMATiC_DMC_i][AutoMATiC_DMC_j-1];
			AutoMATiC_DMC_itmp=AutoMATiC_DMC_itmp+1;
		}
	}
	AutoMATiC_DMC_itmp=1;
	for(AutoMATiC_DMC_i=1;AutoMATiC_DMC_i<=5;++AutoMATiC_DMC_i){
		for(AutoMATiC_DMC_j=1;AutoMATiC_DMC_j<=2;++AutoMATiC_DMC_j){
			AutoMATiC_DMC_Yzad[AutoMATiC_DMC_itmp][1]=ad->z[AutoMATiC_DMC_j-1];
			AutoMATiC_DMC_itmp=AutoMATiC_DMC_itmp+1;
		}
	}
	AutoMATiC_DMC_itmp=1;
	for(AutoMATiC_DMC_i=1;AutoMATiC_DMC_i<=5;++AutoMATiC_DMC_i){
		for(AutoMATiC_DMC_j=1;AutoMATiC_DMC_j<=2;++AutoMATiC_DMC_j){
			AutoMATiC_DMC_Y[AutoMATiC_DMC_itmp][1]=ad->y[ad->k][AutoMATiC_DMC_j-1];
			AutoMATiC_DMC_itmp=AutoMATiC_DMC_itmp+1;
		}
	}
	for(j=1;j<=2;++j) for(k=1;k<=1;++k) AutoMATiC_DMC_e[j][k] = 0;
	for(AutoMATiC_DMC_i=1;AutoMATiC_DMC_i<=2;++AutoMATiC_DMC_i){
		AutoMATiC_DMC_e[AutoMATiC_DMC_i][1]=ad->z[AutoMATiC_DMC_i-1]-ad->y[ad->k][AutoMATiC_DMC_i-1];
	}
	productab(AutoMATiC_DMC_Ke,AutoMATiC_DMC_e,AutoMATiC_DMC_dutmp1,2,2,2,1);
	productab(AutoMATiC_DMC_Ku,AutoMATiC_DMC_dUp,AutoMATiC_DMC_dutmp2,2,8,8,1);
	sumaa(AutoMATiC_DMC_dutmp1,AutoMATiC_DMC_dutmp2,AutoMATiC_DMC_du,2,1,-1);
	for(AutoMATiC_DMC_n=1;AutoMATiC_DMC_n<=2;++AutoMATiC_DMC_n){
		if(AutoMATiC_DMC_du[AutoMATiC_DMC_n][1]>dumax[1][AutoMATiC_DMC_n]){
			AutoMATiC_DMC_du[AutoMATiC_DMC_n][1]=dumax[1][AutoMATiC_DMC_n];
		}
		if(AutoMATiC_DMC_du[AutoMATiC_DMC_n][1]<dumin[1][AutoMATiC_DMC_n]){
			AutoMATiC_DMC_du[AutoMATiC_DMC_n][1]=dumin[1][AutoMATiC_DMC_n];
		}
		AutoMATiC_DMC_tmpu[AutoMATiC_DMC_n][1]=ad->u[ad->k-1][AutoMATiC_DMC_n-1]+AutoMATiC_DMC_du[AutoMATiC_DMC_n][1];
		if(AutoMATiC_DMC_tmpu[AutoMATiC_DMC_n][1]>umax[1][AutoMATiC_DMC_n]){
			AutoMATiC_DMC_tmpu[AutoMATiC_DMC_n][1]=umax[1][AutoMATiC_DMC_n];
		}
		if(AutoMATiC_DMC_tmpu[AutoMATiC_DMC_n][1]<umin[1][AutoMATiC_DMC_n]){
			AutoMATiC_DMC_tmpu[AutoMATiC_DMC_n][1]=umin[1][AutoMATiC_DMC_n];
		}
		AutoMATiC_DMC_du[AutoMATiC_DMC_n][1]=AutoMATiC_DMC_tmpu[AutoMATiC_DMC_n][1]-ad->u[ad->k-1][AutoMATiC_DMC_n-1];
	}
	for(j=1;j<=1;++j) for(k=1;k<=2;++k) control_value[j][k] = 0;
	for(AutoMATiC_DMC_n=1;AutoMATiC_DMC_n<=2;++AutoMATiC_DMC_n){
		control_value[1][AutoMATiC_DMC_n]=AutoMATiC_DMC_du[AutoMATiC_DMC_n][1];
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