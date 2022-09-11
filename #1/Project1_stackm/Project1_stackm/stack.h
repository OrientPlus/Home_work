#pragma once

#include <iostream>
#include <iterator>
#include <random>
#include <chrono>

#define STR_SIZE 5
#define STR_COUNT 5

using namespace std;
using namespace std::chrono;


template <typename T>
class stackm
{
	T* data;
	size_t count, capacity, fill_count;

	void resize_if_needed();
public:
	stackm(size_t capacity = 1'000);
	~stackm();
	void push(const T& elem);
	void push(T&& elem);
	void pop();

	int overlap(stackm& st_two);

	//Checks whether the stack is a subset of the stack passed as a function parameter
	int subset(stackm& st_two);

	const T& top() const;
	T& top();
	T& top(int N);
	size_t size() const;
	chrono::microseconds exec_time;

	//Fills the stack with the contents of the container that is passed as an argument
	void fill(const T* box, const int size_of_container);

	//Fills the stack with randomly generated strings
	void fill(const int random_amount, const int str_len);

};

template<typename T>
inline void stackm<T>::resize_if_needed()
{
	if (this->fill_count + this->count >= this->capacity)
	{
		size_t new_capacity = this->fill_count + this->count + 10;
		T* new_data = new T[new_capacity];
		for (size_t i = 0; i < this->capacity; ++i)
		{
			new_data[i] = std::move(this->data[i]);
		}
		delete[] this->data;
		this->capacity = new_capacity;
		this->data = new_data;
	}
	if (this->count == this->capacity)
	{
		size_t new_capacity = capacity * 2;
		T* new_data = new T[new_capacity];
		for (size_t i = 0; i < this->capacity; ++i)
		{
			new_data[i] = std::move(this->data[i]);
		}
		delete[] this->data;
		this->capacity = new_capacity;
		this->data = new_data;
	}
}

template<typename T>
inline stackm<T>::stackm(size_t capacity)
{
	this->data = new T[capacity];
	this->capacity = capacity;
	this->count = 0;
}

template<typename T>
inline stackm<T>::~stackm()
{
	delete[] this->data;
}

template<typename T>
inline void stackm<T>::push(const T& elem)
{
	resize_if_needed();
	this->data[count++] = elem;
}

template<typename T>
inline void stackm<T>::push(T&& elem)
{
	cout << "Stole the pointer" <<endl;
	resize_if_needed();
	this->data[count++] = elem;
}

template<typename T>
inline void stackm<T>::pop()
{
	if (this->count > 0)
		--this->count;
}

template<typename T>
inline int stackm<T>::overlap(stackm& st_two)
{
	T temp;
	int iterator = 0;
	if (this->size() != st_two.size())
		return 0;
	
	for (int i=0; i<STR_COUNT; i++)
	{
		iterator--;
		if (iterator == -1)
			break;
		temp = this->top(iterator);
		if (this->top(iterator) == st_two.top(iterator))
			continue;
		else
			return 0;
	}
	return 1;
}

template<typename T>
inline int stackm<T>::subset(stackm& st_two)
{
	string s1, s2;
	if (this->size() > st_two.size())
		return 0;
	int iterator;
	for (int j = 0; j<st_two.size()/2; j++)
	{
		iterator = st_two.size() - j;
		for (int i = this->size() - 1; i >= 0; i--)
		{
			iterator--;
			/*s1 = this->top(i);
			s2 = st_two.top(i);*/
			if (this->top(i) != st_two.top(iterator))
				break;
			if (i == 0)
				return 1;
		}
	}
	return 0;
}

template<typename T>
inline const T& stackm<T>::top() const
{
	return this->data[this->count - 1];
}

template<typename T>
inline T& stackm<T>::top()
{
	return this->data[this->count - 1];
}

template<typename T>
inline T& stackm<T>::top(int N)
{
	int temp_count = this->count;
	for (int i = 0; i < N; i++)
	{
		if (temp_count > 0)
		{
			temp_count--;
		}
		else
		{
			cout << endl << "ERROR! Stack bottom reached earlier than expected!";
			system("pause");
			exit(-1);
		}
	}

	return this->data[temp_count - 1];
}

template<typename T>
inline size_t stackm<T>::size() const
{
	return this->count;
}


template<typename T>
inline void stackm<T>::fill(const int rand_amount, const int str_len) 
{
	auto start = chrono::high_resolution_clock::now();

	int pos = 0;
	fill_count = rand_amount;
	resize_if_needed();
	string temp, alph = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ#";
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(0, 53);
	
	for (int i = 0; i < rand_amount; i++)
	{
		temp.clear();
		for (int j = 0; j < str_len; j++)
		{
			pos = dist(gen);
			temp+= alph[pos];
		}
		this->data[count++] = temp;
	}

	auto stop = chrono::high_resolution_clock::now();
	exec_time = duration_cast<microseconds>(stop - start);
}

template<typename T>
inline void stackm<T>::fill(const T* box, const int size_of_mem)
{
	auto start = chrono::high_resolution_clock::now();

	fill_count = size_of_mem;
	resize_if_needed();
	for (int i=0; i<size_of_mem; i++)
	{
		this->data[count++] = box[i];
	}

	auto stop = chrono::high_resolution_clock::now();
	exec_time = duration_cast<microseconds>(stop - start);
} 

