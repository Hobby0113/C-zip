#include"Main.h"

int get_num(void) // 숫자만 받는 함수 scanf대신 사용할 것
{
	int result, check = 0;
	char c;

	while (1)
	{
		result = 0;
		while (1)
		{
			c = getchar();
			if (c == ' ' || c == '\n')
				break;

			if (c<'0' || c>'9')
			{
				//printf("\n다시 입력하세요.\n");
				check = 0;
				break;
			}

			result = result * 10;
			result = result + c - '0';
			check = 1;
		}

		if (check == 1)
			break;
	}

	fflush(stdin);
	return result;
}
void gotoxy(int x, int y) // 좌표 함수 첫 줄의 가장 왼쪽의 좌표가 (1,1)임
{
	COORD Pos = { x - 1,y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
int Random(int x)////랜덤 함수 0~x-1 중 랜덤으로 하나의 정수 반환
{
	int i;
	i = rand() % x;
	return i;
}
int My_strlen(char *string) // 문자열의 길이를 반환, 한글의 경우 2바이트로 계산
{
	int i = 0;

	while (*(string + i) != '\0')
		i++;

	return i;
}
int My_strcmp(char *string1, char *string2) // 두 문자열을 비교해서 같으면 1, 다르면 0을 반환
{
	int i = 0, len = My_strlen(string1);

	if (len == My_strlen(string2))
	{
		for (i = 0; i < len; i++)
			if (*(string1 + i) != *(string2 + i))
				return 0;
		return 1;
	}
	else
		return 0;
}
void get_n_string(char *string, int size) //길이가 n인 문자열을 받음, 인자는(문자열을 저장할 변수, 문자열의 길이), 가장 마지막에 NULL(\0)을 삽입함
{
	int i = 0;

	do {
		string[i] = getchar();
		i++;
	} while (string[i - 1] != '\n' && i<size + 1);

	string[i - 1] = '\0';

	fflush(stdin);

}
void get_n_string_void(char *string, int size) //get_n_string과 같은 함수,But 잘 못 입력한 것에 대한 수정이 불가능하고, 에코가 없음(뭐라고 치는지 안 보임)
{
	int i = 0;

	do {
		string[i] = getch();
		i++;
	} while (string[i - 1] != '\r' && i<size + 1);

	string[i - 1] = '\0';
	fflush(stdin);
}
int Find_pattern(char *string, char *pattern, int mode)// 패턴을 찾는 것을 기본 기능으로 하여, 모드에 따라 반환 값이 다름
{
	int loop_size = My_strlen(string) - My_strlen(pattern) + 1;
	int i = 0, count = 0;

	for (i = 0; i < loop_size; i++)
		if (check_first(string + i, pattern) == 1)
			if (check(string + i, pattern) == 1)
			{
				if (mode == 1) // 모드가 1일 때, 패턴을 찾으면 무조건 1을 반환함
					return 1;
				else if (mode == 2) // 모드가 2일 때, 찾은 패턴의 개수를 반환함.
					count++;
				else if (mode == 3) // 모드가 3일 때, 최초로 찾은 패턴의 위치를 반환함.
					return i;
			}

	if (mode == 1)
		return 0;
	else if (mode == 2)
		return count;
	else if (mode == 3)
		return -1;
	else
		return -1; // 모드에 1,2,3 이외의 정수를 넣었을 때, -1을 반환함
}
int check(char *string, char *pattern) // Find_pattern에 쓰이는 함수, My_strcmp와 거의 같은 기능을 함.
{
	int loop_size = My_strlen(pattern);
	int i = 0;

	for (i = 0; i < loop_size; i++)
	{
		if (*(string + i) != *(pattern + i))
			return 0;
	}
	return 1;

}
int check_first(char *string1, char *string2) //두 문자열의 첫 번째 문자가 같은지 확인, 같으면 1, 다르면 0을 반환
{
	if (*string1 != *string2)
		return 0;
	else
		return 1;
}
int File_Check(FILE *Fp) //파일 오픈 상태에 따라 오픈 실패 시 0, 성공 시 1을 반환
{
	if (Fp == NULL)
		return 0;
	else
		return 1;
}
