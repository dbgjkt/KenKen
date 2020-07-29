#ifndef ADD
#define ADD 0
#endif
#ifndef SUB
#define SUB 1
#endif
#ifndef MUL
#define MUL 2
#endif
#ifndef DIV
#define DIV 3
#endif

void printpuzzle(char *field, char *puzzle, int grid);
void printkenken(char *field, int *oper, int grid);
void printCandidates(char *candidates, int grid);
void printA(char *field, int grid);
void printB(int *oper, int cage);
void printCageFriends(char *cage_friends, int grid);
void printCageIndex(char *cage_index, int cage);
