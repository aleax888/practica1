#include "pch.h"
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <ctime>
using namespace std;



struct functor1
{
	inline bool c(int a, int b) { return a <= b; }
};

struct functor2
{
	inline bool c(int a, int b) { return a >= b; }
};


template <typename T>
struct priority_queue
{
	vector<pair<string, int>> vec;
	T fo;

	void print()
	{
		for (int i = 0; i < vec.size(); ++i)
			cout << vec[i].first << ", " << vec[i].second << endl;
		cout << endl;
	}

	int find(int pty)
	{
		int i = 0;
		for (; i < vec.size() and fo.c(pty, vec[i].second); ++i);
		return i;
	}

	void insert(string activity, int priority)
	{
		vec.insert(vec.begin() + find(priority), { activity, priority });
	}

	void removeMax()
	{
		vec.erase(vec.begin());
	}
};

int main()
{
	srand(time(NULL));
	
	priority_queue<functor2> q;
	
	string x = "actividad Nro ";
	for (int i = 0; i < 10; ++i)
		q.insert(x + to_string(i), rand() % 10 + 1);
	
	q.print();


}
