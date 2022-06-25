#include <iostream>
#include "../pm.bll/menuLogic.h"
#include "../pm.bll/TeamStore.h"

int main()
{
	pm::bll::TeamStore store;
	pm::bll::mainMenu(&store);
}