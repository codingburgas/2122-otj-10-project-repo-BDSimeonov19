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
		pm::type::User loggedInUser;
		pm::type::User admin = {0, "admin", "admin", "admin@codene.com", 12, "713bfda78870bf9d1b261f565286f85e97ee614efe5f0faf7c34e7ca4f65baca", 0, 1};

		pm::type::User create();
		std::string password();
		void add(pm::type::User);
		std::vector<pm::type::User> getAll();
		void remove(size_t);
		void update(pm::type::User, size_t);
		pm::type::User getById(size_t);
		void list();
		bool logIn();
		UserStore();
	};
}