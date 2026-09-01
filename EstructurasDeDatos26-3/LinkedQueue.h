#pragma once
#include <iostream>
#include "TNode.h"
#include "ConsoleUI.h"

// =====================================================================
//  LinkedQueue<T>  -  Cola generica (FIFO) sobre nodos enlazados
//
//  Se opera por los DOS extremos: se encola por atras (_last) y se
//  desencola por adelante (_first). Por eso necesita los dos punteros:
//  sin _last, cada Enqueue tendria que recorrer toda la cola.
//
//  CUIDADO con el bug clasico: cuando sacas el ULTIMO elemento,
//  _first queda en nullptr pero _last se queda apuntando a un nodo
//  que ya liberaste. El siguiente Enqueue escribe sobre memoria muerta.
// =====================================================================

template <class T>
class LinkedQueue
{
private:
    TNode<T>* _first;
    TNode<T>* _last;
    int _size;

public:
    LinkedQueue();
    ~LinkedQueue();

    void Enqueue(T value);
    T Dequeue();
    T Front();
    bool IsEmpty();
    int GetSize();
    void Clear();
    void Print();
};

template <class T>
LinkedQueue<T>::LinkedQueue()
{
    _first = nullptr;
    _last = nullptr;
    _size = 0;
}

template <class T>
LinkedQueue<T>::~LinkedQueue()
{
    Clear();
}

template <class T>
void LinkedQueue<T>::Enqueue(T value)
{
    TNode<T>* n = new TNode<T>(value, _size);

    if (IsEmpty())
    {
        _first = n;
        _last = n;
    }
    else
    {
        _last->setNext(n);
        _last = n;
    }

    _size++;
}

template <class T>
T LinkedQueue<T>::Dequeue()
{
    if (IsEmpty())
    {
        ConsoleUI::PrintError("LinkedQueue::Dequeue - la cola esta vacia");
        return T();
    }

    TNode<T>* temp = _first;
    T valor = temp->getDato();

    _first = _first->getNext();
    delete temp;
    _size--;

    if (_first == nullptr)
    {
        _last = nullptr;
    }

    return valor;
}

template <class T>
T LinkedQueue<T>::Front()
{
    if (IsEmpty())
    {
        ConsoleUI::PrintError("LinkedQueue::Front - la cola esta vacia");
        return T();
    }

    return _first->getDato();
}

template <class T>
bool LinkedQueue<T>::IsEmpty()
{
    return _first == nullptr;
}

template <class T>
int LinkedQueue<T>::GetSize()
{
    return _size;
}

template <class T>
void LinkedQueue<T>::Clear()
{
    while (_first != nullptr)
    {
        TNode<T>* temp = _first;
        _first = _first->getNext();
        delete temp;
    }
    _last = nullptr;
    _size = 0;
}

template <class T>
void LinkedQueue<T>::Print()
{
    if (IsEmpty())
    {
        ConsoleUI::PrintColor("(cola vacia)", ConsoleUI::COLOR_AMARILLO);
        return;
    }

    TNode<T>* actual = _first;
    while (actual != nullptr)
    {
        std::cout << actual->getDato();
        if (actual->getNext() != nullptr)
        {
            std::cout << " -> ";
        }
        actual = actual->getNext();
    }
    std::cout << std::endl;
}
