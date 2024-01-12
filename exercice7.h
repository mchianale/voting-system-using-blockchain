#ifndef EXERCICE7
#define EXERCICE7

typedef struct block{
    Key * author;
    CellProtected * votes;
    unsigned char * hash;
    unsigned char * previous_hash;
    int nonce;
}Block;

//preliminaire
Block * new_block(int, Key *, char *, char *, CellProtected *);
//1
void write_block(char *, Block *);
//2
Block * read_block(char*);
//3
char* block_to_str(Block* block);
//5
unsigned char * str_to_hash(const char *);
//6
int nb_zero(unsigned char *);
void compute_proof_of_work(Block *, int);
//7
int verify_block(Block *, int);
//8
void AnalyseCompute(Block *, int);
//9
void delete_block(Block*);

#endif
