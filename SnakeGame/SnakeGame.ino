#include "SevSeg.h"

SevSeg sevseg;

byte numDigits = 4;
byte digitPins[] = {10, 11, 12, 13};
byte segmentPins[] = {9, 2, 3, 5, 6, 8, 7, 4};
bool resistorsOnSegments = true;
byte hardwareConfig = COMMON_CATHODE;
unsigned long period = 300000;
unsigned long timer = 0;
bool snek = false;
int buzzer = 1; //pin for buzzer

void setup() {
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);
}

void loop() {
  ++timer;
  if(timer >= period) {
    timer = 0;
      if(!snek) {
        sevseg.setChars("PLAY");
        snek = true;
      } else {
        sevseg.setChars("SNEK");
        snek = false;
      }
  }
  sevseg.refreshDisplay();
}
