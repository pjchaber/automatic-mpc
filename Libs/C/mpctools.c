#include <stdlib.h>
#include <math.h>
#include "./defines.h"
#include "./mpctools.h"

static float** create_matrix(long x, long y){
	float ** yp = NULL;
	long i;
	yp = (float**)malloc(sizeof(float*)*x);
	if(yp == 0) while(1);
	for(i = 0; i < x; ++i){
		yp[i] = (float*)malloc(sizeof(float)*y);
		if(yp[i] == 0) while(1);
	}
	return yp;
}

static float* create_vector(long x){
	float* p = (float*)malloc(sizeof(float)*x);
	if(p == 0) while(1);
	return p;
}

void init_archive_data(ArchiveDataPtr ad, long number_of_u, long number_of_y, long size_of_u, long size_of_y, float default_u, float default_y, float current_yzad){
	int i,j;
	ad->number_of_u = number_of_u;
	ad->number_of_y = number_of_y;
	ad->size_of_u = size_of_u;
	ad->size_of_y = size_of_y;
	ad->U    = create_matrix(number_of_u,size_of_u);
	ad->DU   = create_matrix(number_of_u,size_of_u);
	ad->Y    = create_matrix(number_of_y,size_of_y);
	ad->YZAD = create_vector(size_of_y);
	
	for(j=0; j<ad->size_of_u;++j){
		for(i=0; i<ad->number_of_u; ++i) ad->U[i][j] = default_u;
		for(i=0; i<ad->number_of_u; ++i) ad->DU[i][j] = 0;
	}
	for(j=0; j<(ad->size_of_y);++j)	{
		for(i=0; i<(ad->number_of_y); ++i) ad->Y[i][j] = default_y;
		ad->YZAD[j] = current_yzad;
	}
	
	ad-> u = &(ad-> U[ad->number_of_u  ]);
	ad->du = &(ad->DU[ad->number_of_u  ]);
	ad-> y = &(ad-> Y[ad->number_of_y-1]);
	ad-> z = ad->YZAD;

	ad->k = 0;
}

void init_current_control(CurrentControlPtr cc, ArchiveDataPtr ad){
	int i;
	cc->size_of_u = ad->size_of_u;
	cc->u  = (float*)malloc(sizeof(float)*cc->size_of_u);
	cc->du  = (float*)malloc(sizeof(float)*cc->size_of_u);
	if(cc->u == 0) while(1);
	if(cc->du == 0) while(1);
	for(i=0; i<cc->size_of_u; ++i) cc->u[i] = ad->U[0][i];
	for(i=0; i<cc->size_of_u; ++i) cc->du[i] = 0;
}

void new_control(ArchiveDataPtr ad, float* u){
	int i,j;
	for(j=0; j<ad->size_of_u;++j){
		for(i=0; i<ad->number_of_u-1; ++i) {
			ad->U[i][j] = ad->U[i+1][j];
			ad->DU[i][j] = ad->DU[i+1][j];
		}
		ad->U[ad->number_of_u-1][j] = u[j];
		ad->DU[ad->number_of_u-1][j] = u[j] - ad->U[ad->number_of_u-2][j];
	}
}
void new_control_increment(ArchiveDataPtr ad, float* du){
	int i,j;
	for(j=0; j<ad->size_of_u;++j){
		for(i=0; i<ad->number_of_u-1; ++i) {
			ad->U[i][j] = ad->U[i+1][j];
			ad->DU[i][j] = ad->DU[i+1][j];
		}
		ad->U[ad->number_of_u-1][j] = ad->U[ad->number_of_u-2][j]+du[j];
		ad->DU[ad->number_of_u-1][j] = du[j];
	}
}
void new_output(ArchiveDataPtr ad, float* y){
	int i, j;
	for(j=0; j<ad->size_of_y; ++j){
		for(i=0; i<ad->number_of_y-1; ++i) 
			ad->Y[i][j] = ad->Y[i+1][j];
		ad->Y[ad->number_of_y-1][j] = y[j];
	}
}
void new_simulated_signal(ArchiveDataPtr ad, float* y){
	#ifdef HARDWARE_SIMULATION 	// if hardware, then we have to overwrite last signal value with new signal value
	int i, j;
	for(j=0; j<ad->size_of_y; ++j)
		ad->Y[ad->number_of_y-1][j] = y[j];
	#else			// if software, then we have to append new signal value
		new_output(ad,y);
	#endif
}
void set_current_control_increment(CurrentControlPtr c,float* du){
	c->du = du;
	c->type = INC;
}
void set_current_control(CurrentControlPtr c,float* u){
	c->u = u;
	c->type = ABS;
}
void push_current_controls_to_archive_data(CurrentControlPtr c,ArchiveDataPtr  ad){
	if(c->type == ABS) 	new_control(ad, c->u);
	else				new_control_increment(ad, c->du);
}
float* last_control(ArchiveDataPtr ad){
	const int k = 0;
	return ad->u[k-1];
}
float* last_control_increment(ArchiveDataPtr ad){
	const int k = 0;
	return ad->du[k-1];
}

