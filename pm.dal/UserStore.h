#pragma once

#include "../pm.types/User.h"
#include <vector>
#include <string>

namespace pm::dal {
	std::vector<pm::type::User> users;

	struct UserStore {
		void create(pm::type::User user);
		std::vector<pm::type::User> getAll();
		void remove(size_t id);
		void update(pm::type::User user);
		pm::type::User getById(size_t id);
	};
}