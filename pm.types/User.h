#pragma once

#include "pch.h"
#include <string>
#include <ctime>

namespace pm::type {
	struct User
	{
		size_t id;
		std::string firstName;
		std::string lastName;
		std::string Email;
		unsigned short age;
		std::string passwordHash;
		std::time_t createdOn;
	};
}