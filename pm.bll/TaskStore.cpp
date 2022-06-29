#include "pch.h"
#include "TaskStore.h"

//constructor to pull the database info on start of program
pm::bll::TaskStore::TaskStore()
{
	//database.pullDb<pm::type::Task>(&teams, "teams.txt", 7, &pm::dal::db::saveTeam);
}


//create a new team
pm::type::Task pm::bll::TaskStore::create(size_t projectId)
{
	pm::type::Task task;


	std::cout << "Task name\n";
	std::cin >> task.name;
	std::cout << "Task description\n";
	std::cin >> task.description;

	

	std::cout << "Asignee id\n";
	std::cin >> task.assignee;

	task.idOfProject = projectId;
	task.createdOn = time(NULL);
	task.idOfCreator = UserStore::getLoggedUser().id;
	task.lastChange = time(NULL);
	task.idOfChanger = UserStore::getLoggedUser().id;

	return task;
}


//add a new team to the database
void pm::bll::TaskStore::add(pm::type::Task team)
{
	team.id += tasks.size();
	tasks.push_back(team);

	//database.updateDb(tasks);
}

//return all teams
std::vector<pm::type::Task> pm::bll::TaskStore::getAll()
{
	return tasks;
}

//remove a team by id
void pm::bll::TaskStore::remove(size_t id)
{
	if (id + 1 > tasks.size() || id < 0)
		std::cout << "Id out of range\n";
	else {
		tasks.erase(tasks.begin() + id);
		for (int i = id; i < tasks.size(); i++)
			tasks[i].id--;

		//database.updateDb(tasks);
	}
}

//update a team by id
void pm::bll::TaskStore::update(pm::type::Task task, size_t id)
{
	if (id + 1 > tasks.size() || id < 0)
		std::cout << "Id out of range\n";
	else {
		task.id = id;
		task.createdOn = tasks[id].createdOn;
		task.idOfCreator = tasks[id].idOfCreator;
		task.lastChange = time(NULL);
		task.idOfChanger = UserStore::getLoggedUser().id;


		tasks.insert(tasks.begin() + task.id + 1, task);
		tasks.erase(tasks.begin() + task.id);

		//database.updateDb(tasks);
	}
}

//get a team by id
pm::type::Task pm::bll::TaskStore::getById(size_t id)
{
	return tasks[id];
}

//list team by id
void pm::bll::TaskStore::listById(size_t id)
{
	if (id + 1 > tasks.size() || id < 0)
		std::cout << "Id out of range\n";
	else {
		char buffer[80];
		struct tm time;
		const time_t* rawTime;

		std::cout << "Id : " << tasks[id].id << std::endl;
		std::cout << "Name : " << tasks[id].name << std::endl;
		std::cout << "Description : " << tasks[id].description << std::endl;
		std::cout << "Id of project : " << tasks[id].idOfProject << std::endl;
		std::cout << "Assignee : " << tasks[id].assignee << std::endl;

		//translate time_t into human readable format
		localtime_s(&time, &tasks[id].createdOn);
		strftime(buffer, 80, "%d/%m/%y @ %I:%M%p", &time);
		std::cout << "Created on : " << buffer << std::endl;

		std::cout << "Id of creator : " << tasks[id].idOfCreator << std::endl;

		localtime_s(&time, &tasks[id].lastChange);
		strftime(buffer, 80, "%d/%m/%y @ %I:%M%p", &time);
		std::cout << "Last change on : " << buffer << std::endl;

		std::cout << "Id of the user that did the last change : " << tasks[id].idOfChanger << std::endl << std::endl;

	}
}

//list all teams
void pm::bll::TaskStore::listAll()
{
	for (auto i : tasks)
		listById(i.id);
}


//list teams from a vector
void pm::bll::TaskStore::listByIds(std::vector<size_t> ids) {
	for (auto i : ids)
		listById(i);
}