#ifndef EXERCICE6
#define EXERCICE6

typedef struct hashcell{
    Key * key ;
    int val ;
}HashCell;

typedef struct hashtable {
    HashCell ** tab;
    int size;
}HashTable;

//1
CellProtected *  delete_protected_novalide(CellProtected*);
//2
HashCell* create_hashcell(Key*);
//3
int hash_function(Key*, int);
//4
int find_position(HashTable*, Key*);
//5
HashTable* create_hashtable(CellKey*, int);
//6
void delete_hashtable(HashTable*);
//7
int compare(Key*, Key*);
int is_in_Hastable(HashTable*,Key *, int *);
void vote(HashTable* H, Key * key);
Key * compute_winner(CellProtected*, CellKey*,CellKey*, int, int);


#endif
