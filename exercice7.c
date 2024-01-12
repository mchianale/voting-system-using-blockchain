#include "exercice1.h"
#include "exercice2.h"
#include "exercice3.h"
#include "exercice4.h"
#include "exercice5.h"
#include "exercice6.h"
#include "exercice7.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <openssl/sha.h>


//preliminaire
Block * new_block(int nonce, Key * author, char * hash, char * previous_hash, CellProtected * votes) {
	Block * b = (Block*)malloc(sizeof(Block));
	assert(b);
	b->nonce = nonce;
	b->author = author;
	b->votes = votes;
	b->hash = (unsigned char *)hash;
	b->previous_hash = (unsigned char *)previous_hash;
	return b;
}
//1
void write_block(char * nomfile, Block * b){
    FILE * f = fopen(nomfile, "w");
    assert(f);
    char * author = key_to_str(b->author);
    fprintf(f,"%s %s %s %d\n",author,b->hash,b->previous_hash,b->nonce);
    CellProtected * v = b->votes;
    while(v != NULL){
    	char * kstr = key_to_str(v->data->pKey);
        fprintf(f,"%s %s %s\n",kstr,v->data->mess,signature_to_str(v->data->sgn));
        free(kstr);
        v = v->next;
    }
    free(author);
    fclose(f);
}

//2

Block * read_block(char* nomfic){
    FILE * f = fopen(nomfic, "r");
    assert(f);
    char ligne[4092];
    char author[256];
    char hash[256];
    char previous_hash[256];
    int nonce;
    //Initialisation de l'auteur 
    fgets(ligne, 256, f);
    int r = sscanf(ligne,"%s %s %s %d",author,hash,previous_hash,&nonce);
    if (r < 4) {
		return NULL;	
    }
    
    //Initialisation de la cle
    Key * aut = str_to_key(author);
    //Initialisation de la lise
    char messL[256];
    char signL[256];
    char pKeyL[256];
    CellProtected* cp;
    fgets(ligne, 256, f);
    if (sscanf(ligne, "%s %s %s", pKeyL, messL, signL) < 3) { //Initialisation de la liste chainée
	cp = NULL; 
    }
    else {
            Key * pKey = malloc(sizeof(Key));
	    pKey = str_to_key(pKeyL);
	    Signature* sign = str_to_signature(signL);
	    Protected* pr = init_protected(pKey, messL, sign);
	    cp = create_cell_protected(pr);
	    while(fgets(ligne, 256, f) != NULL) {
		if (sscanf(ligne, "%s %s %s", pKeyL, messL, signL) < 3) { 
			break;
		}
		pKey = str_to_key(pKeyL);
		Signature* sign = str_to_signature(signL);
		Protected* pr = init_protected(pKey, messL, sign);
		cp = inserer_en_tetekp(cp, pr);
	    }
    }

    Block * b = (Block*)malloc(sizeof(Block));
    assert(b);
    b->author = aut;
    b->votes = cp;
    b->nonce = nonce;
    b->hash = (unsigned char*) strdup(hash);
    b->previous_hash = (unsigned char *) strdup(previous_hash);
    return b;
}

//3

char* block_to_str(Block* block){
    char buffer[4096];
    buffer[0] = '\0';
    char previous_hash[256];
    sprintf(previous_hash, " %s ", (char*)block->previous_hash);
    char nonce[32];
    sprintf(nonce, "%d", block->nonce);
    char * author = key_to_str(block->author);
    strcat(buffer, author);
    strcat(buffer, previous_hash);
    CellProtected * c = block->votes;
    while(c != NULL){
        char * prot = protected_to_str(c->data);
        strcat(buffer,prot);
	strcat(buffer, " ");
	free(prot);
        c = c->next;
    }
    strcat(buffer, nonce);
    free(author);
    return strdup(buffer); //permet une allocation !
}

//5
unsigned char * str_to_hash(const char * str) {
	unsigned char * d = SHA256((const unsigned char *)str , strlen(str) , 0);
	char * res = (char*)malloc(2*SHA256_DIGEST_LENGTH+1);
	res[0] = '\0';
	//transformation de la chaine => ecriture decimale
	for(int i = 0; i < SHA256_DIGEST_LENGTH; i++){
		sprintf(res,"%s%02x", res, d[i]);
	}
	return (unsigned char *)res;
}

//6

int nb_zero(unsigned char * Hstr) {
	if(Hstr == NULL) {
		return -1; //empeche boucle infinie dans compute_proff_of_work
	}
	int res = 0;
	int i = 0;
	while(Hstr[i]!= '\0') {
		if (Hstr[i] == '0') {
			res++;
			
		}
		else {
			break;
		}
		i++;
	}
	return res;
}
	
	
void compute_proof_of_work(Block * b, int d) {
	assert(b);
	b->nonce = 0;
	char * Bstr = block_to_str(b);
	unsigned char * Hstr = str_to_hash((const char *)Bstr);
	while(nb_zero(Hstr) < d) {
		if (nb_zero(Hstr) == -1) {
			return;
		}
		free(Bstr);
		b->nonce++;
		Bstr = block_to_str(b);
		Hstr = str_to_hash((const char *)Bstr);
	}
	b->hash = Hstr;	
}

//7
int verify_block(Block * b, int d) {
	// un block est valide ssi sa valeur hash possede >= d zeros (en tete)
	if(b == NULL) {
		return 0;
	}
	/*char * Bstr = block_to_str(b);
	 unsigned char * Hstr = str_to_hash((const char *)Bstr);*/
	 
	if ( nb_zero(b->hash) >= d) { return 1; } //hypothese : b->hash est deja str_to_hash((const char *)block_to_str(b))
	/*free(Bstr);*/
	return 0;
}

//8
void AnalyseCompute(Block * b, int n) {
	//on applique la fontion compute_proof_of_work sur b pour d variant de 0 jusqu'a n
	//on mesure le temps mit a chaque fois
	// ecrit dans le fichier AnalyseCompute.txt le temps mit  
	FILE *fichier= fopen("AnalyseCompute.txt","w");
	assert(fichier);
	clock_t temps_initial;
	clock_t temps_final;
	double temps_ecoule;
	srand ( time(NULL) );
	 
	for(int d = 0; d < n; d++) {
		temps_initial=clock();
		compute_proof_of_work(b, d);
		temps_final=clock();
		temps_ecoule = ((double)(temps_final-temps_initial))/CLOCKS_PER_SEC;
		 
		
		fprintf(fichier,"%d %lf\n",d,temps_ecoule);
	}
	fclose(fichier);
}
/*  COMMANDE GNUPLOT
plot "AnalyseCompute.txt" using 1:2 with lines title "Compute_proof_of_work"
*/


//9
void delete_block(Block * b) {
	assert(b);
	free(b->hash);
	free(b->previous_hash);
	CellProtected * temp;
	while(b->votes) {
		temp = b->votes->next;
		free(b->votes);
		b->votes = temp;
	}
	free(b->votes);
	free(b);
}
		


