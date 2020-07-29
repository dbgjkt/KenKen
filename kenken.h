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

#ifndef IMP_FILL
#define IMP_FILL 0
#endif
#ifndef UN_FILL
#define UN_FILL 1
#endif
#ifndef IS_FILL
#define IS_FILL 2
#endif

/*
typedef struct kenken
{
	int grid;
	int cage;
	char* field;
	char* oper;
	char* candidates;          //candidates of each block, the array length = n*n*n
	char* blocks_of_cages;     //number of blocks of one cage, the array length = cage
	char* blocks_of_fields;    //number of blocks of each cage, the array length = n*n
	char* cage_friends;        //record who is the friend of cage, the array length = n*n
	char* cage_index;

}Kenken;
//*/
