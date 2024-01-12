#include "exercice1.h"
#include "exercice2.h"
#include "exercice3.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
//EXERCICE 4
// Q.4.1

int recherche_char(char ** tab, char * elt, int n) {
    for(int i = 0; i < n; i++) {
	if(strcmp(tab[i], elt)==0) {
		return 0; // retourne 0 si la chaine existe deja
	}
    }
    return 1;   // retourne 1 si la chaine n'existe pas 
}
	
void generate_random_data(int nv, int nc) {
	 
	assert(nc<=nv); 
	Key* pKey = (Key*)malloc(sizeof(Key));
	Key* sKey = (Key*)malloc(sizeof(Key));
	
	// citoyen
	FILE * couple = fopen("keys.txt", "w");
	assert(couple);
	
	char * tabV[nv]; //cle prive des citoyens 
	char * tabVP[nv];//cle public des citoyens
	
	for(int i = 0; i < nv; i++) {
		init_pair_keys(pKey, sKey, 3, 7);
		tabV[i] = strdup(key_to_str(sKey));
		tabVP[i] = strdup(key_to_str(pKey));
		fprintf(couple, "%s %s\n", key_to_str(pKey), key_to_str(sKey));
	}
	fclose(couple);
	
	// candidat
	FILE * candidat= fopen("candidates.txt", "w");
	assert(candidat);
	
	char * tabC[nc];//cle public des candidats
	char * tmp;
	int n = 0; // nbr d'element dans tabC
	int r; // valeur aleatoire	
	
	for(int i = 0; i < nc; i++) {
		r = rand()%nv;
		tmp = strdup(tabVP[r]);
		while(recherche_char(tabC, tmp, n)==0) { // empeche les doublons de candidats
			r = rand()%nv;
			tmp = strdup(tabVP[r]);
		}
		tabC[i] = strdup(tmp);
		n++;
		fprintf(candidat, "%s\n",  tmp);	
	}
	fclose(candidat);
	
	
	// declaration de vote
	FILE * declaration = fopen("declarations.txt", "w");
	char * mess;
	 
	Signature* sgn = (Signature*)malloc(sizeof(Signature));
	for(int i = 0; i < nv; i++) {
		r = rand()%nc;
		mess = strdup(tabC[r]);
		sgn = sign(mess, str_to_key(tabV[i]));
		fprintf(declaration, "%s %s %s\n", tabVP[i], mess, signature_to_str(sgn));
	}
	fclose(declaration);
}
