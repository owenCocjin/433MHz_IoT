//Simulates a jamming attack by spamming the frequency with noise
#include <SoftwareSerial.h>
unsigned char hc12tx=6;
unsigned char hc12rx=5;
unsigned char hc12set=13;
unsigned long counter=0;
unsigned char r;  //Holds the random byte to send
char buff[63];

SoftwareSerial HC12(hc12tx, hc12rx);

void setup(){
	randomSeed(analogRead(0));
	pinMode(hc12set, OUTPUT);
	HC12.begin(9600);
	Serial.begin(9600);
	Serial.println("Starting jamming attack! Press enter to begin...");
	while(Serial.available()==0);
	digitalWrite(hc12set, HIGH);
}//setup()

void loop(){
	r=random(255);
	// r=0xff;
	HC12.write(r);
	counter++;
	if(r<0xff){
		Serial.print(" 0x0");
	}//if()
	else{
		Serial.print(" 0x");
	}//else
	Serial.print(r, HEX);
	if(counter%8==0){
		Serial.println();
	}//if()
}//loop()
