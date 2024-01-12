#include "exercice1.h"
#include "exercice2.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

long extended_gcd(long s, long t, long *u, long * v) {
	if ( s == 0 ) {
			*u = 0;
			*v = 1;
			return t;
	}
	long uPrim, vPrim;
	long gcd = extended_gcd(t%s, s, &uPrim, &vPrim);
	*u  = vPrim-(t/s)*uPrim;
	*v = uPrim;
	
	return gcd;
}

/* Q.2.1 */


void assert_generate_key_values(long p, long q, long n, long s, long u) {
	long t = (p-1)*(q-1);
	assert( n == p*q);
	assert( (s*u)%t ==1 ); 
	 
}

void generate_key_values(long p, long q, long*n, long *s, long *u) {
	*n = p*q;
	long t = (p-1)*(q-1);
	long v;
	long gcd = 0;
	while(gcd != 1) {
		*s = rand_long(1, t);
		gcd = extended_gcd(*s, t, u, &v);
	}
	if ( *u < 0) {
		*u = *u + t;
	}
	return;	
}

/* Q.2.2 */
long* encrypt(char * chaine, long s, long n) {
	long * tab = (long*)malloc(strlen(chaine)*sizeof(long));
	assert(tab);
	int i = 0;
	int m;
	 
	while(chaine[i] != '\0') {
		m = (int)chaine[i];
		tab[i]= modpow(m, s, n);
		i++;
	}
	return tab;
}

/* Q.2.3 */
char * decrypt(long * crypted, int size, long u, long n) {
	char * chaine  = (char*)malloc(size+1);
	assert(chaine);
	long m;
	for(int i = 0; i < size; i++) {
		m = modpow(crypted[i], u, n);
		chaine[i] = (char)((int)m);
	}
	chaine[size] = '\0';
	return chaine;
}

/* Fonction de test */
void print_long_vector(long *result, int size) {
	printf("Vector: [");
	for(int i=0; i < size; i++) {
		printf("%ld \t", result[i]);
	}
	printf("]\n");
}

		
