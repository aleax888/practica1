#include "pch.h"
#include <stack>
#include <list>
#include <vector>
#include <utility>
#include <iostream>
using namespace std;

template <typename T>
struct nodo
{
	T dato;
	nodo<T>**hijos = new nodo<T>*[2];

	nodo(T valor) : dato(valor) { hijos[0] = NULL; hijos[1] = NULL; }
};

template <typename T>
struct arbol
{
	nodo<T>* root = NULL;

	void superPrint()
	{
		vector<T> x;
		vector<vector<T> > y;

		// eje x ________________________________________
		stack< pair<nodo<T>*, int> > stk;
		stk.push({ root, 0 });

		nodo<T>* aux = NULL;

		while (!stk.empty())
		{
			aux = stk.top().first;

			if (!aux) stk.pop();
			else
			{
				if (stk.top().second == 0)
				{
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
					cout << x[j];
					e++;
				}
					
				else
					cout << " ";
			}
			cout << endl;
		}
	}

	void in(nodo<T>* p)
	{
		if (!p) return;

		in(p->hijos[0]);
		cout << p->dato << " ";
		in(p->hijos[1]);
	}

	void inorder()
	{
		cout << "three: ";
		in(root);
		cout << endl;
	}

	void inorderP()
	{
		stack< pair<nodo<T>*, int> > stk;
		stk.push({ root, 0 });

		nodo<T>* aux = NULL;

		cout << "three: ";
		while (!stk.empty())
		{
			aux = stk.top().first;
			
			if (!aux) stk.pop();
			else
			{
				if (stk.top().second == 0)
				{
					stk.top().second++;
					stk.push({ aux->hijos[0], 0 });
				}

				else
				{
					stk.pop();
					cout << aux->dato << " ";
					stk.push({ aux->hijos[1], 0 });
				}
			}
		}
		cout << endl;
	}

	void inorderC()
	{
		vector<nodo<T>*> vec;
		if (root) vec.push_back(root);

		while (vec.size() > 0)
		{
			for (int i = 0; i < vec.size(); ++i)
				cout << vec[i]->dato << " ";
			cout << endl;

			for (int i = 0, aux = vec.size(); i < aux; ++i)
			{
				if (vec[0]->hijos[0])
					vec.push_back(vec[0]->hijos[0]);

				if (vec[0]->hijos[1])
					vec.push_back(vec[0]->hijos[1]);

				vec.erase(vec.begin());
			}
		}
	}

	bool find(T valor, nodo<T>**&p)
	{
		while ( (*p) and (*p)->dato != valor)
			p = &(*p)->hijos[((*p)->dato < valor)];

		return (*p);
	}

	void insert(T valor)
	{
		nodo<T>** p = &root;
		
		if (!find(valor, p))
			(*p) = new nodo<T>(valor);
	}

	void remove(T valor)
	{
		nodo<T>** p = &root;
		if (find(valor, p))
		{
			nodo<T>** q = p;
			if ((*p)->hijos[0] != 0 and (*p)->hijos[1] != 0)
			{
				for (q = &(*p)->hijos[1]; (*q)->hijos[0]; q = &(*q)->hijos[0]);
				(*p)->dato = (*q)->dato;
			}

			nodo<T>* t = (*q);
			(*q) = (*q)->hijos[ !((*q)->hijos[0]) ];
			delete[] t;
		}
	}
};



int main()
{
	arbol<int> xd;
	xd.insert(4);
	xd.insert(2);
	xd.insert(6);
	xd.insert(1);
	xd.insert(3);
	xd.insert(5);
	xd.insert(7);

	xd.superPrint();
}
