#pragma once
#include <string>
using namespace std;

class C
{
public:
	string alfabeto = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-";

	C(int);
	~C();

	string cifrar(string);
	string descifrar(string);
	int modulo(int, int);

private:
	int clave;
};

