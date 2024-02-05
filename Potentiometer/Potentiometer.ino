#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
void setup()
{
analogReference(DEFAULT); //set the reference voltage to the
//default value (optional)
lcd.begin(16, 2); //init. LCD
lcd.setCursor(0,0);
lcd.print("Read sensor");
pinMode(A1, INPUT); // Set pin A1 as input (make sure that it
//was not set as output)
}
void loop()
{
int val = analogRead(A1); //reading the analog value
lcd.setCursor(0,1);
lcd.print(val);
}