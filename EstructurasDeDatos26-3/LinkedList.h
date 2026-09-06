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
}

template <class T>
void LinkedList<T>::Add(Node* n)
{
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
    Node* nuevo = new Node();
    nuevo->data = dato;
    nuevo->next = nullptr;
    nuevo->id = _size;

    Add(nuevo);
}

template <class T>
T LinkedList<T>::GetAt(int index)
{
    Node* actual = _first;
    for (int i = 0; i < index; i++)   
    {
        actual = actual->next; 
    }
    return actual->data;  
}

template <class T>
T& LinkedList<T>::operator[](int index)
{
    Node* actual = _first;
    for (int i = 0; i < index; i++)
    {
        actual = actual->next;
    }
    return actual->data;
}

template <class T>
int LinkedList<T>::GetSize()
{
    return _size;
}

template <class T>
void LinkedList<T>::Print()
{
    Node* actual = _first;
    while (actual != nullptr)
    {
        std::cout << actual->data << " ";
        actual = actual->next;
    }
    std::cout << std::endl;
}

template <class T>
void LinkedList<T>::PrintReverse()
{
    PrintReverseRec(_first);
}

template <class T>
void LinkedList<T>::PrintReverseRec(Node* actual)
{
    if (actual == nullptr)
        return;

    PrintReverseRec(actual->next);

    std::cout << actual->data << " ";
}

template <class T>
T LinkedList<T>::GetAtRecursivo(int index)
{
    return GetAtRec(_first, index);
}

template <class T>
T LinkedList<T>::GetAtRec(Node* actual, int index)
{
    if (index == 0)
        return actual->data;

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
        return 0;

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
        return -1;  

    if (actual->data == valor)
        return indiceActual; 

    return BuscarRec(actual->next, valor, indiceActual + 1);
}

template <class T>
void LinkedList<T>::SelectionSort()
{
    for (Node* i = _first; i != nullptr && i->next != nullptr; i = i->next)
    {
        Node* minimo = i;
        for (Node* j = i->next; j != nullptr; j = j->next)
        {
            if (j->data < minimo->data)
                minimo = j;
        }
        T temp = i->data;
        i->data = minimo->data;
        minimo->data = temp;
    }
}

template <class T>
void LinkedList<T>::InsertionSort()
{
    for (Node* actual = _first; actual != nullptr; actual = actual->next)
    {
        Node* j = actual;
        while (j != _first)
        {
            Node* prev = _first;
            while (prev->next != j)
                prev = prev->next;

            if (prev->data > j->data)
            {
                T temp = prev->data;
                prev->data = j->data;
                j->data = temp;
                j = prev; 
            }
            else
            {
                break;
            }
        }
    }
}