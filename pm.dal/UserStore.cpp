#include "pch.h"
#include "UserStore.h"

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

void list() {
	for (auto i : pm::dal::users) {
		std::cout << "Id" << i.id << std::endl;
		std::cout << "Name : " << i.firstName << " " << i.lastName << std::endl;
		std::cout << "Age : " << i.age << std::endl;
		std::cout << "Email : " << i.Email << std::endl;
		std::cout << "Created on : " << i.createdOn;
	}
}