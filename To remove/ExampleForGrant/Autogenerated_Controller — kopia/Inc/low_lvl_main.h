#include "stm32f7xx_hal.h"

void low_lvl_main(void);

float * __measureOutput(void);
void __setControlValue(float* value);
void write_string(char * txt);
void emergency_write_string(void);
void __startListening(UART_HandleTypeDef *huart);
float __getSlaveControlValue(UART_HandleTypeDef *huart);
void __sendMasterControlValue(UART_HandleTypeDef *huart, float value);
