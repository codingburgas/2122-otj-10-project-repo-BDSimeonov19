#include <iostream>
#include "../pm.dal/UserStore.h"

int main()
{
	pm::type::User user(1, "Boris", "Simeonov", "gaming@gmail.com", 16, "boingboing", time(NULL), false);
	/*user.id = 1;
	user.firstName = "Boris";
	user.lastName = "Simeonov";
	user.Email = "gaming@gmail.com";
	user.age = 16;
	user.passwordHash = "boingboing";
	time(&user.createdOn);*/


	pm::dal::UserStore store;
	store.create(user);
	store.list();
}