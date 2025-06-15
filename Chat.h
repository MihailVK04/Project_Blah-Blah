#pragma once
#include "Message.h"
#include "String.h"


struct User {
private:
	String name;
	size_t unreadMess = 0;

public:
	User() = default;
	User(const String& name);
	void setUnreadMess(size_t unread);
	String getName() const;
	size_t getUnreadMess() const;
	void saveToFile(std::fstream& os);
	void readFromFile(std::fstream& is);
};

class Chat {
private:
	size_t uniqId = 0; 
	size_t messageCount = 0;
	size_t messageCap = 0;
	Message** messages = nullptr;

	void copyFrom(const Chat& other);
	void moveFrom(Chat&& other);
	void free();
	void resize();

public:

	Chat() = default;
	Chat(const Chat& other);
	Chat(Chat&& other) noexcept;
	Chat& operator=(const Chat& other);
	Chat& operator=(Chat&& other) noexcept;
	virtual ~Chat();

	void addMessage(const Message& message);
	void printfrom(size_t unread);
	void setId(size_t id);
	Message** getMessages() const;
	size_t getMessageCount() const;
	size_t getUniqId() const;

	virtual Chat* clone() const;
	virtual void addUser(const User& user);
	virtual void addNewUser(const String& name);
	virtual void removeUser(const String& name, int id, const String& user);
	virtual void setAdmin(const String& name, const String& user);
	virtual void printStats(const String& name);
	virtual void viewChat();
	virtual void saveToFile(std::fstream& os);
	virtual void viewActiveChat(const String& username);
};