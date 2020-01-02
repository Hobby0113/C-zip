#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void gotoxy(int x, int y);
void local(int e, int L, int b);
void UI(void); //엘베
int menu(void); //메뉴

//업, 다운
void Up_input(void);
void Down_input(void);
void Up();
void Down();
int ls,le,U=0,D=0,line=3, OFF=0, ele_S=0, lock=0,vip=0;
int ele[7] = {0};

void Lock(void);
void VIP(void);

pthread_t elevator[6];
void *th_E1(void *);
void *th_E2(void *);
void *th_E3(void *);
void *th_E4(void *);
void *th_E5(void *);
void *th_E6(void *);

int main(void)
{
	int a=0,q=0,m=0;
	system("clear");
	UI();
sleep(1);	
	a = pthread_create(&elevator[0],NULL,th_E1,(void *)&q);
sleep(1);
    a = pthread_create(&elevator[1],NULL,th_E2,(void *)&q);
sleep(1);
    a = pthread_create(&elevator[2],NULL,th_E3,(void *)&q);
sleep(1);
    a = pthread_create(&elevator[3],NULL,th_E4,(void *)&q);
sleep(1);
    a = pthread_create(&elevator[4],NULL,th_E5,(void *)&q);
sleep(1);
    a = pthread_create(&elevator[5],NULL,th_E6,(void *)&q);

	while(1)
	{
		m = menu();
		if( m == 1 )
			Up_input();
		else if( m == 2 )
			Down_input();
		else if( m == 3 )
			VIP();
		else if( m == 4 )
			Lock();
		else if( m == 5 )
		{
			OFF = 1;
			break;
		}
	}

	for(a=0;a<6;a++)
        pthread_join(elevator[a],NULL);
	
	return 0;
}

void gotoxy(int x, int y)
{
    printf("\033[%d;%df",y,x);
    fflush(stdout);
}

void local(int e, int L, int b)
{
	int i;

	for(i=1; i < 21 ;i++)
	{
		gotoxy(e*6,3+(20-(i))*2);
		printf(" ");
	}

	gotoxy(e*6,3+(20-L)*2);
    if( b == 0 )
	{
        printf("□");
	}
    else if(b == 2)
	{
        printf("▽");
	}
    else if(b == 1)
	{
		printf("△");
	}

	fflush(stdout);
    gotoxy(3,45);
}

void UI(void)
{
    int a;

    //엘리베이터
    printf("     1     2     3     4     5     6");
    for(a=20;a>-1;a--)
    {
        printf("\n  -------------------------------------\n");
        if(a != 0)
                printf("  |     |     |     |     |     |     | %dF", a);
	}
	printf("\n1.올라가기 2.내려가기 3.vip 4.비상 5.종료 (모든 엘리베이터가 표시될 때 까지 기다리세요)\n:");
}

int menu(void)
{
	int a = 0;
	gotoxy(3,45);
	scanf("%d",&a);
	gotoxy(3,45);
    printf("   ");
    gotoxy(3,45);
	//gotoxy(3,45);
	//printf(" ");
	fflush(stdout);
	return a;
}

void Lock(void)
{
	gotoxy(45,line++);
	printf("%c\033[31m", 7);
    printf("비상! 모든 엘리베이터가 3초간 정지합니다.");
	printf("%c\033[0m", 7);
    gotoxy(3,45);
	lock = 1;
}

void VIP(void)
{
	gotoxy(45,line++);
	if(vip == 0)
	{
		printf("VIP모드가 실행 됩니다.");
		gotoxy(3,45);
		vip = 1;
	}
	else if(vip == 1)
	{
		printf("VIP모드가 종료 됩니다.");
        gotoxy(3,45);
        vip = 0;
	}
}

void Up_input(void)
{
	int s,e;
	//엘베선택
	gotoxy(45,line++);
    printf("어떤 엘리베이터를 이용하시겠습니까?");
    gotoxy(3,45);
    scanf("%d", &ele_S);
    gotoxy(3,45);
    printf("   ");
    gotoxy(3,45);
	//출발 층 선택
	gotoxy(45,line++);
	printf("출발할 층을 입력해주세요");
	gotoxy(3,45);
	scanf("%d", &s);
	gotoxy(3,45);
	printf("   ");
	gotoxy(3,45);
	ls = s;
	//도착 층 선택
	gotoxy(45,line++);
	printf("도착할 층을 입력해주세요");
	gotoxy(3,45);
	scanf("%d", &e);
	gotoxy(3,45);
    printf("   ");
    gotoxy(3,45);
	le = e;

	gotoxy(45,line++);
	printf("%d -> %d 요청", s,e);
	gotoxy(3,45);
	U = 1;

	fflush(stdout);
}
void Down_input(void)
{
    int s,e;
	//엘베선택
	gotoxy(45,line++);
    printf("어떤 엘리베이터를 이용하시겠습니까?");
    gotoxy(3,45);
    scanf("%d", &ele_S);
    gotoxy(3,45);
    printf("   ");
    gotoxy(3,45);
	//출발 층 선택
    gotoxy(45,line++);
    printf("출발할 층을 입력해주세요");
    gotoxy(3,45);
    scanf("%d", &s);
	gotoxy(3,45);
    printf("   ");
    gotoxy(3,45);
    ls = s;
	//도착 층 선택
    gotoxy(45,line++);
    printf("도착할 층을 입력해주세요");
    gotoxy(3,45);
    scanf("%d", &e);
	gotoxy(3,45);
    printf("   ");
    gotoxy(3,45);
    le = e;
	gotoxy(45,line++);
    printf("%d -> %d 요청", s,e);
    gotoxy(3,45);
    D = 1;

	fflush(stdout);
}

void Up(int se,int L, int id, int v)
{
	for( ; se != L;)
    {
		if(lock == 1)
		{
			sleep(3);
			lock = 0;
		}
        local(id,L,1);
        sleep(1);
        gotoxy(3, 45);
		if(v == 1)
		{
			L += 2;
			if( L > se )
				L -= 1;
		}
		else if(v == 0)
			L += 1;
    }
    local(id,L,0);
    gotoxy(45, line++);
    printf("%d호 : %d층 멈춤",id,se);
	gotoxy(3, 45);
    sleep(1);
}
void Down(int se, int L, int id,int v)
{
	for( ; se != L;)
    {
		if(lock == 1)
        {
            sleep(3);
            lock = 0;
        }
        local(id,L,2);
        sleep(1);
        gotoxy(3, 45);
		if(v == 1)
		{
			L -= 2;
			if( L < se)
				L += 1;
		}
        else if(v == 0)
            L -= 1;
    }
    local(id,L,0);
    gotoxy(45, line++);
    printf("%d호 : %d층 멈춤",id,se);
    gotoxy(3, 45);
    sleep(1);
}

void *th_E1(void *q)
{
	int e1=1,L1=1,s=0,e=0,V=0;
	local(e1,L1,0);
	while(1)
	{
		//올라가기
		if( U == 1 && ele_S == 1)
		{
			if( ((ls > 0)&&(ls < 11)) && ((le < 11)&&(le > 0)) )
			{
			U = 0;
			s = ls;
			e = le;
			V = vip;
			vip = 0;
			//출발할 층으로
			if( s >= L1 )
			{
				ele[1] = 1;
				Up(s,L1,e1,V);
				L1 = s;
			}
			else if( s < L1 )
			{
				ele[1] = 2;
				Down(s,L1,e1,V);
				L1 = s;
			}

			ele[1] = 1;
			Up(e,L1,e1,V);
			L1 = e;
			ele[1] = 0;
			}
		}
		else if( D == 1 && ele_S==1)
		{
			if( ((ls > 0)&&(ls < 11)) && ((le < 11)&&(le > 0)) )
			{
			D = 0;
            s = ls;
            e = le;
			V = vip;
            vip = 0;
            //출발할 층으로
            if( s >= L1 )
            {
                ele[1] = 1;
				Up(s,L1,e1,V);
                L1 = s;
            }
            else if( s < L1 )
            {
            	ele[1] = 2;
                Down(s,L1,e1,V);
                L1 = s;
			}

            ele[1] = 2;
            Down(e,L1,e1,V);
            L1 = e;
            ele[1] = 0;
			}
        }
		if(lock == 1)
        {
            sleep(3);
            lock = 0;
        }
		if( OFF == 1)
			pthread_exit((void*)&e1);
	}
}
void *th_E2(void *q)
{
	int e2=2,L2=1,s=0,e=0,V=0;
    local(e2,L2,0);
	while(1)
    {
        //올라가기
        if( U == 1 && ele_S==2)
        {
            if( ((ls > 0)&&(ls < 11)) && ((le < 11)&&(le > 0)) )
            {
            U = 0;
            s = ls;
            e = le;
			V= vip;
			vip=0;
            //출발할 층으로
            if( s >= L2 )
            {
                ele[2] = 1;
				Up(s,L2,e2,V);
                L2 = s;
			}
            else if( s < L2 )
            {
				ele[2] = 2;
				Down(s,L2,e2,V);
                L2 = s;
			}

            ele[2] = 1;
            Up(e,L2,e2,V);
            L2 = e;
            ele[2] = 0;
			}
        }
		else if( D == 1 && ele_S==2)
        {
            if( ((ls > 0)&&(ls < 11)) && ((le < 11)&&(le > 0)) )
            {
            D = 0;
            s = ls;
            e = le;
			V = vip;
			vip = 0;
            //출발할 층으로
			if( s >= L2 )
            {
                ele[2] = 1;
                Up(s,L2,e2,V);
                L2 = s;
            }
            else if( s < L2 )
            {
                ele[2] = 2;
                Down(s,L2,e2,V);
                L2 = s;
            }

            ele[2] = 1;
            Down(e,L2,e2,V);
            L2 = e;
            ele[2] = 0;
            }
		}
		if(lock == 1)
        {
            sleep(3);
            lock = 0;
        }
        if( OFF == 1)
            pthread_exit((void*)&e2);
    }

}
void *th_E3(void *q)
{
    int e3 = 3,L3=11,s=0,e=0,V=0;
    local(e3,L3,0);
	while(1)
    {
        //올라가기
        if( U == 1 && ele_S==3)
        {
            if( (ls > 10 && le > 10) && (ls < 21 && le < 21) )
            {
            U = 0;
            s = ls;
            e = le;
			V = vip;
			vip = 0;
            //출발할 층으로
			if( s >= L3 )
            {
                ele[3] = 1;
                Up(s,L3,e3,V);
                L3 = s;
            }
            else if( s < L3 )
            {
                ele[3] = 2;
                Down(s,L3,e3,V);
                L3 = s;
            }

            ele[3] = 1;
            Up(e,L3,e3,V);
            L3 = e;
            ele[3] = 0;
			}
        }
		else if( D == 1 && ele_S==3)
        {
            if( (ls > 10 && le > 10) && (ls < 21 && le < 21) )
            {
            D = 0;
            s = ls;
            e = le;
			V = vip;
            vip = 0;
            //출발할 층으로
			if( s >= L3 )
            {
                ele[3] = 1;
                Up(s,L3,e3,V);
                L3 = s;
            }
            else if( s < L3 )
            {
                ele[3] = 2;
                Down(s,L3,e3,V);
                L3 = s;
            }

            ele[3] = 1;
            Down(e,L3,e3,V);
            L3 = e;
            ele[3] = 0;
			}
        }
		if(lock == 1)
        {
            sleep(3);
            lock = 0;
        }
        if( OFF == 1)
            pthread_exit((void*)&e3);
    }

}
void *th_E4(void *q)
{
    int e4 = 4,L4=11,s=0,e=0,V=0;
    local(e4,L4,0);
	while(1)
    {
        //올라가기
        if( U == 1 && ele_S == 4)
        {
            if( (ls > 10 && le > 10) && (ls < 21 && le < 21) )
            {
            U = 0;
            s = ls;
            e = le;
			V = vip;
			vip = 0;
            //출발할 층으로
			if( s >= L4 )
            {
                ele[4] = 1;
                Up(s,L4,e4,V);
                L4 = s;
            }
            else if( s < L4 )
            {
                ele[4] = 2;
                Down(s,L4,e4,V);
                L4 = s;
            }

            ele[4] = 1;
            Up(e,L4,e4,V);
            L4 = e;
            ele[4] = 0;
			}
        }
		else if( D == 1 && ele_S == 4)
        {
            if( (ls > 10 && le > 10) && (ls < 21 && le < 21) )
            {
            D = 0;
            s = ls;
            e = le;
			V = vip;
            vip = 0;
            //출발할 층으로
			if( s >= L4 )
            {
                ele[4] = 1;
                Up(s,L4,e4,V);
                L4 = s;
            }
            else if( s < L4 )
            {
                ele[4] = 2;
                Down(s,L4,e4,V);
                L4 = s;
            }

            ele[4] = 1;
            Down(e,L4,e4,V);
            L4 = e;
            ele[4] = 0;
			}
        }
		if(lock == 1)
        {
            sleep(3);
            lock = 0;
        }
        if( OFF == 1)
            pthread_exit((void*)&e4);
    }

}
void *th_E5(void *q)
{
    int e5 = 5,L5=1, s=0,e=0,V=0;
    local(e5,L5,0);
	while(1)
    {
        
        //올라가기
        if( U == 1 && ele_S == 5)
        {
            if( (ls > 10 && le < 11) || (ls < 11 && le > 10) )
            {
            U = 0;
            s = ls;
            e = le;
			V = vip;
            vip = 0;
            //출발할 층으로
            if( s >= L5 )
            {
                ele[5] = 1;
                Up(s,L5,e5,V);
                L5 = s;
            }
            else if( s < L5 )
            {
                ele[5] = 2;
                Down(s,L5,e5,V);
                L5 = s;
            }

            ele[5] = 1;
            Up(e,L5,e5,V);
            L5 = e;
            ele[5] = 0;
            }
        }
		else if( D == 1&& ele_S == 5)
        {
            if( (ls > 10 && le < 11) || (ls < 11 && le > 10) )
            {
            D = 0;
            s = ls;
            e = le;
			V = vip;
            vip = 0;
            //출발할 층으로
            if( s >= L5 )
            {
                ele[5] = 1;
                Up(s,L5,e5,V);
                L5 = s;
            }
            else if( s < L5 )
            {
                ele[5] = 2;
                Down(s,L5,e5,V);
                L5 = s;
            }

            ele[5] = 1;
            Down(e,L5,e5,V);
            L5 = e;
            ele[5] = 0;
            } 
        }
		if(lock == 1)
        {
            sleep(3);
            lock = 0;
        }
        if( OFF == 1)
            pthread_exit((void*)&e5);
    }

}
void *th_E6(void *q)
{
    int e6 = 6,L6=1,s=0,e=0,V=0;
    local(e6,L6,0);
while(1)
    {
        //올라가기
        if( U == 1 && ele_S == 6)
        {
            if( (ls > 10 && le < 11) || (ls < 11 && le > 10) )
            {
            U = 0;
            s = ls;
            e = le;
			V = vip;
            vip = 0;
            //출발할 층으로
            if( s >= L6 )
            {
                ele[6] = 1;
                Up(s,L6,e6,V);
                L6 = s;
            }
            else if( s < L6 )
            {
                ele[6] = 2;
                Down(s,L6,e6,V);
                L6 = s;
            }

            ele[6] = 1;
            Up(e,L6,e6,V);
            L6 = e;
            ele[6] = 0;
            }
        }
		else if( D == 1 && ele_S == 6)
        {
            if( (ls > 10 && le < 11) || (ls < 11 && le > 10) )
            {
            D = 0;
            s = ls;
            e = le;
			V = vip;
            vip = 0;
            //출발할 층으로
            if( s >= L6 )
            {
                ele[6] = 1;
                Up(s,L6,e6,V);
                L6 = s;
            }
            else if( s < L6 )
            {
                ele[6] = 2;
                Down(s,L6,e6,V);
                L6 = s;
            }

            ele[6] = 1;
            Down(e,L6,e6,V);
            L6 = e;
            ele[6] = 0;
            }
       
        }
		if(lock == 1)
        {
            sleep(3);
            lock = 0;
        }
        if( OFF == 1)
            pthread_exit((void*)&e6);
    }

}























