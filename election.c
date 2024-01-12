#include <openssl/sha.h>
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
#include <dirent.h>

int main() {
	//generation data et listes des candidats, des voters et declarations
	srand(time(NULL));
	int sizeC = 3;
	int sizeV = 1000;
   	generate_random_data(sizeV, sizeC);
	//liste key citoyen
	printf("liste citoyens :\n");
	CellKey * clv =  read_public_keys("keys.txt");
	print_list_keys(clv);
	
	//liste key candidat
	printf("liste candidats:\n");
	CellKey * cl =  read_public_keys("candidates.txt");
	print_list_keys(cl);
	
	//declarations
	CellProtected * cd = read_protected("declarations.txt");
	printf("liste declarations:\n");
	print_list_protected(cd);
	
	
	//creation d'un premier block
	Key * author = cd->data->pKey; //10 par 10
	int pas = 0; 
	int d = 3; //!! d < 7
	char file[256];
	int id_file = 0;
	
	//block racine b
	Block * b =  new_block(0, author, "null", (char*)str_to_hash("Rossetta code"), NULL); 
	//le premier block n'a pas de declaration, il est seulement la pour pouvoir ensuite creer des valeurs de hash
	char * bstr = block_to_str(b);
	unsigned char * bhash = str_to_hash((const char *)bstr);
	b->hash = (unsigned char*)strdup((char*)bhash);
	compute_proof_of_work(b, d);
	 
	CellTree * tree = create_node(b);
	//creations des blocks
	while(cd) {
		author = cd->data->pKey;
		while(cd && pas < 10) {	//10 votes par block
			submit_vote(cd->data); //ecriture dans Pending_votes
			pas++; 
			cd = cd->next;
		}
		create_block(tree, author, d);
		sprintf(file,"Block%d.txt", id_file);
		add_block(d, file);
		//on change le bloc de l'arbre a noeud 
		sprintf(file, "./Blockchain/Block%d.txt", id_file);
		Block * b = read_block(file);
		tree = create_node(b);
		id_file++;
		pas = 0;
	}
	
	//creation arbre
	//tree
	CellTree * arbre = read_tree();
	printf("arbre election final :\n");
	print_tree(arbre);
	//vainqueur
	Key * vainqueur = compute_winner_BT(arbre, cl, clv, sizeC+5, sizeV+5);
	assert(vainqueur);
	char * v = key_to_str(vainqueur);
        printf("vainqueur : %s\n",v );
        //free
        free(v);
        free(vainqueur);
        delete_list_protected(cd);
 	delete_list_keys(clv);
	delete_list_keys(cl);	
	 
	return 0;
}
