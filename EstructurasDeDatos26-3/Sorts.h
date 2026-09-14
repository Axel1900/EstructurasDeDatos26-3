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

template <class T>
void Intercambiar(T& a, T& b)
{
    T temporal = a;
    a = b;
    b = temporal;
}

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
    int tamanio = fin - inicio + 1;
    T* temporal = new T[tamanio];

    int i = inicio;  
    int j = medio + 1;  
    int k = 0;        

    while (i <= medio && j <= fin)
    {
        if (arreglo[i] <= arreglo[j])
        {
            temporal[k] = arreglo[i];
            i++;
        }
        else
        {
            temporal[k] = arreglo[j];
            j++;
        }

        k++;
    }

    while (i <= medio)
    {
        temporal[k] = arreglo[i];
        i++;
        k++;
    }

    while (j <= fin)
    {
        temporal[k] = arreglo[j];
        j++;
        k++;
    }

    for (k = 0; k < tamanio; k++)
    {
        arreglo[inicio + k] = temporal[k];
    }

    delete[] temporal;
}

template <class T>
void MergeRec(T* arreglo, int inicio, int fin)
{
    if (inicio >= fin)
    {
        return;
    }

    int medio = inicio + (fin - inicio) / 2;

    MergeRec(arreglo, inicio, medio);
    MergeRec(arreglo, medio + 1, fin);
    Mezclar(arreglo, inicio, medio, fin);
}

template <class T>
void MergeSort(T* arreglo, int tamanio)
{
    if (arreglo == nullptr || tamanio < 2)
    {
        return;
    }

    MergeRec(arreglo, 0, tamanio - 1);
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
    T pivote = arreglo[fin];

    int menor = inicio - 1;

    for (int j = inicio; j < fin; j++)
    {
        if (arreglo[j] <= pivote)
        {
            menor++;
            Intercambiar(arreglo[menor], arreglo[j]);
        }
    }

    Intercambiar(arreglo[menor + 1], arreglo[fin]);

    return menor + 1;
}

template <class T>
void QuickRec(T* arreglo, int inicio, int fin)
{
    if (inicio >= fin)
    {
        return;
    }

    int posicionPivote = Particion(arreglo, inicio, fin);

    QuickRec(arreglo, inicio, posicionPivote - 1);
    QuickRec(arreglo, posicionPivote + 1, fin);
}

template <class T>
void QuickSort(T* arreglo, int tamanio)
{
    if (arreglo == nullptr || tamanio < 2)
    {
        return;
    }

    QuickRec(arreglo, 0, tamanio - 1);
}
