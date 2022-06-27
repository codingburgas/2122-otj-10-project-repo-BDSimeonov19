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

template void pm::dal::db::pullDb<pm::type::User>(std::vector<pm::type::User>*, std::string, int, pm::type::User(*)(std::vector<std::string>));
template void pm::dal::db::pullDb<pm::type::Team>(std::vector<pm::type::Team>*, std::string, int, pm::type::Team(*)(std::vector<std::string>));
template void pm::dal::db::pullDb<pm::type::Project>(std::vector<pm::type::Project>*, std::string, int, pm::type::Project(*)(std::vector<std::string>));

//template for pulling all dbs
template <typename T> void pm::dal::db::pullDb(std::vector<T>* t, std::string filename, int members, T(*func)(std::vector<std::string>)) {
    pm::dal::db database;
    std::string line;


    database.db.open(filename, std::ios::in);

    while (std::getline(database.db, line)) {
        T temp;
        std::vector<std::string> data;


        for (int i = 0; i < members + 1; i++) {
            data.push_back(line.substr(0, line.find('^')));
            line.erase(0, data[i].length() + 1);
        }

        t->push_back(func(data));
    }
}

/*template void pm::dal::db::updateDb(std::vector<pm::type::User>, std::string, void(*)(pm::type::User, pm::dal::db));
template void pm::dal::db::updateDb(std::vector<pm::type::Team>, std::string, void(*)(pm::type::Team, pm::dal::db));
template void pm::dal::db::updateDb(std::vector<pm::type::Project>, std::string, void(*)(pm::type::Project, pm::dal::db));

template <typename T> void pm::dal::db::updateDb(std::vector<T> t, std::string filename, void(*func)(T, pm::dal::db)) {
    pm::dal::db database;

    database.db.open(filename, std::ios::out);

    if (database.db.is_open()) {
        for (auto i : t)
            func(i, database);
        database.db.close();
    }
    else
        std::cerr << "An error has occured" << std::endl;
}*/