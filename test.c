#include <openssl/sha.h>

int main(){
 const char * s = ” R o s e t t a c ode ”;
 unsigned char * d = SHA256 (s , strlen ( s ) , 0) ;
 int i ;
 for( i = 0; i < SHA256_DIGEST_LENGTH ; i ++)
    printf (”%02x” , d [ i ]) ;
 putchar ( ’ \n ’ ) ;
 return 0;
}