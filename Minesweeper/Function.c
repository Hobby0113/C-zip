#include"Main.h"

void gotoxy(int x, int y)
{
	COORD Pos = { x - 1,y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
int Random(int x)
{
	int i;
	i = rand() % x;
	return i;
}
int get_num(void)
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
				//printf("다시 입력하세요.\n");

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

	return result;
}

void play(TILE (*T)[SIZE],int m)
{
	int x, y, mine = m, tile = SIZE*SIZE;
	TILE *TP = NULL;

	while (1)
	{
		UI(mine, tile);
		gotoxy(5, UI_Y + 1);
		x = get_num() - 1;
		gotoxy(13, UI_Y + 1);
		y = get_num() - 1;

		if (correct_num(x, y) == 2)
		{
			if (is_Open(T, x, y) == 0)
			{
				TP = T[x]+y;
				tile -= open_tile(TP, x, y);
				if (TP->i == 9)
				{
					is_Mine();
					break;
				}

			}
			else
				overlap();
		}
		UI(mine,tile);

		if (tile == mine)
			break;
	}
	gotoxy(1, UI_Y + 5);
	printf("정말 수고하셨습니다!");
	Sleep(3000);
}
void UI(int m,int t)
{
	gotoxy(1, UI_Y);
	printf("좌표 입력\n");//13
	printf("행:     열:     \n");//14
	printf("남은 지뢰: %2d개\n", m);//15
	printf("남은 타일: %2d개", t);//16
}
int open_tile(TILE *T,int x, int y)
{
	int sum=0;

	print_one_tile(T, x, y);
	if (T->i == 9)
		return 1;

	if (T->open != 1)
	{
		T->open = 1;
		sum++;
	}
	else
		return 0;

	if(T->i == 0)
		sum += is_Zero(T,x,y);

	return sum;
}
int is_Open(TILE (*T)[SIZE], int x, int y)
{
	if ((T[x]+y)->open == 1)
		return 1;
	else
		return 0;
}
void overlap(void)
{
	gotoxy(1, UI_Y + 4);
	printf("이미 열린 타일입니다.");
	Sleep(2000);
	gotoxy(1, UI_Y + 4);
	printf("                     ");
}
int is_NULL(TILE *T)
{
	if (T == NULL)
		return 1;
	else
		return 0;
}
int correct_num(int x, int y)
{
	int i = 0;
	if (x >= 0 && x < SIZE)
		i++;
	if (y >= 0 && y < SIZE)
		i++;

	return i;
}
int is_Zero(TILE *T, int x, int y)
{
	int i, nx, ny,s=0;
	TILE *TP = NULL;

	for (i = 0; i < 8; i++)
		if (T->NT[i] != NULL)
		{
			TP = (T->NT[i]);
			nx = (&(*TP) - T) / (SIZE - 1);
			if (i == 2 || i == 5)
				ny = ((&(*TP) - T) / -(SIZE - 1));
			else
				ny = ((&(*TP) - T) % SIZE);
			s += open_tile(TP, x + nx, y + ny);
		}
	return s;
}
void testF(TILE *T, int x, int y)
{
	int i,nx,ny;
	TILE *TP = NULL;
	gotoxy(1, 20);

	for (i = 0; i < 8; i++)
		if (T->NT[i] != NULL)
		{
			TP = (T->NT[i]);
			nx = (&(*TP) - T) / 8;
			if (i == 2 || i == 5)
				ny = ((&(*TP) - T) / -8);
			else
				ny = ((&(*TP) - T) % 9);
			printf("%d-%d, %d    ",i, x+nx, y+ ny);
		}
}
void is_Mine(void)
{
	gotoxy(1, UI_Y+5);
	printf("펑!! 지뢰입니다!");
}