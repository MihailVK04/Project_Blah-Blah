#pragma once
#include "User.h"
#include "Administrator.h"
#include "Chat.h"
#include "Container.hpp"
#include "GroupChat.h"
#include "SingleChat.h"
#include "Message.h"
#include "String.h"
#include "Strategy.h"

class AppBody {
private:
	Container<Chat>* chats;
	Container<UserInfo>* users;
	int* chatids = nullptr;
	int size = 0;
	int cap = 0;
	NormalUser* currentUser = nullptr;
	Chat* currentChat = nullptr;

	void copyFrom(const AppBody& other);
	void moveFrom(AppBody&& other);
	void free();
	void resizeChats();

public:
	AppBody() = default;
	AppBody(Container<Chat>* chats, Container<UserInfo>* users, int* ids, int size);
	AppBody(const AppBody& other);
	AppBody(AppBody&& other) noexcept;
	AppBody& operator=(const AppBody& other);
	AppBody& operator=(AppBody&& other) noexcept;
	~AppBody();

	NormalUser* getCurrentUser() const;
	Container<UserInfo>* getUsers() const;
	bool CheckLoginInfoAdmin(const String& username, const String& password, int index);
	bool CheckLoginInfo(const String& username, const String& password, int index);
	void loginUser(int index);
	void loginUserAdmin(int index);
	void createAccount(const String& name, const String& pass);
	void printUserChats()const;
};
