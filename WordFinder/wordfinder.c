#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 20

void input(int n, char search[],char word[], int k, int *front, int *back); // 입력받는 함수
void Read(int f, FILE *F,char str[],int l, int *i, int *k); // 단어 추출 함수
int compare(char str[], char word[],int k, int front); // 단어 비교하는 함수

int main(void)
{
	FILE *F = fopen("sample.txt", "r");
	char word[SIZE] = {0},str[SIZE] = {0}, search[SIZE]={0};
	char *pword = word, *pstr = str;
	int n=0, m=0, i=1, j=0, k=1, front=0, back=0;

	fseek(F,0L,SEEK_END);
	const int f = ftell(F);
	fseek(F,0L,SEEK_SET);

	printf("wordfinder_201611891_문종식\n");

	for(n=1;n<6;n++)
	{
		input(n,search,word,SIZE,&front,&back);
		printf("\nfront : %d,	back : %d",front,back);
		i =1;
		while(1) {
			Read(f,F,str,SIZE, &i, &k);
			if(strlen(str)==(front+back+strlen(word))) {
				if(compare(str,word,SIZE,front)==1) {
					if(k==1) {
						printf("\nline#%d: ", i);
						printf("%s ",str);
						j++;
						k = 0;
					} else if (k==0) {
						printf(", ");
						printf("%s ", str);
						j++;
					}
				}
			}

			if(ftell(F) == f - 1 || ftell(F) == f){
				fseek(F,0L,SEEK_SET);
				break;
			}
		}
		printf("\n\n총 %d 개의 %s 을 찾았습니다.\n", j, search);
		j=0;
	}


	
	fclose(F);
	printf("wordfinder를 종료합니다.");
	return 0;
}

void input(int n,char search[], char word[], int k, int *front, int *back)
{
	int i, s,e;
	char word2[SIZE] = {0};
	printf("%d번째 검색 단어를 입력하세요:",n);
	scanf("%s",word2);

	//printf("길이: %d\n", strlen(word2));

	if(isdigit(word2[1])) {
		*front = word2[1] -'0';
		s=3;
	} else {
		*front = 0;
		s = 0;
	}

	if(isdigit(word2[strlen(word2) - 2])){
		*back = word2[strlen(word2) - 2] - '0';
		e = strlen(word2) - 4;
	} else {
		*back = 0;
		e = strlen(word2)-1;
	}

	for(i=0;i<SIZE;i++){
		word[i]=' ';
		search[i]=' ';
	}
	i = e-s+1;

	for(s;s<=e;s++)
	{
		if(*front == 0)
			word[s] = word2[s];
		else
			word[s-3] = word2[s];
	}
	
	word[i]='\0';

	for(i=0;i<strlen(word2);i++) {
		search[i] = word2[i];
	}
	search[i] = '\0';
}

void Read(int f, FILE *F, char str[],int l, int *i, int *k)
{
	/*
	fgets(str,3,F);
	if(str[0] == '\n' || str[1] == '\n') {
		(*k) = 1;
		(*i)++;
	} else {
		fseek(F, -2L, SEEK_CUR);
	}
	*/

	fscanf(F,"%s", str);

	if(isdigit(str[0])){
		(*k) =1;
		(*i)++;
	}

	//printf("현재 저장된 단어: %s, 단어의 길이: %d, 커서 위치: %d\n",str,strlen(str), ftell(F));
}

int compare(char str[], char word[], int k, int front)
{
	char com[SIZE]={0};
	int c, c2= front;
	for(c=0;c<strlen(word);c++) {
		c2 = front + c;
		com[c] = str[c2];

	}

	if(strncmp(com,word,strlen(word))==0)
		return 1;
	else
		return 2;

}
