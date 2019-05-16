#include "/home/juzio/Playground/C++/Kompilator_skrosny/Libs/C/defines.h"
#include "/home/juzio/Playground/C++/Kompilator_skrosny/Libs/C/profiler.h"
#include "/home/juzio/Playground/C++/Kompilator_skrosny/Libs/C/mpctools.h"
#include "/home/juzio/Playground/C++/Kompilator_skrosny/Libs/C/simulated_signals.h"
#include "/home/juzio/Playground/C++/Kompilator_skrosny/Libs/C/default_functions.h"
#include <stdio.h>

ArchiveData ad;

void write_str(char * str){
    printf("%s\n",str);
}

void idle(){
    printf("%ld %ld\n",sizeof(ad), sizeof(cc));
}
