#include "pch.h"
#include "UserStore.h"
#include "sha256.h"

namespace pm::dal {
	pm::dal::db::db database;
	std::vector<pm::type::User> users = database.pullDb();
}

void pm::dal::UserStore::add(pm::type::User user)
{
	user.id += pm::dal::UserStore::getAll().size();
	pm::dal::users.push_back(user);

	pm::dal::db::db database;
	database.updateDb(users);
}

std::vector<pm::type::User> pm::dal::UserStore::getAll()
{
	return users;
}

void pm::dal::UserStore::remove(size_t id)
{
	users.erase(users.begin() + id);

	pm::dal::db::db database;
	database.updateDb(users);
}

void pm::dal::UserStore::update(pm::type::User user)
{
	users.insert(users.begin() + user.id + 1, user);
	users.erase(users.begin() + user.id);

	pm::dal::db::db database;
	database.updateDb(users);
}

pm::type::User pm::dal::UserStore::getById(size_t id)
{
	return users[id + 1];
}

void pm::dal::UserStore::list() {
	char buffer[80];
	struct tm time;
	for (auto i : pm::dal::users) {
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


std::string pm::dal::UserStore::password() {
	char ch;
	std::string pass;
	int i = 0;
	while ((ch = _getch()) != '\r')
		pass += ch;

	SHA256 sha256;
	return sha256(pass);
}

pm::type::User pm::dal::UserStore::create() {
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