#pragma once

#include <iostream>
#include <iterator>
#include <random>
#include <chrono>

#define STR_SIZE 1'000
#define STR_COUNT 1'000'000

using namespace std;
using namespace std::chrono;


template <typename T>
class stack_array
{
	T* data;
	size_t count, capacity, fill_count;

	void resize_if_needed();
public:
	stack_array(size_t capacity = 2);
	~stack_array();
	void push(const T& elem);
	void push(T&& elem);
	void pop();

	int overlap(stack_array& st_two);

	//Checks whether the stack is a subset of the stack passed as a function parameter
	int subset(stack_array& st_two);

	//Deletes all occurrences of an element in the stack
	int Del(const T& elem);

	const T& top() const;
	T& top();
	T& top(int N);
	size_t size() const;

	void output();

	//Fills the stack with the contents of the container that is passed as an argument
	void fill(const T* box, const int size_of_container);

	//Fills the stack with randomly generated strings
	void fill(const int random_amount, const int str_len);

};

template<typename T>
inline void stack_array<T>::resize_if_needed()
{
	if (this->fill_count + this->count >= this->capacity)
	{
		size_t new_capacity = this->fill_count + this->count + 100;
		T* new_data = new T[new_capacity];
		for (size_t i = 0; i < this->capacity; ++i)
		{
			new_data[i] = std::move(this->data[i]);
		}
		delete[] this->data;
		this->capacity = new_capacity;
		this->data = new_data;
	}
	/*if (this->count == this->capacity)
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
	}*/
}

template<typename T>
inline stack_array<T>::stack_array(size_t capacity)
{
	this->fill_count = 0;
	this->data = new T[capacity];
	this->capacity = capacity;
	this->count = 0;
}

template<typename T>
inline stack_array<T>::~stack_array()
{
	delete[] this->data;
}

template<typename T>
inline void stack_array<T>::push(const T& elem)
{
	resize_if_needed();
	this->data[count++] = elem;
}

template<typename T>
inline void stack_array<T>::push(T&& elem)
{
	resize_if_needed();
	this->data[count++] = elem;
}

template<typename T>
inline void stack_array<T>::pop()
{
	if (this->count > 0)
		--this->count;
}

template<typename T>
inline int stack_array<T>::overlap(stack_array& st_two)
{
	T temp;
	if (this->size() != st_two.size())
		return 0;
	
	for (int i=0; i<this->size(); i++)
	{
		if (this->top(i) == st_two.top(i))
			continue;
		else
			return 0;
	}
	return 1;
}

template<typename T>
inline int stack_array<T>::subset(stack_array& st_two)
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
inline int stack_array<T>::Del(const T& elem)
{
	// 1 - #[del] - 3 - 4 - 5 - 6
	//==>       1 - 3 - 4 - 5 - 6 - 6
	
	int delete_count = 0;
	for (int i = this->size() - 1; i >= 0; i--)
	{
		if (elem == this->top(i))
		{
			for (int j = i; j < this->size()-1; j++)
			{
				this->data[j] = this->data[j + 1];
			}
			delete_count++;
			this->count--;
		}
		else
			continue;
	}
	return delete_count;
}

template<typename T>
inline const T& stack_array<T>::top() const
{
	return this->data[this->count - 1];
}

template<typename T>
inline T& stack_array<T>::top()
{
	return this->data[this->count - 1];
}

template<typename T>
inline T& stack_array<T>::top(int N)
{
	if (N < 0)
	{
		cout << endl << "ERROR! Stack bottom reached earlier than expected!\n";
		system("pause");
		exit(-1);
	}
	else if (N > this->count - 1)
	{
		cout << endl << "ERROR! There is no element with such an index!\n";
		system("pause");
		exit(-1);
	}

	return this->data[N];
}

template<typename T>
inline size_t stack_array<T>::size() const
{
	return this->count;
}

template<typename T>
inline void stack_array<T>::output()
{
	for (int i = 0; i < this->size(); i++)
	{
		if (i % 10 == 0)
			cout << endl;
		cout << "  " << this->data[i];
	}
}

template<typename T>
inline void stack_array<T>::fill(const int rand_amount, const int str_len)
{
	int pos = 0;
	fill_count = rand_amount;
	resize_if_needed();
	string temp, alph = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ#";
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(0, 53);
	
	temp.reserve(STR_SIZE);
	for (int i = 0; i < rand_amount; i++)
	{
		temp.clear();
		for (int j = 0; j < str_len; j++)
		{
			pos = dist(gen);
			temp += alph[pos];
		}
		this->data[count++] = temp;
	}
}

template<typename T>
inline void stack_array<T>::fill(const T* box, const int size_of_box)
{
	fill_count = size_of_box;
	resize_if_needed();
	for (int i=0; i<size_of_box; i++)
	{
		this->data[count++] = box[i];
	}
} 
