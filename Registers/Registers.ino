#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
void setup()
{
// set the ADC clock to 16MHz/128 = 125kHz
ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));
ADMUX |= (1<<REFS0); //Set the ref. voltage to Vcc (5v)
ADCSRA |= (1<<ADEN); //Activate the ADC
ADCSRA |= (1<<ADSC);
}
void loop()
{
int val = read_adc(0); //read the value
lcd.setCursor(0,1);
lcd.print(val);
}
uint16_t read_adc(uint8_t channel)
{
ADMUX &= 0xE0; // delete MUX0-4 bits
ADMUX |= channel&0x07; //Sets in MUX0-2 the value of the
//new channel to be read
ADCSRB = channel&(1<<3); // Set MUX5 value
ADCSRA |= (1<<ADSC); // start conversion
while(ADCSRA & (1<<ADSC)); //Wait for the conversion to
//finish
return ADCW;
}