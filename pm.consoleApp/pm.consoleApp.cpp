#include <iostream>
#include "../pm.dal/UserStore.h"
int main()
{
	pm::type::User user;
	pm::dal::UserStore store;
	store.list();
}