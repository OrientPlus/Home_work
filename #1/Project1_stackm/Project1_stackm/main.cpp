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

	stackm<string> st1, st2, st3, st4, st5;
	string box1[] = { "one", "two", "three", "four", "five"},
		box2[] = { "ten", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"},
		box3[] = { "ten", "one", "two", "one", "four", "five", "one", "seven", "eight", "nine",
		"ten", "one", "one", "three", "one", "five", "six", "one", "eight", "nine" };
	
	st1.fill(STR_COUNT, STR_SIZE);
	st2.fill(STR_COUNT, STR_SIZE);

	if (st1.overlap(st2 ))
		cout << "\n#3 The stacks are completely the same!" << endl;
	else
		cout << "\n#3 The stacks don't match!" << endl;

	st3.fill(box1, 5);
	st4.fill(box2, 10);
	st5.fill(box3, 20);
	

	if (st3.subset(st4))
		cout << "\n\n#4 The stack is a subset of the stack passed as a parameter." << endl;
	else
		cout << "\n\n#4 The stack is not a subset." << endl;


	cout << endl << "#5 BEFORE DELETE:";
	st5.output();

	cout << "\n#5 " << st5.Del("one") << " elements find and delete." << endl;
	st5.output();

	cout << "\n";
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
