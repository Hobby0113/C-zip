#include"Main.h"

void Log_Start_End(FILE *FP, int mode)
{
	time_t timer;
	struct tm Time_log;

	timer = time(NULL);
	localtime_s(&Time_log, &timer);
	if (mode == 1)
		fprintf(FP, "���� �ð�: %d.%2d.%2d %d:%2d\n", Time_log.tm_year + 1900, Time_log.tm_mon + 1, Time_log.tm_mday, Time_log.tm_hour, Time_log.tm_min);
	else if (mode == 2)
		fprintf(FP, "���� �ð�: %d.%2d.%2d %d:%2d\n\n", Time_log.tm_year + 1900, Time_log.tm_mon + 1, Time_log.tm_mday, Time_log.tm_hour, Time_log.tm_min);
}
int Save_DB(void)
{
	int i = 0;
	printf("1. ���ξ��� 2. ����� 3. ���\n�Է�: ");
	i = get_num();

	return i;
}
FILE *NewFile(BUILDING *Header, int Money, FILE *DB, FILE *LOG, int mode)
{
	int  sizeF = 0, sizeR = 0;
	int i = 0, j = 0;
	char FName[50] = { 0 };
	BUILDING *BTEMP = Header;
	ROOM **RTEMP = NULL;
	ROOM *RTEMP2 = NULL;
	FILE *NewDB;

	NewDB = New_OverWrite(mode);
	fprintf(NewDB, "�ڻ� %d\n", Money);

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
						if (RTEMP[j] == NULL)
							fprintf(NewDB, "%d��(%d) %dȣ (�� ��)\n", BTEMP->Building_Num, BTEMP->Value,(i + 1) * 100 + j + 1);
						else
							fprintf(NewDB, "%d��(%d) %dȣ name: %s (PW: %s ) �漼: %d\n", BTEMP->Building_Num, BTEMP->Value, (i + 1) * 100 + j + 1, RTEMP[j]->Name, RTEMP[j]->Password, RTEMP[j]->Value);
					}
				}
			}
		}
	}

	printf("���� �Ϸ�\n");
	fprintf(LOG, "������ ��������\n");

	return NewDB;
}
FILE *New_OverWrite(int mode)
{
	char FName[50] = { 0 };
	FILE *NewDB = NULL;

	if (mode == 1)
		printf("���� ������ ������ �̸��� �Է����ּ���.\n");
	else if (mode == 2)
		printf("��� ������ �̸��� �Է����ּ���.\n");

	printf("ex)NewFile.txt\n-> ");
	get_n_string(FName, 50);
	if (Find_pattern(FName, ".txt", 3) != My_strlen(FName) - 4)
	{
		int i = My_strlen(FName);
		FName[i++] = '.';
		FName[i++] = 't';
		FName[i++] = 'x';
		FName[i] = 't';
	}

	if (mode == 1)
		NewDB = fopen(FName, "w+");
	else if (mode == 2)
	{
		NewDB = fopen(FName, "r+");
		if (NewDB == NULL)
		{
			printf("������ �������� �ʽ��ϴ�.\n���� �����մϴ�.");
			NewDB = fopen(FName, "w+");
		}
	}

	return NewDB;
}

FILE *Input_File(BUILDING *Header_building, int *Money, FILE *LOG)
{

	char next = 0, FName[50] = { 0 };
	FILE *FP = NULL;

	printf("�ҷ��� ������ �̸��� �Է����ּ���.\n");
	printf("ex) NewFile.txt\n-> ");

	get_n_string(FName, 50);
	if (Find_pattern(FName, ".txt", 3) != My_strlen(FName) - 4)
	{
		int i = My_strlen(FName);
		FName[i++] = '.';
		FName[i++] = 't';
		FName[i++] = 'x';
		FName[i] = 't';
	}

	FP = fopen(FName, "r+");
	if (FP == NULL)
	{
		printf("������ �������� �ʽ��ϴ�.\n���� �����մϴ�.");
		FP = fopen(FName, "w+");
		return FP;
	}

	Last_is_Enter(FP);

	printf("DB ����\n");

	Input_BFR(Header_building, FP, Money);

	fprintf(LOG, "������ �ҷ�����\n");
	printf("DB�� �ҷ��Խ��ϴ�.\n�����̽��� ������ �Ѿ�ϴ�.");
	while (next != ' ')
		next = getch();

	return FP;
}
void Input_BFR(BUILDING *Header_building, FILE *FP, long *Money)
{
	char Temp[File_Buffer] = { 0 };
	int Bnum = 0, Fnum = 0, Rnum = 0, location = 0, FMoney = 0;

	fgets(Temp, File_Buffer, FP);
	if (Find_pattern(Temp, "�ڻ�", 2) == 1) {
		location = Find_pattern(Temp, "�ڻ�", 3);
		FMoney = get_num_File(Temp, My_strlen(Temp));;
		*Money = FMoney;
		printf("�ڻ�: %d\n", FMoney);
	}
	else
		printf("�ڻ꿡 ���� �����Ͱ� �����ϴ�.\n�⺻������ ��ü�մϴ�.\n");

	while (!feof(FP))
	{
		fgets(Temp, File_Buffer, FP);
		//printf("%s%d\n",Temp,My_strlen(Temp));
		if (Temp[My_strlen(Temp) - 1] == '\n') {
			if (Find_pattern(Temp, "��", 2) == 1 && Find_pattern(Temp, "ȣ", 2) == 1)
			{
				location = Find_pattern(Temp, "��", 3);
				Bnum = get_num_File(Temp, location);
				location = Find_pattern(Temp, "ȣ", 3);
				Fnum = get_num_File(Temp, location);
				Rnum = Fnum % 100;
				Fnum = Fnum / 100;
				//printf("%d�� %dȣ\n", Bnum, Fnum*100+ Rnum);
				if (Bnum != 0 && Fnum != 0 && Rnum != 0)
				{
					Make_File_Building(Header_building, Bnum, Temp);
					Make_File_Floor(Header_building, Bnum, Fnum);
					Make_File_Room(Header_building, Bnum, Fnum, Rnum);
					if (Find_pattern(Temp, "name: ", 2) == 1 && Find_pattern(Temp, "(PW: ", 2) == 1 && Find_pattern(Temp, ") �漼: ", 2) == 1)
						File_Profile(Header_building, Temp, Bnum, Fnum, Rnum);
				}
			}

		}
		Temp[0] = '\0';
	}
}
int Last_is_Enter(FILE *FP)
{
	char File_end = 0;
	long Fposition = 0;
	fseek(FP, 0, SEEK_END);
	fputs("\n", FP);
	fseek(FP, 0, SEEK_SET);

	return 0;
}
int get_num_File(char *Temp, int location)
{
	int i = 0, result = 0, n = 1;
	for (i = location - 1; i >= 0; i--)
	{
		if (*(Temp + i) >= '0' && *(Temp + i) <= '9')
		{
			result += (*(Temp + i) - '0') * n;
			n *= 10;
		}

		if (*(Temp + i) == ' ')
			break;
	}
	//printf("%d", result);
	return result;
}
void Make_File_Building(BUILDING *Header_building, int Bnum, char Temp[])
{
	int size = 0;
	BUILDING *TEMP = Header_building;
	BUILDING *newbuilding = NULL; // �� ���� �Ҵ�

								  //�ǹ�
	while (TEMP->Next != NULL)
		TEMP = TEMP->Next;
	size = TEMP->Building_Num;

	if (size < Bnum)
	{
		for (; size < Bnum; size++)
		{
			newbuilding = (BUILDING*)malloc(sizeof(BUILDING));
			newbuilding->Building_Num = size + 1;
			if (Find_pattern(Temp, "��(1)", 1) == 1)
				newbuilding->Value = 1;
			if (Find_pattern(Temp, "��(2)", 1) == 1)
				newbuilding->Value = 2;
			newbuilding->Header_Room = NULL;
			newbuilding->Next = NULL;

			TEMP->Next = newbuilding;
			TEMP = TEMP->Next;
		}
	}
}
void Make_File_Floor(BUILDING *Header_building, int Bnum, int Fnum)
{
	int or_size = 0;
	BUILDING *TEMP = Header_building;

	while (TEMP->Building_Num != Bnum)
		TEMP = TEMP->Next;
	//�ش� ���� ����

	if (TEMP->Header_Room == NULL)
	{
		TEMP->Header_Room = (ROOM***)malloc(sizeof(ROOM**)*Fnum);
		memset(TEMP->Header_Room, 0x0, sizeof(ROOM**)*Fnum);
	}
	else
	{
		or_size = _msize(TEMP->Header_Room) / sizeof(ROOM**);
		if (or_size < Fnum)
		{
			TEMP->Header_Room = (ROOM***)realloc(TEMP->Header_Room, sizeof(ROOM**)*Fnum);
			while (or_size < Fnum)
				TEMP->Header_Room[or_size++] = NULL;
		}
	}
}
void Make_File_Room(BUILDING *Header_building, int Bnum, int Fnum, int Rnum)
{
	int or_size = 0;
	BUILDING *TEMP = Header_building;
	ROOM **RTEMP = NULL;

	while (TEMP->Building_Num != Bnum)
		TEMP = TEMP->Next;
	//�ش� ���� ����

	if (TEMP->Header_Room[Fnum - 1] == NULL)
	{
		TEMP->Header_Room[Fnum - 1] = (ROOM**)malloc(sizeof(ROOM*)*Rnum);
		memset(TEMP->Header_Room[Fnum - 1], 0x0, sizeof(ROOM*)*Rnum);
	}
	else
	{
		or_size = _msize(TEMP->Header_Room[Fnum - 1]) / sizeof(ROOM*);
		if (or_size < Rnum)
		{
			TEMP->Header_Room[Fnum - 1] = (ROOM**)realloc(TEMP->Header_Room[Fnum - 1], sizeof(ROOM*)*Rnum);
			RTEMP = TEMP->Header_Room[Fnum - 1];
			while (or_size < Rnum)
				RTEMP[or_size++] = NULL;
		}
	}
}
void File_Profile(BUILDING *Header_building, char Temp[], int Bnum, int Fnum, int Rnum)
{
	BUILDING *ME = Header_building;
	ROOM **RTEMP = NULL;
	FILE *TEMP = fopen("TEMP.txt", "w+");

	fputs(Temp, TEMP);
	fseek(TEMP, 0, SEEK_SET);

	while (ME->Building_Num != Bnum)
		ME = ME->Next;

	RTEMP = ME->Header_Room[Fnum - 1];
	RTEMP[Rnum - 1] = (ROOM*)malloc(sizeof(ROOM));
	RTEMP[Rnum - 1]->Name = (char*)malloc(sizeof(char) * 100);
	fscanf(TEMP, "%*s %*s %*s %s %*s %s %*s %*s %d", RTEMP[Rnum - 1]->Name, RTEMP[Rnum - 1]->Password, &(RTEMP[Rnum - 1]->Value));


}