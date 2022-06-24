#include <iostream>
#include "../pm.bll/menuLogic.h"
#include "../pm.bll/UserStore.h"

int main()
{
	pm::bll::UserStore store;
	pm::bll::mainMenu(&store);
}