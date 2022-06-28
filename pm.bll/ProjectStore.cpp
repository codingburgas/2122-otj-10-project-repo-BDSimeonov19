#include "pch.h"
#include "ProjectStore.h"

//constructor to pull the database info on start of program
pm::bll::ProjectStore::ProjectStore()
{
	database.pullDb<pm::type::Project>(&projects, "projects.txt", 8, &pm::dal::db::saveProject);
}

//create a new project
pm::type::Project pm::bll::ProjectStore::create()
{
	pm::type::Project project;


	std::cout << "Project name\n";
	std::cin >> project.name;
	std::cout << "Project description\n";
	std::cin.ignore();
	std::getline(std::cin, project.description, '\n');

	project.createdOn = time(NULL);
	project.idOfCreator = UserStore::loggedInUser.id;
	project.lastChange = time(NULL);
	project.idOfChanger = UserStore::loggedInUser.id;

	return project;
}

//add a new project to the database
void pm::bll::ProjectStore::add(pm::type::Project project)
{
	project.id += projects.size();
	projects.push_back(project);

	database.updateDb(projects);
}

//return all projects
std::vector<pm::type::Project> pm::bll::ProjectStore::getAll()
{
	return projects;
}

//remove a project by id
void pm::bll::ProjectStore::remove(size_t id)
{
	if (id + 1 > projects.size() || id < 0)
		std::cout << "Id out of range\n";
	else {
		projects.erase(projects.begin() + id);
		for (int i = id; i < projects.size(); i++)
			projects[i].id--;

		database.updateDb(projects);
	}
}

//update a project by id
void pm::bll::ProjectStore::update(pm::type::Project project, size_t id)
{
	if (id + 1 > projects.size() || id < 0)
		std::cout << "Id out of range\n";
	else {
		project.id = id;
		project.createdOn = projects[id].createdOn;
		project.idOfCreator = projects[id].idOfCreator;
		project.lastChange = time(NULL);
		project.idOfChanger = UserStore::loggedInUser.id;
		project.members = projects[id].members;

		projects.insert(projects.begin() + project.id + 1, project);
		projects.erase(projects.begin() + project.id);

		database.updateDb(projects);
	}
}

//get a project by id
pm::type::Project pm::bll::ProjectStore::getById(size_t id)
{
	return projects[id];
}

//list project by id
void pm::bll::ProjectStore::listById(size_t id)
{
	if (id + 1 > projects.size() || id < 0)
		std::cout << "Id out of range\n";
	else {
		char buffer[80];
		struct tm time;
		const time_t* rawTime;

		std::cout << "Id : " << projects[id].id << std::endl;
		std::cout << "Name : " << projects[id].name << std::endl;
		std::cout << "Description : " << projects[id].description << std::endl;


		//display members
		std::cout << "Members : ";

		if (projects[id].members.size() == 0) {
			std::cout << "None\n";
		}
		else {
			for (auto i = projects[id].members.begin(); i < projects[id].members.end() - 1; i++)
				std::cout << TeamStore::getById(*i).name << " ";
			std::cout << TeamStore::getById(projects[id].members[projects[id].members.size() - 1]).name << std::endl;
		}

		//translate time_t into human readable format
		localtime_s(&time, &projects[id].createdOn);
		strftime(buffer, 80, "%d/%m/%y @ %I:%M%p", &time);
		std::cout << "Created on : " << buffer << std::endl;

		std::cout << "Id of creator : " << projects[id].idOfCreator << std::endl;

		localtime_s(&time, &projects[id].lastChange);
		strftime(buffer, 80, "%d/%m/%y @ %I:%M%p", &time);
		std::cout << "Last change on : " << buffer << std::endl;

		std::cout << "Id of the user that did the last change : " << projects[id].idOfChanger << std::endl << std::endl;

	}
}

//list all bprojects
void pm::bll::ProjectStore::listAll()
{
	for (auto i : projects)
		listById(i.id);
}

//assign teams to a project
void pm::bll::ProjectStore::assign(size_t id, std::vector<size_t> members)
{
	std::sort(members.begin(), members.end());

	projects[id].members = {};

	for (auto i : members)
		projects[id].members.push_back(i);


	database.updateDb(projects);
}

//list all projects that contain a team id
std::vector<size_t> pm::bll::ProjectStore::ProjectsWithUser(size_t id)
{


	bool flag = false;
	std::vector<size_t> projectsIds;

	for (auto k : TeamStore::TeamsWithUser(id)) {
		//find all projects the team is in
		for (auto i : projects) {
			if (std::find(i.members.begin(), i.members.end(), k) != i.members.end()) {
				projectsIds.push_back(i.id);
				flag = true;
			}
		}
	}

	std::sort(projectsIds.begin(), projectsIds.end());

	//display the projects the team is a part of
	if (!flag)
		std::cout << "You are a part of no projects\n";

	return projectsIds;
}

void pm::bll::ProjectStore::listByIds(std::vector<size_t> v)
{
	for (auto i : v)
		listById(i);
}
