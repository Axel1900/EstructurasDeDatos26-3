#pragma once

// =====================================================================
//  Edge<T>  -  Arista de un grafo
//
//  Conecta dos nodos. Es la pieza mas simple de las tres, pero trae un
//  problema de C++ que hay que resolver antes de escribirla.
//
//  LA DEPENDENCIA CIRCULAR:
//  Edge necesita saber que existe Node (guarda punteros a nodos), y Node
//  necesita saber que existe Edge (guarda una lista de aristas). Si cada
//  archivo incluye al otro, el compilador entra en un ciclo infinito.
//
//  La solucion es la DECLARACION ADELANTADA de abajo: le dice al
//  compilador "confia en mi, esta clase existe". Con eso basta, porque
//  aqui solo guardamos PUNTEROS a Node: para declarar un puntero, el
//  compilador no necesita saber como esta hecho el tipo por dentro.
//
//  Regla general: si solo guardas punteros o referencias a un tipo,
//  basta con declararlo adelantado. Solo necesitas el #include completo
//  cuando vas a LLAMAR metodos de ese tipo o guardarlo por valor.
//
//  NO agregues #include "Node.h" en este archivo. Node.h incluye a
//  Edge.h, y si te devuelves el include, truena.
// =====================================================================

template <class T> class Node;   // declaracion adelantada

template <class T>
class Edge
{
private:
    Node<T>* _from;
    Node<T>* _to;
    bool _visited;

public:
    Edge();
    Edge(Node<T>* from, Node<T>* to);

    Node<T>* GetFrom();
    Node<T>* GetTo();
    void SetVisited(bool visitado);
    bool GetVisited();
};

template <class T>
Edge<T>::Edge()
{
    // Los punteros arrancan en nullptr. NO crees nodos aqui con 'new':
    // cada arista vacia dejaria dos nodos huerfanos que nadie libera.
    // En C# el recolector de basura te salvaba de eso; aqui es fuga.
    _from = nullptr;
    _to = nullptr;
    _visited = false;
}

template <class T>
Edge<T>::Edge(Node<T>* from, Node<T>* to)
{
    // TODO: guardar 'from' en _from y 'to' en _to, y _visited en false.
    //
    // Suena obvio, pero invertirlos es un error clasico. Y lo peor es
    // que en un grafo NO dirigido el error se ESCONDE: como los
    // recorridos revisan los dos extremos de todas formas, el programa
    // sigue funcionando. Hay una prueba dedicada a cazar esto.
}

template <class T>
Node<T>* Edge<T>::GetFrom()
{
    // TODO
    return nullptr;
}

template <class T>
Node<T>* Edge<T>::GetTo()
{
    // TODO
    return nullptr;
}

template <class T>
void Edge<T>::SetVisited(bool visitado)
{
    // TODO
}

template <class T>
bool Edge<T>::GetVisited()
{
    // TODO
    return false;
}