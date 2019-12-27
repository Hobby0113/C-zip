#include<stdio.h>
#include<stdlib.h> //system("cls") 함수
#include<Windows.h> //Sleep 함수
#include<conio.h> //getch() 함수
#include<time.h>
#include<process.h> //thread 함수

int l=0;

int menu(void);
void play(void);
void gotoxy(int x, int y);
unsigned int WINAPI ThreadFunction(void *arg);

int main(void)
{
	int m=0;

	while (1)
	{
		if (m == 1)
			play();
		else if (m == 2)
			break;

		system("cls");
		m = menu();
	}
	return 0;
}

int menu(void)
{
	int m;

	system("cls");
	printf("1. Play 2. Exit\nSelect: ");
	scanf("%d", &m);

	return m;
}

void play(void)
{
	int i=0;
	char c = 0,n=0,m=0;
	int ac[50] = { 0 };
	short key[4] = { 72, 75,77,80 };
	HANDLE hThread = NULL;
	DWORD dwThreadID = NULL;

	system("cls");
	//배열에 숫자 넣기
	for (i = 0; i < 50; i++)
	{
		ac[i] = key[(rand() % 4)];
	}

	printf("\n 타일의 개수를 입력해주세요.(MAX 50) : ");
	scanf("%d", &i);
	srand(time(NULL));
	system("cls");

	printf("\n    ");
	for (; n < i; n++)
	{
		if (ac[n] == 75)
			printf("◁    ");
		else if (ac[n] == 80)
			printf("▽    ");
		else if (ac[n] == 77)
			printf("▷    ");
		else if (ac[n] == 72)
			printf("△    ");

		if ((n % 10) == 9)
			printf("\n\n    ");
	}
	printf("\n");
	n = 0;
	gotoxy(4, 11);
	printf("남은 타일: %d ", i);

	l = 0;
	hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadFunction, NULL, 0, (unsigned*)&dwThreadID);

	//게임 플레이
	while (1)
	{
		if (n == i)
			break;

		c = getch();
		c = getch();
		if (c == ac[n])
		{
			n++;
			m = n;
			for (; m>0; m--)
			{
				if (m % 10 == 0)
					gotoxy(49, (m / 10) * 2 - 1);
				else
					gotoxy(5 * (m % 10) - 1, 2 * (m / 10) + 1);
				
				printf("       ");
			}
		}
		gotoxy(15, 11);
		printf("%d ", (i-n));
	}
	l = 1;
	printf("\n게임이 끝났습니다. 2초 후 종료합니다.\n");
	Sleep(2000);

}
void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

unsigned int WINAPI ThreadFunction(void *arg)
{
	int t = 0;

	while (1)
	{
		if (l == 1)
			return 0;

		gotoxy(18,11);
		printf("시간: %d", t++);
		Sleep(1000);
		
		if (l == 1)
			return 0;
	}

	return 0;
}

//현재 단계 맞추면 숫자가 올라가고 틀리면 안 올라감
//일단 누르면 무조건 맞춘 수가 출력됨

/*
해야할 것
gotoxy
*/