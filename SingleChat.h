#pragma once
#include "Chat.h"

class SingleChat : public Chat {
private:
	User users[2];

public:

	Chat* clone() const override;
	void printStats(const String& name) override;
	void viewChat() override;
	void saveToFile(std::fstream& os) override;
	void readFromFile(std::fstream& is);
	void viewActiveChat(const String& username) override;
};