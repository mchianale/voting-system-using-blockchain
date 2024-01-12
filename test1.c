#include "exercice1.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <math.h>

int main() {
	srand ( time(NULL) );
	/* Q1 */
	assert(is_prime_naive(7) == 1);
	assert(is_prime_naive(9) == 0);
	
	/* Q2 */
	clock_t temps_initial;
	clock_t temps_final;
	double temps_ecoule = 0.0;
	int i = 3;
	int tmp;
	int res;
	
	temps_initial=clock();
	while(temps_ecoule < 20000.0) {
		tmp = is_prime_naive(i);
		temps_final+=clock();
		temps_ecoule = ((double)(temps_final-temps_initial))/CLOCKS_PER_SEC;
		if(tmp == 1) {
			res = i;
		}
		i += 2;
	}
	printf("derniere valeur retournait par is_prime_naive apres environ 2s: %d\n", res);
	/* potentiel resulat : 99623, 99527 */
	
	/* Q3 */
	assert(modpow_naive(2, 9, 9)==8);
	assert(modpow(2, 9, 9)==8);
	/*assert(mod_test(2, 9, 9)==8);*/
	
	/* Q5 */
	AnalyseModPow(132589);
	
	/* Q8 */
	int low_size;
	int up_size;
	int k;
	/* PROBLEME la boucle s'arrete avant */
	for(int i = 0; i < 100; i++) {
		up_size = rand()%7+1; /* doit etre <= 7 et >= 1*/
		low_size = rand()%up_size + 1; /* low_size <= up_size */
		k = rand()%10 + 1;
		printf("random_prime_number(%d,%d,%d) = %ld\n", low_size, up_size, k, random_prime_number(low_size, up_size, k));
	}
		
	return 0;
}