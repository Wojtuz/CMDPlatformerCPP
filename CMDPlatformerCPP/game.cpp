#include "header.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <wtypes.h>
using namespace std;

const int x = 120;
const int y = 27;

char map[y][x];
int position[2] = { y-3, 1 };

string temp;
int number;

void ClearScreen()
{
	COORD cursorPosition;	
	cursorPosition.X = 0;	
	cursorPosition.Y = 0;	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}
void GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
    horizontal = desktop.right;
	vertical = desktop.bottom;
}


int howHigh()
{
	int above = 0;
	for (int i = 1; i < 5; i++)
	{
		if (map[position[0]-i][position[1]] != '[')
		{
			above++;
		}
		else
		{
			return above;
		}
	}
	return above;
}

void leftRight()
{
	if (GetAsyncKeyState(VK_LEFT) && position[1] > 1 && map[position[0]][position[1] - 1] != '[')
	{
		position[1]--;
	}
	if (GetAsyncKeyState(VK_RIGHT) && position[1] < x - 2 && map[position[0]][position[1] + 1] != '[')
	{
		position[1]++;
	}
}

void playerInput(bool canJump)
{	
	leftRight();
	if (GetAsyncKeyState(VK_UP) && position[0] > 1 && canJump == true)
	{
		switch (howHigh())	//how high can a player jump
		{
			case 0:
				break;
			case 1:
				position[0]--;
				break;
			case 2:
				position[0]-=2;
				break;

			case 3:
				position[0] -= 2;
				Sleep(3);
				leftRight();
				position[0]--;
				break;
			default:
				position[0] -= 2;
				Sleep(3);
				leftRight();
				position[0] -= 2;
				break;
		}



	}
	if (GetAsyncKeyState(VK_DOWN) && position[0] < y-2 && map[position[0]+1][position[1]] != '[')
	{
		position[0]++;
	}
}
void makeMap()
{
	fstream file;
	if (!file)
	{
		cout << "Map has not been found." << endl;
	}
	else
	{
		file.open("Map1.txt", ios::in);
		for (int i = 0; i < 27; i++)
		{
			getline(file, temp, '\n');

			for (int j = 0; j < 120; j++)
			{
				map[i][j] = temp[j];
			}
		}
		file.close();
	}

}
void drawMap()
{
	
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (i == position[0] && j == position[1])
			{
				cout << "O";
			}
			else if (i == 0 || i == y-1 || j == 0 || j == x-1)
			{
				//border/screenbezel
				cout << "#";
			}
			else
			{
				cout << map[i][j];
			}
		}
		cout << endl;
	}
}

void playGame()
{
	int life = 3;
	int score = 0;
	bool isOnGround = true;
	bool isJumping = false;
	bool isMovingLeft = false;
	bool isMovingRight = false;
	bool isDead = false;

	//Make empty map
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	

	while (life > 0)
	{
		cout << "Lives: " << life << "                      Score: " << score << endl;
		
		playerInput(isOnGround);
		makeMap();
		drawMap();

		number = position[0];
		//char x = map[position[0]][position[1]];
		//gravity applied when air is beneath player
		if (map[position[0]+1][position[1]] == ' ')
		{
			position[0]++;
			isOnGround = false;
		}
		else
		{
			isOnGround = true;
		}
		//Sleep(1); //This is the delay between each frame (miliseconds) //Additional delay is unnecessary
		ClearScreen(); //This is the command to clear the console
		//system("cls"); //
	}
}