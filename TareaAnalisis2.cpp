#include <iostream>
#include <unordered_set>

#include "GrafoListas.h"
//#include "GrafoMatriz.h"


//----- INICIO ALGORITMOS -----

//ii. Recorrido en Profundidad Primero para despliegue de etiquetas en pantalla.
void profPrimero(Grafo grafo) {
	if (!grafo.vacio()) {
		unordered_set<string> dvv;
		Grafo::vertice vertActual = grafo.primerVertice();
		while (vertActual) {
			if (dvv.count(vertActual->etiqueta) == 0) {
				profPrimeroR(grafo, vertActual, dvv);
			}
			vertActual = grafo.siguienteVertice(vertActual);
		}
	}
}
void profPrimeroR(Grafo grafo, Grafo::vertice actual, unordered_set<string>& dvv) {
	dvv.insert(actual->etiqueta);
	actual->imprimir(cout);
	auto vAdy = grafo.primerVerticeAdyacente(actual);
	while (vAdy) {
		if (dvv.count(vAdy->etiqueta) == 0) {
			profPrimeroR(grafo, vAdy, dvv);
		}
		vAdy = grafo.siguienteVerticeAdyacente(actual, vAdy);
	}
}


//iii. Averiguar si un grafo tiene ciclos usando el Recorrido en Profundidad Primero
int tieneCiclos(Grafo g) {
	int tieneCiclos = 0;
	if (!g.vacio()) {
		unordered_set<string> dvv;
		Grafo::vertice vertActual = g.primerVertice();
		while (vertActual) {
			if (dvv.count(vertActual->etiqueta) == 0)
			{
				tieneCiclos += tieneCiclosR(g, vertActual, vertActual, dvv);
			}
			vertActual = g.siguienteVertice(vertActual);
		}
	}
	return (tieneCiclos) ? 1 : 0;
}
int tieneCiclosR(Grafo grafo, Grafo::vertice actual, Grafo::vertice inicial, unordered_set<string>& dvv) {
	int tieneCiclo = 0;	
	dvv.insert(actual->etiqueta);
	auto vAdy = grafo.primerVerticeAdyacente(actual);
	while (vAdy) {
		if (vAdy == inicial) {
			++tieneCiclo;
		}
		if (dvv.count(vAdy->etiqueta) == 0){
			tieneCiclo += tieneCiclosR(grafo, vAdy, inicial, dvv);
		}
		vAdy = grafo.siguienteVerticeAdyacente(actual, vAdy);
	}
	return tieneCiclo;
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
	dvv.insert(actual->etiqueta);
	auto vAdy = grafo.primerVerticeAdyacente(actual);
	while (vAdy) {
		if (dvv.count(vAdy->etiqueta) == 0) {
			caminoEntreTodosR(grafo, vAdy, dvv);
		}
		vAdy = grafo.siguienteVerticeAdyacente(actual, vAdy);
	}
}

//----- FIN ALGORITMOS -----

int main()
{
    std::cout << "Hello World!\n";
	Grafo grofo = Grafo();
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