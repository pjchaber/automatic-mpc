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
