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
    // TODO: liberar TODAS las aristas y TODOS los nodos, recorriendo las
    // dos listas del grafo. Una sola vez cada cosa.
}

template <class T>
Node<T>* Graph<T>::AddNode(T valor)
{
    // TODO: crear el nodo, guardarlo en _nodes, y regresarlo para que
    // quien lo pidio pueda usarlo (por ejemplo, para conectarlo).
    return nullptr;
}

template <class T>
void Graph<T>::AddEdge(Node<T>* a, Node<T>* b)
{
    // TODO: 1) validar que ninguno de los dos sea nullptr
    //       2) crear la arista y guardarla en _edges
    //       3) agregarla a la lista de vecinos de AMBOS nodos
    //          (es un grafo NO dirigido: la conexion va en los dos
    //           sentidos, y es LA MISMA arista, no una copia)
}

template <class T>
int Graph<T>::GetNodeCount()
{
    // TODO
    return 0;
}

template <class T>
int Graph<T>::GetEdgeCount()
{
    // TODO
    return 0;
}

template <class T>
void Graph<T>::ResetVisited()
{
    // TODO: poner en false el _visited de todos los nodos y de todas
    // las aristas.
}

template <class T>
void Graph<T>::DFS(LinkedList<T>& resultado)
{
    // TODO: 1) llamar a ResetVisited() PRIMERO. Si no lo haces, correr
    //          el recorrido dos veces te da vacio la segunda vez. Es el
    //          mismo error que ya cazaste con el Flood Fill.
    //
    //       2) recorrer TU LISTA de nodos y, por cada nodo que siga sin
    //          visitar, arrancar una nueva exploracion con DFSRec.
    //
    //          Esto ultimo es lo que hace que funcione con grafos
    //          DESCONECTADOS. Si solo arrancas desde el primer nodo, un
    //          grafo con dos islas te deja la mitad sin visitar.
}

template <class T>
void Graph<T>::DFSRec(Node<T>* n, LinkedList<T>& resultado)
{
    // TODO: marcar el nodo como visitado, agregar su valor al resultado,
    // y recorrer sus aristas.
    //
    // OJO con esto: en un grafo no dirigido, la arista por la que
    // llegaste tambien aparece en la lista del nodo actual. Al seguir
    // una arista tienes que preguntar cual de sus dos extremos NO es el
    // nodo en el que estas parado. Ese es el paso que mas se olvida.
    //
    // Marca el nodo como visitado en cuanto ENTRAS a el, no al salir.
    // Si lo marcas tarde, un ciclo te manda a un bucle infinito.
}

template <class T>
void Graph<T>::BFS(LinkedList<T>& resultado)
{
    // TODO: recorrido en anchura usando TU LinkedQueue<Node<T>*>.
    //
    // Mete el nodo inicial a la cola. Mientras la cola no este vacia:
    // saca uno, agrega su valor al resultado, y encola a los vecinos que
    // no hayan sido visitados.
    //
    // Marca al vecino como visitado EN EL MOMENTO DE ENCOLARLO, no
    // cuando lo saques. Si esperas a sacarlo, el mismo nodo puede
    // entrar dos veces a la cola y aparecer repetido.
    //
    // Igual que en DFS: ResetVisited() al inicio, y recorre tu lista de
    // nodos para cubrir los grafos desconectados.
    //
    // Cuando termines, compara este metodo con DFSRec: es practicamente
    // el mismo algoritmo, y lo unico que cambia es donde guardas los
    // pendientes. Pila = profundidad. Cola = anchura.
}

template <class T>
void Graph<T>::Print()
{
    // TODO: imprimir cada nodo y a quienes esta conectado, usando
    // ConsoleUI.
}