#include <iostream>
#include "../pm.bll/menuLogic.h"
#include "../pm.bll/ProjectManager.h"

int main()
{
	pm::bll::ProjectManager manager;
	pm::bll::mainMenu(&manager);
}