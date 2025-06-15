#pragma once
#include <iostream>
#include <ctime>
#include "Util.h"
#include "Command.h"
#include "AppBody.h"
#include "Strategy.h"
#include "Stack.hpp"
#pragma warning (disable:4996)

void executeCommands(AppBody* body, Container<String>* strings, bool &end) {
    if (*(*strings)[0] == "login") {
        CommandLogin c(body, strings);
        c.execute();
        return;
    }
    if (*(*strings)[0] == "create-account") {
        CommandCreateAccount c(body, strings);
        c.execute();
        return;
    }
    if (*(*strings)[0] == "view-chats") {
        CommandViewChats c(body, strings);
        c.execute();
        return;
    }
    //More command must be put here...
    if (*(*strings)[0] == "exit-program") {
        end = false;
        return;
    }
}

int main()
{
    ReadStrategy m;
    WriteStrategy n;
    UniquePtr<StrategyRW> read(&m);
    UniquePtr<StrategyRW> write(&n);
    Context c(std::move(read));
    Container<Chat> chats;
    Container<UserInfo> users;
    int* ids = nullptr;
    int size = 0;
    c.readWriteInBinary(chats, users, ids, size);
    AppBody app(&chats, &users, ids, size);
    bool loop = true;
    while (loop) {
        Sentences command;
        std::cin >> command;
        Container<String> strings;
        int index = 0, last = 0, inbetween = 0;
        while (index < command.getWords().getSize()) {
            if (command.getWords()[index] == ' ') {
                inbetween = index - last;
                strings.addElement(copyFromChar(command.getWords().c_str(), inbetween));
                last = index + 1;
            }
            index++;
        }
        executeCommands(&app, &strings, loop);
    }
    c.setStrategy(std::move(write));
    c.readWriteInBinary(chats, users, ids, size);
    c.readWriteInText(chats, users, ids, size);
    ids = nullptr;
    delete[] ids;
}