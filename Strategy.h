#pragma once
#include "UniquePtr.hpp"
#include "Container.hpp"
#include "Chat.h"
#include "User.h"
#include "String.h" 
#include "GroupChat.h"
#include "SingleChat.h"

//static const char* convertTochar(int data);

class StrategyRW {
public:
	virtual ~StrategyRW() = default;
	virtual void readWriteChats(char type,Chat* chat, std::fstream& stream) const = 0;
	virtual void readWriteIds(int* other, int& size, std::fstream& stream) const = 0;
	virtual void readWriteUsers(Container<UserInfo>& other, std::fstream& stream) const = 0;
	virtual bool isRead() const = 0;
};

class Context {
private:
	UniquePtr<StrategyRW> strategy;
public:
	explicit Context(UniquePtr<StrategyRW>&& strategy);
	void setStrategy(UniquePtr<StrategyRW>&& strategy);
	void readWriteInBinary(Container<Chat>& chats, Container<UserInfo>& users, int* chatIds, int& size);
	void readWriteInText(Container<Chat>& chats, Container<UserInfo>& users, int* chatIds, int& size);
};

class ReadStrategy : public StrategyRW{
public:
	void readWriteChats(char type,Chat* chat, std::fstream& stream) const override;
	void readWriteIds(int* other,int& size, std::fstream& stream) const override;
	void readWriteUsers(Container<UserInfo>& other, std::fstream& stream) const override;
	bool isRead() const override;
};

class WriteStrategy : public StrategyRW{
public:
	void readWriteChats(char type,Chat* chat, std::fstream& stream) const override;
	void readWriteIds(int* other,int& size, std::fstream& stream) const override;
	void readWriteUsers(Container<UserInfo>& other, std::fstream& stream) const override;
	bool isRead() const override;
};