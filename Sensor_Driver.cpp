#include "Sensor_Driver.h"

void SENSOR_Init(void (*p_interrupt_function)()){
  pinMode(SOUND_SENSOR_PIN, INPUT);
  pinMode(PIR_SENSOR_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(SOUND_SENSOR_PIN), p_interrupt_function, RISING);
}

uint8_t SENSOR_Read_PIR_Sensor(){
  return digitalRead(SOUND_SENSOR_PIN);
}
