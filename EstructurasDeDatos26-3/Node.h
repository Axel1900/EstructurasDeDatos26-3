#pragma once
#include "Edge.h"
#include "LinkedList.h"

// =====================================================================
//  Node<T>  -  Nodo de un grafo
//
//  Guarda un dato y la lista de aristas que lo tocan.
//
//  Fijate que la lista guarda PUNTEROS a Edge, no aristas por valor.
//  Es a proposito: la MISMA arista aparece en la lista de sus dos nodos.
//  Si guardaras copias, cada nodo tendria su propia version y marcar una
//  como visitada no afectaria a la otra.
//
//  EL NODO NO ES DUENO DE SUS ARISTAS. Solo las apunta. Su destructor
//  no debe liberar nada: de eso se encarga el grafo.
// =====================================================================

template <class T>
class Node
{
private:
    T _value;
    bool _visited;
    LinkedList<Edge<T>*> _neighbors;

public:
    Node();
    Node(T valor);

    T GetValue();
    void SetValue(T valor);
    void SetVisited(bool visitado);
    bool GetVisited();

    void AddNeighbor(Edge<T>* arista);
    int GetNeighborCount();
    Edge<T>* GetNeighbor(int indice);
};

template <class T>
Node<T>::Node()
{
    _value = T();
    _visited = false;
}

template <class T>
Node<T>::Node(T valor)
{
    _value = valor;
    _visited = false;
}

template <class T>
T Node<T>::GetValue()
{
    return _value;
}

template <class T>
void Node<T>::SetValue(T valor)
{
    _value = valor;
}

template <class T>
void Node<T>::SetVisited(bool visitado)
{
    _visited = visitado;
}

template <class T>
bool Node<T>::GetVisited()
{
    return _visited;
}

template <class T>
void Node<T>::AddNeighbor(Edge<T>* arista)
{
    if (arista == nullptr)  return;
    _neighbors.Add(arista);
}

template <class T>
int Node<T>::GetNeighborCount()
{
    return _neighbors.GetSize();
}

template <class T>
Edge<T>* Node<T>::GetNeighbor(int indice)
{
    return _neighbors.GetAt(indice) ;
}
