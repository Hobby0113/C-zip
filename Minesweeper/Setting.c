#include"Main.h"

void box(void)
{
	int i, j;
	for (i = 0; i < XY; i++)
	{
		printf("■■");
		for (j = 0; j < XY - 2; j++)
		{
			if (i == 0 || i == XY - 1)
				printf("■");
			else
				printf("  ");
		}
		printf("■%d\n", i);
	}
	printf("■");
	for (i = 0; i < XY - 2; i++)
		printf("%c", 97 + i);
	gotoxy((XY * 2) + 1, 1);
	printf("■");
	gotoxy((XY * 2) + 1, XY);
	printf("  ");
}

int set_tile(TILE (*T)[SIZE])
{
	int i, j, k,count=0;
	TILE *TP = NULL;

	//����, open, Ÿ�� ������ �ʱ�ȭ
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
		{
			TP = T[i]+j;
			TP->i = 0;
			TP->open = 0;
			for (k = 0; k < 8; k++)
				TP->NT[k] = NULL;
		}

	set_mine(T,&count);
	set_tileP(T);
	count_mine(T);

	return count;
}
void print_tile(TILE (*T)[SIZE])
{
	int i, j;
	TILE *TP = NULL;

	for (i = 0; i < SIZE; i++)
	{
		gotoxy(3, 2+i);
		for (j = 0; j < SIZE; j++)
		{
			TP = T[i] + j;
			if (TP->i == 0) printf("��");
			if (TP->i == 1) printf("��");
			if (TP->i == 2) printf("��");
			if (TP->i == 3) printf("��");
			if (TP->i == 4) printf("��");
			if (TP->i == 5) printf("��");
			if (TP->i == 6) printf("��");
			if (TP->i == 7) printf("��");
			if (TP->i == 8) printf("��");
			if (TP->i == 9) printf("��");
		}
	}
}
void set_mine(TILE (*T)[SIZE], int *count)
{
	int i, j, k;
	TILE *TP = NULL;

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			k = Random(SIZE-2);
			if (k == 0)
			{
				TP = T[i]+j;
				TP->i = 9;
				(*count)++;
			}
			if (*count == MINENUM)
				break;
		}
		if (*count == MINENUM)
			break;
	}
}
void set_tileP(TILE (*T)[SIZE])
{
	int i, j;
	TILE *TP = NULL;

	for (i = 0; i<SIZE; i++)
		for (j = 0; j < SIZE; j++)
		{
			TP = T[i] + j;
			if (i != 0)
			{
				if (j != 0)  TP->NT[0] = T[(i - 1)]+(j - 1); //��
				TP->NT[1] = T[(i - 1)] + j; //��
				if (j != SIZE - 1)  TP->NT[2] = T[(i - 1)] + (j + 1); //��
			}
			if (j != 0)
				TP->NT[3] = T[i] + (j - 1); //��
			if (j != SIZE-1)
				TP->NT[4] = T[i] + (j + 1); //��
			if (i != SIZE - 1)
			{
				if (j != 0)  TP->NT[5] = T[(i + 1)] + (j - 1); //��
				TP->NT[6] = T[(i + 1)] + j; //��
				if (j != SIZE - 1)  TP->NT[7] = T[(i + 1)] + (j + 1); //��
			}
		}
}
void count_mine(TILE (*T)[SIZE])
{
	TILE *TP = NULL;
	TILE *TP2 = NULL;
	int i, j, k;

	for (i = 0; i<SIZE; i++)
		for (j = 0; j < SIZE; j++)
		{
			TP = T[i] + j;
			if (TP->i != 9)
				for (k = 0; k < 8; k++)
					if (TP->NT[k] != NULL)
					{
						TP2 = TP->NT[k];
						if (TP2->i == 9)
							(TP->i)++;
					}
		}
}
void print_one_tile(TILE *T, int i, int j)
{
	gotoxy(3 + j * 2, 2 + i);

	if (T->i == 0) printf("��");
	if (T->i == 1) printf("��");
	if (T->i == 2) printf("��");
	if (T->i == 3) printf("��");
	if (T->i == 4) printf("��");
	if (T->i == 5) printf("��");
	if (T->i == 6) printf("��");
	if (T->i == 7) printf("��");
	if (T->i == 8) printf("��");
	if (T->i == 9) printf("��");
}
void print_cover(void)
{
	int i, j;
	for (i = 0; i < SIZE; i++)
	{
		gotoxy(3, 2 + i);
		for (j = 0; j < SIZE; j++)
			 printf("��");
	}
}
