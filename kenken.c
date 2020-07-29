#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "kenken.h"
#include "check_func.c"
#include "print_func.c"
#include "initial.c"

void fillAblock(char *candidates, char *sol, int grid, int x, int y, int c, int value)
{
	int i;
	*(sol + x * grid + y) = c;
	for (i = 0; i < grid; i++)
	{
		*(candidates + (x * grid + i) * grid + c - 1) = 0;
		*(candidates + (i * grid + y) * grid + c - 1) = 0;
		*(candidates + (x * grid + y) * grid + i) = 0;
	}
	*(candidates + (x * grid + y) * grid + c - 1) = value;
	return;
}

void guessAblock(char *candidates, char *sol, int grid, int x, int y, int c, int glevel)
{
	int i;
	int tmpb, tmpr, tmpc;
	*(sol + x * grid + y) = c;
	for (i = 0; i < grid; i++)
	{
		tmpr = *(candidates + (x * grid + i) * grid + c - 1);
		tmpc = *(candidates + (i * grid + y) * grid + c - 1);
		tmpb = *(candidates + (x * grid + y) * grid + i);
		if (tmpr == 1)
			*(candidates + (x * grid + i) * grid + c - 1) = 0 - glevel;
		if (tmpc == 1)
			*(candidates + (i * grid + y) * grid + c - 1) = 0 - glevel;
		if (tmpb == 1)
			*(candidates + (x * grid + y) * grid + i) = 0 - glevel;
	}
	*(candidates + (x * grid + y) * grid + c - 1) = glevel;
	return;
}

void clear_guess(char *candidates, char *sol, int grid, int x, int y, int c, int glevel)
{
	int i, j;
	int clear = 0;
	int tmpsol = 0;
	*(sol + x * grid + y) = 0;
	for (i = 0; i < grid * grid; i++)
	{
		for (j = 0; j < grid; j++)
		{
			if (((*(candidates + i * grid + j) + glevel) == 0) || ((*(candidates + i * grid + j) - glevel) == 0))
			{
				*(candidates + i * grid + j) = 1;
				*(sol + i) = 0;
			}
		}
	}

	if (glevel == 3)
		clear = 0;
	else if (glevel > 3)
		clear = 1 - glevel;
	*(candidates + (x * grid + y) * grid + c - 1) = clear;
	return;
}

int check_n_fill(char *sol, char *candidates, int grid, char *field, int *oper, char *blocks_of_fields,
				 char *cage_friends, char *cage_index, int clevel, int *loop_count, int cage)
{
	int i, j;
	//int loop_count = 0;
	int block_count = 0;
	int value;
	int cb, cr, cc, ca;
	int err;
	int run_twice = 0;
	for (i = 0; i < grid * grid; i++)
	{
		if (isfilled(candidates + i * grid, grid))
			block_count++;
	}

	while (1)
	{
		for (i = 0; i < grid; i++)
		{
			for (j = 0; j < grid; j++)
			{
				printf("(%d,%d)\n", i, j);
				(*loop_count)++;

				cb = checkAblock(i, j, grid, candidates, &value);
				if (cb < 0)
				{
					printf("error:block\n");
					return -1;
				}
				else if (cb > 0)
				{
					run_twice = 0;
					block_count++;
					printf("block(%d,%d,%d)\n", i, j, value);
					if (clevel == 2)
						fillAblock(candidates, sol, grid, i, j, value, clevel);
					else if (clevel > 2)
					{
						guessAblock(candidates, sol, grid, i, j, value, clevel);
						ca = checkAcage(grid, *(field + i * grid + j), *(blocks_of_fields + i * grid + j), candidates, cage_index, cage_friends, oper, sol);
						if (ca < 0)
						{
							printf("error:cage\n");
							return -1;
						}
					}
					//printCandidates(candidates, grid);
				}

				cr = checkArow(i, j + 1, grid, candidates, &value);
				if (cr < 0)
				{
					printf("error:row\n");
					return -1;
				}
				else if (cr > 0)
				{
					run_twice = 0;
					block_count++;
					printf("row(%d,%d,%d)\n", i, value, j + 1);
					if (clevel == 2)
						fillAblock(candidates, sol, grid, i, value, j + 1, clevel);
					else if (clevel > 2)
					{
						guessAblock(candidates, sol, grid, i, value, j + 1, clevel);
						ca = checkAcage(grid, *(field + i * grid + value), *(blocks_of_fields + i * grid + value), candidates, cage_index, cage_friends, oper, sol);
						if (ca < 0)
						{
							printf("error:cage\n");
							return -1;
						}
					}
					//printCandidates(candidates, grid);
				}

				cc = checkAcolumn(j + 1, i, grid, candidates, &value);
				if (cc < 0)
				{
					printf("error:column\n");
					return -1;
				}
				else if (cc > 0)
				{
					run_twice = 0;
					block_count++;
					printf("column(%d,%d,%d)\n", value, i, j + 1);
					if (clevel == 2)
						fillAblock(candidates, sol, grid, value, i, j + 1, clevel);
					if (clevel > 2)
					{
						guessAblock(candidates, sol, grid, value, i, j + 1, clevel);
						ca = checkAcage(grid, *(field + value * grid + i), *(blocks_of_fields + value * grid + i), candidates, cage_index, cage_friends, oper, sol);
						if (ca < 0)
						{
							printf("error:cage\n");
							return -1;
						}
					}
					//printCandidates(candidates, grid);
				}
				if (block_count >= grid * grid)
				{
					printf("***solution found***\n");
					printf("loop_count = %d\n", *loop_count);
					return 1;
				}
			}
		}
		if (run_twice == 0)
		{
			printf("check operations:\n");
			checkOperations(grid, field, oper, blocks_of_fields, candidates, cage_friends, cage_index, clevel);
			//printCandidates(candidates,grid);

			run_twice = 1;
			continue;
		}
		printf("cannot find ans\n");
		printf("loop_count = %d\n", *loop_count);
		break;
	}
	checkOperations(grid, field, oper, blocks_of_fields, candidates, cage_friends, cage_index, 2);
	return 0;
}

void solvepuzzle(char *sol, char *field, int *oper, int grid, int cage)
{
	/************************************************************************
	*	solve: the solution of board, length = n*n							*
	*	field: the field of board, length = n*n								*
	*	oper: the operation	& value of board, length = Fn*2					*
	*		oper[2*i]:	operation of field									*
	*					0:'+',												*
	*					1:'-',												*
	*					2:'*',												*
	*					3:'/'												*
	*		oper[2*i+1]:the value of execution								*
	*	n: the GRID of the board											*
	************************************************************************/
	char *blocks_of_cages;	/*number of blocks of one cage, the array length = cage*/
	char *blocks_of_fields; /*number of blocks of each cage, the array length = n*n*/
	char *candidates;		/*candidates of each block, the array length = n*n*n*/
	char *cage_friends;		/*record who is the friend of cage, the array length = n*n*/
	char *cage_index;
	/************************************************************************
	*					  A Sample of These Variables						*
	*   kenken:        Field:     BoF:       Oper:                          *
	*     -2 -2| 4|x6    0 0 1 2    2 2 1 3    - + x / - - + /              *
	*     /2 /2|x6 x6    3 3 2 2    2 2 3 3    2 4 6 2 1 3 7 2              *
	*     -1|-3 -3|+7    4 5 5 6    2 2 2 2  BoC:                           *
	*     -1|/2 /2|+7    4 7 7 6    2 2 2 2    2 1 3 2 2 2 2 2              *
	*   CageFriends:                                                        *
	*     0 1, 2, 3 6 7, 4 5, 8 12, 9 10, 11 15, 13 14                      *
	*   CageIndex:                                                          *
	*     0    2  3      6    8    10     12     14                         *
	*************************************************************************/
	/************************************************************************
	*						How To Solve Kenken								*
	*	1.	Check all possibilities of numbers in every block.				*
	*	2.	If one block has only one number to fill, fill it up.			*
	*	3.	remove impossible numbers from blocks.							*
	*	4.	If the board is not solved, back to step 2.						*
	*																		*
	*************************************************************************/
	int i, j, k;
	/*initialize BoC*/
	blocks_of_cages = (char *)malloc(cage * sizeof(char));
	memset(blocks_of_cages, 0, cage * sizeof(char));
	initialBoC(blocks_of_cages, field, grid);
	printBoC(blocks_of_cages, cage);

	/*initialize BoF*/
	blocks_of_fields = (char *)malloc(grid * grid * sizeof(char));
	memset(blocks_of_fields, 0, grid * grid * sizeof(char));
	initialBoF(blocks_of_fields, blocks_of_cages, field, grid);
	printBoF(blocks_of_fields, grid);

	/*initialize candidates*/
	candidates = (char *)malloc(grid * grid * grid * sizeof(char));
	memset(candidates, 1, grid * grid * grid * sizeof(char));

	/*initialize cageFriends & cage_index*/
	cage_friends = (char *)malloc(grid * grid * sizeof(char));
	memset(cage_friends, 0, grid * grid * sizeof(char));
	cage_index = (char *)malloc(cage * sizeof(char));
	memset(cage_index, 0, cage * sizeof(char));
	initialCageFriends(cage_friends, cage_index, grid, cage, blocks_of_cages, field);
	printCageFriends(cage_friends, grid);
	printCageIndex(cage_index, cage);

	/* * * start to solve it * * */
	printCandidates(candidates, grid);
	checkOperations(grid, field, oper, blocks_of_fields, candidates, cage_friends, cage_index, 2);
	printCandidates(candidates, grid);

	int guess;
	int check;
	int glevel = 2;
	int maxglevel = 2;
	int fi = 0;
	int mincandi, tmpcandi;
	int gi[90], gj[90];
	int guessdepth_count = 0;
	int loop_count = 0;
	while (1)
	{

		check = check_n_fill(sol, candidates, grid, field, oper, blocks_of_fields, cage_friends, cage_index, glevel, &loop_count, cage);
		printCandidates(candidates, grid);
		if (check == 1)
		{
			break;
		}
		if (check == -1)
		{
			if (glevel <= 2)
			{
				printf("serious error\n");
				printf("loop_count = %d\n", loop_count);
				printf("guessdepth_count = %d\n", guessdepth_count);
				printf("max_glevel = %d\n", maxglevel);
				return;
			}
			printf("there's sth wrong.\n");
			printf("loop_count = %d\n", loop_count);
			printCandidates(candidates, grid);
			printpuzzle(field, sol, grid);
			printf("clear guess:(%d,%d)[%d]\n", gi[glevel] / grid, gi[glevel] % grid, gj[glevel] + 1);
			clear_guess(candidates, sol, grid, gi[glevel] / grid, gi[glevel] % grid, gj[glevel] + 1, glevel);
			printCandidates(candidates, grid);
			printpuzzle(field, sol, grid);
			glevel--;
			printf("------------------glevel=[%d]-----------------------------------------------------\n", glevel);
			guessdepth_count++;
			if (guessdepth_count > 2000)
			{
				printf("wrong edge explode!!!\n");
				printf("max_glevel = %d\n", maxglevel);
				return;
			}
		}
		if (check == 0)
		{
			guess = 0;
			/*
			printCandidates(candidates,grid);
			printpuzzle(field,sol,grid);
			*/
			mincandi = 999999;
			for (i = 0; i < grid * grid; i++)
			{
				tmpcandi = 0;
				for (j = 0; j < grid; j++)
				{
					if (*(candidates + i * grid + j) == 1)
					{
						tmpcandi++;
					}
				}
				if (!isfilled(candidates + i * grid, grid) && mincandi > tmpcandi)
				{
					fi = i;
					mincandi = tmpcandi;
					printf("(%d,%d) is blank. mincandi:[%d]\n", fi / grid, fi % grid, mincandi);
				}
			}
			for (j = 0; j < grid; j++)
			{
				if ((guess == 0) && (*(candidates + fi * grid + j) == 1))
				{
					glevel++;
					gi[glevel] = fi;
					gj[glevel] = j;
					if (maxglevel < glevel)
						maxglevel = glevel;
					printf("------------------glevel=[%d]-----------------------------------------------------\n", glevel);
					printf("guess(%d,%d)=[%d]\n", fi / grid, fi % grid, j + 1);
					guessAblock(candidates, sol, grid, fi / grid, fi % grid, j + 1, glevel);

					/*
					printCandidates(candidates,grid);
					printpuzzle(field,sol,grid);
					*/
				}
			}
		}
	}
	printf("wrongedge_count = %d\n", guessdepth_count);
	printf("max_glevel = %d\n", maxglevel);

	return;
}

int main()
{
	/*
	printf("   c1 c2 c3 c4 \n");
	printf("  ┌──┬──┬──┬──┐\n");
	printf("r1│  │  │  │  │\n");
	printf("  ├──┼──┼──┼──┤\n");
	printf("r2│  │  │  │  │\n");
	printf("  ├──┼──┼──┼──┤\n");
	printf("r3│  │  │  │  │\n");
	printf("  ├──┼──┼──┼──┤\n");
	printf("r4│  │  │  │  │\n");
	printf("  └──┴──┴──┴──┘\n");
	*/
	int i, j;
	int grid;
	int cage;
	scanf("%d", &grid);
	char *A = (char *)malloc(grid * grid * sizeof(char));
	cage = initialA(A, grid);

	int *B = (int *)malloc(cage * 2 * sizeof(int));
	initialB(B, cage);
	char *C = (char *)malloc(grid * grid * sizeof(char));
	memset(C, 0, grid * grid * sizeof(char));
	printA(A, grid);
	printB(B, cage);
	printf("---------------------------------------------------------------\n");

	printkenken(A, B, grid);
	printf("---------------------------------------------------------------\n");
	solvepuzzle(C, A, B, grid, cage);
	printkenken(A, B, grid);
	printf("---------------------------------------------------------------\n");
	printpuzzle(A, C, grid);
	return 0;
}
