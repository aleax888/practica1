#include "pch.h"
#include "Cesar.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	int k = 3;

	Cesar emisor(k);
	Cesar receptor(k);

	string mensaje    = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	string cifrado    = emisor.cifrar(mensaje);
	string descifrado = emisor.descifrar(cifrado);

	cout << "texto plano     : " << mensaje    << endl;
	cout << "texto cifrado   : " << cifrado    << endl;
	cout << "texto descifrado: " << descifrado << endl;



	return 0;
}