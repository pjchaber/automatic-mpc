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
	static float** AutoMATiC_DMC_Y;
	static float** AutoMATiC_DMC_Yzad;
	static float** AutoMATiC_DMC_btmp1;
	static float** AutoMATiC_DMC_btmp2;
	static float** AutoMATiC_DMC_dUp;
	static float** AutoMATiC_DMC_du;
	static float** AutoMATiC_DMC_dutmp1;
	static float** AutoMATiC_DMC_dutmp2;
	static float** AutoMATiC_DMC_e;
	static float** AutoMATiC_DMC_ftmp1;
	static float** AutoMATiC_DMC_ftmp2;
	static float** AutoMATiC_DMC_ftmp3;
	static float** AutoMATiC_DMC_ftmp4;
	static long AutoMATiC_DMC_i;
	static long AutoMATiC_DMC_itmp;
	static long AutoMATiC_DMC_j;
	static long AutoMATiC_DMC_n;
	static float** AutoMATiC_DMC_tmpu;
	static float** AutoMATiC_DMC_uk;
	static float** control_value;
	static long j;
	static long k;
	static float** AutoMATiC_DMC_Ke;
	static float** AutoMATiC_DMC_Ku;
	static float** AutoMATiC_DMC_Mp;
	static float** AutoMATiC_DMC_fconst;
	static float** AutoMATiC_DMC_bvar;
	static float** AutoMATiC_DMC_b;
	static float** dumax;
	static float** dumin;
	static float** umax;
	static float** umin;
	static c_float AutoMATiC_DMC_A_x[80];
	static c_int AutoMATiC_DMC_A_i[80];
	static c_int AutoMATiC_DMC_A_p[11];

	static c_float AutoMATiC_DMC_H_x[66];
	static c_int AutoMATiC_DMC_H_i[66];
	static c_int AutoMATiC_DMC_H_p[11];

	static OSQPSettings *osqp_settings;
	static OSQPWorkspace *osqp_work;
	static OSQPData *osqp_data;
	static c_float osqp_q[10];
	static c_float osqp_lb[40];
	static c_float osqp_ub[40];
	static c_float AutoMATiC_DMC_ftmp[11];
	static c_float AutoMATiC_DMC_btmp[41];
	static c_float AutoMATiC_DMC_qpx[11];
	if(ad == NULL){
		AutoMATiC_DMC_A_x[0] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[1] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[2] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[3] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[4] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[5] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[6] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[7] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[8] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[9] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[10] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[11] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[12] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[13] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[14] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[15] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[16] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[17] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[18] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[19] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[20] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[21] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[22] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[23] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[24] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[25] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[26] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[27] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[28] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[29] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[30] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[31] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[32] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[33] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[34] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[35] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[36] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[37] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[38] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[39] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[40] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[41] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[42] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[43] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[44] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[45] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[46] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[47] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[48] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[49] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[50] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[51] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[52] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[53] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[54] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[55] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[56] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[57] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[58] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[59] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[60] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[61] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[62] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[63] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[64] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[65] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[66] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[67] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[68] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[69] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[70] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[71] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[72] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[73] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[74] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[75] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[76] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[77] = -1.000000e+00f;
		AutoMATiC_DMC_A_x[78] = 1.000000e+00f;
		AutoMATiC_DMC_A_x[79] = 1.000000e+00f;
		AutoMATiC_DMC_A_i[0] = 0;
		AutoMATiC_DMC_A_i[1] = 10;
		AutoMATiC_DMC_A_i[2] = 12;
		AutoMATiC_DMC_A_i[3] = 14;
		AutoMATiC_DMC_A_i[4] = 16;
		AutoMATiC_DMC_A_i[5] = 18;
		AutoMATiC_DMC_A_i[6] = 20;
		AutoMATiC_DMC_A_i[7] = 30;
		AutoMATiC_DMC_A_i[8] = 32;
		AutoMATiC_DMC_A_i[9] = 34;
		AutoMATiC_DMC_A_i[10] = 36;
		AutoMATiC_DMC_A_i[11] = 38;
		AutoMATiC_DMC_A_i[12] = 1;
		AutoMATiC_DMC_A_i[13] = 11;
		AutoMATiC_DMC_A_i[14] = 13;
		AutoMATiC_DMC_A_i[15] = 15;
		AutoMATiC_DMC_A_i[16] = 17;
		AutoMATiC_DMC_A_i[17] = 19;
		AutoMATiC_DMC_A_i[18] = 21;
		AutoMATiC_DMC_A_i[19] = 31;
		AutoMATiC_DMC_A_i[20] = 33;
		AutoMATiC_DMC_A_i[21] = 35;
		AutoMATiC_DMC_A_i[22] = 37;
		AutoMATiC_DMC_A_i[23] = 39;
		AutoMATiC_DMC_A_i[24] = 2;
		AutoMATiC_DMC_A_i[25] = 12;
		AutoMATiC_DMC_A_i[26] = 14;
		AutoMATiC_DMC_A_i[27] = 16;
		AutoMATiC_DMC_A_i[28] = 18;
		AutoMATiC_DMC_A_i[29] = 22;
		AutoMATiC_DMC_A_i[30] = 32;
		AutoMATiC_DMC_A_i[31] = 34;
		AutoMATiC_DMC_A_i[32] = 36;
		AutoMATiC_DMC_A_i[33] = 38;
		AutoMATiC_DMC_A_i[34] = 3;
		AutoMATiC_DMC_A_i[35] = 13;
		AutoMATiC_DMC_A_i[36] = 15;
		AutoMATiC_DMC_A_i[37] = 17;
		AutoMATiC_DMC_A_i[38] = 19;
		AutoMATiC_DMC_A_i[39] = 23;
		AutoMATiC_DMC_A_i[40] = 33;
		AutoMATiC_DMC_A_i[41] = 35;
		AutoMATiC_DMC_A_i[42] = 37;
		AutoMATiC_DMC_A_i[43] = 39;
		AutoMATiC_DMC_A_i[44] = 4;
		AutoMATiC_DMC_A_i[45] = 14;
		AutoMATiC_DMC_A_i[46] = 16;
		AutoMATiC_DMC_A_i[47] = 18;
		AutoMATiC_DMC_A_i[48] = 24;
		AutoMATiC_DMC_A_i[49] = 34;
		AutoMATiC_DMC_A_i[50] = 36;
		AutoMATiC_DMC_A_i[51] = 38;
		AutoMATiC_DMC_A_i[52] = 5;
		AutoMATiC_DMC_A_i[53] = 15;
		AutoMATiC_DMC_A_i[54] = 17;
		AutoMATiC_DMC_A_i[55] = 19;
		AutoMATiC_DMC_A_i[56] = 25;
		AutoMATiC_DMC_A_i[57] = 35;
		AutoMATiC_DMC_A_i[58] = 37;
		AutoMATiC_DMC_A_i[59] = 39;
		AutoMATiC_DMC_A_i[60] = 6;
		AutoMATiC_DMC_A_i[61] = 16;
		AutoMATiC_DMC_A_i[62] = 18;
		AutoMATiC_DMC_A_i[63] = 26;
		AutoMATiC_DMC_A_i[64] = 36;
		AutoMATiC_DMC_A_i[65] = 38;
		AutoMATiC_DMC_A_i[66] = 7;
		AutoMATiC_DMC_A_i[67] = 17;
		AutoMATiC_DMC_A_i[68] = 19;
		AutoMATiC_DMC_A_i[69] = 27;
		AutoMATiC_DMC_A_i[70] = 37;
		AutoMATiC_DMC_A_i[71] = 39;
		AutoMATiC_DMC_A_i[72] = 8;
		AutoMATiC_DMC_A_i[73] = 18;
		AutoMATiC_DMC_A_i[74] = 28;
		AutoMATiC_DMC_A_i[75] = 38;
		AutoMATiC_DMC_A_i[76] = 9;
		AutoMATiC_DMC_A_i[77] = 19;
		AutoMATiC_DMC_A_i[78] = 29;
		AutoMATiC_DMC_A_i[79] = 39;
		AutoMATiC_DMC_A_p[0] = 0;
		AutoMATiC_DMC_A_p[1] = 12;
		AutoMATiC_DMC_A_p[2] = 24;
		AutoMATiC_DMC_A_p[3] = 34;
		AutoMATiC_DMC_A_p[4] = 44;
		AutoMATiC_DMC_A_p[5] = 52;
		AutoMATiC_DMC_A_p[6] = 60;
		AutoMATiC_DMC_A_p[7] = 66;
		AutoMATiC_DMC_A_p[8] = 72;
		AutoMATiC_DMC_A_p[9] = 76;
		AutoMATiC_DMC_A_p[10] = 80;

		AutoMATiC_DMC_H_x[0] = 1.344566e+02f;
		AutoMATiC_DMC_H_x[1] = 4.114478e+01f;
		AutoMATiC_DMC_H_x[2] = 1.000269e+02f;
		AutoMATiC_DMC_H_x[3] = 3.169500e+01f;
		AutoMATiC_DMC_H_x[4] = 6.190011e+01f;
		AutoMATiC_DMC_H_x[5] = 2.023139e+01f;
		AutoMATiC_DMC_H_x[6] = 2.567725e+01f;
		AutoMATiC_DMC_H_x[7] = 8.808511e+00f;
		AutoMATiC_DMC_H_x[8] = 4.114478e+01f;
		AutoMATiC_DMC_H_x[9] = 3.436150e+01f;
		AutoMATiC_DMC_H_x[10] = 3.099487e+01f;
		AutoMATiC_DMC_H_x[11] = 2.477126e+01f;
		AutoMATiC_DMC_H_x[12] = 1.931418e+01f;
		AutoMATiC_DMC_H_x[13] = 1.576652e+01f;
		AutoMATiC_DMC_H_x[14] = 8.233726e+00f;
		AutoMATiC_DMC_H_x[15] = 6.910587e+00f;
		AutoMATiC_DMC_H_x[16] = 1.000269e+02f;
		AutoMATiC_DMC_H_x[17] = 3.099487e+01f;
		AutoMATiC_DMC_H_x[18] = 8.804002e+01f;
		AutoMATiC_DMC_H_x[19] = 2.792375e+01f;
		AutoMATiC_DMC_H_x[20] = 5.644363e+01f;
		AutoMATiC_DMC_H_x[21] = 1.883764e+01f;
		AutoMATiC_DMC_H_x[22] = 2.413991e+01f;
		AutoMATiC_DMC_H_x[23] = 8.414358e+00f;
		AutoMATiC_DMC_H_x[24] = 3.169500e+01f;
		AutoMATiC_DMC_H_x[25] = 2.477126e+01f;
		AutoMATiC_DMC_H_x[26] = 2.792375e+01f;
		AutoMATiC_DMC_H_x[27] = 2.454154e+01f;
		AutoMATiC_DMC_H_x[28] = 1.838345e+01f;
		AutoMATiC_DMC_H_x[29] = 1.514642e+01f;
		AutoMATiC_DMC_H_x[30] = 8.018635e+00f;
		AutoMATiC_DMC_H_x[31] = 6.775021e+00f;
		AutoMATiC_DMC_H_x[32] = 6.190011e+01f;
		AutoMATiC_DMC_H_x[33] = 1.931418e+01f;
		AutoMATiC_DMC_H_x[34] = 5.644363e+01f;
		AutoMATiC_DMC_H_x[35] = 1.838345e+01f;
		AutoMATiC_DMC_H_x[36] = 4.711061e+01f;
		AutoMATiC_DMC_H_x[37] = 1.565679e+01f;
		AutoMATiC_DMC_H_x[38] = 2.097070e+01f;
		AutoMATiC_DMC_H_x[39] = 7.558490e+00f;
		AutoMATiC_DMC_H_x[40] = 2.023139e+01f;
		AutoMATiC_DMC_H_x[41] = 1.576652e+01f;
		AutoMATiC_DMC_H_x[42] = 1.883764e+01f;
		AutoMATiC_DMC_H_x[43] = 1.514642e+01f;
		AutoMATiC_DMC_H_x[44] = 1.565679e+01f;
		AutoMATiC_DMC_H_x[45] = 1.510759e+01f;
		AutoMATiC_DMC_H_x[46] = 7.391926e+00f;
		AutoMATiC_DMC_H_x[47] = 6.332568e+00f;
		AutoMATiC_DMC_H_x[48] = 2.567725e+01f;
		AutoMATiC_DMC_H_x[49] = 8.233726e+00f;
		AutoMATiC_DMC_H_x[50] = 2.413991e+01f;
		AutoMATiC_DMC_H_x[51] = 8.018635e+00f;
		AutoMATiC_DMC_H_x[52] = 2.097070e+01f;
		AutoMATiC_DMC_H_x[53] = 7.391926e+00f;
		AutoMATiC_DMC_H_x[54] = 1.634423e+01f;
		AutoMATiC_DMC_H_x[55] = 5.541646e+00f;
		AutoMATiC_DMC_H_x[56] = 8.808511e+00f;
		AutoMATiC_DMC_H_x[57] = 6.910587e+00f;
		AutoMATiC_DMC_H_x[58] = 8.414358e+00f;
		AutoMATiC_DMC_H_x[59] = 6.775021e+00f;
		AutoMATiC_DMC_H_x[60] = 7.558490e+00f;
		AutoMATiC_DMC_H_x[61] = 6.332568e+00f;
		AutoMATiC_DMC_H_x[62] = 5.541646e+00f;
		AutoMATiC_DMC_H_x[63] = 6.871756e+00f;
		AutoMATiC_DMC_H_x[64] = 2.000000e+00f;
		AutoMATiC_DMC_H_x[65] = 2.000000e+00f;
		AutoMATiC_DMC_H_i[0] = 0;
		AutoMATiC_DMC_H_i[1] = 1;
		AutoMATiC_DMC_H_i[2] = 2;
		AutoMATiC_DMC_H_i[3] = 3;
		AutoMATiC_DMC_H_i[4] = 4;
		AutoMATiC_DMC_H_i[5] = 5;
		AutoMATiC_DMC_H_i[6] = 6;
		AutoMATiC_DMC_H_i[7] = 7;
		AutoMATiC_DMC_H_i[8] = 0;
		AutoMATiC_DMC_H_i[9] = 1;
		AutoMATiC_DMC_H_i[10] = 2;
		AutoMATiC_DMC_H_i[11] = 3;
		AutoMATiC_DMC_H_i[12] = 4;
		AutoMATiC_DMC_H_i[13] = 5;
		AutoMATiC_DMC_H_i[14] = 6;
		AutoMATiC_DMC_H_i[15] = 7;
		AutoMATiC_DMC_H_i[16] = 0;
		AutoMATiC_DMC_H_i[17] = 1;
		AutoMATiC_DMC_H_i[18] = 2;
		AutoMATiC_DMC_H_i[19] = 3;
		AutoMATiC_DMC_H_i[20] = 4;
		AutoMATiC_DMC_H_i[21] = 5;
		AutoMATiC_DMC_H_i[22] = 6;
		AutoMATiC_DMC_H_i[23] = 7;
		AutoMATiC_DMC_H_i[24] = 0;
		AutoMATiC_DMC_H_i[25] = 1;
		AutoMATiC_DMC_H_i[26] = 2;
		AutoMATiC_DMC_H_i[27] = 3;
		AutoMATiC_DMC_H_i[28] = 4;
		AutoMATiC_DMC_H_i[29] = 5;
		AutoMATiC_DMC_H_i[30] = 6;
		AutoMATiC_DMC_H_i[31] = 7;
		AutoMATiC_DMC_H_i[32] = 0;
		AutoMATiC_DMC_H_i[33] = 1;
		AutoMATiC_DMC_H_i[34] = 2;
		AutoMATiC_DMC_H_i[35] = 3;
		AutoMATiC_DMC_H_i[36] = 4;
		AutoMATiC_DMC_H_i[37] = 5;
		AutoMATiC_DMC_H_i[38] = 6;
		AutoMATiC_DMC_H_i[39] = 7;
		AutoMATiC_DMC_H_i[40] = 0;
		AutoMATiC_DMC_H_i[41] = 1;
		AutoMATiC_DMC_H_i[42] = 2;
		AutoMATiC_DMC_H_i[43] = 3;
		AutoMATiC_DMC_H_i[44] = 4;
		AutoMATiC_DMC_H_i[45] = 5;
		AutoMATiC_DMC_H_i[46] = 6;
		AutoMATiC_DMC_H_i[47] = 7;
		AutoMATiC_DMC_H_i[48] = 0;
		AutoMATiC_DMC_H_i[49] = 1;
		AutoMATiC_DMC_H_i[50] = 2;
		AutoMATiC_DMC_H_i[51] = 3;
		AutoMATiC_DMC_H_i[52] = 4;
		AutoMATiC_DMC_H_i[53] = 5;
		AutoMATiC_DMC_H_i[54] = 6;
		AutoMATiC_DMC_H_i[55] = 7;
		AutoMATiC_DMC_H_i[56] = 0;
		AutoMATiC_DMC_H_i[57] = 1;
		AutoMATiC_DMC_H_i[58] = 2;
		AutoMATiC_DMC_H_i[59] = 3;
		AutoMATiC_DMC_H_i[60] = 4;
		AutoMATiC_DMC_H_i[61] = 5;
		AutoMATiC_DMC_H_i[62] = 6;
		AutoMATiC_DMC_H_i[63] = 7;
		AutoMATiC_DMC_H_i[64] = 8;
		AutoMATiC_DMC_H_i[65] = 9;
		AutoMATiC_DMC_H_p[0] = 0;
		AutoMATiC_DMC_H_p[1] = 8;
		AutoMATiC_DMC_H_p[2] = 16;
		AutoMATiC_DMC_H_p[3] = 24;
		AutoMATiC_DMC_H_p[4] = 32;
		AutoMATiC_DMC_H_p[5] = 40;
		AutoMATiC_DMC_H_p[6] = 48;
		AutoMATiC_DMC_H_p[7] = 56;
		AutoMATiC_DMC_H_p[8] = 64;
		AutoMATiC_DMC_H_p[9] = 65;
		AutoMATiC_DMC_H_p[10] = 66;

		osqp_settings = (OSQPSettings *)c_malloc(sizeof(OSQPSettings));
		osqp_data = (OSQPData *)c_malloc(sizeof(OSQPData));
		for(int osqp_it=0; osqp_it < 40; ++osqp_it) osqp_lb[osqp_it] = -100000;
		osqp_data->n = 10;
		osqp_data->m = 40;
		osqp_data->q = osqp_q;
		osqp_data->l = osqp_lb;
		osqp_data->u = osqp_ub;
		osqp_data->P = csc_matrix(osqp_data->n, osqp_data->n, 66, AutoMATiC_DMC_H_x, AutoMATiC_DMC_H_i, AutoMATiC_DMC_H_p);
		osqp_data->A = csc_matrix(osqp_data->m, osqp_data->n, 80, AutoMATiC_DMC_A_x, AutoMATiC_DMC_A_i, AutoMATiC_DMC_A_p);
		osqp_set_default_settings(osqp_settings);
		osqp_work = osqp_setup(osqp_data, osqp_settings);
		AutoMATiC_DMC_dUp = darray(1,8,1,1);
		AutoMATiC_DMC_Yzad = darray(1,10,1,1);
		AutoMATiC_DMC_Y = darray(1,10,1,1);
		AutoMATiC_DMC_tmpu = darray(1,2,1,1);
		AutoMATiC_DMC_e = darray(1,2,1,1);
		AutoMATiC_DMC_du = darray(1,2,1,1);
		AutoMATiC_DMC_uk = darray(1,2,1,1);
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
		AutoMATiC_DMC_ftmp1 = darray(1,10,1,1);
		AutoMATiC_DMC_ftmp2 = darray(1,10,1,1);
		AutoMATiC_DMC_Mp = darray(1,10,1,8);
		AutoMATiC_DMC_Mp[1][1] = 2.552292e+00f;
		AutoMATiC_DMC_Mp[1][2] = 6.321206e-01f;
		AutoMATiC_DMC_Mp[1][3] = 1.249453e+00f;
		AutoMATiC_DMC_Mp[1][4] = 2.325442e-01f;
		AutoMATiC_DMC_Mp[1][5] = 6.116594e-01f;
		AutoMATiC_DMC_Mp[1][6] = 8.554821e-02f;
		AutoMATiC_DMC_Mp[1][7] = 2.994327e-01f;
		AutoMATiC_DMC_Mp[1][8] = 3.147143e-02f;
		AutoMATiC_DMC_Mp[2][1] = 8.111244e-01f;
		AutoMATiC_DMC_Mp[2][2] = 1.426990e+00f;
		AutoMATiC_DMC_Mp[2][3] = 1.532016e-01f;
		AutoMATiC_DMC_Mp[2][4] = 4.088396e-01f;
		AutoMATiC_DMC_Mp[2][5] = 2.893605e-02f;
		AutoMATiC_DMC_Mp[2][6] = 1.171345e-01f;
		AutoMATiC_DMC_Mp[2][7] = 5.465313e-03f;
		AutoMATiC_DMC_Mp[2][8] = 3.355960e-02f;
		AutoMATiC_DMC_Mp[3][1] = 3.801745e+00f;
		AutoMATiC_DMC_Mp[3][2] = 8.646647e-01f;
		AutoMATiC_DMC_Mp[3][3] = 1.861112e+00f;
		AutoMATiC_DMC_Mp[3][4] = 3.180924e-01f;
		AutoMATiC_DMC_Mp[3][5] = 9.110921e-01f;
		AutoMATiC_DMC_Mp[3][6] = 1.170196e-01f;
		AutoMATiC_DMC_Mp[3][7] = 2.994327e-01f;
		AutoMATiC_DMC_Mp[3][8] = 3.147143e-02f;
		AutoMATiC_DMC_Mp[4][1] = 9.643260e-01f;
		AutoMATiC_DMC_Mp[4][2] = 1.835830e+00f;
		AutoMATiC_DMC_Mp[4][3] = 1.821377e-01f;
		AutoMATiC_DMC_Mp[4][4] = 5.259741e-01f;
		AutoMATiC_DMC_Mp[4][5] = 3.440136e-02f;
		AutoMATiC_DMC_Mp[4][6] = 1.506941e-01f;
		AutoMATiC_DMC_Mp[4][7] = 5.465313e-03f;
		AutoMATiC_DMC_Mp[4][8] = 3.355960e-02f;
		AutoMATiC_DMC_Mp[5][1] = 4.413404e+00f;
		AutoMATiC_DMC_Mp[5][2] = 9.502129e-01f;
		AutoMATiC_DMC_Mp[5][3] = 2.160545e+00f;
		AutoMATiC_DMC_Mp[5][4] = 3.495638e-01f;
		AutoMATiC_DMC_Mp[5][5] = 9.110921e-01f;
		AutoMATiC_DMC_Mp[5][6] = 1.170196e-01f;
		AutoMATiC_DMC_Mp[5][7] = 2.994327e-01f;
		AutoMATiC_DMC_Mp[5][8] = 3.147143e-02f;
		AutoMATiC_DMC_Mp[6][1] = 9.932621e-01f;
		AutoMATiC_DMC_Mp[6][2] = 1.952965e+00f;
		AutoMATiC_DMC_Mp[6][3] = 1.876030e-01f;
		AutoMATiC_DMC_Mp[6][4] = 5.595337e-01f;
		AutoMATiC_DMC_Mp[6][5] = 3.440136e-02f;
		AutoMATiC_DMC_Mp[6][6] = 1.506941e-01f;
		AutoMATiC_DMC_Mp[6][7] = 5.465313e-03f;
		AutoMATiC_DMC_Mp[6][8] = 3.355960e-02f;
		AutoMATiC_DMC_Mp[7][1] = 4.712837e+00f;
		AutoMATiC_DMC_Mp[7][2] = 9.816844e-01f;
		AutoMATiC_DMC_Mp[7][3] = 2.160545e+00f;
		AutoMATiC_DMC_Mp[7][4] = 3.495638e-01f;
		AutoMATiC_DMC_Mp[7][5] = 9.110921e-01f;
		AutoMATiC_DMC_Mp[7][6] = 1.170196e-01f;
		AutoMATiC_DMC_Mp[7][7] = 2.994327e-01f;
		AutoMATiC_DMC_Mp[7][8] = 3.147143e-02f;
		AutoMATiC_DMC_Mp[8][1] = 9.987274e-01f;
		AutoMATiC_DMC_Mp[8][2] = 1.986524e+00f;
		AutoMATiC_DMC_Mp[8][3] = 1.876030e-01f;
		AutoMATiC_DMC_Mp[8][4] = 5.595337e-01f;
		AutoMATiC_DMC_Mp[8][5] = 3.440136e-02f;
		AutoMATiC_DMC_Mp[8][6] = 1.506941e-01f;
		AutoMATiC_DMC_Mp[8][7] = 5.465313e-03f;
		AutoMATiC_DMC_Mp[8][8] = 3.355960e-02f;
		AutoMATiC_DMC_Mp[9][1] = 4.712837e+00f;
		AutoMATiC_DMC_Mp[9][2] = 9.816844e-01f;
		AutoMATiC_DMC_Mp[9][3] = 2.160545e+00f;
		AutoMATiC_DMC_Mp[9][4] = 3.495638e-01f;
		AutoMATiC_DMC_Mp[9][5] = 9.110921e-01f;
		AutoMATiC_DMC_Mp[9][6] = 1.170196e-01f;
		AutoMATiC_DMC_Mp[9][7] = 2.994327e-01f;
		AutoMATiC_DMC_Mp[9][8] = 3.147143e-02f;
		AutoMATiC_DMC_Mp[10][1] = 9.987274e-01f;
		AutoMATiC_DMC_Mp[10][2] = 1.986524e+00f;
		AutoMATiC_DMC_Mp[10][3] = 1.876030e-01f;
		AutoMATiC_DMC_Mp[10][4] = 5.595337e-01f;
		AutoMATiC_DMC_Mp[10][5] = 3.440136e-02f;
		AutoMATiC_DMC_Mp[10][6] = 1.506941e-01f;
		AutoMATiC_DMC_Mp[10][7] = 5.465313e-03f;
		AutoMATiC_DMC_Mp[10][8] = 3.355960e-02f;
		AutoMATiC_DMC_ftmp3 = darray(1,10,1,1);
		AutoMATiC_DMC_ftmp4 = darray(1,10,1,1);
		AutoMATiC_DMC_fconst = darray(1,10,1,10);
		AutoMATiC_DMC_fconst[1][1] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[1][2] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[1][3] = -5.104583e+00f;
		AutoMATiC_DMC_fconst[1][4] = -1.622249e+00f;
		AutoMATiC_DMC_fconst[1][5] = -7.603490e+00f;
		AutoMATiC_DMC_fconst[1][6] = -1.928652e+00f;
		AutoMATiC_DMC_fconst[1][7] = -8.826808e+00f;
		AutoMATiC_DMC_fconst[1][8] = -1.986524e+00f;
		AutoMATiC_DMC_fconst[1][9] = -9.425674e+00f;
		AutoMATiC_DMC_fconst[1][10] = -1.997455e+00f;
		AutoMATiC_DMC_fconst[2][1] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[2][2] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[2][3] = -1.264241e+00f;
		AutoMATiC_DMC_fconst[2][4] = -2.853981e+00f;
		AutoMATiC_DMC_fconst[2][5] = -1.729329e+00f;
		AutoMATiC_DMC_fconst[2][6] = -3.671660e+00f;
		AutoMATiC_DMC_fconst[2][7] = -1.900426e+00f;
		AutoMATiC_DMC_fconst[2][8] = -3.905929e+00f;
		AutoMATiC_DMC_fconst[2][9] = -1.963369e+00f;
		AutoMATiC_DMC_fconst[2][10] = -3.973048e+00f;
		AutoMATiC_DMC_fconst[3][1] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[3][2] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[3][3] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[3][4] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[3][5] = -5.104583e+00f;
		AutoMATiC_DMC_fconst[3][6] = -1.622249e+00f;
		AutoMATiC_DMC_fconst[3][7] = -7.603490e+00f;
		AutoMATiC_DMC_fconst[3][8] = -1.928652e+00f;
		AutoMATiC_DMC_fconst[3][9] = -8.826808e+00f;
		AutoMATiC_DMC_fconst[3][10] = -1.986524e+00f;
		AutoMATiC_DMC_fconst[4][1] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[4][2] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[4][3] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[4][4] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[4][5] = -1.264241e+00f;
		AutoMATiC_DMC_fconst[4][6] = -2.853981e+00f;
		AutoMATiC_DMC_fconst[4][7] = -1.729329e+00f;
		AutoMATiC_DMC_fconst[4][8] = -3.671660e+00f;
		AutoMATiC_DMC_fconst[4][9] = -1.900426e+00f;
		AutoMATiC_DMC_fconst[4][10] = -3.905929e+00f;
		AutoMATiC_DMC_fconst[5][1] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[5][2] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[5][3] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[5][4] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[5][5] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[5][6] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[5][7] = -5.104583e+00f;
		AutoMATiC_DMC_fconst[5][8] = -1.622249e+00f;
		AutoMATiC_DMC_fconst[5][9] = -7.603490e+00f;
		AutoMATiC_DMC_fconst[5][10] = -1.928652e+00f;
		AutoMATiC_DMC_fconst[6][1] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[6][2] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[6][3] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[6][4] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[6][5] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[6][6] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[6][7] = -1.264241e+00f;
		AutoMATiC_DMC_fconst[6][8] = -2.853981e+00f;
		AutoMATiC_DMC_fconst[6][9] = -1.729329e+00f;
		AutoMATiC_DMC_fconst[6][10] = -3.671660e+00f;
		AutoMATiC_DMC_fconst[7][1] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[7][2] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[7][3] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[7][4] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[7][5] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[7][6] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[7][7] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[7][8] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[7][9] = -5.104583e+00f;
		AutoMATiC_DMC_fconst[7][10] = -1.622249e+00f;
		AutoMATiC_DMC_fconst[8][1] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[8][2] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[8][3] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[8][4] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[8][5] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[8][6] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[8][7] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[8][8] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[8][9] = -1.264241e+00f;
		AutoMATiC_DMC_fconst[8][10] = -2.853981e+00f;
		AutoMATiC_DMC_fconst[9][1] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[9][2] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[9][3] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[9][4] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[9][5] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[9][6] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[9][7] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[9][8] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[9][9] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[9][10] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[10][1] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[10][2] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[10][3] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[10][4] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[10][5] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[10][6] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[10][7] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[10][8] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[10][9] = 0.000000e+00f;
		AutoMATiC_DMC_fconst[10][10] = 0.000000e+00f;
		AutoMATiC_DMC_btmp1 = darray(1,40,1,1);
		AutoMATiC_DMC_bvar = darray(1,40,1,2);
		AutoMATiC_DMC_bvar[1][1] = 0.000000e+00f;
		AutoMATiC_DMC_bvar[1][2] = 0.000000e+00f;
		AutoMATiC_DMC_bvar[2][1] = 0.000000e+00f;
		AutoMATiC_DMC_bvar[2][2] = 0.000000e+00f;
		AutoMATiC_DMC_bvar[3][1] = 0.000000e+00f;
		AutoMATiC_DMC_bvar[3][2] = 0.000000e+00f;
		AutoMATiC_DMC_bvar[4][1] = 0.000000e+00f;
		AutoMATiC_DMC_bvar[4][2] = 0.000000e+00f;
		AutoMATiC_DMC_bvar[5][1] = 0.000000e+00f;
		AutoMATiC_DMC_bvar[5][2] = 0.000000e+00f;
		AutoMATiC_DMC_bvar[6][1] = 0.000000e+00f;
		AutoMATiC_DMC_bvar[6][2] = 0.000000e+00f;
		AutoMATiC_DMC_bvar[7][1] = 0.000000e+00f;
		AutoMATiC_DMC_bvar[7][2] = 0.000000e+00f;
		AutoMATiC_DMC_bvar[8][1] = 0.000000e+00f;
		AutoMATiC_DMC_bvar[8][2] = 0.000000e+00f;
		AutoMATiC_DMC_bvar[9][1] = 0.000000e+00f;
		AutoMATiC_DMC_bvar[9][2] = 0.000000e+00f;
		AutoMATiC_DMC_bvar[10][1] = 0.000000e+00f;
		AutoMATiC_DMC_bvar[10][2] = 0.000000e+00f;
		AutoMATiC_DMC_bvar[11][1] = 1.000000e+00f;
		AutoMATiC_DMC_bvar[11][2] = 0.000000e+00f;
		AutoMATiC_DMC_bvar[12][1] = 0.000000e+00f;
		AutoMATiC_DMC_bvar[12][2] = 1.000000e+00f;
		AutoMATiC_DMC_bvar[13][1] = 1.000000e+00f;
		AutoMATiC_DMC_bvar[13][2] = 0.000000e+00f;
		AutoMATiC_DMC_bvar[14][1] = 0.000000e+00f;
		AutoMATiC_DMC_bvar[14][2] = 1.000000e+00f;
		AutoMATiC_DMC_bvar[15][1] = 1.000000e+00f;
		AutoMATiC_DMC_bvar[15][2] = 0.000000e+00f;
		AutoMATiC_DMC_bvar[16][1] = 0.000000e+00f;
		AutoMATiC_DMC_bvar[16][2] = 1.000000e+00f;
		AutoMATiC_DMC_bvar[17][1] = 1.000000e+00f;
		AutoMATiC_DMC_bvar[17][2] = 0.000000e+00f;
		AutoMATiC_DMC_bvar[18][1] = 0.000000e+00f;
		AutoMATiC_DMC_bvar[18][2] = 1.000000e+00f;
		AutoMATiC_DMC_bvar[19][1] = 1.000000e+00f;
		AutoMATiC_DMC_bvar[19][2] = 0.000000e+00f;
		AutoMATiC_DMC_bvar[20][1] = 0.000000e+00f;
		AutoMATiC_DMC_bvar[20][2] = 1.000000e+00f;
		AutoMATiC_DMC_bvar[21][1] = -0.000000e+00f;
		AutoMATiC_DMC_bvar[21][2] = -0.000000e+00f;
		AutoMATiC_DMC_bvar[22][1] = -0.000000e+00f;
		AutoMATiC_DMC_bvar[22][2] = -0.000000e+00f;
		AutoMATiC_DMC_bvar[23][1] = -0.000000e+00f;
		AutoMATiC_DMC_bvar[23][2] = -0.000000e+00f;
		AutoMATiC_DMC_bvar[24][1] = -0.000000e+00f;
		AutoMATiC_DMC_bvar[24][2] = -0.000000e+00f;
		AutoMATiC_DMC_bvar[25][1] = -0.000000e+00f;
		AutoMATiC_DMC_bvar[25][2] = -0.000000e+00f;
		AutoMATiC_DMC_bvar[26][1] = -0.000000e+00f;
		AutoMATiC_DMC_bvar[26][2] = -0.000000e+00f;
		AutoMATiC_DMC_bvar[27][1] = -0.000000e+00f;
		AutoMATiC_DMC_bvar[27][2] = -0.000000e+00f;
		AutoMATiC_DMC_bvar[28][1] = -0.000000e+00f;
		AutoMATiC_DMC_bvar[28][2] = -0.000000e+00f;
		AutoMATiC_DMC_bvar[29][1] = -0.000000e+00f;
		AutoMATiC_DMC_bvar[29][2] = -0.000000e+00f;
		AutoMATiC_DMC_bvar[30][1] = -0.000000e+00f;
		AutoMATiC_DMC_bvar[30][2] = -0.000000e+00f;
		AutoMATiC_DMC_bvar[31][1] = -1.000000e+00f;
		AutoMATiC_DMC_bvar[31][2] = -0.000000e+00f;
		AutoMATiC_DMC_bvar[32][1] = -0.000000e+00f;
		AutoMATiC_DMC_bvar[32][2] = -1.000000e+00f;
		AutoMATiC_DMC_bvar[33][1] = -1.000000e+00f;
		AutoMATiC_DMC_bvar[33][2] = -0.000000e+00f;
		AutoMATiC_DMC_bvar[34][1] = -0.000000e+00f;
		AutoMATiC_DMC_bvar[34][2] = -1.000000e+00f;
		AutoMATiC_DMC_bvar[35][1] = -1.000000e+00f;
		AutoMATiC_DMC_bvar[35][2] = -0.000000e+00f;
		AutoMATiC_DMC_bvar[36][1] = -0.000000e+00f;
		AutoMATiC_DMC_bvar[36][2] = -1.000000e+00f;
		AutoMATiC_DMC_bvar[37][1] = -1.000000e+00f;
		AutoMATiC_DMC_bvar[37][2] = -0.000000e+00f;
		AutoMATiC_DMC_bvar[38][1] = -0.000000e+00f;
		AutoMATiC_DMC_bvar[38][2] = -1.000000e+00f;
		AutoMATiC_DMC_bvar[39][1] = -1.000000e+00f;
		AutoMATiC_DMC_bvar[39][2] = -0.000000e+00f;
		AutoMATiC_DMC_bvar[40][1] = -0.000000e+00f;
		AutoMATiC_DMC_bvar[40][2] = -1.000000e+00f;
		AutoMATiC_DMC_btmp2 = darray(1,40,1,1);
		AutoMATiC_DMC_b = darray(1,40,1,1);
		AutoMATiC_DMC_b[1][1] = 1.000000e-02f;
		AutoMATiC_DMC_b[2][1] = 1.000000e-02f;
		AutoMATiC_DMC_b[3][1] = 1.000000e-02f;
		AutoMATiC_DMC_b[4][1] = 1.000000e-02f;
		AutoMATiC_DMC_b[5][1] = 1.000000e-02f;
		AutoMATiC_DMC_b[6][1] = 1.000000e-02f;
		AutoMATiC_DMC_b[7][1] = 1.000000e-02f;
		AutoMATiC_DMC_b[8][1] = 1.000000e-02f;
		AutoMATiC_DMC_b[9][1] = 1.000000e-02f;
		AutoMATiC_DMC_b[10][1] = 1.000000e-02f;
		AutoMATiC_DMC_b[11][1] = 1.000000e+00f;
		AutoMATiC_DMC_b[12][1] = 1.000000e+00f;
		AutoMATiC_DMC_b[13][1] = 1.000000e+00f;
		AutoMATiC_DMC_b[14][1] = 1.000000e+00f;
		AutoMATiC_DMC_b[15][1] = 1.000000e+00f;
		AutoMATiC_DMC_b[16][1] = 1.000000e+00f;
		AutoMATiC_DMC_b[17][1] = 1.000000e+00f;
		AutoMATiC_DMC_b[18][1] = 1.000000e+00f;
		AutoMATiC_DMC_b[19][1] = 1.000000e+00f;
		AutoMATiC_DMC_b[20][1] = 1.000000e+00f;
		AutoMATiC_DMC_b[21][1] = 1.000000e-02f;
		AutoMATiC_DMC_b[22][1] = 1.000000e-02f;
		AutoMATiC_DMC_b[23][1] = 1.000000e-02f;
		AutoMATiC_DMC_b[24][1] = 1.000000e-02f;
		AutoMATiC_DMC_b[25][1] = 1.000000e-02f;
		AutoMATiC_DMC_b[26][1] = 1.000000e-02f;
		AutoMATiC_DMC_b[27][1] = 1.000000e-02f;
		AutoMATiC_DMC_b[28][1] = 1.000000e-02f;
		AutoMATiC_DMC_b[29][1] = 1.000000e-02f;
		AutoMATiC_DMC_b[30][1] = 1.000000e-02f;
		AutoMATiC_DMC_b[31][1] = 1.000000e+00f;
		AutoMATiC_DMC_b[32][1] = 1.000000e+00f;
		AutoMATiC_DMC_b[33][1] = 1.000000e+00f;
		AutoMATiC_DMC_b[34][1] = 1.000000e+00f;
		AutoMATiC_DMC_b[35][1] = 1.000000e+00f;
		AutoMATiC_DMC_b[36][1] = 1.000000e+00f;
		AutoMATiC_DMC_b[37][1] = 1.000000e+00f;
		AutoMATiC_DMC_b[38][1] = 1.000000e+00f;
		AutoMATiC_DMC_b[39][1] = 1.000000e+00f;
		AutoMATiC_DMC_b[40][1] = 1.000000e+00f;
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
	for(j=1;j<=2;++j) for(k=1;k<=1;++k) AutoMATiC_DMC_du[j][k] = 0;
	for(j=1;j<=2;++j) for(k=1;k<=1;++k) AutoMATiC_DMC_uk[j][k] = 0;
	for(AutoMATiC_DMC_i=1;AutoMATiC_DMC_i<=2;++AutoMATiC_DMC_i){
		AutoMATiC_DMC_uk[AutoMATiC_DMC_i][1]=ad->u[ad->k-1][AutoMATiC_DMC_i-1];
	}
	sumaa(AutoMATiC_DMC_Yzad,AutoMATiC_DMC_Y,AutoMATiC_DMC_ftmp1,10,1,-1);
	productab(AutoMATiC_DMC_Mp,AutoMATiC_DMC_dUp,AutoMATiC_DMC_ftmp2,10,8,8,1);
	sumaa(AutoMATiC_DMC_ftmp1,AutoMATiC_DMC_ftmp2,AutoMATiC_DMC_ftmp3,10,1,-1);
	productab(AutoMATiC_DMC_fconst,AutoMATiC_DMC_ftmp3,AutoMATiC_DMC_ftmp4,10,10,10,1);
	for(AutoMATiC_DMC_i=1;AutoMATiC_DMC_i<=10;++AutoMATiC_DMC_i){
		AutoMATiC_DMC_ftmp[AutoMATiC_DMC_i]=AutoMATiC_DMC_ftmp4[AutoMATiC_DMC_i][1];
	}
	productab(AutoMATiC_DMC_bvar,AutoMATiC_DMC_uk,AutoMATiC_DMC_btmp1,40,2,2,1);
	sumaa(AutoMATiC_DMC_b,AutoMATiC_DMC_btmp1,AutoMATiC_DMC_btmp2,40,1,1);
	for(AutoMATiC_DMC_i=1;AutoMATiC_DMC_i<=40;++AutoMATiC_DMC_i){
		AutoMATiC_DMC_btmp[AutoMATiC_DMC_i]=AutoMATiC_DMC_btmp2[AutoMATiC_DMC_i][1];
	}
	for(AutoMATiC_DMC_i=1;AutoMATiC_DMC_i<=10;++AutoMATiC_DMC_i){
		AutoMATiC_DMC_qpx[AutoMATiC_DMC_i]=0;
	}
	memcpy (osqp_q, &(AutoMATiC_DMC_ftmp[1]), 10*sizeof(c_float));
	osqp_update_lin_cost(osqp_work, osqp_q);
	memcpy (osqp_ub, &(AutoMATiC_DMC_btmp[1]), 40*sizeof(c_float));
	osqp_update_bounds(osqp_work, osqp_lb, osqp_ub);
	osqp_solve(osqp_work);
	memcpy (&(AutoMATiC_DMC_qpx[1]), osqp_work->solution->x, 10*sizeof(c_float));

	for(AutoMATiC_DMC_i=1;AutoMATiC_DMC_i<=2;++AutoMATiC_DMC_i){
		AutoMATiC_DMC_du[AutoMATiC_DMC_i][1]=AutoMATiC_DMC_qpx[AutoMATiC_DMC_i];
	}
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
