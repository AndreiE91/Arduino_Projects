int latchPin = 4;
int clockPin =7;
int dataPin = 8; // SSD pins

const unsigned char ssdlut[] = {0b00111111, 0b00000110,
0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101,
0b00000111, 0b01111111, 0b01101111};
const unsigned char anodelut[] = {0b00000001, 0b00000010,
0b00000100, 0b00001000};
char digits[] = {5,2,3,4}; // The number to be
//displayed is 1234. You can change it.
long tua;
char direction;
int currentNumber;

void showNumber(int number) {
  if(number < 0) {
    number *= -1;
  }
  if(number > 9999) {
    number %= 10000;
  }
  digits[0] = number / 1000;
  number %= 1000;
  digits[1] = number / 100;
  number %= 100;
  digits[2] = number / 10;
  number %= 10;
  digits[3] = number;
}

void setup ()
{
  tua = millis();
  currentNumber = 0;
  direction = 1;
pinMode(latchPin,OUTPUT);
pinMode(clockPin,OUTPUT);
pinMode(dataPin,OUTPUT); // The three pins connected to
// the shift register must be output pins
pinMode(A1,INPUT);
}
void loop()
{
  int pinStateStart = digitalRead(A1);
  int pinStateStop = digitalRead(A2);
  int pinStateClear = digitalRead(A3);

  if(pinStateClear == HIGH) {
    currentNumber = 0;
  }

  if(millis() - tua >= 1) {
    if(direction == 1) {
      currentNumber++;
    } else {
      currentNumber--;
    }
    if(currentNumber > 9999) {
      currentNumber = 0;
    } else if(currentNumber < 0) {
      currentNumber = 9999;
    }
    showNumber(currentNumber);
    tua = millis();
  }
for(char i=0; i<=3; i++) // For each of the 4 digits
{
unsigned char digit = digits[i]; // the current digit
unsigned char cathodes = ~ssdlut[digit]; // The
//cathodes of the current digit, we’ll
//negate the value from the original LUT
digitalWrite(latchPin,LOW); // Activate the latch to
//allow writing
shiftOut(dataPin,clockPin,MSBFIRST, cathodes); //
//shift out the cathode byte
shiftOut(dataPin,clockPin,MSBFIRST, anodelut [i] );
// shift out the anode byte
digitalWrite(latchPin,HIGH); // De-activate the latch
//signal
delay(2); // Short wait
}
}