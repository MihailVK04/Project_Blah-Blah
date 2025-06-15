#pragma once
#include "String.h"
#include "Sentences.h"
#include <ctime>
#pragma warning (disable:4996)

class Message {
private:
	String sender;
	Sentences message;
	time_t time;

public:
	Message();
	Message(const Sentences& _message, const String& _sender);
	String getSender() const;
	Sentences getMessage() const;
	time_t getTime() const;
	friend std::ostream& operator<<(std::ostream& os, Message& ref);
	void saveToFile(std::fstream& os);
	void readFromFile(std::fstream& is);
};