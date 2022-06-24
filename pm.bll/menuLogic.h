#pragma once
#include <vector>
#include <string>
#include "../pm.pl/Menu.h"
#include "../pm.types/User.h"
#include "UserStore.h"

namespace pm::bll {
	void mainMenu(pm::bll::UserStore*);
	void logInMenu(pm::bll::UserStore*);
}