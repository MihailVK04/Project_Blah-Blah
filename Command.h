#pragma once
#include "AppBody.h"
#include "Container.hpp"
#include "String.h"

class Command {
public:
	virtual void execute() = 0;
	virtual ~Command() = default;
};

class CommandLogin : public Command 
{
private:
	AppBody* body;
	Container<String>* data;
public:
	CommandLogin(AppBody* b, Container<String>* d);
	void execute() override;
	~CommandLogin();
};

class CommandCreateAccount : public Command 
{
private:
	AppBody* body;
	Container<String>* data;
public:
	CommandCreateAccount(AppBody* b, Container<String>* d);
	void execute() override;
	~CommandCreateAccount();
};

class CommandViewChats : public Command 
{
private:
	AppBody* body;
	Container<String>* data;
public:
	CommandViewChats(AppBody* b, Container<String>* d);
	void execute() override;
	~CommandViewChats();
};

//class CommandSelectChat : public Command 
//{
//private:
//	AppBody* body;
//	Container<String>* data;
//public:
//	CommandSelectChat(AppBody* b, Container<String>* d);
//	void execute() override;
//	~CommandSelectChat();
//};
//
//class CommandCreateGroup : public Command 
//{
//private:
//	AppBody* body;
//	Container<String>* data;
//public:
//	CommandCreateGroup(AppBody* b, Container<String>* d);
//	void execute() override;
//	~CommandCreateGroup();
//};
//
//class CommandLogout : public Command 
//{
//private:
//	AppBody* body;
//	Container<String>* data;
//public:
//	CommandLogout(AppBody* b, Container<String>* d);
//	void execute() override;
//	~CommandLogout();
//};
//
//class CommandLeaveGroup : public Command 
//{
//private:
//	AppBody* body;
//	Container<String>* data;
//public:
//	CommandLeaveGroup(AppBody* b, Container<String>* d);
//	void execute() override;
//	~CommandLeaveGroup();
//};
//
//class CommandAddToGroup : public Command 
//{
//private:
//	AppBody* body;
//	Container<String>* data;
//public:
//	CommandAddToGroup(AppBody* b, Container<String>* d);
//	void execute() override;
//	~CommandAddToGroup();
//};
//
//class CommandKickFromGroup : public Command 
//{
//private:
//	AppBody* body;
//	Container<String>* data;
//public:
//	CommandKickFromGroup(AppBody* b, Container<String>* d);
//	void execute() override;
//	~CommandKickFromGroup();
//};
//
//class CommandSetGroupAdmin : public Command 
//{
//private:
//	AppBody* body;
//	Container<String>* data;
//public:
//	CommandSetGroupAdmin(AppBody* b, Container<String>* d);
//	void execute() override;
//	~CommandSetGroupAdmin();
//};
//
//class CommandGroupStats : public Command 
//{
//private:
//	AppBody* body;
//	Container<String>* data;
//public:
//	CommandGroupStats(AppBody* b, Container<String>* d);
//	void execute() override;
//	~CommandGroupStats();
//};
//
//class CommandDeleteUser : public Command 
//{
//private:
//	AppBody* body;
//	Container<String>* data;
//public:
//	CommandDeleteUser(AppBody* b, Container<String>* d);
//	void execute() override;
//	~CommandDeleteUser();
//};
//
//class CommandDeleteGroup : public Command 
//{
//private:
//	AppBody* body;
//	Container<String>* data;
//public:
//	CommandDeleteGroup(AppBody* b, Container<String>* d);
//	void execute() override;
//	~CommandDeleteGroup();
//};
//
//class CommandViewAllChats : public Command 
//{
//private:
//	AppBody* body;
//	Container<String>* data;
//public:
//	CommandViewAllChats(AppBody* b, Container<String>* d);
//	void execute() override;
//	~CommandViewAllChats();
//};
//
//class CommandExitProgram : public Command 
//{
//private:
//	AppBody* body;
//	Container<String>* data;
//public:
//	CommandExitProgram(AppBody* b, Container<String>* d);
//	void execute() override;
//	~CommandExitProgram();
//};