#include"Main.h"

int main(void)
{
	int i = 0;
	char OFF = 0;
	long Money = 800000;//단위: 만
	long InCome = 0;
	BUILDING *Header_building = (BUILDING*)malloc(sizeof(BUILDING));
	BUILDING *ME = NULL;
	FILE *DB = NULL, *LOG = NULL;

	LOG = fopen("Log.txt", "a+");
	Log_Start_End(LOG, 1);
	Header_Setting(Header_building);
	ME = Header_building;

	i = info();
	GetAsyncKeyState(SPACE);
	if (i == 1)//새로 시작
		DB = NewFile(Header_building, Money, DB, LOG, i);
	if(i == 2)//불러오기
		DB = Input_File(Header_building, &Money, LOG);

	//실행
	while (1)
	{
		Print_Building(ME);
		i = Menu(Money);
		switch (i)
		{
		case 1:
			ME = My_Location(Header_building, LOG);
			break;
		case 2:
			Money += Make_Building(Header_building, &Money, LOG);
			break;
		case 3:
			if (ME->Building_Num != 0)
				Money += Change_Floor(ME, &Money, LOG);
			break;
		case 4:
			if (ME->Building_Num != 0)
				Money += Change_Room(ME, &Money, LOG);
			break;
		case 5:
			In_Out_Room(ME,&Money,LOG);
			break;
		case 6:
			Print_ALL(Header_building, LOG);
			break;
		case 7:
			i = Save_DB();
			if (i == 1 || i == 2)
				DB = NewFile(Header_building, Money, DB, LOG, i);
			break;
		case 8:
			Status(&Money, InCome);
			break;
		case 10:
			OFF = Off(Header_building, Money, LOG, DB);
		default:
			break;
		}

		if (OFF == 1)
			break;
		if (i != 9)
			i = getchar();
			//Sleep(1500);

		InCome = Total_Money(Header_building);
		system("cls");
	}

	fclose(DB);
	fclose(LOG);

	return 0;
}