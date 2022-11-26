#ifndef RGB_DRIVER_H
#define RGB_DRIVER_H

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

#define NUMBER_OF_PIXEL           8
#define LED_PIN                   D2      // D2: GPIO4

typedef enum{
  RGB_OFF_STATE,
  RGB_ON_STATE,
} RGB_RUNNING_STATE_t;

typedef enum{
  AUTO_MODE,
  CUSTOM_MODE,
} MODE_t;

typedef enum{
  SAVE_ENERGY_OFF,
  SAVE_ENERGY_ON,
} SAVE_ENERGY_MODE_t;

typedef enum{
  SINGLE_COLOR_EFFECT,
  DOUBLE_COLOR_EFFECT,
  RAINBOW_EFFECT,
} RGB_EFFECT_t;

typedef struct{
  RGB_RUNNING_STATE_t running_state;
  MODE_t mode;
  SAVE_ENERGY_MODE_t save_energy_mode;
  RGB_EFFECT_t effect;
  Adafruit_NeoPixel *NeoPixel;

  uint16_t single_hsv_color[2];
  uint16_t left_hsv_color[2];
  uint16_t right_hsv_color[2];

  uint8_t rainbow_speed;
  uint32_t firstPixelHue;
  uint32_t rainbow_timer;

  uint8_t running_timer;
} RGB_DATA_t;

extern RGB_DATA_t RGB_Data;

void RGB_Init();
void RGB_Handle();

#endif
