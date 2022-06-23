#pragma once
#include "pch.h"
#include "User.h"
#include <vector>
#include <string>
#include <ctime>

namespace pm::type {
	struct Team
	{
		size_t id = 0;
		std::string name;
		std::vector<pm::type::User> members;
		std::time_t createdOn;
	};
}