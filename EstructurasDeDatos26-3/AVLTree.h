#pragma once
#include "LinkedList.h"
#include "ConsoleUI.h"

// =====================================================================
//  AVLTree<T>  -  Arbol binario de busqueda BALANCEADO
//
//  Es el mismo BST de la practica 5, con una regla de mas: despues de
//  cada insercion, si alguna parte del arbol quedo demasiado cargada
//  hacia un lado, el arbol se reacomoda solo con una ROTACION.
//
//  EL FACTOR DE BALANCE de un nodo es:
//      altura(subarbol izquierdo) - altura(subarbol derecho)
//  Un nodo esta bien si vale -1, 0 o 1. En cuanto vale 2 o -2, ese nodo
//  esta desbalanceado y hay que corregirlo.
//
//  CONVENCION DE ALTURAS (respetala, las pruebas la asumen):
//      un nodo nulo mide 0
//      un nodo hoja mide 1
//  La mayoria de los errores de "se me desbalancea solo" salen de
//  mezclar convenciones a medio camino.
//
//  ---------------------------------------------------------------
//  UN CAMBIO DE PATRON RESPECTO A LA PRACTICA 5
//
//  En tu Tree usaste:      void InsertRec(Node*& n, T valor);
//  Aqui vas a usar:        Node* InsertRec(Node* n, T valor);
//
//  El cambio no es capricho. Una rotacion cambia CUAL nodo es la raiz
//  de ese subarbol: el que estaba arriba baja, y uno de sus hijos sube
//  a ocupar su lugar. Entonces cada llamada recursiva tiene que poder
//  decirle a su padre "despues de acomodarme, ahora el jefe de este
//  subarbol es este otro nodo".
//
//  El patron es: cada funcion recibe la raiz actual del subarbol, hace
//  lo suyo, y REGRESA la raiz que quedo. El padre guarda ese resultado:
//
//      n->left = InsertRec(n->left, valor);
//
//  Las rotaciones y Balancear usan el mismo patron. Cuando lo entiendas,
//  el codigo del AVL se vuelve sorprendentemente corto.
// =====================================================================

template <class T>
class AVLTree
{
private:
    struct Node
    {
        T data;
        Node* left;
        Node* right;
        int height;      // la altura de ESTE subarbol
    };

    Node* _root;
    int _size;

    // --- auxiliares de altura y balance ---
    int Altura(Node* n);
    int FactorBalance(Node* n);
    void ActualizarAltura(Node* n);

    // --- las rotaciones ---
    Node* RotarDerecha(Node* n);
    Node* RotarIzquierda(Node* n);
    Node* Balancear(Node* n);

    // --- auxiliares recursivas ---
    Node* InsertRec(Node* n, T valor);
    bool ContainsRec(Node* n, T valor);
    void InRec(Node* n, LinkedList<T>& resultado);
    void DestruirRec(Node* n);
    bool BalanceadoRec(Node* n);

public:
    AVLTree();
    ~AVLTree();

    void Insert(T valor);
    bool Contains(T valor);
    int GetSize();
    int GetAltura();
    bool EstaBalanceado();
    void InOrden(LinkedList<T>& resultado);
    void Print();
};


template <class T>
AVLTree<T>::AVLTree()
{
    _root = nullptr;
    _size = 0;
}

template <class T>
AVLTree<T>::~AVLTree()
{
    DestruirRec(_root);
    _root = nullptr;
    _size = 0;
}

template <class T>
void AVLTree<T>::DestruirRec(Node* n)
{
    if (n == nullptr)
    {
        return;
    }
    DestruirRec(n->left);
    DestruirRec(n->right);
    delete n;
}


// ---------------------------------------------------------------------
//  ALTURA Y BALANCE
//
//  Empieza por aqui. Sin estas tres, no puedes programar nada mas.
// ---------------------------------------------------------------------

template <class T>
int AVLTree<T>::Altura(Node* n)
{
    if (n == nullptr)
    {
        return 0;
    }
    return n->height;
}

template <class T>
int AVLTree<T>::FactorBalance(Node* n)
{
    if (n == nullptr)
    {
        return;
    }
    return Altura(n->left) - Altura(n->right);
    
}

template <class T>
void AVLTree<T>::ActualizarAltura(Node* n)
{
    if (n == nullptr)
    {
        return;
    }
    int izquierda = Altura(n->left);
    int Derecha = Altura(n->right);
    int temp = 0;
    if (izquierda > Derecha)
    {
        temp = izquierda;
    }
    else
    {
        temp = Derecha;
    }
    n->height = temp + 1;       //+1 para contar este nodo
}


// ---------------------------------------------------------------------
//  LAS ROTACIONES
//
//  Aqui esta el corazon de la practica, y es la parte que te toca
//  investigar. Apoyate en el visualizador de VisuAlgo: puedes insertar
//  valores y ver las rotaciones ocurrir paso a paso.
//
//  DIBUJALAS EN PAPEL ANTES DE PROGRAMARLAS. Tres nodos y sus
//  subarboles. Una rotacion mueve exactamente dos punteros y despues
//  actualiza dos alturas. Si no la puedes dibujar, no la vas a poder
//  programar.
// ---------------------------------------------------------------------

template <class T>
typename AVLTree<T>::Node* AVLTree<T>::RotarDerecha(Node* n)
{
    Node* newRoot = n->left;
    Node* childNode = newRoot->right;

    newRoot->right = n;
    n->left = childNode;
    
    ActualizarAltura(n);
    ActualizarAltura(newRoot);

    return newRoot;
}

template <class T>
typename AVLTree<T>::Node* AVLTree<T>::RotarIzquierda(Node* n)
{
    Node* newRoot = n->right;
    Node* childNode = newRoot->left;

    newRoot->left = n;
    n->right = childNode;

    ActualizarAltura(n);
    ActualizarAltura(newRoot);

    return newRoot;
}

template <class T>
typename AVLTree<T>::Node* AVLTree<T>::Balancear(Node* n)
{
    if (n == nullptr)
    {
        return nullptr;
    }
    ActualizarAltura(n);

    int factor = FactorBalance(n);

    if (factor > 1)
    {
        if (FactorBalance(n->left) < 0)
        {
            n->left = RotarIzquierda(n->left);
        }

        return RotarDerecha(n);
    }

    if (factor < -1)
    {
        if (FactorBalance(n->right) > 0)
        {
            n->right = RotarDerecha(n->right);
        }

        return RotarIzquierda(n);
    }

    return n;
}


// ---------------------------------------------------------------------
//  INSERCION
// ---------------------------------------------------------------------

template <class T>
void AVLTree<T>::Insert(T valor)
{
    // TODO: arrancar la recursion y GUARDAR el resultado en _root.
    // Ese "guardar" es importante: si la raiz rota, _root cambia.
}

template <class T>
typename AVLTree<T>::Node* AVLTree<T>::InsertRec(Node* n, T valor)
{
    // TODO: la estructura es la misma de tu BST (bajar a la izquierda o
    // a la derecha segun la comparacion, no admitir duplicados), con dos
    // diferencias:
    //
    //   1. Guarda el resultado de la llamada recursiva:
    //          n->left = InsertRec(n->left, valor);
    //
    //   2. Al REGRESAR de la recursion, llama a Balancear(n) y regresa
    //      lo que te de.
    //
    // Ese "al regresar" es lo mismo que ya hiciste con PrintReverse y
    // con el post-orden: la accion ocurre cuando la recursion se
    // devuelve, no cuando baja.
    //
    // El nodo nuevo nace con altura 1.
    return n;
}


// ---------------------------------------------------------------------
//  CONSULTA
// ---------------------------------------------------------------------

template <class T>
bool AVLTree<T>::Contains(T valor)
{
    ContainsRec(valor);
    return false;
}

template <class T>
bool AVLTree<T>::ContainsRec(Node* n, T valor)
{
    // TODO: igual que en tu BST. El balanceo no cambia como se busca,
    // solo garantiza que la busqueda sea corta.
    return false;
}

template <class T>
int AVLTree<T>::GetSize()
{
    // TODO
    return _size;
}

template <class T>
int AVLTree<T>::GetAltura()
{
    // TODO: la altura del arbol completo.
    return Node::height;
}

template <class T>
bool AVLTree<T>::EstaBalanceado()
{
    // TODO
    return true;
}

template <class T>
bool AVLTree<T>::BalanceadoRec(Node* n)
{
    // TODO: un nodo nulo esta balanceado. Si no, su factor debe estar
    // entre -1 y 1, Y sus dos hijos tambien deben estar balanceados.
    //
    // Esta funcion es tu DETECTOR: llamala despues de cada insercion
    // mientras depuras. En cuanto regrese false, la insercion que
    // acabas de hacer es la que rompio algo.
    return true;
}


// ---------------------------------------------------------------------
//  RECORRIDO Y SALIDA
// ---------------------------------------------------------------------

template <class T>
void AVLTree<T>::InOrden(LinkedList<T>& resultado)
{
    // TODO
}

template <class T>
void AVLTree<T>::InRec(Node* n, LinkedList<T>& resultado)
{
    // TODO: izquierda, nodo, derecha. En un arbol de busqueda sale
    // ordenado, y eso es tu mejor verificacion: si tu in-orden sale
    // desordenado, alguna rotacion esta moviendo un puntero al lado
    // equivocado.
}

template <class T>
void AVLTree<T>::Print()
{
    // TODO: usa el recorrido in-orden y ConsoleUI. Casi todo el trabajo
    // ya lo hiciste: aqui solo lo conectas.
}
