#pragma once
#include <vector>
#include <string>
#include "../pm.pl/Menu.h"
#include "../pm.types/User.h"
#include "ProjectManager.h"

namespace pm::bll {
	void mainMenu(pm::bll::ProjectManager*);
	void logInMenu(pm::bll::ProjectManager*);
	void projectsManagmentMenu(pm::bll::ProjectManager*);
	void usersManagmentMenu(pm::bll::ProjectManager*);
	void teamsManagmentMenu(pm::bll::ProjectManager*);
	void assignUsersMenu(pm::bll::ProjectManager*, size_t);
}