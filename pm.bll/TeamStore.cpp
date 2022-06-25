#include "pch.h"
#include "TeamStore.h"


pm::bll::TeamStore::TeamStore()
{
    database.pullDb(&teams);
}


pm::type::Team pm::bll::TeamStore::create()
{
	pm::type::Team team;


	std::cout << "Team name\n";
	std::cin >> team.name;

	team.createdOn = time(NULL);
	team.idOfCreator = userStore.loggedInUser.id;
	team.lastChange = time(NULL);
	team.idOfChanger = userStore.loggedInUser.id;

	return team;
}

void pm::bll::TeamStore::add(pm::type::Team team)
{
	team.id += teams.size();
	teams.push_back(team);

	database.updateDb(teams);
}

std::vector<pm::type::Team> pm::bll::TeamStore::getAll()
{
    return teams;
}

void pm::bll::TeamStore::remove(size_t id)
{
	if (id + 1> teams.size() || id < 0)
		std::cout << "Id out of range\n";
	else {
		teams.erase(teams.begin() + id);
		for (int i = id; i < teams.size(); i++)
			teams[i].id--;

		database.updateDb(teams);
	}
}

void pm::bll::TeamStore::update(pm::type::Team team, size_t id)
{
	if (id + 1 > teams.size() || id < 0)
		std::cout << "Id out of range\n";
	else {
		team.id = id;
		team.createdOn = teams[id].createdOn;
		team.idOfCreator = teams[id].idOfCreator;
		team.lastChange = time(NULL);
		team.idOfChanger = userStore.loggedInUser.id;


		teams.insert(teams.begin() + team.id + 1, team);
		teams.erase(teams.begin() + team.id);

		database.updateDb(teams);
	}
}

pm::type::Team pm::bll::TeamStore::getById(size_t id)
{
	return teams[id];
}

void pm::bll::TeamStore::listById(size_t id)
{
	if (id + 1 > teams.size() || id < 0)
		std::cout << "Id out of range\n";
	else {
		char buffer[80];
		struct tm time;
		const time_t* rawTime;

		std::cout << "Id : " << teams[id].id << std::endl;
		std::cout << "Name : " << teams[id].name << std::endl;

		//display members
		std::cout << "Members : ";
		
		if (teams[id].members.size() == 0) {
			std::cout << "None\n";
		}
		else {
			for (auto i = teams[id].members.begin(); i < teams[id].members.end() - 1; i++)
				std::cout << userStore.getById(*i).firstName << " " << userStore.getById(*i).lastName << ", ";
			std::cout << userStore.getById(teams[id].members[teams[id].members.size() - 1]).firstName << " ";
			std::cout << userStore.getById(teams[id].members[teams[id].members.size() - 1]).lastName << std::endl;
		}

		//translate time_t into human readable format
		rawTime = &teams[id].createdOn;
		localtime_s(&time, rawTime);
		strftime(buffer, 80, "%D @ %I:%M%p", &time);
		std::cout << "Created on : " << buffer << std::endl;

		std::cout << "Id of creator : " << teams[id].idOfCreator << std::endl;

		rawTime = &teams[id].lastChange;
		localtime_s(&time, rawTime);
		strftime(buffer, 80, "%D @ %I:%M%p", &time);
		std::cout << "Last change on : " << buffer << std::endl;

		std::cout << "Id of the user that did the last change : " << teams[id].idOfChanger << std::endl << std::endl;

	}
}

void pm::bll::TeamStore::listAll()
{
	for (auto i : teams)
		listById(i.id);
}

void pm::bll::TeamStore::assign(size_t id, std::vector<size_t> members)
{
	
	std::sort(members.begin(), members.end());

	teams[id].members = {};

	for (auto i : members)
		teams[id].members.push_back(i);


	database.updateDb(teams);
}
