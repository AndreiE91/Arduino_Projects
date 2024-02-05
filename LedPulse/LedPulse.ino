int buzerPin = 8; // pin for attaching the piezoelectric
//speaker
int puls = 0; // duty cycle, initially 0
int step = 10; // duty cycle increment step
int ledPin = 9; // on-board LED
void setup() {
// Pin direction setup
pinMode(buzerPin, OUTPUT);
pinMode(ledPin, OUTPUT);
}
void loop() {
// set the duty cycle for both the buzzer and the LED
analogWrite(buzerPin, puls);
analogWrite(ledPin, puls);
// increment the duty cycle
puls = puls + step;
// change the increment direction at the end of the
//interval
if (puls <= 0 || puls >= 255) {
step = -step ;
}
// small delay to sense the effects
delay(30);
}