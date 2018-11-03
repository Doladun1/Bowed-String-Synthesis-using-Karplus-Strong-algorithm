#include<math.h>
#include<stdlib.h>

typedef struct karplus_struct {
	int * string;
	int N;
	int input;
	int j;
	int crossing;
} kstring;

kstring karplus_new( int N, int input ) {
	
	int i;
	kstring K;

	K.N = N;
	K.input = input;
	K.j=0;
	
	K.string = (int *) malloc( N*sizeof(int) );
	
	for( i=0; i<N; i++ ) K.string[i]=0;

	K.crossing=1;
	return K;
}

int karplus_val( kstring *K ) {
	int k;
	k = (K->input) + (K->j);  if(k>=(K->N)) k-=(K->N);
	return K->string[k];
}

int karplus_do( kstring *K, int samp ) {
	int pad, k;

	pad = K->string[K->j];

	k = 1+(K->j); 	if(k>=(K->N)) k-=(K->N);
	pad += K->string[k];
	pad += K->string[k];
	k = 1+(k); 	if(k>=(K->N)) k-=(K->N);
	pad += K->string[k];

        pad = pad * 99/400;

	K->string[K->j] = pad;

	k = (K->input) + (K->j);  if(k>=(K->N)) k-=(K->N);
	K->string[k] += samp;

	K->j = 1+(K->j);  if((K->j)>=(K->N)) K->j -= K->N;

        return pad;
}
