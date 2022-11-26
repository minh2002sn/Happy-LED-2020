#ifndef SENSOR_DRIVER_H
#define SENSOR_DRIVER_H

#include "Arduino.h"

#define SOUND_SENSOR_PIN            D5      // D5: GPIO14
#define PIR_SENSOR_PIN              D1      // D1: GPIO5

void SENSOR_Init(void (*p_interrupt_function)());
uint8_t SENSOR_Read_PIR_Sensor();

#endif
