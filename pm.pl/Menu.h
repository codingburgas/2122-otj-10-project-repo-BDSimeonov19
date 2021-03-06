#pragma once
#include <string>
#include <vector>
#include "../pm.types/User.h"
#include "../pm.bll/ProjectManager.h"


namespace pm::pl {
	void colour(int color);
	void gotoxy(int x, int y);
	void optionsDisplay(std::string str, bool chosen, int posx, int posy, int maxLength); // Display avalable options in the current menu
	int Menu(std::vector<std::string>, pm::bll::ProjectManager*); //Main menu with three options
	void loggedUser(pm::bll::ProjectManager*);
}