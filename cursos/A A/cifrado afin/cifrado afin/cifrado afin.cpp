#include "pch.h"
#include <iostream>
#include <string>
#include "Afin.h"
using namespace std;


int main()
{
	
	/*Afin x;
	Afin y(x.getA(), x.getB());
	x.print();

	string mensaje = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	string cifrado = x.cifrar(mensaje);
	string descifrado = y.descifrar(cifrado);

	cout << "mensaje original:   " << mensaje << endl;
	cout << "mensaje cifrado:    " << cifrado << endl;
	cout << "mensaje descifrado: " << descifrado << endl;*/
	
	
	int opcion; cout << "opcion 1: descifrar \nopcion 2: cifrar\n"; cin >> opcion; cout << endl;
	if (opcion == 1)
	{
		int p; cout << "clave a: "; cin >> p; cout << endl;
		int q; cout << "clave b: "; cin >> q; cout << endl;
		string sms; cout << "mensaje: "; getline(cin, sms); getline(cin, sms); cout << endl;


		Afin a(p, q);
		cout << a.descifrar(sms);
	}

	else
	{
		Afin a;
		a.print();
		string sms; cout << "mensaje: "; getline(cin, sms); getline(cin, sms); cout << endl;
		cout << a.cifrar(sms);
	}

	return 0;
}
