#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "makewav.c"

int length=100;
int delay=400;
int twodelay=200;
long seeed=153;
float two=1.0;

int * delayline;

int main( int argc, char ** argv ) {

	int i,j,k, pad;
	
	twodelay = 2*delay/3;

	srand(seeed);

	delayline = (int *) malloc( delay*sizeof(int) );
	length *= 44100;
	
	for(i=0; i<delay; i++ ) {
		/* delayline[i]=(rand()&65535)-32768; */
		
		j = (int) ( 32767*sin(two*6.28*i/delay) );
		j += (int) ( 3200*sin(3*two*6.28*i/delay) );
		delayline[i] = j;
	}

	wavheader( stdout, length );

	j=0;

	for(i=0; i<length; i++ ) {
		outsample( delayline[j], delayline[j] );
	
		k=j+1; while(k>=delay) k-=delay;
		delayline[j] += delayline[k];
		k=j+1; while(k>=delay) k-=delay;
		delayline[j] += delayline[k];
		k=j+1; while(k>=delay) k-=delay;
		delayline[j] += delayline[k]; 

		delayline[j]  =
		delayline[j]  * 10 / 42;

		pad = 0;
		if( 0 == 1+(rand()&31) )
			pad = (rand()&32768)-16384;
		delayline[j] += pad/6;

		j++; if(j>=delay) j-=delay;
	}

	return 0;
}


