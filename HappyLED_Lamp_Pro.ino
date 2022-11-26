#include "Blynk_Driver.h"
#include "RGB_Driver.h"

Adafruit_NeoPixel LED1(8, D3, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  BLYNK_DRIVER_Init();
  RGB_Init();
  // LED1.begin();
}

void loop() {
  BLYNK_DRIVER_Handle();
  RGB_Handle();
  // for(int i = 0; i < 8; i++){
  //   LED1.setPixelColor(i, LED1.Color(0, 255, 100));
  // }
  // LED1.show();
}
