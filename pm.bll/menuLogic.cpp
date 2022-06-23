#include "pch.h"
#include "menuLogic.h"
#include "../pm.pl/Menu.h"

void pm::bll::mainMenu()
{
	std::vector<std::string> mainMenuOptions = { "        Start        ",
												 "        Help        ",
												 "        History        " ,
												 "        Exit        " };

	switch (pm::pl::Menu(mainMenuOptions)) {
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		return;
	}
}
