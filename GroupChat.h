#pragma once
#include "Chat.h"
#include "String.h"

class GroupChat : public Chat {
private:
	User admin;
	User* users;
	size_t userSize;
	size_t userCap;
	String groupName;

	void copyFrom(const GroupChat& other);
	void moveFrom(GroupChat&& other);
	void free();
	void resizeUsers();

public:
	GroupChat();
	GroupChat(const GroupChat& other);
	GroupChat(GroupChat&& other) noexcept;
	GroupChat& operator=(const GroupChat& other);
	GroupChat& operator=(GroupChat&& other) noexcept;
	~GroupChat();

	Chat* clone() const override;
	void addUser(const User& user) override;
	void addNewUser(const String& name) override;
	void removeUser(const String& name, int id, const String& user) override;
	void setAdmin(const String& name, const String& user) override;
	void viewChat() override;
	void printStats(const String& name) override;
	void saveToFile(std::fstream& os) override;
	void readFromFile(std::fstream& is);
	void viewActiveChat(const String& username) override;
};