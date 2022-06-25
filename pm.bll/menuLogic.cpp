#include "pch.h"
#include "menuLogic.h"


void pm::bll::usersMenu(pm::bll::UserStore* store) {
	size_t id;
	std::vector<std::string> mainMenuOptions = { "List users",
											     "Update user",
												 "Remove user",
												 "Create user",
												 "Back"};

	system("cls");
	switch (pm::pl::Menu(mainMenuOptions, store)) {
	case 0:
		system("cls");
		store->listAll();
		system("pause");
		pm::bll::usersMenu(store);
		break;
	case 1:
		system("cls");
		
		std::cout << "Enter an id\n";
		std::cin >> id;

		store->update(store->create(), id);

		system("pause");
		pm::bll::usersMenu(store);
		break;
	case 2:
		system("cls");

		std::cout << "Enter an id\n";
		std::cin >> id;
		store->remove(id);
		system("pause");
		pm::bll::usersMenu(store);
		break;
	case 3:
		system("cls");
		store->add(store->create());
		system("pause");
		pm::bll::usersMenu(store);
		break;
	case 4:
		system("cls");
		pm::bll::mainMenu(store);
		break;
	}
}

void pm::bll::logInMenu(pm::bll::UserStore* store) {
	if (store->logIn()) {
		std::cout << "Logged in\n";
		system("pause");
		system("cls");
		pm::bll::mainMenu(store);
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
	pm::type::User noUser (0, "", "", "", 0, "", 0, 0, 0, 0, 0);

	if (store->loggedInUser.firstName == "") {
		std::vector<std::string> mainMenuOptions = { "Log in",
													 "Exit" };

		switch (pm::pl::Menu(mainMenuOptions, store)) {
		case 0:
			pm::bll::logInMenu(store);
			break;
		case 1:
			exit(0);
			break;
		}
	}
	else if (store->loggedInUser.admin == 1) {
		std::vector<std::string> mainMenuOptions = { "Users",
													 "Log out",
													 "Exit" };


		switch (pm::pl::Menu(mainMenuOptions, store)) {
		case 0:
			pm::bll::usersMenu(store);
			break;
		case 1:
			store->loggedInUser = noUser;
			pm::bll::mainMenu(store);
			break;
		case 2:
			exit(0);
			break;
		}
	}
	else {
		std::vector<std::string> mainMenuOptions = { "Your user",
													 "Log out",
													 "Back" };

		switch (pm::pl::Menu(mainMenuOptions, store)) {
		case 0:
			
			store->listById(store->loggedInUser.id);
			break;
		case 1:
			store->loggedInUser = noUser;
			pm::bll::mainMenu(store);
			break;
		case 2:
			exit(0);
			break;
		}
	}
}
