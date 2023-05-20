/*

#include "Stack.h"

template<typename T>
size_t Stack<T>::size()
{
	return this->array_size;
}

template<typename T>
Stack<T>::Stack()
{
	this->array = new T[INIT_CAPACITY];
	this->capacity = INIT_CAPACITY;
	this->array_size = 0;
}

template<typename T>
Stack<T>::~Stack()
{
	delete this->array;
}


template<typename T>
void Stack<T>::push(T value)
{
	if (this->array_size >= this->capacity) {  // realloc

		T* temp = this->array;

		this->capacity <<= 1;
		this->array = new T[this->capacity];

		for (size_t i = 0; i < this->size; i++)
			this->array[i] = this->temp[i];
		
		delete temp;
	}

	this->array[this->array_size++] = value;
}

template<typename T>
T Stack<T>::top(void)
{
	if (this->array_size == 0) throw throw "ERROR::Stack [ Array Empty (top) ]";

	return this->array[this->array_size];
}

template<typename T>
T Stack<T>::pop(void)
{
	if (this->array_size == 0) throw throw "ERROR::Stack [ Array Empty (pop) ]";

	return this->array[--this->array_size];
}

template<typename T>
bool Stack<T>::empty()
{
	return this->array_size == 0;
}

template<typename T>
void Stack<T>::clear()
{
	return this->array_size = 0;
}

template<typename T>
void Stack<T>::copyToArray(T *arr)
{
	for (size_t i = 0; i < this->array_size; i++) {
		arr[i] = this->array[i];
	}
}

*/