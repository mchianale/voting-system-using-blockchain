#include "exercice1.h"
#include "exercice2.h"
#include "exercice3.h"
#include "exercice4.h"
#include "exercice5.h"
#include "exercice6.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <math.h>

//1

CellProtected *delete_protected_novalide(CellProtected *list){
    CellProtected *prec;
    CellProtected *cour;
    CellProtected *tmp;
    if (verify(list->data) ==0){
        tmp=list;
        list=list->next;
        delete_cell_protected(tmp);
        return delete_protected_novalide(list);
    }
    prec=list;
    cour=list->next;
    while (cour!=NULL){
        if (verify(cour->data)==0){
            tmp=cour;
            cour=cour->next;
            prec->next=cour;
            delete_cell_protected(tmp);
        } 
	else {
            prec=prec->next;
            cour=cour->next;

        }
    }
    return list;
}
//2

HashCell* create_hashcell(Key* key){
    HashCell* h =(HashCell*)malloc(sizeof(HashCell));
    assert(h);
    h->key = key;
    h->val = 0;
    return h;
}


//3

 int hash_function(Key* key, int size){
     return (key->x + key->n)%size;
 }

//4

int find_position(HashTable* t, Key* key){
     for(int i = 0; i < t->size; i++){
             if((t->tab[i] != NULL) && (t->tab[i]->key == key)){
                 return i;
             }
     }
     return hash_function(key,t->size); //Position de la cle key attendue
 }

//5
HashTable* create_hashtable(CellKey* keys, int size){
    HashTable* t = (HashTable*)malloc(sizeof(HashTable));
    assert(t);
    t->size = size;
    t->tab =(HashCell**)malloc(sizeof(HashCell*)*size);
    assert(t->tab);
    // tab NULL 
    for(int j = 0; j < t->size; j++) {
	t->tab[j] = NULL;
    }

    int pos;
    while(keys != NULL){
	pos = hash_function(keys->data,t->size);
        if (t->tab[pos] != NULL) {
		for(int i = pos; i < t->size; i++) { //probing lineaire
			if ( t->tab[i % (t->size)] == NULL) {	
				t->tab[i % (t->size)] = create_hashcell(keys->data);
				break;
			}
		}
	}
	else {
		t->tab[pos] = create_hashcell(keys->data);	
	}
        keys = keys->next;
    }
    return t;
}

//6
void delete_hashtable(HashTable * t){
     int i;
     for(i = 0;i < t->size;i++){
        free(t->tab[i]);
     }
     free(t->tab);
     free(t);
 }

//7

int compare(Key * key1, Key * key2)  {
	if(key1->x == key2->x && key1->n == key2->n){
		return 1;
	}
	return 0;
}

int is_in_Hastable(HashTable* H,Key * key, int * val){
    assert(H);
    int pos = hash_function(key,H->size);
    if((H->tab[pos] != NULL) && compare(H->tab[pos]->key,key)==1 ){
	*val = H->tab[pos]->val;
	return 1;
    }
    for(int i = pos ; i <= H->size ; i++){
        if((H->tab[i%(H->size)] != NULL) && compare(H->tab[i%(H->size)]->key,key)==1 ){
            *val = H->tab[i%(H->size)]->val; // on recupere en passant la valeur de la cellule cherchée
            return 1;
        }
    }
    *val = -1;
    return 0;
}

void vote(HashTable* H, Key * key) {
    assert(H);
    int pos = hash_function(key,H->size);
    if((H->tab[pos] != NULL) && compare(H->tab[pos]->key,key)==1 ){
	H->tab[pos]->val++;
	return;
    }
    for(int i = pos ; i <= H->size ; i++){
          if((H->tab[i%(H->size)] != NULL) && compare(H->tab[i%(H->size)]->key,key)==1 ){
             H->tab[i%(H->size)]->val++;
        }
    }
}

Key * compute_winner(CellProtected* decl, CellKey* candidates,CellKey* voters, int sizeC, int sizeV){
    
    HashTable* Hc = create_hashtable(candidates,sizeC);
    HashTable* Hv = create_hashtable(voters,sizeV); 
    decl = delete_protected_novalide(decl); // on supprime les mauvaises declarations
     
    int temp_val = 0;
    int temp_vote = 0;
    int max = 0;
    Key * vainqueur = NULL;
    while( decl != NULL){
        Key * voter = decl->data->pKey;
        Key * candidat = str_to_key(decl->data->mess);  

        //On verfife que la personne est bien sur la liste electorale et On verifie que la personne vote bien pour un candidat
	if( is_in_Hastable(Hc, candidat, &temp_vote) == 1 && is_in_Hastable(Hv, voter, &temp_val) == 1 ) {
        	//On verifie que la personne n'a pas deja vote 
		if (temp_val == 0) {
			vote(Hc, candidat);
			vote(Hv, voter);
			 
			if( temp_vote + 1 > max) {
				max = temp_vote + 1;
				vainqueur = candidat;
			}
		}
	}
	//free(candidat);
        decl = decl->next;
    }
    delete_hashtable(Hc);
    delete_hashtable(Hv);
    return vainqueur;
}
 


