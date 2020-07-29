#include "kenken.h"

//int checkADD(int, int, int, int, char*, int, char*);
int checkADD(int value, int blocks, int grid, int candi, char *candidates, int me, char *my_friends);
int checkSUB(int value, int grid, int candi, char *candidates, int me, int my_friend);
//int checkSUB(int, int, int, char*, int, int);
//int checkMUL(int, int, int, int, char*, int, char*);
int checkMUL(int value, int blocks, int grid, int candi, char *candidates, int me, char *my_friends);

int checkDIV(int value, int grid, int candi, char *candidates, int me, int my_friend);
void checkOperations(int grid, char *field, int *oper, char *blocks_of_fields,
					 char *candidates, char *cage_friends, char *cage_index, int clevel);

int checkAblock(int row, int column, int grid, char *candidate, int *value);
int checkArow(int row, int val, int grid, char *candidate, int *value);
int checkAcolumn(int val, int column, int grid, char *candidate, int *value);
int checkAcage(int grid, int cage_n, int block, char *candidates,
			   char *cage_index, char *cage_friends, int *oper, char *sol);
