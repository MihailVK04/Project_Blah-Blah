#include "Chat.h"

User::User(const String& _name)
{
	name = _name;
}

void User::setUnreadMess(size_t unread)
{
	unreadMess = unread;
}

String User::getName() const
{
	return name;
}

size_t User::getUnreadMess() const
{
	return unreadMess;
}

void User::saveToFile(std::fstream& os) {
	os.write((const char*)&unreadMess, sizeof(size_t));
	name.saveToFile(os);
}

void User::readFromFile(std::fstream& is) {
	is.read((char*)&unreadMess, sizeof(size_t));
	name.readFromFile(is);
}

void Chat::copyFrom(const Chat& other) {
	uniqId = other.uniqId;
	messageCount = other.messageCount;
	messageCap = other.messageCap;
	messages = new Message* [messageCap];
	int i = 0;
	while (i < messageCap) {
		//*messages[i] = *other.messages[i];
		messages[i] = new Message(*other.messages[i]);
		i++;
	}
}

void Chat::moveFrom(Chat&& other) {
	uniqId = other.uniqId;
	messageCount = other.messageCount;
	messageCap = other.messageCap;
	messages = other.messages;
	other.uniqId = other.messageCount = other.messageCap = 0;
	other.messages = nullptr;
}

void Chat::free() {
	int i = 0;
	while (i < messageCap) {
		delete[] messages[i];
		i++;
	}
	delete[] messages;
}

void Chat::resize() {

	if (messageCap == 0) {
		messageCap = 1;
		messages = new Message* [messageCap];
	}

	if (messageCount == messageCap) {
		messageCap = messageCap * 2;
		Message** newdata = new Message* [messageCap];
		int i = 0;
		while (i < messageCount) {
			//*newdata[i] = *messages[i];
			newdata[i] = new Message(*messages[i]);
		}
		free();
		messages = newdata;
		newdata = nullptr;
	}
}

Chat::Chat(const Chat& other) {
	copyFrom(other);
}

Chat::Chat(Chat&& other) noexcept{
	moveFrom(std::move(other));
}

Chat& Chat::operator=(const Chat& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Chat& Chat::operator=(Chat&& other) noexcept{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Chat::~Chat() {
	free();
}

void Chat::addMessage(const Message& message)
{
	resize();
	Message* newMessage = new Message(message);
	messages[messageCount] = newMessage;
	messageCount++;
}

void Chat::printfrom(size_t unread)
{
	if (unread <= 0) {
		std::cout << *messages[messageCount - 1];
	}
	else {
		int i = unread;
		while (i > 0) {
			std::cout << *messages[messageCount - i];
			i--;
		}
	}
}

void Chat::setId(size_t id)
{
	uniqId = id;
}

Message** Chat::getMessages() const
{
	return messages;
}

size_t Chat::getMessageCount() const
{
	return messageCount;
}

size_t Chat::getUniqId() const
{
	return uniqId;
}

Chat* Chat::clone() const
{
	return nullptr;
}

void Chat::addUser(const User& user) {
	std::cout << "Cannot add another user. Maybe try to make a group chat!" << '\n';
}

void Chat::addNewUser(const String& name) {
	std::cout << "Cannot add another user. Maybe try to make a group chat!" << '\n';
}

void Chat::removeUser(const String& name, int id, const String& user) {
	std::cout << "Cannot remove user. Not authorized or not possible for this chat." << '\n';
}

void Chat::setAdmin(const String& name, const String& user) {
	std::cout << "Setting admin is not permited here!" << '\n';
}

void Chat::printStats(const String& name) {
	return;
}

void Chat::viewChat() {
	return;
}

void Chat::saveToFile(std::fstream& os) {
	return;
}

void Chat::viewActiveChat(const String& username)
{
	return;
}
