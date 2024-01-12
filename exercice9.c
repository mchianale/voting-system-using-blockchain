#include "exercice1.h"
#include "exercice2.h"
#include "exercice3.h"
#include "exercice4.h"
#include "exercice5.h"
#include "exercice6.h"
#include "exercice7.h"
#include "exercice8.h"
#include "exercice9.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <openssl/sha.h>
#include <dirent.h>
//1
void submit_vote(Protected * p) {
	FILE * f = fopen("./Blockchain/Pending_votes.txt", "a");
	assert(f);
	char * vote = protected_to_str(p);
	fprintf(f, "%s\n", vote);
	free(vote);
	fclose(f);
}
//2
void create_block(CellTree * tree, Key * author, int d) {
	//on recupere les votes dans Pending_votes.txt
	CellProtected * votes = read_protected("./Blockchain/Pending_votes.txt");
	//on cree le block
	CellTree * last = last_node(tree); //previous hash
	char * previous = strdup((char*)last->block->hash);
	Block * b = new_block(0, author, "null", previous, votes);
	char * bstr = block_to_str(b);
	unsigned char * bhash = str_to_hash((const char*)bstr);
	b->hash = (unsigned char*)strdup((char*)bhash);
	compute_proof_of_work(b, d);
	//on supprime Pendind_votes
	assert(remove("./Blockchain/Pending_votes.txt")==0);
	//ecriture du block obtenu
	write_block("./Blockchain/Pending_block.txt", b);
	//free
	free(bstr);
	free(b->hash);
	free(b->previous_hash);
	delete_list_protected(b->votes); 
	free(b);	 	
}

//3
void add_block(int d, char * name) {
	Block * b = read_block("./Blockchain/Pending_block.txt");
	if(verify_block(b,d) == 1) {
		char chemin[256] = "\0";
	        strcat(chemin,"./Blockchain/");
	        strcat(chemin, name); 
		write_block(chemin, b);
	}
	//on supprime Pendind_block
	assert(remove("./Blockchain/Pending_block.txt")==0);
	//free
	free(b->hash);
	free(b->previous_hash);
	delete_list_protected(b->votes);
	free(b);
	
}

//4
CellTree * read_tree() {
	//ouverture dossier
	int len_dir = 0;
	DIR * dos = opendir("./Blockchain/");
	assert(dos);
	//nbr de fichiers dans le dossier
	struct dirent * file;
	while((file = readdir(dos))) {
		if(strcmp(file->d_name, ".") != 0 && strcmp(file->d_name, "..") != 0) {
			len_dir++;
		}
	}
	closedir(dos);
	//tableau de noeuds
	CellTree * tab[len_dir];
	assert(tab);
	//creation des block
	DIR * dos2 = opendir("./Blockchain/");
	assert(dos2);
	Block * b = NULL;
	int i = 0;
	char chemin[256]; //name des files 
	while((file = readdir(dos2))) {
			if(strcmp(file->d_name, ".") != 0 && strcmp(file->d_name, "..") != 0) {
			chemin[0] = '\0';
			strcat(chemin, "./Blockchain/");
			strcat(chemin, file->d_name);
			b = read_block(chemin);
			
			if(b!=NULL) {
				tab[i] = create_node(b);
				i++;
			}
			 
		}
	}
	closedir(dos2);
	//si il y eu moins de noeuds construits que prevu on rempli les cases vides par NULL
	for(int j = i; j < len_dir; j++) {
		tab[j] = NULL;
	}
	//add child pour chaque noeud de tab
	for(int pere = 0; pere < len_dir; pere++){
		if(tab[pere]==NULL) {
			break;
		}
		for(int fils = 0; fils < len_dir; fils++) {
			if (strcmp((char*)tab[pere]->block->hash, (char*)tab[fils]->block->previous_hash) == 0) {
				add_child(tab[pere], tab[fils]);
			}
		}
	}
	//recherche racine
	int nb_racine = 0; //on verfie qu'il y a une seule racine
	CellTree * racine = NULL;
	for(int noeud = 0; noeud < len_dir; noeud++){
		if(tab[noeud]==NULL) { 
			break;
		}
		if(tab[noeud]->father == NULL) {
			 racine = tab[noeud];
			 nb_racine++;
		}
	}
	if(nb_racine == 1) {
		return racine;
	}
	return NULL; //pas de racine ou racine non unique  => pas d'arbre
}
			
//5
Key * compute_winner_BT(CellTree * tree, CellKey * candidates, CellKey * voters, int sizeC, int sizeV) {
	//on verifie les conditions 
	assert( sizeC >= len_list_keys(candidates));
	assert( sizeV >= len_list_keys(voters));
	if(tree == NULL) {
		return NULL;
	}
	//on recupere declaration de votes
	CellProtected * decl = get_votes(tree);
	if(decl == NULL) {
		return NULL;
	}
	//on recupere le gagnant
	// la suppression des mauvaises declarations est inclue dans compute_winner
	Key * vainqueur = compute_winner(decl,candidates,voters, sizeC, sizeV);	
	//free (seulement les cellules pas les datas 
	CellProtected * temp;
	while(decl) {
		temp = decl->next;
		free(decl);
		decl = temp;
	}
	return vainqueur;
		
}

 		
			
			
		
	
	
