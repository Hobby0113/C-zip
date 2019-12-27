#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#define SIZE 100

void menu(void);
void gotoxy(int x, int y);

typedef struct {
	char c[3];
	int n;
	int nL;
	int nR;
	int nU;
	int nD;
} Num;

void ground(Num *d, int s, int s2, int c);
void next(Num *d,int R[],  int s, int s2, int m, int g); //m은 미러, g는 난이도
void NList(Num *N, int s, int s2);
int isolation(int i, Num *N, int R[],int l, int s, int s2);
void play(int R[], int s);
void reset(int R[]);

//쓰레드 함수
void *t_Com(void *array);

//전역 변수
int W, U_WL, C_WL, t; // W- 게임종료,U-사용자 스코어, C-컴퓨터 스코어, m-안내 메시지

//메인 함수 
int main(void)
{
	int m;
	Num N[SIZE] = { 0 };
	int R[SIZE] = { 0 };

	NList(N,SIZE,3); //구조체에 정보 입력

	//printf("pathfinder_201611891_문종식\n");

	t = 0;
	U_WL = 0;
	C_WL = 0;

	while(1)
	{
		system("clear");
/*
		for(m=0;m<SIZE;m++)
		{
			printf("%d U= %d, D= %d, R= %d, L= %d\n", N[m].n, N[m].nU, N[m].nD, N[m].nR, N[m].nL);
		}
*/
		menu();

		if(W != 1)
		{
		printf("select menu : ");
		scanf("%d", &m);
		printf("\n");
		}
		// 노말과 이지를 나누는 변수, 미러와 낫미러를 누군하는 변수

		if(m == 1 )// 일반 모드, 미러
		{
			ground(N,SIZE,3,0);
			next(N,R,SIZE,3,1,0);
			ground(N,SIZE,3,1);
			play(R,SIZE);
		}
		if(m == 2)// 일반 모드, 낫 미러
		{
			ground(N,SIZE,3,1);
			next(N,R,SIZE,3,0,0);
			play(R,SIZE);
		}
		if(m == 3)// 턴제 게임 모드
		{
			t = 1;
			ground(N,SIZE,3,1);
			next(N,R,SIZE,3,0,0);
			play(R,SIZE);
			t = 0;
		}
		if(m == 4)
			break;

		reset(R);

		fpurge(stdin); // 리눅스 환경에서 버퍼를 비우는 함수
	}

	return 0;
}


//구조체 배열 정보 입력 함수
void NList(Num *N, int s, int s2)
{
	int i;

	for(i = 0 ; i < 100 ; i++)
	{
		//숫자 저장
		N[i].n  = i;
		N[i].nL = i - 1;
		N[i].nR = i + 1;
		N[i].nU = i -10;
		N[i].nD = i +10;
		if(i/10 == 0)
			N[i].nU = -1;
		if(i/10 == 9)
			N[i].nD = -1;
		if(i%10 == 0)
			N[i].nL = -1;
		if(i%10 == 9)
			N[i].nR = -1;

		//문자열 저장
		sprintf(N[i].c,"%d",i);
		if(i<10)
		{
			N[i].c[1] = N[i].c[0];
			N[i].c[0] = 48;
		}
	}
}

//메뉴함수
void menu(void)
{
	printf("\npathfinder_201611891_문종식\n");
	printf("\n=======================\n");
	printf("1. Game Start - helper\n");
	printf("2. Game Start - normal\n");
	printf("3. Game Start - turn mode\n");
	printf("4. Exit\n");
	printf("=======================\n\n");
	printf("current score uset vs computer\n%d : %d\n\n", U_WL,C_WL);

}

//기록 초기화
void reset(int R[])
{
	int r;
	for(r = 1; R[r]!=0; r++)
		R[r] = 0;
}

//goto함수
void gotoxy(int x, int y)
{
	printf("\033[%d;%df",y ,x);
	fflush(stdout);
}

//게임 판 함수
void ground(Num *N, int s, int s2, int c)
{
	int n;

	system("clear"); //화면 청소
	gotoxy(18,2);
	printf("Play Ground                                            ");
	
	if(c == 1)
		printf("Computer\n\n");
	
	gotoxy(5, 4);
	for(n = 0; n<SIZE; n++)
	{
		gotoxy( (((N[n].n)%10)*4) + 5, (((N[n].n)/10)*2) + 4 );
		printf("|%s|",N[n].c);

		if(c == 1)
		{
			gotoxy( (((N[n].n)%10)*4) + 57, (((N[n].n)/10)*2) + 4 );
			printf("|%s|",N[n].c);
		}
		
/*
		if(n%10 == 9)
		{
			printf("\n\n");
			gotoxy(5, (n/10)*2 + 6);
		}
*/
	}

}

//길 생성 함수
void next(Num *N, int R[], int s, int s2, int m, int g)
{
	int i,j,k,l=0;

	W = 0;

	gotoxy(6,4);
	printf("##");
	R[0] = 0;

	srand(time(NULL));
	while(1)
	{
		gotoxy(5,25);
		printf("Input : ");
		//scanf("%d", &i);


		i = (rand() % 99) + 1;
	
		k = R[l]; //마지막 타일 저장

		//if(i > R[l]) // easy모드
		//{

		if( (i == N[k].nL || i == N[k].nR) || (i == N[k].nU || i == N[k].nD) ) // 상하좌우에 위치 하는지 확인
		{
			//printf("\n\nOK-1");
			if( R[l-1] != i || l == 0) //방금 전 지나온 타일인지 확인
			{
				//printf("\n\nOK-2");
				for(j = 0; j<=l; j++) //길이 붙어버리는지 확인
				{
					k = R[j]; //j번째 타일 저장

					if(j == l) //직전 타일은 무시하기 위해
					{
						j = 1;
						break;
					}

					if( (i == N[k].nR || i == N[k].nL) || (i == N[k].nU || i == N[k].nD) )
					{
						//printf("\n\nback");
						j = 0;
						break;
					}
				}

				if( j == 1) // 모두 충족 했다면 진행
				{
					//printf("\n\nOk-3");
					l++; //진행한 타일 개수 증가
					R[l] = i; // 기록에 추가
					gotoxy( ((i%10)*4)+6 , ((i/10)*2)+4 );// 타일 위치로 가기
					//printf("##");//임시
					if( l !=0)
						k = isolation(i,N,R,l,s,s2);
				}

			}
		}
		//} // easy 모드 
		fpurge(stdin);
		if(R[l] == 99)
		{
			i = 0;
			break;
		}

//*/
		//고립 판별
		//if(l != 0)
		//	k = isolation(i,N,R,l,s,s2);

		//printf("\n\n%d\n", k);

		if(k == 4)
		{
			for(l = 1; R[l] != 0; l++)
				R[l] = 0;
			l = 0;
		}
//*/
	}

	if(i==0 && m == 1)
	{
		for(i = 0; i<=l; i++)
		{
			gotoxy( ((R[i]%10)*4)+6 , ((R[i]/10)*2)+4 ); // 타일 위치로 가기
			printf("##");
		}
		gotoxy(5,25);
		printf("힌트는 10초간 보여집니다.");
		fflush(stdout);
		sleep(10);
	}
}

int isolation(int i, Num *N, int R[],int l, int s, int s2)
{
	int a=0, b,c;

	//위
	for(b = 0; b<=l-1; b++)
	{
		c = N[i].nU;
		if(c == -1)
		{
			a++;
			break;
		}
		if( (R[b] == N[c].nU || R[b] == N[c].nD) || (R[b] == N[c].nL || R[b] == N[c].nR) )
		{
			a++;
			break;
		}
	}

	//아래
	for(b = 0; b<=l-1; b++)
	{
		c = N[i].nD;
		if(c == -1)
		{
			a++;
			break;
		}
		if( (R[b] == N[c].nU || R[b] == N[c].nD) || (R[b] == N[c].nL || R[b] == N[c].nR) )
		{
			a++;
			break;
		}
	}

	//왼쪽
	for(b = 0; b<=l-1; b++)
	{
		c = N[i].nL;
		if(c == -1)
		{
			a++;
			break;
		}
		if( (R[b] == N[c].nU || R[b] == N[c].nD) || (R[b] == N[c].nL || R[b] == N[c].nR) )
		{
			a++;
			break;
		}
	}

	//오른쪽
	for(b = 0; b<=l-1; b++)
	{
		c = N[i].nR;
		if(c == -1)
		{
			a++;
			break;
		}
		if( (R[b] == N[c].nU || R[b] == N[c].nD) || (R[b] == N[c].nL || R[b] == N[c].nR) )
		{
			a++;
			break;
		}
	}

	return a;
}

void play(int R[], int s)
{
	int r,i=0,thr, st,ms=29;

	pthread_t p_Com;

	gotoxy(6,4);
	printf("##"); //00부터
 
	gotoxy(5,24);
	printf("종료를 원하면 -1을 입력하세요.");
	gotoxy(5,25);
	printf("Input : ");

	gotoxy(50,27);
	printf("Ready!");
	fflush(stdout);
	sleep(2);
	
	printf("\b\b\b\b\b\bGo!!!!");

	thr = pthread_create(&p_Com, NULL, t_Com, (void *)R);

	gotoxy(13,25);

	for(r = 1; R[r] != 0 ; )
	{
		if(t==1 || t == 0)
{
		scanf("%d", &i);

		if(W == 1)
		
		{
			gotoxy(13,25);
			printf("Lose!");
			break;
		}

		if( i == -1)
		{
			W = 2;
			gotoxy(40,26);
			printf("게임을 종료합니다. 잠시 후 메뉴 화면으로 넘어갑니다.");

			break;
		}

		if(i > 99 || i < -1)
		{
			gotoxy(0,ms);
			ms++;
			if(ms == 50)
				ms = 29;
			printf("범위 내 값을 확인해 주세요.");
		}

		if(i == R[r])
		{
			r++;
			gotoxy( ((i%10)*4)+6 , ((i/10)*2)+4 );
			printf("##");
		}
		else
		{
			gotoxy(0,ms);
			ms++;
			if(ms == 50)
				ms = 29;
			printf("주의! %d으로 연결된 길은 없습니다!",i);
			if( t !=0)
			{
			gotoxy(0,ms);
			ms++;
			if(ms == 50)
				ms=29;
			t = 2;
			printf("턴이 넘어갑니다.(사용자 -> 컴퓨터)");
			}

		}
		gotoxy(13,25);
		fflush(stdout);
}
	}

	if(R[r-1] == 99)
	{
		U_WL++;
		W =1 ;
		printf("Win!!");
		gotoxy(70,26);
		printf("Lose!");
	}

	fflush(stdout);

	pthread_join(p_Com, (void **)&st);

	fflush(stdout);
	sleep(1);

	gotoxy(40,27);
	printf("게임이 끝났습니다. 다시 하시겠습니까? (1:다시 0: 메뉴로) :");
	scanf("%d", &i);

	if(i == 0)
		W = 0;
	if(i == 1)
	{
		gotoxy(40,28);
		printf("잠시후 게임을 다시 시작합니다.");
		fflush(stdout);
		sleep(2);
		W = 1;
	}
}

void *t_Com(void *array)
{
	int a,b,cms = 29;
	int arr[SIZE] = { 0 };

	gotoxy(58,4);
	printf("##");
	fflush(stdout);
	gotoxy(13,25);

	for(a = 0; a<SIZE; a++)
		arr[a] = ((int *)array)[a];

	//srand(time(NULL));
	for(b=1;arr[b] != 0; )
	{
		if(t == 2 || t == 0 )
		{

		a = (rand() % 4) + 1;
		switch(a)
		{
			case 1:
				a = arr[b-1] + 1;
				break;
			case 2:
				a = arr[b-1] - 1;
				break;
			case 3:
				a = arr[b-1] + 10;
				break;
			case 4:
				a = arr[b-1] - 10;
				break;
		}


		if(W ==2)
		{
			pthread_exit((void*)&W);
		}
		if(W == 1)
		{
			gotoxy(70,26);
			printf("Lose!");
			pthread_exit((void*)&W);
			break;
		}

		if(a == arr[b])
		{
			b++;
			gotoxy( ((a%10)*4) + 58 , ((a/10)*2)+4 );
			fflush(stdout);
			printf("##");
			gotoxy( 65,24);
			printf("컴퓨터 %d에서 %d로 이동 성공!", arr[b-2],arr[b-1]);
			
			gotoxy(13,25);
			
			sleep(1);
		}
		else
		{
			gotoxy(65,24);
			printf("컴퓨터 %d 시도! 길찾기 실패!",a);
			gotoxy(13,25);
			sleep(1);
			if( t != 0 )
			{
				gotoxy(65,cms);
				cms++;
				if( cms ==50)
					cms = 29;
			t = 1;
			printf("턴이 넘어갑니다.(컴퓨터 -> 사용자)");
			gotoxy(13,25);
			}
		}
		}
	}

	if(arr[b-1] == 99)
	{
		C_WL++;
		gotoxy(70,25);
		printf("Win!!");
		gotoxy(13,25);
		printf("Lose! 숫자를 입력하면 넘어갑니다.");
		W = 1;
	}

	fflush(stdout);

}

//컴퓨터와의 스코어 표시-완료
//게임 도중 나가기-완료
//추가 구현 사항
//사용자 도우미 기능- 완료
//하드코어 모드
