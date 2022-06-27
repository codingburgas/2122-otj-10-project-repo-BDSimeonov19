#pragma once
#include "../pm.types/User.h"
#include "../pm.types/Team.h"
#include <vector>
#include <fstream>
#include <iostream>

namespace pm::dal {
	struct db {
		std::fstream db;
		static pm::type::User saveUser(std::vector<std::string>);
		static pm::type::Team saveTeam(std::vector<std::string>);
		void updateDb(std::vector<pm::type::User>);
		void updateDb(std::vector<pm::type::Team>);
		/*void pullDb(std::vector<pm::type::User>* users);
		void pullDb(std::vector<pm::type::Team>* teams);*/

		template <typename T> void pullDb(std::vector<T>* t, std::string filename, int members, T(*func)(std::vector<std::string>)) {
			pm::dal::db database;
			std::string line;


			database.db.open(filename, std::ios::in);

			while (std::getline(database.db, line)) {
				T temp;
				std::vector<std::string> data;


				for (int i = 0; i < members + 1; i++) {
					data.push_back(line.substr(0, line.find('^')));
					line.erase(0, data[i].length() + 1);
				}

				t->push_back(func(data));
			}
		}

	};
}