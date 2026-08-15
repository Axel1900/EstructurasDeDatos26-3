#pragma once
#include <string>

class ConsoleUI
{
public:
	static const int COLOR_RESET;
	static const int COLOR_ROJO;
	static const int COLOR_VERDE;
	static const int COLOR_AMARILLO;
	static const int COLOR_AZUL;
	static const int COLOR_MAGENTA;
	static const int COLOR_CYAN;
	static const int COLOR_BLANCO;

	static void PrintTitle(std::string texto);
	static void PrintTitle(std::string texto, int ancho);
	static void PrintColor(std::string texto, int codigoColor);
	static void PrintSuccess(std::string texto);
	static void PrintError(std::string texto);
	static void PrintSeparator();
	static void PrintList(int* arreglo, int tamanio);
	static void Pause();
	static void ClearScreen();
};