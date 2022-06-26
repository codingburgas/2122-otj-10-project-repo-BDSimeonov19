#include "pch.h"
#include "UserStore.h"
#include "sha256.h"

//constructor to pull the database info on start of program
pm::bll::UserStore::UserStore()
{
	users.push_back(admin);
	database.pullDb(&users);
}

//add a new user to the database
void pm::bll::UserStore::add(pm::type::User user)
{
	user.id += users.size();
	users.push_back(user);

	database.updateDb(users);
}

//returns all users
std::vector<pm::type::User> pm::bll::UserStore::getAll()
{
	return users;
}

//remove a user by id
void pm::bll::UserStore::remove(size_t id)
{
	if (id == 0)
		std::cout << "Can not remove admin\n";
	else if (id == loggedInUser.id)
		std::cout << "Can not remove logged in user\n";
	else if (id + 1 > users.size() || id < 0)
		std::cout << "Id out of range\n";
	else {
		users.erase(users.begin() + id);

		for (int i = id; i < users.size(); i++)
			users[i].id--;

		database.updateDb(users);
	}
}

//update a user by id
void pm::bll::UserStore::update(pm::type::User user, size_t id)
{
	if (id == 0)
		std::cout << "Can not change admin\n";

	else {
		user.id = id;
		user.createdOn = users[id].createdOn;
		user.idOfCreator = users[id].idOfCreator;
		user.lastChange = time(NULL);
		user.idOfChanger = loggedInUser.id;


		users.insert(users.begin() + user.id + 1, user);
		users.erase(users.begin() + user.id);

		database.updateDb(users);
	}
}

//get a user by id
pm::type::User pm::bll::UserStore::getById(size_t id)
{
	return users[id];
}

//list all users
void pm::bll::UserStore::listAll() {
	for (auto i : users)
		listById(i.id);
}

//list all users
void pm::bll::UserStore::listById(size_t id) {
	char buffer[80];
	struct tm time;
	const time_t* rawTime;

	std::cout << "Id : " << users[id].id << std::endl;
	std::cout << "Name : " << users[id].firstName << " " << users[id].lastName << std::endl;
	std::cout << "Age : " << users[id].age << std::endl;
	std::cout << "Email : " << users[id].Email << std::endl;

	//translate time_t into human readable format
	localtime_s(&time, &users[id].createdOn);
	strftime(buffer, 80, "%d/%m/%y @ %I:%M%p", &time);
	std::cout << "Created on : " << buffer << std::endl;

	std::cout << "Id of creator : " << users[id].idOfCreator << std::endl;
	
	localtime_s(&time, &users[id].lastChange);
	strftime(buffer, 80, "%d/%m/%y @ %I:%M%p", &time);
	std::cout << "Last change on : " << buffer << std::endl;

	std::cout << "Id of the user that did the last change : " << users[id].idOfChanger << std::endl;
	std::cout << "Privilege level : " << users[id].admin << std::endl << std::endl;
}

//hash a user's password using sha256
std::string pm::bll::UserStore::password() {
	char ch;
	std::string pass;
	int i = 0;
	while ((ch = _getch()) != '\r')
		pass += ch;

	SHA256 sha256;
	return sha256(pass);
}

//create a new user
pm::type::User pm::bll::UserStore::create() {
	pm::type::User user;


	std::cout << "First and last names\n";
	std::cin >> user.firstName >> user.lastName;
	std::cout << "Email\n";
	std::cin >> user.Email;
	std::cout << "Age\n";
	std::cin >> user.age;
	std::cout << "Enter password\n";
	user.passwordHash = password();
	user.createdOn = time(NULL);
	user.idOfCreator = loggedInUser.id;
	user.lastChange = time(NULL);
	user.idOfChanger = loggedInUser.id;
	std::cout << "Enter privilege level\n";
	std::cin >> user.admin;

	return user;
}

//log in system
bool pm::bll::UserStore::logIn() {
	std::string name, password;
	std::cout << "Enter first name\n";
	std::cin >> name;
	std::cout << "Enter password\n";
	password = pm::bll::UserStore::password();

	for (auto i : users) {
		if (i.firstName == name && i.passwordHash == password) {
			loggedInUser = i;
			return true;
		}
	}

	if (name == "admin" && password == "713bfda78870bf9d1b261f565286f85e97ee614efe5f0faf7c34e7ca4f65baca") {
		loggedInUser = admin;
		return true;
	}
	return false;
}
