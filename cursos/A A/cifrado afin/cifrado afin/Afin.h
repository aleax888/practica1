#pragma once
#include <string>
#include <ctime>
#include <iostream>
#include <bitset>
using namespace std;

class Afin
{
public: //abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-
	string alfabeto = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ";
	int alfatam = alfabeto.size();

	int genClave();

	Afin();
	Afin(int, int);
	~Afin();

	void print(void);

	string cifrar(string);
	string descifrar(string);

	int modulo(int, int);
	int euclidesE(int, int, int );

	int getA();
	int getB();


private:
	int claveA;
	int claveB;
};

