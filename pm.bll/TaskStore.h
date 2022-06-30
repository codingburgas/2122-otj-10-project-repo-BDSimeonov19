#pragma once

#include "../pm.types/Task.h"
#include "UserStore.h"
#include "ProjectStore.h"
#include "../pm.dal/dbLogic.h"
#include <algorithm>
#include <iostream>
#include <conio.h>


namespace pm::bll {

	struct TaskStore {

		TaskStore();

		pm::dal::db database;
		std::vector<pm::type::Task> tasks;

		pm::type::Task create(size_t);
		void add(pm::type::Task);
		std::vector<pm::type::Task> getAll();
		void remove(size_t);
		void update(pm::type::Task, size_t);
		pm::type::Task getById(size_t);
		void listById(size_t);
		void listAll();
		void listByIds(std::vector<size_t>);
		std::vector<size_t> TasksWithUser(size_t);
	};
}