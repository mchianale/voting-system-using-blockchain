#ifndef EXERCICE5
#define EXERCICE5
typedef struct cellKey {
	Key * data ;
	struct cellKey * next ;
} CellKey ;

typedef struct cellProtected {
	Protected * data ;
	struct cellProtected * next ;
	} CellProtected ;
//5.1
CellKey * create_cell_key(Key*);
//5.2
CellKey * insere_entete(CellKey*, Key*);
//5.3
CellKey * read_public_keys(char *);
//5.4
void print_list_keys(CellKey*);
//5.5
void delete_cell_key(CellKey*);
void delete_list_keys(CellKey*);
//en plus
int len_list_keys(CellKey *);
//6
CellProtected* create_cell_protected(Protected*);
//7
CellProtected* inserer_en_tetekp(CellProtected*, Protected*);
//8
CellProtected* read_protected(char*);
//9
void print_list_protected(CellProtected *);
//10
void delete_cell_protected(CellProtected*);
void delete_list_protected(CellProtected*);
#endif
