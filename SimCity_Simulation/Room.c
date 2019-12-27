#include"Main.h"

long Change_Room(BUILDING *ME, long *Money, FILE *FP)
{
	char YN = 'Y';
	int i = 0, floor = 0;

	printf("�� ���� ���� �����Ͻðڽ��ϱ�?\n�Է�: ");
	floor = get_num(); // �����Ϸ��� ��
	if (ME->Header_Room != NULL)
		i = _msize(ME->Header_Room) / sizeof(ROOM**); // �� ��

	printf("������ ���� %d���Դϴ�.\n", floor);
	printf("���� �� ���� �ϳ��� ���氡���մϴ�.\n");
	printf("�� +1 : -%d����\n", M_Add_Room);
	printf("�� -1 :  +%d����\n", M_Sub_Room);
	printf("�� ���� �����Ͻðڽ��ϱ�? (Y/N)\n�Է�: ");
	YN = getchar();

	if (YN == 'y' || YN == 'Y')
	{
		if (floor <= i && floor > 0)
		{
			if (ME->Header_Room[floor - 1] == NULL)
				if (*Money >= M_Add_Room)
					*Money += First_Room(ME, floor, FP);
				else
					printf("���� �����մϴ�.\n");
			else
			{
				printf("1. �ø��� 2. ���̱�\n�Է�: ");
				i = get_num();
				if (i == 1)
					*Money += Add_Room(ME, floor, Money, FP);
				else if (i == 2)
					*Money += Sub_Room(ME, floor, FP);
			}
		}
		else
			printf("%d���� �����ϴ�.", floor);
	}
	else
		printf("����Ͽ����ϴ�.\n");
	return 0;
}
long First_Room(BUILDING *ME, int Floor, FILE *FP)
{
	int i = _msize(ME->Header_Room) / sizeof(ROOM**);

	printf("���� ������� ���� �����ϴ�.\n");
	ME->Header_Room[Floor - 1] = (ROOM**)malloc(sizeof(ROOM*));
	memset(ME->Header_Room[Floor - 1], 0x0, sizeof(ROOM*));
	if (ME->Header_Room[Floor - 1] == NULL)
		printf("�����߽��ϴ�.\n");
	else
	{
		printf("�� �����մϴ�.\n");
		fprintf(FP, "%d��: %d�� �� ����\n", ME->Building_Num, i);
		return -M_Add_Room;
	}

	return 0;
}
long Add_Room(BUILDING *ME, int Floor, long *Money, FILE *FP)
{
	int or_size = _msize(ME->Header_Room[Floor - 1]) / sizeof(ROOM**);
	ROOM **RTEMP = NULL;
	int value = ME->Value;

	if (value == 1)
	{
		if (or_size < 5)
		{
			if (*Money >= M_Add_Room)
			{
				printf("���� %d���� ���� %d���Դϴ�.\n", Floor, or_size);
				ME->Header_Room[Floor - 1] = (ROOM**)realloc(ME->Header_Room[Floor - 1], sizeof(ROOM*)*(or_size + 1));
				printf("%d�� -> %d������ ����Ǿ����ϴ�.\n", or_size, or_size + 1);
				fprintf(FP, "%d�� %d��: �� ���� %d�� -> %d��\n", ME->Building_Num, Floor, or_size, or_size + 1);
				RTEMP = ME->Header_Room[Floor - 1];
				RTEMP[or_size] = NULL;
				return -M_Add_Room;
			}
			else
				printf("���� �����մϴ�.");
		}
		else
			printf("�� �̻� �߰��� �� �����ϴ�.\n");
	}
	else if (value == 2)
	{
		if (or_size < 3)
		{
			if (*Money >= M_Add_Room)
			{
				printf("���� %d���� ���� %d���Դϴ�.\n", Floor, or_size);
				ME->Header_Room[Floor - 1] = (ROOM**)realloc(ME->Header_Room[Floor - 1], sizeof(ROOM*)*(or_size + 1));
				printf("%d�� -> %d������ ����Ǿ����ϴ�.\n", or_size, or_size + 1);
				fprintf(FP, "%d�� %d��: �� ���� %d�� -> %d��\n", ME->Building_Num, Floor, or_size, or_size + 1);
				RTEMP = ME->Header_Room[Floor - 1];
				RTEMP[or_size] = NULL;
				return -M_Add_Room;
			}
			else
				printf("���� �����մϴ�.");
		}
		else
			printf("�� �̻� �߰��� �� �����ϴ�.\n");
	}

	return 0;
}
long Sub_Room(BUILDING *ME, int Floor, FILE *FP)
{
	int or_size = _msize(ME->Header_Room[Floor - 1]) / sizeof(ROOM**);
	ROOM **RTEMP = NULL;

	RTEMP = ME->Header_Room[Floor - 1];

	printf("���� %d���� ���� %d���Դϴ�.\n", Floor, or_size);
	free(RTEMP[or_size - 1]);
	ME->Header_Room[Floor - 1] = (ROOM**)realloc(ME->Header_Room[Floor - 1], sizeof(ROOM*)*(or_size - 1));
	printf("%d�� -> %d������ ����Ǿ����ϴ�.\n", or_size, or_size - 1);
	fprintf(FP, "%d�� %d��: �� ���� %d�� -> %d��\n", ME->Building_Num, Floor, or_size, or_size - 1);

	return M_Sub_Room;
}

long In_Out_Room(BUILDING *ME, long *Money, FILE *FP)
{
	int i = 0, result = 0;
	printf("���� �� %d������ ����� �ʿ��մϴ�.\n", M_Enter_Room);
	printf("�� �����µ� �ʿ��� ����� �����ϴ�.\n");

	printf("1. ���� 2. ������\n�Է�: ");
	i = get_num();
	if (i == 1)
		if (*Money > 400)
			result += Enter_Room(ME, FP);
		else
			printf("���� �����մϴ�.\n");
	else if (i == 2)
		Out_Room(ME, FP);
	else
		printf("�Է��� �߸��Ǿ����ϴ�.\n����մϴ�.\n");

	return result;
}
long Enter_Room(BUILDING *ME, FILE *FP)
{
	int num = 0, TF = 0;
	int sizeF = 0, sizeR = 0;
	ROOM **Floor = NULL;

	printf("�� ȣ�� �����մϱ�?\n�Է�: ");
	num = get_num();

	if (ME->Header_Room != NULL)
	{
		sizeF = _msize(ME->Header_Room) / sizeof(ROOM**);
		if ((num / 100) <= sizeF && (num / 100) > 0)
		{
			sizeF = num / 100;
			Floor = ME->Header_Room[sizeF - 1];
			if (Floor != NULL)
			{
				sizeR = _msize(Floor) / sizeof(ROOM*);
				if ((num % 100) <= sizeR && (num % 100) > 0)
				{
					sizeR = num % 100;
					TF = 1;
					if (Floor[sizeR - 1] == NULL)
					{
						Floor[sizeR - 1] = Profile_Room();
						if (Floor[sizeR - 1] != NULL)
						{
							printf("���� ����!");
							fprintf(FP, "%d�� %dȣ ����(PW : %s )\n", ME->Building_Num, num, Floor[sizeR - 1]->Password);
							return -M_Enter_Room;
						}
						else
							printf("���� ����!");
					}
					else
						printf("�� ���� �ƴմϴ�.");
				}
			}
		}
	}

	if (TF != 1)
		printf("%dȣ�� ã�� ���߽��ϴ�.\n", num);

	return 0;
}
void Out_Room(BUILDING *ME, FILE *FP)
{
	int i = 0, num = 0, TF = 0;
	int sizeF = 0, sizeR = 0;
	char PW[9] = { 0 };
	ROOM *NewRoom = NULL;
	ROOM **Floor = NULL;

	printf("�� ȣ�� �����ϱ�?\n�Է�: ");
	num = get_num();

	if (ME->Header_Room != NULL)
	{
		sizeF = _msize(ME->Header_Room) / sizeof(ROOM**);
		if ((num / 100) <= sizeF && (num / 100) > 0)
		{
			sizeF = num / 100;
			Floor = ME->Header_Room[sizeF - 1];
			if (Floor != NULL)
			{
				sizeR = _msize(Floor) / sizeof(ROOM*);
				if ((num % 100) <= sizeR && (num % 100) > 0)
				{
					sizeR = num % 100;
					TF = 1;
					if (Floor[sizeR - 1] != NULL)
					{
						printf("��й�ȣ�� �Է��ϼ���.\n: ");
						get_n_string_void(PW, 9);
						printf("\n");
						if (Find_pattern(PW, Floor[sizeR - 1]->Password, 1) == 1)
						{
							printf("%d�� �������ϴ�.\n", num);
							fprintf(FP, "%d�� %dȣ �̻�\n", ME->Building_Num, num);
							Floor[sizeR - 1] = NULL;
						}
						else
							printf("��й�ȣ�� Ʋ�Ƚ��ϴ�!\n");
					}
					else
						printf("�̹� �� ���Դϴ�.");
				}
			}
		}
	}

	if (TF != 1)
		printf("%dȣ�� ã�� ���߽��ϴ�.\n", num);
}
ROOM *Profile_Room(void)
{
	int size = 0, name_size = 0, i = 0;
	ROOM* New_Room = (ROOM*)malloc(sizeof(ROOM));

	printf("������ �̸��� ����: ");
	name_size = get_num();
	New_Room->Name = (char*)malloc((sizeof(char)*(2 * name_size)) + 1);

	printf("������ �̸�: ");
	get_n_string(New_Room->Name, (2 * name_size));

	printf("�漼(1~500���� �� ����): ");
	New_Room->Value = Random(500)+1;
	printf("%d����\n", New_Room->Value);

	printf("��й�ȣ(����,���� �ִ�8��): ");
	get_n_string(New_Room->Password, 8);

	return New_Room;
}