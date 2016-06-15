/*
   This program is used to display something on a lcd
   									By UPO-JZSB
									2016/6/14
*/

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <lcd.h>
#include <unistd.h>

/* Define PINS
   1 VSS;2 VDD;3 V0;4 RS;5 RW;6 E;7 D0;8 D1;9 D2;10 D3;11 D4;12 D5;13 D6;14 D7;15 A;16 K
     GND   +5v   R    21   GND  22  23   24   25    26    27    28    29    6    +5v  GND
*/

#define ROWS 2
#define COLS 16
#define BITS 8
#define RS 21
#define E 22	//Strobe
#define D0 23
#define D1 24
#define D2 25
#define D3 26
#define D4 27
#define D5 28
#define D6 29
#define D7 6

int main(void)
{
	wiringPiSetup();

	int fd;
	fd = lcdInit(ROWS,COLS,BITS,RS,E,D0,D1,D2,D3,D4,D5,D6,D7);

	if(-1 == fd)
	{
		fprintf(stderr,"Initialize lcd fault\n");
		exit(EXIT_FAILURE);
	}

	lcdClear(fd);
	lcdPosition(fd,0,0);

	lcdPuts(fd,"Raspberry Pi");

	lcdPosition(fd,0,1);
	lcdPuts(fd,"     ----UPOJZSB");
//	sleep(3);
}
