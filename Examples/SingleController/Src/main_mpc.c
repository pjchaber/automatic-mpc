#include "C:\Users\Admin\Documents\GitHub\AutoMATiC\Libs\C\defines.h"
#include "C:\Users\Admin\Documents\GitHub\AutoMATiC\Libs\C\profiler.h"
#include "C:\Users\Admin\Documents\GitHub\AutoMATiC\Libs\C\mpctools.h"
#include "C:\Users\Admin\Documents\GitHub\AutoMATiC\Libs\C\simulated_signals.h"
#include "C:\Users\Admin\Documents\GitHub\AutoMATiC\Libs\C\obl_macierzowe.h"
#include "C:\Users\Admin\Documents\GitHub\AutoMATiC\Libs\C\mat_lib.h"
#include "C:\Users\Admin\Documents\GitHub\AutoMATiC\Libs\C\alokacja_nr.h"
#include "C:\Users\Admin\Documents\GitHub\AutoMATiC\Libs\C\pk.h"
#include "stm32f7xx_hal.h"
#include <string.h>
#include "main.h"
#include "mat_lib.h"

#define U_SIZE 2
#define Y_SIZE 2

extern void timer_loop(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    if (htim->Instance == TIM2) {
        timer_loop();
    }
}

long get_time(){
    return HAL_GetTick();
}

void hardware_setup(){
profiler_start(1);
    low_lvl_main();
profiler_end(1);
}

void controller(ArchiveData * ad, CurrentControl * c){
	static float** control_value;
	static float** du;
	static float** dutmp;
	static float** e;
	static long n;
	static float** tmpu;
	static long j;
	static long k;
	static float** r;
	static float** to_vec;
	if(ad == NULL){
		dutmp = dtablica(1,2,1,2);
		du = dtablica(1,2,1,1);
		e = dtablica(1,2,1,3);
		tmpu = dtablica(1,2,1,1);
		control_value = dtablica(1,1,1,2);
		r = dtablica(1,3,1,2);
		r[1][1] = 0.000000e+00f;
		r[1][2] = 4.500000e+00f;
		r[2][1] = -4.050000e+00f;
		r[2][2] = -1.305000e+01f;
		r[3][1] = 4.950000e+00f;
		r[3][2] = 9.450000e+00f;
		to_vec = dtablica(1,2,1,1);
		to_vec[1][1] = 1.000000e+00f;
		to_vec[2][1] = 1.000000e+00f;
		return;
	}
	for(j=1;j<=2;++j) for(k=1;k<=2;++k) dutmp[j][k] = 0;
	for(j=1;j<=2;++j) for(k=1;k<=1;++k) du[j][k] = 0;
	for(j=1;j<=2;++j) for(k=1;k<=3;++k) e[j][k] = 0;
	for(j=1;j<=2;++j) for(k=1;k<=1;++k) tmpu[j][k] = 0;
	for(j=1;j<=1;++j) for(k=1;k<=2;++k) control_value[j][k] = 0;
	for(n=1;n<=2;++n){
		e[n][1]=ad->z[n-1]-ad->y[ad->k-0][n-1];
		e[n][2]=ad->z[n-1]-ad->y[ad->k-1][n-1];
		e[n][3]=ad->z[n-1]-ad->y[ad->k-2][n-1];
	}
	iloczynab(r,e,dutmp,3,2,2,3);
	iloczynab(dutmp,to_vec,du,2,2,2,1);
	for(n=1;n<=2;++n){
		control_value[1][n]=du[n][1];
	}

	set_current_control_increment(c,&(control_value[1][1])); // du is indexed starting with 1, therefore to maintain compatibility it is required to refer to first element of an actual array
}

ArchiveData ad;
CurrentControl cc;

void measurements(){
profiler_start(4);
    new_output(&ad,__measureOutput());
profiler_end(4);
}

void controller_setup(){
profiler_start(2);
    init_archive_data(&ad, 200, 200, U_SIZE, Y_SIZE, 0, 0, 0.01);
    init_current_control(&cc,&ad);
    get_time();
    controller(NULL,NULL);
    //controller2(NULL,NULL);
profiler_end(2);
}

void idle(){
profiler_start(13);
    const int k = 0;
	static char str[1000] = {0};

    // Komunikacja z komputerem zbierającym dane 
    sprintf(str, "x = [%d,%f,%f,",0, ad.y[k][0], ad.y[k][1]);
    write_string(str);
    sprintf(str,      "%f,%f,", ad.z[0], ad.z[1]);
    write_string(str);
    sprintf(str,      "%f,%f, ", ad.u[k-1][0],ad.u[k-1][1]);
    write_string(str);
    write_string("];\n\r");
profiler_end(13);
}

void loop(){
profiler_start(10);
    static int i = 0;
	if(i<  50){ ad.z[0] = -0.1; ad.z[1] =  0.2; }
	else      { ad.z[0] =  0.1; ad.z[1] = -0.2; }
    if(++i > 100) i = 0;
	
profiler_start(50);
	controller(&ad,&cc);
profiler_end(50);
	
    push_current_controls_to_archive_data(&cc,&ad);	
profiler_end(10);
}

void controls(){
profiler_start(3);
    __setControlValue(last_control(&ad));
profiler_end(3);
}

void timeout(){
    while(1);
}
