#include "pch.h"
#include "Menu.h"


void pm::pl::colour(int color) //Sets color of the text
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void pm::pl::gotoxy(int x, int y) //Get the coordinates inside the console
{
	COORD coord;
	coord.X = x; // x-axis
	coord.Y = y; // y-axis
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void pm::pl::loggedUser(pm::bll::ProjectManager* manager) {
	if (manager->ustore.loggedInUser.firstName == "")
		std::cout << "No current logged user\n";

	else
		manager->ustore.listById(manager->ustore.loggedInUser.id);
}

void pm::pl::optionsDisplay(std::string str, bool chosen, int posx, int posy, int maxOptionLength) { // Display avalable options in the current menu
	//error handler
	HANDLE hdlOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hdlOut == INVALID_HANDLE_VALUE)
	{
		std::cerr << "Encountered an Error: " << GetLastError();
		system("cls");
	}

	//if the text has been chosen, highlit it
	if (chosen)
		pm::pl::colour(3); // 3 is the colour code for dark aqua

	pm::pl::gotoxy(posx, posy); std::cout << char(201);

	for (int i = 0; i < maxOptionLength; i++)
		std::cout << char(205);

	std::cout << char(187);
	pm::pl::gotoxy(posx, posy + 1); std::cout << char(186);

	//add necessary padding to center the text
	for (int i = str.length(); i < maxOptionLength; i++) {
		if (i % 2)
			str = " " + str;
		else
			str = str + " ";
	}
	std::cout << str;

	std::cout << char(186) << std::endl;
	pm::pl::gotoxy(posx, posy + 2); std::cout << char(200);

	for (int i = 0; i < maxOptionLength; i++)
		std::cout << char(205);

	std::cout << char(188);

	SetConsoleTextAttribute(hdlOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

int pm::pl::Menu(std::vector<std::string> options, pm::bll::ProjectManager* manager)
{
	
	pm::pl::loggedUser(manager);

	char upInput = 72;
	char downInput = 80;
	char key; // Key to be entered
	int counter = 0;


	while (true)
	{
		//finds the length of the largest option
		float maxOptionLength = 0;
		for (auto i : options) {
			if (i.length() > maxOptionLength)
				maxOptionLength = i.length();
		}

		//add pading
		maxOptionLength += 4;

		//output each option
		for (auto i = options.begin(); i < options.end(); i++) {
			int k = options.size() - (options.end() - i);
			pl::optionsDisplay(*i, counter == k, 58 - (ceil(maxOptionLength / 2)), 13 + 3 * k, maxOptionLength);
		}

		key = _getch();

		if (key == upInput && counter > 0) // 72 is the ASCII code for the up arrow
			counter--;

		if (key == downInput && counter < options.size() - 1) // 80 is the ASCII code for the down arrow
			counter++;

		if (key == '\r') // enter key
		{
			system("cls");
			return counter;
		}
	}
}