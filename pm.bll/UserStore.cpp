#include "pch.h"
#include "UserStore.h"
#include "sha256.h"

//constructor to pull the database info on start of program
pm::bll::UserStore::UserStore()
{
	dal::db database;
	database.pullDb(&users);
	database.pullDb(&teams);
}

//add a new user to the database
void pm::bll::UserStore::add(pm::type::User user)
{
	user.id += pm::bll::UserStore::getAll().size();
	pm::bll::UserStore::users.push_back(user);

	pm::dal::db database;
	database.updateDb(users);
}

//returns all users
std::vector<pm::type::User> pm::bll::UserStore::getAll()
{
	return users;
}

//remove a user by id
void pm::bll::UserStore::remove(size_t id)
{
	users.erase(users.begin() + id);

	pm::dal::db database;
	database.updateDb(users);
}

//update a user by id
void pm::bll::UserStore::update(pm::type::User user)
{
	users.insert(users.begin() + user.id + 1, user);
	users.erase(users.begin() + user.id);

	pm::dal::db database;
	database.updateDb(users);
}

//get a user by id
pm::type::User pm::bll::UserStore::getById(size_t id)
{
	return users[id + 1];
}

//list all users
void pm::bll::UserStore::list() {
	char buffer[80];
	struct tm time;
	for (auto i : users) {
		std::cout << "Id : " << i.id << std::endl;
		std::cout << "Name : " << i.firstName << " " << i.lastName << std::endl;
		std::cout << "Age : " << i.age << std::endl;
		std::cout << "Email : " << i.Email << std::endl;

		//translate time_t into human readable format
		const time_t* rawTime = &i.createdOn;
		localtime_s(&time, rawTime);
		strftime(buffer, 80, "%D @ %I:%M%p", &time);
		std::cout << "Created on : " << buffer << std::endl;
	}
}

//hash a user's password using sha256
std::string pm::bll::UserStore::password() {
	char ch;
	std::string pass;
	int i = 0;
	while ((ch = _getch()) != '\r')
		pass += ch;

	SHA256 sha256;
	return sha256(pass);
}

//create a new user
pm::type::User pm::bll::UserStore::create() {
	pm::type::User user;
	std::cout << "First and last names\n";
	std::cin >> user.firstName >> user.lastName;
	std::cout << "Email\n";
	std::cin >> user.Email;
	std::cout << "Age\n";
	std::cin >> user.age;
	std::cout << "Enter password\n";
	user.passwordHash = password();
	user.createdOn = time(NULL);
	user.admin = false;

	return user;
}