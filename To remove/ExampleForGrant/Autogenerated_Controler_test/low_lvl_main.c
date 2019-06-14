#include <string.h>
#include <stdio.h>
#include "low_lvl_main.h"
float adc_val_f[2] = {0,0};

float* __measureOutput(){	
  // TODO
	return adc_val_f;
}
void __setControlValue(float* value){ // we assume that this part is known at the design time
  // TODO
}

void write_string(char * txt){
	printf(txt);
}
