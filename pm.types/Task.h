#pragma once
#include "pch.h"
#include <string>
#include <ctime>

namespace pm::type {
	struct Task 
	{
		size_t id = 0;
		std::string name = "";
		std::string description = "";
		size_t idOfProject = 0;
		size_t assignee = 0;
		int status = 0;

		std::time_t createdOn = 0;
		size_t idOfCreator = 0;
		std::time_t lastChange = 0;
		size_t idOfChanger = 0;
	};
}
