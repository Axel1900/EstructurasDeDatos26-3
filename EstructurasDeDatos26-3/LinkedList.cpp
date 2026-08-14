#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList()
{
	_first = nullptr;
	_size = 0;
}

void LinkedList::Add(int dato)
{
	Node* nuevo = new Node();
	nuevo->data = dato;
	nuevo->next = nullptr;

	if (_first == nullptr)
	{
		_first = nuevo;
	}
	else
	{
		Node* actual = _first;
		while (actual->next != nullptr)
		{
			actual = actual->next;
		}
		actual->next = nuevo;
	}
	_size++;
}

int LinkedList::GetAt(int index)
{
	if (index < 0 || index >= _size)
	{
		return -1;
	}

	Node* actual = _first;
	for (int i = 0; i < index; i++)
	{
		actual = actual->next;
	}
	return actual->data;
}

int LinkedList::GetSize()
{
	return _size;
}

void LinkedList::Print()
{
	Node* actual = _first;
	while (actual != nullptr)
	{
		actual = actual->next;
	}
}

void LinkedList::SelectionSort()
{
	Node* actual = _first;
	while (actual != nullptr)
	{
		Node* menor = actual;
		Node* recorrido = actual->next;

		while (recorrido != nullptr)
		{
			if (recorrido->data < menor->data)
			{
				menor = recorrido;
			}
			recorrido = recorrido->next;
		}

		int temp = actual->data;
		actual->data = menor->data;
		menor->data = temp;

		actual = actual->next;
	}
}

LinkedList::~LinkedList()
{
	Node* actual = _first;
	while (actual != nullptr)
	{
		Node* siguiente = actual->next;
		delete actual;
		actual = siguiente;
	}
}