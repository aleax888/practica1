#include "pch.h"
#include "C.h"


C::C(int k)
{
	clave = k;
}


C::~C()
{
}

int C::modulo(int mod, int num)
{
	if (num > 0)
		return num - (num / mod)*mod;
	else
		return num - (num / mod - 1)*mod;
}

string C::cifrar(string smsN)
{
	string cifrado;
	size_t aguja;

	for (int i = 0; i < smsN.size(); ++i)
	{
		aguja = alfabeto.find(smsN[i]);
		aguja += clave;

		if (aguja >= alfabeto.size())
			aguja = modulo(alfabeto.size(), aguja);

		cifrado += alfabeto[aguja];
	}

	return cifrado;
}

string C::descifrar(string smsC)
{
	string descifrado;
	size_t aguja;

	for (int i = 0; i < smsC.size(); ++i)
	{
		aguja = alfabeto.find(smsC[i]);
		aguja -= clave;

		if (aguja >= alfabeto.size())
			aguja = modulo(alfabeto.size(), aguja);

		descifrado += alfabeto[aguja];
	}


	return descifrado;
}
