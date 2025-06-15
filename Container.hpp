#pragma once
#include <iostream>

template<class T>
class Container {
private:
	T** elements;
	size_t size;
	size_t cap;

	void copyFrom(const Container<T>& other);
	void moveFrom(Container<T>&& other);
	void free();
	void resize();

public:
	Container();
	Container(const Container<T>& other);
	Container(Container<T>&& other) noexcept;
	Container<T>& operator=(const Container<T>& other);
	Container<T>& operator=(Container<T>&& other) noexcept;
	~Container();

	void addElement(const T& element);
	void deleteElement(size_t place);
	T* operator[](size_t index);
	const T* operator[](size_t index) const;
	size_t getSize() const;
};

template<class T>
void Container<T>::copyFrom(const Container<T>& other) {
	size = other.size;
	cap = other.cap;
	elements = new T* [cap];
	for (int i = 0; i < size; i++) {
		elements[i] = new T(*other.elements[i]);
	}
}

template<class T>
void Container<T>::moveFrom(Container<T>&& other) {
	size = other.size;
	cap = other.cap;
	elements = other.elements;
	other.size = other.cap = 0;
	other.elements = nullptr;
}

template<class T>
void Container<T>::free() {
	for (int i = 0; i < cap; i++) {
		delete[] elements[i];
	}
	delete[] elements;
}

template<class T>
void Container<T>::resize() {
	if (elements == nullptr) {
		cap = 1;
		elements = new T* [cap];
	}

	if (cap == size) {
		cap = cap * 2;
		T** newData = new T* [cap];
		for (int i = 0; i < size; i++) {
			newData[i] = new T(*elements[i]);
		}
		free();
		elements = newData;
		newData = nullptr;
	}
}

template<class T>
Container<T>::Container() {
	cap = size = 0;
	elements = nullptr;
}

template<class T>
Container<T>::Container(const Container<T>& other) {
	copyFrom(other);
}

template<class T>
Container<T>::Container(Container<T>&& other) noexcept{
	moveFrom(std::move(other));
}

template<class T>
Container<T>& Container<T>::operator=(const Container<T>& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

template<class T>
Container<T>& Container<T>::operator=(Container<T>&& other) noexcept{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<class T>
Container<T>::~Container() {
	free();
}

template<class T>
void Container<T>::addElement(const T& element) {
	resize();
	T* newElement = new T(element);
	elements[size] = newElement;
	size++;
}

template<class T>
void Container<T>::deleteElement(size_t place) {
	if (place >= size) {
		return;
	}

	bool found = false;
	for (int i = 0; i < size - 1; i++) {
		if (i == place) {
			delete[] elements[i];
			found = true;
		}
		if (found) {
			elements[i] = elements[i + 1];
		}
	}
	delete[] elements[size - 1];
	elements[size - 1] = nullptr;
	size--;
}

template<class T>
T* Container<T>::operator[](size_t index) {
	if (index >= size) {
		return nullptr;
	}
	else {
		return elements[index];
	}
}

template<class T>
const T* Container<T>::operator[](size_t index) const {
	if (index >= size) {
		return nullptr;
	}
	else {
		return elements[index];
	}
}

template<class T>
size_t Container<T>::getSize() const {
	return size;
}