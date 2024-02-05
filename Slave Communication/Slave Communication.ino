
#include <LiquidCrystal.h>
// include I2C library
#include <Wire.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
bool stringComplete = false;

String inputString = "";
bool strComplete = false;
char x;

void setup() 
{
  // Open I2C bus as slave
  Wire.begin(9);
  lcd.begin(16,2);
  lcd.print("Master");
  Serial.begin(9600);
}
void loop() 
{
  if (stringComplete) 
  {
    // reset the flag
    stringComplete = false;
    Wire.begin(9);
  }
  if (strComplete)
  {
    Serial.println(inputString);
    strComplete = false;
  }
}

void receiveEvent(int bytes) 
{
  inputString = "";
  while(Wire.available()) 
  {
    x = Wire.read(); //read I2C received character
    inputString += x;
    if (x == '\n') 
    {
      strComplete = true;
    }
  }
}

void serialEvent() 
{
  Wire.begin();
  while (Serial.available()) 
  {
    // read the new received byte
    char inChar = (char)Serial.read();
    // check if new line character has been received; if not, add it to the string
    // we do not add new line in input string since it will show an extra character in the LCD
    if (inChar != '\n')
    {
      Wire.beginTransmission(9);
      Wire.write(inChar);
      Wire.endTransmission();
    }
    // dif the receive character is new line, set the flag so that the loop will know to display the received data
    if (inChar == '\n') 
    {    
      Wire.beginTransmission(9);
      Wire.write(inChar);
      Wire.endTransmission();
      stringComplete = true;
    }
  }
}