#pragma once

#include "../pm.types/Project.h"
#include "../pm.dal/dbLogic.h"
#include "TeamStore.h"
#include <iostream>
#include <algorithm>
#include <conio.h>


namespace pm::bll {

	struct ProjectStore {

		ProjectStore();

		pm::dal::db database;
		static std::vector<pm::type::Project> projects;

		pm::type::Project create();
		void add(pm::type::Project);
		std::vector<pm::type::Project> getAll();
		void remove(size_t);
		void update(pm::type::Project, size_t);
		static pm::type::Project getById(size_t);
		void listById(size_t);
		void listAll();
		void assign(size_t, std::vector<size_t>);
		static std::vector<size_t> ProjectsWithUser(size_t);
		void listByIds(std::vector<size_t>);
	};
}