// =====================================================================
//  Tests_AVL.cpp  -  Pruebas del arbol AVL
//  Estructuras de Datos (GPD4402) - SAE Institute Mexico
// =====================================================================
//
//  OJO: este archivo NO lleva DOCTEST_CONFIG_IMPLEMENT.
//  Ese define ya vive en Tests.cpp y solo puede estar en UN archivo.
//
//  Grupo nuevo: "AVL"
//
//  NO modifiques este archivo. Es el contrato.
//
//  CONVENCION DE ALTURAS que usan estas pruebas:
//      un nodo nulo mide 0
//      un nodo hoja mide 1
//  Si eliges otra convencion, las pruebas van a fallar aunque tu arbol
//  este bien. Respeta esta.
//
// =====================================================================

#include "doctest.h"

#include "AVLTree.h"
#include "LinkedList.h"

#include <string>


TEST_SUITE("AVL")
{
    // -----------------------------------------------------------------
    //  Lo basico: sigue siendo un arbol binario de busqueda
    // -----------------------------------------------------------------

    TEST_CASE("Un arbol recien creado esta vacio y balanceado")
    {
        AVLTree<int> a;
        CHECK(a.GetSize() == 0);
        CHECK(a.GetAltura() == 0);
        CHECK(a.EstaBalanceado() == true);
    }

    TEST_CASE("Un arbol de un solo nodo mide 1 de altura")
    {
        AVLTree<int> a;
        a.Insert(50);
        CHECK(a.GetSize() == 1);
        CHECK(a.GetAltura() == 1);
    }

    TEST_CASE("Insert aumenta el tamanio")
    {
        AVLTree<int> a;
        a.Insert(50);
        a.Insert(30);
        a.Insert(70);
        CHECK(a.GetSize() == 3);
    }

    TEST_CASE("Insertar un valor repetido NO lo duplica")
    {
        AVLTree<int> a;
        a.Insert(50);
        a.Insert(50);
        CHECK(a.GetSize() == 1);
    }

    TEST_CASE("Contains encuentra lo que esta y no lo que no esta")
    {
        AVLTree<int> a;
        a.Insert(50);
        a.Insert(30);
        a.Insert(70);
        a.Insert(20);

        CHECK(a.Contains(50) == true);
        CHECK(a.Contains(20) == true);
        CHECK(a.Contains(99) == false);
    }

    TEST_CASE("InOrden sale ordenado de menor a mayor")
    {
        AVLTree<int> a;
        a.Insert(50); a.Insert(30); a.Insert(70);
        a.Insert(20); a.Insert(40); a.Insert(80);

        LinkedList<int> r;
        a.InOrden(r);

        CHECK(r.GetSize() == 6);
        CHECK(r.GetAt(0) == 20);
        CHECK(r.GetAt(1) == 30);
        CHECK(r.GetAt(2) == 40);
        CHECK(r.GetAt(3) == 50);
        CHECK(r.GetAt(4) == 70);
        CHECK(r.GetAt(5) == 80);
    }


    // -----------------------------------------------------------------
    //  LOS CUATRO CASOS DE DESBALANCE
    //
    //  Cada uno se reproduce con TRES nodos. Son los escenarios mas
    //  chiquitos posibles para depurar cada rotacion.
    //
    //  Sin rotacion, los tres nodos quedan en linea y la altura seria 3.
    //  Con la rotacion correcta, el arbol queda parejo y mide 2.
    // -----------------------------------------------------------------

    TEST_CASE("Caso DERECHA-DERECHA (insertar 1, 2, 3)")
    {
        AVLTree<int> a;
        a.Insert(1);
        a.Insert(2);
        a.Insert(3);

        CHECK(a.GetAltura() == 2);          // sin rotar seria 3
        CHECK(a.EstaBalanceado() == true);

        LinkedList<int> r;
        a.InOrden(r);
        CHECK(r.GetAt(0) == 1);
        CHECK(r.GetAt(1) == 2);
        CHECK(r.GetAt(2) == 3);
    }

    TEST_CASE("Caso IZQUIERDA-IZQUIERDA (insertar 3, 2, 1)")
    {
        AVLTree<int> a;
        a.Insert(3);
        a.Insert(2);
        a.Insert(1);

        CHECK(a.GetAltura() == 2);
        CHECK(a.EstaBalanceado() == true);

        LinkedList<int> r;
        a.InOrden(r);
        CHECK(r.GetAt(0) == 1);
        CHECK(r.GetAt(1) == 2);
        CHECK(r.GetAt(2) == 3);
    }

    TEST_CASE("Caso IZQUIERDA-DERECHA (insertar 3, 1, 2)")
    {
        // Este NO se arregla con una sola rotacion.
        AVLTree<int> a;
        a.Insert(3);
        a.Insert(1);
        a.Insert(2);

        CHECK(a.GetAltura() == 2);
        CHECK(a.EstaBalanceado() == true);

        LinkedList<int> r;
        a.InOrden(r);
        CHECK(r.GetAt(0) == 1);
        CHECK(r.GetAt(1) == 2);
        CHECK(r.GetAt(2) == 3);
    }

    TEST_CASE("Caso DERECHA-IZQUIERDA (insertar 1, 3, 2)")
    {
        // Este tampoco se arregla con una sola rotacion.
        AVLTree<int> a;
        a.Insert(1);
        a.Insert(3);
        a.Insert(2);

        CHECK(a.GetAltura() == 2);
        CHECK(a.EstaBalanceado() == true);

        LinkedList<int> r;
        a.InOrden(r);
        CHECK(r.GetAt(0) == 1);
        CHECK(r.GetAt(1) == 2);
        CHECK(r.GetAt(2) == 3);
    }


    // -----------------------------------------------------------------
    //  LA RAZON DE SER DEL AVL
    //
    //  Estas son las pruebas que separan un AVL de un BST cualquiera.
    // -----------------------------------------------------------------

    TEST_CASE("Insertar 1 al 15 en orden creciente NO degenera el arbol")
    {
        // Un BST normal quedaria con altura 15 (una lista con pasos
        // extra). El AVL se queda en 4.
        AVLTree<int> a;
        for (int i = 1; i <= 15; i++) a.Insert(i);

        CHECK(a.GetSize() == 15);
        CHECK(a.GetAltura() == 4);
        CHECK(a.EstaBalanceado() == true);
    }

    TEST_CASE("Insertar 15 al 1 en orden decreciente tampoco lo degenera")
    {
        AVLTree<int> a;
        for (int i = 15; i >= 1; i--) a.Insert(i);

        CHECK(a.GetSize() == 15);
        CHECK(a.GetAltura() == 4);
        CHECK(a.EstaBalanceado() == true);
    }

    TEST_CASE("El arbol sigue balanceado DESPUES DE CADA insercion")
    {
        // No basta con que quede balanceado al final: la propiedad se
        // mantiene en todo momento. Si esta prueba falla en algun paso,
        // ese es el numero que rompio tu rebalanceo.
        AVLTree<int> a;
        for (int i = 1; i <= 30; i++)
        {
            a.Insert(i);
            CHECK(a.EstaBalanceado() == true);
        }
    }

    TEST_CASE("Las rotaciones NO alteran el orden de los datos")
    {
        // Reacomodan la FORMA del arbol, pero sigue siendo un arbol
        // binario de busqueda valido. Si tu in-orden sale desordenado,
        // alguna rotacion esta moviendo un puntero al lado equivocado.
        AVLTree<int> a;
        int valores[10] = { 50, 20, 80, 10, 30, 60, 90, 5, 25, 35 };
        for (int i = 0; i < 10; i++) a.Insert(valores[i]);

        LinkedList<int> r;
        a.InOrden(r);

        CHECK(r.GetSize() == 10);
        for (int i = 1; i < r.GetSize(); i++)
        {
            CHECK(r.GetAt(i - 1) < r.GetAt(i));
        }
    }

    TEST_CASE("Con 100 elementos secuenciales la altura se mantiene chica")
    {
        // Un BST normal llegaria a 100. El AVL se queda en un puñado.
        AVLTree<int> a;
        for (int i = 1; i <= 100; i++) a.Insert(i);

        CHECK(a.GetSize() == 100);
        CHECK(a.GetAltura() <= 8);
        CHECK(a.EstaBalanceado() == true);
    }

    TEST_CASE("Todo lo insertado se puede volver a encontrar")
    {
        // Una rotacion mal hecha puede dejar nodos colgando fuera del
        // arbol: siguen existiendo en memoria, pero ya no se alcanzan.
        AVLTree<int> a;
        for (int i = 1; i <= 50; i++) a.Insert(i);

        for (int i = 1; i <= 50; i++)
        {
            CHECK(a.Contains(i) == true);
        }
        CHECK(a.Contains(51) == false);
        CHECK(a.Contains(0) == false);
    }

    TEST_CASE("El in-orden conserva TODOS los elementos insertados")
    {
        AVLTree<int> a;
        for (int i = 1; i <= 20; i++) a.Insert(i);

        LinkedList<int> r;
        a.InOrden(r);

        CHECK(r.GetSize() == 20);
        for (int i = 0; i < 20; i++)
        {
            CHECK(r.GetAt(i) == i + 1);
        }
    }


    // -----------------------------------------------------------------
    //  Casos limite y genericidad
    // -----------------------------------------------------------------

    TEST_CASE("Los recorridos sobre un arbol vacio no truenan")
    {
        AVLTree<int> a;
        LinkedList<int> r;
        a.InOrden(r);
        CHECK(r.GetSize() == 0);
        CHECK(a.Contains(1) == false);
    }

    TEST_CASE("Dos nodos: no hace falta rotar")
    {
        AVLTree<int> a;
        a.Insert(2);
        a.Insert(1);

        CHECK(a.GetAltura() == 2);
        CHECK(a.EstaBalanceado() == true);
    }

    TEST_CASE("El AVL funciona con cualquier tipo de dato")
    {
        AVLTree<char> a;
        a.Insert('a');
        a.Insert('b');
        a.Insert('c');   // provoca una rotacion

        CHECK(a.GetAltura() == 2);
        CHECK(a.EstaBalanceado() == true);

        LinkedList<char> r;
        a.InOrden(r);
        CHECK(r.GetAt(0) == 'a');
        CHECK(r.GetAt(1) == 'b');
        CHECK(r.GetAt(2) == 'c');
    }

    TEST_CASE("El AVL tambien funciona con cadenas")
    {
        AVLTree<std::string> a;
        a.Insert("abeja");
        a.Insert("mono");
        a.Insert("zorro");

        CHECK(a.GetAltura() == 2);
        CHECK(a.Contains("mono") == true);
        CHECK(a.Contains("gato") == false);
    }
}
