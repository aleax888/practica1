#include "pch.h"
#include <stack>
#include <vector>
#include <queue>
#include <list>
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
	queue<nodo<T>*> que;
	
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

	void swaper(nodo<T> *p)
	{
		if (!p) return;
		
		if (p->hijos[0] and p->dato < p->hijos[0]->dato)
		{
			T aux = p->dato;
			p->dato = p->hijos[0]->dato;
			p->hijos[0]->dato = aux;

			swaper(root);
		}
		
		else
			swaper(p->hijos[0]);
		
		if (p->hijos[1] and p->dato < p->hijos[1]->dato)
		{
			T aux = p->dato;
			p->dato = p->hijos[1]->dato;
			p->hijos[1]->dato = aux;

			swaper(root);
		}

		else
			swaper(p->hijos[1]);
	}
	
	
	void insert(T valor)
	{
		if (!root)
		{
			root = new nodo<T>(valor);
			que.push(root);
		}

		else
		{
			if (!que.front()->hijos[0])
			{
				que.front()->hijos[0] = new nodo<T>(valor);
				que.push(que.front()->hijos[0]);
			}

			else 
			{
				que.front()->hijos[1] = new nodo<T>(valor);
				que.push(que.front()->hijos[1]);
				que.pop();
			}
		}
		swaper(root);
	}

	void removeMax()
	{

	}
};



int main()
{
	arbol<int> xd;
	
	xd.insert(1);
	xd.insert(2);
	xd.insert(3);
	xd.insert(4);
	xd.insert(5);
	xd.insert(6);
	xd.insert(7);

	

	xd.inorder();
	
	

}
