#include "User.h"

void NormalUser::copyFrom(const NormalUser& other) {
	username = other.username;
	password = other.password;
	chatSize = other.chatSize;
	chatCap = other.chatCap;
	chats = new Chat*[chatCap];
	for (int i = 0; i < chatSize; i++) {
		chats[i] = new Chat(*other.chats[i]);
	}
}

void NormalUser::moveFrom(NormalUser&& other) {
	username = other.username;
	password = other.password;
	chatSize = other.chatSize;
	chatCap = other.chatCap;
	chats = other.chats;
	other.username = other.password = "Null";
	other.chatCap = other.chatSize = 0;
	other.chats = nullptr;
}

void NormalUser::free() {
	for (int i = 0; i < chatCap; i++) {
		delete[] chats[i];
	}
	delete[] chats;
}

void NormalUser::resize() {
	if (chats == nullptr) {
		chatCap = 1;
		chats = new Chat* [chatCap];
	}

	if (chatSize == chatCap) {
		chatCap = chatCap * 2;
		Chat** newdata = new Chat* [chatCap];
		for (int i = 0; i < chatSize; i++) {
			newdata[i] = new Chat(*chats[i]);
		}
		free();
		chats = newdata;
		newdata = nullptr;
	}
}

NormalUser::NormalUser() {
	username = "";
	password = "";
	chats = nullptr;
	chatCap = chatSize = 0;
}

NormalUser::NormalUser(const String& _username, const String& _password) : username(_username), password(_password){
	chats = nullptr;
	chatCap = chatSize = 0;
}

NormalUser::NormalUser(const NormalUser& other) {
	copyFrom(other);
}

NormalUser::NormalUser(NormalUser&& other) noexcept{
	moveFrom(std::move(other));
}

NormalUser& NormalUser::operator=(const NormalUser& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

NormalUser& NormalUser::operator=(NormalUser&& other) noexcept{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

NormalUser::~NormalUser() {
	free();
}

String NormalUser::getUsername() const
{
	return username;
}

Chat* NormalUser::getChat(size_t id) const
{
	for (int i = 0; i < chatSize; i++) {
		if (id == chats[i]->getUniqId()) {
			return chats[i];
		}
	}
	return nullptr;
}

size_t NormalUser::getChatSize() const
{
	return chatSize;
}

void NormalUser::addChat(const Chat& chat)
{
	resize();
	Chat* newChat = new Chat(chat);
	chats[chatSize] = newChat;
	chatSize++;
}

void NormalUser::removeChat(size_t id)
{
	bool found = false;
	for (int i = 0; i < chatSize - 1; i++) {
		if (id == chats[i]->getUniqId()) {
			delete[] chats[i];
			chats[i] = nullptr;
			found = true;
		}
		if (found) {
			chats[i] = chats[i + 1];
		}
	}
	if (chats[chatSize - 1]->getUniqId() == id || chats[chatSize - 1] == chats[chatSize - 2]) {
		delete[] chats[chatSize - 1];
		chats[chatSize - 1] = nullptr;
		chatSize--;
	}
}

void UserInfo::copyFrom(const UserInfo& other)
{
	username = other.username;
	password = other.password;
	adminKey = other.adminKey;
	size = other.size;
	cap = other.cap;
	chatIds = new int[cap];
	for (int i = 0; i < size; i++) {
		chatIds[i] = other.chatIds[i];
	}
}

void UserInfo::moveFrom(UserInfo&& other)
{
	username = other.username;
	password = other.password;
	adminKey = other.adminKey;
	size = other.size;
	cap = other.cap;
	chatIds = other.chatIds;
	other.username = other.password = "Null";
	other.adminKey = other.cap = other.size = 0;
	other.chatIds = nullptr;
}

void UserInfo::free() {
	delete[] chatIds;
}

void UserInfo::resize() {
	if (chatIds == nullptr) {
		cap = 1;
		chatIds = new int[cap];
	}

	if (size == cap) {
		cap = cap * 2;
		int* data = new int[cap];
		for (int i = 0; i < size; i++) {
			data[i] = chatIds[i];
		}
		free();
		chatIds = data;
		data = nullptr;
	}
}

UserInfo::UserInfo()
{
	username = password = "Unknown";
	adminKey = cap = size = 0;
	chatIds = nullptr;
}

UserInfo::UserInfo(const String& name, const String& pass) : username(name), password(pass)
{
	adminKey = cap = size = 0;
	chatIds = nullptr;
}

UserInfo::UserInfo(const UserInfo& other)
{
	copyFrom(other);
}

UserInfo::UserInfo(UserInfo&& other) noexcept
{
	moveFrom(std::move(other));
}

UserInfo& UserInfo::operator=(const UserInfo& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

UserInfo& UserInfo::operator=(UserInfo&& other) noexcept
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

UserInfo::~UserInfo()
{
	free();
}

void UserInfo::setAdminKey(int key)
{
	adminKey = key;
}

void UserInfo::addChatId(int id)
{
	if (chatIds == nullptr) {
		cap = 1;
		chatIds = new int[cap];
	}

	resize();
	chatIds[size] = id;
	size++;
}

String UserInfo::getUsername() const {
	return username;
}

String UserInfo::getPassword() const
{
	return password;
}

int UserInfo::getAdminKey() const
{
	return adminKey;
}

int UserInfo::getChatId(int index) const
{
	if (index < size) {
		return chatIds[index];
	}
	return -1;
}

int UserInfo::getSize() const {
	return size;
}

void UserInfo::saveToFile(std::fstream& os) {
	username.saveToFile(os);
	password.saveToFile(os);
	os.write((const char*)&adminKey, sizeof(int));
	os.write((const char*)&size, sizeof(int));
	for (int i = 0; i < size; i++) {
		os.write((const char*)&chatIds[i], sizeof(int));
	}
}

void UserInfo::readFromFile(std::fstream& is) {
	username.readFromFile(is);
	password.readFromFile(is);
	is.read((char*)&adminKey, sizeof(int));
	is.read((char*)&size, sizeof(int));
	for (int i = 0; i < size; i++) {
		int data = 0;
		is.read((char*)&data, sizeof(int));
		addChatId(data);
	}
}

bool UserInfo::compareUsernames(const String& _username)
{
	return username == _username;
}

bool UserInfo::comparePassword(const String& _password)
{
	return password == _password;
}

bool UserInfo::isAdmin() const
{
	return adminKey != 0;
}

int NormalUser::getKey() const {
	return 0;
}

NormalUser* NormalUser::clone() const {
	return new NormalUser(*this);
}