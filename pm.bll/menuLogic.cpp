#include "pch.h"
#include "menuLogic.h"

void pm::bll::assignMembersMenu(pm::bll::TeamStore* store, size_t id) {
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

void pm::bll::teamsManagmentMenu(pm::bll::TeamStore* store) {
	size_t id;
	std::vector<std::string> options = { "List teams",
										 "Update team",
										 "Remove team",
										 "Create team",
										 "Assign memebers",
										 "Back" };

	system("cls");
	switch (pm::pl::Menu(options, store)) {
	case 0:
		system("cls");
		store->listAll();

		system("pause");
		pm::bll::teamsManagmentMenu(store);
		break;
	case 1:
		system("cls");

		std::cout << "Enter id of team\n";
		std::cin >> id;
		store->update(store->create(), id);

		system("pause");
		pm::bll::teamsManagmentMenu(store);

		break;
	case 2:
		system("cls");

		std::cout << "Enter id of team\n";
		std::cin >> id;
		store->remove(id);

		system("pause");
		pm::bll::teamsManagmentMenu(store);

		break;
	case 3:
		system("cls");
		store->add(store->create());

		system("pause");
		pm::bll::teamsManagmentMenu(store);
		break;
	case 4:
		system("cls");
		std::cout << "Enter id of team\n";
		std::cin >> id;
		system("cls");

		if (id + 1 > store->teams.size() || id < 0) {
			std::cout << "Id out of range\n";
			system("pause");
			pm::bll::teamsManagmentMenu(store);
		}

		else
			pm::bll::assignMembersMenu(store, id);

		break;
	case 5:
		system("cls");
		pm::bll::mainMenu(store);
		break;
	}
}

void pm::bll::usersManagmentMenu(pm::bll::TeamStore* store) {
	size_t id;
	std::vector<std::string> options = { "List users",
												 "Update user",
												 "Remove user",
												 "Create user",
												 "Back" };

	system("cls");
	switch (pm::pl::Menu(options, store)) {
	case 0:
		system("cls");
		store->userStore.listAll();
		system("pause");
		pm::bll::usersManagmentMenu(store);
		break;
	case 1:
		system("cls");

		std::cout << "Enter an id\n";
		std::cin >> id;

		store->userStore.update(store->userStore.create(), id);

		system("pause");
		pm::bll::usersManagmentMenu(store);
		break;
	case 2:
		system("cls");

		std::cout << "Enter an id\n";
		std::cin >> id;
		store->userStore.remove(id);
		system("pause");
		pm::bll::usersManagmentMenu(store);
		break;
	case 3:
		system("cls");
		store->userStore.add(store->userStore.create());
		system("pause");
		pm::bll::usersManagmentMenu(store);
		break;
	case 4:
		system("cls");
		pm::bll::mainMenu(store);
		break;
	}
}

void pm::bll::logInMenu(pm::bll::TeamStore* store) {
	if (store->userStore.logIn()) {
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

void pm::bll::mainMenu(pm::bll::TeamStore* store)
{
	pm::type::User noUser(0, "", "", "", 0, "", 0, 0, 0, 0, 0);

	if (store->userStore.loggedInUser.firstName == "") {
		std::vector<std::string> options = { "Log in",
													 "Exit" };

		switch (pm::pl::Menu(options, store)) {
		case 0:
			pm::bll::logInMenu(store);
			break;
		case 1:
			exit(0);
			break;
		}
	}
	else if (store->userStore.loggedInUser.admin == 1) {
		std::vector<std::string> options = { "Users",
													 "Teams",
													 "Log out",
													 "Exit" };


		switch (pm::pl::Menu(options, store)) {
		case 0:
			pm::bll::usersManagmentMenu(store);
			break;
		case 1:
			pm::bll::teamsManagmentMenu(store);
			break;
		case 2:
			store->userStore.loggedInUser = noUser;
			pm::bll::mainMenu(store);
			break;
		case 3:
			exit(0);
			break;
		}
	}
	else {
		bool flag = false;
		std::vector<size_t> teamsIds;
		std::vector<std::string> options = { "Your user",
													 "Your teams",
													 "Log out",
													 "Back" };

		switch (pm::pl::Menu(options, store)) {
		case 0:

			store->listById(store->userStore.loggedInUser.id);
			break;
		case 1:
			//find all teams the user is in
			for (auto i : store->teams){
				if (std::find(i.members.begin(), i.members.end(), store->userStore.loggedInUser.id) != i.members.end()) {
					teamsIds.push_back(i.id);
					flag = true;
				}
			}

			//display the teams the user is a part of
			if (flag) {
				for (auto i : teamsIds)
					store->listById(i);
			}
			else
				std::cout << "You are a part of no teams\n";
			

			system("pause");
			mainMenu(store);

			break;
		case 2:
			store->userStore.loggedInUser = noUser;
			pm::bll::mainMenu(store);
			break;

		case 3:
			exit(0);
			break;
		}
	}
}
