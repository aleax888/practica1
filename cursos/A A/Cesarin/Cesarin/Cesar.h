#pragma once
#include <string>
using namespace std;
class Cesar
{
public:
	string alfabeto = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

	Cesar(int);
	~Cesar();

	string cifrar(string);
	string descifrar(string);
	int modulo(int, int);

private:
	int clave;
};

