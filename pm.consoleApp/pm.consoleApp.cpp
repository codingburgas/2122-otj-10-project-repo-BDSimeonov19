#include <iostream>
#include "../pm.bll/UserStore.h"

int main()
{
	pm::type::User user;
	pm::bll::UserStore store;
	store.list();
}