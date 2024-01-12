#include <openssl/sha.h>
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
#include "exercice7.h"
// !!!! attention crash pour n >= 7
//programme pour analyser le temps mit par compute_proof_of_work
int main() {
 srand(time(NULL));
  
 int n = 6;
 //creation d'un block (le meme que dans main7)
 CellProtected * votes = read_protected("declarations.txt");
 votes = delete_protected_novalide(votes);
 assert(votes);
 Key * author = votes->data->pKey;
 assert(author);
 unsigned char * hash = str_to_hash("Rosetta code");
 unsigned char * previous_hash = str_to_hash("Previous code");
 Block * b = new_block(0, author, (char*)hash, (char*)previous_hash, votes);
 
 //Analyse
 AnalyseCompute(b, n); // 6 
 
 //free
 delete_block(b);
 free(author);
 printf("AnalyseCompute(b,%d) fait\n", n);
 return 0;
}


//faire graphe
// quand d = 4 le temps depasse 1 s = 2.5 s
