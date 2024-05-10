#include "header.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
using namespace std;

const int x = 40;
const int y = 14;

char map[y][x];
int position[2] = { y-2, 1 };


void playerInput(bool canJump)
{
	if (GetAsyncKeyState(VK_LEFT) && position[1] > 1)
	{
		position[1]--;
	}
	if (GetAsyncKeyState(VK_RIGHT) && position[1] < x-2)
	{
		position[1]++;
	}
	if (GetAsyncKeyState(VK_UP) && position[0] > 1 && canJump == true)
	{
		position[0]-=2;
		Sleep(20);
		position[0]-=2;
	}
	if (GetAsyncKeyState(VK_DOWN) && position[0] < y-2)
	{
		position[0]++;
	}
}

void drawMap()
{
	fstream file;
	file.open("map.txt", ios::in);

	file.close();
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
	bool isDucking = false;
	bool isMovingLeft = false;
	bool isMovingRight = false;
	bool isDead = false;

	//Make empty map
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			map[i][j] = ' ';
		}
	}

	while (life > 0)
	{
		cout << "Lives: " << life << "                      Score: " << score << endl;
		
		playerInput(isOnGround);
		drawMap();

		//gravity applied when air is beneath player
		if (*map[(position[0]-1)] == ' ' && position[0] < y-2)
		{
			position[0]++;
			isOnGround = false;
		}
		else
		{
			isOnGround = true;
		}
		Sleep(15); //This is the delay between each frame (miliseconds)
		system("cls"); //This is the command to clear the console
	}
}