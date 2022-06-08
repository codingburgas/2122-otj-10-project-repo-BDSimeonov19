#include <iostream>
#include "../pm.dal/UserStore.h"

int main()
{
	pm::type::User user;
	user.id = 1;
	user.firstName = "Boris";
	user.lastName = "Simeonov";
	user.Email = "gaming@gmail.com";
	user.age = 16;
	user.passwordHash = "boingboing";
	time(&user.createdOn);


	pm::dal::UserStore store;
	store.create(user);
	store.list();
}