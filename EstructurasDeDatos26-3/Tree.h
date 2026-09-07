#pragma once
#include "LinkedList.h"
#include "Stack.h"
#include "LinkedQueue.h"
#include "ConsoleUI.h"
#include <sstream>

// =====================================================================
//  Tree<T>  -  Arbol binario de busqueda (BST)
//
//  La regla del BST: todo lo MENOR que un nodo vive a su izquierda,
//  todo lo MAYOR vive a su derecha. Gracias a esa regla, buscar no
//  recorre todo: en cada nodo descartas la mitad del arbol.
//
//  LOS RECORRIDOS no imprimen: LLENAN una LinkedList<T> que se les
//  pasa por referencia. Asi el recorrido queda separado de como se
//  muestra, y ademas se puede verificar automaticamente.
//
//  Los tres recorridos DFS recursivos son LAS MISMAS TRES LINEAS con
//  la linea de "agregar al resultado" en distinto lugar:
//      Pre-orden:   nodo,        izquierda,   derecha
//      In-orden:    izquierda,   nodo,        derecha    <- sale ORDENADO
//      Post-orden:  izquierda,   derecha,     nodo
//  Escribe uno, y los otros dos son mover una linea.
// =====================================================================

template <class T>
class Tree
{
private:
    struct Node
    {
        T data;
        Node* left;
        Node* right;
    };

    Node* _root;
    int _size;

    // Auxiliares recursivas. Reciben el nodo actual porque la recursion
    // necesita "bajar", y desde afuera nadie ve los nodos.
    void DestruirRec(Node* n);
    void InsertRec(Node*& n, T valor);
    bool ContainsRec(Node* n, T valor);
    int  AlturaRec(Node* n);

    void PreRec(Node* n, LinkedList<T>& resultado);
    void InRec(Node* n, LinkedList<T>& resultado);
    void PostRec(Node* n, LinkedList<T>& resultado);
    void NivelRec(Node* n, int nivel, LinkedList<T>& resultado);

public:
    Tree();
    ~Tree();

    void Insert(T valor);
    bool Contains(T valor);
    int GetSize();
    int GetAltura();
    void Print();

    // --- DFS recursivos ---
    void PreOrden(LinkedList<T>& resultado);
    void InOrden(LinkedList<T>& resultado);
    void PostOrden(LinkedList<T>& resultado);

    // --- DFS iterativo (usa TU Stack) ---
    void InOrdenIterativo(LinkedList<T>& resultado);

    // --- BFS ---
    void PorNiveles(LinkedList<T>& resultado);            // usa TU LinkedQueue
    void PorNivelesRecursivo(LinkedList<T>& resultado);   // sin cola
};

template <class T>
Tree<T>::Tree()
{
    _root = nullptr;
    _size = 0;
}

template <class T>
Tree<T>::~Tree()
{
    DestruirRec(_root);
}

template <class T>
void Tree<T>::DestruirRec(Node* n)
{
    if (n == nullptr)
        return;

    DestruirRec(n->left);
    DestruirRec(n->right);
    delete n;
}

template <class T>
void Tree<T>::Insert(T valor)
{
    InsertRec(_root, valor);
}

template <class T>
void Tree<T>::InsertRec(Node*& n, T valor)
{
    if (n == nullptr)
    {
        n = new Node();
        n->data = valor;
        n->left = nullptr;
        n->right = nullptr;
        _size++;
        return;
    }

    if (valor < n->data)
        InsertRec(n->left, valor);
    else if (valor > n->data)
        InsertRec(n->right, valor);
}

template <class T>
bool Tree<T>::Contains(T valor)
{
    return ContainsRec(_root, valor);
}

template <class T>
bool Tree<T>::ContainsRec(Node* n, T valor)
{
    if (n == nullptr)
        return false;

    if (valor == n->data)
        return true;

    if (valor < n->data)
        return ContainsRec(n->left, valor);

    return ContainsRec(n->right, valor);
}

template <class T>
int Tree<T>::GetSize()
{
    return _size;
}

template <class T>
int Tree<T>::GetAltura()
{
    return AlturaRec(_root);
}

template <class T>
int Tree<T>::AlturaRec(Node* n)
{
    if (n == nullptr)
        return 0;

    int izquierda = AlturaRec(n->left);
    int derecha = AlturaRec(n->right);

    return 1 + (izquierda > derecha ? izquierda : derecha);
}

template <class T>
void Tree<T>::PreOrden(LinkedList<T>& resultado)
{
    PreRec(_root, resultado);
}

template <class T>
void Tree<T>::PreRec(Node* n, LinkedList<T>& resultado)
{
    if (n == nullptr)
        return;

    resultado.Add(n->data);
    PreRec(n->left, resultado);
    PreRec(n->right, resultado);
}

template <class T>
void Tree<T>::InOrden(LinkedList<T>& resultado)
{
    InRec(_root, resultado);
}

template <class T>
void Tree<T>::InRec(Node* n, LinkedList<T>& resultado)
{
    if (n == nullptr)
        return;

    InRec(n->left, resultado);
    resultado.Add(n->data);
    InRec(n->right, resultado);
}

template <class T>
void Tree<T>::PostOrden(LinkedList<T>& resultado)
{
    PostRec(_root, resultado);
}

template <class T>
void Tree<T>::PostRec(Node* n, LinkedList<T>& resultado)
{
    if (n == nullptr)
        return;

    PostRec(n->left, resultado);
    PostRec(n->right, resultado);
    resultado.Add(n->data);
}

template <class T>
void Tree<T>::InOrdenIterativo(LinkedList<T>& resultado)
{
    Stack<Node*> pila;
    Node* actual = _root;

    while (actual != nullptr || !pila.IsEmpty())
    {
        while (actual != nullptr)
        {
            pila.Push(actual);
            actual = actual->left;
        }

        actual = pila.Pop();
        resultado.Add(actual->data);
        actual = actual->right;
    }
}

template <class T>
void Tree<T>::PorNiveles(LinkedList<T>& resultado)
{
    // TODO: BFS con TU LinkedQueue<Node*>.
    //
    // Mete la raiz a la cola. Mientras la cola no este vacia:
    // saca uno, agregalo al resultado, y encola a sus hijos
    // (primero el izquierdo, luego el derecho).
    //
    // Fijate: es el MISMO algoritmo que el de arriba, pero cambiando
    // la pila por una cola. Eso solito convierte un DFS en un BFS.
}

template <class T>
void Tree<T>::PorNivelesRecursivo(LinkedList<T>& resultado)
{
    // TODO: el mismo resultado que PorNiveles, pero SIN cola.
    //
    // Estrategia: pide la altura del arbol, y luego, para cada nivel
    // del 1 hasta la altura, baja recursivamente y agrega solo los
    // nodos de ESE nivel.
    //
    // Va a ser mas lento que la version con cola: los nodos de arriba
    // se vuelven a recorrer una vez por cada nivel que hay debajo.
    // Compara las dos versiones y piensa por que.
}

template <class T>
void Tree<T>::NivelRec(Node* n, int nivel, LinkedList<T>& resultado)
{
    // TODO: si nivel == 1, este nodo es de los que van al resultado.
    //       Si no, baja a los dos hijos pidiendo el nivel de abajo.
}

template <class T>
void Tree<T>::Print()
{
    LinkedList<T> resultado;
    InRec(_root, resultado);

    for (int i = 0; i < resultado.GetSize(); i++)
    {
        std::ostringstream ss;
        ss << resultado.GetAt(i);
        ConsoleUI::PrintColor(ss.str(), ConsoleUI::COLOR_VERDE);
    }
    ConsoleUI::PrintSeparator();
}
