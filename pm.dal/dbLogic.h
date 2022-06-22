#pragma once
#include <fstream>
#include <vector>
#include "../pm.types/User.h"

namespace pm::dal::db {
	struct db {
		std::fstream db;
		void updateDb(std::vector<pm::type::User>);
		std::vector<pm::type::User> pullDb();
	};
}