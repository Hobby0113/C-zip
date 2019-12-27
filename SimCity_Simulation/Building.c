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
		printf("�� ���� ��...\n");
		if (*Money < 10000)
			printf("���� �ڻ�: %10d����\n", *Money);
		else
		{
			if (*Money % 10000 == 0)
				printf("���� �ڻ�: %10d���\n", *Money / 10000);
			else
				printf("���� �ڻ�: %3d��%5d����\n", *Money / 10000, *Money % 10000);
		}

		if ((500 + InCome) < 10000)
			printf("���� ����: %d����/s\n", (500 + InCome));
		else
		{
			if ((500 + InCome) % 10000 == 0)
				printf("���� ����: %d���/s\n", (500 + InCome) / 10000);
			else
				printf("���� ����: %d�� %d����/s\n", (500 + InCome) / 10000, (500 + InCome) % 10000);
		}
		
		printf("�޴��� �̿��Ϸ��� SPACE�� �����ּ���.\n");
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
	printf("1. �̵��ϱ�        2. ��������        |\n");
	printf("3. �� �� ����      4. �� �� ����      |\n");
	printf("5. �����ϱ� & �� ������               |\n");
	printf("6. ������ü����    7. �����ϱ�        |\n");
	printf("8. �� ����         10. ����           |\n");
	if(Money < 10000)
		printf("���� �ڻ�:  %10d����            |\n", Money);
	else
	{
		if(Money %10000 == 0)
			printf("���� �ڻ�:  %10d���            |\n", Money / 10000);
		else
			printf("���� �ڻ�:  %3d��%5d����            |\n", Money / 10000, Money % 10000);
	}
	printf("---------------------------------------\n");

	printf("�Է�: ");
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
		printf("������ ��ġ: ������\n");
	else
	{
		if(BTEMP->Value == 1)
			printf("������ ��ġ: %2d�� ����Ʈ (�ּ�: 0x%p)\n", BTEMP->Building_Num, BTEMP);
		else
			printf("������ ��ġ: %2d�� ���� (�ּ�: 0x%p)\n", BTEMP->Building_Num, BTEMP);
	}
		

	if (BTEMP->Header_Room != NULL)
	{
		sizeF = _msize(BTEMP->Header_Room) / sizeof(ROOM***);
		for (i = sizeF - 1; i >= 0; i--)
		{
			gotoxy(X, Y++);
			printf("----------%2d��----------\n", i + 1);
			RTEMP = BTEMP->Header_Room[i];
			if (RTEMP != NULL)
			{
				sizeR = _msize(RTEMP) / sizeof(ROOM*);
				for (j = 0; j < sizeR; j++)
				{
					gotoxy(X, Y++);
					printf("%dȣ  ", (i + 1) * 100 + j + 1);
					if (RTEMP[j] == NULL)
						printf("(�� ��)\n");
					else
						printf("%s (�漼: %d)\n", RTEMP[j]->Name, RTEMP[j]->Value);
				}
			}
		}
	}
	else
	{
		gotoxy(X, Y++);
		if (BTEMP->Building_Num != 0)
			printf("���� �����ϴ�!\n");
	}
}

long Make_Building(BUILDING *Header_building,long *Money, FILE *FP)
{
	int k = 1, i = 0;
	char YN = 0;
	BUILDING *newbuilding = (BUILDING*)malloc(sizeof(BUILDING)); // �� ���� �Ҵ�
	BUILDING *Last = Header_building; // ������ building�� ã�� ������

	while (Last->Next != NULL)
		Last = Last->Next;

	k = Last->Building_Num + 1;
	// ������ ��带 ã�� �ο��� Num���

	newbuilding->Building_Num = k;
	newbuilding->Value = 0;
	newbuilding->Header_Room = NULL;
	newbuilding->Next = NULL;

	printf("���� ������ �ǹ��� %d���Դϴ�.\n", k);
	printf("�ʿ��� �ݾ���\n");
	printf("����Ʈ: 50����Դϴ�.\n");
	printf("  ����: 30����Դϴ�.\n");
	printf("�ǹ��� �����ðڽ��ϱ�? (Y/N)\n�Է�: ");

	YN = getchar();
	if (YN == 'y' || YN == 'Y')
	{
		printf("1. ����Ʈ 2. ����\n�Է�:");
		i = get_num();
		if (i == 1)
			newbuilding->Value = Make_APT(Money, FP, k);
		else if (i == 2)
			newbuilding->Value = Make_House(Money, FP, k);
	}
	else
		printf("����Ͽ����ϴ�.\n");

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
		printf("���� �����մϴ�!\n");
		return 0;
	}
	else
	{
		printf("%d��(����Ʈ)�� ��������ϴ�.\n", k);
		*Money -= M_Add_APT;
		fprintf(FP, "%d�� ����Ʈ �Ǽ�\n", k);
		return 1;
	}

}
int Make_House(long *Money, FILE *FP, int k)
{
	if (*Money < M_Add_HOUSE)
	{
		printf("���� �����մϴ�!\n");
		return 0;
	}
	else
	{
		printf("%d��(����)�� ��������ϴ�.\n", k);
		*Money -= M_Add_HOUSE;
		fprintf(FP, "%d�� ���� �Ǽ�\n", k);
		return 2;
	}
}
BUILDING *My_Location(BUILDING *Header, FILE *FP)
{
	int i = 0;
	BUILDING *TEMP = Header;

	printf("�� ������ ���ðڽ��ϱ�? : ");
	i = get_num();

	while (TEMP->Building_Num != i)
	{
		TEMP = TEMP->Next;
		if (TEMP == NULL)
		{
			printf("%d���� �����ϴ�.\n", i);
			TEMP = Header;
			break;
		}
	}

	if (TEMP->Building_Num == 0)
	{
		printf("�����Ƿ� �̵��մϴ�.\n");
		fprintf(FP, "�����Ƿ� �̵�\n");
	}
	else
	{
		printf("%d������ �̵��մϴ�.\n", TEMP->Building_Num);
		fprintf(FP, "%d������ �̵�\n", TEMP->Building_Num);
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
		printf("���� ��ġ: %2d�� (�ּ�: 0x%p)\n", BTEMP->Building_Num, BTEMP);
		if (BTEMP->Header_Room != NULL)
		{
			sizeF = _msize(BTEMP->Header_Room) / sizeof(ROOM***);
			for (i = sizeF - 1; i >= 0; i--)
			{
				gotoxy(X*(count - 1), Y++);
				printf("----------%2d��----------\n", i + 1);
				RTEMP = BTEMP->Header_Room[i];
				if (RTEMP != NULL)
				{
					sizeR = _msize(RTEMP) / sizeof(ROOM*);
					for (j = 0; j < sizeR; j++)
					{
						gotoxy(X*(count - 1), Y++);
						printf("%dȣ  ", (i + 1) * 100 + j + 1);
						if (RTEMP[j] == NULL)
							printf("(�� ��)\n");
						else
							printf("%s (�漼: %d)\n", RTEMP[j]->Name, RTEMP[j]->Value);
					}
				}
			}
		}
		else
		{
			gotoxy(X*(count - 1), Y++);
			printf("���� �����ϴ�!\n");
		}
		if (count % 3 == 0)
		{
			gotoxy(X*(count - 1), Y++);
			printf("������(����)");
			count = getchar();
			system("cls");
			count = 0;
		}
	}
	fprintf(FP, "���� ��ü ��ȸ\n");
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

	printf("�ɽ�Ƽ�� ���� �� ȯ���մϴ�.\n");
	printf("������ �����е��� City�� ������ �Ǿ� ��ϰ� �˴ϴ�.\n");
	printf("���ν��� �� 80����� �ڻ����� �����մϴ�.\n");
	printf("�ҷ����� �� ������Ʈ ������ SimCity.txt�� �����ͷ� �ҷ��ɴϴ�.\n");

	printf("�ǹ��� ������ ����� ���� �� �⺻������\n");
	printf("500����/s �� ������ �ֽ��ϴ�.\n");
	printf("�� �޴��̿� �߿� ������ �����ϴ�.\n\n");

	printf("1. ���ν��� 2. �ҷ�����\n�Է�: ");
	i = get_num();
	if (i != 1 && i != 2) {
		printf("�߸� �Է��ϼ̽��ϴ�. ���� �����մϴ�.");
		i = 1;
	}
	printf("�����̽��� ������ ������ ���۵˴ϴ�.\n");

	while(next != ' ')
		next = getch();

	return i;
}
char Off(BUILDING *Header, int Money, FILE *FP, FILE *DB)
{
	char YN = 0;
	int i = 0;
	printf("�������� ���� �����ʹ� ������ϴ�.\n");
	printf("�����ϰ� �����Ͻðڽ��ϱ�? (Y/N)\n�Է�: ");

	YN = getchar();
	if (YN == 'y' || YN == 'Y')
	{
		printf("1. ���ξ��� 2. ����� 3. ����\n�Է�: ");
		i = get_num();
		if (i == 1 || i ==2)
			DB = NewFile(Header, Money, DB, FP,i);
		printf("������ �����մϴ�.\n");
	}
	else
		printf("�������� �ʰ� �����մϴ�.\n");

	Log_Start_End(FP, 2);

	return 1;
}
