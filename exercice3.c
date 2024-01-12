#include "exercice1.h"
#include "exercice2.h"
#include "exercice3.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
 

/* Q.3.2 */
void init_key(Key* key, long val, long n){
	key->x = val;
	key->n = n;
}

/* Q.3.3 */
void init_pair_keys(Key* pKey, Key* sKey, long low_size, long up_size) {
	long p = random_prime_number(low_size, up_size, 5000);
	long q = random_prime_number(low_size, up_size, 5000);
	while(p==q) {
		q = random_prime_number(low_size, up_size, 5000);
	}
	long n, s, u;
	generate_key_values(p, q, &n, &s, &u);
	init_key(pKey, s, n);
	init_key(sKey, u, n);
}
	
/* Q.3.4 */
char * key_to_str(Key * key){
	char * str = (char*)malloc(256*sizeof(char));
	assert(str);
	sprintf(str, "(%lx,%lx)", key->x, key->n);
	return str;
}

Key * str_to_key(char* str){
	long x;
	long n;
	sscanf(str, "(%lx,%lx)", &x, &n);
	Key * key = (Key*)malloc(sizeof(Key));
	assert(key);
	init_key(key, x, n);
	return key;
}

/* Q.3.6 */
Signature* init_signature(long* content, int size){
	Signature * s = (Signature*)malloc(sizeof(Signature));
	assert(s);
	s->taille = size;
	s->tab = (long*)malloc(size*sizeof(long));
	for(int i = 0; i < size; i++) {
		(s->tab)[i] = content[i];
	}
	return s;
}
	
/* 3.7 */
Signature* sign(char* mess, Key* sKey){
	long * tab = encrypt(mess,sKey->x,sKey->n);
    	Signature * res = init_signature(tab,strlen(mess));
    	return res;
}

/* 3.8 */	
char * signature_to_str(Signature * sgn){
    char * result = malloc (10* sgn -> taille * sizeof ( char ) ) ;
    result [0]= '#' ;
    int pos = 1;
    char buffer [156];
    for (int i =0; i < sgn->taille ; i++) {
        sprintf(buffer ,"%lx", sgn->tab[i]) ;
            for (int j =0; j < strlen( buffer ) ; j++) {
                result [pos] = buffer[j];
                     pos = pos +1;
            }
    result [ pos ] = '#' ;
    pos = pos +1;
    }
    result[pos] = '\0' ;
    result = realloc(result , (pos +1) * sizeof ( char ));
    return result ;
}

Signature * str_to_signature( char * str ){
    int len = strlen ( str ) ;
    long * content = ( long *) malloc ( sizeof ( long ) * len ) ;
    int num = 0;
    char buffer [256];
    int pos = 0;
    for (int i =0; i < len ; i ++) {
        if ( str [ i ] != '#' ) {
            buffer [ pos ] = str [ i ];
            pos = pos +1;
        }else {
            if ( pos != 0) {
                buffer [ pos ] = '\0' ;
                sscanf( buffer , "%lx", &(content[num]) ) ;
                num = num + 1;
                pos = 0;
            }
        }
    }
    content = realloc ( content , num * sizeof ( long));
    return init_signature(content,num);
}

/* 3.10 */
Protected * init_protected(Key* pKey, char* mess, Signature* sgn) {
	Protected * p = (Protected*)malloc(sizeof(Protected));
	assert(p);
	p->pKey = pKey;
	p->mess = strdup(mess);
	p->sgn = sgn;
	return p;
}
	
/* 3.11 */
int verify(Protected* pr) {
	char * mess_sgn = decrypt(pr->sgn->tab,pr->sgn->taille,pr->pKey->x,pr->pKey->n);
	 
    if(strcmp(mess_sgn,pr->mess) == 0){
	free(mess_sgn);
        return 1;
    }
    free(mess_sgn);
    return 0;
}

/* 3.12 */
char * protected_to_str(Protected* p){
    char * str = (char*)malloc(256 * sizeof(char));
    sprintf(str, "%s %s %s",key_to_str(p->pKey), p->mess,signature_to_str(p->sgn));
    return str; 
}


Protected * str_to_protected(char* mess){ 
	
	printf("mess :%s\n", mess);
	char keyStr[256];
	char messStr[256];
	char SignStr[256];
	sscanf(mess,"%s %s %s", keyStr, messStr, SignStr);
        Protected * p = init_protected(str_to_key(keyStr), messStr, str_to_signature(SignStr));
    return p;

}

