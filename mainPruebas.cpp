#include <iostream>
#include <stdlib.h> //Para usar system("cls");
#include <conio.h> //Para usar _getch();
#include <unordered_set>
#include <queue>
#include <map>
#include <chrono>
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

//i. Recorrido en Ancho Primero para despliegue de etiquetas en pantalla.			-*-*- SIRVE
void anchoPrimero(Grafo & grafo) {
	unordered_set <string> dvv; //diccionarios vertices recorridos
	queue <Grafo::vertice> cola;
	Grafo::vertice verticeActual = grafo.primerVertice();

	while (grafo.verticeValido(verticeActual)) {
		if (!dvv.count(grafo.getEtiqueta(verticeActual))) {
			cola.push(verticeActual);
			dvv.insert(grafo.getEtiqueta(verticeActual));
			while (!cola.empty()) {
				Grafo::vertice verticeP = cola.front(); 
				cola.pop();
				cout << grafo.getEtiqueta(verticeP) << " ";
				Grafo::vertice verticeAdy = grafo.primerVerticeAdyacente(verticeP);
				while (grafo.verticeValido(verticeAdy)) {
					if (!dvv.count(grafo.getEtiqueta(verticeAdy))) {
						cola.push(verticeAdy);
						dvv.insert(grafo.getEtiqueta(verticeAdy));
					}
					verticeAdy = grafo.siguienteVerticeAdyacente(verticeP, verticeAdy);
				}
			}
		}
		verticeActual = grafo.siguienteVertice(verticeActual);
	}
}

//ii. Recorrido en Profundidad Primero para despliegue de etiquetas en pantalla.	-*-*- SIRVE
void profPrimeroR(Grafo& grafo, Grafo::vertice& actual, unordered_set<string>& dvv) {
	dvv.insert(grafo.getEtiqueta(actual));
	cout << grafo.getEtiqueta(actual);
	auto vAdy = grafo.primerVerticeAdyacente(actual);
	while (grafo.verticeValido(vAdy)) {
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
		while (grafo.verticeValido(vertActual)) {
			if (dvv.count(grafo.getEtiqueta(vertActual)) == 0) {
				profPrimeroR(grafo, vertActual, dvv);
			}
			vertActual = grafo.siguienteVertice(vertActual);
		}
	}
}

//iii. Averiguar si un grafo tiene ciclos usando el Recorrido en Profundidad Primero		-*-*- SIRVE
int tieneCiclosR(Grafo& grafo, Grafo::vertice& actual, Grafo::vertice& anterior, Grafo::vertice& inicial, unordered_set<string>& dvv) {
	int tieneCiclo = 0;
	dvv.insert(grafo.getEtiqueta(actual));
	auto vAdy = grafo.primerVerticeAdyacente(actual);
	while (grafo.verticeValido(vAdy)) {
		if (vAdy == inicial && anterior != inicial) {
			++tieneCiclo;
		}
		if (dvv.count(grafo.getEtiqueta(vAdy)) == 0) {
			tieneCiclo += tieneCiclosR(grafo, vAdy, actual, inicial, dvv);
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
		while (g.verticeValido(vertActual)) {
			if (dvv.count(g.getEtiqueta(vertActual)) == 0)
			{
				tieneCiclos += tieneCiclosR(g, vertActual, vertActual, vertActual, dvv);
			}
			vertActual = g.siguienteVertice(vertActual);
		}
	}
	return (tieneCiclos) ? 1 : 0;
}

//v. Floyd													-*-*- SIRVE
void floyd(Grafo g) {
	int vertTotales = g.numVertices();
	int ** matrizCostos = new int*[vertTotales];
	map<int, Grafo::vertice> relacion1a1;
	auto vertice1 = g.primerVertice();
	Grafo::vertice vertice2;
	for (int i = 0; i < vertTotales; ++i) {
		relacion1a1.insert(pair<int, Grafo::vertice>(i, vertice1));
		vertice2 = g.primerVertice();
		matrizCostos[i] = new int[vertTotales];
		for (int j = 0; j < vertTotales; ++j) {
			matrizCostos[i][j] = 1000000000; //Analogo a infinito
			if (g.existeArista(vertice1, vertice2)) {
				matrizCostos[i][j] = g.peso(vertice1, vertice2);
			}
			else if (i == j) {
				matrizCostos[i][j] = 0;
			}
			vertice2 = g.siguienteVertice(vertice2);
		}
		vertice1 = g.siguienteVertice(vertice1);
	}
	Grafo::vertice pivote;
	for (int k = 0; k < vertTotales; ++k) {
		pivote = relacion1a1[k];
		vertice1 = g.primerVertice();
		for (int i = 0; i < vertTotales; ++i) {
			vertice2 = g.primerVertice();
			for (int j = 0; j < vertTotales; ++j) {
				if (matrizCostos[i][j] > (matrizCostos[i][k] + matrizCostos[k][j])) {
					matrizCostos[i][j] = matrizCostos[i][k] + matrizCostos[k][j];
				}
			}
			vertice1 = g.siguienteVertice(vertice1);
		}
	}
	//Imprimir Resultados
	for (int i = 0; i < g.numVertices(); ++i) {
		for (int j = 0; j < g.numVertices(); ++j) {
			cout << matrizCostos[i][j] << ",";
		}
		cout << endl;
	}
	for (int i = 0; i < g.numVertices(); ++i) {
		delete[] matrizCostos[i];
	}
	delete[]matrizCostos;
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
	while (grafo.verticeValido(vAdy)) {
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
	Grafo g1 = Grafo();
	Grafo g2 = Grafo();
	Grafo g3 = Grafo();
	auto inicio = chrono::steady_clock::now();
	for (int i = 0; i < 1000; ++i) {
		g1.agregarVertice(to_string(i));
	}
	auto fin = chrono::steady_clock::now();
	cout << "Agregar 1k:"
		<< chrono::duration_cast<chrono::milliseconds>(fin - inicio).count()
		<< " milisegundos" << endl;

	inicio = chrono::steady_clock::now();
	for (int i = 0; i < 10000; ++i) {
		g2.agregarVertice(to_string(i));
	}
	fin = chrono::steady_clock::now();
	cout << "Agregar 10k:"
		<< chrono::duration_cast<chrono::milliseconds>(fin - inicio).count()
		<< " milisegundos" << endl;
	inicio = chrono::steady_clock::now();
	for (int i = 0; i < 100000; ++i) {
		g3.agregarVertice(to_string(i));
	}
	fin = chrono::steady_clock::now();
	cout << "Agregar 100k:"
		<< chrono::duration_cast<chrono::milliseconds>(fin - inicio).count()
		<< " milisegundos" << endl;


	Grafo::vertice v1;
	Grafo::vertice v11;
	Grafo::vertice v2;
	Grafo::vertice v22;
	Grafo::vertice v3;
	Grafo::vertice v33;

	inicio = chrono::steady_clock::now();
	for (int i = 0; i < 1000; ++i) {
		v1 = traducir(g1, to_string(rand()%1000));
		v11 = traducir(g1,to_string(rand() % 1000));
		g1.agregarArista(v1,v11,5.0);
	}
	fin = chrono::steady_clock::now();
	cout << "Aristas 1k:"
		<< chrono::duration_cast<chrono::milliseconds>(fin - inicio).count()
		<< " milisegundos" << endl;

	inicio = chrono::steady_clock::now();
	for (int i = 0; i < 10000; ++i) {
		v2 = traducir(g2, to_string(rand() % 10000));
		v22 = traducir(g2, to_string(rand() % 10000));
		g2.agregarArista(v2, v22, 5.0);
	}
	fin = chrono::steady_clock::now();
	cout << "Aristas 10k:"
		<< chrono::duration_cast<chrono::milliseconds>(fin - inicio).count()
		<< " milisegundos" << endl;
	inicio = chrono::steady_clock::now();
	for (int i = 0; i < 100000; ++i) {
		v3 = traducir(g3, to_string(rand() % 100000));
		v33 = traducir(g3, to_string(rand() % 100000));
		g3.agregarArista(v3, v33, 5.0);
	}
	fin = chrono::steady_clock::now();
	cout << "Aristas 100k:"
		<< chrono::duration_cast<chrono::milliseconds>(fin - inicio).count()
		<< " milisegundos" << endl;


	cin.ignore();
	return 0;
}
