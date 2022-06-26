#include "pch.h"
#include "menuLogic.h"

void pm::bll::assignMembersMenu(TeamStore* store, size_t id) {
	std::vector<size_t> members;
	std::vector<std::string> options;

	//make all users options
	for (auto i : store->userStore.users)
		options.push_back(std::to_string(i.id) + " " + i.firstName + " " + i.lastName);
	options.push_back("Done");

	while (true) {
		int choice = pm::pl::Menu(options, store);

		//if done is selected, assign the chosen members
		if (choice == options.size() - 1) {
			store->assign(id, members);
			teamsManagmentMenu(store);
		}

		//if a user is selected, add them to a list and remove them from options
		members.push_back(int(options[choice][0] - '0'));
		options.erase(options.begin() + choice);

	}
}

void pm::bll::teamsManagmentMenu(TeamStore* store) {
	system("cls");

	size_t id;
	std::vector<std::string> options = { "List teams",
										 "Update team",
										 "Remove team",
										 "Create team",
										 "Assign memebers",
										 "Back" };

	switch (pm::pl::Menu(options, store)) {
	//list all teams
	case 0:
		system("cls");
		store->listAll();

		system("pause");
		teamsManagmentMenu(store);
		break;

	//update a team by id
	case 1:
		system("cls");

		std::cout << "Enter id of team\n";
		std::cin >> id;
		store->update(store->create(), id);

		system("pause");
		teamsManagmentMenu(store);

		break;

	//remove a team by id
	case 2:
		system("cls");

		std::cout << "Enter id of team\n";
		std::cin >> id;
		store->remove(id);

		system("pause");
		teamsManagmentMenu(store);

		break;

	//add a new team
	case 3:
		system("cls");
		store->add(store->create());

		system("pause");
		teamsManagmentMenu(store);

		break;

	//assign memebers to a team
	case 4:
		system("cls");
		std::cout << "Enter id of team\n";
		std::cin >> id;
		system("cls");

		if (id + 1 > store->teams.size() || id < 0) {
			std::cout << "Id out of range\n";
			system("pause");
			teamsManagmentMenu(store);
		}

		else
			assignMembersMenu(store, id);

		break;

	//go back
	case 5:

		mainMenu(store);
		break;
	}
}

void pm::bll::usersManagmentMenu(TeamStore* store) {
	system("cls");

	size_t id;
	std::vector<std::string> options = { "List users",
												 "Update user",
												 "Remove user",
												 "Create user",
												 "Back" };

	switch (pm::pl::Menu(options, store)) {
	
	//list all users
	case 0:
		system("cls");
		store->userStore.listAll();
		system("pause");
		usersManagmentMenu(store);
		break;

	//update user by id
	case 1:
		system("cls");

		std::cout << "Enter an id\n";
		std::cin >> id;

		store->userStore.update(store->userStore.create(), id);

		system("pause");
		usersManagmentMenu(store);

		break;

	//remove user by id
	case 2:
		system("cls");

		std::cout << "Enter an id\n";
		std::cin >> id;
		store->userStore.remove(id);

		system("pause");
		usersManagmentMenu(store);

		break;

	//add new user
	case 3:
		system("cls");
		store->userStore.add(store->userStore.create());

		system("pause");
		usersManagmentMenu(store);

		break;

	//go back
	case 4:
		mainMenu(store);
		break;
	}
}

void pm::bll::logInMenu(TeamStore* store) {
	if (store->userStore.logIn()) {
		std::cout << "Logged in\n";
		system("pause");
		mainMenu(store);
	}

	else {
		std::cout << "Incorrect credentials, try again\n";
		system("pause");
		logInMenu(store);
	}
}

void pm::bll::mainMenu(TeamStore* store)
{
	system("cls");
	//dummy logged out user
	pm::type::User noUser;

	//menu for non-logged in users
	if (store->userStore.loggedInUser.firstName == "") {
		std::vector<std::string> options = { "Log in",
													 "Exit" };

		switch (pm::pl::Menu(options, store)) {
		case 0:
			logInMenu(store);
			break;
		case 1:
			exit(0);
			break;
		}
	}

	//menu for logged in admin user
	else if (store->userStore.loggedInUser.admin == 1) {
		std::vector<std::string> options = { "Users",
													 "Teams",
													 "Log out",
													 "Exit" };


		switch (pm::pl::Menu(options, store)) {
		case 0:
			usersManagmentMenu(store);
			break;
		case 1:
			teamsManagmentMenu(store);
			break;
		case 2:
			store->userStore.loggedInUser = noUser;
			mainMenu(store);
			break;
		case 3:
			exit(0);
			break;
		}
	}

	//menu for logged in non-admin user
	else {
		std::vector<std::string> options = { "Your user",
													 "Your teams",
													 "Log out",
													 "Back" };

		switch (pm::pl::Menu(options, store)) {
		case 0:
			//list the user data that matches the logged in user
			store->listById(store->userStore.loggedInUser.id);
			system("pause");
			break;
		case 1:
			//list all teams that the logged in user is a part of
			store->listByUserId();
			system("pause");
			break;
		case 2:
			store->userStore.loggedInUser = noUser;
			break;

		case 3:
			exit(0);
			break;
		}

		//go back to main menu
		mainMenu(store);
	}
}
