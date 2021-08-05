// Notes:
//  - Most data (ip/mac addrs, etc...) are all hardcoded for PoC
//  - Im p sure the checksum algos are very wrong!
//  - To change to/from trigger mode, there are 4 lines to edit, all surrounded by /* Trigger mode */
#include <SoftwareSerial.h>
int RED=10;
int GREEN=11;
int BLUE=9;
const int FRAME_LEN=14;
const int PACKET_LEN=20;
const int SEGMENT_LEN=45;
unsigned char fullLen[2]={0x00,FRAME_LEN+PACKET_LEN+SEGMENT_LEN};
unsigned char hc12tx=3;
unsigned char hc12rx=2;
unsigned char hc12set=6;
/* Trigger mode */
// unsigned char motion_sense=17;
/* Trigger mode */
unsigned char carry;

SoftwareSerial HC12(hc12tx, hc12rx);
unsigned long calcChecksum(unsigned char arr[], int length);

unsigned char eth_frame[FRAME_LEN]={0xff,0xff,0xff,0xff,0xff,0xff,  //dst
0x48,0x45,0x20,0xa4,0xf9,0x43,  //src (Cracker)
// 0x98,0x22,0xef,0xbf,0x64,0xb1,  //src (My laptop)
0x08,0x00};  //IPv4
unsigned char ip_packet[PACKET_LEN]={0x45,  //version/ihl
0x00,  //tos/ecn
0x00,0x00,  //length of ip header+upper
0xc0,0x0c,  //id
0x00,0x00,  //flags/fragment offset
0x40,  //ttl
0x01,  //protocol
0x00,0x00,  //ip checksum [10:11]
// 0x0a,0x00,0x00,0xfe,  //src ip (IoT IP)
0xc0,0xa8,0x01,0x14,  //src ip (IoT IP:192.168.1.20)
0xff,0xff,0xff,0xff};  //dst ip
unsigned char icmp_segment[SEGMENT_LEN]={0x08,  //type (echo message)
0x00,  //code,
0x00,0x00,  //checksum,
0x00,0x00,  //id
0x00,0x00,  //seq
0x5b,0x41,0x4c,0x45,0x52,0x54,0x5d,0x3a,0x20,0x4d,0x6f,0x74,0x69,0x6f,0x6e,0x20,0x64,0x65,0x74,0x65,0x63,0x74,0x69,0x6f,0x6e,0x20,0x74,0x72,0x69,0x67,0x67,0x65,0x72,0x65,0x64,0x21,0x0a};  //Payload

void setup(){
	pinMode(RED, OUTPUT);
	pinMode(GREEN, OUTPUT);
	pinMode(BLUE, OUTPUT);
/* Trigger mode */
	// pinMode(motion_sense, INPUT);
/* Trigger mode */
	digitalWrite(RED, HIGH);
	digitalWrite(GREEN, LOW);
	digitalWrite(BLUE, LOW);
	Serial.begin(9600);
	HC12.begin(9600);
}//setup()

void loop(){
	/* Trigger mode */
	// if(digitalRead(motion_sense)==HIGH){
	/* 1/1 mode */
	delay(1000);
	if(1==1){
	/* Constant ping mode */
	// if (1==1){
		digitalWrite(RED, LOW);
		digitalWrite(GREEN, HIGH);
		digitalWrite(BLUE, HIGH);
		// Serial.println("Motion! Writing...");
		//Zero out checksum fields
		ip_packet[10]=0x00;
		ip_packet[11]=0x00;
		icmp_segment[2]=0x00;
		icmp_segment[3]=0x00;
		//Set IP length (hardcoded)
		ip_packet[3]=PACKET_LEN+SEGMENT_LEN;
		//Calculate ICMP & IPv4 checksum
		// Serial.println("IP Checksum:");
		unsigned short ip_check=calcChecksum(ip_packet, PACKET_LEN);
		// Serial.println("ICMP Checksum:");
		unsigned short icmp_check=calcChecksum(icmp_segment, SEGMENT_LEN);
		//Assign the calculated checksums
		ip_packet[10]=ip_check>>8;
		ip_packet[11]=ip_check&0x00ff;
		icmp_segment[2]=icmp_check>>8;
		icmp_segment[3]=icmp_check&0x00ff;
		//Send the data
		HC12.write(fullLen, 2);
		HC12.write(eth_frame, FRAME_LEN);
		HC12.write(ip_packet, PACKET_LEN);
		HC12.write(icmp_segment, SEGMENT_LEN);
		//Increment ICMP identifier
		icmp_segment[5]++;
		digitalWrite(BLUE, LOW);
/* Trigger mode */
		// while(digitalRead(motion_sense)==HIGH);
/* Trigger mode */
		digitalWrite(GREEN, LOW);
		digitalWrite(RED, HIGH);
	}//if()
}//loop()

unsigned long calcChecksum(unsigned char arr[], int length){
	/*Calculates checksum of entire array.
Assumes appropriate fields are already zeroed out (checksum fields)*/
	unsigned long sum=0x0000;
	unsigned short cur_dword;
	//Iterate every 2 bytes
	for(int i=0;i<(length/2);++i){
		cur_dword=(arr[i*2]<<8)+arr[i*2+1];
		sum+=cur_dword;
	}//for()
	if(length%2==1){
		sum+=arr[length-1]<<8;
	}//if()
	if(sum>0xffff){
		carry=sum>>16;
		sum=sum&0xffff;
		sum+=carry;
	}//if()
	return sum^0xffff;
}//calcChecksum()
