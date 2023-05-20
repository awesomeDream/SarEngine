#pragma once

#define INIT_CAPACITY 16

template<typename T>
class Stack
{
private:
	T* array;
	size_t capacity;
	size_t array_size;
	
public:
	size_t size() { return this->array_size; }

public:
	Stack()
	{
		this->array = new T[INIT_CAPACITY];
		this->capacity = INIT_CAPACITY;
		this->array_size = 0;
	}

	~Stack()
	{
		delete this->array;
	}

public:
	void push(T value)
	{
		if (this->array_size >= this->capacity) {  // realloc

			T* temp = this->array;

			this->capacity <<= 1;
			this->array = new T[this->capacity];

			for (size_t i = 0; i < this->array_size; i++)
				this->array[i] = temp[i];

			delete temp;
		}

		this->array[this->array_size++] = value;
	}
	T top(void)
	{
		if (this->array_size == 0) throw throw "ERROR::Stack [ Array Empty (top) ]";

		return this->array[this->array_size];
	}
	T pop(void)
	{
		if (this->array_size == 0) throw throw "ERROR::Stack [ Array Empty (pop) ]";

		return this->array[--this->array_size];
	}

public:
	bool empty() { return this->array_size == 0; }
	void clear() { return this->array_size = 0; }

public:
	void copyToArray(T *arr)
	{
		for (size_t i = 0; i < this->array_size; i++) {
			arr[i] = this->array[i];
		}
	}
};

typedef Stack<int> StackInt;
typedef Stack<float> StackFloat;