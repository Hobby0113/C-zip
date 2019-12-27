#include"Arrow_Game.h"

void print_arrow(int *arrow){
	int i = 0, n = 0;
  short key[4] = { 72,75,77,80 };

  system("clear");
  srand(time(NULL));
	for (i = 0; i < 50; i++)
	{
		arrow[i] = key[(rand() % 4)];
	}

	printf("\n Input Max tile(MAX 50) : ");
	scanf("%d", &i);
	system("clear");

  //print arroew
  //↑→←↓
	printf("\n    ");
	for (; n < i; n++)
	{
		if (arrow[n] == RIGHT)
			printf("→    ");
		else if (arrow[n] == LEFT)
			printf("←    ");
		else if (arrow[n] == UP)
			printf("↑    ");
		else if (arrow[n] == DOWN)
			printf("↓    ");

		if ((n % 10) == 9)
			printf("\n\n    ");
	}
}

//Start Game
int main(void) {
	int input = 0;

	while (TRUE) {
		if (input == 1)
			break;
		else if (input == 2)
			break;

		system("clear");
		input = menu();
	}
	return 0;
}

//menu
int menu(void) {
	int input;
	int arrow[50] = { 0 };
	int c = 0;

	initscr();
	printf("1. Play 2. Exit\nSelect: ");
	print_arrow(arrow);
	printf("\n%d %d\n", arrow[2], arrow[4]);
	printf("\n%d", &c);
	scanf("%d", &input);

	return input;
}
