#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "makewav.c"
#include "delayline.c"
#include "karplus.c"

int main( int argc, char ** argv ) {

	double RMS = 0.0;
	int i,k,kk, bowL, bowR, pad, xa, xb, xc;
	int Hz, Bw, Mag, mask;
	float trythis;
	int seeed=153, length=441000;
	filter F, G, H, K, L;
	kstring S;
	int impulseflag=1;

	srand(seeed);

	Hz = atoi(argv[1]);
	Bw = atoi(argv[2]);
	Mag = atoi(argv[3]);
	trythis = atof(argv[4]);

	mask = 1<<Mag;

	S = karplus_new( Hz, Hz/3 );

        F = filter_new( 44100, 261, Bw );
        G = filter_new( 44100, 392, Bw );
        H = filter_new( 44100, 440, Bw );
        K = filter_new( 44100, 523, Bw );
        L = filter_new( 44100, 659, Bw );

	wavheader( stdout, length );

	for(i=0; i<length; i++ ) {

		pad =0;

		if( (1&(i/64000))==0 ) {
			
			if( karplus_val(&S) < 0 ) 
				impulseflag=0;
			else {
				if( impulseflag==0 ) impulseflag=1;
			}

			if( impulseflag==1 ) {
                		pad = rand()&(mask-1);
                		if( pad>(mask/2) ) pad -= mask;
	
				impulseflag=-1;
			}
		} 

                kk  = (int) filter_do( &F, (double) pad );
                kk += (int) filter_do( &G, (double) pad );
                kk += (int) filter_do( &H, (double) pad );
                kk += (int) filter_do( &K, (double) pad );
                kk += (int) filter_do( &L, (double) pad );

		pad = kk;

		pad = karplus_do( &S, pad );

		pad *= trythis;

		RMS += (double)pad*pad;

		outsample( pad, pad );

	}

	fprintf( stderr, "RMS = %f\n", sqrt(RMS/length) );

	return 0;
}
