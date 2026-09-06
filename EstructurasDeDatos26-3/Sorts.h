#pragma once

// =====================================================================
//  Sorts.h  -  Ordenamientos de division (divide y venceras)
//
//  Estas son FUNCIONES LIBRES, no metodos de ninguna clase. No es un
//  capricho:
//
//  SelectionSort e InsertionSort SI viven dentro de LinkedList, porque
//  para funcionar necesitan caminar de nodo en nodo, o sea que necesitan
//  conocer las tripas de la lista.
//
//  MergeSort y QuickSort no necesitan nada de eso: solo necesitan una
//  secuencia de elementos que puedan comparar e intercambiar. Por eso el
//  mismo codigo, sin cambiar una linea, ordena enteros, caracteres o
//  cadenas, vengan de donde vengan.
//
//  La regla: si el algoritmo necesita saber como esta construida la
//  estructura por dentro, va adentro de la clase. Si solo necesita una
//  secuencia, va afuera como funcion libre.
//
//  Y de paso, ya sabes por que en la biblioteca estandar existe
//  std::sort como funcion libre y no vector::sort como metodo.
// =====================================================================


// ---------------------------------------------------------------------
//  MERGE SORT
//
//  1. Parte el arreglo a la mitad.
//  2. Ordena cada mitad (llamandose a si mismo).
//  3. Combina las dos mitades ordenadas en una sola.
//
//  Caso base: un arreglo de un solo elemento ya esta ordenado.
//  Todo el trabajo real esta en el paso 3.
// ---------------------------------------------------------------------

template <class T>
void Mezclar(T* arreglo, int inicio, int medio, int fin)
{
    // TODO: recibes DOS MITADES YA ORDENADAS dentro del mismo arreglo:
    //       de 'inicio' a 'medio', y de 'medio+1' a 'fin'.
    //       Tienes que producir un solo tramo ordenado.
    //
    // Ve comparando el primer elemento pendiente de cada mitad y toma el
    // menor. Cuando una mitad se acabe, copia lo que quede de la otra.
    //
    // Vas a necesitar un arreglo temporal. Acuerdate de liberarlo.
}

template <class T>
void MergeRec(T* arreglo, int inicio, int fin)
{
    // TODO: caso base, partir a la mitad, ordenar cada lado, mezclar.
}

template <class T>
void MergeSort(T* arreglo, int tamanio)
{
    // TODO: arrancar la recursion. Cuidado con el arreglo vacio.
}


// ---------------------------------------------------------------------
//  QUICK SORT
//
//  1. Escoge un elemento como PIVOTE.
//  2. Acomoda el arreglo para que todo lo menor al pivote quede a su
//     izquierda y todo lo mayor a su derecha (particion).
//  3. Ordena cada lado (llamandose a si mismo).
//
//  Fijate en la diferencia con Merge Sort: aquel divide facil y trabaja
//  al combinar. Este trabaja al dividir, y ya no necesita combinar nada,
//  porque despues de la particion cada lado quedo en su lugar.
// ---------------------------------------------------------------------

template <class T>
int Particion(T* arreglo, int inicio, int fin)
{
    // TODO: elige un pivote, acomoda los elementos a su alrededor, y
    // regresa la POSICION FINAL del pivote. Esa posicion es la que
    // separa los dos lados que hay que ordenar despues.
    //
    // Dibuja esto en papel con cinco numeros antes de programarlo. Es el
    // punto donde mas gente se atora.
    return inicio;
}

template <class T>
void QuickRec(T* arreglo, int inicio, int fin)
{
    // TODO: caso base, particionar, y ordenar los dos lados.
    // El pivote ya quedo en su lugar: no lo incluyas en ninguno de los
    // dos lados o te vas a ciclar para siempre.
}

template <class T>
void QuickSort(T* arreglo, int tamanio)
{
    // TODO: arrancar la recursion. Cuidado con el arreglo vacio.
}