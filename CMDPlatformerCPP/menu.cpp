#include "header.h"
#include <iostream>
using namespace std;

int menu(bool firstTime)
{

	cout << "****Game!****" << endl;
	cout << "1. Play Game" << endl; //Not working
	cout << "2. Scoreboard" << endl; //Not working
	//we can add binds to rebind movement keys
	//we can add a instructions page
	cout << "3. Exit" << endl;
	cout << "Please enter the number of the option you would like to select: ";
	int choice;
	cin >> choice;

	return choice;
}