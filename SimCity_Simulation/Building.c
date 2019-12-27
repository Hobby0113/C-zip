#include"Main.h"

int Header_Setting(BUILDING *Header)
{
	Header->Value = 0;
	Header->Next = NULL;
	Header->Building_Num = 0;
	Header->Header_Room = NULL;

	return Header->Building_Num;
}
void Status(long *Money, long InCome)
{
	int i = 0, count = 0;
	while (!GetAsyncKeyState(SPACE))
	{

		gotoxy(1, 10);
		printf("돈 버는 중...\n");
		if (*Money < 10000)
			printf("현재 자산: %10d만원\n", *Money);
		else
		{
			if (*Money % 10000 == 0)
				printf("현재 자산: %10d억원\n", *Money / 10000);
			else
				printf("현재 자산: %3d억%5d만원\n", *Money / 10000, *Money % 10000);
		}

		if ((500 + InCome) < 10000)
			printf("현재 수입: %d만원/s\n", (500 + InCome));
		else
		{
			if ((500 + InCome) % 10000 == 0)
				printf("현재 수입: %d억원/s\n", (500 + InCome) / 10000);
			else
				printf("현재 수입: %d억 %d만원/s\n", (500 + InCome) / 10000, (500 + InCome) % 10000);
		}
		
		printf("메뉴를 이용하려면 SPACE를 눌러주세요.\n");
		printf("[         ]");


		gotoxy(2, 14);
		(count)++;

		
		i = count;
		while ((i--) > 0)
			printf("$");

		Sleep(100);
		if (count % 10 == 9)
		{
			*Money += (500+InCome);
			count = 0;
		}
	}
}
long Total_Money(BUILDING *Header)
{
	int sizeF = 0, sizeR = 0, i = 0, j = 0;
	long result = 0;
	BUILDING *BTEMP = Header;
	ROOM **RTEMP = NULL;

	while (BTEMP->Next != NULL)
	{
		BTEMP = BTEMP->Next;
		if (BTEMP->Header_Room != NULL)
		{
			sizeF = _msize(BTEMP->Header_Room) / sizeof(ROOM***);
			for (i = sizeF - 1; i >= 0; i--)
			{
				RTEMP = BTEMP->Header_Room[i];
				if (RTEMP != NULL)
				{
					sizeR = _msize(RTEMP) / sizeof(ROOM*);
					for (j = 0; j < sizeR; j++)
					{
						if (RTEMP[j] != NULL)
							result += RTEMP[j]->Value;
					}
				}
			}
		}
	}

	return result;
}
int Menu(long Money)
{
	int i = 0;

	gotoxy(1, 1);
	printf("MENU-----------------------------------\n");
	printf("1. 이동하기        2. 빌딩짓기        |\n");
	printf("3. 층 수 변경      4. 방 수 변경      |\n");
	printf("5. 입주하기 & 방 나가기               |\n");
	printf("6. 빌딩전체보기    7. 저장하기        |\n");
	printf("8. 돈 벌기         10. 종료           |\n");
	if(Money < 10000)
		printf("현재 자산:  %10d만원            |\n", Money);
	else
	{
		if(Money %10000 == 0)
			printf("현재 자산:  %10d억원            |\n", Money / 10000);
		else
			printf("현재 자산:  %3d억%5d만원            |\n", Money / 10000, Money % 10000);
	}
	printf("---------------------------------------\n");

	printf("입력: ");
	i = get_num();

	return i;
}
void Print_Building(BUILDING *ME)
{
	int Y = 1, sizeF = 0, sizeR = 0, sizeM = 0;
	int i = 0, j = 0, k = 0;
	BUILDING *BTEMP = ME;
	ROOM **RTEMP = NULL;

	system("cls");
	gotoxy(X, Y++);
	if (ME->Building_Num == 0)
		printf("※현재 위치: 관리실\n");
	else
	{
		if(BTEMP->Value == 1)
			printf("※현재 위치: %2d동 아파트 (주소: 0x%p)\n", BTEMP->Building_Num, BTEMP);
		else
			printf("※현재 위치: %2d동 주택 (주소: 0x%p)\n", BTEMP->Building_Num, BTEMP);
	}
		

	if (BTEMP->Header_Room != NULL)
	{
		sizeF = _msize(BTEMP->Header_Room) / sizeof(ROOM***);
		for (i = sizeF - 1; i >= 0; i--)
		{
			gotoxy(X, Y++);
			printf("----------%2d층----------\n", i + 1);
			RTEMP = BTEMP->Header_Room[i];
			if (RTEMP != NULL)
			{
				sizeR = _msize(RTEMP) / sizeof(ROOM*);
				for (j = 0; j < sizeR; j++)
				{
					gotoxy(X, Y++);
					printf("%d호  ", (i + 1) * 100 + j + 1);
					if (RTEMP[j] == NULL)
						printf("(빈 방)\n");
					else
						printf("%s (방세: %d)\n", RTEMP[j]->Name, RTEMP[j]->Value);
				}
			}
		}
	}
	else
	{
		gotoxy(X, Y++);
		if (BTEMP->Building_Num != 0)
			printf("층이 없습니다!\n");
	}
}

long Make_Building(BUILDING *Header_building,long *Money, FILE *FP)
{
	int k = 1, i = 0;
	char YN = 0;
	BUILDING *newbuilding = (BUILDING*)malloc(sizeof(BUILDING)); // 새 빌딩 할당
	BUILDING *Last = Header_building; // 마지막 building을 찾을 포인터

	while (Last->Next != NULL)
		Last = Last->Next;

	k = Last->Building_Num + 1;
	// 마지막 노드를 찾고 부여할 Num계산

	newbuilding->Building_Num = k;
	newbuilding->Value = 0;
	newbuilding->Header_Room = NULL;
	newbuilding->Next = NULL;

	printf("현재 지어질 건물은 %d동입니다.\n", k);
	printf("필요한 금액은\n");
	printf("아파트: 50억원입니다.\n");
	printf("  주택: 30억원입니다.\n");
	printf("건물을 지으시겠습니까? (Y/N)\n입력: ");

	YN = getchar();
	if (YN == 'y' || YN == 'Y')
	{
		printf("1. 아파트 2. 주택\n입력:");
		i = get_num();
		if (i == 1)
			newbuilding->Value = Make_APT(Money, FP, k);
		else if (i == 2)
			newbuilding->Value = Make_House(Money, FP, k);
	}
	else
		printf("취소하였습니다.\n");

	if (newbuilding->Value == 0)
	{
		free(newbuilding);
		newbuilding = NULL;
	}

	Last->Next = newbuilding;

	return 0;
}
int Make_APT(long *Money, FILE *FP, int k)
{
	if (*Money < M_Add_APT)
	{
		printf("돈이 부족합니다!\n");
		return 0;
	}
	else
	{
		printf("%d동(아파트)을 만들었습니다.\n", k);
		*Money -= M_Add_APT;
		fprintf(FP, "%d동 아파트 건설\n", k);
		return 1;
	}

}
int Make_House(long *Money, FILE *FP, int k)
{
	if (*Money < M_Add_HOUSE)
	{
		printf("돈이 부족합니다!\n");
		return 0;
	}
	else
	{
		printf("%d동(주택)을 만들었습니다.\n", k);
		*Money -= M_Add_HOUSE;
		fprintf(FP, "%d동 주택 건설\n", k);
		return 2;
	}
}
BUILDING *My_Location(BUILDING *Header, FILE *FP)
{
	int i = 0;
	BUILDING *TEMP = Header;

	printf("몇 동으로 가시겠습니까? : ");
	i = get_num();

	while (TEMP->Building_Num != i)
	{
		TEMP = TEMP->Next;
		if (TEMP == NULL)
		{
			printf("%d동은 없습니다.\n", i);
			TEMP = Header;
			break;
		}
	}

	if (TEMP->Building_Num == 0)
	{
		printf("관리실로 이동합니다.\n");
		fprintf(FP, "관리실로 이동\n");
	}
	else
	{
		printf("%d동으로 이동합니다.\n", TEMP->Building_Num);
		fprintf(FP, "%d동으로 이동\n", TEMP->Building_Num);
	}

	return TEMP;
}

void Print_ALL(BUILDING *Header_building, FILE *FP)
{
	int Y = 1, sizeF = 0, sizeR = 0;
	int i = 0, j = 0, k = 0, count = 0;
	BUILDING *BTEMP = Header_building;
	ROOM **RTEMP = NULL;
	ROOM *RTEMP2 = NULL;

	system("cls");
	while (BTEMP->Next != NULL)
	{
		BTEMP = BTEMP->Next;
		Y = 1;
		count++;
		gotoxy(X*(count - 1), Y++);
		printf("현재 위치: %2d동 (주소: 0x%p)\n", BTEMP->Building_Num, BTEMP);
		if (BTEMP->Header_Room != NULL)
		{
			sizeF = _msize(BTEMP->Header_Room) / sizeof(ROOM***);
			for (i = sizeF - 1; i >= 0; i--)
			{
				gotoxy(X*(count - 1), Y++);
				printf("----------%2d층----------\n", i + 1);
				RTEMP = BTEMP->Header_Room[i];
				if (RTEMP != NULL)
				{
					sizeR = _msize(RTEMP) / sizeof(ROOM*);
					for (j = 0; j < sizeR; j++)
					{
						gotoxy(X*(count - 1), Y++);
						printf("%d호  ", (i + 1) * 100 + j + 1);
						if (RTEMP[j] == NULL)
							printf("(빈 방)\n");
						else
							printf("%s (방세: %d)\n", RTEMP[j]->Name, RTEMP[j]->Value);
					}
				}
			}
		}
		else
		{
			gotoxy(X*(count - 1), Y++);
			printf("층이 없습니다!\n");
		}
		if (count % 3 == 0)
		{
			gotoxy(X*(count - 1), Y++);
			printf("다음장(엔터)");
			count = getchar();
			system("cls");
			count = 0;
		}
	}
	fprintf(FP, "빌딩 전체 조회\n");
}

int info(void)
{
	int next = 0, i = 0;
	printf("ver 1.0\n");
	printf(" ____  _            ____ _ _\n");
	printf("/ ___|(_)_ __ ___  / ___(_) |_ _   _\n");
	printf("\\___ \\| | '_ ` _ \\| |   | | __| | | |\n");
	printf(" ___) | | | | | | | |___| | |_| |_| |\n");
	printf("|____/|_|_| |_| |_|\\____|_|\\__|\\__, |\n");
	printf("                               |___/\n");
	printf("                          Made of C\n\n");

	printf("심시티에 오신 걸 환영합니다.\n");
	printf("앞으로 여러분들은 City의 주인이 되어 운영하게 됩니다.\n");
	printf("새로시작 시 80억원의 자산으로 시작합니다.\n");
	printf("불러오기 시 프로젝트 폴더에 SimCity.txt의 데이터로 불러옵니다.\n");

	printf("건물의 입주한 사람이 없을 시 기본적으로\n");
	printf("500만원/s 의 수입이 있습니다.\n");
	printf("단 메뉴이용 중엔 수입이 없습니다.\n\n");

	printf("1. 새로시작 2. 불러오기\n입력: ");
	i = get_num();
	if (i != 1 && i != 2) {
		printf("잘못 입력하셨습니다. 새로 시작합니다.");
		i = 1;
	}
	printf("스페이스를 누르면 게임이 시작됩니다.\n");

	while(next != ' ')
		next = getch();

	return i;
}
char Off(BUILDING *Header, int Money, FILE *FP, FILE *DB)
{
	char YN = 0;
	int i = 0;
	printf("저장하지 않은 데이터는 사라집니다.\n");
	printf("저장하고 종료하시겠습니까? (Y/N)\n입력: ");

	YN = getchar();
	if (YN == 'y' || YN == 'Y')
	{
		printf("1. 새로쓰기 2. 덮어쓰기 3. 종료\n입력: ");
		i = get_num();
		if (i == 1 || i ==2)
			DB = NewFile(Header, Money, DB, FP,i);
		printf("게임을 종료합니다.\n");
	}
	else
		printf("저장하지 않고 종료합니다.\n");

	Log_Start_End(FP, 2);

	return 1;
}
