#pragma once

#include "pch.h"
#include <string>
#include <ctime>

namespace pm::type {
	struct User
	{
		size_t id = 0;
		std::string firstName = "";
		std::string lastName = "";
		std::string Email = "";
		unsigned short age = 0;
		std::string passwordHash = "";
		std::time_t createdOn = 0;
		bool admin = 0;
	};
}