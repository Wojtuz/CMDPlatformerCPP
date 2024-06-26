#include "header.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <wtypes.h>
using namespace std;


const int x = 120;
const int y = 27;

int dmgTick = 0;

char map[y][x];
string temp;

int startLVL = 1;

class Player
{
public:
	Player();

	string nickname;
	int life;
	int score;
	int posX;
	int posY;
	int exPosX;
	int exPosY;
	int collectedScore = 0;
	int level = startLVL;

	char sprite = 'O';

	bool dontMove = false;
	bool isHurt = false;
	bool scoring = false;
	bool Won = false;
	bool canJump = true;
	bool doubleJump = false;
	bool gameOn = true;

	void setup()
	{
		posY = y - 3;
		posX = 1;
		exPosY = y - 3;
		exPosX = 1;
		life = 3;
		score = 0;
		sprite = 'O';	
	}

	void nextLevel()
	{
		posY = y - 3;
		posX = 1;
		exPosY = y - 3;
		exPosX = 1;
		life = 3;
		Won = false;
		gameOn = true;
		dontMove = false;
	}

	void newGame()
	{
		life = 3;
		score = 0;
		level = startLVL;
		Won = false;
	}
};
Player::Player()
{
	setup();
}

Player player;

void setConsoleColor(int background, int foreground)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, background * 16 + foreground);
}

void ResetColor() { 
	setConsoleColor(0, 15);
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

void displayGameOver() {
	cout << " _______  _______  __   __  _______    _______  __   __  _______  ______    __  " << endl;
	cout << "|       ||   _   ||  |_|  ||       |  |       ||  | |  ||       ||    _ |  |  | " << endl;
	cout << "|    ___||  |_|  ||       ||    ___|  |   _   ||  |_|  ||    ___||   | ||  |  | " << endl;
	cout << "|   | __ |       ||       ||   |___   |  | |  ||       ||   |___ |   |_||_ |  | " << endl;
	cout << "|   ||  ||       ||       ||    ___|  |  |_|  ||       ||    ___||    __  ||__| " << endl;
	cout << "|   |_| ||   _   || ||_|| ||   |___   |       | |     | |   |___ |   |  | | __  " << endl;
	cout << "|_______||__| |__||_|   |_||_______|  |_______|  |___|  |_______||___|  |_||__| " << endl;
	cout <<"                                                                                 " << endl;
}

void displayLevelCleared() {
	cout << " ___      _______  __   __  _______  ___        _______  ___      _______  _______  ______    _______  ______   __  " << endl;
	cout << "|   |    |       ||  | |  ||       ||   |      |       ||   |    |       ||   _   ||    _ |  |       ||      | |  | " << endl;
	cout << "|   |    |    ___||  |_|  ||    ___||   |      |       ||   |    |    ___||  |_|  ||   | ||  |    ___||  _    ||  | " << endl;
	cout << "|   |    |   |___ |       ||   |___ |   |      |       ||   |    |   |___ |       ||   |_||_ |   |___ | | |   ||  | " << endl;
	cout << "|   |___ |    ___||       ||    ___||   |___   |      _||   |___ |    ___||       ||    __  ||    ___|| |_|   ||__| " << endl;
	cout << "|       ||   |___  |     | |   |___ |       |  |     |_ |       ||   |___ |   _   ||   |  | ||   |___ |       | __  " << endl;
	cout << "|_______||_______|  |___|  |_______||_______|  |_______||_______||_______||__| |__||___|  |_||_______||______| |__| " << endl;
	cout << "                                                                                                                    " << endl;
}

void eventCheck()
{
	switch (map[player.posY][player.posX])
	{
	case '$':
		map[player.posY][player.posX] = ' ';
		player.score++;
		break;
	case 'X':
		player.life--;
		player.posX -= 2;
		player.isHurt = true;
		player.dontMove = true;
		break;
	case '&':
		player.doubleJump = true;
		break;
	case '|':
		player.Won = true;

		switch (player.life)
		{
		case -1:
			player.gameOn = false;
			break;
		case 0:
			player.life--;
			Sleep(400);
			break;
		default:
			player.life--;
			Sleep(100);
			player.score += 10;
			player.scoring = true;
			player.dontMove = true;
			break;
		}
		break;
	default:
		break;
	}

	if (player.life == 0)
	{
		player.gameOn = false;
		player.isHurt = false;
		dmgTick = 0;
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
	eventCheck();
}

void jump()
{
	if (GetAsyncKeyState(VK_UP) && player.posY > 1 && (player.canJump || player.doubleJump))
	{
		player.doubleJump = false;
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

void clearMap()
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			map[i][j] = ' ';
		}
	}
}

bool makeMap()
{
	fstream file; 
	
	clearMap();

	file.open("Map" + to_string(player.level) + ".txt", ios::in);
	if (!file.is_open())
	{
		cout << "Map" + to_string(player.level) + ".txt not found!" << endl;
		cout << "You can create another map by creating MapX.txt (X being level number you want to create. Use Insert to make it easier c:)." << endl;
		cout << "Press BACKSPACE to continue" << endl;

		while (1)
		{
			if (GetAsyncKeyState(VK_BACK))
			{
				system("cls");
				break;
			}
			Sleep(100);
		}

		return false;
	}
	for (int i = 0; i < 27; i++)
	{
		getline(file, temp, '\n');
		for (int j = 0; j < 120; j++)
		{
			map[i][j] = temp[j];
		}
	}
	file.close();
	return true;
}

// Color codes:
// 0 = Black, 1 = Blue, 2 = Green, 3 = Aqua, 4 = Red, 5 = Purple, 6 = Yellow, 7 = White,
// 8 = Gray, 9 = Light Blue, 10 = Light Green, 11 = Light Aqua, 12 = Light Red, 13 = Light Purple, 14 = Light Yellow, 15 = Bright White

void drawMap()
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (i == player.posY && j == player.posX)
			{
				if (player.isHurt && dmgTick % 2 == 0)
				{
					setConsoleColor(9, 12);
					dmgTick++;
				}
				else if (player.isHurt && dmgTick % 2 == 1)
				{
					setConsoleColor(9, 0);
					dmgTick++;
				}
				else if (player.doubleJump)
				{
					setConsoleColor(9, 11);
				}
				else
				{
					setConsoleColor(9, 0);
				}
				if (dmgTick == 8)
				{
					player.dontMove = false;
					player.isHurt = false;
					dmgTick = 0;
				}
				if (player.life == 0 && !player.Won)
				{
					player.sprite = '_';
				}
				cout << player.sprite;
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
			case '&':
				setConsoleColor(9, 11);
				cout << '&';
				setConsoleColor(9, 10);
				break;
			case '#':
				setConsoleColor(13, 13);
				cout << '#';
				setConsoleColor(9, 10);
				break;
			case '<':
				setConsoleColor(9, 5);
				cout << '<';
				setConsoleColor(9, 10);
				break;
			case ']':
				setConsoleColor(9, 5);
				cout << ']';
				setConsoleColor(9, 10);
				break;
			case '|':
				setConsoleColor(9, 5);
				cout << '|';
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
	player.nextLevel();
	if(makeMap())
	{
		player.setup();
		while (player.gameOn)
		{
			int shownLife = player.life;
			if (player.life < 1)
			{
				shownLife = 0;
			}

			setConsoleColor(0, 15);
			cout << "Lives: " << shownLife << "                      Score: " << player.score << "                      Level: " << player.level << endl;
			setConsoleColor(9, 10);

			if (!player.dontMove)
			{
				playerInput();
			}

			eventCheck();

			drawMap();


			//char x = map[posY][player.posX];
			//gravity applied when air is beneath player
			player.canJump = applyGravity();

			//Sleep(1); //This is the delay between each frame (miliseconds) //Additional delay is unnecessary
			ClearScreen(); //This is the command to clear the console
			//system("cls"); //
		}
		if (player.Won)
		{
			win();
			player.level++;
			player.nextLevel();
			playGame();
		}
		else 
		{
			Sleep(2000);
			lost();
		}
	}
}

void saveScore()
{

	fstream file;
	file.open("scoreboard.txt", ios::out | ios::app);
	if (file.is_open()) 
	{
		file << player.nickname << " " << player.collectedScore << endl;
		file.close();
	}
	else 
	{
		cout << "Unable to open a file!" << endl;
	}
}

void win()
{
	ResetColor();
	system("cls");
	displayLevelCleared();
	cout << "Press BACKSPACE to continue" << endl;
	player.collectedScore += player.score;
	if (player.level > startLVL) {
		saveScore();
	}
	while (1) {
		if (GetAsyncKeyState(VK_BACK)) {
			system("cls");
			break;
		}
		Sleep(100);

	}
	system("cls");
	cout << "Loading";
	Sleep(100);
	for (int i = 0; i < 4; i++)
	{
		cout << ".";
		Sleep(100);
	}
	system("cls");
}

void lost()
{
	ResetColor();
	system("cls");
	displayGameOver();
	cout << "Lifes ended. Press BACKSPACE to continue" << endl;
	player.collectedScore += player.score;
	saveScore();
	while (1) 
	{
		if (GetAsyncKeyState(VK_BACK)) {
			system("cls");
			break;
		}
		Sleep(100);
	}
}

void startGame()
{
	player.newGame();
	playGame();
}