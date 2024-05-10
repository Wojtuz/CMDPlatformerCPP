#include <iostream>
#include "header.h" //we can use this to store functions regarding different parts of the program, like the menu, the game, etc. so that we can split the code into multiple files and see (github) what changed in each file
using namespace std;

int exitGame = 0;
string null;

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
		playGame();
		break;
	case 2:
		cout << "Scoreboard" << endl;
		break;
	case 3:
		exitGame = 1;
		break;
	default:
		break;
	}
	cin >> null;
	cout << "\033[2J\033[1;1H";
}

