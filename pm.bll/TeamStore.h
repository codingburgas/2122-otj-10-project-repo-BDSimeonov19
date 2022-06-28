#pragma once

#include "../pm.types/User.h"
#include "../pm.bll/UserStore.h"
#include "../pm.types/Team.h"
#include "../pm.dal/dbLogic.h"
#include <algorithm>
#include <iostream>
#include <conio.h>


namespace pm::bll {

	struct TeamStore {

		TeamStore();

		pm::dal::db database;
		static std::vector<pm::type::Team> teams;

		pm::type::Team create();
		void add(pm::type::Team);
		std::vector<pm::type::Team> getAll();
		void remove(size_t);
		void update(pm::type::Team, size_t);
		static pm::type::Team getById(size_t);
		void listById(size_t);
		void listAll();
		void assign(size_t, std::vector<size_t>);
		static std::vector<size_t> TeamsWithUser(size_t);
		void listByIds(std::vector<size_t>);
		void removeFromTeam(size_t);
	};
}