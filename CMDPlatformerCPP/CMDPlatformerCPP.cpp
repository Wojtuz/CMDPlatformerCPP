#include <iostream>
using namespace std;

int exitGame = 0;

int menu(bool firstTime)
{
	
	cout << "****Game!****" << endl;
	cout << "1. Play Game" << endl; //Not working
	cout << "2. Scoreboard" << endl; //Not working
	cout << "3. Exit" << endl;
	cout << "Please enter the number of the option you would like to select: ";
	int choice;
	cin >> choice;

	return choice;
}
void choice(int choice)
{
	switch (choice)
	{
	case 1:
		cout << "Play Game" << endl;
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