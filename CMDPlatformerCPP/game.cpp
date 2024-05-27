#include "header.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <wtypes.h>
using namespace std;

int life = 3;
int score = 0;

const int x = 120;
const int y = 27;

char map[y][x];
int position[2] = { y-3, 1 };
int exPosition[2] = { y-3, 1 };

string temp;




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

void coinCheck()
{
	if (map[position[0]][position[1]] == '$')
	{
		map[position[0]][position[1]] = ' ';
		score++;
	}
}
void lifeCheck() {
	if (map[position[0]][position[1]] == 'X')
	{
		life--;
		position[1]-=3;
	}
}

void exPosUpdate()
{
	exPosition[0] = position[0];
	exPosition[1] = position[1];
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

void leftRightDown()
{
	if (GetAsyncKeyState(VK_LEFT) && position[1] > 1 && map[position[0]][position[1] - 1] != '[')
	{
		position[1]--;
	}
	if (GetAsyncKeyState(VK_RIGHT) && position[1] < x - 2 && map[position[0]][position[1] + 1] != '[')
	{
		position[1]++;
	}
	if (GetAsyncKeyState(VK_DOWN) && position[0] < y - 2 && map[position[0] + 1][position[1]] != '[')
	{
		position[0]++;
	}
}

void oneBlockUp()
{
	exPosUpdate();
	position[0]--;
	coinCheck();
}

void jump(bool canJump)
{
	if (GetAsyncKeyState(VK_UP) && position[0] > 1 && canJump == true)
	{
		switch (howHigh())	//how high can a player jump
		{
    case 0:
			break;
		case 1:
			oneBlockUp();
			break;
		case 2:
			oneBlockUp();
			oneBlockUp();
			break;

		case 3:
			oneBlockUp();
			oneBlockUp();
			Sleep(3);
			leftRightDown();
			oneBlockUp();
			break;
		default:
			oneBlockUp();
			oneBlockUp();
			Sleep(3);
			leftRightDown();
			oneBlockUp();
			oneBlockUp();
			break;
		}



	}
}

bool applyGravity()
{
	bool isOnGround;
	if (map[position[0] + 1][position[1]] == '[' || map[position[0] + 1][position[1]] == '~')
	{
		isOnGround = true;
	}
	else
	{
		position[0]++;
		isOnGround = false;
	}
	return isOnGround;
}

void errorHandler()
{
	if (map[position[0]][position[1]] == '[')
	{
		position[0]--;
	}
}

void playerInput(bool canJump)
{	
	leftRightDown();
	jump(canJump);
	errorHandler();
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
	score = 0;
	life = 3;
	bool isOnGround = true;
	bool isJumping = false;
	bool isMovingLeft = false;
	bool isMovingRight = false;
	bool isDead = false;

	//Make empty map
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	
	makeMap();

	while (life > 0)
	{
		cout << "Lives: " << life << "                      Score: " << score << endl;
		
		playerInput(isOnGround);
		coinCheck();
		lifeCheck();
		drawMap();


		//char x = map[position[0]][position[1]];
		//gravity applied when air is beneath player
		isOnGround = applyGravity();
		
		//Sleep(1); //This is the delay between each frame (miliseconds) //Additional delay is unnecessary
		ClearScreen(); //This is the command to clear the console
		//system("cls"); //
	}
	system("cls");
	fstream scores;
	scores.open("scoreboard.txt", ios::out);

	cout << "Lifes ended. GAME OVER!" << endl;
	cout << "Press any key to continue" << endl;

}