#include "C:\Users\Admin\Documents\GitHub\Cpp\Kompilator_skrosny\Libs\C\defines.h"
#include "C:\Users\Admin\Documents\GitHub\Cpp\Kompilator_skrosny\Libs\C\mpctools.h"
#include "C:\Users\Admin\Documents\GitHub\Cpp\Kompilator_skrosny\Libs\C\simulated_signals.h"
#include "C:\Users\Admin\Documents\GitHub\Cpp\Kompilator_skrosny\Libs\C\default_functions.h"
#include "stm32f7xx_hal.h"
#include <string.h>
#include "low_lvl_main.h"
#include "obl_macierzowe.h"
#include "mat_lib.h"
#include "alokacja_nr.h"
#include "pk.h"

#define __FUN_WRITE() {write_string((char*)__func__);write_string((char*)"\r\n");}while(0)

float us[3] = {0.0f};
float avg_us[1] = {0.0f};
int maximum_ind = -1;
char str[100] = {0};

extern ADC_HandleTypeDef hadc3;
extern DMA_HandleTypeDef hdma_adc3;

extern DAC_HandleTypeDef hdac;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim5;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart6;

extern void timer_loop(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    if (htim->Instance == TIM2) {
        timer_loop();
    }


}

long get_time(){
    return HAL_GetTick();
}

float* measureOutput(){
    return __measureOutput(); // values from -1 to 1
}

void setControlValue(float* value){ // values from -1 to 1
    __setControlValue(value);
}

void hardware_setup(){
    low_lvl_main();
}

void string_spin(){
    static int ind = 0;
    static char txt[3] = "?\r\0";
    // static char stages[4] = {'\\','|','/','-'}; int ssize = 4;
    static char stages[5] = {' ','_','o','O','o'}; int ssize = 5;
    txt[0] = stages[ind];
    write_string(txt);
    ind = (ind+1)%ssize;
}

void printMat(float ** A, long x, long y, const char * fmat){
    long i = 1;
    long j = 1;
    for(i=1; i<=x; ++i){
        if(i==1) write_string("[");
        else     write_string(" ");
        for(j=1; j<=y; ++j){
            sprintf(str,fmat,A[i][j]);
            write_string(str);
            if(j==y && i!=x) write_string(";\n\r");
            if(j!=y) write_string(",");
        }
        if(i==x) write_string("]\n\r");
    }
}

void printVec(float * A, long x, const char * fmat){
    long i = 1;
    write_string("[");
    for(i=1; i<=x; ++i){
        if(i!=1) write_string(" ");
        sprintf(str,fmat,A[i]);
        write_string(str);
        if(i!=x) write_string(";\n\r");
    }
    write_string("]\n\r");
}
//////////////////////////////////////////////////// TUTAJ ZACZYNA SIE ROBOTA SPECJALISTY MATLAB
void CONTROLLER(ArchiveData * ad, CurrentControl * c){
	static float Kyzad[1][1] = {{+3.005202799571041e-01f}};
	static float Ku[1][1][2] = {{{-5.941193939204396e-02f,+5.941193939204396e-02f}}};
	static float Ky[1][1][3] = {{{-1.028291081879766e+00f,+7.617469811487909e-01f,-3.397617922612951e-02f}}};

	static long r,m,n,j;
	static float du[1];
	const long k = 0;
	if(ad == NULL) return;
	for(r=0;r<1;++r){
		du[r] = 0.0f;
		for(m=0;m<1;++m){
			du[r] += Kyzad[r][m]*ad->z[m];
		}
		for(n=0;n<1;++n){
			for(j=0;j<2;++j){
				du[r] += Ku[r][n][j]*ad->u[k-j-1][n];
			}
		}
		for(m=0;m<1;++m){
			for(j=0;j<3;++j){
				du[r] += Ky[r][m][j]*ad->y[k-j][m];
			}
		}
	}
	for(n=0;n<1;++n){
		if(ad->u[k-1][n]+du[n] > +1.000000000000000e+00f) du[n] = +1.000000000000000e+00f-ad->u[k-1][n];
		if(ad->u[k-1][n]+du[n] < -1.000000000000000e+00f) du[n] = -1.000000000000000e+00f-ad->u[k-1][n];
	}
	setCurrentControlIncrement(c,du);
}
void CONTROLLER_N(ArchiveData * ad, CurrentControl * c){
	static long m,i,j,p,n,l;
	static float ymod,ddmc,liczba;
	static float du[1];
	static float **reg_M,**reg_PSI,**reg_LAMBDA;
	static float **mod_wspa,***mod_wspb,*reg_Yzad,*reg_Y0;
	static float **pk_A,**pk_G,*pk_b,*pk_t,*pk_x,*reg_wp1,**reg_mp1,**reg_gpc_y0;
	const long k = 0;
	if(ad == NULL){
		mod_wspa=dtablica(1,1,1,2);
		mod_wspb=dtablica3(1,1,1,1,1,2);
		reg_M=dtablica(1,20,1,5);
		reg_PSI=dtablica(1,20,1,20);
		reg_LAMBDA=dtablica(1,5,1,5);
		mod_wspa[1][1] = -7.875594597027000e-01f;
		mod_wspa[1][2] = +3.526926067685000e-02f;
		mod_wspb[1][1][1] = +1.783577301464000e-01f;
		mod_wspb[1][1][2] = +6.167306699759000e-02f;
		reg_M[1][1] = +1.783577301464000e-01f;		reg_M[1][2] = +0.000000000000000e+00f;		reg_M[1][3] = +0.000000000000000e+00f;		reg_M[1][4] = +0.000000000000000e+00f;		reg_M[1][5] = +0.000000000000000e+00f;		reg_M[2][1] = +3.804981147318888e-01f;		reg_M[2][2] = +1.783577301464000e-01f;		reg_M[2][3] = +0.000000000000000e+00f;		reg_M[2][4] = +0.000000000000000e+00f;		reg_M[2][5] = +0.000000000000000e+00f;		reg_M[3][1] = +5.334051415218677e-01f;		reg_M[3][2] = +3.804981147318888e-01f;		reg_M[3][3] = +1.783577301464000e-01f;		reg_M[3][4] = +0.000000000000000e+00f;		reg_M[3][5] = +0.000000000000000e+00f;		reg_M[4][1] = +6.466991750080654e-01f;		reg_M[4][2] = +5.334051415218677e-01f;		reg_M[4][3] = +3.804981147318888e-01f;		reg_M[4][4] = +1.783577301464000e-01f;		reg_M[4][5] = +0.000000000000000e+00f;		reg_M[5][1] = +7.305320450208170e-01f;		reg_M[5][2] = +6.466991750080654e-01f;		reg_M[5][3] = +5.334051415218677e-01f;		reg_M[5][4] = +3.804981147318888e-01f;		reg_M[5][5] = +1.783577301464000e-01f;		reg_M[6][1] = +7.925596180332299e-01f;		reg_M[6][2] = +7.305320450208170e-01f;		reg_M[6][3] = +6.466991750080654e-01f;		reg_M[6][4] = +5.334051415218677e-01f;		reg_M[6][5] = +3.804981147318888e-01f;		reg_M[7][1] = +8.384532965757874e-01f;		reg_M[7][2] = +7.925596180332299e-01f;		reg_M[7][3] = +7.305320450208170e-01f;		reg_M[7][4] = +6.466991750080654e-01f;		reg_M[7][5] = +5.334051415218677e-01f;		reg_M[8][1] = +8.724096306108061e-01f;		reg_M[8][2] = +8.384532965757874e-01f;		reg_M[8][3] = +7.925596180332299e-01f;		reg_M[8][4] = +7.305320450208170e-01f;		reg_M[8][5] = +6.466991750080654e-01f;		reg_M[9][1] = +8.975336265849729e-01f;		reg_M[9][2] = +8.724096306108061e-01f;		reg_M[9][3] = +8.384532965757874e-01f;		reg_M[9][4] = +7.925596180332299e-01f;		reg_M[9][5] = +7.305320450208170e-01f;		reg_M[10][1] = +9.161226524832493e-01f;		reg_M[10][2] = +8.975336265849729e-01f;		reg_M[10][3] = +8.724096306108061e-01f;		reg_M[10][4] = +8.384532965757874e-01f;		reg_M[10][5] = +7.925596180332299e-01f;		reg_M[11][1] = +9.298765109128383e-01f;		reg_M[11][2] = +9.161226524832493e-01f;		reg_M[11][3] = +8.975336265849729e-01f;		reg_M[11][4] = +8.724096306108061e-01f;		reg_M[11][5] = +8.384532965757874e-01f;		reg_M[12][1] = +9.400528710263377e-01f;		reg_M[12][2] = +9.298765109128383e-01f;		reg_M[12][3] = +9.161226524832493e-01f;		reg_M[12][4] = +8.975336265849729e-01f;		reg_M[12][5] = +8.724096306108061e-01f;		reg_M[13][1] = +9.475822712807999e-01f;		reg_M[13][2] = +9.400528710263377e-01f;		reg_M[13][3] = +9.298765109128383e-01f;		reg_M[13][4] = +9.161226524832493e-01f;		reg_M[13][5] = +8.975336265849729e-01f;		reg_M[14][1] = +9.531532089795050e-01f;		reg_M[14][2] = +9.475822712807999e-01f;		reg_M[14][3] = +9.400528710263377e-01f;		reg_M[14][4] = +9.298765109128383e-01f;		reg_M[14][5] = +9.161226524832493e-01f;		reg_M[15][1] = +9.572750972832195e-01f;		reg_M[15][2] = +9.531532089795050e-01f;		reg_M[15][3] = +9.475822712807999e-01f;		reg_M[15][4] = +9.400528710263377e-01f;		reg_M[15][5] = +9.298765109128383e-01f;		reg_M[16][1] = +9.603248465547377e-01f;		reg_M[16][2] = +9.572750972832195e-01f;		reg_M[16][3] = +9.531532089795050e-01f;		reg_M[16][4] = +9.475822712807999e-01f;		reg_M[16][5] = +9.400528710263377e-01f;		reg_M[17][1] = +9.625813294901787e-01f;		reg_M[17][2] = +9.603248465547377e-01f;		reg_M[17][3] = +9.572750972832195e-01f;		reg_M[17][4] = +9.531532089795050e-01f;		reg_M[17][5] = +9.475822712807999e-01f;		reg_M[18][1] = +9.642508815695867e-01f;		reg_M[18][2] = +9.625813294901787e-01f;		reg_M[18][3] = +9.603248465547377e-01f;		reg_M[18][4] = +9.572750972832195e-01f;		reg_M[18][5] = +9.531532089795050e-01f;		reg_M[19][1] = +9.654861686183279e-01f;		reg_M[19][2] = +9.642508815695867e-01f;		reg_M[19][3] = +9.625813294901787e-01f;		reg_M[19][4] = +9.603248465547377e-01f;		reg_M[19][5] = +9.572750972832195e-01f;		reg_M[20][1] = +9.664001467515101e-01f;		reg_M[20][2] = +9.654861686183279e-01f;		reg_M[20][3] = +9.642508815695867e-01f;		reg_M[20][4] = +9.625813294901787e-01f;		reg_M[20][5] = +9.603248465547377e-01f;
		for(i=1;i<=20;++i)
			for(j=1;j<=20;++j)
				reg_PSI[i][j] = 0.0f;
		reg_PSI[1][1] = +1.000000000000000e+00f;
		reg_PSI[2][2] = +1.000000000000000e+00f;
		reg_PSI[3][3] = +1.000000000000000e+00f;
		reg_PSI[4][4] = +1.000000000000000e+00f;
		reg_PSI[5][5] = +1.000000000000000e+00f;
		reg_PSI[6][6] = +1.000000000000000e+00f;
		reg_PSI[7][7] = +1.000000000000000e+00f;
		reg_PSI[8][8] = +1.000000000000000e+00f;
		reg_PSI[9][9] = +1.000000000000000e+00f;
		reg_PSI[10][10] = +1.000000000000000e+00f;
		reg_PSI[11][11] = +1.000000000000000e+00f;
		reg_PSI[12][12] = +1.000000000000000e+00f;
		reg_PSI[13][13] = +1.000000000000000e+00f;
		reg_PSI[14][14] = +1.000000000000000e+00f;
		reg_PSI[15][15] = +1.000000000000000e+00f;
		reg_PSI[16][16] = +1.000000000000000e+00f;
		reg_PSI[17][17] = +1.000000000000000e+00f;
		reg_PSI[18][18] = +1.000000000000000e+00f;
		reg_PSI[19][19] = +1.000000000000000e+00f;
		reg_PSI[20][20] = +1.000000000000000e+00f;

		for(i=1;i<=5;++i)
			for(j=1;j<=5;++j)
				reg_LAMBDA[i][j] = 0.0f;
		reg_LAMBDA[1][1] = +1.000000000000000e+01f;
		reg_LAMBDA[2][2] = +1.000000000000000e+01f;
		reg_LAMBDA[3][3] = +1.000000000000000e+01f;
		reg_LAMBDA[4][4] = +1.000000000000000e+01f;
		reg_LAMBDA[5][5] = +1.000000000000000e+01f;

		ustawilogr(10);
		ustawilzm(5);

		inicjalizacjapk();
		pk_A=pobierzA();
		pk_G=pobierzG();
		pk_b=pobierzb();
		pk_t=pobierzt();
		pk_x=pobierzx();

		for(i=1;i<=10;++i)
			for(j=1;j<=5;++j)
				pk_A[i][j] = 0.0f;
		pk_A[1][1] = +1.000000000000000e+00f;
		pk_A[2][1] = -1.000000000000000e+00f;
		pk_A[3][1] = +1.000000000000000e+00f;
		pk_A[3][2] = +1.000000000000000e+00f;
		pk_A[4][1] = -1.000000000000000e+00f;
		pk_A[4][2] = -1.000000000000000e+00f;
		pk_A[5][1] = +1.000000000000000e+00f;
		pk_A[5][2] = +1.000000000000000e+00f;
		pk_A[5][3] = +1.000000000000000e+00f;
		pk_A[6][1] = -1.000000000000000e+00f;
		pk_A[6][2] = -1.000000000000000e+00f;
		pk_A[6][3] = -1.000000000000000e+00f;
		pk_A[7][1] = +1.000000000000000e+00f;
		pk_A[7][2] = +1.000000000000000e+00f;
		pk_A[7][3] = +1.000000000000000e+00f;
		pk_A[7][4] = +1.000000000000000e+00f;
		pk_A[8][1] = -1.000000000000000e+00f;
		pk_A[8][2] = -1.000000000000000e+00f;
		pk_A[8][3] = -1.000000000000000e+00f;
		pk_A[8][4] = -1.000000000000000e+00f;
		pk_A[9][1] = +1.000000000000000e+00f;
		pk_A[9][2] = +1.000000000000000e+00f;
		pk_A[9][3] = +1.000000000000000e+00f;
		pk_A[9][4] = +1.000000000000000e+00f;
		pk_A[9][5] = +1.000000000000000e+00f;
		pk_A[10][1] = -1.000000000000000e+00f;
		pk_A[10][2] = -1.000000000000000e+00f;
		pk_A[10][3] = -1.000000000000000e+00f;
		pk_A[10][4] = -1.000000000000000e+00f;
		pk_A[10][5] = -1.000000000000000e+00f;

		for(i=1;i<=10;++i)
			pk_b[i] = 0.0f;

		pk_G[1][1] = +4.853185302540036e+01f;
		pk_G[1][2] = +2.747350708510794e+01f;
		pk_G[1][3] = +2.620638381541338e+01f;
		pk_G[1][4] = +2.478461007666184e+01f;
		pk_G[1][5] = +2.324981436577183e+01f;
		pk_G[2][1] = +2.747350708510794e+01f;
		pk_G[2][2] = +4.666399453811768e+01f;
		pk_G[2][3] = +2.560741513502933e+01f;
		pk_G[2][4] = +2.434267942850513e+01f;
		pk_G[2][5] = +2.292413260050270e+01f;
		pk_G[3][1] = +2.620638381541338e+01f;
		pk_G[3][2] = +2.560741513502933e+01f;
		pk_G[3][3] = +4.479966745453108e+01f;
		pk_G[3][4] = +2.374547335656240e+01f;
		pk_G[3][5] = +2.248396150891912e+01f;
		pk_G[4][1] = +2.478461007666184e+01f;
		pk_G[4][2] = +2.434267942850513e+01f;
		pk_G[4][3] = +2.374547335656240e+01f;
		pk_G[4][4] = +4.294010792931563e+01f;
		pk_G[4][5] = +2.188913356547574e+01f;
		pk_G[5][1] = +2.324981436577183e+01f;
		pk_G[5][2] = +2.292413260050270e+01f;
		pk_G[5][3] = +2.248396150891912e+01f;
		pk_G[5][4] = +2.188913356547574e+01f;
		pk_G[5][5] = +4.108698229754947e+01f;

		reg_Yzad=dwektor(1,20);
		reg_Y0  =dwektor(1,20);
		reg_wp1 =dwektor(1,20);
		reg_mp1 =dtablica(1,5,1,20);
		reg_gpc_y0 =dtablica(1,1,1,20);
		return;
	}
	for(m=1;m<=1;m++){
		ymod=0.0f;
		for(n=1;n<=1;n++)
			for(i=1;i<=2;i++)
				ymod=ymod+mod_wspb[m][n][i]*ad->u[k-i][n-1];
		for(i=1;i<=2;i++)
			ymod=ymod-mod_wspa[m][i]*ad->y[k-i][m-1];
		ddmc=ad->y[k][m-1]-ymod;
		for(p=1;p<=20;p++){
			reg_gpc_y0[m][p]=ddmc;
			for(n=1;n<=1;n++){
				for(i=1;i<=2;i++){
					if(-i+p>=0)
						liczba=ad->u[k-1][n-1];
					else
						liczba=ad->u[k-i+p][n-1];
					reg_gpc_y0[m][p]=reg_gpc_y0[m][p]+mod_wspb[m][n][i]*liczba;
				}
			}
			for(i=1;i<=2;i++){
				if(-i+p>=1)
					liczba=reg_gpc_y0[m][p-i];
				else
					liczba=ad->y[k+p-i][m-1];
				reg_gpc_y0[m][p]=reg_gpc_y0[m][p]-mod_wspa[m][i]*liczba;
			}
		}
	}
	l=1;
	for(p=1;p<=20;p++){
		for(m=1;m<=1;m++){
			reg_Y0[l++]=reg_gpc_y0[m][p];
		}
	}
	l=1;
	for(p=1;p<=20;p++){
		for(m=0;m<1;m++){
			reg_Yzad[l++] = ad->z[m];
		}
	}

	i=1;
	for(p=0;p<=4;p++){
		for(n=1;n<=1;n++){
			pk_b[i++]=-1.000000000000000e+00f-ad->u[k-1][n-1];
			pk_b[i++]=-1.000000000000000e+00f+ad->u[k-1][n-1];
		}
	}

	for(i=1;i<=5;i++) pk_x[i]=0.0f;
	sumaww(reg_Yzad,reg_Y0,reg_wp1,20,-1);
	iloczynatb(reg_M,reg_PSI,reg_mp1,20,5,20,20);
	iloczynaw(reg_mp1,reg_wp1,pk_t,5,20,20);
	for(i=1;i<=5;i++) pk_t[i]=-2.0f*pk_t[i];

	i=pk();

	for(n=1;n<=1;n++) du[n-1]=pk_x[n];

	setCurrentControlIncrement(c,du);
}

//////////////////////////////////////////////////// TUTAJ ZACZYNA SIE ROBOTA UZYTKOWNIKA KONCOWEGO
ArchiveData ad;
CurrentControl cc;

void measurements(){
    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
    new_output(&ad,measureOutput());
}

void controller_setup(){
    init_archive_data(&ad, 100, 100, 1, 1, 0, 0, 0.01);
    init_current_control(&cc,&ad);
    get_time();
    CONTROLLER(NULL,NULL);
    CONTROLLER_N(NULL,NULL);
}

void idle(){
    const int k = 0;
    static int i = 0;
    static char str[100] = {0};
    // Komunikacja z komputerem zbierającym dane 
    // sprintf(str, "y=[%8.4f,%8.4f];z=[%8.4f,%8.4f];u=[%8.4f,%8.4f];\n\r", ad.y[k][0],ad.y[k][1],ad.z[0],ad.z[1],ad.u[k-1][0],ad.u[k-1][1]);
    sprintf(str, "y=%8.4f;z=%8.4f;u=%8.4f;us=[%8.4f, %8.4f, %8.4f];\n\r", ad.y[k][0],ad.z[0],ad.u[k-1][0],us[0],us[1],us[2]);
    write_string(str);

    if(i<50){    
        ad.z[0] = -0.5;
        HAL_GPIO_WritePin(SETPOINT_GPIO_Port,SETPOINT1_Pin,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(SETPOINT_GPIO_Port,SETPOINT2_Pin,GPIO_PIN_RESET);
    } else {
        ad.z[0] = +0.5;
        HAL_GPIO_WritePin(SETPOINT_GPIO_Port,SETPOINT1_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(SETPOINT_GPIO_Port,SETPOINT2_Pin,GPIO_PIN_SET);
    }   
    if(++i >= 100) i = 0;
    //HAL_Delay(1000);
}

void loop(){
    __startListening(&huart2);
    __startListening(&huart6);
    CONTROLLER_N(&ad,&cc);

    // static float du[1] = {0};
    // if(i++<500) du[0] = 0.0f;
    // else      du[0] = 1.0f;
    // setCurrentControl(&cc,du);
    // string_spin();
}

void controls(){
    static float * lu;
    const int k = 0;
    const float max_dif = 0.02;
    static int i = 0;
    static float avg = 0.0f;
    static float difs[3] = {0.0f};
    static char str[100] = {0};
    static int debug = 0;
    static int maximum_ind_2 = -1;

    HAL_Delay(20);
    us[2] = cc.du[0]+ad.u[k-1][0];
    us[1] = __getSlaveControlValue(&huart2);
    us[0] = __getSlaveControlValue(&huart6);

    // Decision!!!
    if(isnan(us[0]))
        us[0] = us[2];
    if(isnan(us[1]))
        us[1] = us[2];

    avg = 0.0f;
    for(i=0;i<3;++i) avg += us[i]/3;
    for(i=0;i<3;++i) difs[i] = us[i]-avg;
    for(i=0;i<3;++i) if(difs[i]*difs[i] <= max_dif*max_dif) difs[i] = 0.0f; // jesli jakies dif miesci sie w okregu, to nie jest juz interesujace

    if(debug){
        write_string("%%------------------------------------------------------\n\r");
        sprintf(str,"us=[%f,%f,%f];\n\r",us[0],us[1],us[2]); write_string(str);
        sprintf(str,"max_dif=%f;\n\r",max_dif); write_string(str);
        write_string("%%......................................................\n\r");
        sprintf(str,"avg=%f;\n\r",avg); write_string(str);
        sprintf(str,"difs=[%f,%f,%f];\n\r",difs[0],difs[1],difs[2]); write_string(str);
    }
    maximum_ind = -1;
    for(i=0;i<3;++i){
        if(difs[i] > 0.0f){
            maximum_ind = 0;
            break; // check if there are any nonzero difs;
        }
    }
    if(debug){
        sprintf(str,"maximum_ind=%d;\n\r",maximum_ind); write_string(str);
    }

    if(maximum_ind == -1){ // all signals are close
        avg_us[0] = avg;
    } else { // at least one signal is not close
        // look for largest dif
        for(i=0;i<3;++i) if(difs[maximum_ind]*difs[maximum_ind]<difs[i]*difs[i]) maximum_ind = i;
        if(debug){
            write_string("%%......................................................\n\r");
            sprintf(str,"maximum_ind=%d;\n\r",maximum_ind); write_string(str);
        }

        avg = 0.0f;
        for(i=0;i<3;++i) if(i!=maximum_ind) avg += us[i]/2;
        for(i=0;i<3;++i) if(i!=maximum_ind) difs[i] = us[i]-avg;
        for(i=0;i<3;++i) if(i!=maximum_ind) if(difs[i]*difs[i] <= max_dif*max_dif) difs[i] = 0.0f; // jesli jakies dif miesci sie w okregu, to nie jest juz interesujace
        if(debug){
            sprintf(str,"avg=%f;\n\r",avg); write_string(str);
            sprintf(str,"difs=[%f,%f,%f];\n\r",difs[0],difs[1],difs[2]); write_string(str);
        }
        maximum_ind_2 = -1;
        for(i=0;i<3;++i){
            if(i!=maximum_ind && difs[i] > 0.0f){
                maximum_ind_2 = 0;
                break;
            }
        }
        if(debug){
            sprintf(str,"maximum_ind=%d;\n\r",maximum_ind); write_string(str);
        }
        if(maximum_ind_2 == -1) avg_us[0] = avg; // those two signals are close enough
        else                    avg_us[0] = us[2]; // no signals are close enough, therefore I trust myself
    }
    if(debug){
        sprintf(str,"result=%f;\n\r",avg_us[0]); write_string(str);
    }

    setCurrentControl(&cc,avg_us);

    pushCurrentControlsToArchiveData(&cc,&ad);
    setControlValue(last_control(&ad));

    // __sendMasterControlValue(&huart1,last_control(&ad));
    lu = last_control(&ad);
    __sendMasterControlValue(&huart2,lu[0]);
    __sendMasterControlValue(&huart6,lu[0]);
    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);

 
}

void timeout(){
    //setControlValue(0.0);
    // while(1);
}

// zups
