#include"Main.h"

long Change_Room(BUILDING *ME, long *Money, FILE *FP)
{
	char YN = 'Y';
	int i = 0, floor = 0;

	printf("몇 층의 방을 변경하시겠습니까?\n입력: ");
	floor = get_num(); // 변경하려는 층
	if (ME->Header_Room != NULL)
		i = _msize(ME->Header_Room) / sizeof(ROOM**); // 층 수

	printf("변경할 층은 %d층입니다.\n", floor);
	printf("방은 한 번에 하나씩 변경가능합니다.\n");
	printf("방 +1 : -%d만원\n", M_Add_Room);
	printf("방 -1 :  +%d만원\n", M_Sub_Room);
	printf("방 수를 변경하시겠습니까? (Y/N)\n입력: ");
	YN = getchar();

	if (YN == 'y' || YN == 'Y')
	{
		if (floor <= i && floor > 0)
		{
			if (ME->Header_Room[floor - 1] == NULL)
				if (*Money >= M_Add_Room)
					*Money += First_Room(ME, floor, FP);
				else
					printf("돈이 부족합니다.\n");
			else
			{
				printf("1. 늘리기 2. 줄이기\n입력: ");
				i = get_num();
				if (i == 1)
					*Money += Add_Room(ME, floor, Money, FP);
				else if (i == 2)
					*Money += Sub_Room(ME, floor, FP);
			}
		}
		else
			printf("%d층은 없습니다.", floor);
	}
	else
		printf("취소하였습니다.\n");
	return 0;
}
long First_Room(BUILDING *ME, int Floor, FILE *FP)
{
	int i = _msize(ME->Header_Room) / sizeof(ROOM**);

	printf("현재 만들어진 방이 없습니다.\n");
	ME->Header_Room[Floor - 1] = (ROOM**)malloc(sizeof(ROOM*));
	memset(ME->Header_Room[Floor - 1], 0x0, sizeof(ROOM*));
	if (ME->Header_Room[Floor - 1] == NULL)
		printf("실패했습니다.\n");
	else
	{
		printf("방 생성합니다.\n");
		fprintf(FP, "%d동: %d층 방 생성\n", ME->Building_Num, i);
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
				printf("현재 %d층은 방이 %d개입니다.\n", Floor, or_size);
				ME->Header_Room[Floor - 1] = (ROOM**)realloc(ME->Header_Room[Floor - 1], sizeof(ROOM*)*(or_size + 1));
				printf("%d개 -> %d개으로 변경되었습니다.\n", or_size, or_size + 1);
				fprintf(FP, "%d동 %d층: 방 개수 %d개 -> %d개\n", ME->Building_Num, Floor, or_size, or_size + 1);
				RTEMP = ME->Header_Room[Floor - 1];
				RTEMP[or_size] = NULL;
				return -M_Add_Room;
			}
			else
				printf("돈이 부족합니다.");
		}
		else
			printf("더 이상 추가할 수 없습니다.\n");
	}
	else if (value == 2)
	{
		if (or_size < 3)
		{
			if (*Money >= M_Add_Room)
			{
				printf("현재 %d층은 방이 %d개입니다.\n", Floor, or_size);
				ME->Header_Room[Floor - 1] = (ROOM**)realloc(ME->Header_Room[Floor - 1], sizeof(ROOM*)*(or_size + 1));
				printf("%d개 -> %d개으로 변경되었습니다.\n", or_size, or_size + 1);
				fprintf(FP, "%d동 %d층: 방 개수 %d개 -> %d개\n", ME->Building_Num, Floor, or_size, or_size + 1);
				RTEMP = ME->Header_Room[Floor - 1];
				RTEMP[or_size] = NULL;
				return -M_Add_Room;
			}
			else
				printf("돈이 부족합니다.");
		}
		else
			printf("더 이상 추가할 수 없습니다.\n");
	}

	return 0;
}
long Sub_Room(BUILDING *ME, int Floor, FILE *FP)
{
	int or_size = _msize(ME->Header_Room[Floor - 1]) / sizeof(ROOM**);
	ROOM **RTEMP = NULL;

	RTEMP = ME->Header_Room[Floor - 1];

	printf("현재 %d층은 방이 %d개입니다.\n", Floor, or_size);
	free(RTEMP[or_size - 1]);
	ME->Header_Room[Floor - 1] = (ROOM**)realloc(ME->Header_Room[Floor - 1], sizeof(ROOM*)*(or_size - 1));
	printf("%d개 -> %d개으로 변경되었습니다.\n", or_size, or_size - 1);
	fprintf(FP, "%d동 %d층: 방 개수 %d개 -> %d개\n", ME->Building_Num, Floor, or_size, or_size - 1);

	return M_Sub_Room;
}

long In_Out_Room(BUILDING *ME, long *Money, FILE *FP)
{
	int i = 0, result = 0;
	printf("입주 시 %d만원의 비용이 필요합니다.\n", M_Enter_Room);
	printf("방 나가는데 필요한 비용은 없습니다.\n");

	printf("1. 입주 2. 나가기\n입력: ");
	i = get_num();
	if (i == 1)
		if (*Money > 400)
			result += Enter_Room(ME, FP);
		else
			printf("돈이 부족합니다.\n");
	else if (i == 2)
		Out_Room(ME, FP);
	else
		printf("입력이 잘못되었습니다.\n취소합니다.\n");

	return result;
}
long Enter_Room(BUILDING *ME, FILE *FP)
{
	int num = 0, TF = 0;
	int sizeF = 0, sizeR = 0;
	ROOM **Floor = NULL;

	printf("몇 호에 입주합니까?\n입력: ");
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
							printf("입주 성공!");
							fprintf(FP, "%d동 %d호 입주(PW : %s )\n", ME->Building_Num, num, Floor[sizeR - 1]->Password);
							return -M_Enter_Room;
						}
						else
							printf("입주 실패!");
					}
					else
						printf("빈 방이 아닙니다.");
				}
			}
		}
	}

	if (TF != 1)
		printf("%d호를 찾지 못했습니다.\n", num);

	return 0;
}
void Out_Room(BUILDING *ME, FILE *FP)
{
	int i = 0, num = 0, TF = 0;
	int sizeF = 0, sizeR = 0;
	char PW[9] = { 0 };
	ROOM *NewRoom = NULL;
	ROOM **Floor = NULL;

	printf("몇 호가 나갑니까?\n입력: ");
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
						printf("비밀번호를 입력하세요.\n: ");
						get_n_string_void(PW, 9);
						printf("\n");
						if (Find_pattern(PW, Floor[sizeR - 1]->Password, 1) == 1)
						{
							printf("%d가 나갔습니다.\n", num);
							fprintf(FP, "%d동 %d호 이사\n", ME->Building_Num, num);
							Floor[sizeR - 1] = NULL;
						}
						else
							printf("비밀번호가 틀렸습니다!\n");
					}
					else
						printf("이미 빈 방입니다.");
				}
			}
		}
	}

	if (TF != 1)
		printf("%d호를 찾지 못했습니다.\n", num);
}
ROOM *Profile_Room(void)
{
	int size = 0, name_size = 0, i = 0;
	ROOM* New_Room = (ROOM*)malloc(sizeof(ROOM));

	printf("입주자 이름의 길이: ");
	name_size = get_num();
	New_Room->Name = (char*)malloc((sizeof(char)*(2 * name_size)) + 1);

	printf("입주자 이름: ");
	get_n_string(New_Room->Name, (2 * name_size));

	printf("방세(1~500만원 중 랜덤): ");
	New_Room->Value = Random(500)+1;
	printf("%d만원\n", New_Room->Value);

	printf("비밀번호(영문,숫자 최대8자): ");
	get_n_string(New_Room->Password, 8);

	return New_Room;
}