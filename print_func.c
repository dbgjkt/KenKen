#include "print_func.h"

/*
void printpuzzle(int A[], int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("+--");
		}
		printf("+\n");
		for(j=0;j<n;j++)
		{
			printf("|%2d",A[i*n+j]);
		}
		printf("|\n");
	}
	for(j=0;j<n;j++)
	{
		printf("+--");
	}
	printf("+\n");
	return;
}
*/
void printpuzzle(char *A, char *B, int grid)
{
	int i, j;
	int value;
	for (i = 0; i < grid; i++)
	{
		for (j = 0; j < grid; j++)
		{
			if (i > 0 && *(A + (i - 1) * grid + j) == *(A + i * grid + j))
				printf("+    ");
			else
				printf("+----");
		}
		printf("+\n");
		for (j = 0; j < grid; j++)
		{
			if (j > 0 && *(A + i * grid + j - 1) == *(A + i * grid + j))
				printf(" ");
			else
				printf("|");
			printf("%4d", *(B + i * grid + j));
		}
		printf("|\n");
	}
	for (j = 0; j < grid; j++)
	{
		printf("+----");
	}
	printf("+\n");
	return;
}

void printkenken(char *A, int *B, int grid)
{
	int i, j;
	int value;
	for (i = 0; i < grid; i++)
	{
		for (j = 0; j < grid; j++)
		{
			if (i > 0 && *(A + (i - 1) * grid + j) == *(A + i * grid + j))
				printf("+    ");
			else
				printf("+----");
		}
		printf("+\n");
		for (j = 0; j < grid; j++)
		{
			if (j > 0 && *(A + i * grid + j - 1) == *(A + i * grid + j))
				printf(" ");
			else
				printf("|");
			value = *(A + i * grid + j);
			switch (*(B + 2 * value))
			{
			case ADD:
				printf("+");
				break;
			case SUB:
				printf("-");
				break;
			case MUL:
				printf("*");
				break;
			case DIV:
				printf("/");
				break;
			default:
				printf("?");
				break;
			}
			printf("%3d", *(B + 2 * value + 1));
		}
		printf("|\n");
	}
	for (j = 0; j < grid; j++)
	{
		printf("+----");
	}
	printf("+\n");
	return;
}

void printCandidates(char *candidates, int grid)
{
	int i, j, k;
	int tmp;
	for (i = 0; i < grid; i++)
	{
		for (j = 0; j < grid; j++)
		{
			for (k = 0; k < grid; k++)
			{
				if (k > 0)
					printf(",");
				tmp = candidates[i * grid * grid + j * grid + k];
				if (tmp >= 0)
					printf(" %X", tmp);
				else
					printf("-%X", 0 - tmp);
			}
			printf("; ");
		}
		printf("\n");
	}
	printf("\n");
	return;
}

void printA(char *A, int grid)
{
	int i;
	printf("A:\n");
	for (i = 0; i < grid * grid; i++)
	{
		printf("%2d ", *(A + i));
		if ((i + 1) % grid == 0)
			printf("\n");
	}
	return;
}

void printB(int *B, int cage)
{
	int i;
	printf("B:\n");
	for (i = 0; i < cage; i++)
	{
		switch (*(B + 2 * i))
		{
		case ADD:
			printf(" + ");
			break;

		case SUB:
			printf(" - ");
			break;

		case MUL:
			printf(" * ");
			break;

		case DIV:
			printf(" / ");
			break;
		}
	}
	printf("\n");
	for (i = 0; i < cage; i++)
	{
		printf("%2d ", *(B + 2 * i + 1));
	}
	printf("\n");
	return;
}

void printBoC(char *blocks_of_cages, int cage)
{
	int i;
	printf("BoC:\n");
	for (i = 0; i < cage; i++)
	{
		printf("%d ", *(blocks_of_cages + i));
	}
	printf("\n--------------------------\n");
	return;
}

void printBoF(char *blocks_of_fields, int grid)
{
	int i;
	printf("BoF:\n");
	for (i = 0; i < grid * grid; i++)
	{
		printf("%2d ", *(blocks_of_fields + i));
		if ((i + 1) % grid == 0)
			printf("\n");
	}
	printf("--------------------------\n");
	return;
}

void printCageFriends(char *cage_friends, int grid)
{
	int i;
	printf("cageFriends:\n");
	for (i = 0; i < grid * grid; i++)
	{
		printf("%2d ", *(cage_friends + i));
	}
	printf("\n--------------------------\n");
	return;
}

void printCageIndex(char *cage_index, int cage)
{
	int i;
	printf("cageIndex:\n");
	for (i = 0; i < cage; i++)
	{
		printf("%2d ", *(cage_index + i));
	}
	printf("\n--------------------------\n");
	return;
}
