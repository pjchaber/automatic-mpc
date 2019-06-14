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
	static long Iuf;
	static long Iuftmp;
	static long Iyf;
	static float** Y0;
	static float** Yzad;
	static float** btmp1;
	static float** btmp2;
	static float** control_value;
	static float** disturbance;
	static float** du;
	static float** ftmp1;
	static float** ftmp4;
	static long i;
	static long itmp;
	static long j;
	static long m;
	static long n;
	static long p;
	static long r;
	static float** tmpu;
	static float** uk;
	static float** y0;
	static long k;
	static float*** GPC_b;
	static float** GPC_a;
	static float** fconst;
	static float** bvar;
	static float** b;
	static float** dumax;
	static float** dumin;
	static float** umax;
	static float** umin;
	static c_float A_x[80];
	static c_int A_i[80];
	static c_int A_p[11];

	static c_float H_x[66];
	static c_int H_i[66];
	static c_int H_p[11];

	static OSQPSettings *osqp_settings;
	static OSQPWorkspace *osqp_work;
	static OSQPData *osqp_data;
	static c_float osqp_q[10];
	static c_float osqp_lb[40];
	static c_float osqp_ub[40];
	static c_float ftmp[11];
	static c_float btmp[41];
	static c_float qpx[11];
	if(ad == NULL){
		A_x[0] = -1.000000e+00f;
		A_x[1] = 1.000000e+00f;
		A_x[2] = -1.000000e+00f;
		A_x[3] = -1.000000e+00f;
		A_x[4] = -1.000000e+00f;
		A_x[5] = -1.000000e+00f;
		A_x[6] = -1.000000e+00f;
		A_x[7] = 1.000000e+00f;
		A_x[8] = 1.000000e+00f;
		A_x[9] = 1.000000e+00f;
		A_x[10] = 1.000000e+00f;
		A_x[11] = 1.000000e+00f;
		A_x[12] = -1.000000e+00f;
		A_x[13] = 1.000000e+00f;
		A_x[14] = -1.000000e+00f;
		A_x[15] = -1.000000e+00f;
		A_x[16] = -1.000000e+00f;
		A_x[17] = -1.000000e+00f;
		A_x[18] = -1.000000e+00f;
		A_x[19] = 1.000000e+00f;
		A_x[20] = 1.000000e+00f;
		A_x[21] = 1.000000e+00f;
		A_x[22] = 1.000000e+00f;
		A_x[23] = 1.000000e+00f;
		A_x[24] = -1.000000e+00f;
		A_x[25] = 1.000000e+00f;
		A_x[26] = -1.000000e+00f;
		A_x[27] = -1.000000e+00f;
		A_x[28] = -1.000000e+00f;
		A_x[29] = -1.000000e+00f;
		A_x[30] = 1.000000e+00f;
		A_x[31] = 1.000000e+00f;
		A_x[32] = 1.000000e+00f;
		A_x[33] = 1.000000e+00f;
		A_x[34] = -1.000000e+00f;
		A_x[35] = 1.000000e+00f;
		A_x[36] = -1.000000e+00f;
		A_x[37] = -1.000000e+00f;
		A_x[38] = -1.000000e+00f;
		A_x[39] = -1.000000e+00f;
		A_x[40] = 1.000000e+00f;
		A_x[41] = 1.000000e+00f;
		A_x[42] = 1.000000e+00f;
		A_x[43] = 1.000000e+00f;
		A_x[44] = -1.000000e+00f;
		A_x[45] = 1.000000e+00f;
		A_x[46] = -1.000000e+00f;
		A_x[47] = -1.000000e+00f;
		A_x[48] = -1.000000e+00f;
		A_x[49] = 1.000000e+00f;
		A_x[50] = 1.000000e+00f;
		A_x[51] = 1.000000e+00f;
		A_x[52] = -1.000000e+00f;
		A_x[53] = 1.000000e+00f;
		A_x[54] = -1.000000e+00f;
		A_x[55] = -1.000000e+00f;
		A_x[56] = -1.000000e+00f;
		A_x[57] = 1.000000e+00f;
		A_x[58] = 1.000000e+00f;
		A_x[59] = 1.000000e+00f;
		A_x[60] = -1.000000e+00f;
		A_x[61] = 1.000000e+00f;
		A_x[62] = -1.000000e+00f;
		A_x[63] = -1.000000e+00f;
		A_x[64] = 1.000000e+00f;
		A_x[65] = 1.000000e+00f;
		A_x[66] = -1.000000e+00f;
		A_x[67] = 1.000000e+00f;
		A_x[68] = -1.000000e+00f;
		A_x[69] = -1.000000e+00f;
		A_x[70] = 1.000000e+00f;
		A_x[71] = 1.000000e+00f;
		A_x[72] = -1.000000e+00f;
		A_x[73] = 1.000000e+00f;
		A_x[74] = -1.000000e+00f;
		A_x[75] = 1.000000e+00f;
		A_x[76] = -1.000000e+00f;
		A_x[77] = 1.000000e+00f;
		A_x[78] = -1.000000e+00f;
		A_x[79] = 1.000000e+00f;
		A_i[0] = 0;
		A_i[1] = 10;
		A_i[2] = 20;
		A_i[3] = 22;
		A_i[4] = 24;
		A_i[5] = 26;
		A_i[6] = 28;
		A_i[7] = 30;
		A_i[8] = 32;
		A_i[9] = 34;
		A_i[10] = 36;
		A_i[11] = 38;
		A_i[12] = 1;
		A_i[13] = 11;
		A_i[14] = 21;
		A_i[15] = 23;
		A_i[16] = 25;
		A_i[17] = 27;
		A_i[18] = 29;
		A_i[19] = 31;
		A_i[20] = 33;
		A_i[21] = 35;
		A_i[22] = 37;
		A_i[23] = 39;
		A_i[24] = 2;
		A_i[25] = 12;
		A_i[26] = 22;
		A_i[27] = 24;
		A_i[28] = 26;
		A_i[29] = 28;
		A_i[30] = 32;
		A_i[31] = 34;
		A_i[32] = 36;
		A_i[33] = 38;
		A_i[34] = 3;
		A_i[35] = 13;
		A_i[36] = 23;
		A_i[37] = 25;
		A_i[38] = 27;
		A_i[39] = 29;
		A_i[40] = 33;
		A_i[41] = 35;
		A_i[42] = 37;
		A_i[43] = 39;
		A_i[44] = 4;
		A_i[45] = 14;
		A_i[46] = 24;
		A_i[47] = 26;
		A_i[48] = 28;
		A_i[49] = 34;
		A_i[50] = 36;
		A_i[51] = 38;
		A_i[52] = 5;
		A_i[53] = 15;
		A_i[54] = 25;
		A_i[55] = 27;
		A_i[56] = 29;
		A_i[57] = 35;
		A_i[58] = 37;
		A_i[59] = 39;
		A_i[60] = 6;
		A_i[61] = 16;
		A_i[62] = 26;
		A_i[63] = 28;
		A_i[64] = 36;
		A_i[65] = 38;
		A_i[66] = 7;
		A_i[67] = 17;
		A_i[68] = 27;
		A_i[69] = 29;
		A_i[70] = 37;
		A_i[71] = 39;
		A_i[72] = 8;
		A_i[73] = 18;
		A_i[74] = 28;
		A_i[75] = 38;
		A_i[76] = 9;
		A_i[77] = 19;
		A_i[78] = 29;
		A_i[79] = 39;
		A_p[0] = 0;
		A_p[1] = 12;
		A_p[2] = 24;
		A_p[3] = 34;
		A_p[4] = 44;
		A_p[5] = 52;
		A_p[6] = 60;
		A_p[7] = 66;
		A_p[8] = 72;
		A_p[9] = 76;
		A_p[10] = 80;

		H_x[0] = 1.344566e+02f;
		H_x[1] = 4.114478e+01f;
		H_x[2] = 1.000269e+02f;
		H_x[3] = 3.169500e+01f;
		H_x[4] = 6.190011e+01f;
		H_x[5] = 2.023139e+01f;
		H_x[6] = 2.567725e+01f;
		H_x[7] = 8.808511e+00f;
		H_x[8] = 4.114478e+01f;
		H_x[9] = 3.436150e+01f;
		H_x[10] = 3.099487e+01f;
		H_x[11] = 2.477126e+01f;
		H_x[12] = 1.931418e+01f;
		H_x[13] = 1.576652e+01f;
		H_x[14] = 8.233726e+00f;
		H_x[15] = 6.910587e+00f;
		H_x[16] = 1.000269e+02f;
		H_x[17] = 3.099487e+01f;
		H_x[18] = 8.804002e+01f;
		H_x[19] = 2.792375e+01f;
		H_x[20] = 5.644363e+01f;
		H_x[21] = 1.883764e+01f;
		H_x[22] = 2.413991e+01f;
		H_x[23] = 8.414358e+00f;
		H_x[24] = 3.169500e+01f;
		H_x[25] = 2.477126e+01f;
		H_x[26] = 2.792375e+01f;
		H_x[27] = 2.454154e+01f;
		H_x[28] = 1.838345e+01f;
		H_x[29] = 1.514642e+01f;
		H_x[30] = 8.018635e+00f;
		H_x[31] = 6.775021e+00f;
		H_x[32] = 6.190011e+01f;
		H_x[33] = 1.931418e+01f;
		H_x[34] = 5.644363e+01f;
		H_x[35] = 1.838345e+01f;
		H_x[36] = 4.711061e+01f;
		H_x[37] = 1.565679e+01f;
		H_x[38] = 2.097070e+01f;
		H_x[39] = 7.558490e+00f;
		H_x[40] = 2.023139e+01f;
		H_x[41] = 1.576652e+01f;
		H_x[42] = 1.883764e+01f;
		H_x[43] = 1.514642e+01f;
		H_x[44] = 1.565679e+01f;
		H_x[45] = 1.510759e+01f;
		H_x[46] = 7.391926e+00f;
		H_x[47] = 6.332568e+00f;
		H_x[48] = 2.567725e+01f;
		H_x[49] = 8.233726e+00f;
		H_x[50] = 2.413991e+01f;
		H_x[51] = 8.018635e+00f;
		H_x[52] = 2.097070e+01f;
		H_x[53] = 7.391926e+00f;
		H_x[54] = 1.634423e+01f;
		H_x[55] = 5.541646e+00f;
		H_x[56] = 8.808511e+00f;
		H_x[57] = 6.910587e+00f;
		H_x[58] = 8.414358e+00f;
		H_x[59] = 6.775021e+00f;
		H_x[60] = 7.558490e+00f;
		H_x[61] = 6.332568e+00f;
		H_x[62] = 5.541646e+00f;
		H_x[63] = 6.871756e+00f;
		H_x[64] = 2.000000e+00f;
		H_x[65] = 2.000000e+00f;
		H_i[0] = 0;
		H_i[1] = 1;
		H_i[2] = 2;
		H_i[3] = 3;
		H_i[4] = 4;
		H_i[5] = 5;
		H_i[6] = 6;
		H_i[7] = 7;
		H_i[8] = 0;
		H_i[9] = 1;
		H_i[10] = 2;
		H_i[11] = 3;
		H_i[12] = 4;
		H_i[13] = 5;
		H_i[14] = 6;
		H_i[15] = 7;
		H_i[16] = 0;
		H_i[17] = 1;
		H_i[18] = 2;
		H_i[19] = 3;
		H_i[20] = 4;
		H_i[21] = 5;
		H_i[22] = 6;
		H_i[23] = 7;
		H_i[24] = 0;
		H_i[25] = 1;
		H_i[26] = 2;
		H_i[27] = 3;
		H_i[28] = 4;
		H_i[29] = 5;
		H_i[30] = 6;
		H_i[31] = 7;
		H_i[32] = 0;
		H_i[33] = 1;
		H_i[34] = 2;
		H_i[35] = 3;
		H_i[36] = 4;
		H_i[37] = 5;
		H_i[38] = 6;
		H_i[39] = 7;
		H_i[40] = 0;
		H_i[41] = 1;
		H_i[42] = 2;
		H_i[43] = 3;
		H_i[44] = 4;
		H_i[45] = 5;
		H_i[46] = 6;
		H_i[47] = 7;
		H_i[48] = 0;
		H_i[49] = 1;
		H_i[50] = 2;
		H_i[51] = 3;
		H_i[52] = 4;
		H_i[53] = 5;
		H_i[54] = 6;
		H_i[55] = 7;
		H_i[56] = 0;
		H_i[57] = 1;
		H_i[58] = 2;
		H_i[59] = 3;
		H_i[60] = 4;
		H_i[61] = 5;
		H_i[62] = 6;
		H_i[63] = 7;
		H_i[64] = 8;
		H_i[65] = 9;
		H_p[0] = 0;
		H_p[1] = 8;
		H_p[2] = 16;
		H_p[3] = 24;
		H_p[4] = 32;
		H_p[5] = 40;
		H_p[6] = 48;
		H_p[7] = 56;
		H_p[8] = 64;
		H_p[9] = 65;
		H_p[10] = 66;

		osqp_settings = (OSQPSettings *)c_malloc(sizeof(OSQPSettings));
		osqp_data = (OSQPData *)c_malloc(sizeof(OSQPData));
		for(int osqp_it=0; osqp_it < 40; ++osqp_it) osqp_lb[osqp_it] = -100000;
		osqp_data->n = 10;
		osqp_data->m = 40;
		osqp_data->q = osqp_q;
		osqp_data->l = osqp_lb;
		osqp_data->u = osqp_ub;
		osqp_data->P = csc_matrix(osqp_data->n, osqp_data->n, 66, H_x, H_i, H_p);
		osqp_data->A = csc_matrix(osqp_data->m, osqp_data->n, 80, A_x, A_i, A_p);
		osqp_set_default_settings(osqp_settings);
		osqp_work = osqp_setup(osqp_data, osqp_settings);
		tmpu = darray(1,2,1,1);
		du = darray(1,2,1,1);
		Yzad = darray(1,10,1,1);
		y0 = darray(1,2,1,5);
		Y0 = darray(1,10,1,1);
		uk = darray(1,2,1,1);
		disturbance = darray(1,2,1,1);
		control_value = darray(1,1,1,2);
		ftmp1 = darray(1,10,1,1);
		ftmp4 = darray(1,10,1,1);
		fconst = darray(1,10,1,10);
		fconst[1][1] = 0.000000e+00f;
		fconst[1][2] = 0.000000e+00f;
		fconst[1][3] = -5.104583e+00f;
		fconst[1][4] = -1.622249e+00f;
		fconst[1][5] = -7.603490e+00f;
		fconst[1][6] = -1.928652e+00f;
		fconst[1][7] = -8.826808e+00f;
		fconst[1][8] = -1.986524e+00f;
		fconst[1][9] = -9.425674e+00f;
		fconst[1][10] = -1.997455e+00f;
		fconst[2][1] = 0.000000e+00f;
		fconst[2][2] = 0.000000e+00f;
		fconst[2][3] = -1.264241e+00f;
		fconst[2][4] = -2.853981e+00f;
		fconst[2][5] = -1.729329e+00f;
		fconst[2][6] = -3.671660e+00f;
		fconst[2][7] = -1.900426e+00f;
		fconst[2][8] = -3.905929e+00f;
		fconst[2][9] = -1.963369e+00f;
		fconst[2][10] = -3.973048e+00f;
		fconst[3][1] = 0.000000e+00f;
		fconst[3][2] = 0.000000e+00f;
		fconst[3][3] = 0.000000e+00f;
		fconst[3][4] = 0.000000e+00f;
		fconst[3][5] = -5.104583e+00f;
		fconst[3][6] = -1.622249e+00f;
		fconst[3][7] = -7.603490e+00f;
		fconst[3][8] = -1.928652e+00f;
		fconst[3][9] = -8.826808e+00f;
		fconst[3][10] = -1.986524e+00f;
		fconst[4][1] = 0.000000e+00f;
		fconst[4][2] = 0.000000e+00f;
		fconst[4][3] = 0.000000e+00f;
		fconst[4][4] = 0.000000e+00f;
		fconst[4][5] = -1.264241e+00f;
		fconst[4][6] = -2.853981e+00f;
		fconst[4][7] = -1.729329e+00f;
		fconst[4][8] = -3.671660e+00f;
		fconst[4][9] = -1.900426e+00f;
		fconst[4][10] = -3.905929e+00f;
		fconst[5][1] = 0.000000e+00f;
		fconst[5][2] = 0.000000e+00f;
		fconst[5][3] = 0.000000e+00f;
		fconst[5][4] = 0.000000e+00f;
		fconst[5][5] = 0.000000e+00f;
		fconst[5][6] = 0.000000e+00f;
		fconst[5][7] = -5.104583e+00f;
		fconst[5][8] = -1.622249e+00f;
		fconst[5][9] = -7.603490e+00f;
		fconst[5][10] = -1.928652e+00f;
		fconst[6][1] = 0.000000e+00f;
		fconst[6][2] = 0.000000e+00f;
		fconst[6][3] = 0.000000e+00f;
		fconst[6][4] = 0.000000e+00f;
		fconst[6][5] = 0.000000e+00f;
		fconst[6][6] = 0.000000e+00f;
		fconst[6][7] = -1.264241e+00f;
		fconst[6][8] = -2.853981e+00f;
		fconst[6][9] = -1.729329e+00f;
		fconst[6][10] = -3.671660e+00f;
		fconst[7][1] = 0.000000e+00f;
		fconst[7][2] = 0.000000e+00f;
		fconst[7][3] = 0.000000e+00f;
		fconst[7][4] = 0.000000e+00f;
		fconst[7][5] = 0.000000e+00f;
		fconst[7][6] = 0.000000e+00f;
		fconst[7][7] = 0.000000e+00f;
		fconst[7][8] = 0.000000e+00f;
		fconst[7][9] = -5.104583e+00f;
		fconst[7][10] = -1.622249e+00f;
		fconst[8][1] = 0.000000e+00f;
		fconst[8][2] = 0.000000e+00f;
		fconst[8][3] = 0.000000e+00f;
		fconst[8][4] = 0.000000e+00f;
		fconst[8][5] = 0.000000e+00f;
		fconst[8][6] = 0.000000e+00f;
		fconst[8][7] = 0.000000e+00f;
		fconst[8][8] = 0.000000e+00f;
		fconst[8][9] = -1.264241e+00f;
		fconst[8][10] = -2.853981e+00f;
		fconst[9][1] = 0.000000e+00f;
		fconst[9][2] = 0.000000e+00f;
		fconst[9][3] = 0.000000e+00f;
		fconst[9][4] = 0.000000e+00f;
		fconst[9][5] = 0.000000e+00f;
		fconst[9][6] = 0.000000e+00f;
		fconst[9][7] = 0.000000e+00f;
		fconst[9][8] = 0.000000e+00f;
		fconst[9][9] = 0.000000e+00f;
		fconst[9][10] = 0.000000e+00f;
		fconst[10][1] = 0.000000e+00f;
		fconst[10][2] = 0.000000e+00f;
		fconst[10][3] = 0.000000e+00f;
		fconst[10][4] = 0.000000e+00f;
		fconst[10][5] = 0.000000e+00f;
		fconst[10][6] = 0.000000e+00f;
		fconst[10][7] = 0.000000e+00f;
		fconst[10][8] = 0.000000e+00f;
		fconst[10][9] = 0.000000e+00f;
		fconst[10][10] = 0.000000e+00f;
		btmp1 = darray(1,40,1,1);
		bvar = darray(1,40,1,2);
		bvar[1][1] = 0.000000e+00f;
		bvar[1][2] = 0.000000e+00f;
		bvar[2][1] = 0.000000e+00f;
		bvar[2][2] = 0.000000e+00f;
		bvar[3][1] = 0.000000e+00f;
		bvar[3][2] = 0.000000e+00f;
		bvar[4][1] = 0.000000e+00f;
		bvar[4][2] = 0.000000e+00f;
		bvar[5][1] = 0.000000e+00f;
		bvar[5][2] = 0.000000e+00f;
		bvar[6][1] = 0.000000e+00f;
		bvar[6][2] = 0.000000e+00f;
		bvar[7][1] = 0.000000e+00f;
		bvar[7][2] = 0.000000e+00f;
		bvar[8][1] = 0.000000e+00f;
		bvar[8][2] = 0.000000e+00f;
		bvar[9][1] = 0.000000e+00f;
		bvar[9][2] = 0.000000e+00f;
		bvar[10][1] = 0.000000e+00f;
		bvar[10][2] = 0.000000e+00f;
		bvar[11][1] = 0.000000e+00f;
		bvar[11][2] = 0.000000e+00f;
		bvar[12][1] = 0.000000e+00f;
		bvar[12][2] = 0.000000e+00f;
		bvar[13][1] = 0.000000e+00f;
		bvar[13][2] = 0.000000e+00f;
		bvar[14][1] = 0.000000e+00f;
		bvar[14][2] = 0.000000e+00f;
		bvar[15][1] = 0.000000e+00f;
		bvar[15][2] = 0.000000e+00f;
		bvar[16][1] = 0.000000e+00f;
		bvar[16][2] = 0.000000e+00f;
		bvar[17][1] = 0.000000e+00f;
		bvar[17][2] = 0.000000e+00f;
		bvar[18][1] = 0.000000e+00f;
		bvar[18][2] = 0.000000e+00f;
		bvar[19][1] = 0.000000e+00f;
		bvar[19][2] = 0.000000e+00f;
		bvar[20][1] = 0.000000e+00f;
		bvar[20][2] = 0.000000e+00f;
		bvar[21][1] = 1.000000e+00f;
		bvar[21][2] = 0.000000e+00f;
		bvar[22][1] = 0.000000e+00f;
		bvar[22][2] = 1.000000e+00f;
		bvar[23][1] = 1.000000e+00f;
		bvar[23][2] = 0.000000e+00f;
		bvar[24][1] = 0.000000e+00f;
		bvar[24][2] = 1.000000e+00f;
		bvar[25][1] = 1.000000e+00f;
		bvar[25][2] = 0.000000e+00f;
		bvar[26][1] = 0.000000e+00f;
		bvar[26][2] = 1.000000e+00f;
		bvar[27][1] = 1.000000e+00f;
		bvar[27][2] = 0.000000e+00f;
		bvar[28][1] = 0.000000e+00f;
		bvar[28][2] = 1.000000e+00f;
		bvar[29][1] = 1.000000e+00f;
		bvar[29][2] = 0.000000e+00f;
		bvar[30][1] = 0.000000e+00f;
		bvar[30][2] = 1.000000e+00f;
		bvar[31][1] = -1.000000e+00f;
		bvar[31][2] = -0.000000e+00f;
		bvar[32][1] = -0.000000e+00f;
		bvar[32][2] = -1.000000e+00f;
		bvar[33][1] = -1.000000e+00f;
		bvar[33][2] = -0.000000e+00f;
		bvar[34][1] = -0.000000e+00f;
		bvar[34][2] = -1.000000e+00f;
		bvar[35][1] = -1.000000e+00f;
		bvar[35][2] = -0.000000e+00f;
		bvar[36][1] = -0.000000e+00f;
		bvar[36][2] = -1.000000e+00f;
		bvar[37][1] = -1.000000e+00f;
		bvar[37][2] = -0.000000e+00f;
		bvar[38][1] = -0.000000e+00f;
		bvar[38][2] = -1.000000e+00f;
		bvar[39][1] = -1.000000e+00f;
		bvar[39][2] = -0.000000e+00f;
		bvar[40][1] = -0.000000e+00f;
		bvar[40][2] = -1.000000e+00f;
		btmp2 = darray(1,40,1,1);
		b = darray(1,40,1,1);
		b[1][1] = 1.000000e-02f;
		b[2][1] = 1.000000e-02f;
		b[3][1] = 1.000000e-02f;
		b[4][1] = 1.000000e-02f;
		b[5][1] = 1.000000e-02f;
		b[6][1] = 1.000000e-02f;
		b[7][1] = 1.000000e-02f;
		b[8][1] = 1.000000e-02f;
		b[9][1] = 1.000000e-02f;
		b[10][1] = 1.000000e-02f;
		b[11][1] = 1.000000e-02f;
		b[12][1] = 1.000000e-02f;
		b[13][1] = 1.000000e-02f;
		b[14][1] = 1.000000e-02f;
		b[15][1] = 1.000000e-02f;
		b[16][1] = 1.000000e-02f;
		b[17][1] = 1.000000e-02f;
		b[18][1] = 1.000000e-02f;
		b[19][1] = 1.000000e-02f;
		b[20][1] = 1.000000e-02f;
		b[21][1] = 1.000000e+00f;
		b[22][1] = 1.000000e+00f;
		b[23][1] = 1.000000e+00f;
		b[24][1] = 1.000000e+00f;
		b[25][1] = 1.000000e+00f;
		b[26][1] = 1.000000e+00f;
		b[27][1] = 1.000000e+00f;
		b[28][1] = 1.000000e+00f;
		b[29][1] = 1.000000e+00f;
		b[30][1] = 1.000000e+00f;
		b[31][1] = 1.000000e+00f;
		b[32][1] = 1.000000e+00f;
		b[33][1] = 1.000000e+00f;
		b[34][1] = 1.000000e+00f;
		b[35][1] = 1.000000e+00f;
		b[36][1] = 1.000000e+00f;
		b[37][1] = 1.000000e+00f;
		b[38][1] = 1.000000e+00f;
		b[39][1] = 1.000000e+00f;
		b[40][1] = 1.000000e+00f;
		GPC_b = darray3(1,2,1,2,1,4);
		GPC_b[1][1][1] = 0.000000e+00f;
		GPC_b[1][1][2] = 2.552292e+00f;
		GPC_b[1][1][3] = -9.389356e-01f;
		GPC_b[1][1][4] = 0.000000e+00f;
		GPC_b[1][2][1] = 0.000000e+00f;
		GPC_b[1][2][2] = 6.321206e-01f;
		GPC_b[1][2][3] = -3.094493e-01f;
		GPC_b[1][2][4] = 0.000000e+00f;
		GPC_b[2][1][1] = 0.000000e+00f;
		GPC_b[2][1][2] = 8.111244e-01f;
		GPC_b[2][1][3] = -2.323910e-01f;
		GPC_b[2][1][4] = 0.000000e+00f;
		GPC_b[2][2][1] = 0.000000e+00f;
		GPC_b[2][2][2] = 1.426990e+00f;
		GPC_b[2][2][3] = -2.695237e-01f;
		GPC_b[2][2][4] = 0.000000e+00f;
		GPC_a = darray(1,2,1,2);
		GPC_a[1][1] = -8.574211e-01f;
		GPC_a[1][2] = 1.800923e-01f;
		GPC_a[2][1] = -4.753804e-01f;
		GPC_a[2][2] = 5.411377e-02f;
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
	for(j=1;j<=2;++j) for(k=1;k<=1;++k) tmpu[j][k] = 0;
	for(j=1;j<=2;++j) for(k=1;k<=1;++k) du[j][k] = 0;
	for(j=1;j<=10;++j) for(k=1;k<=1;++k) Yzad[j][k] = 0;
	for(j=1;j<=2;++j) for(k=1;k<=5;++k) y0[j][k] = 0;
	for(j=1;j<=10;++j) for(k=1;k<=1;++k) Y0[j][k] = 0;
	itmp=1;
	for(i=1;i<=5;++i){
		for(j=1;j<=2;++j){
			Yzad[itmp][1]=ad->z[j-1];
			itmp=itmp+1;
		}
	}
	for(j=1;j<=2;++j) for(k=1;k<=1;++k) uk[j][k] = 0;
	for(i=1;i<=2;++i){
		uk[i][1]=ad->u[ad->k-1][i-1];
	}
	for(j=1;j<=2;++j) for(k=1;k<=1;++k) disturbance[j][k] = 0;
	for(m=1;m<=2;++m){
		disturbance[m][1]=0;
		for(n=1;n<=2;++n){
			for(i=1;i<=4;++i){
				disturbance[m][1]=disturbance[m][1]+GPC_b[m][n][i]*ad->u[ad->k-i][n-1];
			}
		}
		for(i=1;i<=2;++i){
			disturbance[m][1]=disturbance[m][1]-GPC_a[m][i]*ad->y[ad->k-i][m-1];
		}
		disturbance[m][1]=ad->y[ad->k][m-1]-disturbance[m][1];
		for(p=1;p<=5;++p){
			Iyf=p-1;
			if(2<Iyf){
				Iyf=2;
			}
			Iuftmp=4;
			if(p<Iuftmp){
				Iuftmp=p;
			}
			Iuf=0;
			if(Iuftmp>Iuf){
				Iuf=Iuftmp;
			}
			y0[m][p]=disturbance[m][1];
			for(n=1;n<=2;++n){
				for(r=1;r<=Iuf;++r){
					y0[m][p]=y0[m][p]+GPC_b[m][n][r]*ad->u[ad->k-1][n-1];
				}
			}
			for(n=1;n<=2;++n){
				for(r=(Iuf+1);r<=4;++r){
					y0[m][p]=y0[m][p]+GPC_b[m][n][r]*ad->u[ad->k-r+p][n-1];
				}
			}
			for(r=1;r<=Iyf;++r){
				y0[m][p]=y0[m][p]-GPC_a[m][r]*y0[m][p-r];
			}
			for(r=(Iyf+1);r<=2;++r){
				y0[m][p]=y0[m][p]-GPC_a[m][r]*ad->y[ad->k-r+p][m-1];
			}
		}
	}
	itmp=1;
	for(i=1;i<=5;++i){
		for(j=1;j<=2;++j){
			Y0[itmp][1]=y0[j][i];
			itmp=itmp+1;
		}
	}
	sumaa(Yzad,Y0,ftmp1,10,1,-1);
	productab(fconst,ftmp1,ftmp4,10,10,10,1);
	for(i=1;i<=10;++i){
		ftmp[i]=ftmp4[i][1];
	}
	productab(bvar,uk,btmp1,40,2,2,1);
	sumaa(b,btmp1,btmp2,40,1,1);
	for(i=1;i<=40;++i){
		btmp[i]=btmp2[i][1];
	}
	for(i=1;i<=2;++i){
		qpx[i]=0;
	}
	memcpy (osqp_q, &(ftmp[1]), 10*sizeof(c_float));
	osqp_update_lin_cost(osqp_work, osqp_q);
	memcpy (osqp_ub, &(btmp[1]), 40*sizeof(c_float));
	osqp_update_bounds(osqp_work, osqp_lb, osqp_ub);
	osqp_solve(osqp_work);
	memcpy (&(qpx[1]), osqp_work->solution->x, 10*sizeof(c_float));

	for(i=1;i<=2;++i){
		du[i][1]=qpx[i];
	}
	for(n=1;n<=2;++n){
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
	for(j=1;j<=1;++j) for(k=1;k<=2;++k) control_value[j][k] = 0;
	for(n=1;n<=2;++n){
		control_value[1][n]=du[n][1];
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
	if(++i > 10) profiler_print();
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
