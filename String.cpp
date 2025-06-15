#include "String.h"
#include <cstring>
#include <algorithm>
#pragma warning (disable:4996)

//static unsigned int nextRoundPowerOfTwo(unsigned int num) {
//	unsigned int i = 1;
//	while (num >= i) {
//		i = i << 1;
//	}
//	return i;
//}

String::String(size_t stringLenght)
{
	allocDataSize = nextRoundPowerOfTwo(stringLenght+1);
	data = new char[allocDataSize+1];
	size = 0;
	data[size] = '\0';
}

void String::resize(unsigned int newAllocDataSize)
{
	char* newData = new char[newAllocDataSize+1];
	std::strcpy(newData, data);
	delete[] data;
	data = newData;
	allocDataSize = newAllocDataSize;
}

void String::free()
{
	delete[] data;
}

void String::copyFrom(const String& other)
{
	allocDataSize = other.allocDataSize;
	data = new char[allocDataSize];
	std::strcpy(data, other.data);
	size = other.size;
}

void String::moveFrom(String&& other)
{
	data = other.data;
	other.data = nullptr;
	size = other.size;
	other.size = 0;
	allocDataSize = other.allocDataSize;
	other.allocDataSize = 0;
}

String::String():String("") {}

String::String(const char* _data)
{
	size = std::strlen(_data);
	allocDataSize = nextRoundPowerOfTwo(size+1);
	data = new char[allocDataSize];
	strcpy(data, _data);
	data[size] = '\0';
}

String::String(const String& other)
{
	copyFrom(other);
}

String::String(String&& other) noexcept
{
	moveFrom(std::move(other));
}

String& String::operator=(const String& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

String& String::operator=(String&& other) noexcept
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

String::~String()
{
	free();
}

void String::setData(const char* buff)
{
	strcpy(data, buff);
}

void String::setResize(unsigned int newAllocDataSize)
{
	if(newAllocDataSize > allocDataSize){
		resize(newAllocDataSize);
	}
}

void String::setSize(size_t newSize)
{
	size = newSize;
}

size_t String::getCapacity() const
{
	return allocDataSize-1;
}

size_t String::getSize() const
{
	return size;
}

const char* String::c_str() const
{
	return data;
}

String String::operator+=(const String& other)
{
	if (getSize() + other.getSize() + 1 > allocDataSize) {
		resize(nextRoundPowerOfTwo(getSize() + other.getSize() + 1));
	}

	std::strncat(data, other.data, other.getSize());
	size = getSize() + other.getSize();
	return *this;
}

char& String::operator[](size_t index)
{
	return data[index];
}

const char& String::operator[](size_t index) const
{
	return data[index];
}

void String::saveToFile(std::fstream& os)
{
	os.write((const char*)&size, sizeof(size_t));
	os.write((const char*)data, size * sizeof(char));
}

void String::readFromFile(std::fstream& is)
{
	is.read((char*)&size, sizeof(size_t));
	allocDataSize = size + 1;
	data = new char[allocDataSize];
	is.read(data, sizeof(char) * size);
	data[size] = '\0';
}

std::ostream& operator<<(std::ostream& os, const String& obj)
{
	return os<<obj.data;
}

std::istream& operator>>(std::istream& is, String& ref)
{
	char buff[1024];
	is >> buff;
	size_t buffStringSize = std::strlen(buff);
	if (buffStringSize > ref.getCapacity()) {
		ref.resize(nextRoundPowerOfTwo(buffStringSize + 1));
	}
	strcpy(ref.data, buff);
	ref.size = buffStringSize;
	if (is.peek() == '\n') {
		is.seekg(1, std::ios::cur);
	}
	return is;
}

String operator+(const String& lhs, const String& rhs)
{
	String result(lhs.getSize() + rhs.getSize());
	result += lhs;
	result += rhs;
	return result;
}

bool operator==(const String& lhs, const String& rhs)
{
	return std::strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const String& lhs, const String& rhs)
{
	return std::strcmp(lhs.c_str(), rhs.c_str()) != 0;
}

bool operator<(const String& lhs, const String& rhs)
{
	return std::strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const String& lhs, const String& rhs)
{
	return std::strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}

bool operator>(const String& lhs, const String& rhs)
{
	return std::strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator>=(const String& lhs, const String& rhs)
{
	return std::strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}
