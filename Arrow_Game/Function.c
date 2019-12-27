#include"Arrow_Game.h"

void play(void) {
	char c = 0,n=0,m=0;
	int arrow[50] = { 0 };

	//HANDLE hThread = NULL;
	//DWORD dwThreadID = NULL;

	n = 0;
	gotoxy(4, 11);
	printf("���� Ÿ��: %d ", i);

	l = 0;
	//hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadFunction, NULL, 0, (unsigned*)&dwThreadID);

	//���� �÷���
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
	printf("\n������ �������ϴ�. 2�� �� �����մϴ�.\n");
	Sleep(2000);

}

void print_arrow(int[] arrow){
  short key[4] = { 72,75,77,80 };

  system("clear");
  srand(time(NULL));
	for (i = 0; i < 50; i++)
	{
		ac[i] = key[(rand() % 4)];
	}

	printf("\n Input Max tile(MAX 50) : ");
	scanf("%d", &i);
	system("clear");

  //print arroew
  //↑→←↓
	printf("\n    ");
	for (; n < i; n++)
	{
		if (ac[n] == 75)
			printf("a    ");
		else if (ac[n] == 80)
			printf("b    ");
		else if (ac[n] == 77)
			printf("c    ");
		else if (ac[n] == 72)
			printf("d    ");

		if ((n % 10) == 9)
			printf("\n\n    ");
	}

	printf("\n");
}

//start to (1,1)
void gotoxy(int x, int y)
{
    printf("\033[%d;%df", y, x);
    fflush(stdout);
}
/*
int _getch(void)
{
    int ch;
    struct termios buf;
    struct termios save;

    tcgetattr(0, &save);
    buf = save;
    buf.c_lflag &= ~(ICANON|ECHO);
    buf.c_cc[VMIN] = 1;
    buf.c_cc[VTIME] = 0;
    tcsetattr(0, TCSAFLUSH, &buf);
    ch = getchar();
    tcsetattr(0, TCSAFLUSH, &save);
    return ch;
}
*/
unsigned int WINAPI ThreadFunction(void *arg)
{
	int t = 0;

	while (1)
	{
		if (l == 1)
			return 0;

		gotoxy(18,11);
		printf("�ð�: %d", t++);
		Sleep(1000);

		if (l == 1)
			return 0;
	}

	return 0;
}
