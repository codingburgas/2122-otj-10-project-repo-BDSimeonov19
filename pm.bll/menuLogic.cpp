#include "pch.h"
#include "menuLogic.h"


void pm::bll::logInMenu(pm::bll::UserStore* store) {
	if (store->logIn()) {
		std::cout << "Logged in\n";
		system("pause");
		system("cls");
		mainMenu(store);
	}
	else {
		std::cout << "Incorrect credentials, try again\n";
		system("pause");
		system("cls");
		pm::bll::logInMenu(store);
	}
}

void pm::bll::mainMenu(pm::bll::UserStore* store)
{
	std::vector<std::string> mainMenuOptions = { "Log in",
												 "Exit"};

	switch (pm::pl::Menu(mainMenuOptions, store)) {
	case 0:
		pm::bll::logInMenu(store);
		break;
	case 1:
		break;
	}
}
