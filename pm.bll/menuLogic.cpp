#include "pch.h"
#include "menuLogic.h"

void pm::bll::assignTeamsMenu(ProjectManager* manager, size_t id) {
	std::vector<size_t> members;
	std::vector<std::string> options;

	//make all users options
	for (auto i : manager->tstore.teams)
		options.push_back(std::to_string(i.id) + " " + i.name);
	options.push_back("Done");

	while (true) {
		int choice = pm::pl::Menu(options, manager);

		//if done is selected, assign the chosen members
		if (choice == options.size() - 1) {
			manager->pstore.assign(id, members);
			projectsManagmentMenu(manager);
		}

		//if a user is selected, add them to a list and remove them from options
		members.push_back(int(options[choice][0] - '0'));
		options.erase(options.begin() + choice);

	}
}

void pm::bll::projectsManagmentMenu(ProjectManager* manager) {
	system("cls");

	std::vector<size_t> projects = manager->pstore.ProjectsWithUser(manager->ustore.loggedInUser.id);
	size_t id;
	std::vector<std::string> options = { "List projects",
										 "Update project",
										 "Remove project",
										 "Create project",
										 "Assign memebers"
										 "Tasks",
										 "Back" };

	switch (pm::pl::Menu(options, manager)) {
		//list all projects
	case 0:
		manager->pstore.listAll();

		system("pause");
		projectsManagmentMenu(manager);
		break;

		//update a projects by id
	case 1:
		system("cls");

		std::cout << "Enter id of project\n";
		std::cin >> id;

		if (manager->ustore.loggedInUser.admin == 0 && std::find(projects.begin(), projects.end(), id) == projects.end())
			std::cout << "You don't have the privileges to alter this project.\n";

		else
			manager->pstore.update(manager->pstore.create(), id);

		system("pause");
		projectsManagmentMenu(manager);

		break;

		//remove a projects by id
	case 2:
		system("cls");

		std::cout << "Enter id of project\n";
		std::cin >> id;

		if (manager->ustore.loggedInUser.admin == 0 && std::find(projects.begin(), projects.end(), id) == projects.end())
			std::cout << "You don't have the privileges to alter this project.\n";

		else
			manager->pstore.remove(id);

		system("pause");
		projectsManagmentMenu(manager);

		break;

		//add a new projects
	case 3:
		system("cls");


		manager->pstore.add(manager->pstore.create());

		system("pause");
		projectsManagmentMenu(manager);

		break;

		//assign teams to a projects
	case 4:
		system("cls");
		std::cout << "Enter id of project\n";
		std::cin >> id;
		system("cls");

		if (manager->ustore.loggedInUser.admin == 0 && std::find(projects.begin(), projects.end(), id) == projects.end())
			std::cout << "You don't have the privileges to alter this project.\n";

		else
			assignTeamsMenu(manager, id);

		break;

	case 5:
		
		break;
		//go back
	case 6:

		mainMenu(manager);
		break;
	}
}

void pm::bll::assignUsersMenu(ProjectManager* manager, size_t id) {
	std::vector<size_t> members;
	std::vector<std::string> options;

	//make all users options
	for (auto i : manager->ustore.users)
		options.push_back(std::to_string(i.id) + " " + i.firstName + " " + i.lastName);
	options.push_back("Done");

	while (true) {
		int choice = pm::pl::Menu(options, manager);

		//if done is selected, assign the chosen members
		if (choice == options.size() - 1) {
			manager->tstore.assign(id, members);
			teamsManagmentMenu(manager);
		}

		//if a user is selected, add them to a list and remove them from options
		members.push_back(int(options[choice][0] - '0'));
		options.erase(options.begin() + choice);

	}
}

void pm::bll::teamsManagmentMenu(ProjectManager* manager) {
	system("cls");

	size_t id;
	std::vector<std::string> options = { "List teams",
										 "Update team",
										 "Remove team",
										 "Create team",
										 "Assign memebers",
										 "Back" };

	switch (pm::pl::Menu(options, manager)) {
		//list all teams
	case 0:
		system("cls");
		manager->tstore.listAll();

		system("pause");
		teamsManagmentMenu(manager);
		break;

		//update a team by id
	case 1:
		system("cls");

		std::cout << "Enter id of team\n";
		std::cin >> id;

		manager->tstore.update(manager->tstore.create(), id);

		system("pause");
		teamsManagmentMenu(manager);

		break;

		//remove a team by id
	case 2:
		system("cls");

		std::cout << "Enter id of team\n";
		std::cin >> id;


		manager->tstore.remove(id);

		system("pause");
		teamsManagmentMenu(manager);

		break;

		//add a new team
	case 3:
		system("cls");

		manager->tstore.add(manager->tstore.create());

		system("pause");
		teamsManagmentMenu(manager);

		break;

		//assign memebers to a team
	case 4:
		system("cls");
		std::cout << "Enter id of team\n";
		std::cin >> id;
		system("cls");

		assignUsersMenu(manager, id);

		break;

		//go back
	case 5:

		mainMenu(manager);
		break;
	}
}

void pm::bll::usersManagmentMenu(ProjectManager* manager) {
	system("cls");

	size_t id;
	std::vector<std::string> options = { "List users",
												 "Update user",
												 "Remove user",
												 "Create user",
												 "Back" };

	switch (pm::pl::Menu(options, manager)) {

		//list all users
	case 0:
		system("cls");
		manager->ustore.listAll();
		system("pause");
		usersManagmentMenu(manager);
		break;

		//update user by id
	case 1:
		system("cls");

		std::cout << "Enter an id\n";
		std::cin >> id;


		manager->ustore.update(manager->ustore.create(), id);

		system("pause");
		usersManagmentMenu(manager);

		break;

		//remove user by id
	case 2:
		system("cls");

		std::cout << "Enter an id\n";
		std::cin >> id;
		manager->ustore.remove(id);
		manager->tstore.removeFromTeam(id);

		system("pause");
		usersManagmentMenu(manager);

		break;

		//add new user
	case 3:
		system("cls");

		manager->ustore.add(manager->ustore.create());

		system("pause");
		usersManagmentMenu(manager);

		break;

		//go back
	case 4:
		mainMenu(manager);
		break;
	}
}

void pm::bll::logInMenu(ProjectManager* manager) {
	system("cls");
	if (manager->ustore.logIn()) {
		std::cout << "Logged in\n";
		system("pause");
		mainMenu(manager);
	}

	else {
		std::cout << "Incorrect credentials, try again\n";
		system("pause");
		logInMenu(manager);
	}
}

void pm::bll::mainMenu(ProjectManager* manager)
{
	system("cls");
	//dummy logged out user
	pm::type::User noUser;

	//menu for non-logged in users
	if (manager->ustore.loggedInUser.firstName == "") {
		std::vector<std::string> options = { "Log in",
													 "Exit" };

		switch (pm::pl::Menu(options, manager)) {
		case 0:
			logInMenu(manager);
			break;
		case 1:
			exit(0);
			break;
		}
	}

	//menu for logged in admin user
	else if (manager->ustore.loggedInUser.admin == 1) {
		std::vector<std::string> options = { "Users",
													 "Teams",
													 "Projects",
													 "Log out",
													 "Exit" };


		switch (pm::pl::Menu(options, manager)) {
		case 0:
			usersManagmentMenu(manager);
			break;
		case 1:
			teamsManagmentMenu(manager);
			break;
		case 2:
			projectsManagmentMenu(manager);
			break;
		case 3:
			manager->ustore.loggedInUser = noUser;
			mainMenu(manager);
			break;
		case 4:
			exit(0);
			break;
		}
	}

	//menu for logged in non-admin user
	else {
		std::vector<std::string> options = { "Your user",
													 "Your teams",
													 "Your projects",
													 "Project actions",
													 "Log out",
													 "Back" };

		switch (pm::pl::Menu(options, manager)) {
		case 0:
			//list the user data that matches the logged in user
			manager->tstore.listById(manager->ustore.loggedInUser.id);
			system("pause");
			break;
		case 1:
			//list all teams that the logged in user is a part of
			manager->tstore.listByIds(manager->tstore.TeamsWithUser(manager->ustore.loggedInUser.id));
			system("pause");
			break;
		case 2:
			//list all projects that the logged in user is a part of
			manager->pstore.listByIds(manager->pstore.ProjectsWithUser(manager->ustore.loggedInUser.id));
			system("pause");
			break;
		case 3:
			//give the user options for editing his teams
			projectsManagmentMenu(manager);
			break;
		case 4:
			manager->ustore.loggedInUser = noUser;
			break;

		case 5:
			exit(0);
			break;
		}

		//go back to main menu
		mainMenu(manager);
	}
}
