#include <stdlib.h>
#include <stdio.h>
#include "./default_functions.h"
#include "./defines.h"
#include "./mpctools.h"
#include "./simulated_signals.h"

#ifdef VERBOSE
	#define WRITE_FUN __write_string((char*)__func__)
#else
	#define WRITE_FUN 
#endif

extern ArchiveData ad;
extern CurrentControl cc;

void write_string(char * str) { printf("DBG: %s\n",str); }

long get_time(void)               { WRITE_FUN; return 0; }
void hardware_setup(void)         { WRITE_FUN; }
void controller_setup(void)       { WRITE_FUN; }
void sim_setup(void)              { WRITE_FUN; }
void measurements(void)           { WRITE_FUN; }
void loop(void)                   { WRITE_FUN; }
void controls(void)               { WRITE_FUN; }
void idle(void)                   { WRITE_FUN; }
void timeout(void)                { WRITE_FUN; while(1); /*exit(1);*/ }

#ifdef SIMULATION
void sim_measurements(void)  { WRITE_FUN; SIMULATE_FUNCTION(&ad); }
void sim_controls(void)      { WRITE_FUN; push_current_controls_to_archive_data(&cc,&ad); }
#else
void sim_measurements(void)  { WRITE_FUN; }
void sim_controls(void)      { WRITE_FUN; }
#endif


void __write_string(char * str)     { write_string(str); }
long __get_time(void)               { return get_time(); }
void __hardware_setup(void)         { hardware_setup(); }
void __controller_setup(void)       { controller_setup(); }
void __sim_setup(void)              { sim_setup(); }
void __measurements(void)           { measurements(); }
void __loop(void)                   { loop(); }
void __controls(void)               { controls(); }
void __idle(void)                   { idle(); }
void __timeout(void)                { timeout(); }
void __sim_measurements(void)       { sim_measurements(); }
void __sim_controls(void)           { sim_controls(); }


