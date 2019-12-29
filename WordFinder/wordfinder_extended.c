#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 20
#define SIZE2 700

void input(char word2[], char search[],char word[], int k, int *front, int *back); // 입력받는 함수
void Read(int f, FILE *F,char str[],int l, int *i, int *k); // 단어 추출 함수
int compare(char str[], char word[],int k, int front); // 단어 비교하는 함수
int UI(int n); //command 함수

typedef struct word_list {
	char sword[SIZE];
	int line[SIZE2];
}LIST;

void reset(LIST arr[], int a, int b); //구조체 초기화 함수
void structcompare(char str[], LIST arr[], int a, int b,int l); //구조체 단어 비교함수
int struct_array(LIST arr[], int a, int b, int n); //구조체 사전식 정렬 함수

int main(void)
{
	FILE *F = fopen("sample.txt", "r");
	char word[SIZE] = {0}, word2[SIZE] = {0}, str[SIZE] = {0}, search[SIZE]={0}, alpha[1];
	char *pword = word, *pstr = str;
	int n=0, m=0, m2=0, i=1, j=0, k=1, front=0, back=0,a=0,l=0;
	LIST arr[SIZE2];
	struct arr *plist;


	fseek(F,0L,SEEK_END);
	const int f = ftell(F);
	fseek(F,0L,SEEK_SET);

	printf("wordfinder_201611891_문종식\n");

	while(1)
	{
		n = UI(j);

		//1번 기능
		if(n==1)
		{
		//모두 초기화시킬 함수 필요
		reset(arr,SIZE,SIZE2);

		printf("select command is : 1. Search word (in text file)\n");
		input(word2,search,word,SIZE,&front,&back);
		printf("\nfront : %d,	back : %d\nfind word complete\n\n\ncurrent word: %s\n",front,back,word2);

		i = 1; //라인 변수
		while(1) {
			Read(f,F,str,SIZE, &i, &k);
			if(strlen(str)==(front+back+strlen(word))) {
				if(compare(str,word,SIZE,front)==1) {
					structcompare(str,arr, SIZE,SIZE2,i);

					//printf("%s\n",str);
					}
				}

			if(ftell(F) == f - 1 || ftell(F) == f){
				fseek(F,0L,SEEK_SET);
				break;
			}
		}

		//2번 기능
		} else if (n == 2) {

			printf("select command is : 2. Display all word (in 1's result)\n");
			struct_array(arr,SIZE,SIZE2,0);

/*
			m = arr[a].sword[0];
			//printf("%d\n",m);

			while(1)
			{
				printf("\nWord = %s  Line = ", arr[a].sword);
				for(l=0;arr[a].line[l]!=0;l++)
				{
					if(l>0)
						printf(", ");
					printf("%d", arr[a].line[l]);
				}

				//출력 끝
				a++;
				if(arr[a].sword[0]=='\0')
				{
					struct_array(arr,SIZE,SIZE2,0);
					break;
				}
			}

			a=0;
			l=0;
*/
			printf("\ncurrent word: %s", word2);

		//3번기능
		} else if (n == 3) {
			printf("select command is : 3. Display alphabet word (in 1's result)\n");
			printf("\ninput : ");
			scanf("%s", alpha);
			a=0;
			while(1)
			{
				if( alpha[0] == arr[a].sword[0] )
					l = 1;

				if( arr[a].sword[0]<91 )
				{
					if ( alpha[0] == (arr[a].sword[0]+32))
						l = 1;
				} else {
					if ( alpha[0] == (arr[a].sword[0]-32))
						l = 1;
				}

				if( l == 1 )
				{
					printf("\nWord = %s  Line = ", arr[a].sword);
					for(l=0;arr[a].line[l]!=0;l++)
					{
						if(l>0)
							printf(", ");
						printf("%d", arr[a].line[l]);
					}
				}

				if(arr[a].sword[0]=='\0')
				{
					printf("\ncureent word: %s", word2);
					a=0;
					break;
				}
				a++;
				l = 0;
			}

		//4번 기능
		} else if (n == 4) {
			break;
		}
	}



	fclose(F);
	printf("wordfinder를 종료합니다.\n");
	return 0;
}

void input(char word2[],char search[], char word[], int k, int *front, int *back)
{
	int i, s,e;
	printf("\n단어를 입력하세요:");
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

	for(;s<=e;s++)
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

	//printf("저장된 단어: %s, 단어의 길이: %d, 커서 위치: %d\n",str,strlen(str), ftell(F));
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

int UI(int n)
{
	printf("\n----------------------------------------\n");
	printf("1. Search word (in text file)\n");
	printf("2. Display all word (in 1's result)\n");
	printf("3. Display alphabet word (in 1's result)\n");
	printf("4. Quit\n");
	printf("----------------------------------------\n\ninput command: ");

	scanf("%d", &n);

	return n;
}

//command 2번 함수, 구조체에 저장하는 함수
void structcompare(char str[], LIST arr[], int a, int b, int l)
{
	int i=0,j=0;
	if(arr[i].sword[0]=='\0')
	{
		strcpy(arr[i].sword,str);
		arr[i].line[j]=l;
		l = 0;
	}

	if(l!=0){
	for(i = 0;arr[i].sword[0]!='\0';){
		if(strcmp(str,arr[i].sword)==0){
			while(1){
				if(arr[i].line[j] == 0){
					arr[i].line[j] = l;
					if(arr[i].line[j]==arr[i].line[j-1])
						arr[i].line[j]=0;
					break;
				}
				j++;
			}
			break;
		}
		i++;
		if(arr[i].sword[0]=='\0'){
			strcpy(arr[i].sword,str);
			arr[i].line[j] = l;
			break;
		}
	}
	}
}

void reset(LIST arr[], int a, int b)
{
	int i,j;

	for(i=0;arr[i].sword[0]!='\0';)
	{
		for(j=0;j<strlen(arr[i].sword);j++)
		{
			arr[i].sword[j] = '\0';
		}

		for(j=0;arr[i].line[j]!=0;j++)
		{
			arr[i].line[j] = 0;
		}
		i++;
	}
}

int struct_array(LIST arr[], int a, int b, int n)
{
	int i, j = 0, min = 127, temp=0;

	//가장 앞을 찾는다
	for(i=0;arr[i].sword[0] != '\0'; i++)
	{
		//대문자 인지 판별
		if(arr[i].sword[0] < 91)
		{
			j = arr[i].sword[0]+32;
		}


		if(arr[i].sword[0] < min && j < min)
		{
			temp = arr[i].sword[0];
			if(temp > n)
			{
				min = temp;
			}
		}
		j=0;
	} //min이 정해지는 구간
	//printf("\n%d", min);

	if(min ==127)
		return 0;

	//리스트 스캔
		for(i=0;arr[i].sword[0] != '\0' ; i++)
		{
			if(arr[i].sword[0] == min || (arr[i].sword[0]+32) == min)
			{
				printf("\nWord = %s   Line = ", arr[i].sword);
				for(j=0;arr[i].line[j] != 0; j++)
				{
					if(j>0)
						printf(", ");
					printf("%d", arr[i].line[j]);
				}
			}

		}
	struct_array(arr,a,b,min);
	return 0;
}
