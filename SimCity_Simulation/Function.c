#include"Main.h"

int get_num(void) // ���ڸ� �޴� �Լ� scanf��� ����� ��
{
	int result, check = 0;
	char c;

	while (1)
	{
		result = 0;
		while (1)
		{
			c = getchar();
			if (c == ' ' || c == '\n')
				break;

			if (c<'0' || c>'9')
			{
				//printf("\n�ٽ� �Է��ϼ���.\n");
				check = 0;
				break;
			}

			result = result * 10;
			result = result + c - '0';
			check = 1;
		}

		if (check == 1)
			break;
	}

	fflush(stdin);
	return result;
}
void gotoxy(int x, int y) // ��ǥ �Լ� ù ���� ���� ������ ��ǥ�� (1,1)��
{
	COORD Pos = { x - 1,y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
int Random(int x)////���� �Լ� 0~x-1 �� �������� �ϳ��� ���� ��ȯ
{
	int i;
	i = rand() % x;
	return i;
}
int My_strlen(char *string) // ���ڿ��� ���̸� ��ȯ, �ѱ��� ��� 2����Ʈ�� ���
{
	int i = 0;

	while (*(string + i) != '\0')
		i++;

	return i;
}
int My_strcmp(char *string1, char *string2) // �� ���ڿ��� ���ؼ� ������ 1, �ٸ��� 0�� ��ȯ
{
	int i = 0, len = My_strlen(string1);

	if (len == My_strlen(string2))
	{
		for (i = 0; i < len; i++)
			if (*(string1 + i) != *(string2 + i))
				return 0;
		return 1;
	}
	else
		return 0;
}
void get_n_string(char *string, int size) //���̰� n�� ���ڿ��� ����, ���ڴ�(���ڿ��� ������ ����, ���ڿ��� ����), ���� �������� NULL(\0)�� ������
{
	int i = 0;

	do {
		string[i] = getchar();
		i++;
	} while (string[i - 1] != '\n' && i<size + 1);

	string[i - 1] = '\0';

	fflush(stdin);

}
void get_n_string_void(char *string, int size) //get_n_string�� ���� �Լ�,But �� �� �Է��� �Ϳ� ���� ������ �Ұ����ϰ�, ���ڰ� ����(����� ġ���� �� ����)
{
	int i = 0;

	do {
		string[i] = getch();
		i++;
	} while (string[i - 1] != '\r' && i<size + 1);

	string[i - 1] = '\0';
	fflush(stdin);
}
int Find_pattern(char *string, char *pattern, int mode)// ������ ã�� ���� �⺻ ������� �Ͽ�, ��忡 ���� ��ȯ ���� �ٸ�
{
	int loop_size = My_strlen(string) - My_strlen(pattern) + 1;
	int i = 0, count = 0;

	for (i = 0; i < loop_size; i++)
		if (check_first(string + i, pattern) == 1)
			if (check(string + i, pattern) == 1)
			{
				if (mode == 1) // ��尡 1�� ��, ������ ã���� ������ 1�� ��ȯ��
					return 1;
				else if (mode == 2) // ��尡 2�� ��, ã�� ������ ������ ��ȯ��.
					count++;
				else if (mode == 3) // ��尡 3�� ��, ���ʷ� ã�� ������ ��ġ�� ��ȯ��.
					return i;
			}

	if (mode == 1)
		return 0;
	else if (mode == 2)
		return count;
	else if (mode == 3)
		return -1;
	else
		return -1; // ��忡 1,2,3 �̿��� ������ �־��� ��, -1�� ��ȯ��
}
int check(char *string, char *pattern) // Find_pattern�� ���̴� �Լ�, My_strcmp�� ���� ���� ����� ��.
{
	int loop_size = My_strlen(pattern);
	int i = 0;

	for (i = 0; i < loop_size; i++)
	{
		if (*(string + i) != *(pattern + i))
			return 0;
	}
	return 1;

}
int check_first(char *string1, char *string2) //�� ���ڿ��� ù ��° ���ڰ� ������ Ȯ��, ������ 1, �ٸ��� 0�� ��ȯ
{
	if (*string1 != *string2)
		return 0;
	else
		return 1;
}
int File_Check(FILE *Fp) //���� ���� ���¿� ���� ���� ���� �� 0, ���� �� 1�� ��ȯ
{
	if (Fp == NULL)
		return 0;
	else
		return 1;
}
