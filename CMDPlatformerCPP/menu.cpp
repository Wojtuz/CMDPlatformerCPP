#include "header.h"
#include <iostream>
#include <Windows.h>
using namespace std;

int menu(bool firstTime)
{

	cout << "****Game!****" << endl;
	cout << "1. Play Game" << endl; // Actually it works
	cout << "2. Scoreboard" << endl; //Actually it works
	//we can add binds to rebind movement keys
	//we can add a instructions page
	cout << "3. Exit" << endl;
	cout << "Please enter the number of the option you would like to select: ";
	int choice;
	cin >> choice;
	system("cls");
	return choice;
}