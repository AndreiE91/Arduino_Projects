//include LCD library
#include <LiquidCrystal.h>
String inputString = "";// create an empty string to hold the
//incoming serial data
// Boolean flag to test whether a complete string has been
//received (enter pressed in serial monitor)
boolean stringComplete = false;
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
void setup() {
// initialize serial interface
Serial.begin(9600); // implicit serial frame format
//initialize lcd
lcd.begin(16, 2);
// reserve 200 bytes for the string
inputString.reserve(200);
}
void loop() {
// display the string when new line is received
if (stringComplete) {
lcd.setCursor(0, 0);
lcd.clear();
lcd.print(inputString);
Serial.println(inputString);
// empty the string
inputString = "";
// reset the flag
stringComplete = false;
}
}
/*
SerialEvent is called when new data is received on the RX port
This function is automatically called when the loop is called.
If we add delays in loop we will also delay the showing of the
result. */
void serialEvent() {
while (Serial.available()) {
// read the new received byte
char inChar = (char)Serial.read();
// check if new line character has been received; if
//not, add it to the string
// we do not add new line in input string since it
//will show an extra character in the LCD
if (inChar != '\n')
inputString += inChar;
// dif the receive character is new line, set the flag
//so that the loop will know to display
//the received data
if (inChar == '\n') {
stringComplete = true;
}
}
}