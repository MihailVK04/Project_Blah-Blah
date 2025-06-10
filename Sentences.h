#pragma once
#include "String.h"

class Sentences {
private:
	String words;
public:
	String getWords() const;
	void saveToFile(std::ofstream& os);
	void readFromFile(std::ifstream& is);
	friend std::ostream& operator<<(std::ostream& os, Sentences& object);
	friend std::istream& operator>>(std::istream& is, Sentences& object);
};