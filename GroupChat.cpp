#include "GroupChat.h"

void GroupChat::copyFrom(const GroupChat& other)
{
	admin = other.admin;
	userSize = other.userSize;
	userCap = other.userCap;
	groupName = other.groupName;
	users = new User[userCap];
	for (int i = 0; i < userSize; i++) {
		users[i] = other.users[i];
	}
}

void GroupChat::moveFrom(GroupChat&& other)
{
	admin = other.admin;
	userSize = other.userSize;
	userCap = other.userCap;
	groupName = other.groupName;
	users = other.users;
	other.userCap = other.userSize = 0;
	other.groupName = "null";
	other.users = nullptr;
}

void GroupChat::free() {
	delete[] users;
}

void GroupChat::resizeUsers()
{
	if (userCap == 0) {
		userCap = 1;
		users = new User[userCap];
	}

	if (userSize == userCap) {
		userCap *= 2;
		User* newdata = new User[userCap];
		for (int i = 0; i < userSize; i++) {
			newdata[i] = users[i];
		}
		users = newdata;
		newdata = nullptr;
	}
}

GroupChat::GroupChat()
{
	userSize = userCap = 0;
	users = nullptr;
}

GroupChat::GroupChat(const GroupChat& other) : Chat(other)
{
	copyFrom(other);
}

GroupChat::GroupChat(GroupChat&& other) noexcept: Chat(std::move(other))
{
	moveFrom(std::move(other));
}

GroupChat& GroupChat::operator=(const GroupChat& other)
{
	if (this != &other) {
		Chat::operator=(other);
		free();
		copyFrom(other);
	}
	return *this;
}

GroupChat& GroupChat::operator=(GroupChat&& other) noexcept
{
	if (this != &other) {
		Chat::operator=(std::move(other));
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

GroupChat::~GroupChat()
{
	free();
}

Chat* GroupChat::clone() const
{
	return new GroupChat(*this);
}

void GroupChat::addUser(const User& user)
{
	for (int i = 0; i < userSize; i++) {
		if (user.getName() == users[i].getName()) {
			std::cout << "Cannot add user, user is already in the group!!" << '\n';
			return;
		}
	}

	resizeUsers();
	users[userSize++] = user;
}

void GroupChat::addNewUser(const String& name)
{
	for (int i = 0; i < userSize; i++) {
		if (name == users[i].getName()) {
			std::cout << "Cannot add user, user is already in the group!!" << '\n';
			return;
		}
	}

	resizeUsers();
	User u(name);
	u.setUnreadMess(0);
	users[userSize] = u;
	userSize++;
}

void GroupChat::removeUser(const String& name, int id, const String& user)
{
	if (name != admin.getName() || id < 0) {
		std::cout << "Cannot delete user, no authorized permission!!" << '\n';
		return;
	}

	bool userFound = false;
	for (int i = 0; i < userSize - 1; i++) {
		if (user == users[i].getName() || userFound) {
			users[i] = users[i + 1];
			userFound = true;
		}
	}
	userSize--;
}

void GroupChat::setAdmin(const String& name, const String& user)
{
	int place = 0, i = 0;
	bool found = false;

	while (i < userSize && !found) {
		if (users[i].getName() == user) {
			place = i;
			found = true;
		}
		i++;
	}

	if (name != admin.getName() && found) {
		std::cout << "Cannot give role to user, no authorized permission!!" << '\n';
		return;
	}

	User temp = admin;
	admin = users[place];
	users[place] = temp;
}

void GroupChat::viewChat() {
	std::cout << getUniqId() << ": " << groupName << " (" << getMessageCount() << "msg) Admin: " << admin.getName() << ",";
}

void GroupChat::printStats(const String& name) {
	std::cout << "*----------*" << '\n';
	std::cout << groupName << '\n';
	std::cout << "*----------*" << '\n';
	std::cout << "Message count: " << getMessageCount() << " messages!" << '\n';
	std::cout << "*----------*" << '\n';
	std::cout << "Admin: " << admin.getName() << '\n';
	std::cout << "Other users: ";
	for (int i = 0; i < userSize; i++) {
		if (name == users[i].getName()) {
			std::cout << "You, ";
		}
		else {
			std::cout << users[i].getName() << ", ";
		}
	}
	std::cout << '\n';
}

void GroupChat::saveToFile(std::fstream& os){
	char s = 'g';
	size_t id = getUniqId();
	size_t count = getMessageCount();
	os.write((const char*)&s, sizeof(char));
	groupName.saveToFile(os);
	admin.saveToFile(os);
	os.write((const char*)&userSize, sizeof(size_t));
	for (int i = 0; i < userSize; i++) {
		users[i].saveToFile(os);
	}
	os.write((const char*)&id, sizeof(size_t));
	os.write((const char*)&count, sizeof(size_t));
	Message** data = getMessages();
	for (int i = 0; i < count; i++) {
		data[i]->saveToFile(os);
	}
	data = nullptr;
	delete[] data;
}

void GroupChat::readFromFile(std::fstream& is) {
	size_t id = 0;
	size_t count = 0;
	groupName.readFromFile(is);
	admin.readFromFile(is);
	is.read((char*)&userSize, sizeof(size_t));
	for (int i = 0; i < userSize; i++) {
		User u;
		u.readFromFile(is);
		addUser(u);
	}
	is.read((char*)&id, sizeof(size_t));
	setId(id);
	is.read((char*)&count, sizeof(size_t));
	for (int i = 0; i < count; i++) {
		Message m;
		m.readFromFile(is);
		addMessage(m);
	}
}

void GroupChat::viewActiveChat(const String& username)
{
	size_t messages = 0;
	for (int i = 0; i < userSize; i++) {
		if (username == users[i].getName()) {
			messages = users[i].getUnreadMess();
			break;
		}
	}
	std::cout << groupName << " (" << messages << " unread) ,";
}
