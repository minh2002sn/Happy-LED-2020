#include "RGB_Driver.h"
#include "Sensor_Driver.h"

#define RUNNING_TIME                60000
#define MIN_WAITING_TIME            5

Adafruit_NeoPixel NeoPixel(NUMBER_OF_PIXEL, LED_PIN, NEO_RGB + NEO_KHZ800);
RGB_DATA_t RGB_Data = {RGB_ON_STATE, AUTO_MODE, SAVE_ENERGY_OFF, SINGLE_COLOR_EFFECT, &NeoPixel, 0, 0, 0, 0, 0, 0, 0};

IRAM_ATTR void SENSOR_Auto_Change_Effect(){
  static uint32_t timer = 0;
  if((millis() - timer >= MIN_WAITING_TIME) && (RGB_Data.mode == AUTO_MODE)){
    RGB_Data.effect = (RGB_EFFECT_t)(millis() % 3);                 // random from 0 to 2
    RGB_Data.left_hsv_color[RGB_Data.mode] = random(0xFFFF);       // random from 0 to 2^16 - 1
    RGB_Data.right_hsv_color[RGB_Data.mode] = random(0xFFFF);      // random from 0 to 2^16 - 1
    RGB_Data.single_hsv_color[RGB_Data.mode] = RGB_Data.left_hsv_color[RGB_Data.mode];
    timer = millis();
  }
}

void RGB_Init(){
  SENSOR_Init(SENSOR_Auto_Change_Effect);
  RGB_Data.NeoPixel->begin();
  RGB_Data.NeoPixel->clear();
  RGB_Data.NeoPixel->show();
}

void RGB_Handle(){
  // if(RGB_Data.save_energy_mode == SAVE_ENERGY_ON){
  //   if(SENSOR_Read_PIR_Sensor()){
  //     RGB_Data.running_timer = millis();
  //   }

  //   if(millis() - RGB_Data.running_timer > RUNNING_TIME){
  //     RGB_Data.running_state = RGB_OFF_STATE;
  //   } else{
  //     RGB_Data.running_state = RGB_ON_STATE;
  //   }
  // } else{
  //   RGB_Data.running_state = RGB_ON_STATE;
  // }

  if(RGB_Data.running_state == RGB_ON_STATE){
    switch(RGB_Data.effect){
      case SINGLE_COLOR_EFFECT:
        for(int i = 0; i < NUMBER_OF_PIXEL; i++){
          RGB_Data.NeoPixel->setPixelColor(i, RGB_Data.NeoPixel->ColorHSV(RGB_Data.single_hsv_color[RGB_Data.mode]));
        }
        // if(RGB_Data.single_color[RGB_Data.mode] > 510){
        //   for(int i = 0; i < NUMBER_OF_PIXEL; i++){
        //     RGB_Data.NeoPixel->setPixelColor(i, RGB_Data.NeoPixel->Color(RGB_Data.single_color[RGB_Data.mode] - 510, 0, 255));
        //   }
        // } else if(RGB_Data.single_color[RGB_Data.mode] > 255){
        //   for(int i = 0; i < NUMBER_OF_PIXEL; i++){
        //     RGB_Data.NeoPixel->setPixelColor(i, RGB_Data.NeoPixel->Color(0, 510 - RGB_Data.single_color[RGB_Data.mode], RGB_Data.single_color[RGB_Data.mode] - 255));
        //   }
        // } else{
        //   for(int i = 0; i < NUMBER_OF_PIXEL; i++){
        //     RGB_Data.NeoPixel->setPixelColor(i, RGB_Data.NeoPixel->Color(255 - RGB_Data.single_color[RGB_Data.mode], RGB_Data.single_color[RGB_Data.mode], 0));
        //   }
        // }
        break;
      case DOUBLE_COLOR_EFFECT:
        for(int i = 0; i < NUMBER_OF_PIXEL/2; i++){
          RGB_Data.NeoPixel->setPixelColor(i, RGB_Data.NeoPixel->ColorHSV(RGB_Data.left_hsv_color[RGB_Data.mode]));
        }
        for(int i = 0; i < NUMBER_OF_PIXEL/2; i++){
          RGB_Data.NeoPixel->setPixelColor(i + 4, RGB_Data.NeoPixel->ColorHSV(RGB_Data.right_hsv_color[RGB_Data.mode]));
        }

        // if(RGB_Data.left_color[RGB_Data.mode] > 510){
        //   for(int i = 0; i < NUMBER_OF_PIXEL / 2; i++){
        //     RGB_Data.NeoPixel->setPixelColor(i, RGB_Data.NeoPixel->Color(RGB_Data.left_color[RGB_Data.mode] - 510, 0, 255));
        //   }
        // } else if(RGB_Data.left_color[RGB_Data.mode] > 255){
        //   for(int i = 0; i < NUMBER_OF_PIXEL / 2; i++){
        //     RGB_Data.NeoPixel->setPixelColor(i, RGB_Data.NeoPixel->Color(0, 510 - RGB_Data.left_color[RGB_Data.mode], RGB_Data.left_color[RGB_Data.mode] - 255));
        //   }
        // } else{
        //   for(int i = 0; i < NUMBER_OF_PIXEL / 2; i++){
        //     RGB_Data.NeoPixel->setPixelColor(i, RGB_Data.NeoPixel->Color(255 - RGB_Data.left_color[RGB_Data.mode], RGB_Data.left_color[RGB_Data.mode], 0));
        //   }
        // }

        // if(RGB_Data.right_color[RGB_Data.mode] > 510){
        //   for(int i = 0; i < NUMBER_OF_PIXEL / 2; i++){
        //     RGB_Data.NeoPixel->setPixelColor(i + 4, RGB_Data.NeoPixel->Color(RGB_Data.right_color[RGB_Data.mode] - 510, 0, 255));
        //   }
        // } else if(RGB_Data.right_color[RGB_Data.mode] > 255){
        //   for(int i = 0; i < NUMBER_OF_PIXEL / 2; i++){
        //     RGB_Data.NeoPixel->setPixelColor(i + 4, RGB_Data.NeoPixel->Color(0, 510 - RGB_Data.right_color[RGB_Data.mode], RGB_Data.right_color[RGB_Data.mode] - 255));
        //   }
        // } else{
        //   for(int i = 0; i < NUMBER_OF_PIXEL / 2; i++){
        //     RGB_Data.NeoPixel->setPixelColor(i + 4, RGB_Data.NeoPixel->Color(255 - RGB_Data.right_color[RGB_Data.mode], RGB_Data.right_color[RGB_Data.mode], 0));
        //   }
        // }
        break;
      case RAINBOW_EFFECT:
        if(millis() - RGB_Data.rainbow_timer > 100 - RGB_Data.rainbow_speed){
          for(int i = 0; i < NUMBER_OF_PIXEL; i++){
            int t_pixelHue = RGB_Data.firstPixelHue + (i * 65536L / NUMBER_OF_PIXEL);
            RGB_Data.NeoPixel->setPixelColor(i, RGB_Data.NeoPixel->gamma32(RGB_Data.NeoPixel->ColorHSV(t_pixelHue)));
          }
          if(RGB_Data.firstPixelHue < 3 * 65536)
            RGB_Data.firstPixelHue += 256;
          else
            RGB_Data.firstPixelHue = 0;
          RGB_Data.rainbow_timer = millis();
        }
        break;
      default:
        break;
    }
  } else{
    RGB_Data.NeoPixel->clear();
  }
  RGB_Data.NeoPixel->show();
}