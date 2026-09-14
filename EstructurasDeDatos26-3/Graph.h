#pragma once
#include "Node.h"
#include "Edge.h"
#include "LinkedList.h"
#include "LinkedQueue.h"
#include "ConsoleUI.h"

// =====================================================================
//  Graph<T>  -  Grafo NO dirigido
//
//  EL GRAFO ES EL DUENO DE TODO. El crea los nodos y las aristas, y el
//  las destruye. Ni Node ni Edge liberan nada.
//
//  POR QUE: una arista esta en la lista de vecinos de DOS nodos. Si cada
//  nodo liberara sus propias aristas en su destructor, la arista que
//  conecta A con B se liberaria dos veces: una cuando muere A y otra
//  cuando muere B. Eso es un DOUBLE FREE y tumba el programa, o peor, lo
//  corrompe en silencio.
//
//  Por eso el grafo guarda DOS listas propias: una con todos los nodos y
//  otra con todas las aristas. El destructor recorre esas dos listas y
//  libera cada cosa una sola vez.
//
//  Es el mismo principio por el que hiciste privado el Push(TNode<T>*)
//  de tu Stack: cuando no queda claro quien es dueno de un pedazo de
//  memoria, la estructura contenedora debe serlo, y nadie de afuera
//  puede meter mano.
// =====================================================================

template <class T>
class Graph
{
private:
    LinkedList<Node<T>*> _nodes;
    LinkedList<Edge<T>*> _edges;

    // Auxiliar recursiva del DFS. Recibe el nodo actual porque la
    // recursion necesita avanzar, y desde afuera nadie ve los nodos.
    void DFSRec(Node<T>* n, LinkedList<T>& resultado);

public:
    Graph();
    ~Graph();

    Node<T>* AddNode(T valor);
    void AddEdge(Node<T>* a, Node<T>* b);

    int GetNodeCount();
    int GetEdgeCount();
    void ResetVisited();

    void DFS(LinkedList<T>& resultado);
    void BFS(LinkedList<T>& resultado);
    void Print();
};

template <class T>
Graph<T>::Graph()
{
}

template <class T>
Graph<T>::~Graph()
{
    for (int i; i < _edges.GetSize(); i++)
    {
        delete _edges.GetAt(i);
    }
    for (int i; i < _nodes.GetSize(); i++)
    {
        delete _nodes.GetAt(i);
    }
}

template <class T>
Node<T>* Graph<T>::AddNode(T valor)
{
    Node<T>* nuevo = new Node<T>(valor);
    _nodes.Add(nuevo);
    return nuevo;
}

template <class T>
void Graph<T>::AddEdge(Node<T>* a, Node<T>* b)
{
    if (a == nullptr) return;
    if (b == nullptr) return;
    Edge<T>* arista = new Node<T>*(a, b);
    _edges.Add(arista);
    a->AddNeighbor(arista)
    b->AddNeighbor(arista)
}

template <class T>
int Graph<T>::GetNodeCount()
{
    return _nodes.GetSize();
}

template <class T>
int Graph<T>::GetEdgeCount()
{
    return _edges.GetSize();
}

template <class T>
void Graph<T>::ResetVisited()
{
    for (int i = 0; i < _nodes.GetSize(); i++)
    {
        _nodes.GetAt(i)->SetVisited(false);
    }

    for (int i = 0; i < _edges.GetSize(); i++)
    {
        _edges.GetAt(i)->SetVisited(false);
    }
}

template <class T>
void Graph<T>::DFS(LinkedList<T>& resultado)
{
    ResetVisited();
    for (int i = 0; i < _nodes.GetSize(); i++)
    {
        Node<T>* actual = _nodes.GetAt(i);
        if (actual != nullptr && actual->GetVisited() == false)
        {
            DFSRec(actual,resultado)
        }
    }
}

template <class T>
void Graph<T>::DFSRec(Node<T>* n, LinkedList<T>& resultado)
{
    if (n == nullptr)
    {
        return;
    }

    n->SetVisited(true);
    resultado.Add(n->GetValue());

    for (int i = 0; i < n->GetNeighborCount(); i++)
    {
        Edge<T>* arista = n->GetNeighbor(i);

        if (arista == nullptr)
        {
            continue;
        }

        Node<T>* vecino = arista->GetFrom();

        if (vecino == n)
        {
            vecino = arista->GetTo();
        }

        if (vecino != nullptr && vecino->GetVisited() == false)
        {
            arista->SetVisited(true);
            DFSRec(vecino, resultado);
        }
    }
}

template <class T>
void Graph<T>::BFS(LinkedList<T>& resultado)
{
    ResetVisited();

    for (int i = 0; i < _nodes.GetSize(); i++)
    {
        Node<T>* inicio = _nodes.GetAt(i);

        if (inicio == nullptr || inicio->GetVisited() == true)
        {
            continue;
        }

        LinkedQueue<Node<T>*> pendientes;

        inicio->SetVisited(true);
        pendientes.Enqueue(inicio);

        while (pendientes.IsEmpty() == false)
        {
            Node<T>* actual = pendientes.Dequeue();
            resultado.Add(actual->GetValue());

            for (int j = 0; j < actual->GetNeighborCount(); j++)
            {
                Edge<T>* arista = actual->GetNeighbor(j);

                if (arista == nullptr)
                {
                    continue;
                }

                Node<T>* vecino = arista->GetFrom();

                if (vecino == actual)
                {
                    vecino = arista->GetTo();
                }

                if (vecino != nullptr && vecino->GetVisited() == false)
                {
                    vecino->SetVisited(true);
                    arista->SetVisited(true);
                    pendientes.Enqueue(vecino);
                }
            }
        }
    }
}

template <class T>
void Graph<T>::Print()
{
    onsoleUI::PrintTitle("GRAFO", 40);

    if (_nodes.GetSize() == 0)
    {
        ConsoleUI::PrintColor("(grafo vacio)", ConsoleUI::COLOR_AMARILLO);
        return;
    }

    for (int i = 0; i < _nodes.GetSize(); i++)
    {
        Node<T>* actual = _nodes.GetAt(i);

        std::ostringstream linea;
        linea << actual->GetValue() << " -> ";

        if (actual->GetNeighborCount() == 0)
        {
            linea << "(sin conexiones)";
        }

        for (int j = 0; j < actual->GetNeighborCount(); j++)
        {
            Edge<T>* arista = actual->GetNeighbor(j);
            Node<T>* vecino = arista->GetFrom();

            if (vecino == actual)
            {
                vecino = arista->GetTo();
            }

            linea << vecino->GetValue();

            if (j < actual->GetNeighborCount() - 1)
            {
                linea << ", ";
            }
        }

        ConsoleUI::PrintColor(linea.str(), ConsoleUI::COLOR_CYAN);
    }

    ConsoleUI::PrintSeparator();

    std::ostringstream resumen;
    resumen << "Nodos: " << GetNodeCount() << "   Aristas: " << GetEdgeCount();
    ConsoleUI::PrintColor(resumen.str(), ConsoleUI::COLOR_BLANCO);
}
