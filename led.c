/*This program is used to control 4-byte LED light to show time
 							
  						UPO-JZSB 2016/5/21
  a
 ---
b| |c
d---
e| |f
 ---  .h
  g

 0 abcefg 1 cf 2 acdeg 3 acdfg 4 bcdf 5 abdfg 6 abdefg 7 acf 8 abcdefg 9 abcdfg
 */
#include <wiringPi.h>
#include <time.h>
#include <unistd.h>

int n[10][8] ={
	{1,1,1,0,1,1,1,0},
	{0,0,1,0,0,1,0,0},
	{1,0,1,1,1,0,1,0},
	{1,0,1,1,0,1,1,0},
	{0,1,1,1,0,1,0,0},
	{1,1,0,1,0,1,1,0},
	{1,1,0,1,1,1,1,0},
	{1,0,1,0,0,1,0,0},
	{1,1,1,1,1,1,1,0},
	{1,1,1,1,0,1,1,0}
};

void setled(int dest, int * num);

int main(void)
{
	//initialize Raspberry Pi and pins
	wiringPiSetup();

	pinMode(0,OUTPUT);
	pinMode(1,OUTPUT);
	pinMode(2,OUTPUT);
	pinMode(3,OUTPUT);
	pinMode(4,OUTPUT);
	pinMode(5,OUTPUT);
	pinMode(21,OUTPUT);
	pinMode(22,OUTPUT);
	pinMode(23,OUTPUT);
	pinMode(24,OUTPUT);
	pinMode(25,OUTPUT);
	pinMode(26,OUTPUT);

	//get time

	time_t the_time;
	struct tm * tm_ptr;
	
	while(1)
	{
	
	the_time = time((time_t *)0);
	
	tm_ptr = localtime(&the_time);

	//recode time h_1h_2:m_1m:2 hh:mm 
	int h_1, h_2, m_1, m_2;

	h_1 = tm_ptr->tm_hour / 10;
	h_2 = tm_ptr->tm_hour - (tm_ptr->tm_hour / 10) * 10;

	m_1 = tm_ptr->tm_min /10;
	m_2 = tm_ptr->tm_min - (tm_ptr->tm_min / 10) * 10;

	//if them show at the same time, the power is not enough
	setled(1,n[h_1]);
	sleep(1);
	setled(2,n[h_2]);
	sleep(1);
	setled(3,n[m_1]);
	sleep(1);
	setled(4,n[m_2]);
	sleep(1);

	}
}
/*
 (GPIO)
 0      1      2      3      4      5 
 |      |      |      |      |      |
 ||||||.||||||.||||||.||||||.||||||.|
 |      |      |      |      |      |
 21     22     23     24     25     26
 */
void setled(int dest, int * num)
{
	switch(dest)
	{
		case 1:
			digitalWrite(0,LOW);
			digitalWrite(3,HIGH);
			digitalWrite(4,HIGH);
			digitalWrite(26,HIGH);
			break;
		case 2:
			digitalWrite(3,LOW);
			digitalWrite(0,HIGH);
			digitalWrite(4,HIGH);
			digitalWrite(26,HIGH);
			break;
		case 3:
			digitalWrite(4,LOW);
			digitalWrite(0,HIGH);
			digitalWrite(3,HIGH);
			digitalWrite(26,HIGH);
			break;
		case 4:
			digitalWrite(26,LOW);
			digitalWrite(0,HIGH);
			digitalWrite(3,HIGH);
			digitalWrite(4,HIGH);
			break;
	}

	digitalWrite(1,num[0]);
	digitalWrite(2,num[1]);
	digitalWrite(5,num[2]);
	digitalWrite(25,num[3]);
	digitalWrite(21,num[4]);
	digitalWrite(24,num[5]);
	digitalWrite(22,num[6]);
	digitalWrite(23,num[7]);
}
