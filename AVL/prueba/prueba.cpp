#include "pch.h"
#include <ctime>
#include <string>
#include <stack>
#include <queue>
#include <list>
#include <utility>
#include <vector>
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
		queue<nodo<T>*> q;
		q.push(root);

		while (!q.empty())
		{
			for (int i = q.size(); i > 0; --i)
			{
				cout << q.front()->dato << " ";
				if (q.front()->hijos[0]) q.push(q.front()->hijos[0]);
				if (q.front()->hijos[1]) q.push(q.front()->hijos[1]);
				q.pop();
			}
			cout << endl;
		}
	}

	int nivel(nodo<T>* x)
	{
		int izq = 0;
		int der = 0;

		queue<nodo<T>*> q;
		if (x->hijos[0]) q.push(x->hijos[0]);
		while (!q.empty())
		{
			for (int i = q.size(); i > 0; --i)
			{
				if (q.front()->hijos[0]) q.push(q.front()->hijos[0]);
				if (q.front()->hijos[1]) q.push(q.front()->hijos[1]);
				q.pop();
			}
			izq++;
		} 
		
		if (x->hijos[1]) q.push(x->hijos[1]);
		while (!q.empty())
		{
			for (int i = q.size(); i > 0; --i)
			{
				if (q.front()->hijos[0]) q.push(q.front()->hijos[0]);
				if (q.front()->hijos[1]) q.push(q.front()->hijos[1]);
				q.pop();
			}
			der++;
		} 

		return der - izq;
	}

	void swing(T valor)
	{
		vector< pair<nodo<T>**, int> > camino;
		for (nodo<T>** p = &root; *p; p = &(*p)->hijos[((*p)->dato < valor)])
			camino.push_back({ p, nivel(*p)});

		
		vector< pair<nodo<T>**, int> > error;
		for (int i = camino.size() - 1; i >= 0; --i)
		{
			if (camino.size() > 2 and (camino[i].second == 2 or camino[i].second == -2))
			{
				error.push_back(camino[i]);
				error.push_back(camino[i + 1]);
				error.push_back(camino[i + 2]);
				break;
			}
		}camino.clear();
		
		if (error.size() > 0)
		{
			
			if (error[0].second * error[1].second < 0)
			{
				int m = 1;
				if (error[0].second < 0) m = 0;
				
				nodo<T>* aux1 = (*error[1].first);
				(*error[1].first) = (*error[2].first);
				(*error[2].first) = (*error[2].first)->hijos[m];
				(*error[1].first)->hijos[m] = aux1;
			}
			
			int w = 0;
			if (error[0].second < 0) w = 1;

			nodo<T>* aux = (*error[0].first);
			(*error[0].first) = (*error[1].first);
			(*error[1].first) = (*error[1].first)->hijos[w];
			(*error[0].first)->hijos[w] = aux;
		}
	}

	bool find(T valor, nodo<T>**&p)
	{
		for (p = &root; (*p) and (*p)->dato != valor; p = &(*p)->hijos[((*p)->dato < valor)]);

		return (*p);
	}

	void insert(T valor)
	{
		nodo<T>** p = &root;

		if (!find(valor, p))
			(*p) = new nodo<T>(valor);

		swing(valor);
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
			(*q) = (*q)->hijos[!((*q)->hijos[0])];
			delete[] t;
			
		}
	}
};



int main()
{
	arbol<int> xd;

	srand(time(NULL));

	//for (int i = 0; i < 7; ++i) xd.insert(rand() % 100);
	
	xd.insert(3);
	xd.insert(1);
	xd.insert(2);
	xd.insert(4);
	
	xd.superPrint();
	xd.remove(1);
	xd.superPrint();

}
