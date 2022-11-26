#include "Blynk_Driver.h"
#include "RGB_Driver.h"

#define BLYNK_TEMPLATE_ID       "TMPLLs81LR8n"
#define BLYNK_DEVICE_NAME       "LED Control"
#define BLYNK_AUTH_TOKEN        "JXO0yZjeIfYf0Ldmye7stJU3b8f00Juh"

#define BLYNK_PRINT             Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "DepThiVo";
char pass[] = "daucatmoi";

// BlynkTimer timer;

#define MODE_BUTTON                 V0
#define SAVE_ENERGY_BUTTON          V1
#define SINGLE_COLOR_MODE_BUTTON    V2
#define SINGLE_COLOR_SLIDER         V3
#define DOUBLE_COLOR_MODE_BUTTON    V4
#define LEFT_COLOR_SLIDER           V5
#define RIGHT_COLOR_SLIDER          V6
#define RAINBOW_MODE_BUTTON         V7
#define RAINBOW_SPEED_SLIDER        V8

// Mode button
BLYNK_WRITE(MODE_BUTTON){
  RGB_Data.mode = (param.asInt() == 1) ? CUSTOM_MODE : AUTO_MODE;
  if(RGB_Data.mode == AUTO_MODE){
    Blynk.virtualWrite(SINGLE_COLOR_MODE_BUTTON, 0);
    Blynk.virtualWrite(DOUBLE_COLOR_MODE_BUTTON, 0);
    Blynk.virtualWrite(RAINBOW_MODE_BUTTON, 0);
  } else{
    Blynk.virtualWrite(SINGLE_COLOR_MODE_BUTTON, 1);
    RGB_Data.effect = SINGLE_COLOR_EFFECT;
  }
}

// Save energy mode button
BLYNK_WRITE(SAVE_ENERGY_BUTTON){
  RGB_Data.save_energy_mode = (SAVE_ENERGY_MODE_t)param.asInt();
}

// Single color mode button
BLYNK_WRITE(SINGLE_COLOR_MODE_BUTTON){
  if(RGB_Data.mode == AUTO_MODE){
    Blynk.virtualWrite(SINGLE_COLOR_MODE_BUTTON, 0);
    Blynk.virtualWrite(DOUBLE_COLOR_MODE_BUTTON, 0);
    Blynk.virtualWrite(RAINBOW_MODE_BUTTON, 0);
    RGB_Data.running_state = RGB_OFF_STATE;
    return;
  }
  if(param.asInt()){
    RGB_Data.running_state = RGB_ON_STATE;
    RGB_Data.effect = SINGLE_COLOR_EFFECT;
    Blynk.virtualWrite(DOUBLE_COLOR_MODE_BUTTON, 0);
    Blynk.virtualWrite(RAINBOW_MODE_BUTTON, 0);
  } else{
    RGB_Data.running_state = RGB_OFF_STATE;
  }
}

// Color for single color mode
BLYNK_WRITE(SINGLE_COLOR_SLIDER){
  RGB_Data.single_hsv_color[RGB_Data.mode] = param.asInt();
}

// Double color mode button
BLYNK_WRITE(DOUBLE_COLOR_MODE_BUTTON){
  if(RGB_Data.mode == AUTO_MODE){
    Blynk.virtualWrite(SINGLE_COLOR_MODE_BUTTON, 0);
    Blynk.virtualWrite(DOUBLE_COLOR_MODE_BUTTON, 0);
    Blynk.virtualWrite(RAINBOW_MODE_BUTTON, 0);
    RGB_Data.running_state = RGB_OFF_STATE;
    return;
  }
  if(param.asInt()){
    RGB_Data.running_state = RGB_ON_STATE;
    RGB_Data.effect = DOUBLE_COLOR_EFFECT;
    Blynk.virtualWrite(SINGLE_COLOR_MODE_BUTTON, 0);
    Blynk.virtualWrite(RAINBOW_MODE_BUTTON, 0);
  } else{
    RGB_Data.running_state = RGB_OFF_STATE;
  }
}

// Left color for double color mode
BLYNK_WRITE(LEFT_COLOR_SLIDER){
  RGB_Data.left_hsv_color[RGB_Data.mode] = param.asInt();
}

// Right color for double color mode
BLYNK_WRITE(RIGHT_COLOR_SLIDER){
  RGB_Data.right_hsv_color[RGB_Data.mode] = param.asInt();
}

// Rainbow mode
BLYNK_WRITE(RAINBOW_MODE_BUTTON){
  if(RGB_Data.mode == AUTO_MODE){
    Blynk.virtualWrite(SINGLE_COLOR_MODE_BUTTON, 0);
    Blynk.virtualWrite(DOUBLE_COLOR_MODE_BUTTON, 0);
    Blynk.virtualWrite(RAINBOW_MODE_BUTTON, 0);
    RGB_Data.running_state = RGB_OFF_STATE;
    return;
  }
  if(param.asInt()){
    RGB_Data.running_state = RGB_ON_STATE;
    RGB_Data.effect = RAINBOW_EFFECT;
    Blynk.virtualWrite(SINGLE_COLOR_MODE_BUTTON, 0);
    Blynk.virtualWrite(DOUBLE_COLOR_MODE_BUTTON, 0);
  } else{
    RGB_Data.running_state = RGB_OFF_STATE;
  }
}

// Speed for rainbow mode
BLYNK_WRITE(RAINBOW_SPEED_SLIDER){
  if(RGB_Data.mode == CUSTOM_MODE){
    RGB_Data.rainbow_speed = param.asInt();
  }
}

void BLYNK_DRIVER_Init(){
  Blynk.begin(auth, ssid, pass);
  // timer.setInterval(1000L, myTimerEvent);

  Blynk.virtualWrite(MODE_BUTTON, 0);
  Blynk.virtualWrite(SAVE_ENERGY_BUTTON, 0);
  Blynk.virtualWrite(SINGLE_COLOR_MODE_BUTTON, 0);
  Blynk.virtualWrite(SINGLE_COLOR_SLIDER, 0);
  Blynk.virtualWrite(DOUBLE_COLOR_MODE_BUTTON, 0);
  Blynk.virtualWrite(LEFT_COLOR_SLIDER, 0);
  Blynk.virtualWrite(RIGHT_COLOR_SLIDER, 0);
  Blynk.virtualWrite(RAINBOW_MODE_BUTTON, 0);
  Blynk.virtualWrite(RAINBOW_SPEED_SLIDER, 0);
}

void BLYNK_DRIVER_Handle(){
  Blynk.run();
}
