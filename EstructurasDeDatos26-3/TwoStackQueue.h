#pragma once
#include "Stack.h"

// =====================================================================
//  TwoStackQueue<T>  -  Cola (FIFO) construida con DOS pilas (LIFO)
//
//  LA IDEA: una pila invierte el orden. Dos pilas lo invierten dos
//  veces, y volver a invertir es regresar al orden original.
//  Orden original = FIFO = cola.
//
//  COMO FUNCIONA:
//    Enqueue -> siempre empuja a _entrada.
//    Dequeue -> saca de _salida. Y SOLO si _salida esta vacia,
//               primero vuelca TODA _entrada dentro de _salida.
//
//  LA REGLA CRITICA: solo vuelcas cuando _salida esta VACIA.
//  Si vuelcas teniendo elementos ahi, los nuevos caen encima de los
//  viejos y salen antes. Ese es el error que casi todos cometen.
//
//  Fijate que esta clase NO maneja punteros ni memoria: reutiliza tu
//  Stack, que ya sabe hacerlo. Por eso tampoco necesita destructor
//  propio (los destructores de _entrada y _salida corren solos).
//
//  IMPORTANTE: tiene EXACTAMENTE la misma interfaz publica que
//  LinkedQueue. Un mismo main debe funcionar con las dos cambiando
//  una sola linea.
// =====================================================================

template <class T>
class TwoStackQueue
{
private:
    Stack<T> _entrada;
    Stack<T> _salida;

    void Volcar();   // pasa todo de _entrada a _salida (si hace falta)

public:
    TwoStackQueue();
    ~TwoStackQueue();

    void Enqueue(T value);
    T Dequeue();
    T Front();
    bool IsEmpty();
    int GetSize();
    void Clear();
    void Print();
};

template <class T>
TwoStackQueue<T>::TwoStackQueue()
{

}

template <class T>
TwoStackQueue<T>::~TwoStackQueue()
{

}

template <class T>
void TwoStackQueue<T>::Volcar()
{
    if (_salida.IsEmpty())
    {
        while (!_entrada.IsEmpty())
        {
            _salida.Push(_entrada.Pop());
        }
    }
}

template <class T>
void TwoStackQueue<T>::Enqueue(T value)
{
    _entrada.Push(value);
}

template <class T>
T TwoStackQueue<T>::Dequeue()
{
    Volcar();

    if (_salida.IsEmpty())
        return T();
    return _salida.Pop();
}

template <class T>
T TwoStackQueue<T>::Front()
{
    Volcar();

    if (_salida.IsEmpty())
        return T();
    return _salida.Top();
}

template <class T>
bool TwoStackQueue<T>::IsEmpty()
{
    return _entrada.IsEmpty() && _salida.IsEmpty();
}

template <class T>
int TwoStackQueue<T>::GetSize()
{
    return _entrada.GetSize() + _salida.GetSize();
}

template <class T>
void TwoStackQueue<T>::Clear()
{
    _entrada.Clear();
    _salida.Clear();
}

template <class T>
void TwoStackQueue<T>::Print()
{
    Volcar();
    _salida.Print();
}