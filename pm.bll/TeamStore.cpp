#include "pch.h"
#include "TeamStore.h"

std::vector<pm::type::Team> pm::bll::TeamStore::teams = {};

//constructor to pull the database info on start of program
pm::bll::TeamStore::TeamStore()
{
	database.pullDb<pm::type::Team>(&teams, "teams.txt", 7, &pm::dal::db::saveTeam);
}


//create a new team
pm::type::Team pm::bll::TeamStore::create()
{
	pm::type::Team team;


	std::cout << "Team name\n";
	std::cin >> team.name;

	team.createdOn = time(NULL);
	team.idOfCreator = UserStore::getLoggedUser().id;
	team.lastChange = time(NULL);
	team.idOfChanger = UserStore::getLoggedUser().id;

	return team;
}


//add a new team to the database
void pm::bll::TeamStore::add(pm::type::Team team)
{
	team.id += teams.size();
	teams.push_back(team);

	database.updateDb(teams);
}

//return all teams
std::vector<pm::type::Team> pm::bll::TeamStore::getAll()
{
    return teams;
}

//remove a team by id
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

//update a team by id
void pm::bll::TeamStore::update(pm::type::Team team, size_t id)
{
	if (id + 1 > teams.size() || id < 0)
		std::cout << "Id out of range\n";
	else {
		team.id = id;
		team.createdOn = teams[id].createdOn;
		team.idOfCreator = teams[id].idOfCreator;
		team.lastChange = time(NULL);
		team.idOfChanger = UserStore::getLoggedUser().id;


		teams.insert(teams.begin() + team.id + 1, team);
		teams.erase(teams.begin() + team.id);

		database.updateDb(teams);
	}
}

//get a team by id
pm::type::Team pm::bll::TeamStore::getById(size_t id)
{
	return teams[id];
}

//list team by id
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
				std::cout << UserStore::getById(*i).firstName << " " << UserStore::getById(*i).lastName << ", ";
			std::cout << UserStore::getById(teams[id].members[teams[id].members.size() - 1]).firstName << " ";
			std::cout << UserStore::getById(teams[id].members[teams[id].members.size() - 1]).lastName << std::endl;
		}

		//translate time_t into human readable format
		localtime_s(&time, &teams[id].createdOn);
		strftime(buffer, 80, "%d/%m/%y @ %I:%M%p", &time);
		std::cout << "Created on : " << buffer << std::endl;

		std::cout << "Id of creator : " << teams[id].idOfCreator << std::endl;

	    localtime_s(&time, &teams[id].lastChange);
		strftime(buffer, 80, "%d/%m/%y @ %I:%M%p", &time);
		std::cout << "Last change on : " << buffer << std::endl;

		std::cout << "Id of the user that did the last change : " << teams[id].idOfChanger << std::endl << std::endl;

	}
}

//list all teams
void pm::bll::TeamStore::listAll()
{
	for (auto i : teams)
		listById(i.id);
}

//assign users to a team
void pm::bll::TeamStore::assign(size_t id, std::vector<size_t> members)
{
	
	std::sort(members.begin(), members.end());

	teams[id].members = {};

	for (auto i : members)
		teams[id].members.push_back(i);


	database.updateDb(teams);
}


//return all teams that contain a user id
std::vector<size_t> pm::bll::TeamStore::TeamsWithUser()
{
	bool flag = false;
	std::vector<size_t> teamsIds;

	//find all teams the user is in
	for (auto i : teams) {
		if (std::find(i.members.begin(), i.members.end(), UserStore::loggedInUser.id) != i.members.end()) {
			teamsIds.push_back(i.id);
			flag = true;
		}
	}

	//display the teams the user is a part of
	if (!flag)
		std::cout << "You are a part of no teams\n";


	return teamsIds;
}

//list teams from a vector
void pm::bll::TeamStore::listByIds(std::vector<size_t> ids) {
	for (auto i : ids)
		listById(i);
}

//remove a user from all teams by id
void pm::bll::TeamStore::removeFromTeam(size_t id)
{
	for (auto &i : teams) {
		for (auto j = i.members.begin(); j < i.members.end(); j++) {
			if (*j == id) {
				i.members.erase(j);
				break;
			}
		}
	}

	database.updateDb(teams);
}
