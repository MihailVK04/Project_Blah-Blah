#include "Strategy.h"
#include "Util.h"

Context::Context(UniquePtr<StrategyRW>&& strategy) :strategy(std::move(strategy)) {}

void Context::setStrategy(UniquePtr<StrategyRW>&& strategy)
{
	this->strategy = std::move(strategy);
}

void Context::readWriteInBinary(Container<Chat>& chats, Container<UserInfo>& users, int* chatIds, int& size)
{
	String extension(".dat");
	if (strategy->isRead()) {
		std::fstream stream("chatIds.dat", std::ios::in|std::ios::binary);
		if (!stream.is_open()) {
			std::cout << "Error while opennig file!" << '\n';
			return;
		}
		strategy->readWriteIds(chatIds, size, stream);
		stream.close();
		std::fstream ustream("users.dat", std::ios::in | std::ios::binary);
		if (!ustream.is_open()) {
			std::cout << "Error while opennig file!" << '\n';
			return;
		}
		strategy->readWriteUsers(users, ustream);
		ustream.close();
		for (int i = 0; i < size; i++) {
			String name("chats_");
			name += convertTochar(chatIds[i]);
			name += extension;
			std::fstream cstream(name.c_str(), std::ios::in | std::ios::binary);
			if (!cstream.is_open()) {
				std::cout << "Error while opennig file!" << '\n';
				return;
			}
			char type;
			cstream.read((char*)&type, sizeof(char));
			Chat* buff = new Chat();
			strategy->readWriteChats(type, buff, cstream);
			chats.addElement(*buff);
			cstream.close();
			delete buff;
		}

	}
	else {
		std::fstream stream("chatIds.dat", std::ios::out | std::ios::binary);
		if (!stream.is_open()) {
			std::cout << "Error while opennig file!" << '\n';
			return;
		}
		strategy->readWriteIds(chatIds, size, stream);
		stream.close();
		std::fstream ustream("users.dat", std::ios::out | std::ios::binary);
		if (!ustream.is_open()) {
			std::cout << "Error while opennig file!" << '\n';
			return;
		}
		strategy->readWriteUsers(users, ustream);
		ustream.close();
		for (int i = 0; i < size; i++) {
			String name("chats_");
			name += String(convertTochar(chatIds[i]));
			name += extension;
			std::fstream cstream(name.c_str(), std::ios::out | std::ios::binary);
			if (!cstream.is_open()) {
				std::cout << "Error while opennig file!" << '\n';
				return;
			}
			char type = 'w';
			strategy->readWriteChats(type, chats[i], cstream);
			cstream.close();
		}
	}
}

void Context::readWriteInText(Container<Chat>& chats, Container<UserInfo>& users, int* chatIds, int& size)
{
	String extension(".txt");
	if (strategy->isRead()) {
		std::fstream stream("chatIds.txt", std::ios::in | std::ios::binary);
		if (!stream.is_open()) {
			std::cout << "Error while opennig file!" << '\n';
			return;
		}
		strategy->readWriteIds(chatIds, size, stream);
		stream.close();
		std::fstream ustream("users.txt", std::ios::in | std::ios::binary);
		if (!ustream.is_open()) {
			std::cout << "Error while opennig file!" << '\n';
			return;
		}
		strategy->readWriteUsers(users, ustream);
		ustream.close();
		for (int i = 0; i < size; i++) {
			String name("chats_");
			name += String(convertTochar(chatIds[i]));
			name += extension;
			std::fstream cstream(name.c_str(), std::ios::in | std::ios::binary);
			if (!cstream.is_open()) {
				std::cout << "Error while opennig file!" << '\n';
				return;
			}
			char type;
			cstream.read((char*)&type, sizeof(char));
			Chat* buff = new Chat;
			strategy->readWriteChats(type, buff, cstream);
			chats.addElement(*buff);
			cstream.close();
			delete buff;
		}

	}
	else {
		std::fstream stream("chatIds.txt", std::ios::out | std::ios::binary);
		if (!stream.is_open()) {
			std::cout << "Error while opennig file!" << '\n';
			return;
		}
		strategy->readWriteIds(chatIds, size, stream);
		stream.close();
		std::fstream ustream("users.txt", std::ios::out | std::ios::binary);
		if (!ustream.is_open()) {
			std::cout << "Error while opennig file!" << '\n';
			return;
		}
		strategy->readWriteUsers(users, ustream);
		ustream.close();
		for (int i = 0; i < size; i++) {
			String name("chats_");
			name += String(convertTochar(chatIds[i]));
			name += extension;
			std::fstream cstream(name.c_str(), std::ios::out | std::ios::binary);
			if (!cstream.is_open()) {
				std::cout << "Error while opennig file!" << '\n';
				return;
			}
			char type = 'w';
			strategy->readWriteChats(type, chats[i], cstream);
			cstream.close();
		}
	}
}

void ReadStrategy::readWriteChats(char type,Chat* chat, std::fstream& stream) const
{
	if (type == 'g') {
		GroupChat Newchat;
		Newchat.readFromFile(stream);
		chat = Newchat.clone();;
	}
	else if (type == 's') {
		SingleChat Newchat;
		Newchat.readFromFile(stream);
		chat = Newchat.clone();
	}
	chat = Chat().clone();
}

void ReadStrategy::readWriteIds(int* other,int& size, std::fstream& stream) const
{
	int newSize = 0;
	stream.read((char*)&newSize, sizeof(int));
	other = new int[newSize * 2];
	for (int i = 0; i < newSize; i++) {
		stream.read((char*)&other[i], sizeof(int));
	}
	size = newSize;
}

void ReadStrategy::readWriteUsers(Container<UserInfo>& other, std::fstream& stream) const
{
	UserInfo buff;
	int size = 0;
	stream.read((char*)&size, sizeof(int));
	for (int i = 0; i < size; i++) {
		buff.readFromFile(stream);
		other.addElement(buff);
	}
}

bool ReadStrategy::isRead() const
{
	return true;
}

void WriteStrategy::readWriteChats(char type, Chat* chat, std::fstream& stream) const
{
	chat->saveToFile(stream);
}

void WriteStrategy::readWriteIds(int* other,int& size, std::fstream& stream) const
{
	stream.write((const char*)&size, sizeof(int));
	for (int i = 0; i < size; i++) {
		stream.write((const char*)&other[i], sizeof(int));
	}
}

void WriteStrategy::readWriteUsers(Container<UserInfo>& other, std::fstream& stream) const
{
	size_t size = other.getSize();
	stream.write((const char*)&size, sizeof(size_t));
	for (int i = 0; i < size; i++) {
		other[size]->saveToFile(stream);
	}
}

bool WriteStrategy::isRead() const
{
	return false;
}

//const char* convertTochar(int data) {
//	int buff;
//	int i = 0;
//	int size = 1;
//	while (data >= size) {
//		size *= 10;
//		i++;
//	}
//	size / 10;
//	char* result = new char[i];
//	for (int j = 0; j < i; j++) {
//		buff = data / size;
//		data = data % size;
//		size / 10;
//		result[j] = buff + '0';
//	}
//	return result;
//}
