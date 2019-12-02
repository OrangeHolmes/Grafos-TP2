#include <iostream>
#include <unordered_set>

#include "GrafoListas.h"
//#include "GrafoMatriz.h"

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

//ii. Recorrido en Profundidad Primero para despliegue de etiquetas en pantalla.
void profPrimeroR(Grafo grafo, Grafo::vertice actual, unordered_set<string>& dvv) {
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
void profPrimero(Grafo grafo) {
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

//iii. Averiguar si un grafo tiene ciclos usando el Recorrido en Profundidad Primero
int tieneCiclosR(Grafo grafo, Grafo::vertice actual, Grafo::vertice inicial, unordered_set<string>& dvv) {
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
int tieneCiclos(Grafo g) {
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



//x. Aislar un Vertice
void aislarVertice(Grafo grafo, Grafo::vertice vert) {
	while (grafo.numVerticesAdyacentes(vert)) {
		auto vAdy = grafo.primerVerticeAdyacente(vert);
		grafo.eliminarArista(vert, vAdy);
	}
}

//xii. Averiguar si existe camino entre todo par de vértices
int caminoEntreTodos(Grafo grafo) {
	int conexo = 0;
	if (!grafo.vacio()) {
		unordered_set<string> dvv;
		auto vertActual = grafo.primerVertice();
		profPrimeroR(grafo, vertActual, dvv);
		conexo = (dvv.size() == grafo.numVertices());
	}
	return conexo;
}
void caminoEntreTodosR(Grafo grafo, Grafo::vertice actual, unordered_set<string>& dvv) {
	dvv.insert(grafo.getEtiqueta(actual));
	auto vAdy = grafo.primerVerticeAdyacente(actual);
	while (vAdy) {
		if (dvv.count(grafo.getEtiqueta(vAdy)) == 0) {
			caminoEntreTodosR(grafo, vAdy, dvv);
		}
		vAdy = grafo.siguienteVerticeAdyacente(actual, vAdy);
	}
}

//----- FIN ALGORITMOS -----

int main()
{
    std::cout << "Hello World!\n";
	Grafo g = Grafo();
	g.agregarVertice("A");
	g.agregarVertice("B");
	g.agregarVertice("C");
	g.agregarVertice("D");
	Grafo::vertice a = traducir(g, "A");
	Grafo::vertice b = traducir(g, "B");
	Grafo::vertice c = traducir(g, "C");
	Grafo::vertice d = traducir(g, "D");

	g.agregarArista(a,b,5);
	g.agregarArista(a, c, 2);
	g.agregarArista(a, d, 7);
	g.agregarArista(b, a, 1);
	g.imprimir(cout);
}