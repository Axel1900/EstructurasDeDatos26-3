#pragma once
#include <iostream>

// =====================================================================
//  LinkedList<T>  -  Lista ligada simple, ahora generica
//
//  Es la misma lista que ya programaste, pero con templates: en lugar
//  de servir solo para int, ahora sirve para cualquier tipo.
//
//  NUEVO EN ESTA VERSION:
//    - operator[] que regresa REFERENCIA (T&), para poder escribir:
//         lista[0] = 99;
//    - versiones RECURSIVAS de operaciones que ya tenias iterativas
//    - PrintReverse, que imprime la lista al reves
// =====================================================================

template <class T>
class LinkedList
{
private:
    struct Node
    {
        T data;
        Node* next;
        int id;
    };

    Node* _first;
    int _size;
    T _basura;   // valor de respaldo para operator[] fuera de rango

    // Privada: desde afuera solo se puede usar Add(T dato).
    void Add(Node* n);

    Node* NodoEn(int index);

    // Auxiliares recursivas. Reciben el nodo actual porque la
    // recursion necesita "avanzar", y desde afuera nadie ve los nodos.
    T GetAtRec(Node* actual, int index);
    int CountRec(Node* actual);
    int BuscarRec(Node* actual, T valor, int indiceActual);
    void PrintReverseRec(Node* actual);

public:
    LinkedList();
    ~LinkedList();

    void Add(T dato);
    T GetAt(int index);
    T& operator[](int index);
    int GetSize();
    void Print();

    void PrintReverse();
    T GetAtRecursivo(int index);
    int CountRecursivo();
    int BuscarRecursivo(T valor);

    void SelectionSort();
    void InsertionSort();
};

template <class T>
LinkedList<T>::LinkedList()
{
    _first = nullptr;
    _size = 0;
    _basura = T();
}

template <class T>
LinkedList<T>::~LinkedList()
{
    Node* actual = _first;
    while (actual != nullptr)
    {
        Node* siguiente = actual->next;
        delete actual;
        actual = siguiente;
    }
    _first = nullptr;
    _size = 0;
}

template <class T>
typename LinkedList<T>::Node* LinkedList<T>::NodoEn(int index)
{
    if (index < 0 || index >= _size)
    {
        return nullptr;
    }

    Node* actual = _first;
    for (int i = 0; i < index; i++)
    {
        actual = actual->next;
    }
    return actual;
}

template <class T>
void LinkedList<T>::Add(Node* n)
{
    n->next = nullptr;

    if (_first == nullptr)
    {
        _first = n;
    }
    else
    {
        Node* actual = _first;
        while (actual->next != nullptr)
        {
            actual = actual->next;
        }
        actual->next = n;
    }

    _size++;
}

template <class T>
void LinkedList<T>::Add(T dato)
{
    Node* n = new Node();
    n->data = dato;
    n->next = nullptr;
    n->id = _size;

    Add(n);
}

template <class T>
T LinkedList<T>::GetAt(int index)
{
    Node* nodo = NodoEn(index);
    if (nodo == nullptr)
    {
        ConsoleUI::PrintError("LinkedList::GetAt - indice fuera de rango");
        return T();
    }
    return nodo->data;
}

template <class T>
T& LinkedList<T>::operator[](int index)
{
    Node* nodo = NodoEn(index);
    if (nodo == nullptr)
    {
        ConsoleUI::PrintError("LinkedList::operator[] - indice fuera de rango, se regreso una referencia de respaldo");
        _basura = T();
        return _basura;
    }
    return nodo->data;
}

template <class T>
int LinkedList<T>::GetSize()
{
    return _size;
}

template <class T>
void LinkedList<T>::Print()
{
    if (_first == nullptr)
    {
        ConsoleUI::PrintColor("(lista vacia)", ConsoleUI::COLOR_AMARILLO);
        return;
    }

    Node* actual = _first;
    while (actual != nullptr)
    {
        std::cout << actual->data;
        if (actual->next != nullptr)
        {
            std::cout << " -> ";
        }
        actual = actual->next;
    }
    std::cout << std::endl;
}

template <class T>
void LinkedList<T>::PrintReverse()
{
    PrintReverseRec(_first);
    std::cout << std::endl;
}

template <class T>
void LinkedList<T>::PrintReverseRec(Node* actual)
{
    if (actual == nullptr)
    {
        return;
    }

    PrintReverseRec(actual->next);
    std::cout << actual->data;
    if (actual != _first)
    {
        std::cout << " ";
    }
}

template <class T>
T LinkedList<T>::GetAtRecursivo(int index)
{
    if (index < 0 || index >= _size)
    {
        ConsoleUI::PrintError("LinkedList::GetAtRecursivo - indice fuera de rango");
        return T();
    }
    return GetAtRec(_first, index);
}

template <class T>
T LinkedList<T>::GetAtRec(Node* actual, int index)
{
    if (index == 0)
    {
        return actual->data;
    }
    return GetAtRec(actual->next, index - 1);
}

template <class T>
int LinkedList<T>::CountRecursivo()
{
    return CountRec(_first);
}

template <class T>
int LinkedList<T>::CountRec(Node* actual)
{
    if (actual == nullptr)
    {
        return 0;
    }
    return 1 + CountRec(actual->next);
}

template <class T>
int LinkedList<T>::BuscarRecursivo(T valor)
{
    return BuscarRec(_first, valor, 0);
}

template <class T>
int LinkedList<T>::BuscarRec(Node* actual, T valor, int indiceActual)
{
    if (actual == nullptr)
    {
        return -1; 
    }
    if (actual->data == valor)
    {
        return indiceActual;
    }
    return BuscarRec(actual->next, valor, indiceActual + 1);
}

template <class T>
void LinkedList<T>::SelectionSort()
{
    for (int i = 0; i < _size - 1; i++)
    {
        int indiceMinimo = i;

        for (int j = i + 1; j < _size; j++)
        {
            if (NodoEn(j)->data < NodoEn(indiceMinimo)->data)
            {
                indiceMinimo = j;
            }
        }

        if (indiceMinimo != i)
        {
            Node* nodoI = NodoEn(i);
            Node* nodoMin = NodoEn(indiceMinimo);

            T temp = nodoI->data;
            nodoI->data = nodoMin->data;
            nodoMin->data = temp;
        }
    }
}

template <class T>
void LinkedList<T>::InsertionSort()
{
    for (int i = 1; i < _size; i++)
    {
        T clave = NodoEn(i)->data;
        int j = i - 1;

        while (j >= 0 && NodoEn(j)->data > clave)
        {
            NodoEn(j + 1)->data = NodoEn(j)->data;
            j--;
        }

        NodoEn(j + 1)->data = clave;
    }
}
