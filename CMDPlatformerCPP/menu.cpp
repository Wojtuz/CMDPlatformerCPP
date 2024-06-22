#include "header.h"
#include <iostream>
#include <Windows.h>
using namespace std;
void displayGame() {
	cout << "  _______  _______  __   __  _______  " << endl;
	cout << " |       ||   _   ||  |_|  ||       | " << endl;
	cout << " |    ___||  |_|  ||       ||    ___| " << endl;
	cout << " |   | __ |       ||       ||   |___  " << endl;
	cout << " |   ||  ||       ||       ||    ___| " << endl;
	cout << " |   |_| ||   _   || ||_|| ||   |___  " << endl;
	cout << " |_______||__| |__||_|   |_||_______| " << endl;
	cout << "                                      " << endl;
}
int menu(bool firstTime)
{

	displayGame();
	cout << "1. Play Game" << endl; // Actually it works
	cout << "2. Scoreboard" << endl; //Actually it works
	//we can add binds to rebind movement keys
	cout << "3. How to play?" << endl;
	cout << "4. Credits" << endl;
	cout << "5. Exit" << endl;
	cout << "Please enter the number of the option you would like to select: ";
	int choice;
	cin >> choice;
	system("cls");
	return choice;
}