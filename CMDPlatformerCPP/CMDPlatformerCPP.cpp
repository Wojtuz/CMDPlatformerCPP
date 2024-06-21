#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include "header.h" //we can use this to store functions regarding different parts of the program, like the menu, the game, etc. so that we can split the code into multiple files and see (github) what changed in each file
using namespace std;

int exitGame = 0;
string null;
string scores;
void playGame();
void choice(int choice);

fstream file;



int main()
{
	int pick = menu(true);
	choice(pick);
	while (exitGame == 0)
	{
		pick = menu(false);
		choice(pick);
	}
	return 0;
}

void choice(int choice)
{
	switch (choice)
	{
		case 1:
			setNickname();
			startGame();
			break;
		case 2:
			cout << "Scoreboard" << endl;
			openScoreboard();
			break;
		case 3:
			file.open("howtoplay.txt", ios::in);
			if (!file.is_open()) 
			{
				cout << "File not found" << endl;
			}
			else 
			{
				string temp;
				while (getline(file, temp)) 
				{
					cout << temp << endl;
				}
				file.close();
			}

			cout << "Press BACKSPACE to continue" << endl;

			while (1) 
			{
				if (GetAsyncKeyState(VK_BACK)) {
					system("cls");
					break;
				}
			}
			break;
			case 4:
			exitGame = 1;
			break;
		default:
			break;
	}
	//cin >> null;
	cout << "\033[2J\033[1;1H";
}

