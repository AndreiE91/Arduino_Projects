LiquidCrystal(7,6,5,4,3,2);
bool receiveComplete = false;

String inputString = "";
bool sendComplete = false;
char x;

void setup() {
	Wire.begin(9);
	lcd.begin(16,2);
	Serial.begin(9600);
}

void loop(){
	if(sendComplete) {
		sendComplete = false;
		Wire.begin(9);
	}
	if(receiveComplete) {
		Serial.println(inputString);
		receiveComplete = false;
	}
}

void receiveEvent(int bytes) {
	inputString = "";
	x = Wire.read();
	inputString += x;
	if(x == '\n') {
		receiveComplete = true;
	}
}

void serialEvent(){
	Wire.begin();
	while(Serial.available()) {
		char inChar = (char)Serial.read();
		if(inChar != '\n') {
			Wire.beginTransmission(9);
			Wire.write(inChar);
			Wire.endTransmission();
		}
		if(inChar == '\n') {
			Wire.beginTransmission(9);
			Wire.write(inChar);
			Wire.endTransmission();
			sendComplete = true;
		}
	}
}
	