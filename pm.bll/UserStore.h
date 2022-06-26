#pragma once

#include "../pm.types/User.h"
#include "../pm.dal/dbLogic.h"
#include <iostream>
#include <conio.h>


namespace pm::bll {

	struct UserStore {

		UserStore();

		pm::dal::db database;
		static std::vector<pm::type::User> users;
		static pm::type::User loggedInUser;
		pm::type::User admin = {0, "admin", "admin", "admin@codene.com", 12, "713bfda78870bf9d1b261f565286f85e97ee614efe5f0faf7c34e7ca4f65baca", 0, 0, 0, 0, 1};

		pm::type::User create();
		void add(pm::type::User);
		std::vector<pm::type::User> getAll();
		void remove(size_t);
		void update(pm::type::User, size_t);
		static pm::type::User getById(size_t);
		void listById(size_t);
		void listAll();
		std::string password();
		bool logIn();
		static pm::type::User getLoggedUser();
	};
}