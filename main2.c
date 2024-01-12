#include "exercice2.h"
#include "exercice1.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include <math.h>
int main() {
	srand ( time(NULL) );
	long p = random_prime_number(3, 7, 5000);
	long q = random_prime_number(3, 7, 5000);
	while(p==q) {
		q = random_prime_number(3, 7, 5000);
	}
	printf("p : %ld, q : %ld\n", p, q);
	long n, s, u;
	generate_key_values(p, q, &n, &s, &u);
	while(u==s) {
		generate_key_values(p, q, &n, &s, &u);
	}
		
	printf("cle publique = (%ld, %ld) \n", s, n);
	printf("cle privee = (%ld, %ld) \n", u, n);
	assert_generate_key_values(p, q, n, s, u);
	
	char message[1000] = "Hello";
	int len = strlen(message);
	
	// chiffrement
	long * crypted = encrypt(message, s, n);
	printf("Initial message %s \n", message);
	printf("Encoded representation : \n");
	print_long_vector(crypted, len);
	
	// dechiffrement
	char * decoded = decrypt(crypted, len, u, n);
	printf("Decoded %s \n", decoded);
	return 0;
}

 