#include"Main.h"

long Change_Floor(BUILDING *ME, long *Money, FILE *FP)
{
	char YN = 'Y';
	int i = 0;
	BUILDING *TEMP = ME;

	printf("���� ������ �ǹ��� %d���Դϴ�.\n", ME->Building_Num);
	printf("���� �� ���� �� ���� ���氡���մϴ�.\n");
	printf("�� +1 : -%d����\n", M_Add_Floor);
	printf("�� -1 : +%d����\n", M_Sub_Floor);
	printf("�� ���� �����Ͻðڽ��ϱ�? (Y/N)\n�Է�: ");
	YN = getchar();

	if (YN == 'y' || YN == 'Y')
	{
		if (TEMP->Header_Room == NULL)
			if (*Money >= M_Add_Floor)
				*Money += First_Floor(ME, FP);
			else
				printf("���� �����մϴ�.\n");
		else
		{
			printf("1. �ø��� 2. ���̱�\n�Է�: ");
			i = get_num();
			if (i == 1)
				*Money += Add_Floor(ME, Money, FP);
			else if (i == 2)
				*Money += Sub_Floor(ME, FP);
		}
	}
	else
		printf("����Ͽ����ϴ�.\n");

	return 0;
}
long First_Floor(BUILDING *ME, FILE *FP)
{
	printf("���� ������ ���� �����ϴ�.\n");
	ME->Header_Room = (ROOM***)malloc(sizeof(ROOM**));
	memset(ME->Header_Room, 0x0, sizeof(ROOM**));
	if (ME->Header_Room == NULL)
		printf("�����߽��ϴ�.\n");
	else
	{
		printf("1���� �����մϴ�.\n");
		fprintf(FP, "%d��: 1�� ����\n", ME->Building_Num);
		return -M_Add_Floor;
	}

	return 0;
}
long Add_Floor(BUILDING *ME, long *Money, FILE *FP)
{
	int or_size = _msize(ME->Header_Room) / sizeof(ROOM**);
	int value = ME->Value;

	if (value == 1)
	{
		if (or_size < 15)
		{
			if (*Money >= M_Add_Floor)
			{
				printf("���� %d���� %d���Դϴ�.\n", ME->Building_Num, or_size);
				ME->Header_Room = (ROOM***)realloc(ME->Header_Room, sizeof(ROOM**)*(or_size + 1));
				printf("%d�� -> %d������ ����Ǿ����ϴ�.\n", or_size, or_size + 1);
				fprintf(FP, "%d��: %d�� -> %d��\n", ME->Building_Num, or_size, or_size + 1);
				ME->Header_Room[or_size] = NULL;
				return -M_Add_Floor;
			}
			else
				printf("���� �����մϴ�.\n");
		}
		else
			printf("�� �̻� �߰��� �� �����ϴ�.\n");
	}
	else if(value == 2)
	{
		if (or_size < 5)
		{
			if (*Money >= M_Add_Floor)
			{
				printf("���� %d���� %d���Դϴ�.\n", ME->Building_Num, or_size);
				ME->Header_Room = (ROOM***)realloc(ME->Header_Room, sizeof(ROOM**)*(or_size + 1));
				printf("%d�� -> %d������ ����Ǿ����ϴ�.\n", or_size, or_size + 1);
				fprintf(FP, "%d��: %d�� -> %d��\n", ME->Building_Num, or_size, or_size + 1);
				ME->Header_Room[or_size] = NULL;
				return -M_Add_Floor;
			}
			else
				printf("���� �����մϴ�.\n");
		}
		else
			printf("�� �̻� �߰��� �� �����ϴ�.\n");
	}

	return 0;
}
long Sub_Floor(BUILDING *ME, FILE *FP)
{
	int or_size = _msize(ME->Header_Room) / sizeof(ROOM**);

	printf("���� %d���� %d���Դϴ�.\n", ME->Building_Num, or_size);
	free(ME->Header_Room[or_size - 1]);
	ME->Header_Room = (ROOM***)realloc(ME->Header_Room, sizeof(ROOM**)*(or_size - 1));
	printf("%d�� -> %d������ ����Ǿ����ϴ�.\n", or_size, or_size - 1);
	fprintf(FP, "%d��: %d�� -> %d��\n", ME->Building_Num, or_size, or_size - 1);

	return M_Sub_Floor;
}