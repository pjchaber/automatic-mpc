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

#ifndef __PROFILER_H__
#define __PROFILER_H__
typedef struct ProfilerEntry ProfilerEntry;

struct ProfilerEntry {
	unsigned char id;
	unsigned long time_start;
	unsigned long time_stop;
	unsigned long time_min;
	unsigned long time_max;
	unsigned long time_total;
	unsigned int  entries;
	unsigned int  running;
	char * name;
	ProfilerEntry * next;
};

typedef struct Profiler Profiler;
struct Profiler {
	ProfilerEntry * first;
};

void profiler_print(void);
Profiler * get_profiler(void);
ProfilerEntry * find_profiler_entry(unsigned char id);
ProfilerEntry * add_new_profiler_entry(unsigned char id, char * name);
void profiler_start(unsigned char id, char * name);
void profiler_count(unsigned char id, char * name);
void profiler_end(unsigned char id);	
int profiler_exists(void);

#endif
