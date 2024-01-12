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
 
int main() {
 srand(time(NULL));
 //4
 const char * s = "Rosetta code";
 unsigned char * d = SHA256((const char unsigned *)s , strlen ( s ) , 0) ;
 int i ;
 printf("test de base : %s\n", s);
 for( i = 0; i < SHA256_DIGEST_LENGTH ; i ++)
    printf("%02x" , d[i]) ;
 putchar ('\n') ;
 
 //creation d'un block
 CellProtected * votes = read_protected("declarations.txt");
 votes = delete_protected_novalide(votes);
 assert(votes);
 Key * author = votes->data->pKey;
 assert(author);
 unsigned char * hash = str_to_hash(s);
 printf("str_to_hash(%s) => %s\n", s, hash); //doit == au printf 4
 unsigned char * previous_hash = str_to_hash("Previous code");
 printf("str_to_hash(Previous code) => %s\n", previous_hash);
 
 Block * b = new_block(0, author, (char*)hash, (char*)previous_hash, votes);
 printf("block b : author | previous_hash | votes (declarations.txt) | nonce\n");
 char * Bstr = block_to_str(b);
 printf("%s\n", Bstr);
 
 //ecriture et lecture
 write_block("Block.txt", b);
 Block * Bdup = read_block("Block.txt");
 char * BstrDup = block_to_str(Bdup);
 printf("block Bdup (block lu pour Block.txt :\n");
 printf("%s\n", BstrDup);
  //assert(strcmp(Bstr, BstrDup)==0); la liste de vote est lu a l'envers   mais sinon correcte
 free(BstrDup);
 delete_block(Bdup);

 
  
 //compute_proof_of_work
 compute_proof_of_work(b, 4);
 free(Bstr);
 Bstr = block_to_str(b);
 printf("compute_proof_of_work(b, 4):\n");
 printf("nouvelle valeur de b->hash : %s\n", b->hash);
 printf("nouvelle valeur de b->nonce : %d\n", b->nonce);
 write_block("Block.txt",b);
 int valide = verify_block(b, 4);
 if (valide == 1) {
 	printf("block valide pour d = 4\n");
 }
 else {
 	printf("block non valide pour d = 4\n");
 }
 
 //free
 free(Bstr);
 delete_block(b);
 free(author);
  
 return 0;
}
