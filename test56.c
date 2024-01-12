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
 

int main() {
	srand(time(NULL));
	//4
   	generate_random_data(5, 3);
	//liste key citoyen
	printf("liste citoyens :\n");
	CellKey * clv =  read_public_keys("keys.txt");
	print_list_keys(clv);
	
	//liste key candidat
	printf("liste candidats:\n");
	CellKey * cl =  read_public_keys("candidates.txt");
	print_list_keys(cl);
	
	
	CellProtected * cd = read_protected("declarations.txt");
        
	
	cd = delete_protected_novalide(cd);
	printf("liste declarations (apres supression) :\n");
	print_list_protected(cd);
	
	Key * vainqueur = compute_winner(cd, cl, clv, 10, 10);
	assert(vainqueur);
        printf("vainqueur : %s\n", key_to_str(vainqueur));

	delete_list_protected(cd);
 	delete_list_keys(clv);
	delete_list_keys(cl);
}
