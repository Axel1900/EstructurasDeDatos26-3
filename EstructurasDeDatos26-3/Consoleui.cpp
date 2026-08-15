#include "ConsoleUI.h"
#include <iostream>
#include <cstdlib>

const int ConsoleUI::COLOR_RESET = 0;
const int ConsoleUI::COLOR_ROJO = 31;
const int ConsoleUI::COLOR_VERDE = 32;
const int ConsoleUI::COLOR_AMARILLO = 33;
const int ConsoleUI::COLOR_AZUL = 34;
const int ConsoleUI::COLOR_MAGENTA = 35;
const int ConsoleUI::COLOR_CYAN = 36;
const int ConsoleUI::COLOR_BLANCO = 37;


void ConsoleUI::PrintTitle(std::string texto)
{
	int ancho = (int)texto.length();
	PrintTitle(texto, ancho);
}

void ConsoleUI::PrintTitle(std::string texto, int ancho)
{
	if ((int)texto.length() > ancho)
	{
		ancho = (int)texto.length();
	}

	for (int i = 0; i < ancho; i++)
	{
		std::cout << "=";
	}
	std::cout << std::endl;

	std::cout << texto << std::endl;

	for (int i = 0; i < ancho; i++)
	{
		std::cout << "=";
	}
	std::cout << std::endl;
}

void ConsoleUI::PrintColor(std::string texto, int codigoColor)
{
	std::cout << "\033[" << codigoColor << "m" << texto << "\033[" << COLOR_RESET << "m" << std::endl;
}

void ConsoleUI::PrintSuccess(std::string texto)
{
	PrintColor(texto, COLOR_VERDE);
}

void ConsoleUI::PrintError(std::string texto)
{
	PrintColor(texto, COLOR_ROJO);
}

void ConsoleUI::PrintSeparator()
{
	std::cout << "----------------------------------------" << std::endl;
}

void ConsoleUI::PrintList(int* arreglo, int tamanio)
{
	for (int i = 0; i < tamanio; i++)
	{
		std::cout << "[" << i << "] " << arreglo[i] << std::endl;
	}
}

void ConsoleUI::Pause()
{
	std::cout << std::endl << "presiona una tecla para continuar...";
	system("pause");
}

void ConsoleUI::ClearScreen()
{
	system("cls");
}