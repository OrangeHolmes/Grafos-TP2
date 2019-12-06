#include <iostream>
#include <stdlib.h> //Para usar system("cls");
#include <conio.h> //Para usar _getch();
#include <unordered_set>

#include "GrafoListas.h"
//#include "GrafoMatriz.h"

using namespace std;
Grafo::vertice traducir(Grafo& g, string etiq) {
	Grafo::vertice actual = g.primerVertice();
	int seguir = 1;
	while (actual && seguir) {
		if (g.getEtiqueta(actual).compare(etiq)) { //Si es 0 son iguales 
			actual = g.siguienteVertice(actual);
		}
		else {
			seguir = 0;
		}
	}
	return actual;
}

//----- INICIO ALGORITMOS -----

//ii. Recorrido en Profundidad Primero para despliegue de etiquetas en pantalla.	-*-*- SIRVE
void profPrimeroR(Grafo& grafo, Grafo::vertice& actual, unordered_set<string>& dvv) {
	dvv.insert(grafo.getEtiqueta(actual));
	cout << grafo.getEtiqueta(actual);
	auto vAdy = grafo.primerVerticeAdyacente(actual);
	while (vAdy) {
		if (dvv.count(grafo.getEtiqueta(vAdy)) == 0) {
			profPrimeroR(grafo, vAdy, dvv);
		}
		vAdy = grafo.siguienteVerticeAdyacente(actual, vAdy);
	}
}
void profPrimero(Grafo& grafo) {
	if (!grafo.vacio()) {
		unordered_set<string> dvv;
		Grafo::vertice vertActual = grafo.primerVertice();
		while (vertActual) {
			if (dvv.count(grafo.getEtiqueta(vertActual)) == 0) {
				profPrimeroR(grafo, vertActual, dvv);
			}
			vertActual = grafo.siguienteVertice(vertActual);
		}
	}
}

//iii. Averiguar si un grafo tiene ciclos usando el Recorrido en Profundidad Primero		-*-*- NO SIRVE
int tieneCiclosR(Grafo& grafo, Grafo::vertice& actual, Grafo::vertice& inicial, unordered_set<string>& dvv) {
	int tieneCiclo = 0;
	dvv.insert(grafo.getEtiqueta(actual));
	auto vAdy = grafo.primerVerticeAdyacente(actual);
	while (vAdy) {
		if (vAdy == inicial) {
			++tieneCiclo;
		}
		if (dvv.count(grafo.getEtiqueta(vAdy)) == 0) {
			tieneCiclo += tieneCiclosR(grafo, vAdy, inicial, dvv);
		}
		vAdy = grafo.siguienteVerticeAdyacente(actual, vAdy);
	}
	return tieneCiclo;
}
int tieneCiclos(Grafo& g) {
	int tieneCiclos = 0;
	if (!g.vacio()) {
		unordered_set<string> dvv;
		Grafo::vertice vertActual = g.primerVertice();
		while (vertActual) {
			if (dvv.count(g.getEtiqueta(vertActual)) == 0)
			{
				tieneCiclos += tieneCiclosR(g, vertActual, vertActual, dvv);
			}
			vertActual = g.siguienteVertice(vertActual);
		}
	}
	return (tieneCiclos) ? 1 : 0;
}

//x. Aislar un Vertice										 -*-*- SIRVE
void aislarVertice(Grafo& grafo, Grafo::vertice& vert) {
	Grafo::vertice vAdy;
	while (grafo.numVerticesAdyacentes(vert)) {
		vAdy = grafo.primerVerticeAdyacente(vert);
		grafo.eliminarArista(vert, vAdy);
	}
}

//xii. Averiguar si existe camino entre todo par de vértices  -*-*- SIRVE
void caminoEntreTodosR(Grafo& grafo, Grafo::vertice& actual, unordered_set<string>& dvv) {
	dvv.insert(grafo.getEtiqueta(actual));
	auto vAdy = grafo.primerVerticeAdyacente(actual);
	while (vAdy) {
		if (dvv.count(grafo.getEtiqueta(vAdy)) == 0) {
			caminoEntreTodosR(grafo, vAdy, dvv);
		}
		vAdy = grafo.siguienteVerticeAdyacente(actual, vAdy);
	}
}
int caminoEntreTodos(Grafo& grafo) {
	int conexo = 0;
	if (!grafo.vacio()) {
		unordered_set<string> dvv;
		auto vertActual = grafo.primerVertice();
		caminoEntreTodosR(grafo, vertActual, dvv);
		conexo = (dvv.size() == grafo.numVertices());
	}
	return conexo;
}
//----- FIN ALGORITMOS -----

int main()
{
	Grafo g = Grafo();
	Grafo::vertice a, s, d, f;
	g.agregarVertice("a");
	g.agregarVertice("s");
	g.agregarVertice("d");
	g.agregarVertice("f");
	a = traducir(g, "a");
	s = traducir(g, "s");
	d = traducir(g, "d");
	f = traducir(g, "f");
	g.agregarArista(a, s, 1.0);
	g.agregarArista(s, d, 2.0);
	g.agregarArista(d, f, 3.0);
	g.agregarArista(s, f, 4.0);
	//g.agregarArista(f, d, 5.0);
	cout << caminoEntreTodos(g);
	
	return 0;
}