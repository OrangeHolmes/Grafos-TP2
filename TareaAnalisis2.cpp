// TareaAnalisis2.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
#include <iostream>
#include "GrafoListas.h"

int main()
{
    std::cout << "Hello World!\n";
	ListaVertices grofo = ListaVertices();
	auto* a = grofo.agregarVertice("AnuelAA");
	auto* b = grofo.agregarVertice("BadBunny");
	auto* c = grofo.agregarVertice("Cmen");
	auto* d= grofo.agregarVertice("Danito");
	auto* ab = grofo.agregarArista(a,b,5);
	auto* ac = grofo.agregarArista(a, c, 2);
	auto* ad = grofo.agregarArista(a, d, 7);
	auto* ba = grofo.agregarArista(b, a, 1);
	grofo.imprimir(cout);
}