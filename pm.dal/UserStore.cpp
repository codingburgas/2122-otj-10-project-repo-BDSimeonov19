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