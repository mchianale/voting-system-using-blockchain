#ifndef EXERCICE3
#define EXERCICE3

/* 3.1 */
typedef struct key {
	long x;
	long n;
} Key;

typedef struct signature {
	int taille;
	long * tab;
} Signature;

/* 3.9 */
typedef struct protected {
	Key * pKey;
	char * mess;
	Signature * sgn;
} Protected;

/* 3.2 */
void init_key(Key*, long, long);
/* 3.3 */
void init_pair_keys(Key* , Key* , long , long );
/* 3.4 */
char * key_to_str(Key*);
Key * str_to_key(char * );
/* Q.3.6 */
Signature* init_signature(long*, int);
/* 3.7 */
Signature* sign(char*, Key*);
/* 3.8 */
char * signature_to_str(Signature *);
Signature * str_to_signature ( char *);
/* 3.10 */
Protected * init_protected(Key*, char*, Signature*);
/* 3.11 */
int verify(Protected*);
/* 3.12 */
char * protected_to_str(Protected*);
Protected * str_to_protected(char*);

#endif 

