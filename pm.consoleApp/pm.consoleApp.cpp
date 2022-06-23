#include <iostream>
#include "../pm.bll/UserStore.h"

int main()
{
	pm::type::User user;
	pm::dal::UserStore store;
	store.list();
}