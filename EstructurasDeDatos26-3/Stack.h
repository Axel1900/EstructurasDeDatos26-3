#pragma once
#include <iostream>
#include "TNode.h"
#include "ConsoleUI.h"

// =====================================================================
//  Stack<T>  -  Pila generica (LIFO)
//
//  El tope es la CABEZA de la lista: cada nodo apunta hacia ABAJO.
//  Gracias a eso, Push y Pop son O(1): nunca hay que recorrer nada.
//
//  TODO: implementa todo lo que dice TODO.
// =====================================================================

template <class T>
class Stack
{
private:
    TNode<T>* _top;
    int _size;

    // Privada a proposito: si alguien de afuera pudiera pasar un nodo,
    // no quedaria claro quien es dueño de esa memoria ni quien la libera.
    // Desde afuera solo se puede usar Push(T value).
    void Push(TNode<T>* n);

    void CopiarRec(TNode<T>* actual);

public:
    Stack();
    Stack(const Stack<T>& otro);              // constructor de copia
    Stack<T>& operator=(const Stack<T>& otro); // operador de asignacion
    ~Stack();

    void Push(T value);
    T Pop();
    T Top();
    bool IsEmpty();
    int GetSize();
    void Clear();
    void Print();
};

template <class T>
Stack<T>::Stack()
{
    _top = nullptr;
    _size = 0;
}

template <class T>
void Stack<T>::CopiarRec(TNode<T>* actual)
{
    if (actual == nullptr) return;

    CopiarRec(actual->getNext());
    Push(actual->getDato());
}

template <class T>
Stack<T>::Stack(const Stack<T>& otro)
{
    // TODO: copia PROFUNDA. Hay que crear nodos NUEVOS con los mismos
    // valores y en el mismo orden, no apuntar a los nodos de 'otro'.
    _top = nullptr;
    _size = 0;
    CopiarRec(otro._top);
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& otro)
{
    if (this == &otro)
    {
        // TODO: 1) cuidado con la autoasignacion (a = a)
        //       2) libera lo que ya tenias
        //       3) copia profunda de 'otro'
        return *this;
    }

    Clear();
    CopiarRec(otro._top);

    return *this;
}

template <class T>
Stack<T>::~Stack()
{
    Clear();
}

template <class T>
void Stack<T>::Push(TNode<T>* n)
{
    n->setNext(_top);
    _top = n;
    _size++;
}

template <class T>
void Stack<T>::Push(T value)
{
    TNode<T>* n = new TNode<T>(value, _size);
    Push(n);
}

template <class T>
T Stack<T>::Pop()
{
    if (IsEmpty())
    {
        ConsoleUI::PrintError("Stack::Pop - la pila esta vacia");
        return T();
    }

    TNode<T>* temp = _top;
    T valor = temp->getDato();

    _top = temp->getNext();
    delete temp;
    _size--;

    return valor;
}

template <class T>
T Stack<T>::Top()
{
    if (IsEmpty())
    {
        ConsoleUI::PrintError("Stack::Top - la pila esta vacia");
        return T();
    }

    return _top->getDato();
}

template <class T>
bool Stack<T>::IsEmpty()
{
    return _top == nullptr;
}

template <class T>
int Stack<T>::GetSize()
{
    return _size;
}

template <class T>
void Stack<T>::Clear()
{
    while (_top != nullptr)
    {
        TNode<T>* temp = _top;
        _top = _top->getNext();
        delete temp;
    }
    _size = 0;
}

template <class T>
void Stack<T>::Print()
{
    if (IsEmpty())
    {
        ConsoleUI::PrintColor("(pila vacia)", ConsoleUI::COLOR_AMARILLO);
        return;
    }

    TNode<T>* actual = _top;
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
