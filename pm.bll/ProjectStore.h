#pragma once

#include "../pm.types/Project.h"
#include "../pm.bll/TeamStore.h"
#include "../pm.dal/dbLogic.h"
#include <iostream>
#include <algorithm>
#include <conio.h>


namespace pm::bll {

	struct ProjectStore {

		ProjectStore();

		pm::dal::db database;
		std::vector<pm::type::Project> projects;
		pm::bll::TeamStore teamStore;

		pm::type::Project create();
		void add(pm::type::Project);
		std::vector<pm::type::Project> getAll();
		void remove(size_t);
		void update(pm::type::Project, size_t);
		pm::type::Project getById(size_t);
		void listById(size_t);
		void listAll();
		void assign(size_t, std::vector<size_t>);
		void listByTeamId(size_t);
	};
}