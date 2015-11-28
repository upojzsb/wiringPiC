#include <wiringPi.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

int main(int argc, char * argv[])
{
	//Error handlng

	if( argc != 2 ){
		fprintf(stderr, "Usage: %s sensor\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	short int sensor;

	if( (sensor = atoi(argv[1])) <=0 ){
		fprintf(stderr,"Please input a effective sensor ID\n");
		exit(EXIT_FAILURE);
	}

	if( -1 == wiringPiSetup() ){
		fprintf(stderr,"Cannot initialize GPIO\n");
		exit(EXIT_FAILURE);
	}

	//Set sensor's Pin 

	pinMode(sensor, INPUT);

	struct timeval start, end;

	while(TRUE){
		while( ( LOW == digitalRead(sensor) ))
			;
		while( (HIGH == digitalRead(sensor) ))
			;
		puts("Beginning");
		gettimeofday( &start, NULL);
		while( (LOW == digitalRead(sensor) ))
			;
		puts("End");
		gettimeofday( &end, NULL);

		fprintf(stdout,"%d us\n", (1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec));
	}
}


