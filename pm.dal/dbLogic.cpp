#include "pch.h"
#include "dbLogic.h"

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

pm::type::Team pm::dal::db::saveTeam(std::vector<std::string> data) {
    pm::type::Team team;
    team.id = std::stoi(data[0]);
    team.name = data[1];
    //team.members = 
    team.createdOn = std::stoi(data[3]);
    return team;
}

void pm::dal::db::pullDb(std::vector<pm::type::User>* users)
{
    pm::dal::db database;
    std::string line;


    database.db.open("users.txt", std::ios::in);
    
    while (std::getline(database.db, line)) {
        pm::type::User temp;
        std::vector<std::string> data;
     

        for (int i = 0; i < 11; i++) {
            data.push_back(line.substr(0, line.find('^')));
            line.erase(0, data[i].length() + 1);
        }

        users->push_back(saveUser(data));
    }
}


void pm::dal::db::pullDb(std::vector<pm::type::Team>* teams) {
    pm::dal::db database;
    std::string line;


    database.db.open("teams.txt", std::ios::in);

    while (std::getline(database.db, line)) {
        pm::type::Team temp;
        std::vector<std::string> data;


        for (int i = 0; i < 11; i++) {
            data.push_back(line.substr(0, line.find('^')));
            line.erase(0, data[i].length() + 1);
        }

        teams->push_back(saveTeam(data));
    }
}

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
