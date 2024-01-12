#ifndef EXERCICE8
#define EXERCICE8
typedef struct block_tree_cell {
	Block * block;
	struct block_tree_cell * father;
	struct block_tree_cell * firstChild;
	struct block_tree_cell * nextBro;
	int height;
}CellTree;

//1
CellTree * create_node(Block *);
//2
int update_height(CellTree *, CellTree *);
//3
void add_child(CellTree *, CellTree *);
//4
void print_tree(CellTree *);
//5
void delete_node(CellTree *);
void delete_tree(CellTree *);
//6
CellTree * highest_child(CellTree *);
//7
CellTree * last_node(CellTree *);
//8
CellProtected * fusion_liste(CellProtected *, CellProtected *);
//9
CellProtected * get_votes(CellTree *);
#endif
