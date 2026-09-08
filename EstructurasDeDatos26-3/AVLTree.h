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
    // TODO: llamar a DestruirRec desde la raiz
}

template <class T>
void AVLTree<T>::DestruirRec(Node* n)
{
    // TODO: destruir primero los hijos y HASTA EL FINAL el nodo actual.
    // Igual que en tu Tree: ese orden es el post-orden.
}


// ---------------------------------------------------------------------
//  ALTURA Y BALANCE
//
//  Empieza por aqui. Sin estas tres, no puedes programar nada mas.
// ---------------------------------------------------------------------

template <class T>
int AVLTree<T>::Altura(Node* n)
{
    // TODO: regresar la altura GUARDADA en el nodo, o 0 si es nulo.
    //
    // Fijate que NO la recalcula recorriendo el arbol: la lee del campo
    // height. Por eso es O(1), y por eso es tan importante mantener ese
    // campo actualizado.
    return 0;
}

template <class T>
int AVLTree<T>::FactorBalance(Node* n)
{
    // TODO: altura(izquierda) - altura(derecha). Un nodo nulo da 0.
    //
    // Positivo = cargado a la izquierda.
    // Negativo = cargado a la derecha.
    return 0;
}

template <class T>
void AVLTree<T>::ActualizarAltura(Node* n)
{
    // TODO: la altura de n es 1 mas que la del MAS ALTO de sus dos hijos.
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
    // TODO: el hijo izquierdo de n sube a ocupar su lugar, y n baja a
    // ser su hijo derecho. El subarbol que estorba se reacomoda.
    //
    // CUIDADO CON EL ORDEN DE LAS ALTURAS: primero actualiza la del nodo
    // que BAJO, despues la del que SUBIO. Si lo haces al reves, las
    // alturas quedan mal y el arbol se desbalancea sin que te des
    // cuenta. Este es EL error mas comun del AVL.
    //
    // Regresa el nodo que quedo arriba.
    return n;
}

template <class T>
typename AVLTree<T>::Node* AVLTree<T>::RotarIzquierda(Node* n)
{
    // TODO: el espejo exacto de RotarDerecha.
    return n;
}

template <class T>
typename AVLTree<T>::Node* AVLTree<T>::Balancear(Node* n)
{
    // TODO: actualiza la altura de n, calcula su factor de balance, y
    // si esta desbalanceado aplica la correccion que corresponda.
    //
    // Hay CUATRO casos, pero solo DOS rotaciones. Los otros dos casos
    // son combinaciones:
    //
    //   IZQUIERDA-IZQUIERDA (LL): n cargado a la izquierda, y su hijo
    //       izquierdo TAMBIEN cargado a la izquierda.
    //       -> una sola rotacion.
    //
    //   DERECHA-DERECHA (RR): el espejo del anterior.
    //       -> una sola rotacion, en el otro sentido.
    //
    //   IZQUIERDA-DERECHA (LR): n cargado a la izquierda, pero su hijo
    //       izquierdo cargado a la DERECHA. Una sola rotacion no lo
    //       arregla: lo deja desbalanceado del otro lado.
    //       -> DOS rotaciones.
    //
    //   DERECHA-IZQUIERDA (RL): el espejo del anterior.
    //       -> DOS rotaciones.
    //
    // Para distinguirlos necesitas el factor de balance de n Y el de su
    // hijo del lado cargado.
    //
    // Regresa el nodo que quedo arriba (si no hubo rotacion, es el mismo
    // que entro).
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
    // TODO
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
    return 0;
}

template <class T>
int AVLTree<T>::GetAltura()
{
    // TODO: la altura del arbol completo.
    return 0;
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
