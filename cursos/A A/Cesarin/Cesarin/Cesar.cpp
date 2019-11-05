#include "pch.h"
#include "Cesar.h"
#include <iostream>

Cesar::Cesar(int k)
{
	clave = k;
}


Cesar::~Cesar()
{
}

int Cesar::modulo(int mod, int num)
{
	if (num > 0)
		return num - (num / mod)*mod;
	else
		return num - (num / mod - 1)*mod;
}

string Cesar::cifrar(string smsN)
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

string Cesar::descifrar(string smsC)
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