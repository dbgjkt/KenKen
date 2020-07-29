#include "check_func.h"
//#include "print_func.c"

int isfilled(char *candidates, int grid)
{
	int i;
	for (i = 0; i < grid; i++)
	{
		if (*(candidates + i) >= 2)
			return 1;
	}
	return 0;
}

int checkADD(int value, int blocks, int grid, int candi, char *candidates, int me, char *my_friends)
{
	int i, j;
	int check = 0, another;
	int newv;
	if (*(candidates + me * grid + candi - 1) != 1)
		return 1;

	newv = value - candi;
	switch (blocks)
	{
	case 1:
		return (candi == value) ? 1 : 0;
		break;

	case 2:
		another = *(my_friends);
		if (another == me)
		{
			another = *(my_friends + 1);
		}
		if ((newv < 1) || (grid < newv) || (*(candidates + another * grid + newv - 1) <= 0))
		{
			return 0;
		}
		break;

	default:
		for (i = 0; i < blocks; i++)
		{
			if (*(my_friends + i) == me)
			{
				*(my_friends + i) = *(my_friends + blocks - 1);
			}
			another = *(my_friends + i);
			for (j = 0; j < grid; j++)
			{
				check += checkADD(value - candi, blocks - 1, grid, j + 1, candidates, another, my_friends);
			}
		}
		if (check == 0)
		{
			return 0;
		}
		break;
	}
	return 1;
}

int checkSUB(int value, int grid, int candi, char *candidates, int me, int my_friend)
{
	int i1, i2;
	if (*(candidates + me * grid + candi - 1) != 1)
		return 1;

	i1 = candi + value;
	i2 = candi - value;

	if ((0 < i1) && (i1 <= grid) && (*(candidates + my_friend * grid + i1 - 1) > 0))
	{
		return 1;
	}
	if ((0 < i2) && (i2 <= grid) && (*(candidates + my_friend * grid + i2 - 1) > 0))
	{
		return 1;
	}

	return 0;
}

int checkMUL(int value, int blocks, int grid, int candi, char *candidates, int me, char *my_friends)
{
	int i, j;
	int check = 0, another;
	if (*(candidates + me * grid + candi - 1) != 1)
		return 1;
	if ((value < candi) || ((value % candi) != 0))
		return 0;
	int newv = value / candi;

	switch (blocks)
	{
	case 2:
		another = *(my_friends);
		if (another == me)
		{
			another = *(my_friends + 1);
		}
		if ((newv < 1) || (grid < newv) || (*(candidates + another * grid + newv - 1) <= 0))
		{
			return 0;
		}
		break;

	default:
		for (i = 0; i < blocks - 1; i++)
		{
			//*
			if (*(my_friends + i) == me)
			{
				*(my_friends + i) = *(my_friends + blocks - 1);
			}
			another = *(my_friends + i);
			//*/
			for (j = 0; j < grid; j++)
			{
				if ((newv < (j + 1)) || (newv % (j + 1)) != 0)
				{
					continue;
				}
				check += checkMUL(newv, blocks - 1, grid, j + 1, candidates, another, my_friends);
			}
		}
		if (check == 0)
		{
			return 0;
		}
		break;
	}
	return 1;
}

int checkDIV(int value, int grid, int candi, char *candidates, int me, int my_friend)
{
	int i1, i2;
	if (*(candidates + me * grid + candi - 1) != 1)
		return 1;

	i1 = candi * value;
	if (candi % value == 0)
		i2 = candi / value;
	else
		i2 = -1;
	if ((0 < i1) && (i1 <= grid) && (*(candidates + my_friend * grid + i1 - 1) > 0))
	{
		return 1;
	}
	if ((i2 != -1) && (0 < i2) && (i2 <= grid) && (*(candidates + my_friend * grid + i2 - 1) > 0))
	{
		return 1;
	}

	return 0;
}

void checkOperations(int grid, char *field, int *oper, char *blocks_of_fields,
					 char *candidates, char *cage_friends, char *cage_index, int clevel)
{
	int i, j, k;
	int friends_index;
	int del_value = 0;
	int op, value;
	int blocks;
	char *my_friends;

	if (clevel > 2)
	{
		del_value = 0 - clevel;
	}

	for (i = 0; i < grid * grid; i++)
	{
		op = oper[2 * field[i]];
		value = oper[2 * field[i] + 1];
		friends_index = *(cage_friends + *(cage_index + field[i]));
		blocks = *(blocks_of_fields + i);
		for (j = 0; j < grid; j++)
		{
			switch (op)
			{
			case ADD:
				my_friends = (char *)malloc(blocks * sizeof(char));
				for (k = 0; k < blocks; k++)
				{
					*(my_friends + k) = *(cage_friends + *(cage_index + field[i]) + k);
				}
				if (!checkADD(value, blocks, grid, j + 1, candidates, i, my_friends))
				{
					printf("checkADD(%d,%d)[%d] has changed.\n", i / grid, i % grid, j + 1);
					*(candidates + i * grid + j) = del_value;
				}
				//printf("checkADD OK.\n");
				free(my_friends);
				break;

			case SUB:
				if (i == friends_index)
					friends_index = *(cage_friends + *(cage_index + field[i]) + 1);
				if (!checkSUB(value, grid, j + 1, candidates, i, friends_index))
				{
					printf("checkSUB(%d,%d)[%d] has changed.\n", i / grid, i % grid, j + 1);
					*(candidates + i * grid + j) = del_value;
				}
				break;

			case MUL:
				my_friends = (char *)malloc(blocks * sizeof(char));
				for (k = 0; k < blocks; k++)
				{
					*(my_friends + k) = *(cage_friends + *(cage_index + field[i]) + k);
				}
				if (!checkMUL(value, blocks, grid, j + 1, candidates, i, my_friends))
				{
					printf("checkMUL(%d,%d)[%d] has changed.\n", i / grid, i % grid, j + 1);
					*(candidates + i * grid + j) = del_value;
				}
				//printf("checkMUL OK.\n");
				free(my_friends);
				break;

			case DIV:
				if (i == friends_index)
					friends_index = *(cage_friends + *(cage_index + field[i]) + 1);
				if (!checkDIV(value, grid, j + 1, candidates, i, friends_index))
				{
					printf("checkDIV(%d,%d)[%d] has changed.\n", i / grid, i % grid, j + 1);
					*(candidates + i * grid + j) = del_value;
				}
				break;
			}
		}
	}
	return;
}

int checkAblock(int row, int column, int grid, char *candidate, int *value)
{
	int i;
	int c = 0;
	int tmp;
	for (i = 0; i < grid; i++)
	{
		tmp = *(candidate + (row * grid + column) * grid + i);
		if (tmp > 1)
			c += 2;
		else if (tmp == 1)
		{
			c += 1;
			*value = i + 1;
		}
	}
	if (c == 0)
		return -1;
	else if (c == 1)
		return 1;
	return 0;
}

int checkArow(int row, int val, int grid, char *candidate, int *value)
{
	int i;
	int c = 0;
	int tmp;
	for (i = 0; i < grid; i++)
	{
		tmp = *(candidate + (row * grid + i) * grid + val - 1);
		if (tmp > 1)
			c += 2;
		else if (tmp == 1)
		{
			c += 1;
			*value = i;
		}
	}
	if (c == 0)
		return -1;
	else if (c == 1)
		return 1;
	return 0;
}

int checkAcolumn(int val, int column, int grid, char *candidate, int *value)
{
	int i;
	int c = 0;
	int tmp;
	for (i = 0; i < grid; i++)
	{
		tmp = *(candidate + (i * grid + column) * grid + val - 1);
		if (tmp > 1)
			c += 2;
		else if (tmp == 1)
		{
			c += 1;
			*value = i;
		}
	}
	if (c == 0)
		return -1;
	else if (c == 1)
		return 1;
	return 0;
}

int checkAcage(int grid, int cage_n, int block, char *candidates, char *cage_index, char *cage_friends, int *oper, char *sol)
{
	printf("*************checkAcage:**************\n");
	int i, j;
	int value;
	int val1, val2;
	char *cfriends = (char *)malloc(block * sizeof(char));
	char tmp;
	for (i = 0; i < block; i++)
	{
		tmp = *(cage_friends + *(cage_index + cage_n) + i);
		*(cfriends + i) = tmp;
	}
	//*
	printf("cage=%d,block=%d,index=%d,  ", cage_n, block, *(cage_index + cage_n));
	printf("friends:");
	for (i = 0; i < block; i++)
		printf("%2d ", *(cfriends + i));
	printf("\n");
	//*/
	for (i = 0; i < block; i++)
	{
		if (!isfilled(candidates + (*(cfriends + i)) * grid, grid))
		{
			printf("Not filled yet\n");
			return 1;
		}
	}
	switch (*(oper + 2 * cage_n))
	{
	case ADD:
		value = 0;
		printf("cage: ADD\n");
		for (i = 0; i < block; i++)
		{
			value += *(sol + *(cfriends + i));
		}
		printf("value=%d,op=%d\n", value, *(oper + 2 * cage_n + 1));
		if (value != *(oper + 2 * cage_n + 1))
		{
			return -1;
		}
		break;

	case SUB:
		printf("cage: SUB\n");
		val1 = *(sol + *(cfriends));
		val2 = *(sol + *(cfriends + 1));
		value = (val1 > val2) ? val1 - val2 : val2 - val1;
		printf("value=%d,op=%d\n", value, *(oper + 2 * cage_n + 1));
		if (value != *(oper + 2 * cage_n + 1))
		{
			return -1;
		}
		break;

	case MUL:
		printf("cage: MUL\n");
		value = 1;
		for (i = 0; i < block; i++)
		{
			value *= *(sol + *(cfriends + i));
		}
		printf("value=%d,op=%d\n", value, *(oper + 2 * cage_n + 1));
		if (value != *(oper + 2 * cage_n + 1))
		{
			return -1;
		}
		break;

	case DIV:
		printf("cage: DIV\n");
		val1 = *(sol + *(cfriends));
		val2 = *(sol + *(cfriends + 1));
		value = (val1 > val2) ? val1 / val2 : val2 / val1;
		printf("value=%d,op=%d\n", value, *(oper + 2 * cage_n + 1));
		if (value != *(oper + 2 * cage_n + 1))
		{
			return -1;
		}
		break;
	}
	return 1;
}
