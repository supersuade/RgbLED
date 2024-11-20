/* Light House */
#include "RgbLED.h"
/*
 *
 * Light House Code
 * Something quick and dirty for controlling a light house.
 * The base and teh tower.
 * Cycle, Pause, and White
 */                               

 //teensy 3.0
 //top LED RBG: 5,6,9
 //bottomLED: 20,21,22
RgbLED topLED(5,6,9,100,255);
RgbLED bottomLED(20,21,22,30,255);

int counter = 0;
void setup(){
  Serial.begin(9600);
  Serial.println("Hello.");
  topLED.setWhite();
  bottomLED.setWhite();
  bottomLED.setPulseSpeed(20);
  delay(1000);
  Serial.println("Beginning Color Shifting");
}
void loop(){
  topLED.updateLED();
  bottomLED.updateLED();
  delay(1);
}
