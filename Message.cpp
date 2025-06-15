#include "Message.h"

Message::Message() {
	sender = "Unknown";
	time = std::time(nullptr);
}

Message::Message(const Sentences& _message, const String& _sender) : message(_message), sender(_sender) {
	time = std::time(nullptr);
}

String Message::getSender() const
{
	return sender;
}

Sentences Message::getMessage() const
{
	return message;
}

time_t Message::getTime() const
{
	return time;
}

void Message::saveToFile(std::fstream& os) {
	os.write((const char*)&time, sizeof(time_t));
	this->sender.saveToFile(os);
	this->message.saveToFile(os);
}

void Message::readFromFile(std::fstream& is)
{
	is.read((char*)&time, sizeof(time_t));
	this->sender.readFromFile(is);
	this->message.readFromFile(is);
}

std::ostream& operator<<(std::ostream& os, Message& ref)
{
	os << "--------" << '\n';
	os << ref.sender << '\n';
	os << ref.message << '\n';
	os << "Sent: " << std::ctime(&ref.time) << '\n';
	return os;
}
