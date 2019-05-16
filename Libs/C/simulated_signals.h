#ifndef __SIMULATED_SIGNALS_H__
#define __SIMULATED_SIGNALS_H__
#include <math.h>
#include <stdio.h>
//#include <time.h>
#include <stdlib.h>
#include "./mpctools.h"

void sim_none (ArchiveDataPtr ad);
void sim_sinus(ArchiveDataPtr ad);
void sim_step (ArchiveDataPtr ad);
void sim_const(ArchiveDataPtr ad);
void sim_saw  (ArchiveDataPtr ad);
void sim_rand (ArchiveDataPtr ad);

void sim_test (ArchiveDataPtr ad);

#endif
