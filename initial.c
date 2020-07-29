
void initialBoC(char *blocks_of_cages, char *field, int grid)
{
	int i;
	for (i = 0; i < grid * grid; i++)
	{
		(*(blocks_of_cages + field[i]))++;
	}
	return;
}

void initialBoF(char *blocks_of_fields, char *blocks_of_cages, char *field, int grid)
{
	int i;
	for (i = 0; i < grid * grid; i++)
	{
		*(blocks_of_fields + i) = *(blocks_of_cages + field[i]);
	}
	return;
}

void initialCageFriends(char *cage_friends, char *cage_index, int grid, int cage, char *blocks_of_fields, char *field)
{
	int i;

	for (i = 1; i < cage; i++)
	{
		*(cage_index + i) += *(cage_index + i - 1) + *(blocks_of_fields + i - 1);
	}

	for (i = 0; i < grid * grid; i++)
	{
		*(cage_friends + *(cage_index + field[i])) = i;
		(*(cage_index + field[i]))++;
	}

	for (i = cage - 1; i > 0; i--)
	{
		*(cage_index + i) = *(cage_index + i - 1);
	}
	*cage_index = 0;

	return;
}

int initialA(char *A, int grid)
{
	int i, cage = 0;
	int tmp;
	for (i = 0; i < grid * grid; i++)
	{
		scanf("%d", &tmp);
		*(A + i) = tmp;
		if (tmp > cage)
			cage = tmp;
	}
	return cage + 1;
}

void initialB(int *B, int cage)
{
	int i, tmp;
	char op[4];
	for (i = 0; i < cage; i++)
	{
		scanf("%s%d", &op, &tmp);
		*(B + 2 * i + 1) = tmp;
		if (strcmp(op, "+") == 0)
			*(B + 2 * i) = ADD;
		else if (strcmp(op, "-") == 0)
			*(B + 2 * i) = SUB;
		else if (strcmp(op, "*") == 0)
			*(B + 2 * i) = MUL;
		else if (strcmp(op, "/") == 0)
			*(B + 2 * i) = DIV;
		else
			*(B + 2 * i) = 0;
	}
	return;
}
