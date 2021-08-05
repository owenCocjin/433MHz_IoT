#include <SoftwareSerial.h>
int RED=10;
int GREEN=11;
int BLUE=9;
unsigned char hc12tx=3;
unsigned char hc12rx=2;
unsigned char hc12set=6;
unsigned short length;
unsigned char buff;

SoftwareSerial HC12(hc12tx, hc12rx);

void printHex(unsigned char b);

void setup(){
	pinMode(RED, OUTPUT);
	pinMode(GREEN, OUTPUT);
	pinMode(BLUE, OUTPUT);
	digitalWrite(RED, HIGH);
	digitalWrite(GREEN, LOW);
	digitalWrite(BLUE, LOW);
	Serial.begin(9600);
	HC12.begin(9600);
}//setup()

void loop(){
	if(HC12.available()>1){
		digitalWrite(BLUE, HIGH);
		length=HC12.read();
		length<<=8;
		length+=HC12.read();
		Serial.write(length>>8);
		Serial.write(length&0x00ff);
		for(int i=1;i<=length;++i){
			if(HC12.available()){
				Serial.write(HC12.read());
			}//if()
			else{
				--i;
			}//else
		}//for()
		digitalWrite(BLUE, LOW);
	}//if()
}//loop()

void printHex(unsigned char b){
	if(b<0x10){
		Serial.print("0x0");
	}//if()
	else{
		Serial.print("0x");
	}//else
	Serial.print(b, HEX);
}//printHex()
