#pragma once
#include "Chat.h"
#include "String.h"

struct UserInfo {
private:
	String username;
	String password;
	int adminKey;
	int* chatIds;
	int size;
	int cap;

	void copyFrom(const UserInfo& other);
	void moveFrom(UserInfo&& other);
	void free();
	void resize();

public:

	UserInfo();
	UserInfo(const String& name, const String& pass);
	UserInfo(const UserInfo& other);
	UserInfo(UserInfo&& other) noexcept;
	UserInfo& operator=(const UserInfo& other);
	UserInfo& operator=(UserInfo&& other) noexcept;
	~UserInfo();

	void setAdminKey(int key);
	void addChatId(int id);
	String getUsername() const;
	String getPassword() const;
	int getAdminKey() const;
	int getChatId(int index) const;
	int getSize() const;
	void saveToFile(std::fstream& os);
	void readFromFile(std::fstream& is);
	bool compareUsernames(const String& _username);
	bool comparePassword(const String& _password);
	bool isAdmin() const;
};

class NormalUser {
private:
	String username;
	String password;
	size_t chatSize;
	size_t chatCap;
	Chat** chats;

	void copyFrom(const NormalUser& other);
	void moveFrom(NormalUser&& other);
	void free();
	void resize();

public:

	NormalUser();
	NormalUser(const String& username, const String& password);
	NormalUser(const NormalUser& other);
	NormalUser(NormalUser&& other) noexcept;
	NormalUser& operator=(const NormalUser& other);
	NormalUser& operator=(NormalUser&& other) noexcept;
	virtual ~NormalUser();

	String getUsername() const;
	Chat* getChat(size_t id) const;
	size_t getChatSize()const;
	void addChat(const Chat& chat);
	void removeChat(size_t id);
	virtual int getKey() const;
	virtual NormalUser* clone() const;
};