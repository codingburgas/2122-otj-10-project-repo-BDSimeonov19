#pragma once
#include "../pm.types/User.h"
#include "../pm.types/Team.h"
#include "../pm.types/Project.h"
#include <vector>
#include <fstream>
#include <iostream>

namespace pm::dal {
	struct db {
		std::fstream db;
		static pm::type::User saveUser(std::vector<std::string>);
		static pm::type::Team saveTeam(std::vector<std::string>);
		static pm::type::Project saveProject(std::vector<std::string>);
		void updateDb(std::vector<pm::type::User>);
		void updateDb(std::vector<pm::type::Team>);
		void updateDb(std::vector<pm::type::Project>);

		//template <typename T> void updateDb(std::vector<T>, std::string, void(*)(T, pm::dal::db));
		template <typename T> void pullDb(std::vector<T>*, std::string, int, T(*)(std::vector<std::string>));
		
	};
}