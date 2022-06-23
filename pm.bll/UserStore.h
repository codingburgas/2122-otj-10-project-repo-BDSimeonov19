#pragma once

#include "../pm.types/User.h"
#include "../pm.dal/dbLogic.h"
#include <iostream>
#include <vector>


namespace pm::dal {

	struct UserStore {
		pm::type::User create();
		std::string password();
		void add(pm::type::User user);
		std::vector<pm::type::User> getAll();
		void remove(size_t id);
		void update(pm::type::User user);
		pm::type::User getById(size_t id);
		void list();
	};
}