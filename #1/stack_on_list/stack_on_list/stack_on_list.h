#pragma once

#include <iostream>
#include <list>
#include <chrono>

#include <stack>
#include <random>

#define STR_SIZE 10
#define STR_COUNT 5

using namespace std;
using namespace std::chrono;

template <typename T>
struct Node
{
	T* elem;
	Node<T>* next;
};

template <typename T>
class stack_list
{
	Node<T>* pTop;

	size_t Size;
	void resize_if_need();
public:
	stack_list() { pTop = nullptr; }
	~stack_list();
	void push(const T& elem);
	void push(T&& elem);
	int pop();

	int overlap(stack_list& st_two);

	//Checks whether the stack is a subset of the stack passed as a function parameter
	int subset(stack_list& st_two);

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
inline void stack_list<T>::resize_if_need()
{
}

template<typename T>
inline stack_list<T>::stack_list()
{
	
}

template<typename T>
inline stack_list<T>::~stack_list()
{
}

template<typename T>
inline void stack_list<T>::push(const T& elem)
{

}

template<typename T>
inline void stack_list<T>::push(T&& elem)
{
}

template<typename T>
inline int stack_list<T>::pop()
{
}

template<typename T>
inline int stack_list<T>::overlap(stack_list& st_two)
{
	return 0;
}

template<typename T>
inline int stack_list<T>::subset(stack_list& st_two)
{
	return 0;
}

template<typename T>
inline int stack_list<T>::Del(const T& elem)
{
	return 0;
}

template<typename T>
inline const T& stack_list<T>::top() const
{
	
}

template<typename T>
inline T& stack_list<T>::top()
{
	
}

template<typename T>
inline T& stack_list<T>::top(int N)
{
	
}

template<typename T>
inline size_t stack_list<T>::size() const
{
}

template<typename T>
inline void stack_list<T>::output()
{
}

template<typename T>
inline void stack_list<T>::fill(const T* box, const int size_of_container)
{
}

template<typename T>
inline void stack_list<T>::fill(const int random_amount, const int str_len)
{
}
