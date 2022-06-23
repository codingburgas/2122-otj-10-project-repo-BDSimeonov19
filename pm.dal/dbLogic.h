#pragma once
#include "../pm.types/User.h"
#include "../pm.types/Team.h"
#include <vector>
#include <fstream>
#include <iostream>

namespace pm::dal {
	struct db {
		std::fstream db;
		pm::type::User saveUser(std::vector<std::string>);
		pm::type::Team saveTeam(std::vector<std::string>);
		void updateDb(std::vector<pm::type::User>);
		void pullDb(std::vector<pm::type::User>* users);
		void pullDb(std::vector<pm::type::Team>* teams);
	};
}