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

#ifndef __DEFAULT_FUNCTIONS_H__
#define __DEFAULT_FUNCTIONS_H__

#include "./mpctools.h"

void __attribute__((weak)) write_string(char * str);
long __attribute__((weak)) get_time(void);
void __attribute__((weak)) hardware_setup(void);
void __attribute__((weak)) controller_setup(void);
void __attribute__((weak)) sim_setup(void);
void __attribute__((weak)) measurements(void);
void __attribute__((weak)) loop(void);
void __attribute__((weak)) controls(void);
void __attribute__((weak)) idle(void);
void __attribute__((weak)) timeout(void);
void __attribute__((weak)) sim_measurements(void);
void __attribute__((weak)) sim_controls(void);

void __write_string(char * str);
long __get_time(void);
void __hardware_setup(void);
void __controller_setup(void);
void __sim_setup(void);
void __measurements(void);
void __loop(void);
void __controls(void);
void __idle(void);
void __timeout(void);
void __sim_measurements(void);
void __sim_controls(void);

#endif
