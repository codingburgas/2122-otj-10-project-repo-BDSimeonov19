#include "pch.h"
#include "dbLogic.h"

std::vector<pm::type::User> pm::dal::db::db::pullDb()
{
    pm::dal::db::db database;
    std::string line;
    std::vector<pm::type::User> users;


    database.db.open("users.txt", std::ios::in);
    
    while (std::getline(database.db, line)) {
        pm::type::User temp;
        
        std::string data = line.substr(0, line.find('^'));
        temp.id = std::stoi(data);
        line.erase(0, data.length()+1);

        data = line.substr(0, line.find('^'));
        temp.firstName = data;
        line.erase(0, data.length() + 1);

        data = line.substr(0, line.find('^'));
        temp.lastName = data;
        line.erase(0, data.length() + 1);

        data = line.substr(0, line.find('^'));
        temp.Email = data;
        line.erase(0, data.length() + 1);

        data = line.substr(0, line.find('^'));
        temp.age = std::stoi(data);
        line.erase(0, data.length() + 1);

        data = line.substr(0, line.find('^'));
        temp.createdOn = std::stoi(data);
        line.erase(0, data.length() + 1);

        data = line.substr(0, line.find('^'));
        temp.passwordHash = data;
        line.erase(0, data.length() + 1);

        data = line.substr(0, line.find('^'));
        temp.admin = std::stoi(data);
        line.erase(0, data.length() + 1);

        users.push_back(temp);
    }
    return users;
}

void pm::dal::db::db::updateDb(std::vector<pm::type::User> users)
{
    pm::dal::db::db database;
    database.db.open("users.txt", std::ios::out);

    if (database.db.is_open()) {
        for (auto i : users) {
            database.db << i.id << '^';
            database.db << i.firstName << '^';
            database.db << i.lastName << '^';
            database.db << i.Email << '^';
            database.db << i.age << '^';
            database.db << i.createdOn << '^';
            database.db << i.passwordHash << '^';
            database.db << i.admin << std::endl;
        }

        database.db.close();
    }
    else
        std::cerr << "An error has occured" << std::endl;
}
