#include"Main.h"

long Change_Floor(BUILDING *ME, long *Money, FILE *FP)
{
	char YN = 'Y';
	int i = 0;
	BUILDING *TEMP = ME;

	printf("층을 변경할 건물은 %d동입니다.\n", ME->Building_Num);
	printf("층은 한 번에 한 층씩 변경가능합니다.\n");
	printf("층 +1 : -%d만원\n", M_Add_Floor);
	printf("층 -1 : +%d만원\n", M_Sub_Floor);
	printf("층 수를 변경하시겠습니까? (Y/N)\n입력: ");
	YN = getchar();

	if (YN == 'y' || YN == 'Y')
	{
		if (TEMP->Header_Room == NULL)
			if (*Money >= M_Add_Floor)
				*Money += First_Floor(ME, FP);
			else
				printf("돈이 부족합니다.\n");
		else
		{
			printf("1. 늘리기 2. 줄이기\n입력: ");
			i = get_num();
			if (i == 1)
				*Money += Add_Floor(ME, Money, FP);
			else if (i == 2)
				*Money += Sub_Floor(ME, FP);
		}
	}
	else
		printf("취소하였습니다.\n");

	return 0;
}
long First_Floor(BUILDING *ME, FILE *FP)
{
	printf("현재 지어진 층이 없습니다.\n");
	ME->Header_Room = (ROOM***)malloc(sizeof(ROOM**));
	memset(ME->Header_Room, 0x0, sizeof(ROOM**));
	if (ME->Header_Room == NULL)
		printf("실패했습니다.\n");
	else
	{
		printf("1층을 생성합니다.\n");
		fprintf(FP, "%d동: 1층 생성\n", ME->Building_Num);
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
				printf("현재 %d동은 %d층입니다.\n", ME->Building_Num, or_size);
				ME->Header_Room = (ROOM***)realloc(ME->Header_Room, sizeof(ROOM**)*(or_size + 1));
				printf("%d층 -> %d층으로 변경되었습니다.\n", or_size, or_size + 1);
				fprintf(FP, "%d동: %d층 -> %d층\n", ME->Building_Num, or_size, or_size + 1);
				ME->Header_Room[or_size] = NULL;
				return -M_Add_Floor;
			}
			else
				printf("돈이 부족합니다.\n");
		}
		else
			printf("더 이상 추가할 수 없습니다.\n");
	}
	else if(value == 2)
	{
		if (or_size < 5)
		{
			if (*Money >= M_Add_Floor)
			{
				printf("현재 %d동은 %d층입니다.\n", ME->Building_Num, or_size);
				ME->Header_Room = (ROOM***)realloc(ME->Header_Room, sizeof(ROOM**)*(or_size + 1));
				printf("%d층 -> %d층으로 변경되었습니다.\n", or_size, or_size + 1);
				fprintf(FP, "%d동: %d층 -> %d층\n", ME->Building_Num, or_size, or_size + 1);
				ME->Header_Room[or_size] = NULL;
				return -M_Add_Floor;
			}
			else
				printf("돈이 부족합니다.\n");
		}
		else
			printf("더 이상 추가할 수 없습니다.\n");
	}

	return 0;
}
long Sub_Floor(BUILDING *ME, FILE *FP)
{
	int or_size = _msize(ME->Header_Room) / sizeof(ROOM**);

	printf("현재 %d동은 %d층입니다.\n", ME->Building_Num, or_size);
	free(ME->Header_Room[or_size - 1]);
	ME->Header_Room = (ROOM***)realloc(ME->Header_Room, sizeof(ROOM**)*(or_size - 1));
	printf("%d층 -> %d층으로 변경되었습니다.\n", or_size, or_size - 1);
	fprintf(FP, "%d동: %d층 -> %d층\n", ME->Building_Num, or_size, or_size - 1);

	return M_Sub_Floor;
}