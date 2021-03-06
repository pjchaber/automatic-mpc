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

#ifndef __MPCTOOLS_H__
#define __MPCTOOLS_H__

#ifndef MIN
	#define MIN(x,y) ((x)<(y)?(x):(y))
#endif

#ifndef ABS
	#define ABS(x) ((x)<0?(-(x)):(x))
#endif

#ifndef M
	#define M(x) ((x)-1)
#endif

typedef struct {
	// raw data
	float **    U; // będę tutaj trzymał wartości: ...,  u[k-2],  u[k-1]
	float **   DU; // będę tutaj trzymał wartości: ..., du[k-2], du[k-1]
	float **    Y; // będę tutaj trzymał wartości: ...,  y[k-2],  y[k-1],  y[k]
	float *  YZAD;
	
	// helpful pointers
	float **  u; //  u[k] - wskaźnik na element za ostatnim
	float ** du; // du[k] - wskaźnik na element za ostatnim
	float **  y; //  y[k] - wskaźnik na ostatni element
	float *   z;

	long k; // just for giggles
	
	// information about dimensionality
	long number_of_u;
	long number_of_y;
	long size_of_u; // tutaj będzie informacja o wymiarowości problemu
	long size_of_y; // tutaj będzie informacja o wymiarowości problemu
} ArchiveData, *ArchiveDataPtr;

typedef enum {ABS, INC} CCType;

typedef struct {
	CCType type;
	long size_of_u;
	float* u;
	float* du;
} CurrentControl, *CurrentControlPtr;

void init_archive_data(ArchiveDataPtr ad, long number_of_u, long number_of_y, long size_of_u, long size_of_y, float default_u, float default_y, float current_yzad);
void init_current_control(CurrentControlPtr cc, ArchiveDataPtr ad);
void new_control(ArchiveDataPtr ad, float* u);
void new_control_increment(ArchiveDataPtr ad, float* du);
void new_output(ArchiveDataPtr ad, float* y);
void new_simulated_signal(ArchiveDataPtr ad, float* y);
void set_current_control_increment(CurrentControlPtr c,float* du);                 // void setCurrentControlIncrement(CurrentControlPtr c,float* du);
void set_current_control(CurrentControlPtr c,float* u);                            // void setCurrentControl(CurrentControlPtr c,float* u);
void push_current_controls_to_archive_data(CurrentControlPtr c,ArchiveDataPtr ad); // void pushCurrentControlsToArchiveData(CurrentControlPtr c,ArchiveDataPtr ad);
float* last_control(ArchiveDataPtr ad);
float* last_control_increment(ArchiveDataPtr ad);

#endif
