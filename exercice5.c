#include "exercice1.h"
#include "exercice2.h"
#include "exercice3.h"
#include "exercice4.h"
#include "exercice5.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
 

//1
CellKey* create_cell_key(Key* key) {
    CellKey* cellk = (CellKey*) malloc (sizeof(CellKey));
    cellk->data = key;
    cellk->next = NULL;
    return cellk;
}

//2
CellKey* insere_entete(CellKey* cellk, Key* key) {
    CellKey* current = create_cell_key(key);
    current->next = cellk;
    return current;
}
//3
CellKey* read_public_keys(char* nomfile) {
    char ligne[256];
    char pKeyL[256];
    char sKeyL[256];
    

    FILE * f= fopen(nomfile, "r");
    assert(f);
    Key* pKey = malloc(sizeof(Key));
    fgets(ligne, 256, f);
    if (sscanf(ligne, "%s %s",pKeyL, sKeyL)<1) {//Initialisation de la liste chainée
	return NULL; 
    }
    pKey = str_to_key(pKeyL);
    CellKey* c = create_cell_key(pKey);

    while(fgets(ligne, 256, f) != NULL) {
         if (sscanf(ligne, "%s %s",pKeyL, sKeyL)<1) { //Initialisation de la liste chainée
	    return c; 
    	}
        pKey = str_to_key(pKeyL);
        c = insere_entete(c, pKey);
    }

    fclose(f);
    return c;
}
//4
void print_list_keys(CellKey* LCK) {
	while(LCK) {
		printf("%s\n", key_to_str(LCK->data));
		LCK = LCK->next;
	}
}
	
//5
void delete_cell_key(CellKey* c) { // suprime element en tete
	free(c->data);
	free(c);
}


void delete_list_keys(CellKey* c) {
	while(c != NULL) {
		CellKey * tmp = c->next;
		delete_cell_key(c);
		c = tmp;
	}
	free(c);
}
//en plus
int len_list_keys(CellKey * c){
	int res = 0;
	while(c) {
		res++;
		c = c->next;
	}
	return res;
}
//6
CellProtected* create_cell_protected(Protected* pr) {
    CellProtected* cp = (CellProtected*) malloc(sizeof(CellProtected*));
    cp->data = pr;
    cp->next = NULL;
    return cp;
}

//7
CellProtected* inserer_en_tetekp(CellProtected* cp, Protected* pr) {
    CellProtected* tmp = create_cell_protected(pr);
    tmp->next = cp;
    return tmp;
}
//8
CellProtected* read_protected(char* nomfile) {
    char ligne[256];
    char messL[256];
    char signL[256];
    char pKeyL[256];

    FILE * f = fopen(nomfile, "r");
    assert(f);
    fgets(ligne, 256, f);
    if (sscanf(ligne, "%s %s %s", pKeyL, messL, signL) < 3) { //Initialisation de la liste chainée
	return NULL; 
    }
    Key * pKey = malloc(sizeof(Key));
    pKey = str_to_key(pKeyL);
    Signature* sign = str_to_signature(signL);
    Protected* pr = init_protected(pKey, messL, sign);
    CellProtected* cp = create_cell_protected(pr);
    while(fgets(ligne, 256, f) != NULL) {
        if (sscanf(ligne, "%s %s %s", pKeyL, messL, signL) < 3) { 
		return cp;
	}
        pKey = str_to_key(pKeyL);
        Signature* sign = str_to_signature(signL);
        Protected* pr = init_protected(pKey, messL, sign);
        cp = inserer_en_tetekp(cp, pr);
    }

    fclose(f);
    return cp;
}
//9 
void print_list_protected(CellProtected * c) {
 
     while(c) {
	printf("%s \n", protected_to_str(c->data));
	c = c->next;
     }
}

//10
void delete_cell_protected(CellProtected* c){
    free(c->data->pKey);
    free(c->data->mess);
    free(c->data->sgn->tab);
    free(c->data->sgn);
    free(c->data);
    free(c);
}

void delete_list_protected(CellProtected* c){
	while(c != NULL) {
		CellProtected * tmp = c->next;
		delete_cell_protected(c);
		c = tmp;
	}
	free(c);
}




