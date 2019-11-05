#include "pch.h"
#include <stack>
#include <vector>
#include <queue>
#include <list>
#include <string>
#include <utility>
#include <iostream>
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
struct nodo
{
	T dato;
	nodo<T>**hijos = new nodo<T>*[2];

	nodo(T valor) : dato(valor) { hijos[0] = NULL; hijos[1] = NULL; }
};

template <typename T, typename F>
struct arbol
{
	nodo<T>* root = NULL;
	vector<nodo<T>**> vec;
	F fo;

	arbol()
	{
		vec.push_back(&root);
	}
	void superPrint()
	{
		string ancho = to_string(root->dato);
		vector<T> x;
		vector<vector<T> > y;

		// eje x ________________________________________
		stack< pair<nodo<T>*, int> > stk;
		stk.push({ root, 0 });

		nodo<T>* aux = NULL;
		
		string str;
		while (!stk.empty())
		{
			aux = stk.top().first;

			if (!aux) stk.pop();
			else
			{
				if (stk.top().second == 0)
				{
					str = to_string(aux->dato); if (str.size() > ancho.size()) ancho = str;
					stk.top().second++;
					stk.push({ aux->hijos[0], 0 });
				}

				else
				{
					stk.pop();
					x.push_back(aux->dato);
					stk.push({ aux->hijos[1], 0 });
				}
			}
		}

		// eje y ____________________________________
		vector<nodo<T>*> vec;
		vector<T> vecaux;
		
		if (root)
		{
			vec.push_back(root);
			vecaux.push_back(root->dato);
		}

		while (vec.size() > 0)
		{
			y.push_back(vecaux);
			vecaux.clear();

			for (int i = 0, aux = vec.size(); i < aux; ++i)
			{
				if (vec[0]->hijos[0])
				{
					vec.push_back(vec[0]->hijos[0]);
					vecaux.push_back(vec[0]->hijos[0]->dato);
				}

				if (vec[0]->hijos[1])
				{
					vec.push_back(vec[0]->hijos[1]);
					vecaux.push_back(vec[0]->hijos[1]->dato);
				}

				vec.erase(vec.begin());
			}
		}

		
		// print xd 
		for (int i = 0; i < y.size(); ++i)
		{
			for (int j = 0, e = 0; j < x.size() and e < y[i].size(); j++)
			{
				if (y[i][e] == x[j])
				{
					string aux = to_string(x[j]);
					for (int i = aux.size(); i < ancho.size(); ++i)
						aux.push_back(' ');
					cout << aux;
					e++;
				}

				else
				{
					for (int i = 0; i < ancho.size(); ++i)
						cout << " ";
				}
					
			}
			cout << endl;
		}
	}

	void printC()
	{
		if (root)
		{
			cout << "Priority queue: ";
			for (int i = 0; i < vec.size(); ++i)
				if ((*vec[i]))
					cout << (*vec[i])->dato << " ";
				//else cout << "* ";
			cout << endl;
		}
		else
			cout << "No hay elementos" << endl;
	}

	void swaper(nodo<T> *p)
	{
		if (!p) return;

		if (p->hijos[0] and fo.c(p->dato, p->hijos[0]->dato))
		{
			T aux = p->dato;
			p->dato = p->hijos[0]->dato;
			p->hijos[0]->dato = aux;

			swaper(root);
		}

		else
			swaper(p->hijos[0]);

		if (p->hijos[1] and fo.c(p->dato, p->hijos[0]->dato))
		{
			T aux = p->dato;
			p->dato = p->hijos[1]->dato;
			p->hijos[1]->dato = aux;

			swaper(root);
		}

		else
			swaper(p->hijos[1]);
	}

	bool find(T valor, nodo<T>**& p)
	{
		int i = 0;

		for (; (*vec[i]) and (*vec[i])->dato != valor; ++i);
		
		p = vec[i];
		
		return (*p) and (*p)->dato == valor;
	}

	void insert(T valor)
	{
		nodo<T>** p = NULL;
		if (!find(valor, p))
		{
			(*p) = new nodo<T>(valor);
			
			vec.push_back(&(*p)->hijos[0]);
			vec.push_back(&(*p)->hijos[1]);
			
			swaper(root);
		}
	}

	void removeMax()
	{
		(*vec[0])->dato = (*vec[vec.size() / 2 - 1])->dato;
		(*vec[vec.size() / 2 - 1]) = NULL;
		vec.pop_back();
		vec.pop_back();

		swaper(root);
	}

	void heapsort()
	{
		list<int> l;

		int aux = vec.size() / 2;
		for (int i = 0; i < aux; ++i)
		{
			l.push_front((*vec[0])->dato);
			removeMax();
		}
			

		for (list<int>::iterator i = l.begin(); i != l.end(); i++)
			cout << *i << " ";
		cout << endl;
	}

};



int main()
{
	arbol<int, functor2> xd;

	xd.insert(8);
	xd.insert(3);
	xd.insert(10);
	xd.insert(1);
	xd.insert(6);
	xd.insert(4);
	xd.insert(7);
	xd.insert(13);
	xd.insert(14);
	

	xd.superPrint();


}
