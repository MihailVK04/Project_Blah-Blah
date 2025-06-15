#pragma once

static unsigned int nextRoundPowerOfTwo(unsigned int num) {
	unsigned int i = 1;
	while (num >= i) {
		i = i << 1;
	}
	return i;
}

static int numbersCount(int data) {
	int i = 0;
	int size = 1;
	while (data >= size) {
		size *= 10;
		i++;
	}
	return i;
}

static int tenToThePowerOf(int n) {
	int num = 1;
	for (int i = 0; i < n; i++) {
		num *= 10;
	}
	return num;
}

static const char* convertTochar(int data) {
	int buff;
	int i = numbersCount(data);
	int size = tenToThePowerOf(i-1);
	char* result = new char[i];
	for (int j = 0; j < i; j++) {
		buff = data / size;
		data = data % size;
		size /= 10;
		result[j] = buff + '0';
	}
	return result;
}

static const char* copyFromChar(const char* data, int index) {
	char* newdata = new char[index];
	for (int i = 0; i < index; i++) {
		newdata[i] = data[i];
	}
	return newdata;
}