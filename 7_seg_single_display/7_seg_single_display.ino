#include "SevSeg.h"

SevSeg sevseg;


byte numDigits = 1;
byte digitPins[] = {};
byte segmentPins[] = {6, 5, 2, 3, 4, 7, 8, 9};
bool resistorsOnSegments = true;
byte hardwareConfig = COMMON_ANODE;
int displayDelay = 750;
int buzzer = 1; //pin for buzzer
int buzzerStep = 150;

void setup() {
    sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
}

void loop() {
  for(int i = 0; i < 10; ++i) {
  displayDelay = analogRead(A1);
  delay(1);
  tone(buzzer, buzzerStep * i);
  sevseg.setNumber(i);
  sevseg.refreshDisplay();
  delay(displayDelay);
  }
  for(int i = 0; i < 6; ++i) {
    switch(i) {
      case 0: {
        displayDelay = analogRead(A0);
        delay(1);
        tone(buzzer, buzzerStep * 10 + buzzerStep * i);
        sevseg.setChars("a");
        sevseg.refreshDisplay();
        delay(displayDelay);
        break;
      }
      case 1: {
        displayDelay = analogRead(A0);
        delay(1);
        tone(buzzer, buzzerStep * 10 + buzzerStep * i);
        sevseg.setChars("b");
        sevseg.refreshDisplay();
        delay(displayDelay);
        break;
      }
      case 2: {
        displayDelay = analogRead(A0);
        delay(1);
        tone(buzzer, buzzerStep * 10 + buzzerStep * i);
        sevseg.setChars("c");
        sevseg.refreshDisplay();
        delay(displayDelay);
        break;
      }
      case 3: {
        displayDelay = analogRead(A0);
        delay(1);
        tone(buzzer, buzzerStep * 10 + buzzerStep * i);
        sevseg.setChars("d");
        sevseg.refreshDisplay();
        delay(displayDelay);
        break;
      }
      case 4: {
        displayDelay = analogRead(A0);
        delay(1);
        tone(buzzer, buzzerStep * 10 + buzzerStep * i);
        sevseg.setChars("e");
        sevseg.refreshDisplay();
        delay(displayDelay);
        break;
      }
      case 5: {
        displayDelay = analogRead(A0);
        delay(1);
        tone(buzzer, buzzerStep * 10 + buzzerStep * i);
        sevseg.setChars("f");
        sevseg.refreshDisplay();
        delay(displayDelay);
        break;
      }
    }
  }
}
