#include "pch.h"
#include <iostream>
#include <ctime>
using namespace std;


int numero1(int m, int n)
{
	if (m == 0)
		return n;

	while (m != 0)
	{
		if (n > m)
			n -= m;

		else
			m -= n;
	}
	return n;
}

int numero2(int m, int n)
{
	int t;
	while (n != 0)
	{
		t = n;
		n = m % n;
		m = t;
	}

	return m;
}

int numero3(int m, int n)
{
	if (n == 0)
		return m;

	else
		numero3(n, m % n);
}

int numero4(int m, int n)
{
	if (m == 0 || n == 0)
		return 0;

	int s = 0;
	while (!(m % 2) && !(n % 2))
	{
		m /= 2;
		n /= 2;
		s++;
	}

	while (!(n % 2))
		n /= 2;

	while (m != 0)
	{
		while (!(m % 2))
			m /= 2;

		if (m < n)
			swap(m, n);

		m -= n;
		m /= 2;
	}

	return pow(2, s) * n;
}


int main()
{
	cout << numero2(231345, 1575) << endl;
	//cout << numero4(231345, 1575) << endl;

	clock_t t = clock();
	cout << t;

	return 0;
}
