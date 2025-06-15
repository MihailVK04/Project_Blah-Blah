#include "SingleChat.h"

Chat* SingleChat::clone() const
{
	return new SingleChat(*this);
}

void SingleChat::printStats(const String& name)
{
	for (int i = 0; i < 2; i++) {
		if (users[i].getName() == name) {
			continue;
		}
		else {
			std::cout << "*----------*" << '\n';
			std::cout << users[i].getName() << '\n';
			std::cout << "*----------*" << '\n';
		}

		std::cout << "Message count: " << getMessageCount() << " messages!" << '\n';
		std::cout << '\n';
	}
}

void SingleChat::viewChat()
{
	std::cout << getUniqId() << ": " << users[0].getName() << "-" << users[1].getName() << " (" << getMessageCount() << " msg),";
}

void SingleChat::saveToFile(std::fstream& os) {
	char s = 's';
	size_t id = getUniqId();
	size_t count = getMessageCount();
	os.write((const char*)&s, sizeof(char));
	users[0].saveToFile(os);
	users[1].saveToFile(os);
	os.write((const char*)&id, sizeof(size_t));
	os.write((const char*)&count, sizeof(size_t));
	Message** data = getMessages();
	for (int i = 0; i < count; i++) {
		data[i]->saveToFile(os);
	}
	data = nullptr;
	delete[] data;
}

void SingleChat::readFromFile(std::fstream& is) {
	size_t id = 0;
	size_t count = 0;
	users[0].readFromFile(is);
	users[1].readFromFile(is);
	is.read((char*)&id, sizeof(size_t));
	setId(id);
	is.read((char*)&count, sizeof(size_t));
	for (int i = 0; i < count; i++) {
		Message m;
		m.readFromFile(is);
		addMessage(m);
	}
}

void SingleChat::viewActiveChat(const String& username)
{
	size_t messages = 0;
	String name;
	for (int i = 0; i < 2; i++) {
		if (username == users[i].getName()) {
			messages = users[i].getUnreadMess();
		}
		else {
			name == users[i].getName();
		}
	}
	std::cout << name << " (" << messages << " unread) ,";
}
