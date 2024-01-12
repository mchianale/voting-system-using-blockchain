#include "exercice1.h"
#include "exercice2.h"
#include "exercice3.h"
#include "exercice4.h"
#include "exercice5.h"
#include "exercice6.h"
#include "exercice7.h"
#include "exercice8.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <openssl/sha.h>

//1
CellTree * create_node(Block * b) {
	CellTree * t = (CellTree*)malloc(sizeof(CellTree));
	assert(t);
	if(b==NULL) { return NULL;}
	t->block = b;
	t->height = 0;
	t->father = NULL;
	t->firstChild = NULL;
	t->nextBro = NULL;
	return t;
}

//2
int update_height(CellTree * father, CellTree * child) {
	 if(father == NULL || child == NULL) {
	 	return 0; //on ne modifie pas height de father
	 }
	 if(child->father != father) {
	 	return 0; //on ne modifie pas height de father
	 }
	 if (father->height < child->height + 1) {
	 	father->height = child->height + 1;
	 	return 1; //height change
	 }
	 return 0; //on ne modifie pas height
}

//3
void add_child(CellTree * father, CellTree * child) {
	//add
	if(father == NULL || child == NULL) {
	 	return ; //aucune modification
	}
	child->father = father;
	CellTree * temp = father->firstChild;
	if(temp == NULL) {
		father->firstChild = child;
	}
	else {
		while(temp->nextBro) {
			temp = temp->nextBro;
		}
		temp->nextBro = child; //le dernier fils de father devient child
	}
	
	//update de height
	CellTree * prec = father;
	CellTree * children = child;
	int b = 1; 
	while(prec && b == 1) { //on s'arrete quand il n'y a plus de modification
		b = update_height(prec, children);
		children = prec;
		prec = prec->father;
	}
}	

//4
void print_tree(CellTree * t) {
	if(t==NULL) { //condition d'arret
		return;
	}
	printf("Noeud de hauteur : %d et id : %s\n", t->height, t->block->hash);
	//recursion
	// d'abord sur les freres de t puis sur ses fils
	print_tree(t->nextBro);
	print_tree(t->firstChild);
}
	
//5
void delete_node(CellTree * node){
	delete_block(node->block);
	free(node);
}

void delete_tree(CellTree * t) {
	if(t) {
		CellTree * TempBro = t->nextBro;
		CellTree * TempChild = t->firstChild;
		delete_node(t);
		delete_tree(TempBro);
		delete_tree(TempChild);
	}
}
//6
CellTree * highest_child(CellTree * cell) {
	if(!cell) {
		return NULL;
	}
	CellTree * TempChild = cell->firstChild;
	CellTree * res = cell->firstChild;
	while(TempChild) {
		if(TempChild->height > res->height) {
			res = TempChild;
		}
		TempChild = TempChild->nextBro;
	}
	return res;
}	
	
//7
CellTree * last_node(CellTree * tree) {
	if(!tree) {
		return NULL;
	}
 	if(tree->firstChild == NULL) {
 		return tree; //on retourne la feuille
 	}
 	else {
 		last_node(highest_child(tree));
 	}
 }
 		
//8
CellProtected * fusion_liste(CellProtected * c1, CellProtected * c2) {
	if(!c1) {
		return c2;
	}
	if(!c2) {
		return c1;
	}
	// on ajoute c2 à la fin de c1
	CellProtected * temp = c1;
	while(temp->next) {
	 	temp = temp->next;
	}
	
	temp->next = c2;
	return c1;
}
//complexite : O(taille de c1) 
// complexite : O(1) si CellProtected est doublement chaine et qu'on a acces au dernier element de la liste en O(1) alors direct
	
//9
CellProtected * get_votes(CellTree * tree){
	if(!tree) {
		return NULL;
	}
	CellTree * depart = last_node(tree);
	CellProtected * votes = NULL;
	while(depart) {
		votes = fusion_liste(votes,depart->block->votes);
		depart = depart->father;
	}
	return votes;
}
	
	
	
	
	
	
	
	
