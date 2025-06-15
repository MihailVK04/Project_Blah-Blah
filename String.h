#pragma once
#include <iostream>
#include <fstream>
#include "Util.h"

//static unsigned int nextRoundPowerOfTwo(unsigned int num) {
//	unsigned int i = 1;
//	while (num >= i) {
//		i = i << 1;
//	}
//	return i;
//}

class String {
private:
	size_t size;
	size_t allocDataSize;
	char* data;

	explicit String(size_t stringLenght);
	void resize(unsigned int newAllocDataSize);
	void free();
	void copyFrom(const String& other);
	void moveFrom(String&& other);

public:
	String();
	String(const char* _data);
	String(const String& other);
	String(String&& other) noexcept;
	String& operator=(const String& other);
	String& operator=(String&& other) noexcept;
	~String();

	void setData(const char* buff);
	void setResize(unsigned int newAllocDataSize);
	void setSize(size_t newSize);
	size_t getCapacity() const;
	size_t getSize() const;
	const char* c_str() const;
	String operator+=(const String& other);
	char& operator[](size_t index);
	const char& operator[](size_t index) const;
	void saveToFile(std::fstream& os);
	void readFromFile(std::fstream& is);
	friend std::ostream& operator<<(std::ostream& os, const String& obj);
	friend std::istream& operator>>(std::istream& is, String& ref);
	friend String operator+(const String& lhs, const String& rhs);
};

bool operator==(const String& lhs, const String& rhs);
bool operator!=(const String& lhs, const String& rhs);
bool operator<(const String& lhs, const String& rhs);
bool operator<=(const String& lhs, const String& rhs);
bool operator>(const String& lhs, const String& rhs);
bool operator>=(const String& lhs, const String& rhs);