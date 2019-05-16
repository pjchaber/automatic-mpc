#include <math.h>
#include <stdio.h>
//#include <time.h>
#include <stdlib.h>
#include "./defines.h"
#include "./mpctools.h"

void sim_none(ArchiveDataPtr ad){ // default
}

void sim_test(ArchiveDataPtr ad){
//	static float y = 0;
//	y = 0.9f*y+0.1f*ad->uk1[M(-1)];
//	new_simulated_signal(ad, y);
}

#ifndef M_PI
#define M_PI 3.14f
#endif

#ifndef SIN_PERIOD
#define SIN_PERIOD 150
#endif

#ifndef SIN_AMPLITUDE
#define SIN_AMPLITUDE 2.0
#endif

#ifndef SIN_BIAS
#define SIN_BIAS      -0.5
#endif

void sim_sinus(ArchiveDataPtr ad){
//	static float x = 0.0;
//	static float delta_x = 2*M_PI/SIN_PERIOD;
//	float y = 0.5*(sin(x)+1.0)*SIN_AMPLITUDE+SIN_BIAS;
//	x += delta_x;
//	if(x >= 2*M_PI) x -= 2*M_PI;
//	new_simulated_signal(ad, y);
}

#ifndef CONST_VALUE
#define CONST_VALUE 1.0
#endif

void sim_const(ArchiveDataPtr ad){
//	new_simulated_signal(ad, CONST_VALUE);
}

#ifndef STEP_DELAY
#define STEP_DELAY 10
#endif

#ifndef STEP_LOW
#define STEP_LOW 1.0
#endif

#ifndef STEP_HIGH
#define STEP_HIGH 5.0
#endif
void sim_step(ArchiveDataPtr ad){
//	static long time = 0;
//	if(time >= STEP_DELAY){
//		new_simulated_signal(ad, STEP_HIGH);
//	} else {
//		++time; // increments until reaches STEP_DELAY
//		new_simulated_signal(ad, STEP_LOW);
//	}
}

#ifndef SAW_UPTIME
#define SAW_UPTIME 10
#endif

#ifndef SAW_DOWNTIME
#define SAW_DOWNTIME 15
#endif

#ifndef SAW_AMPLITUDE
#define SAW_AMPLITUDE 1.0f
#endif

#ifndef SAW_BIAS
#define SAW_BIAS -0.5f
#endif

#ifndef SAW_FIRSTUP
#define SAW_FIRSTUP 1
#endif

#ifndef SAW_TIMESTART
#define SAW_TIMESTART 8
#endif
void sim_saw(ArchiveDataPtr ad){
//	static long time = SAW_TIMESTART;
//	static int up = SAW_FIRSTUP;
//	float y = 0;

//	if(up)	y = (((float)time)/SAW_UPTIME)*SAW_AMPLITUDE+SAW_BIAS;
//	else	y = SAW_AMPLITUDE - (((float)time)/SAW_DOWNTIME)*SAW_AMPLITUDE+SAW_BIAS;

//	++time;
//	if(up == 1 && time >= SAW_UPTIME  ){ up = 0; time = 0; } 
//	if(up == 0 && time >= SAW_DOWNTIME){ up = 1; time = 0; } 
//	new_simulated_signal(ad, y);
}

#ifndef RAND_AMPLITUDE
#define RAND_AMPLITUDE 2.0f
#endif

#ifndef RAND_BIAS
#define RAND_BIAS -0.5f
#endif

#ifndef RAND_SEED
#define RAND_SEED 0 
#endif

void sim_rand(ArchiveDataPtr ad){
//	static float init = 0;
//	if(init == 0){
//		srand((unsigned int)RAND_SEED);	
//		init = 1;
//	}
//	new_simulated_signal(ad, ((float)rand()/(float)(RAND_MAX)) * RAND_AMPLITUDE + RAND_BIAS);
}
