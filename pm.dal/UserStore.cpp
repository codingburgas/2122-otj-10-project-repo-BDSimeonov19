#include "pch.h"
#include "UserStore.h"

namespace pm::dal {
	std::vector<pm::type::User> users;
}

void pm::dal::UserStore::create(pm::type::User user)
{
	pm::dal::users.push_back(user);
}

std::vector<pm::type::User> pm::dal::UserStore::getAll()
{
	return users;
}

void pm::dal::UserStore::remove(size_t id)
{
	users.erase(users.begin() + id);
}

void pm::dal::UserStore::update(pm::type::User user)
{
	users.insert(users.begin() + user.id + 1, user);
	users.erase(users.begin() + user.id);
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
		const time_t* rawTime = &i.createdOn;
		localtime_s(&time, rawTime);
		strftime(buffer, 80, "%D @ %I:%M%p", &time);
		std::cout << "Created on : " << buffer;
	}
}