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


ArchiveData ad;
CurrentControl cc;

void controller_setup(){
profiler_start(2);
    init_archive_data(&ad, 200, 200, U_SIZE, Y_SIZE, 0, 0, 0.01);
    init_current_control(&cc,&ad);
    controller(NULL,NULL);
profiler_end(2);
}

void idle(){
profiler_start(13);
    const int k = 0;
	static char str[1000] = {0};

    sprintf(str, "x = [%f,%f,",ad.y[k][0], ad.y[k][1]);    write_string(str);
    sprintf(str,      "%f,%f,",ad.z[0], ad.z[1]);          write_string(str);
    sprintf(str,      "%f,%f,",ad.u[k-1][0],ad.u[k-1][1]); write_string(str);
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

void timeout(){
    while(1);
}
