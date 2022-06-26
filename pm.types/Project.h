#pragma once
#include "pch.h"
#include "Team.h"
#include <vector>
#include <string>
#include <ctime>

namespace pm::type {
	struct Project
	{
		size_t id = 0;
		std::string name = "";
		std::string description = "";
		std::vector<size_t> members;

		std::time_t createdOn = 0;
		size_t idOfCreator = 0;
		std::time_t lastChange = 0;
		size_t idOfChanger = 0;
	};
}