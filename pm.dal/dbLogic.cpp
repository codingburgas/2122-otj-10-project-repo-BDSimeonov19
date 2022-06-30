#include "pch.h"
#include "dbLogic.h"


//saves the passed data to a User
pm::type::User pm::dal::db::saveUser(std::vector<std::string> data) {
    pm::type::User user;
    user.id = std::stoi(data[0]);
    user.firstName = data[1];
    user.lastName = data[2];
    user.Email = data[3];
    user.age = std::stoi(data[4]);
    user.createdOn = std::stoi(data[5]);
    user.idOfCreator = std::stoi(data[6]);
    user.lastChange = std::stoi(data[7]);
    user.idOfChanger = std::stoi(data[8]);
    user.passwordHash = data[9];
    user.admin = std::stoi(data[10]);

    return user;
}

//saves the passed data to a Team
pm::type::Team pm::dal::db::saveTeam(std::vector<std::string> data) {
    pm::type::Team team;
    team.id = std::stoi(data[0]);
    team.name = data[1];

    //saves the members
    if (data[2] == "-")
        team.members = {};
    else {
        while (data[2].find(",") != std::string::npos) {
            team.members.push_back(std::stoi(data[2].substr(0, data[2].find(','))));
            data[2].erase(0, data[2].find(",") + 1);
        }
        team.members.push_back(std::stoi(data[2]));
    }



    team.createdOn = std::stoi(data[3]);
    team.idOfCreator = std::stoi(data[4]);
    team.lastChange = std::stoi(data[5]);
    team.idOfChanger = std::stoi(data[6]);

    return team;
}


//saves the passed data to a Project
pm::type::Project pm::dal::db::saveProject(std::vector<std::string> data) {
    pm::type::Project project;
    project.id = std::stoi(data[0]);
    project.name = data[1];
    project.description = data[2];

    //saves the members
    if (data[3] == "-")
        project.members = {};
    else {
        while (data[3].find(",") != std::string::npos) {
            project.members.push_back(std::stoi(data[3].substr(0, data[3].find(','))));
            data[3].erase(0, data[3].find(",") + 1);
        }
        project.members.push_back(std::stoi(data[3]));
    }



    project.createdOn = std::stoi(data[4]);
    project.idOfCreator = std::stoi(data[5]);
    project.lastChange = std::stoi(data[6]);
    project.idOfChanger = std::stoi(data[7]);

    return project;
}

//saves the passed data to a Task
pm::type::Task pm::dal::db::saveTask(std::vector<std::string> data) {
    pm::type::Task task;
    task.id = std::stoi(data[0]);
    task.name = data[1];
    task.description = data[2];
    task.idOfProject = std::stoi(data[3]);
    task.assignee = std::stoi(data[4]);
    task.status = std::stoi(data[5]);

    task.createdOn = std::stoi(data[6]);
    task.idOfCreator = std::stoi(data[7]);
    task.lastChange = std::stoi(data[8]);
    task.idOfChanger = std::stoi(data[9]);

    return task;
}

//updates the user database
void pm::dal::db::updateDb(std::vector<pm::type::User> users)
{
    pm::dal::db database;

    database.db.open("users.txt", std::ios::out);

    if (database.db.is_open()) {
        for (auto i = users.begin() + 1; i < users.end(); i++) {
            database.db << i->id << '^';
            database.db << i->firstName << '^';
            database.db << i->lastName << '^';
            database.db << i->Email << '^';
            database.db << i->age << '^';
            database.db << i->createdOn << '^';
            database.db << i->idOfCreator << '^';
            database.db << i->lastChange << '^';
            database.db << i->idOfChanger << '^';
            database.db << i->passwordHash << '^';
            database.db << i->admin << std::endl;
        }

        database.db.close();
    }
    else
        std::cerr << "An error has occured" << std::endl;
}

//updates the team database
void pm::dal::db::updateDb(std::vector<pm::type::Team> teams)
{
    pm::dal::db database;

    database.db.open("teams.txt", std::ios::out);

    if (database.db.is_open()) {
        for (auto i : teams) {
            database.db << i.id << '^';
            database.db << i.name << '^';

            if (i.members.size() != 0) {
                for (auto j = 0; j < i.members.size() - 1; j++)
                    database.db << i.members[j] << ',';
                database.db << i.members[i.members.size() - 1] << '^';
            }
            else
                database.db << "-^";

            database.db << i.createdOn << '^';
            database.db << i.idOfCreator << '^';
            database.db << i.lastChange << '^';
            database.db << i.idOfChanger << std::endl;
        }

        database.db.close();
    }
    else
        std::cerr << "An error has occured" << std::endl;
}

//updates the project database
void pm::dal::db::updateDb(std::vector<pm::type::Project> projects)
{
    pm::dal::db database;

    database.db.open("projects.txt", std::ios::out);

    if (database.db.is_open()) {
        for (auto i : projects) {
            database.db << i.id << '^';
            database.db << i.name << '^';
            database.db << i.description << '^';

            if (i.members.size() != 0) {
                for (auto j = 0; j < i.members.size() - 1; j++)
                    database.db << i.members[j] << ',';
                database.db << i.members[i.members.size() - 1] << '^';
            }
            else
                database.db << "-^";

            database.db << i.createdOn << '^';
            database.db << i.idOfCreator << '^';
            database.db << i.lastChange << '^';
            database.db << i.idOfChanger << std::endl;
        }

        database.db.close();
    }
    else
        std::cerr << "An error has occured" << std::endl;
}

//updates the task database
void pm::dal::db::updateDb(std::vector<pm::type::Task> tasks)
{
    pm::dal::db database;

    database.db.open("tasks.txt", std::ios::out);

    if (database.db.is_open()) {
        for (auto i : tasks) {
            database.db << i.id << '^';
            database.db << i.name << '^';
            database.db << i.description << '^';
            database.db << i.idOfProject << '^';
            database.db << i.assignee << '^';
            database.db << i.status << '^';
            database.db << i.createdOn << '^';
            database.db << i.idOfCreator << '^';
            database.db << i.lastChange << '^';
            database.db << i.idOfChanger << std::endl;
        }

        database.db.close();
    }
    else
        std::cerr << "An error has occured" << std::endl;
}