#include <iostream>
#include <array>
#include <random>
#include <stack>

#include "stack.h"


void gen_str(string *box, const int len, const int amount_str);

string get_rand_str(size_t str_len);

void My_stack();
void Def_stack();

int main()
{
	
	My_stack();
	Def_stack();

	stackm<string> st1, st2, st1_1, st2_2;
	string box1[] = { "onee", "two", "three", "four", "five"},
		box2[] = { "ten", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	
	st1.fill(STR_COUNT, STR_SIZE);
	st2.fill(STR_COUNT, STR_SIZE);

	if (st1.overlap(st2 ))
		cout << "\n#3 The stacks are completely the same!" << endl;
	else
		cout << "\n#3 The stacks don't match!" << endl;

	st1_1.fill(box1, 5);
	st2_2.fill(box2, 10);

	if (st1_1.subset(st2_2))
		cout << "\n\n#4 The stack is a subset of the stack passed as a parameter." << endl;
	else
		cout << "\n\n#4 The stack is not a subset." << endl;

	system("pause");
	return 0;
} 

void Def_stack()
{
	stack<string> st;
	string* box = new string[STR_COUNT], str;

	gen_str(box, STR_COUNT, STR_SIZE);

	auto start = high_resolution_clock::now();

	cout << "\n######################## DEFAULT STACK ######################" << endl;
	for (int i = 0; i < STR_COUNT; i++)
	{
		st.push(box[i]);
		cout << st.top() << endl;
	}

	cout << "\n---------------Strings are temporary variables-------------" << endl;
	for (int i = 0; i < STR_COUNT; i++)
	{
		str = get_rand_str(STR_SIZE);
		st.push(str);
		cout << st.top() << endl;
	}
	
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "\n\n### TIME EXECUTABLE DEFAULT STACK: " << duration << " microseconds" << endl;

	cout << "Stack size: " << st.size() << endl;
	delete[] box;
}

void My_stack()
{
	stackm<string> my_stack;

	cout << "\n########################### MY STACK ###########################" << endl;

	string* box = new string[STR_COUNT];
	gen_str(box, STR_COUNT, STR_SIZE);
	my_stack.fill(box, STR_COUNT);
	for (int i = 0; i < STR_COUNT; i++)
	{
		cout << my_stack.top(i) << endl;
	}

	cout << "\n---------------Strings are temporary variables-------------" << endl;

	my_stack.fill(STR_COUNT, STR_SIZE);
	for (int i = 0; i < STR_COUNT; i++)
	{
		cout << my_stack.top(i) << endl;
	}

	cout << "\n\n### TIME EXECUTABLE MY_STACK: " << my_stack.exec_time << " microseconds" << endl;
	cout << "Stack size: " << my_stack.size() << endl;
	delete[] box;
}

void gen_str(string* box, const int amount_str, const int len)
{
	string alph = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ#";
	int pos;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(0, 53);

	for (int i = 0; i < amount_str; i++)
	{
		for (int j = 0; j < len; j++)
		{
			pos = dist(gen);
			box[i] += alph[pos];
		}
	}
}

string get_rand_str(size_t str_len)
{
	string alph = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ#", result;
	int pos;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(0, 53);

	for (int i = 0; i < str_len; i++)
	{
		pos = dist(gen);
		result += alph[pos];
	}
	return result;
}
