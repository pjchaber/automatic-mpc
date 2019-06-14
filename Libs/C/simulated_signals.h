/*
 * This file is part of AutoMATiC.
 * AutoMATiC -- Automatic code generation based on the MATLAB and 
 * C languages.
 * 
 * Copytight (C) 2018-2019 by Patryk Chaber. Developed within the 
 * Warsaw University of Technology, Institute of Control and 
 * Computation Engineering under supervision of Maciej Lawrynczuk. 
 * All rights reserved.
 * 
 * AutoMATiC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * AutoMATiC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with AutoMATiC.  If not, see <https://www.gnu.org/licenses/>.
 */

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
