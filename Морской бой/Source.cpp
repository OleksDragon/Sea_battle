#include<iostream>
#include<conio.h>
#include<windows.h>
#include <ctime>
#include<cstdlib>
using namespace std;

enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // �������� ���������� � ���������� ���������� (����������� �����)

const int S = 12; // ������ ����
int ship_number = 4; // ����� �������, ������� ������������ � �������

void SetColor(ConsoleColor text, ConsoleColor background); //�������� ���� ������
void SetCursor(short x, short y); //������������� ������� ������� �� �����������
void lineUp(int x, int y); // ������� ����� ����
void lineVertical(int x, int y); // ������������ ����� ����
void lineCross(int x, int y); // ��������� ����� ����
void lineDown(int x, int y); // ������ ����� ����
void letters(int x, int y); // ����� �� ����
void numbers(int x, int y); // ����� �� ����
void map_comp(const int x1, const int y); // ���� 1 � ������������
void map_player(const int x1, const int y, const int rast); // ���� 2 � ������������
void show_player(const int x1, const int y, const int rast); // ������� PLAYER �������
void title(); // ��������� ��������
void choice_placement(char placement[2][30], int n);  // ����� �����������
void show_pos(int arr[][S], int x, int y, int a, int b, int d); // ����� �������� � ��������� ���� ������
void show_pos_comp(int arr[][S], int x, int y, int a, int b); // ����� �������� � ��������� ���� ����������
int placement_ship(int arr[][S], int ship_deck, int ship_count, int& ship_number); // ������������� ����������� � �������� ��������
void auto_placement(int arr[][S]); // ������������� ����������� ��������
void ship_show(int x, int y, int urdl, int ship_deck, int moveRight, int  moveDown); // ����� �� ����� ������� ������ ���������
bool ship_exam(int x, int y, int urdl, int ship_deck, int startCoordX, int startCoordY, const int rast, int moveRight, int moveDown); // �������� ���������� ������� � �������� ����
bool exam_ship_arr(int arr[][S], int x, int y, int urdl, int ship_deck, int ship_number); // �������� ������ ��������� �������
void show_placement_ships(int boats); // ������� ��� ������ ��������� ��������
void ship_sunk(int arr[][S], int S); // ��������� ��������� �������
void computer_move(int player_ship[][S], int S, int& xc, int& yc, int& live, int& mode, bool shooting); // �������� ���������

int main()
{
	char placement[2][30] = { " AUTOMATIC  PLACEMENT "," MANUAL     PLACEMENT " };

	int player_ship[S][S] = { 0 }; // ���� � ��������� ������
	int comp_ship[S][S] = { 0 }; // ���� � ��������� ����������

	const int startCoordX = 10; // ���������� X ��� ��������� ������� �������
	const int startCoordY = 6; // ���������� Y ��� ��������� ������� �������
	const int rast = 65; // ���������� ����� ��������� �������� ����1 � ����2
	const int moveRight = 4; // �������� ������ �+=4
	const int moveDown = 2; // �������� ���� Y+=2
	const int number_of_ships = 10; // ���������� ��������	
	int live4 = 4, live5 = 3, live6 = 3, live7 = 2, live8 = 2, live9 = 2, live = 0;
	int urdl_c = 0, mode = 0, start;	

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE); // �������� ���������� � ���������� ���������� (����������� �����)

	COORD cPos = { startCoordX + 1, startCoordY + 1 }; // ���������� X=4 � Y=10 ��� ��������� ������� �������

	title(); // ����� �������� ����
	SetCursor(0, 0);
	Sleep(3000);
	system("cls"); //������� �������	

#pragma region ����������� ��������
	int choice = 1, A = 0;
	bool manual_placement = true;
	
	int y_choice = 2;

	do //��������� ����
	{
		choice_placement(placement, choice);
		int code = _getch(); // �������� ������� �������	
		if (code == 224) // ������ �������
		{
			code = _getch();
		}
		else if (code == 13)
		{
			do
			{
				switch (choice)
				{
				case 0: // e��� 0
					manual_placement = false; //�������������� �������o���
					A++;
					break;
				case 1:
					manual_placement = true; //������ �����������
					A++;
					y_choice++;
					break;
				}
			} while (code != 13);
		}
		switch (code) 
		{
		case 72: //���� ������ "��������� �����"
			if (y_choice > 0) 
			{
				y_choice--; 
				choice = y_choice; //��������� �����
				choice_placement(placement, choice); //����� ������� �� �����
			}
			break;
		case 80: //���� ������ "��������� ����"
			if (y_choice < 1) 
			{
				y_choice++; 
				choice = y_choice; //��������� �����
				choice_placement(placement, choice); //����� ������� �� �����
			}
			break;
		}
	} while (A < 1);

	// �������������� ����������� ��������
	if (manual_placement == false)
	{
		int n;
		system("cls"); //������� �������
		SetCursor(46, 13);
		SetColor(LightGreen, Black); // ����� �����
		cout << "AUTOMATIC ARRANGEMENT OF SHIPS";
		SetCursor(0, 0);
		Sleep(2000);
		system("cls"); //������� �������
		Sleep(1000);

		do
		{
			SetCursor(20, 13);
			SetColor(LightBlue, Black);
			cout << "TO CHANGE THE LOCATION PRESS ANY KEY";
			SetColor(Yellow, Black);
			SetCursor(22, 17);
			cout << "PRESS INTER TO CONFIRM LOCATION";
			map_player(startCoordX, startCoordY, rast); // ������� ���� 2
			Sleep(1000);
			auto_placement(player_ship); // �������������� ����������� �������� ������
			show_pos(player_ship, startCoordX + 1, startCoordY + 1, moveRight, moveDown, rast); // ����� �������� � ���������

			SetCursor(0, 0);
			n = _getch();
			system("cls"); // ������� ������
			if (n != 13)
			{
				for (int i = 0; i < S; i++)
				{
					for (int j = 0; j < S; j++)
					{
						player_ship[i][j] = 0;
					}
				}
			}
		} while (n != 13);		
	}

	// ������ ����������� ��������
	else if (manual_placement == true)
	{
		system("cls"); //������� �������
		SetCursor(50, 13);
		SetColor(LightGreen, Black); // ����� �����
		cout << "MANUAL ARRANGEMENT OF SHIPS";
		SetCursor(0, 0);
		Sleep(2000);
		system("cls"); //������� �������
		Sleep(1000);
		//map_comp(startCoordX, startCoordY); // ������� ���� 1
		map_player(startCoordX, startCoordY, rast); // ������� ���� 2
		Sleep(2000);

		//COORD cPos = { startCoordX + rast +1, startCoordY + 1 }; // ���������� X=4 � Y=10 ��� ��������� ������� �������	
		int ship_deck = 4;
		int ship_count = 1;
		int boats = 0;
		int urdl = 0;
		int x = startCoordX + rast + 1;
		int y = startCoordY + 1;
		int code;

		while (boats < number_of_ships)
		{
			int i = 0;
			while (i < ship_count)
			{
				int j = 0;
				while (j < 1)
				{
					system("cls"); //������� �������
					map_player(startCoordX, startCoordY, rast); // ������� ���� 2			
					show_pos(player_ship, startCoordX + 1, startCoordY + 1, moveRight, moveDown, rast);
					ship_show(x, y, urdl, ship_deck, moveRight, moveDown);
					show_placement_ships(boats);

					int temp_x = x;
					int temp_y = y;
					int temp_urdl = urdl;
					int x1 = ((x - startCoordX - 1 - rast) / moveRight) + 1;
					int y1 = ((y - startCoordY - 1) / moveDown) + 1;

					SetColor(LightGray, Black); // ����� �����					
					code = _getch();
					if (code == 224) // ������ �������
					{
						code = _getch();
					}
					else if (code == 13)
					{
						if (exam_ship_arr(player_ship, x1, y1, urdl, ship_deck, ship_number))
						{
							urdl = 0;
							x = x1;
							y = y1;
							j++;
							boats++;
							ship_number++;
						}
					}
					switch (code)
					{
					case 72: // ������ ������� �����				
						y -= moveDown;
						break;
					case 77: // ������ ������� ������				
						x += moveRight;// �������� ������ X +=4				
						break;
					case 75: // ������ ������� �����				
						x -= moveRight;
						break;
					case 80: // ������ ������� ����				
						y += moveDown;// �������� ���� Y+=2				
						break;
					case 32: // ����� ������			
						urdl = !urdl; // �������� �������
						break;
					}
					if (!ship_exam(x, y, urdl, ship_deck, startCoordX, startCoordY, rast, moveRight, moveDown))
					{
						x = temp_x;
						y = temp_y;
						urdl = temp_urdl;
					}
				}
				i++;
			}
			ship_count++;
			ship_deck--;
		}		
	}

#pragma endregion ����������� ��������

	Sleep(1000);
	ship_number = 4;
	auto_placement(comp_ship); // ����������� �������� ����������
	//show_pos(comp_ship, startCoordX + 1, startCoordY + 1, moveRight, moveDown, 0); // ����� �������� � ��������� ����������	

	system("cls"); //������� �������
	SetCursor(54, 13);
	SetColor(LightGreen, Black); // ����� �����
	cout << "S T A R T  G A M E";
	SetCursor(0, 0);
	Sleep(2000);
	system("cls"); //������� �������
	Sleep(1000);

	bool whole_ships_player;
	bool whole_ships_comp;
	bool shooting = true;
	
	int xc = 0, yc = 0;
	
	srand(time(NULL));
	start = 0 + rand() % 2;

	if (start == 0)
	{
		system("cls"); //������� �������
		SetCursor(54, 13);
		SetColor(LightGreen, Black); // ����� �����
		cout << "PLAYER FIRST SHOT";
		SetCursor(0, 0);
		Sleep(2000);
		system("cls"); //������� �������
		Sleep(1000);
	}
	if (start == 1)
	{
		system("cls"); //������� �������
		SetCursor(54, 13);
		SetColor(LightGreen, Black); // ����� �����
		cout << "COMPUTER FIRST SHOT";
		SetCursor(0, 0);
		Sleep(2000);
		system("cls"); //������� �������
		Sleep(1000);
	}
			
	do
	{		
		if (start == 0) // ������� ������
		{
			do
			{
				system("cls"); // ������� ������
				map_comp(startCoordX, startCoordY); // ������� ���� 1
				map_player(startCoordX, startCoordY, rast); // ������� ���� 2
				show_pos(player_ship, startCoordX + 1, startCoordY + 1, moveRight, moveDown, rast); // ����� �������� � ���������	
				show_pos_comp(comp_ship, startCoordX + 1, startCoordY + 1, moveRight, moveDown); // ����� �������� � ��������� ����������

				SetConsoleCursorPosition(hCon, cPos); // ��������� ������� �������	
				SetColor(LightGreen, Black); // ����� �����
				cout << (char)219 << (char)219 << (char)219; // ������		

				int code = _getch(); // �������� ������� �������	
				if (code == 224) // ������ �������
				{
					code = _getch();
				}
				else if (code == 13)
				{
					int t_ship = 0;

					int x = ((cPos.X - startCoordX - 1) / moveRight) + 1;
					int y = ((cPos.Y - startCoordY - 1) / moveDown) + 1;

					if (comp_ship[y][x] == 0)
					{
						comp_ship[y][x] = 2;
						break;
					}
					else if (comp_ship[y][x] >= 4)
					{
						t_ship = comp_ship[y][x];
						comp_ship[y][x] = 3;
						cout << "\a";
					}
					bool n2 = 1;
					for (int i = 1; i < S - 1; i++)
					{
						for (int j = 0; j < S - 1; j++)
						{
							if (comp_ship[i][j] == t_ship)
							{
								n2 = 0;
							}
						}
					}
					if (n2 == 1)
					{
						ship_sunk(comp_ship, S);
					}
				}

				switch (code)
				{
				case 72: // ������ ������� �����
					if (cPos.Y - moveDown > startCoordY - 1)
					{
						cPos.Y -= moveDown;
					}
					break;
				case 77: // ������ ������� ������
					if (cPos.X - moveRight < startCoordX + 32)
					{
						cPos.X += moveRight;// �������� ������ X +=4
					}
					break;
				case 75: // ������ ������� �����
					if (cPos.X - moveRight > startCoordX)
					{
						cPos.X -= moveRight;
					}
					break;
				case 80: // ������ ������� ����
					if (cPos.Y - moveDown < startCoordY + 17)
					{
						cPos.Y += moveDown;// �������� ���� Y+=2
					}
					break;
				}

				whole_ships_player = false;

				for (int i = 0; i < S; i++)
				{
					for (int j = 0; j < S; j++)
					{
						if (comp_ship[i][j] >= 4)
						{
							whole_ships_player = true;
						}
					}
				}
			} while (whole_ships_player == true);
			start = 1;
		}
		
		if (start == 1) // ������� ����������
		{
			system("cls"); // ������� ������
			map_comp(startCoordX, startCoordY); // ������� ���� 1
			map_player(startCoordX, startCoordY, rast); // ������� ���� 2
			show_pos(player_ship, startCoordX + 1, startCoordY + 1, moveRight, moveDown, rast); // ����� �������� � ���������	
			show_pos_comp(comp_ship, startCoordX + 1, startCoordY + 1, moveRight, moveDown); // ����� �������� � ��������� ����������
			show_player(startCoordX, startCoordY, rast);

			do
			{
				if (mode == 0)
				{
					do
					{
						srand(time(NULL));						
						xc = 1 + rand() % 10;
						yc = 1 + rand() % 10;
						if (player_ship[yc][xc] == 0)
						{
							player_ship[yc][xc] = 2;
							shooting = false;
							break;
						}
						else if (player_ship[yc][xc] >= 4)
						{
							shooting = true;
							mode = 1;
							break;
						}
					} while (player_ship[yc][xc] > 1);
				}

				if (mode == 1 && shooting == false)
				{
					computer_move(player_ship, S, xc, yc, live, mode, shooting); // �������� ���������
				}

				if (mode == 1 && shooting == true)
				{
					if (player_ship[yc][xc] == 4)
					{
						player_ship[yc][xc] = 3;
						cout << "\a";
						show_player(startCoordX, startCoordY, rast);
						live4--;
						live = live4;
						computer_move(player_ship, S, xc, yc, live, mode, shooting); // �������� ���������
					}
					else if (player_ship[yc][xc] == 5)
					{
						player_ship[yc][xc] = 3;
						cout << "\a";
						show_player(startCoordX, startCoordY, rast);
						live5--;
						live = live5;
						computer_move(player_ship, S, xc, yc, live, mode, shooting); // �������� ���������
					}
					else if (player_ship[yc][xc] == 6)
					{
						player_ship[yc][xc] = 3;
						cout << "\a";
						show_player(startCoordX, startCoordY, rast);
						live6--;
						live = live6;
						computer_move(player_ship, S, xc, yc, live, mode, shooting); // �������� ���������
					}
					else if (player_ship[yc][xc] == 7)
					{
						player_ship[yc][xc] = 3;
						cout << "\a";
						show_player(startCoordX, startCoordY, rast);
						live7--;
						live = live7;
						computer_move(player_ship, S, xc, yc, live, mode, shooting); // �������� ���������
					}
					else if (player_ship[yc][xc] == 8)
					{
						player_ship[yc][xc] = 3;
						cout << "\a";
						show_player(startCoordX, startCoordY, rast);
						live8--;
						live = live8;
						computer_move(player_ship, S, xc, yc, live, mode, shooting); // �������� ���������
					}
					else if (player_ship[yc][xc] == 9)
					{
						player_ship[yc][xc] = 3;
						cout << "\a";
						show_player(startCoordX, startCoordY, rast);
						live9--;
						live = live9;
						computer_move(player_ship, S, xc, yc, live, mode, shooting); // �������� ���������
					}
					else if (player_ship[yc][xc] >= 10 && player_ship[yc][xc] < 14)
					{
						cout << "\a";
						player_ship[yc][xc] = 3;
						show_player(startCoordX, startCoordY, rast);
						mode = 0;
						shooting = true;
						ship_sunk(player_ship, S);
					}
				}

				if (mode == 4 && shooting == false)
				{
					mode = 1;
					computer_move(player_ship, S, xc, yc, live, mode, shooting); // �������� ���������
					show_player(startCoordX, startCoordY, rast);
				}

				if (mode == 3)
				{
					mode = 4;
					shooting = false;
					break;
				}

				whole_ships_comp = true;
				for (int i = 0; i < S; i++)
				{
					for (int j = 0; j < S; j++)
					{
						if (player_ship[i][j] >= 4)
						{
							whole_ships_comp = false;
						}
					}
				}
				if (whole_ships_comp)
				{
					break;
				}
			} while (shooting);
			start = 0;
		}

		whole_ships_player = false;
		whole_ships_comp = true;
		for (int i = 0; i < S; i++)
		{
			for (int j = 0; j < S; j++)
			{
				if (comp_ship[i][j] >= 4)
				{
					whole_ships_player = true;
				}
				if (player_ship[i][j] >= 4)
				{
					whole_ships_comp = false;
				}
			}
		}

	} while ((whole_ships_player == true && whole_ships_comp == false) || (whole_ships_player == false && whole_ships_comp == true));

	if (whole_ships_player == false)
	{
		system("cls"); //������� �������
		SetCursor(44, 13);
		SetColor(LightGreen, Black); // ����� �����
		cout << "C O N G R A T U L A T I O N S !";
		SetCursor(54, 17);
		cout << "Y O U  W I N !";
		SetCursor(0, 0);
		Sleep(4000);
	}

	if (whole_ships_comp == true)
	{
		system("cls"); //������� �������
		SetCursor(54, 13);
		SetColor(LightRed, Black); // ����� �����
		cout << "Y O U  L O S E!";
		SetCursor(0, 0);
		Sleep(4000);
	}

	system("cls"); //������� �������
	SetCursor(54, 13);
	SetColor(LightBlue, Black); // ����� �����
	cout << "G A M E  O W E R";
	SetCursor(0, 0);
	Sleep(4000);
	system("cls"); //������� �������

	SetColor(White, Black); // ����� �����
	system("pause");
	return 0;
}

//�������� ���� ������
void SetColor(ConsoleColor text, ConsoleColor background)
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

//������������� ������� ������� �� �����������
void SetCursor(short x, short y)
{
	COORD cPos = { x, y }; // ���������� x � y ��� ��������� ������� �������
	SetConsoleCursorPosition(hStdOut, cPos);
}

// ������� ����� ����
void lineUp(int x, int y)
{
	SetCursor(x, y);
	cout << (char)201;
	cout << (char)205;
	for (int i = 1; i < 10; i++)
	{
		cout << (char)205;
		cout << (char)205;
		cout << (char)203;
		cout << (char)205;
	}
	cout << (char)205;
	cout << (char)205;
	cout << (char)187;
}

// ������������ ����� ����
void lineVertical(int x, int y)
{
	for (int i = 0; i < 10; i++)
	{
		SetCursor(x, y);
		for (int j = 0; j <= 10; j++)
		{
			cout << "  ";
			cout << (char)186;
			cout << " ";
		}
		y += 2;
	}
}

// ��������� ����� ����
void lineCross(int x, int y)
{
	for (int i = 1; i < 10; i++)
	{
		SetCursor(x, y);
		cout << (char)204;
		cout << (char)205;
		for (int j = 1; j < 10; j++)
		{
			cout << (char)205;
			cout << (char)205;
			cout << (char)206;
			cout << (char)205;
		}
		cout << (char)205;
		cout << (char)205;
		cout << (char)185;
		y += 2;
	}
}

// ������ ����� ����
void lineDown(int x, int y)
{
	SetCursor(x, y);
	cout << (char)200;
	cout << (char)205;
	for (int i = 1; i < 10; i++)
	{
		cout << (char)205;
		cout << (char)205;
		cout << (char)202;
		cout << (char)205;
	}
	cout << (char)205;
	cout << (char)205;
	cout << (char)188;
}

// ����� �� ����
void letters(int x, int y)
{
	char arrBukv[10] = { 'A','B','C','D','E','F','G','H','I','J' };
	for (size_t i = 0; i < 10; i++)
	{
		SetCursor(x, y - 1);
		cout << arrBukv[i];
		x += 4;
	}
}

// ����� �� ����
void numbers(int x, int y)
{
	for (int i = 1; i < 11; i++)
	{
		SetCursor(x - 3, y);
		cout << i << endl;
		y += 2;
	}
}

// ���� 1 � ������������
void map_comp(const int x1, const int y)
{
	SetColor(White, Black); // ����� �����

	//���� 1	
	lineUp(x1, y); // ������� ����� ����		
	lineVertical(x1 - 2, y + 1); // ������������ ����� ����
	lineCross(x1, y + 2); // ��������� ����� ����	
	lineDown(x1, y + 20); // ������ ����� ����			
	letters(x1 + 2, y); // ����� �� ����	
	numbers(x1, y + 1); // ����� �� ����
	SetColor(Yellow, Black);
	SetCursor(x1 + 13, y - 4);
	cout << "C O M P U T E R";
	SetCursor(0, 0);
}

// ���� 2 � ������������
void map_player(const int x1, const int y, const int rast)
{
	SetColor(White, Black); // ����� �����
	const int x2 = x1 + rast;

	// ���� 2	
	lineUp(x2, y); // ������� ����� ����	
	lineVertical(x2 - 2, y + 1); // ������������ ����� ����
	lineCross(x2, y + 2); // ��������� ����� ����	
	lineDown(x2, y + 20); // ������ ����� ����		
	letters(x2 + 2, y); // ����� �� ����	
	numbers(x2, y + 1); // ����� �� ����
	SetColor(Yellow, Black);
	SetCursor(x2 + 15, y - 4);
	cout << "P L A Y E R";
	SetCursor(0, 0);
}

// ������� PLAYER �������
void show_player(const int x1, const int y, const int rast)
{
	int x2 = x1 + rast;
	SetColor(Red, Black);
	SetCursor(x2 + 15, y - 4);
	cout << "P L A Y E R";
	SetCursor(0, 0);
}

// ��������� ��������
void title()
{
	SetColor(LightBlue, Black); // ����� �����
	SetCursor(52, 13);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX fontInfo = { sizeof(CONSOLE_FONT_INFOEX) };
	GetCurrentConsoleFontEx(hConsole, false, &fontInfo);
	fontInfo.dwFontSize.X = 10;
	fontInfo.dwFontSize.Y = 20;
	SetCurrentConsoleFontEx(hConsole, false, &fontInfo);
	cout << "S E A   B A T T L E";
}

// ����� �����������
void choice_placement(char placement[2][30], int n)
{
	system("cls");
	for (int i = 0; i < 2; i++)
	{
		SetCursor(50, 8 + i);
		for (int j = 0; j < 30; j++)
		{
			if (i == n)
			{
				SetColor(Black, White);
			}
			else
			{
				SetColor(White, Black);
			}
			cout << placement[i][j];
		}
	}
	SetColor(LightBlue, Black); // ����� �����
	SetCursor(40, 13);
	cout << "USE THE " << (char)30 << " AND " << (char)31 << " BUTTONS TO SELECT A LAYOUT";
	SetCursor(0, 0);
}

// ����� �������� � ��������� ���� ������
void show_pos(int arr[][S], int x, int y, int a, int b, int d)
{
	x += d;
	for (int i = 1; i < 11; i++)
	{
		SetCursor(x, y);
		y += b;
		for (int j = 1; j < 11; j++)
		{
			if (arr[i][j] == 0)
			{
				SetColor(Black, Black); // ����� �����
				cout << (char)219 << (char)219 << (char)219;
				SetColor(White, Black); // ����� �����
				cout << (char)186;
			}
			else if (arr[i][j] >= 4)
			{
				SetColor(LightBlue, Black); // ����� �����				
				cout << (char)219 << (char)219 << (char)219;
				SetColor(White, Black); // ����� �����
				cout << (char)186;
			}
			else if (arr[i][j] == 2)
			{
				SetColor(DarkGray, Black); // ����� �����
				cout << (char)219 << (char)219 << (char)219;
				SetColor(White, Black); // ����� �����
				cout << (char)186;
			}
			else if (arr[i][j] == 3)
			{
				SetColor(Red, Black); // ����� �����
				cout << (char)219 << (char)219 << (char)219;
				SetColor(White, Black); // ����� �����
				cout << (char)186;
			}
			else if (arr[i][j] == 1)
			{
				SetColor(DarkGray, Black); // ����� �����
				cout << (char)219 << (char)219 << (char)219;
				SetColor(White, Black); // ����� �����
				cout << (char)186;
			}
		}
	}
}

// ����� �������� � ��������� ���� ����������
void show_pos_comp(int arr[][S], int x, int y, int a, int b)
{
	for (int i = 1; i < 11; i++)
	{
		SetCursor(x, y);
		y += b;
		for (int j = 1; j < 11; j++)
		{
			if (arr[i][j] == 0)
			{
				SetColor(Black, Black); // ����� �����
				cout << (char)219 << (char)219 << (char)219;
				SetColor(White, Black); // ����� �����
				cout << (char)186;
			}
			else if (arr[i][j] >= 4)
			{
				SetColor(Black, Black); // ����� �����	LightBlue			
				cout << (char)219 << (char)219 << (char)219;
				SetColor(White, Black); // ����� �����
				cout << (char)186;
			}
			else if (arr[i][j] == 2)
			{
				SetColor(DarkGray, Black); // ����� �����
				cout << (char)219 << (char)219 << (char)219;
				SetColor(White, Black); // ����� �����
				cout << (char)186;
			}
			else if (arr[i][j] == 3)
			{
				SetColor(Red, Black); // ����� �����
				cout << (char)219 << (char)219 << (char)219;
				SetColor(White, Black); // ����� �����
				cout << (char)186;
			}
			else if (arr[i][j] == 1)
			{
				SetColor(DarkGray, Black); // ����� �����
				cout << (char)219 << (char)219 << (char)219;
				SetColor(White, Black); // ����� �����
				cout << (char)186;
			}
		}
	}
}

// ������������� ����������� � �������� ��������
int placement_ship(int arr[][S], int ship_deck, int ship_count, int& ship_number)
{
	int n = 11;
	bool setting_is_possible = 1;
	int x, y;
	int urdl;
	int temp_x;
	int temp_y;
	int count_ship = 0;

	while (count_ship < ship_count)
	{
		srand(time(NULL));
		do
		{
			x = 1 + rand() % n;
			y = 1 + rand() % n;
			temp_x = x;
			temp_y = y;
			urdl = 0 + rand() % 4;
			setting_is_possible = 1;
			for (int i = 0; i < ship_deck; ++i)
			{
				if (x < 1 || y < 1 || x >= n || y >= n)
				{
					setting_is_possible = 0;
					break;
				}
				if (arr[y][x] >= 4 ||
					arr[y][x + 1] >= 4 ||
					arr[y][x - 1] >= 4 ||
					arr[y + 1][x] >= 4 ||
					arr[y + 1][x + 1] >= 4 ||
					arr[y + 1][x - 1] >= 4 ||
					arr[y - 1][x] >= 4 ||
					arr[y - 1][x + 1] >= 4 ||
					arr[y - 1][x - 1] >= 4)
				{
					setting_is_possible = 0;
					break;
				}
				switch (urdl)
				{
				case 0: x++;
					break;
				case 1: y++;
					break;
				case 2: x--;
					break;
				case 3:	y--;
					break;
				}
			}
		} while (setting_is_possible != 1);
		if (setting_is_possible == 1)
		{
			x = temp_x;
			y = temp_y;
			for (int i = 0; i < ship_deck; ++i)
			{
				arr[y][x] = ship_number;
				switch (urdl)
				{
				case 0: x++;
					break;
				case 1: y++;
					break;
				case 2: x--;
					break;
				case 3: y--;
					break;
				}
			}
			ship_number++;
		}
		count_ship++;
	}
	return arr[10][10];
}

// ������������� ����������� ��������
void auto_placement(int arr[][S])
{
	int ship_deck = 4;
	int ship_count = 1;
	placement_ship(arr, ship_deck, ship_count, ship_number);
	--ship_deck;
	++ship_count;
	placement_ship(arr, ship_deck, ship_count, ship_number);
	--ship_deck;
	++ship_count;
	placement_ship(arr, ship_deck, ship_count, ship_number);
	--ship_deck;
	++ship_count;
	placement_ship(arr, ship_deck, ship_count, ship_number);
}

// ����� �� ����� ������� ������ ���������
void ship_show(int x, int y, int urdl, int ship_deck, int moveRight, int moveDown)
{
	for (int i = 0; i < ship_deck; i++)
	{
		SetCursor(x, y);

		if (urdl == 0 || urdl == 2)
		{
			SetColor(LightGray, Black); // ����� �����	
			cout << (char)219 << (char)219 << (char)219;
			SetColor(White, Black); // ����� �����
			cout << (char)186;
		}
		else
		{
			SetColor(LightGray, Black); // ����� �����	
			cout << (char)219 << (char)219 << (char)219 << endl;
		}

		switch (urdl)
		{
		case 0: x += moveRight;
			break;
		case 1: y += moveDown;
			break;
		case 2: x -= moveRight;
			break;
		case 3: y -= moveDown;
			break;
		}
	}
}

// �������� ���������� ������� � �������� ����
bool ship_exam(int x, int y, int urdl, int ship_deck, int startCoordX, int startCoordY, const int rast, int moveRight, int moveDown)
{
	bool exam_map = 1;
	for (int i = 0; i < ship_deck; ++i)
	{
		if (x < startCoordX + rast ||
			y < startCoordY ||
			x >= startCoordX + rast + (moveRight * 10) ||
			y >= startCoordY + (moveDown * 10))
		{
			exam_map = 0;
			break;
		}

		switch (urdl)
		{
		case 0: x += moveRight;
			break;
		case 1: y += moveDown;
			break;
		case 2: x -= moveRight;
			break;
		case 3:	y -= moveDown;
			break;
		}
	}
	return exam_map;
}

// �������� ������ ��������� �������
bool exam_ship_arr(int arr[][S], int x, int y, int urdl, int ship_deck, int ship_number)
{
	int n = 11;
	int temp_x = x;
	int temp_y = y;
	bool setting_is_possible = 1;
	for (int i = 0; i < ship_deck; ++i)
	{
		if (x <= 0 || y <= 0 || x >= n || y >= n)
		{
			setting_is_possible = 0;
			break;
		}
		if (arr[y][x] >= 4 ||
			arr[y][x + 1] >= 4 ||
			arr[y][x - 1] >= 4 ||
			arr[y + 1][x] >= 4 ||
			arr[y + 1][x + 1] >= 4 ||
			arr[y + 1][x - 1] >= 4 ||
			arr[y - 1][x] >= 4 ||
			arr[y - 1][x + 1] >= 4 ||
			arr[y - 1][x - 1] >= 4)
		{
			setting_is_possible = 0;
			break;
		}
		switch (urdl)
		{
		case 0: x++;
			break;
		case 1: y++;
			break;
		case 2: x--;
			break;
		case 3:	y--;
			break;
		}
	}

	if (setting_is_possible == 1)
	{
		x = temp_x;
		y = temp_y;
		for (int i = 0; i < ship_deck; ++i)
		{
			arr[y][x] = ship_number;
			switch (urdl)
			{
			case 0: x++;
				break;
			case 1: y++;
				break;
			case 2: x--;
				break;
			case 3: y--;
				break;
			}
		}
	}
	return setting_is_possible;
}

// ������� ��� ������ ��������� ��������
void show_placement_ships(int boats)
{
	SetCursor(23, 19);
	SetColor(Yellow, Black);
	cout << "USE SPACE TO ROTATE";

	SetColor(LightBlue, Black);
	switch (boats)
	{
	case 0:
	{
		SetCursor(20, 11);
		SetColor(Yellow, Black);
		cout << "INSTALL A FOUR-DECKS SHIP";
		SetColor(LightBlue, Black);
		SetCursor(25, 15);
		for (int i = 0; i < 4; i++)
		{
			cout << (char)219 << (char)219 << (char)219 << " ";
		}
		SetCursor(0, 0);
		break;
	}
	case 1:
	{
		int y = 17;
		SetCursor(20, 11);
		SetColor(Yellow, Black);
		cout << "INSTALL A THREE-DECKS SHIP";
		SetColor(LightBlue, Black);
		for (int i = 0; i < 3; i++, y -= 2)
		{
			SetCursor(27, y);
			cout << (char)219 << (char)219 << (char)219;
			SetCursor(35, y);
			cout << (char)219 << (char)219 << (char)219;
		}
		SetCursor(0, 0);
		break;
	}
	case 2:
	{
		int y = 17;
		SetCursor(20, 11);
		SetColor(Yellow, Black);
		cout << "INSTALL A THREE-DECKS SHIP";
		SetColor(LightBlue, Black);
		for (int i = 0; i < 3; i++, y -= 2)
		{
			SetCursor(27, y);
			cout << (char)219 << (char)219 << (char)219;
		}
		SetCursor(0, 0);
		break;
	}
	case 3:
	{
		SetCursor(20, 11);
		SetColor(Yellow, Black);
		cout << "INSTALL A TWO-DECKS SHIP";
		SetColor(LightBlue, Black);
		SetCursor(23, 13);
		for (int i = 0; i < 2; i++)
		{
			cout << (char)219 << (char)219 << (char)219 << " ";
		}
		SetCursor(29, 15);
		for (int i = 0; i < 2; i++)
		{
			cout << (char)219 << (char)219 << (char)219 << " ";
		}
		SetCursor(35, 17);
		for (int i = 0; i < 2; i++)
		{
			cout << (char)219 << (char)219 << (char)219 << " ";
		}
		SetCursor(0, 0);
		break;
	}
	case 4:
	{
		SetCursor(20, 11);
		SetColor(Yellow, Black);
		cout << "INSTALL A TWO-DECKS SHIP";
		SetColor(LightBlue, Black);
		SetCursor(25, 14);
		for (int i = 0; i < 2; i++)
		{
			cout << (char)219 << (char)219 << (char)219 << " ";
		}
		SetCursor(33, 16);
		for (int i = 0; i < 2; i++)
		{
			cout << (char)219 << (char)219 << (char)219 << " ";
		}
		SetCursor(0, 0);
		break;
	}
	case 5:
	{
		SetCursor(20, 11);
		SetColor(Yellow, Black);
		cout << "INSTALL A TWO-DECKS SHIP";
		SetColor(LightBlue, Black);
		SetCursor(29, 15);
		for (int i = 0; i < 2; i++)
		{
			cout << (char)219 << (char)219 << (char)219 << " ";
		}
		SetCursor(0, 0);
		break;
	}
	case 6:
	{
		SetCursor(20, 11);
		SetColor(Yellow, Black);
		cout << "INSTALL A ONE-DECKS SHIP";
		SetColor(LightBlue, Black);

		SetCursor(27, 13);
		cout << (char)219 << (char)219 << (char)219 << " ";

		SetCursor(35, 13);
		cout << (char)219 << (char)219 << (char)219 << " ";

		SetCursor(27, 17);
		cout << (char)219 << (char)219 << (char)219 << " ";

		SetCursor(35, 17);
		cout << (char)219 << (char)219 << (char)219 << " ";

		SetCursor(0, 0);
		break;
	}
	case 7:
	{
		SetCursor(20, 11);
		SetColor(Yellow, Black);
		cout << "INSTALL A ONE-DECKS SHIP";
		SetColor(LightBlue, Black);

		SetCursor(27, 13);
		cout << (char)219 << (char)219 << (char)219 << " ";

		SetCursor(35, 13);
		cout << (char)219 << (char)219 << (char)219 << " ";

		SetCursor(27, 17);
		cout << (char)219 << (char)219 << (char)219 << " ";

		SetCursor(0, 0);
		break;
	}
	case 8:
	{
		SetCursor(20, 11);
		SetColor(Yellow, Black);
		cout << "INSTALL A ONE-DECKS SHIP";
		SetColor(LightBlue, Black);

		SetCursor(35, 13);
		cout << (char)219 << (char)219 << (char)219 << " ";

		SetCursor(27, 17);
		cout << (char)219 << (char)219 << (char)219 << " ";

		SetCursor(0, 0);
		break;
	}
	case 9:
	{
		SetCursor(20, 11);
		SetColor(Yellow, Black);
		cout << "INSTALL A ONE-DECKS SHIP";
		SetColor(LightBlue, Black);

		SetCursor(35, 13);
		cout << (char)219 << (char)219 << (char)219 << " ";

		SetCursor(0, 0);
		break;
	}
	}
}

// ��������� ��������� �������
void ship_sunk(int arr[][S], int S)
{
	for (int i = 1; i < S - 1; i++)
	{
		for (int j = 1; j < S - 1; j++)
		{
			if (arr[i][j] == 3 && arr[i][j + 1] == 0)
			{
				arr[i][j + 1] = 2;
			}
			if (arr[i][j] == 3 && arr[i][j - 1] == 0)
			{
				arr[i][j - 1] = 2;
			}
			if (arr[i][j] == 3 && arr[i - 1][j + 1] == 0)
			{
				arr[i - 1][j + 1] = 2;
			}
			if (arr[i][j] == 3 && arr[i + 1][j + 1] == 0)
			{
				arr[i + 1][j + 1] = 2;
			}
			if (arr[i][j] == 3 && arr[i - 1][j] == 0)
			{
				arr[i - 1][j] = 2;
			}
			if (arr[i][j] == 3 && arr[i + 1][j] == 0)
			{
				arr[i + 1][j] = 2;
			}
			if (arr[i][j] == 3 && arr[i - 1][j - 1] == 0)
			{
				arr[i - 1][j - 1] = 2;
			}
			if (arr[i][j] == 3 && arr[i + 1][j - 1] == 0)
			{
				arr[i + 1][j - 1] = 2;
			}
		}
	}
}

// �������� ���������
void computer_move(int player_ship[][S], int S, int& xc, int& yc, int& live, int& mode, bool shooting)
{
	int n = 0;
	int temp_x = 0, temp_y = 0;
	int urdl_c;

	temp_x = xc;
	temp_y = yc;

	do
	{
		xc = temp_x;
		yc = temp_y;
		urdl_c = rand() % 4;
		mode = 1;
		if (urdl_c == 0)
		{
			if (xc > 1)
			{
				xc--;
			}
			else
			{
				urdl_c = 1;
			}
		}
		if (urdl_c == 1)
		{
			if (xc < 10)
			{
				xc++;
			}
			else
			{
				urdl_c = 0;
			}
		}
		if (urdl_c == 2)
		{
			if (yc < 10)
			{
				yc++;
			}
			else
			{
				urdl_c = 3;
			}

		}
		if (urdl_c == 3)
		{
			if (yc > 1)
			{
				yc--;
			}
			else
			{
				urdl_c = 2;
			}
		}
	} while (player_ship[yc][xc] >= 2 && player_ship[yc][xc] < 4);

	xc = temp_x;
	yc = temp_y;

	switch (urdl_c)
	{
	case 0:
	{
		do
		{
			if (urdl_c == 0)
			{
				if (xc > 1)
				{
					xc--;
				}
				else
				{
					urdl_c = 1;
					xc = temp_x;
					yc = temp_y;
				}
			}
			if (urdl_c == 1)
			{
				xc++;
			}
			if (player_ship[yc][xc] == 0)
			{
				player_ship[yc][xc] = 2;
				xc = temp_x;
				yc = temp_y;
				mode = 3;
				break;
			}

			if (player_ship[yc][xc] >= 4 && live > 1)
			{
				player_ship[yc][xc] = 3;
				live--;
				mode = 1;
				shooting = true;
				cout << "\a";
			}
			else if (player_ship[yc][xc] >= 4 && live <= 1)
			{
				player_ship[yc][xc] = 3;
				live = 0;
				mode = 0;
				shooting = true;
				cout << "\a";
				ship_sunk(player_ship, S);
			}
			else
			{
				urdl_c = 1;
			}
		} while (live != 0);
		break;
	}
	case 1:
	{
		do
		{
			if (urdl_c == 1)
			{
				if (xc < 11)
				{
					xc++;
				}
				else
				{
					urdl_c = 0;
					xc = temp_x;
					yc = temp_y;
				}

			}
			if (urdl_c == 0)
			{
				xc--;
			}

			if (player_ship[yc][xc] == 0)
			{
				player_ship[yc][xc] = 2;
				xc = temp_x;
				yc = temp_y;
				mode = 3;
				break;
			}
			if (player_ship[yc][xc] >= 4 && live > 1)
			{
				player_ship[yc][xc] = 3;
				live--;
				mode = 1;
				shooting = true;
				cout << "\a";
			}
			else if (player_ship[yc][xc] >= 4 && live <= 1)
			{
				player_ship[yc][xc] = 3;
				live = 0;
				mode = 0;
				shooting = true;
				cout << "\a";
				ship_sunk(player_ship, S);
			}
			else
			{
				urdl_c = 0;
			}
		} while (live != 0);
		break;
	}
	case 2:
	{
		do
		{
			if (urdl_c == 2)
			{
				if (yc < 11)
				{
					yc++;
				}
				else
				{
					urdl_c = 3;
					xc = temp_x;
					yc = temp_y;
				}
			}
			if (urdl_c == 3)
			{
				yc--;
			}

			if (player_ship[yc][xc] == 0)
			{
				player_ship[yc][xc] = 2;
				xc = temp_x;
				yc = temp_y;
				mode = 3;
				break;
			}
			if (player_ship[yc][xc] >= 4 && live > 1)
			{
				player_ship[yc][xc] = 3;
				live--;
				mode = 1;
				shooting = true;
				cout << "\a";
			}
			else if (player_ship[yc][xc] >= 4 && live <= 1)
			{
				player_ship[yc][xc] = 3;
				live = 0;
				mode = 0;
				shooting = true;
				cout << "\a";
				ship_sunk(player_ship, S);
			}
			else
			{
				urdl_c = 3;
			}
		} while (live != 0);
		break;
	}
	case 3:
	{
		do
		{
			if (urdl_c == 3)
			{
				if (yc > 1)
				{
					yc--;
				}
				else
				{
					urdl_c = 2;
					xc = temp_x;
					yc = temp_y;
				}
			}
			if (urdl_c == 2)
			{
				yc++;
			}
			if (player_ship[yc][xc] == 0)
			{
				player_ship[yc][xc] = 2;
				xc = temp_x;
				yc = temp_y;
				mode = 3;
				break;
			}
			if (player_ship[yc][xc] >= 4 && live > 1)
			{
				player_ship[yc][xc] = 3;
				live--;
				mode = 1;
				shooting = true;
				cout << "\a";
			}
			else if (player_ship[yc][xc] >= 4 && live <= 1)
			{
				player_ship[yc][xc] = 3;
				live = 0;
				mode = 0;
				shooting = true;
				cout << "\a";
				ship_sunk(player_ship, S);
			}
			else
			{
				urdl_c = 2;
			}
		} while (live != 0);
		break;
	}
	}
}
