#include <LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2);
volatile int buttonVariable;
bool isRunning = false;
byte clock0[8] = {
B00100,
B00100,
B00100,
B00100,
B00000,
B00000,
B00000,
};
byte clock1[8] = {
B00001,
B00010,
B00010,
B00100,
B00000,
B00000,
B00000,
};
byte clock2[8] = {
B00000,
B00000,
B00000,
B00111,
B00000,
B00000,
B00000,
};
byte clock3[8] = {
B00000,
B00000,
B00000,
B00100,
B00010,
B00010,
B00001,
};
byte clock4[8] = {
B00000,
B00000,
B00000,
B00100,
B00100,
B00100,
B00100,
};
byte clock5[8] = {
B00000,
B00000,
B00000,
B00100,
B01000,
B01000,
B10000,
};
byte clock6[8] = {
B00000,
B00000,
B00000,
B11100,
B00000,
B00000,
B00000,
};
byte clock7[8] = {
B10000,
B01000,
B01000,
B00100,
B00000,
B00000,
B00000,
};
void setup()
{
buttonVariable = 0;
lcd.begin(16,2);
lcd.print("Timer Animation");
lcd.setCursor(0,1);
delay(1000);
lcd.print("Press START");
delay(1000);
// The 2 interrupt pins 21 and 20 declared as inputs with
//pull-up resistors activated
pinMode(20 ,INPUT);
pinMode(21 ,INPUT);
digitalWrite(20, HIGH);
digitalWrite(21, HIGH);
// Atach ISRs to the interrupts corresponding to pins 21
//and 20 (INT0 and INT1)
attachInterrupt(digitalPinToInterrupt(20), functieUnu,
RISING);
attachInterrupt(digitalPinToInterrupt(21), functieDoi,
CHANGE);
}
void loop()
{
  lcd.clear();
  lcd.createChar(0, clock0);
  lcd.setCursor(0, 0);
  lcd.write(byte(0));
  delay(200);
  lcd.clear();
  lcd.createChar(0, clock1);
  lcd.setCursor(0, 0);
  lcd.write(byte(0));
  delay(200);
  lcd.clear();
  lcd.createChar(0, clock2);
  lcd.setCursor(0, 0);
  lcd.write(byte(0));
  delay(200);
  lcd.clear();
  lcd.createChar(0, clock3);
  lcd.setCursor(0, 0);
  lcd.write(byte(0));
  delay(200);
  lcd.clear();
  lcd.createChar(0, clock4);
  lcd.setCursor(0, 0);
  lcd.write(byte(0));
  delay(200);
  lcd.clear();
  lcd.createChar(0, clock5);
  lcd.setCursor(0, 0);
  lcd.write(byte(0));
  delay(200);
  lcd.clear();
  lcd.createChar(0, clock6);
  lcd.setCursor(0, 0);
  lcd.write(byte(0));
  delay(200);
  lcd.clear();
  lcd.createChar(0, clock7);
  lcd.setCursor(0, 0);
  lcd.write(byte(0));
  delay(200);
}
// First ISR function
void functieUnu()
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Functia Unu");
}
// 2-nd ISR function
void functieDoi()
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Functia Doi");
}