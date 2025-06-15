#include "AppBody.h"

void AppBody::copyFrom(const AppBody& other)
{
	chats = new Container<Chat>(*other.chats);
	users = new Container<UserInfo>(*other.users);
	currentUser = new NormalUser(*other.currentUser);
	currentChat = new Chat(*other.currentChat);
	size = other.size;
	cap = other.cap;
	chatids = new int[cap];
	for (int i = 0; i < size; i++) {
		chatids[i] = other.chatids[i];
	}
}

void AppBody::moveFrom(AppBody&& other)
{
	chats = other.chats;
	users = other.users;
	currentUser = other.currentUser;
	currentChat = other.currentChat;
	size = other.size;
	cap = other.cap;
	chatids = other.chatids;
	other.size = other.cap = 0;
	other.currentUser = nullptr;
	other.currentChat = nullptr;
	chatids = nullptr;
	other.chats = nullptr;
	other.users = nullptr;
}

void AppBody::free() {
	delete[] chatids;
}

void AppBody::resizeChats() {
	if (chatids == nullptr) {
		cap = 1;
		chatids = new int[cap];
	}

	if (size == cap) {
		cap = cap * 2;
		int* newdata = new int[cap];
		for (int i = 0; i < size; i++) {
			newdata[i] = chatids[i];
		}
		free();
		chatids = newdata;
		newdata = nullptr;
	}
}

AppBody::AppBody(Container<Chat>* _chats, Container<UserInfo>* _users, int* _ids, int _size)
{
	chats = _chats;
	users = _users;
	chatids = _ids;
	size = _size;
	cap = 2 * size;
}

AppBody::AppBody(const AppBody& other)
{
	copyFrom(other);
}

AppBody::AppBody(AppBody&& other) noexcept
{
	moveFrom(std::move(other));
}

AppBody& AppBody::operator=(const AppBody& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

AppBody& AppBody::operator=(AppBody&& other) noexcept
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

AppBody::~AppBody()
{
	free();
}

NormalUser* AppBody::getCurrentUser() const
{
	return currentUser;
}

Container<UserInfo>* AppBody::getUsers() const
{
	return users;
}

bool AppBody::CheckLoginInfo(const String& username, const String& password, int index)
{
	return (*users)[index]->compareUsernames(username) && (*users)[index]->comparePassword(password);
}

bool AppBody::CheckLoginInfoAdmin(const String& username, const String& password, int index)
{
	return CheckLoginInfo(username, password, index) || (*users)[index]->isAdmin();
}

void AppBody::loginUser(int index)
{
	String name = (*users)[index]->getUsername();
	String password = (*users)[index]->getPassword();
	currentUser = new NormalUser(name, password);
	int size = (*users)[index]->getSize();
	for (int i = 0; i < size; i++) {
		int key = (*users)[index]->getChatId(i);
		int chatSize = chats->getSize();
		for (int j = 0; j < chatSize; j++) {
			if (key == (*chats)[j]->getUniqId()) {
				currentUser->addChat(*(*chats)[j]);
			}
		}
	}
}

void AppBody::loginUserAdmin(int index)
{
	String name = (*users)[index]->getUsername();
	String password = (*users)[index]->getPassword();
	int AdminKey = (*users)[index]->getAdminKey();
	Administrator buff(name, password,AdminKey);
	int size = (*users)[index]->getSize();
	for (int i = 0; i < size; i++) {
		int key = (*users)[index]->getChatId(i);
		int chatSize = chats->getSize();
		for (int j = 0; j < chatSize; j++) {
			if (key == (*chats)[j]->getUniqId()) {
				buff.addChat(*(*chats)[j]);
			}
		}
	}
	currentUser = buff.clone();
}

void AppBody::createAccount(const String& name, const String& pass)
{
	int size = users->getSize();
	bool found = false;
	for (int i = 0; i < size; i++) {
		if (CheckLoginInfo(name, pass, i) == true) {
			found = true;
		}
		if ((*users)[i]->compareUsernames(name)) {
			std::cout << "Name altready in use, try other name!" << '\n';
		}
	}
	if (!found) {
		UserInfo newdata(name, pass);
		users->addElement(newdata);
		std::cout << "Account created!" << '\n';
	}
}

void AppBody::printUserChats() const
{
	size_t size = currentUser->getChatSize();
	for (int i = 0; i < size; i++) {
		currentUser->getChat(i)->viewActiveChat(currentUser->getUsername());
	}
}
