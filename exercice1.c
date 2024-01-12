#include "exercice1.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
 
/* EXERCICE 1 */

/* Q1 */
int is_prime_naive(long p){
	if (p == 2) {
		return 1;
	}
	for(int i = 3; i < p; i++) {
		if (p%i == 0) {
			return 0;
		}
	}
	return 1;
}
/* complexite :  O(p) */

/* Q3 */
long modpow_naive(long a, long m, long n) {
	assert(n!=0);
	long res = 1;
	for(int i = 0; i < m; i++) {
		res*=a;
	}
	return res%n;
}	
/* complexite :  O(m) */

/* Q4 */
long modpow(long a, long m, long n) {
	long p;
  
	for (p = 1; m > 0; m = m/ 2) {
		if (m % 2 != 0){
			p = (p * a) % n;
		}
		a = (a * a) % n;
	}
  return p;
}
	
/* complexite :  ?? */

/* Q5 COMMANDE GNUPLOT
plot "AnalyseModPow.txt" using 1:2 with lines title "modpow naive"
replot "AnalyseModPow.txt" using 1:3 with lines title "modpow"
*/
void AnalyseModPow(int a) {
	/* ecrit dans le fichier AnalyseModPow.txt le temps mis 
	par la fct modpow_naive et modpow pour la valeur a avec differente valeurs m et n */
	FILE *fichier= fopen("AnalyseModPow.txt","w");
	assert(fichier);
	clock_t temps_initial;
	clock_t temps_final;
	double temps_ecoule_naive;
	double temps_ecoule;
	srand ( time(NULL) );
	int random;
	 
	for(int i = 1000; i <= 10000; i+=1000) {
		temps_initial=clock();
		for(long j=0;j<i;j++){
			random = rand() % 10 + 1; /* entier entre 1 et 10, on evite le zero */
			modpow_naive(a, j, random);
		}
		temps_final=clock();
		temps_ecoule_naive = ((double)(temps_final-temps_initial))/CLOCKS_PER_SEC;
		
		temps_initial=clock();
		for(long j=0;j<i;j++){
			random = rand() % 10 + 1;
			modpow(a, j, random);
		}
		temps_final=clock();
		temps_ecoule = ((double)(temps_final-temps_initial))/CLOCKS_PER_SEC;
		
		fprintf(fichier,"%d %lf %lf\n",i,temps_ecoule_naive,temps_ecoule);
	}
	fclose(fichier);
}

/* Q6 
-int witness(long a, long b, long d, long p) qui teste si a est un t´emoin de Miller pour
p, pour un entier a donn´e.
-long rand long(long low, long up) qui retourne un entier long g´en´er´e al´eatoirement entre
low et up inclus.
-int_is_prime_miller(long p, int k) qui r´ealise le test de Miller-Rabin en g´en´erant k valeurs
de a au hasard, et en testant si chaque valeur de a est un t´emoin de Miller pour p. La fonction
retourne 0 d`es qu’un t´emoin de Miller est trouv´e (p n’est pas premier), et retourne 1 si aucun
t´emoin de Miller n’a ´et´e trouv´e (p est probablement premier).*/

int witness(long a, long b, long d, long p) {
	long x = modpow(a, d, p);
	if(x==1){
		return 0;
	}
	for(long i = 0; i < b; i++) {
		if(x == p-1) {
			return 0;
		}
		x  = modpow(x, 2, p);
	}
	return 1;
}

long rand_long(long low, long up) {
	return rand() % (up - low + 1)+low;
}

int is_prime_miller(long p, int k) {
	if(p == 2){
		return 1;
	}
	if((p%2==0)|| p <= 1) {
		return 0;
	}
	long b = 0;
	long d = p-1;
	while(!(d & 1)){
		d = d/2;
		b=b+1;
	}
	long a;
	int i;
	for(i = 0; i < k; i++) {
		a = rand_long(2, p-1);
		if(witness(a,b,d,p)){
			return 0;
		}
	}
	return 1;
}

/* Q8 */	
long ipow(long b, long e){
  if (e==0) {
    return 1;
  } 
  else if (b==0) {
    return 0;
  } 
  else if (e%2==0) {
    long tmp=ipow(b,e/2);
    return tmp*tmp;
  } 
  else {
    long tmp=ipow(b,(e-1)/2);
    return b*tmp*tmp;
  }
}

long random_prime_number(int low_size, int up_size, int k) {
	if ((low_size == 0)&&(up_size == 0)) { return -1; } /* up = 1 et low = 1 => rand_long(1, 1) tjr egal à 1 => boucle infinie */
	assert(low_size <= up_size);
	assert(low_size <= 31);
	assert(up_size <= 31);
	long low =  ipow(2, low_size-1); // plus petit entier a low_size bits, 2^(low_size-1)
	
	long up = ipow(2, up_size)-1; // plus grand entier a up_size bits : 2^(up_size)-1*/
	int b = 0;
	long res;
	while(b == 0) {
		res = rand_long(low, up);
		b = is_prime_miller(res, k);
	}
	return res;
}
	
