#include "header.h"
#include <Windows.h>
#include <iostream>
using namespace std;

void playGame()
{
	int life = 3;
	int position[] = { 0, 0 };
	int score = 0;
	bool isOnGround = true;
	bool isJumping = false;
	bool isDucking = false;
	bool isMovingLeft = false;
	bool isMovingRight = false;
	bool isDead = false;
	while (life > 0)
	{
		if (GetAsyncKeyState(VK_UP) & 0x8000) //Checks if the up arrow key is pressed
		{
			cout << "jump";
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) //Checks if the left arrow key is pressed
		{
			cout << "left";
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) //Checks if the right arrow key is pressed
		{
			cout << "right";
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) //Checks if the down arrow key is pressed
		{
			cout << "duck";
		}
		Sleep(10); //This is the delay between each frame (miliseconds)
	}
}