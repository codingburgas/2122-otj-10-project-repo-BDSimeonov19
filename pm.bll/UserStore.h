#pragma once

#include "../pm.types/User.h"
#include "../pm.types/Team.h"
#include "../pm.dal/dbLogic.h"
#include <iostream>
#include <conio.h>


namespace pm::bll {

	struct UserStore {
		pm::dal::db database;
		std::vector<pm::type::User> users;
		std::vector<pm::type::Team> teams;
		pm::type::User create();
		std::string password();
		void add(pm::type::User user);
		std::vector<pm::type::User> getAll();
		void remove(size_t id);
		void update(pm::type::User user);
		pm::type::User getById(size_t id);
		void list();
		UserStore();
	};
}