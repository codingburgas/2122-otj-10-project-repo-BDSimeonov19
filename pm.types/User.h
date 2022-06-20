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
		bool admin;

		User(size_t id, std::string firstName, std::string lastName, std::string Email, unsigned short age, std::string passwordHash, std::time_t createdOn, bool isAdmin) {
			this->id = id;
			this->firstName = firstName;
			this->lastName = lastName;
			this->Email = Email;
			this->age = age;
			this->passwordHash = passwordHash;
			this->createdOn = createdOn;
			this->admin = admin;
		}
	};
	
	
}