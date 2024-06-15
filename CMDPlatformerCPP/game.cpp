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
string temp;

class Player
{
public:
	Player();
	int posX;
	int posY;
	int exPosX;
	int exPosY;

	bool canJump = true;
	bool isOnGround = true;
	bool isJumping = false;
	bool isMovingLeft = false;
	bool isMovingRight = false;
	bool isDead = false;

};
Player::Player()
{
	posY = y - 3;
	posX = 1;
	exPosY = y - 3;
	exPosX = 1;
}

Player player;


void setConsoleColor(int background, int foreground) 
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, background * 16 + foreground);
}


void setConsoleColor(int background, int foreground)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, background * 16 + foreground);
}

void ResetColor() { 
	cout << "\033[0m"; 
}

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

	if (map[player.posY][player.posX] == '$')
	{
		map[player.posY][player.posX] = ' ';
		score++;
	}
}
void lifeCheck() {
	if (map[player.posY][player.posX] == 'X')
	{
		life--;
		player.posX -= 3;
	}
}

void exPosUpdate()
{
	player.exPosY = player.posY;
	player.exPosX = player.posX;
}

int howHigh()
{
	int above = 0;
	for (int i = 1; i < 5; i++)
	{
		if (map[player.posY - i][player.posX] != '[')
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
	if (GetAsyncKeyState(VK_LEFT) && player.posX > 1 && map[player.posY][player.posX - 1] != '[')
	{
		player.posX--;
	}
	if (GetAsyncKeyState(VK_RIGHT) && player.posX < x - 2 && map[player.posY][player.posX + 1] != '[')
	{
		player.posX++;
	}
	if (GetAsyncKeyState(VK_DOWN) && player.posY < y - 2 && map[player.posY + 1][player.posX] != '[')
	{
		player.posY++;
	}
}

void oneBlockUp()
{
	exPosUpdate();
	player.posY--;
	coinCheck();
}

void jump()
{
	if (GetAsyncKeyState(VK_UP) && player.posY > 1 && player.canJump == true)
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
	if (map[player.posY + 1][player.posX] == '[' || map[player.posY + 1][player.posX] == '~')

	{
		isOnGround = true;
	}
	else
	{
		player.posY++;
		isOnGround = false;
	}
	return isOnGround;
}

void errorHandler()
{
	if (map[player.posY][player.posX] == '[')
	{
		player.posY--;
	}
}

void setNickname() {

	cout << "Enter your nickname: " << endl;
	cin >> player.nickname;
	system("cls");
}

void playerInput()
{
	leftRightDown();
	jump();
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
			if (i == player.posY && j == player.posX)
			{
				setConsoleColor(9, 0);
				cout << "O";
				setConsoleColor(9, 10);
			}
			else switch (map[i][j])
			{
			case '$':
				setConsoleColor(9, 14);
				cout << '$';
				setConsoleColor(9, 10);
				break;
			case 'X':
				setConsoleColor(9, 12);
				cout << 'X';
				setConsoleColor(9, 10);
				break;
			case '~':
				setConsoleColor(9, 15);
				cout << '~';
				setConsoleColor(9, 10);
				break;
			case '#':
				setConsoleColor(13, 13);
				cout << '#';
				setConsoleColor(9, 10);
				break;
			default:
				cout << map[i][j];
				break;
			}
		}
		cout << endl;
	}
}

void playGame()
{
	setConsoleColor(0, 15);
	//Make empty map
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);

	makeMap();

	while (life > 0)
	{
		setConsoleColor(0, 15);
		cout << "Lives: " << life << "                      Score: " << score << endl;
		setConsoleColor(9, 10);

		playerInput();

		coinCheck();
		lifeCheck();
		drawMap();


		//char x = map[posY][player.posX];
		//gravity applied when air is beneath player
		player.canJump = applyGravity();

		//Sleep(1); //This is the delay between each frame (miliseconds) //Additional delay is unnecessary
		ClearScreen(); //This is the command to clear the console
		//system("cls"); //
	}
	fstream file;
	file.open("scoreboard.txt", ios::out | ios::app);
	if (file.is_open()) {
		file << player.nickname << " " << score << endl;
		file.close();

	}
	else {
		cout << "Unable to open a file!" << endl;
	}
	system("cls");
	ResetColor();
	cout << "Lifes ended. GAME OVER!" << endl;
	cout << "Press any key to continue" << endl;
}