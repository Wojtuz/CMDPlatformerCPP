#include <iostream>
#include <fstream>
#include <string>
#include "header.h" //we can use this to store functions regarding different parts of the program, like the menu, the game, etc. so that we can split the code into multiple files and see (github) what changed in each file
using namespace std;

int exitGame = 0;
string null;
string nickname;
string scores;

void playGame();
void choice(int choice);
void createPlayer() {

		cout << "Enter your nickname: " << endl;
		cin >> nickname;
		fstream file;
		file.open("scoreboard.txt", ios::out | ios::app);
		if (file.is_open()) {
			file << nickname << " " << "0" << endl;
			file.close();
			system("cls");
		}
		else {
			cout << "Unable to open a file!" << endl;
		}
		
	
}
void openScoreboard() {
	fstream file;
	file.open("scoreboard.txt", ios::in);
	if (file.is_open()) {
		while (!file.eof()) {
			getline(file, scores, '\n');
			cout << scores << endl;
		}
	}
}

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
		createPlayer();
		playGame();
		break;
	case 2:
		cout << "Scoreboard" << endl;
		openScoreboard();
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

