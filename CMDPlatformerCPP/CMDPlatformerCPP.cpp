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
		playGame();
		break;
	case 2:
		cout << "Scoreboard" << endl;
		openScoreboard();
	    break;
	case 3:
		cout << "How to play?" << endl;
		cout << "Your main goal is to finish the map. Collect coins and scores." << endl;
		cout << "Avoid spikes, because they can harm you. REMEMBER, you have ONLY 3 lifes!" << endl;
		cout << "Control keys: " << endl;
		cout << "UP Arrow - jumping" << endl;
		cout << "RIGHT Arrow - walking forward" << endl;
		cout << "LEFT Arrow - walking backward" << endl;
		cout << "DOWN Arrow - falling down" << endl;
		cout << "GLHF!" << endl;
		break;
	case 4:
		exitGame = 1;
		break;
	default:
		break;
	}
	cin >> null;
	cout << "\033[2J\033[1;1H";
}

