#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<malloc.h>
#include<Windows.h>
#include<time.h>
#include<conio.h>

#define X 44
#define File_Buffer 255
#define DEBUG printf("OK");
#define SPACE	VK_SPACE

#define M_Add_APT 500000
#define M_Add_HOUSE 300000
#define M_Add_Floor 3000
#define M_Sub_Floor 1700
#define M_Add_Room 1500
#define M_Sub_Room 800
#define M_Enter_Room 400

typedef struct BUILDING {
	int Building_Num;
	int Value; // 아파트는 1, 주택은 2
	struct ROOM ***Header_Room;
	struct BUILDING *Next;
} BUILDING;
typedef struct ROOM {
	int Value;
	char *Name;
	char Password[9];
} ROOM;

int Header_Setting(BUILDING *Header);
void Log_Start_End(FILE *FP, int mode); // 1시작, 2 종료
void Status(long *Money, long InCome);
long Total_Money(BUILDING *Header);
int Menu(long Money);
void Print_Building(BUILDING *ME);

//Building
long Make_Building(BUILDING *Header_building, long *Money, FILE *FP);
int Make_APT(long *Money, FILE *FP, int k);
int Make_House(long *Money, FILE *FP, int k);
BUILDING *My_Location(BUILDING *ME, FILE *FP);

//Floor
long Change_Floor(BUILDING *ME, long *Money, FILE *FP);
long First_Floor(BUILDING *ME, FILE *FP);
long Add_Floor(BUILDING *ME, long *Money, FILE *FP);
long Sub_Floor(BUILDING *ME, FILE *FP);

//Room
long Change_Room(BUILDING *ME, long *Money, FILE *FP);
long First_Room(BUILDING *ME, int Floor, FILE *FP);
long Add_Room(BUILDING *ME,int Floor, long *Money, FILE *FP);
long Sub_Room(BUILDING *ME,int Floor, FILE *FP);
long In_Out_Room(BUILDING *ME, long *Money, FILE *FP);
long Enter_Room(BUILDING *ME, FILE *FP);
void Out_Room(BUILDING *ME, FILE *FP);
ROOM *Profile_Room(void);

void Print_ALL(BUILDING *Header_building, FILE *FP);

int Save_DB(void);
FILE *NewFile(BUILDING *Header, int Money, FILE *DB, FILE *LOG, int mode);
//mode 1->새로저장 2->덮어쓰기
FILE *New_OverWrite(int mode);

//FILE
FILE *Input_File(BUILDING *Header_building, int *Money,FILE *FP);
void Input_BFR(BUILDING *Header_building, FILE *FP, long *Money);
int Last_is_Enter(FILE *FP);
int get_num_File(char *Temp, int location);
void Make_File_Building(BUILDING *Header_building, int Bnum, char Temp[]);
void Make_File_Floor(BUILDING *Header_building, int Bnum, int Fnum);
void Make_File_Room(BUILDING *Header_building, int Bnum, int Fnum, int Rnum);
void File_Profile(BUILDING *Header_building, char Temp[], int Bnum, int Fnum, int Rnum);

int info(void);
char Off(BUILDING *Header, int Money, FILE *FP, FILE *DB);

//Function.c
int get_num(void);
void gotoxy(int x, int y);
int Random(int x);
int My_strlen(char *string);
int My_strcmp(char *string1, char *string2);
void get_n_string(char *string, int size);
void get_n_string_void(char *string, int size);
int Find_pattern(char *string, char *pattern, int mode);
// 모드 1: 패턴이 있는지(실패시 0), 2: 몇개 있는지, 3: 최초의 패턴이 어디에 있는지(실패시 -1), 미(오)입력 시: -1
int check(char *string, char *pattern);
int check_first(char *string1, char *string2);
int File_Check(FILE *Fp);