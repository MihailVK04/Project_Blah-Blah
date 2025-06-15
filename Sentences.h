#pragma once
#include "String.h"

class Sentences {
private:
	String words;
public:
	String getWords() const;
	void saveToFile(std::fstream& os);
	void readFromFile(std::fstream& is);
	friend std::ostream& operator<<(std::ostream& os, Sentences& object);
	friend std::istream& operator>>(std::istream& is, Sentences& object);
};