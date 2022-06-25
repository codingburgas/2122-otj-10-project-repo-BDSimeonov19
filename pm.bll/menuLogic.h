#pragma once
#include <vector>
#include <string>
#include "../pm.pl/Menu.h"
#include "../pm.types/User.h"
#include "TeamStore.h"

namespace pm::bll {
	void mainMenu(pm::bll::TeamStore*);
	void logInMenu(pm::bll::TeamStore*);
	void usersManagmentMenu(pm::bll::TeamStore*);
	void teamsManagmentMenu(pm::bll::TeamStore*);
	void assignMembersMenu(pm::bll::TeamStore*, size_t);
}