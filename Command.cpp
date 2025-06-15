#include "Command.h"

CommandLogin::CommandLogin(AppBody* b, Container<String>* d) : body(b), data(d)
{
}

void CommandLogin::execute()
{
	if (body->getCurrentUser() != nullptr) {
		std::cout << "Already a loged user, try logout first!" << '\n';
		return;
	}

	if (data->getSize() == 3) {
		size_t size = body->getUsers()->getSize();
		for (int i = 0; i < size; i++) {
			if (body->CheckLoginInfoAdmin(*(*data)[1], *(*data)[2], i)) {
				body->loginUserAdmin(i);
				std::cout << "Logged in!" << '\n';
				return;
			}
			else if (body->CheckLoginInfo(*(*data)[1], *(*data)[2], i)) {
				body->loginUser(i);
				std::cout << "Logged in!" << '\n';
				return;
			}
		}
		if (body->getCurrentUser() != nullptr) {
			std::cout << "No user found. Would you like to create a new one?(y/n)" << '\n';
			char answer;
			std::cin >> answer;
			if (answer == 'y') {
				body->createAccount(*(*data)[1], *(*data)[2]);
				std::cout << "Try login aggain." << '\n';
			}
			else {
				return;
			}
		}
	}
}

CommandLogin::~CommandLogin()
{
	body = nullptr;
	data = nullptr;
}

CommandCreateAccount::CommandCreateAccount(AppBody* b, Container<String>* d) : body(b), data(d)
{
}

void CommandCreateAccount::execute()
{
	if (data->getSize() == 3) {
		body->createAccount(*(*data)[1], *(*data)[2]);
	}
}

CommandCreateAccount::~CommandCreateAccount()
{
	body = nullptr;
	data = nullptr;
}

CommandViewChats::CommandViewChats(AppBody* b, Container<String>* d) : body(b), data(d)
{
}

void CommandViewChats::execute()
{
	if (body->getCurrentUser() != nullptr) {
		body->printUserChats();
	}
}

CommandViewChats::~CommandViewChats()
{
	body = nullptr;
	data = nullptr;
}

//CommandSelectChat::CommandSelectChat(AppBody* b, Container<String>* d) : body(b), data(d)
//{
//}
//
//CommandSelectChat::~CommandSelectChat()
//{
//	body = nullptr;
//	data = nullptr;
//}
//
//CommandCreateGroup::CommandCreateGroup(AppBody* b, Container<String>* d) : body(b), data(d)
//{
//}
//
//CommandCreateGroup::~CommandCreateGroup()
//{
//	body = nullptr;
//	data = nullptr;
//}
//
//CommandLogout::CommandLogout(AppBody* b, Container<String>* d) : body(b), data(d)
//{
//}
//
//CommandLogout::~CommandLogout()
//{
//	body = nullptr;
//	data = nullptr;
//}
//
//CommandLeaveGroup::CommandLeaveGroup(AppBody* b, Container<String>* d) : body(b), data(d)
//{
//}
//
//CommandLeaveGroup::~CommandLeaveGroup()
//{
//	body = nullptr;
//	data = nullptr;
//}
//
//CommandAddToGroup::CommandAddToGroup(AppBody* b, Container<String>* d) : body(b), data(d)
//{
//}
//
//CommandAddToGroup::~CommandAddToGroup()
//{
//	body = nullptr;
//	data = nullptr;
//}
//
//CommandKickFromGroup::CommandKickFromGroup(AppBody* b, Container<String>* d) : body(b), data(d)
//{
//}
//
//CommandKickFromGroup::~CommandKickFromGroup()
//{
//	body = nullptr;
//	data = nullptr;
//}
//
//CommandSetGroupAdmin::CommandSetGroupAdmin(AppBody* b, Container<String>* d) : body(b), data(d)
//{
//}
//
//CommandSetGroupAdmin::~CommandSetGroupAdmin()
//{
//	body = nullptr;
//	data = nullptr;
//}
//
//CommandGroupStats::CommandGroupStats(AppBody* b, Container<String>* d) : body(b), data(d)
//{
//}
//
//CommandGroupStats::~CommandGroupStats()
//{
//	body = nullptr;
//	data = nullptr;
//}
//
//CommandDeleteUser::CommandDeleteUser(AppBody* b, Container<String>* d) : body(b), data(d)
//{
//}
//
//CommandDeleteUser::~CommandDeleteUser()
//{
//	body = nullptr;
//	data = nullptr;
//}
//
//CommandDeleteGroup::CommandDeleteGroup(AppBody* b, Container<String>* d) : body(b), data(d)
//{
//}
//
//CommandDeleteGroup::~CommandDeleteGroup()
//{
//	body = nullptr;
//	data = nullptr;
//}
//
//CommandViewAllChats::CommandViewAllChats(AppBody* b, Container<String>* d) : body(b), data(d)
//{
//}
//
//CommandViewAllChats::~CommandViewAllChats()
//{
//	body = nullptr;
//	data = nullptr;
//}
//
//CommandExitProgram::CommandExitProgram(AppBody* b, Container<String>* d) : body(b), data(d)
//{
//}
//
//CommandExitProgram::~CommandExitProgram()
//{
//	body = nullptr;
//	data = nullptr;
//}
