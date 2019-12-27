#include<stdio.h>
#include<stdlib.h>
#include<curses.h>
//#include<Windows.h> //Sleep
//#include<conio.h> //getch()
#include<time.h>
//#include<process.h> //thread

#define TRUE 1
#define FALSE 0
#define LEFT 68
#define RIGHT 67
#define UP 65
#define DOWN 66

int l=0;

int menu(void);
void play(void);
void gotoxy(int x, int y);
//unsigned int WINAPI ThreadFunction(void *arg);
