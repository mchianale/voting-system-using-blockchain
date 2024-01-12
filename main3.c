#include "exercice1.h"
#include "exercice2.h"
#include "exercice3.h"
#include "exercice4.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <math.h>

int main(void){

    srand(time(NULL));
    //Testing Init Keys
    Key* pKey = (Key*)malloc(sizeof(Key));
    Key* sKey = (Key*)malloc(sizeof(Key));
    init_pair_keys(pKey, sKey, 3, 7);
    printf("pKey: %lx , %lx \n", pKey->x, pKey->n);
    printf("sKey: %lx , %lx \n", sKey->x, sKey->n);

    
    //Testing Key Serialization
    char* chaine = key_to_str(pKey);
    printf("key to str : %s\n", chaine);

    Key* k = str_to_key(chaine);
    printf("str to key : %lx , %lx \n", k->x, k->n);
    printf("\n");
    //Testing signature
    //Candidate keys:
    Key* pKeyC = malloc(sizeof(Key));
    Key* sKeyC = malloc(sizeof(Key));
    init_pair_keys(pKeyC, sKeyC,3,7);
    //Declaration:
    char* mess = key_to_str(pKeyC);
    printf("%s vote pour %s\n",key_to_str(pKey), mess);
    printf("\n");
    Signature* sgn = sign(mess, sKey);
    printf("signature : ");
    print_long_vector(sgn->tab,sgn->taille);
    chaine = signature_to_str(sgn);
    printf("signature to str : %s \n", chaine);
    sgn = str_to_signature(chaine);
    printf("str to signature : ");
    print_long_vector(sgn->tab,sgn->taille);

    
    //Testing protected:
    Protected* pr = init_protected(pKey,mess,sgn);
    //Verification:
    if (verify(pr) != 0){
        printf("Signature valide\n");
    }else{
        printf("Signature non valide\n");
    }
    chaine = protected_to_str(pr);
    printf("protected to str : %s\n", chaine);
    pr = str_to_protected(chaine);
    printf("str to protected : %s %s %s\n",key_to_str(pr->pKey),pr->mess, signature_to_str(pr->sgn));
	
   
	
    free(pKey);
    free(sKey);
    free(pKeyC);
    free(sKeyC);
    free(chaine);
    return 0;
}
