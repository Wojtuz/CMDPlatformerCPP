#include "header.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
using namespace std;

char map[60][20];
int position[2] = { 0, 0 };


void updatePosition()
{
	if (GetAsyncKeyState(VK_LEFT) && position[1] > 0)
	{
		position[1]--;
	}
	if (GetAsyncKeyState(VK_RIGHT) && position[1] < 19)
	{
		position[1]++;
	}
	if (GetAsyncKeyState(VK_UP) && position[0] > 0)
	{
		position[0]--;
	}
	if (GetAsyncKeyState(VK_DOWN) && position[0] < 19)
	{
		position[0]++;
	}
}

void drawMap()
{
	fstream file;
	file.open("map.txt", ios::in);
	for (int i = 0; i < 60; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			map[i][j] = ' ';
		}
	}
	file.close();
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (i == position[0] && j == position[1])
			{
				cout << "O";
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


	for (int i = 0; i < 60; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			map[i][j] = ' ';
		}
	}

	while (life > 0)
	{
		cout << "Lives: " << life << "                      Score: " << score << endl;
		drawMap();
		updatePosition();
		Sleep(15); //This is the delay between each frame (miliseconds)
		system("cls"); //This is the command to clear the console
	}
}