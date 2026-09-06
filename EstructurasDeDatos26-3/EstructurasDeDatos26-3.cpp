// =====================================================================
//  EstructurasDeDatos26-3.cpp
//  Estructuras de Datos (GPD4402) - SAE Institute Mexico
// =====================================================================

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "ConsoleUI.h"
#include "TNode.h"
#include "Stack.h"
#include "LinkedQueue.h"
#include "TwoStackQueue.h"
#include "LinkedList.h"
#include "Grid.h"
#include "Tests.h"

void MenuPruebas();
void DemoStack();
void DemoColas();
void DemoLista();
void DemoGrid();

int main()
{
    srand((unsigned int)time(NULL));

    int opcion = -1;

    do
    {
        std::cout << std::endl;
        ConsoleUI::PrintTitle("ESTRUCTURAS DE DATOS - LIBRERIA", 45);
        std::cout << "1.- Demo Stack" << std::endl;
        std::cout << "2.- Demo Colas (LinkedQueue vs TwoStackQueue)" << std::endl;
        std::cout << "3.- Demo Lista Ligada" << std::endl;
        std::cout << "4.- Demo Grid / Flood Fill" << std::endl;
        ConsoleUI::PrintSeparator();
        std::cout << "8.- Correr TODAS las pruebas" << std::endl;
        std::cout << "9.- Correr pruebas de un grupo" << std::endl;
        std::cout << "0.- Salir" << std::endl;
        std::cout << "Elige una opcion: ";

        std::cin >> opcion;

        // Si el usuario mete letras en lugar de numeros, cin se traba.
        // Estas lineas lo destraban.
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            opcion = -1;
        }

        switch (opcion)
        {
        case 1: DemoStack();  break;
        case 2: DemoColas();  break;
        case 3: DemoLista();  break;
        case 4: DemoGrid();   break;

        case 8: CorrerTodasLasPruebas(); break;
        case 9: MenuPruebas();           break;

        case 0:
            ConsoleUI::PrintSuccess("Hasta luego.");
            break;

        default:
            ConsoleUI::PrintError("Opcion invalida.");
            break;
        }

    } while (opcion != 0);

    return 0;
}

// =====================================================================
//  Submenu de pruebas
// =====================================================================
void MenuPruebas()
{
    int grupo = 0;

    std::cout << std::endl;
    ConsoleUI::PrintTitle("GRUPOS DE PRUEBAS");
    std::cout << "1.- Stack" << std::endl;
    std::cout << "2.- ReglaDeTres" << std::endl;
    std::cout << "3.- Queue" << std::endl;
    std::cout << "4.- LinkedList" << std::endl;
    std::cout << "5.- Recursividad" << std::endl;
    std::cout << "6.- Grid" << std::endl;
    std::cout << "7.- Memoria" << std::endl;
    std::cout << "8.- HashTable" << std::endl;
    std::cout << "9.- Tree" << std::endl;
    std::cout << "10.- Recorridos" << std::endl;
    std::cout << "Elige un grupo: ";
    std::cin >> grupo;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        ConsoleUI::PrintError("Opcion invalida.");
        return;
    }

    switch (grupo)
    {
    case 1: CorrerPruebasDe("Stack");        break;
    case 2: CorrerPruebasDe("ReglaDeTres");  break;
    case 3: CorrerPruebasDe("Queue");        break;
    case 4: CorrerPruebasDe("LinkedList");   break;
    case 5: CorrerPruebasDe("Recursividad"); break;
    case 6: CorrerPruebasDe("Grid");         break;
    case 7: CorrerPruebasDe("Memoria");      break;
    case 8:  CorrerPruebasDe("HashTable");  break;
    case 9:  CorrerPruebasDe("Tree");       break;
    case 10: CorrerPruebasDe("Recorridos"); break;
    default: ConsoleUI::PrintError("Grupo invalido."); break;
    }
}

// =====================================================================
//  Demos
// =====================================================================
void DemoStack()
{
    std::cout << std::endl;
    ConsoleUI::PrintTitle("DEMO STACK");

    Stack<int> pila;
    pila.Push(10);
    pila.Push(20);
    pila.Push(30);

    std::cout << "Contenido (del tope hacia abajo): ";
    pila.Print();

    std::cout << "Tamanio: " << pila.GetSize() << std::endl;
    std::cout << "Top:     " << pila.Top() << std::endl;
    std::cout << "Pop:     " << pila.Pop() << std::endl;
    std::cout << "Pop:     " << pila.Pop() << std::endl;
    std::cout << "Tamanio despues de 2 Pop: " << pila.GetSize() << std::endl;

    ConsoleUI::Pause();
}

void DemoColas()
{
    std::cout << std::endl;
    ConsoleUI::PrintTitle("DEMO COLAS");
    std::cout << "Las dos clases tienen la MISMA interfaz publica," << std::endl;
    std::cout << "aunque por dentro son completamente distintas." << std::endl;

    ConsoleUI::PrintSeparator();
    ConsoleUI::PrintColor("LinkedQueue:", ConsoleUI::COLOR_CYAN);
    LinkedQueue<int> colaA;
    colaA.Enqueue(1);
    colaA.Enqueue(2);
    colaA.Enqueue(3);
    std::cout << "  Contenido: ";
    colaA.Print();
    std::cout << "  Front:   " << colaA.Front() << std::endl;
    std::cout << "  Dequeue: " << colaA.Dequeue() << std::endl;
    std::cout << "  Dequeue: " << colaA.Dequeue() << std::endl;

    ConsoleUI::PrintSeparator();
    ConsoleUI::PrintColor("TwoStackQueue:", ConsoleUI::COLOR_MAGENTA);
    TwoStackQueue<int> colaB;
    colaB.Enqueue(1);
    colaB.Enqueue(2);
    colaB.Enqueue(3);
    std::cout << "  Contenido: ";
    colaB.Print();
    std::cout << "  Front:   " << colaB.Front() << std::endl;
    std::cout << "  Dequeue: " << colaB.Dequeue() << std::endl;
    std::cout << "  Dequeue: " << colaB.Dequeue() << std::endl;

    ConsoleUI::PrintSeparator();
    std::cout << "Si las dos imprimen lo mismo, las dos cumplen el contrato." << std::endl;

    ConsoleUI::Pause();
}

void DemoLista()
{
    std::cout << std::endl;
    ConsoleUI::PrintTitle("DEMO LISTA LIGADA");

    LinkedList<int> lista;
    lista.Add(5);
    lista.Add(2);
    lista.Add(8);
    lista.Add(1);

    std::cout << "Lista original:" << std::endl;
    lista.Print();

    std::cout << "Al reves: ";
    lista.PrintReverse();

    ConsoleUI::PrintSeparator();
    std::cout << "GetAt(2):            " << lista.GetAt(2) << std::endl;
    std::cout << "GetAtRecursivo(2):   " << lista.GetAtRecursivo(2) << std::endl;
    std::cout << "CountRecursivo():    " << lista.CountRecursivo() << std::endl;
    std::cout << "BuscarRecursivo(8):  " << lista.BuscarRecursivo(8) << std::endl;
    std::cout << "BuscarRecursivo(99): " << lista.BuscarRecursivo(99) << std::endl;
    ConsoleUI::PrintSeparator();

    // operator[] regresa referencia, por eso se puede ESCRIBIR
    lista[0] = 99;
    std::cout << "Despues de lista[0] = 99:" << std::endl;
    lista.Print();

    lista.SelectionSort();
    std::cout << "Con SelectionSort:" << std::endl;
    lista.Print();

    ConsoleUI::Pause();
}

void DemoGrid()
{
    std::cout << std::endl;
    ConsoleUI::PrintTitle("DEMO GRID / FLOOD FILL");
    std::cout << "Esta rejilla es el tablero de tu Match-3." << std::endl << std::endl;

    Grid<int> tablero(8, 8);

    for (int f = 0; f < tablero.GetFilas(); f++)
    {
        for (int c = 0; c < tablero.GetColumnas(); c++)
        {
            tablero.Set(f, c, rand() % 5 + 1);
        }
    }

    tablero.Print();

    int fila = 0;
    int columna = 0;

    std::cout << std::endl << "Fila a revisar (0 a 7): ";
    std::cin >> fila;
    std::cout << "Columna a revisar (0 a 7): ";
    std::cin >> columna;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        ConsoleUI::PrintError("Coordenada invalida.");
        return;
    }

    int conectadas = tablero.FloodFill(fila, columna);

    ConsoleUI::PrintSeparator();
    std::cout << "Valor en esa celda: " << tablero.Get(fila, columna) << std::endl;
    std::cout << "Celdas conectadas del mismo valor: " << conectadas << std::endl;

    if (conectadas >= 3)
    {
        ConsoleUI::PrintSuccess("Eso seria una combinacion valida en el Match-3.");
    }
    else
    {
        ConsoleUI::PrintColor("Muy pocas: no formaria combinacion.", ConsoleUI::COLOR_AMARILLO);
    }

    ConsoleUI::Pause();
}