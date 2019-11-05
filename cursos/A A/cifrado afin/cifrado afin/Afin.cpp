#include "pch.h"
#include "Afin.h"

// detector de overflow __________________________________________________________
template <int n>
int overflow(bitset<n> a, bitset<n> b)
{
	int aux;
	int acarreo = 0;
	for (int i = 0; i < n; ++i)
	{
		aux = (a[i] + b[i] + acarreo) % 2;
		acarreo = (a[i] + b[i] + acarreo) / 2;
	}

	return acarreo;
}

// sumador binario _______________________________________________________________
template <int n>
bitset<n> suma(bitset<n> a, bitset<n> b)
{
	bitset<n> resultado;

	int aux;
	int acarreo = 0;
	for (int i = 0; i < n; ++i)
	{
		aux = (a[i] + b[i] + acarreo) % 2;
		acarreo = (a[i] + b[i] + acarreo) / 2;

		resultado[i] = aux;
	}

	return resultado;
}

// calculador de complemento a 2 (negativo) _____________________________________
template <int n>
bitset<n> CA2(bitset<n> a)
{
	bitset<n> aux = a.flip();
	return suma<n>(aux, 1);
}

// resta binaria ________________________________________________________________
template<int n, int m>
bitset<n> resta(bitset<n> a, bitset<m> b)
{
	int acarreo = 0;
	int aux = 0;

	bitset< n >temp = CA2<n>(b);

	bitset< n >resultado = suma<n>(temp, a);

	return resultado;
}

// multiplicador binario sin signo _______________________________________________
template <int o, int p>
bitset<o + p> multiplicacion(bitset<o> m, bitset<p> q)
{
	int signo = 1;
	if (m[m.size() - 1])
	{
		m = CA2<o>(m);
		signo *= -1;
	}
	if (q[q.size() - 1])
	{
		q = CA2<p>(q);
		signo *= -1;
	}

	bitset<o> a;
	bitset<p> b = q;

	int acarreo = 0;
	int aux;
	int cuenta = p;

	for (int i = 0; i < cuenta; ++i)
	{
		if (q[i])
		{
			acarreo = overflow<o>(a, m);
			a = suma<o>(a, m);
			aux = a[0];
			a >>= 1;
			a[a.size() - 1] = acarreo;

			b >>= 1;
			b[b.size() - 1] = aux;
		}

		else
		{
			aux = a[0];
			a >>= 1;
			acarreo = 0;
			a[a.size() - 1] = acarreo;

			b >>= 1;
			b[b.size() - 1] = aux;
		}
	}

	bitset<o + p> resultado;

	for (int i = 0; i < p; ++i)
		resultado[i] = b[i];

	for (int i = p, j = 0; i < p + o; ++i, ++j)
		resultado[i] = a[j];

	if (signo == -1)
		resultado = CA2<o + p>(resultado);

	return resultado;
}

// tranformador de binario a decimal _____________________________________________
template <int n>
int interpreter(bitset<n> a)
{
	int resultado = 0;
	int p = 1;

	for (int i = 0; i < a.size() - 1; ++i)
	{
		resultado += a[i] * p;
		p *= 2;
	}

	if (a[a.size() - 1])
		resultado -= a[a.size() - 1] * p;
	else
		resultado += a[a.size() - 1] * p;

	return resultado;
}

// comprobar si es par ___________________________________________________________
template <int n>
bool par(bitset<n> a)
{
	if (a[0])
		return false;
	else
		return true;
}

// division entre dos a un numero par_____________________________________________
template <int n>
void divi2(bitset<n> &a)
{
	a = a >> 1;
}

// elvar 2 a una potencia n ______________________________________________________
template <int n>
void pote2(bitset<n> &a, int b)
{
	if (!b)
		a = a >> 1;
	else
		for (int i = 1; i < b; ++i)
		{
			a = a << 1;
		}
}

// intercambiar dos numeros binarios _____________________________________________
template <int n>
void change(bitset<n> &a, bitset<n> &b)
{
	bitset<n> temp = a;
	a = b;
	b = temp;
}

// comparacion si a es menor que b
template <int n>
bool comp(bitset<n> a, bitset<n> b)
{
	int x = interpreter<n>(a);
	int y = interpreter<n>(b);

	if (x < y)
		return true;
	else
		return false;
}

// euclides algoritmo 4 __________________________________________________________
template <int t>
int numero4(int num1, int num2)
{
	bitset<t> m(num1);
	bitset<t> n(num2);

	if (m == 0 || n == 0)
		return 0;

	bitset<t> s;
	while (par<t>(m) && par<t>(n))
	{
		divi2<t>(m);
		divi2<t>(n);
		suma<t>(s, 1);
	}

	while (par<t>(n))
		divi2<t>(n);

	while (m != 0)
	{
		while (par<t>(m))
			divi2<t>(m);

		if (comp<t>(m, n))
			change<t>(m, n);

		m = resta(m, n);
		divi2<t>(m);
	}

	int s1 = interpreter<t>(s);
	bitset<t> dos(2);
	pote2(dos, s1);


	return interpreter<t*2>(multiplicacion<t, t>(dos, n));
}

int Afin::modulo(int num, int mod) 
{
	int x = num / mod;

	if (num <= 0) x--;

	if ((num - x * mod) == mod)
		return 0;

	return num - x * mod;
}

void aux(int &a, int &b, int &c)
{
	int x = a - (b * c);
	a = c;
	c = x;
}

int Afin::euclidesE(int num1, int num2, int a)
{
	int q;
	int r1 = num1, r2 = num2;
	int s1 = 1, s2 = 0;
	int t1 = 0, t2 = 1;

	while (r2 > 0)
	{
		q = r1 / r2;

		aux(r1, q, r2);
		if (a == 2) aux(s1, q, s2);
		if (a == 3) aux(t1, q, t2);
	}

	if (a == 1)
		return r1;
	else if (a == 2)
		return modulo(s1,alfatam);
	else if (a == 3)
		return modulo(t1, alfatam);
}

int Afin::genClave()
{
	int x;
	do
	{
		x = modulo(rand(), alfatam) + 1;

	} while (euclidesE(x, alfabeto.size(), 1) != 1);
	return x;
}

Afin::Afin()
{
	srand(time(NULL));
	claveA = genClave();
	claveB = modulo(rand(), alfatam) + 1;
}

Afin::Afin(int a, int b)
{
	int invA = euclidesE(a, alfatam, 2);
	claveA = invA;
	claveB = b;
}

Afin::~Afin()
{
}

void Afin::print()
{
	std::cout << "a: " << claveA << endl;
	std::cout << "b: " << claveB << endl;
}

string Afin::cifrar(string sms)
{
	string cifrado;
	size_t aguja;
	int aux;

	for (int i = 0; i < sms.size(); ++i)
	{
		aguja = alfabeto.find(sms[i]);
		aux = (claveA * aguja) + claveB;
		cifrado += alfabeto[modulo(aux, alfatam)];
	}

	return cifrado;
}

string Afin::descifrar(string sms)
{
	string descifrado;
	size_t aguja;
	int aux;
	
	for (int i = 0; i < sms.size(); ++i)
	{
		aguja = alfabeto.find(sms[i]);
		aux = claveA * (aguja - claveB);
		descifrado += alfabeto[modulo(aux, alfatam)];
	}

	return descifrado;
}

int Afin::getA(){ return claveA; }
	
int Afin::getB() { return claveB; }























