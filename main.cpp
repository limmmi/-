#pragma comment(lib, "User32.lib")
#include<iostream>
#include<windows.h>
#include<string>
#include<conio.h>
#include<fstream>
using namespace std;

void COLOR_PRINT(const char* s, int color)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | color);
	printf(s);
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);
}

void HideCursor()  //隐藏光标
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);	
}

void gotoxy(short x, short y)  //光标跳跃,内容覆写
{
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}

void clear()
{
	for (int i = 0; i < 40; i++)
		for (int j = 0; j < 120; j++)
		{
			gotoxy(j, i);
			cout << " ";
		}
}

void clear_map()
{
	gotoxy(33,7);
	for (int i = 0; i < 28; i++)
		for (int j = 0; j < 53; j++)
		{
			gotoxy(33+j, 7+i);
			cout << " ";
		}
}

void clear5x5(int x,int y)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			gotoxy(x+j, y+i);
			cout << " ";
		}
	}
}

void page0(string(*map0)[10],int*p)
{
	system("cls");
	gotoxy(0, 0);
	cout << "Esc:主菜单";
	while (1)
	{
		int tx = 53;
		int ty = 20;
		gotoxy(tx,ty);
		for (int j = 0; j < 7; j++)
		{
			for (int i = 0; i < 10; i++)
			{
				gotoxy(tx + i, ty + j);
				cout << map0[j][i];
			}
		}
		gotoxy(0, 0);
		if (_kbhit())
		{
			int temp = _getch();
			if(temp==32)    //空格
			{
				*p = 1;
				break;
			}
			if (temp == 13)   //回车
			{
				system("cls");
				ifstream ifs("again存档数据.lh", ios::in);
				int buf = 1;
				ifs >> buf;                     //buf 关卡
				ifs.close();
				*p = buf;
				break;
			}
		}
    }
}


void page1(string (*map11)[61],int*p,int *pos_x,int *pos_y)
{
	system("cls");
	int tx = 29;
	int ty = 3;
	int x = 31 + *pos_x;
	int y = 20 + *pos_y;
	//--------------------------------------------------------------------------------------
	for (int j = 0; j < 35; j++)
	{
		for (int i = 0; i < 61; i++)
		{
			gotoxy(tx + i, ty + j);
			cout << map11[j][i];
		}
	}
	ifstream ifs2("again存档数据2.lh", ios::in);
	int fire = 0;
	ifs2 >> fire;
	ifs2.close();
	if (fire == 0)
	{
		gotoxy(84, 18);
		COLOR_PRINT("*", 4);
	}
	//--------------------------------------------------------------------------------------
	while (1)
	{
		gotoxy(x, y);
		COLOR_PRINT("*", 1);
		gotoxy(x, y);
		if (_kbhit())
		{
			int temp = _getch();
			if (temp == 65 || temp == 97)      //a
			{
				if (x == 31 and y == 20)
				{
					*p = 2;
					*pos_x = 56;
					*pos_y = 0;
					ofstream ofs("again存档数据.lh", ios::out);
					ofs << 1 << endl;
					ofs.close();
					break;
				}
				if (map11[y - ty][x - tx - 1] == " ")
				{
					cout << " ";
					x-=1;
				}
			}
			if (temp == 68 || temp == 100)     //d
			{
				if (x == 87 and y == 20)
				{
					*p = 2;
					*pos_x = 0;
					*pos_y = 0;
					ofstream ofs("again存档数据.lh", ios::out);
					ofs << 2 << endl;
					ofs.close();
					break;
				}
				if (map11[y - ty][x - tx + 1] == " ")
				{
					cout << " ";
					x+=1;
				}
			}
			if (temp == 87 || temp == 119)      //w
			{
				if (map11[y - ty - 1][x - tx] == " ")
				{
					cout << " ";
					y-=1;
				}
			}
			if (temp == 83 || temp == 115)     //s
			{
				if (x == 84 and y == 17)
				{
					ofstream ofs("again存档数据2.lh", ios::out);   //火种
					ofs << 1 << endl;                            //0是没有火种,1有
					ofs.close();
				}
				if (map11[y - ty + 1][x - tx] == " ")
				{
					cout << " ";
					y+=1;
				}
			}
			if (temp == 27)    //esc
			{
				*p = 0;
				*pos_x = 0;
				*pos_y = 0;
				break;
			}
		}
	}
	gotoxy(0, 0);
}


void page2(string(*map2)[61],int*p, int* pos_x, int* pos_y)
{
	system("cls");
	int fire = 0;
	ifstream ifs3("again存档数据2.lh", ios::in);
	ifs3 >> fire;
	ifs3.close();
	gotoxy(31,19);
	cout << "##";
	gotoxy(31, 21);
	cout << "##";
	gotoxy(86, 19);
	cout << "##";
	gotoxy(86, 21);
	cout << "##";

	int tx = 29;     //tx,ty:地图左上角坐标
	int ty = 3;
	
	int x = 31 + *pos_x;   //x,y:*坐标
	int y = 20 + *pos_y;

	//--------------------------------------------------------------------------------------
	while (fire == 0)
	{
		map2[y-ty][x-tx] = "*";
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				gotoxy(x - 1 + j, y - 1 + i);
				cout << map2[y-ty-1 + i][x-tx-1 + j];
			}
		}
		if (_kbhit())
		{
			int temp = _getch();
			if (temp == 65 || temp == 97)      //a
			{
				if (x == 31 and y == 20)
				{
					*p = 1;
					*pos_x = 56;
					*pos_y = 0;
					ofstream ofs("again存档数据.lh", ios::out);
					ofs << 2 << endl;
					ofs.close();
					break;
				}
				if (map2[y - ty][x - tx - 1] == " ")
				{
					map2[y - ty][x - tx] = " ";
					x -= 1;
					clear_map();
				}
			}
			if (temp == 68 || temp == 100)     //d
			{
				if (x == 87 and y == 20)
				{
					*p = 1;
					*pos_x = 0;
					*pos_y = 0;
					ofstream ofs("again存档数据.lh", ios::out);
					ofs << 1 << endl;
					ofs.close();
					break;
				}
				if (map2[y - ty][x - tx + 1] == " ")
				{
					map2[y - ty][x - tx] = " ";
					x += 1;
					clear_map();
				}
			}
			if (temp == 87 || temp == 119)      //w
			{
				if (map2[y - ty - 1][x - tx] == " ")
				{
					map2[y - ty][x - tx] = " ";
					y -= 1;
					clear_map();
				}
			}
			if (temp == 83 || temp == 115)     //s
			{
				if (map2[y - ty + 1][x - tx] == " ")
				{
					map2[y - ty][x - tx] = " ";
					y += 1;
					clear_map();
				}
			}
			if (temp == 27)    //esc
			{
				*p = 0;
				*pos_x = 0;
				*pos_y = 0;
				break;
			}
		}
	}
	while (fire == 1)
	{
		map2[y - ty][x - tx] = "*";
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				gotoxy(x - 2 + j, y - 2 + i);
				cout << map2[y - ty - 2 + i][x - tx - 2 + j];
			}
		}
		if (_kbhit())
		{
			int temp = _getch();
			if (temp == 65 || temp == 97)      //a
			{
				if (x == 31 and y == 20)
				{
					*p = 1;
					*pos_x = 56;
					*pos_y = 0;
					ofstream ofs("again存档数据.lh", ios::out);
					ofs << 2 << endl;
					ofs.close();
					break;
				}
				if (map2[y - ty][x - tx - 1] == " ")
				{
					map2[y - ty][x - tx] = " ";
					x -= 1;
					clear_map();
				}
			}
			if (temp == 68 || temp == 100)     //d
			{
				if (x == 87 and y == 20)
				{
					*p = 1;
					*pos_x = 0;
					*pos_y = 0;
					ofstream ofs("again存档数据.lh", ios::out);
					ofs << 1 << endl;
					ofs.close();
					break;
				}
				if (map2[y - ty][x - tx + 1] == " ")
				{
					map2[y - ty][x - tx] = " ";
					x += 1;
					clear_map();
				}
			}
			if (temp == 87 || temp == 119)      //w
			{
				if (map2[y - ty - 1][x - tx] == " ")
				{
					map2[y - ty][x - tx] = " ";
					y -= 1;
					clear_map();
				}
			}
			if (temp == 83 || temp == 115)     //s
			{
				if (map2[y - ty + 1][x - tx] == " ")
				{
					map2[y - ty][x - tx] = " ";
					y += 1;
					clear_map();
				}
			}
			if (temp == 27)    //esc
			{
				*p = 0;
				*pos_x = 0;
				*pos_y = 0;
				break;
			}
		}
	}
}

//生成地图0
void map_zero(string(*map0)[10])
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 10; j++)
			map0[i][j] = " ";
	}
	for (int i = 0; i < 10; i++)
	{
		map0[0][i] = "#";
		map0[3][i] = "#";
		map0[6][i] = "#";
	}
	for (int j = 0; j < 7; j++)
	{
		map0[j][0] = "#";
		map0[j][9] = "#";
	}
	map0[1][1]="回";
	map0[1][3] = "到";
	map0[1][5] = "起";
	map0[1][7] = "点";
	map0[2][1] = "*";
	map0[2][2] = "*";
	map0[2][3] = "空";
	map0[2][5] = "格";
	map0[2][7] = "*";
	map0[2][8] = "*";
	map0[4][1] = "旧";
	map0[4][3] = "的";
	map0[4][5] = "步";
	map0[4][7] = "伐";
	map0[5][1] = "*";
	map0[5][2] = "*";
	map0[5][3] = "回";
	map0[5][5] = "车";
	map0[5][7] = "*";
	map0[5][8] = "*";
}

//生成地图1
void map_one(string(*map1)[53])
{
	for (int j = 0; j < 27; j++)
	{
		for (int i = 0; i < 53; i++)
			map1[j][i] = " ";
	}
	for (int i = 0; i < 53; i++)
	{
		map1[0][i] = "#";
		map1[26][i] = "#";
	}
	for (int j = 0; j < 27; j++)
	{
		map1[j][0] = "#";
		map1[j][52] = "#";
	}
	map1[13][52] = " ";
	//========================================================第二行
	for (int i = 2; i < 13; i++)
		map1[2][i] = "#";
	for (int i = 16; i < 21; i++)
		map1[2][i] = "#";
	for (int i = 24; i < 27; i++)
		map1[2][i] = "#";
	for (int i = 30; i < 45; i++)
		map1[2][i] = "#";
	for (int i = 48; i < 51; i++)
		map1[2][i] = "#";
	//=======================================================第四行
	for (int i = 0; i < 5; i++)
		map1[4][i] = "#";
	for (int i = 10; i < 17; i++)
		map1[4][i] = "#";
	for (int i = 18; i < 21; i++)
		map1[4][i] = "#";
	for (int i = 24; i < 29; i++)
		map1[4][i] = "#";
	for (int i = 32; i < 37; i++)
		map1[4][i] = "#";
	for (int i = 40; i < 43; i++)
		map1[4][i] = "#";
	for (int i = 46; i < 49; i++)
		map1[4][i] = "#";
	//=====================================================第六行
	for (int i = 2; i < 7; i++)
		map1[6][i] = "#";
	for (int i = 14; i < 25; i++)
		map1[6][i] = "#";
	for (int i = 26; i < 29; i++)
		map1[6][i] = "#";
	for (int i = 32; i < 39; i++)
		map1[6][i] = "#";
	for (int i = 44; i < 49; i++)
		map1[6][i] = "#";
	//=====================================================第八行
	for (int i = 2; i < 13; i++)
		map1[8][i] = "#";
	for (int i = 18; i < 21; i++)
		map1[8][i] = "#";
	for (int i = 22; i < 25; i++)
		map1[8][i] = "#";
	for (int i = 28; i < 33; i++)
		map1[8][i] = "#";
	for (int i = 36; i < 39; i++)
		map1[8][i] = "#";
	for (int i = 40; i < 47; i++)
		map1[8][i] = "#";
	//=====================================================第十行
	for (int i = 6; i < 11; i++)
		map1[10][i] = "#";
	for (int i = 12; i < 15; i++)
		map1[10][i] = "#";
	for (int i = 16; i < 19; i++)
		map1[10][i] = "#";
	for (int i = 20; i < 23; i++)
		map1[10][i] = "#";
	for (int i = 26; i < 29; i++)
		map1[10][i] = "#";
	for (int i = 30; i < 35; i++)
		map1[10][i] = "#";
	for (int i = 44; i < 47; i++)
		map1[10][i] = "#";
	for (int i = 48; i < 51; i++)
		map1[10][i] = "#";
	//=====================================================第十二行
	for (int i = 0; i < 5; i++)
		map1[12][i] = "#";
	for (int i = 6; i < 9; i++)
		map1[12][i] = "#";
	for (int i = 10; i < 17; i++)
		map1[12][i] = "#";
	for (int i = 32; i < 40; i++)
		map1[12][i] = "#";
	for (int i = 42; i < 45; i++)
		map1[12][i] = "#";
	for (int i = 46; i < 53; i++)
		map1[12][i] = "#";
	//=====================================================第十四行
	for (int i = 0; i < 9; i++)
		map1[14][i] = "#";
	for (int i = 12; i < 15; i++)
		map1[14][i] = "#";
	for (int i = 16; i < 19; i++)
		map1[14][i] = "#";
	for (int i = 22; i < 25; i++)
		map1[14][i] = "#";
	for (int i = 28; i < 31; i++)
		map1[14][i] = "#";
	for (int i = 34; i < 37; i++)
		map1[14][i] = "#";
	for (int i = 40; i < 43; i++)
		map1[14][i] = "#";
	for (int i = 44; i < 47; i++)
		map1[14][i] = "#";
	for (int i = 48; i < 53; i++)
		map1[14][i] = "#";
	//=====================================================第十六行
	for (int i = 6; i < 11; i++)
		map1[16][i] = "#";
	for (int i = 16; i < 21; i++)
		map1[16][i] = "#";
	for (int i = 22; i < 27; i++)
		map1[16][i] = "#";
	for (int i = 30; i < 33; i++)
		map1[16][i] = "#";
	for (int i = 46; i < 49; i++)
		map1[16][i] = "#";
	//=====================================================第十八行
	for (int i = 2; i < 5; i++)
		map1[18][i] = "#";
	for (int i = 8; i < 19; i++)
		map1[18][i] = "#";
	for (int i = 20; i < 23; i++)
		map1[18][i] = "#";
	for (int i = 28; i < 31; i++)
		map1[18][i] = "#";
	for (int i = 32; i < 35; i++)
		map1[18][i] = "#";
	for (int i = 42; i < 47; i++)
		map1[18][i] = "#";
	//=====================================================第二十行
	for (int i = 0; i < 5; i++)
		map1[20][i] = "#";
	for (int i = 10; i < 13; i++)
		map1[20][i] = "#";
	for (int i = 14; i < 19; i++)
		map1[20][i] = "#";
	for (int i = 22; i < 27; i++)
		map1[20][i] = "#";
	for (int i = 28; i < 35; i++)
		map1[20][i] = "#";
	for (int i = 36; i < 39; i++)
		map1[20][i] = "#";
	for (int i = 42; i < 45; i++)
		map1[20][i] = "#";
	for (int i = 46; i < 49; i++)
		map1[20][i] = "#";
	//=====================================================第二二行
	for (int i = 8; i < 13; i++)
		map1[22][i] = "#";
	for (int i = 16; i < 25; i++)
		map1[22][i] = "#";
	for (int i = 26; i < 29; i++)
		map1[22][i] = "#";
	for (int i = 30; i < 43; i++)
		map1[22][i] = "#";
	for (int i = 44; i < 51; i++)
		map1[22][i] = "#";
	//=====================================================第二四行
	for (int i = 2; i < 9; i++)
		map1[24][i] = "#";
	for (int i = 10; i < 17; i++)
		map1[24][i] = "#";
	for (int i = 20; i < 23; i++)
		map1[24][i] = "#";
	for (int i = 24; i < 29; i++)
		map1[24][i] = "#";
	for (int i = 33; i < 45; i++)
		map1[24][i] = "#";
	for (int i = 46; i < 49; i++)
		map1[24][i] = "#";
	//=====================================================第二列
	for (int i = 6; i < 11; i++)
		map1[i][2] = "#";
	for (int i = 16; i < 19; i++)
		map1[i][2] = "#";
	for (int i = 22; i < 25; i++)
		map1[i][2] = "#";
	//=====================================================第四列
	for (int i = 10; i < 13; i++)
		map1[i][4] = "#";
	for (int i = 14; i < 19; i++)
		map1[i][4] = "#";
	for (int i = 20; i < 23; i++)
		map1[i][4] = "#";
	//=====================================================第六列
	for (int i = 2; i < 7; i++)
		map1[i][6] = "#";
	for (int i = 10; i < 13; i++)
		map1[i][6] = "#";
	for (int i = 16; i < 25; i++)
		map1[i][6] = "#";
	//=====================================================第八列
	for (int i = 0; i < 3; i++)
		map1[i][8] = "#";
	for (int i = 4; i < 9; i++)
		map1[i][8] = "#";
	for (int i = 16; i < 23; i++)
		map1[i][8] = "#";
	for (int i = 24; i < 27; i++)
		map1[i][8] = "#";
	//=====================================================第十列
	for (int i = 4; i < 7; i++)
		map1[i][10] = "#";
	for (int i = 10; i < 17; i++)
		map1[i][10] = "#";
	//=====================================================第十二列
	for (int i = 2; i < 5; i++)
		map1[i][12] = "#";
	for (int i = 6; i < 11; i++)
		map1[i][12] = "#";
	for (int i = 14; i < 19; i++)
		map1[i][12] = "#";
	for (int i = 20; i < 23; i++)
		map1[i][12] = "#";
	//=====================================================第十四列
	for (int i = 0; i < 3; i++)
		map1[i][14] = "#";
	for (int i = 8; i < 11; i++)
		map1[i][14] = "#";
	for (int i = 14; i < 17; i++)
		map1[i][14] = "#";
	for (int i = 20; i < 25; i++)
		map1[i][14] = "#";
	//=====================================================第十六列
	for (int i = 2; i < 5; i++)
		map1[i][16] = "#";
	for (int i = 6; i < 11; i++)
		map1[i][16] = "#";
	for (int i = 12; i < 17; i++)
		map1[i][16] = "#";
	for (int i = 22; i < 25; i++)
		map1[i][16] = "#";
	//=====================================================第十八列
	for (int i = 4; i < 7; i++)
		map1[i][18] = "#";
	for (int i = 8; i < 13; i++)
		map1[i][18] = "#";
	for (int i = 24; i < 27; i++)
		map1[i][18] = "#";
	//=====================================================第二十列
	for (int i = 10; i < 17; i++)
		map1[i][20] = "#";
	for (int i = 18; i < 23; i++)
		map1[i][20] = "#";
	//=====================================================第二二列
	for (int i = 0; i < 5; i++)
		map1[i][22] = "#";
	for (int i = 8; i < 13; i++)
		map1[i][22] = "#";
	for (int i = 14; i < 17; i++)
		map1[i][22] = "#";
	for (int i = 18; i < 21; i++)
		map1[i][22] = "#";
	for (int i = 24; i < 27; i++)
		map1[i][22] = "#";
	//=====================================================第二四列
	for (int i = 2; i < 5; i++)
		map1[i][24] = "#";
	for (int i = 6; i < 9; i++)
		map1[i][24] = "#";
	for (int i = 10; i < 15; i++)
		map1[i][24] = "#";
	for (int i = 16; i < 19; i++)
		map1[i][24] = "#";
	for (int i = 22; i < 25; i++)
		map1[i][24] = "#";
	//=====================================================第二六列
	for (int i = 6; i < 9; i++)
		map1[i][26] = "#";
	for (int i = 12; i < 23; i++)
		map1[i][26] = "#";
	//=====================================================第二八列
	for (int i = 0; i < 7; i++)
		map1[i][28] = "#";
	for (int i = 8; i < 19; i++)
		map1[i][28] = "#";
	for (int i = 20; i < 23; i++)
		map1[i][28] = "#";
	//=====================================================第三十列
	for (int i = 2; i < 9; i++)
		map1[i][30] = "#";
	for (int i = 10; i < 13; i++)
		map1[i][30] = "#";
	for (int i = 16; i < 19; i++)
		map1[i][30] = "#";
	for (int i = 22; i < 27; i++)
		map1[i][30] = "#";
	//=====================================================第三二列
	for (int i = 4; i < 7; i++)
		map1[i][32] = "#";
	for (int i = 14; i < 19; i++)
		map1[i][32] = "#";
	//=====================================================第三四列
	for (int i = 6; i < 11; i++)
		map1[i][34] = "#";
	for (int i = 14; i < 17; i++)
		map1[i][34] = "#";
	for (int i = 18; i < 21; i++)
		map1[i][34] = "#";
	for (int i = 24; i < 27; i++)
		map1[i][34] = "#";
	//=====================================================第三六列
	for (int i = 8; i < 13; i++)
		map1[i][36] = "#";
	for (int i = 14; i < 21; i++)
		map1[i][36] = "#";
	//=====================================================第三八列
	for (int i = 2; i < 7; i++)
		map1[i][38] = "#";
	for (int i = 8; i < 11; i++)
		map1[i][38] = "#";
	for (int i = 12; i < 21; i++)
		map1[i][38] = "#";
	//=====================================================第四十列
	for (int i = 4; i < 13; i++)
		map1[i][40] = "#";
	for (int i = 14; i < 23; i++)
		map1[i][40] = "#";
	//=====================================================第四二列
	for (int i = 4; i < 7; i++)
		map1[i][42] = "#";
	for (int i = 8; i < 11; i++)
		map1[i][42] = "#";
	for (int i = 12; i < 17; i++)
		map1[i][42] = "#";
	//=====================================================第四四列
	for (int i = 2; i < 7; i++)
		map1[i][44] = "#";
	for (int i = 10; i < 13; i++)
		map1[i][44] = "#";
	for (int i = 14; i < 19; i++)
		map1[i][44] = "#";
	for (int i = 20; i < 25; i++)
		map1[i][44] = "#";
	//=====================================================第四六列
	for (int i = 0; i < 3; i++)
		map1[i][46] = "#";
	for (int i = 8; i < 11; i++)
		map1[i][46] = "#";
	for (int i = 12; i < 15; i++)
		map1[i][46] = "#";
	for (int i = 18; i < 21; i++)
		map1[i][46] = "#";
	//=====================================================第四八列
	for (int i = 2; i < 11; i++)
		map1[i][48] = "#";
	for (int i = 16; i < 21; i++)
		map1[i][48] = "#";
	for (int i = 24; i < 27; i++)
		map1[i][48] = "#";
	//=====================================================第五十列
	for (int i = 2; i < 9; i++)
		map1[i][50] = "#";
	for (int i = 10; i < 13; i++)
		map1[i][50] = "#";
	for (int i = 16; i < 25; i++)
		map1[i][50] = "#";
}  //生成

//生成地图map11
void map_eleven(string(*map1)[53],string(*map11)[61])
{
	for (int i = 0; i < 61; i++)
	{
		map11[0][i] = " ";
		map11[1][i] = " ";
		map11[31][i] = " ";
		map11[32][i] = " ";
		map11[2][i] = " ";
		map11[3][i] = " ";
		map11[33][i] = " ";
		map11[34][i] = " ";
	}
	for (int i = 0; i < 35; i++)
	{
		map11[i][0] = " ";
		map11[i][1] = " ";
		map11[i][57] = " ";
		map11[i][58] = " ";
		map11[i][2] = " ";
		map11[i][3] = " ";
		map11[i][59] = " ";
		map11[i][60] = " ";
	}
	for(int i=0;i<27;i++)
		for (int j = 0; j < 53; j++)
		{
			map11[i+4][j+4] = map1[i][j];
		}
	map11[17][4] = " ";
	map11[16][2] = "#";
	map11[16][3] = "#";
	map11[18][2] = "#";
	map11[18][3] = "#";

	map11[16][57] = "#";
	map11[16][58] = "#";
	map11[18][57] = "#";
	map11[18][58] = "#";
}

//生成地图二
void map_two(string(*map11)[61],string(*map2)[61])
{
	for (int i = 0; i < 35; i++)
	{
		for (int j = 0; j < 61; j++)
			map2[i][j] = map11[i][60 - j];
	}
}


int main()
{
	HideCursor(); //隐藏光标
	SetWindowLongPtrA(GetConsoleWindow(), GWL_STYLE, GetWindowLongPtrA(GetConsoleWindow(), GWL_STYLE) & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
	SetConsoleTitleA("cycle");

	ifstream ifs("again存档数据.lh", ios::in);
	if (!ifs)
	{
		ofstream ofs("again存档数据.lh", ios::out);   //关卡
		ofs << 1 << endl;
		ofs.close();
	}
	ifs.close();

	ifstream ifs2("again存档数据2.lh", ios::in);
	if (!ifs2)
	{
		ofstream ofs("again存档数据2.lh", ios::out);   //火种
		ofs << 0 << endl;                            //0是没有火种
		ofs.close();
	}
	ifs2.close();


	int page = 0;
	int* p = &page;

	string(*map0)[10] = new string[7][10];
	string(*map1)[53] = new string[27][53];
	string(*map11)[61] = new string[35][61];    //由于map1地图小了map11是map1的加大
	string(*map2)[61] = new string[35][61];


	map_zero(map0);
	map_one(map1);
	map_eleven(map1, map11);
	map_two(map11, map2);

	int posx = 0;
	int posy = 0;
	int* pos_x = &posx;
	int* pos_y = &posy;

	while (1)
	{
		if(page==0)
			page0(map0,p);
		if(page==1)
			page1(map11,p,pos_x,pos_y);
		if(page==2)
			page2(map2,p, pos_x, pos_y);
	}
	delete[] map0;
	delete[] map1;
	delete[] map2;
	delete[] map11;
	return 0;
}