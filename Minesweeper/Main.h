#pragma once
#include<stdio.h>
#include<stdlib.h>
//#include<Windows.h>
#include<time.h>
#include <unistd.h>

#define XY 22
#define SIZE (XY-2)
#define TILENUM 81
#define MINENUM (XY)
#define UI_Y (XY+2)

// �ۨ���   Ÿ�� ������ �迭 ��Ģ ����
// ��  ��
// ������

typedef struct{
	struct TILE* NT[8];
	int i;
	char open; //1 ���� 0 ����
} TILE;

//Setting.c
void box(void);
int set_tile(TILE (*T)[SIZE]);
void print_tile(TILE (*T)[SIZE]);
void set_mine(TILE (*T)[SIZE], int *count);
void set_tileP(TILE (*T)[SIZE]);
void count_mine(TILE (*T)[SIZE]);
void print_one_tile(TILE *T, int i, int j);
void print_cover(void);

//Function.c
void gotoxy(int x, int y);
int Random(int x);
int get_num(void);
void play(TILE (*T)[SIZE], int m);
void UI(int m,int t);
int open_tile(TILE *T, int x, int y);
int is_Open(TILE (*T)[SIZE], int x, int y);
void overlap(void);
int is_NULL(TILE *T);
int correct_num(int x, int y);
int is_Zero(TILE *T, int x, int y);
void testF(TILE *T, int x, int y);
void is_Mine(void);
