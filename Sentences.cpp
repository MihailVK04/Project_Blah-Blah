#include "Sentences.h"

std::ostream& operator<<(std::ostream& os, Sentences& object)
{
	os << object.words;
	return os;
}

std::istream& operator>>(std::istream& is, Sentences& object)
{
	object.words = String();
	while (true) {
		char buff[1024];
		is >> buff;
		String stringBuff;
		size_t buffStringSize = std::strlen(buff);
		if (buffStringSize > stringBuff.getCapacity()) {
			stringBuff.setResize(nextRoundPowerOfTwo(buffStringSize + 1));
		}
		stringBuff.setSize(buffStringSize);
		stringBuff.setData(buff);
		object.words += stringBuff;
		object.words += String(" ");
		if (is.peek() == '\n') {
			is.seekg(1, std::ios::cur);
			break;
		}
	}
	return is;
} 

String Sentences::getWords() const
{
	return words;
}

void Sentences::saveToFile(std::ofstream& os) {
	words.saveToFile(os);
}

void Sentences::readFromFile(std::ifstream& is) {
	words.readFromFile(is);
}