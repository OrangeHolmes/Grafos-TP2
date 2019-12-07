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
				//cout << grafo.getEtiqueta(verticeP) << " ";
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
	//cout << grafo.getEtiqueta(actual);
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

//viii. Prim
//metodo aux
int determinarMin(vector<double> & valores, vector<bool> & recorridos) {
	int min, minV = INT_MAX;

	for (int i = 0; i < valores.size(); ++i) {
		if (valores[i] < minV && recorridos[i] == false) {
			min = i;
			minV = valores[i];
		}
	}
	return min;
}
void prim(Grafo & grafo) {
	vector<double> menorCosto;
	vector<string> masCercano;
	vector<bool> recorridos;
	map<int, Grafo::vertice> relacion;
	Grafo::vertice verticeActual = grafo.primerVertice();

	for (int i = 0; i < grafo.numVertices(); ++i) {
		relacion.insert(pair<int, Grafo::vertice>(i, verticeActual));
		menorCosto.push_back(double(1000000.0));
		masCercano.push_back("-");
		recorridos.push_back(false);
		verticeActual = grafo.siguienteVertice(verticeActual);
	}
	menorCosto[0] = 0;

	for (int j = 0; j < grafo.numVertices() - 1; ++j) {
		int min = determinarMin(menorCosto, recorridos);
		recorridos[min] = true;
		Grafo::vertice vMin = relacion[min];

		for (int k = 0; k < grafo.numVertices(); ++k) {
			Grafo::vertice vK = relacion[k];
			if (!recorridos[k] && grafo.existeArista(vMin, vK)) {
				if (grafo.peso(vMin, vK) < menorCosto[k]) {    //si el peso de la arista j,k es menor a el valor al que se llegaba a k, se modifica el valor
					menorCosto[k] = grafo.peso(vMin, vK);
					masCercano[k] = grafo.getEtiqueta(vMin);
				}
			}
		}
	}
	/*for (int i = 1; i < menorCosto.size(); ++i) {
		cout << "Llegamos al vertice " << grafo.getEtiqueta(relacion[i]) << ", a partir del vertice " << masCercano[i] << ", con un valor de " << menorCosto[i] << endl;
	}*/
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
	for (int i = 0; i < 100; ++i) {
		g1.agregarVertice(to_string(i));
	}
	auto fin = chrono::steady_clock::now();
	cout << "Agregar 30:"
		<< chrono::duration_cast<chrono::milliseconds>(fin - inicio).count()
		<< " milisegundos" << endl;

	inicio = chrono::steady_clock::now();
	for (int i = 0; i < 200; ++i) {
		g2.agregarVertice(to_string(i));
	}
	fin = chrono::steady_clock::now();
	cout << "Agregar 60:"
		<< chrono::duration_cast<chrono::milliseconds>(fin - inicio).count()
		<< " milisegundos" << endl;
	inicio = chrono::steady_clock::now();
	for (int i = 0; i < 400; ++i) {
		g3.agregarVertice(to_string(i));
	}
	fin = chrono::steady_clock::now();
	cout << "Agregar 90:"
		<< chrono::duration_cast<chrono::milliseconds>(fin - inicio).count()
		<< " milisegundos" << endl;


	Grafo::vertice v1;
	Grafo::vertice v11;
	Grafo::vertice v2;
	Grafo::vertice v22;
	Grafo::vertice v3;
	Grafo::vertice v33;

	inicio = chrono::steady_clock::now();
	for (int i = 0; i < 99; ++i) {
		v1 = traducir(g1, to_string(i));
		v11 = traducir(g1,to_string(i+1));
		g1.agregarArista(v1,v11,4.0);
	}
	fin = chrono::steady_clock::now();
	cout << "Aristas 500:"
		<< chrono::duration_cast<chrono::milliseconds>(fin - inicio).count()
		<< " milisegundos" << endl;

	inicio = chrono::steady_clock::now();
	for (int i = 0; i < 199; ++i) {
		v2 = traducir(g2, to_string(i));
		v22 = traducir(g2, to_string(i + 1));
		g2.agregarArista(v2, v22, 4.0);
	}
	fin = chrono::steady_clock::now();
	cout << "Aristas 1000:"
		<< chrono::duration_cast<chrono::milliseconds>(fin - inicio).count()
		<< " milisegundos" << endl;
	inicio = chrono::steady_clock::now();
	for (int i = 0; i < 399; ++i) {
		v3 = traducir(g3, to_string(i));
		v33 = traducir(g3, to_string(i + 1));
		g3.agregarArista(v3, v33, 4.0);
	}
	fin = chrono::steady_clock::now();
	cout << "Aristas 2000:"
		<< chrono::duration_cast<chrono::milliseconds>(fin - inicio).count()
		<< " milisegundos" << endl;
	
	// PRUEBAS PRIM
	inicio = chrono::steady_clock::now();
	prim(g1);
	fin = chrono::steady_clock::now();
	cout << "Prim 30:"
		<< chrono::duration_cast<chrono::milliseconds>(fin - inicio).count()
		<< " milisegundos" << endl;

	inicio = chrono::steady_clock::now();
	prim(g2);
	fin = chrono::steady_clock::now();
	cout << "Prim 60:"
		<< chrono::duration_cast<chrono::milliseconds>(fin - inicio).count()
		<< " milisegundos" << endl;
	inicio = chrono::steady_clock::now();
	prim(g3);
	fin = chrono::steady_clock::now();
	cout << "Prim 90:"
		<< chrono::duration_cast<chrono::milliseconds>(fin - inicio).count()
		<< " milisegundos" << endl;

	/* PRUEBAS PESO, PRIMER_ARISTA*/
	//inicio = chrono::steady_clock::now();
	//for (int i = 0; i < 499; ++i) {
	//	v1 = traducir(g1, to_string(i));
	//	v11 = traducir(g1, to_string(i + 1));
	//	g1.peso(v1, v11);
	//}
	//fin = chrono::steady_clock::now();
	//cout << "Pesos 500:"
	//	<< chrono::duration_cast<chrono::milliseconds>(fin - inicio).count()
	//	<< " milisegundos" << endl;

	//inicio = chrono::steady_clock::now();
	//for (int i = 0; i < 999; ++i) {
	//	v2 = traducir(g2, to_string(i));
	//	v22 = traducir(g2, to_string(i + 1));
	//	g2.peso(v2, v22);
	//}
	//fin = chrono::steady_clock::now();
	//cout << "Pesos 1000:"
	//	<< chrono::duration_cast<chrono::milliseconds>(fin - inicio).count()
	//	<< " milisegundos" << endl;
	//inicio = chrono::steady_clock::now();
	//for (int i = 0; i < 1999; ++i) {
	//	v3 = traducir(g3, to_string(i));
	//	v33 = traducir(g3, to_string(i + 1));
	//	g3.peso(v3, v33);
	//}
	//fin = chrono::steady_clock::now();
	//cout << "Pesos 2000:"
	//	<< chrono::duration_cast<chrono::milliseconds>(fin - inicio).count()
	//	<< " milisegundos" << endl;

	////// PRIMER ARISTA
	//inicio = chrono::steady_clock::now();
	//for (int i = 0; i < 499; ++i) {
	//	v1 = traducir(g1, to_string(i));
	//	g1.primerVerticeAdyacente(v1);
	//}
	//fin = chrono::steady_clock::now();
	//cout << "PVA 500:"
	//	<< chrono::duration_cast<chrono::milliseconds>(fin - inicio).count()
	//	<< " milisegundos" << endl;

	//inicio = chrono::steady_clock::now();
	//for (int i = 0; i < 999; ++i) {
	//	v2 = traducir(g2, to_string(i));
	//	g2.primerVerticeAdyacente(v2);
	//}
	//fin = chrono::steady_clock::now();
	//cout << "PVA 1000:"
	//	<< chrono::duration_cast<chrono::milliseconds>(fin - inicio).count()
	//	<< " milisegundos" << endl;
	//inicio = chrono::steady_clock::now();
	//for (int i = 0; i < 1999; ++i) {
	//	v3 = traducir(g3, to_string(i));
	//	g3.primerVerticeAdyacente(v3);
	//}
	//fin = chrono::steady_clock::now();
	//cout << "PVA 2000:"
	//	<< chrono::duration_cast<chrono::milliseconds>(fin - inicio).count()
	//	<< " milisegundos" << endl;



	/*PRUEBA ANCHO VS PROFUNDIDAD
	inicio = chrono::steady_clock::now();
	profPrimero(g1);
	fin = chrono::steady_clock::now();
	cout << "prof Primero 20:"
		<< chrono::duration_cast<chrono::milliseconds>(fin - inicio).count()
		<< " milisegundos" << endl;
	inicio = chrono::steady_clock::now();
	profPrimero(g2);
	fin = chrono::steady_clock::now();
	cout << "prof Primero 40:"
		<< chrono::duration_cast<chrono::milliseconds>(fin - inicio).count()
		<< " milisegundos" << endl;
	inicio = chrono::steady_clock::now();
	profPrimero(g3);
	fin = chrono::steady_clock::now();
	cout << "prof Primero 80:"
		<< chrono::duration_cast<chrono::milliseconds>(fin - inicio).count()
		<< " milisegundos" << endl;

	
	inicio = chrono::steady_clock::now();
	anchoPrimero(g1);
	fin = chrono::steady_clock::now();
	cout << "ancho Primero 20:"
		<< chrono::duration_cast<chrono::milliseconds>(fin - inicio).count()
		<< " milisegundos" << endl;
	inicio = chrono::steady_clock::now();
	anchoPrimero(g2);
	fin = chrono::steady_clock::now();
	cout << "ancho Primero 40:"
		<< chrono::duration_cast<chrono::milliseconds>(fin - inicio).count()
		<< " milisegundos" << endl;
	inicio = chrono::steady_clock::now();
	anchoPrimero(g3);
	fin = chrono::steady_clock::now();
	cout << "ancho Primero 80:"
		<< chrono::duration_cast<chrono::milliseconds>(fin - inicio).count()
		<< " milisegundos" << endl;*/


	// PRUEBA BORRADOS DE ARISTAS
	//inicio = chrono::steady_clock::now();
	//for (int i = 0; i < 499; ++i) {
	//	v1 = traducir(g1, to_string(i));
	//	v11 = traducir(g1, to_string(i + 1));
	//	g1.eliminarArista(v1, v11);
	//}
	//fin = chrono::steady_clock::now();
	//cout << "Borrar Aristas 500:"
	//	<< chrono::duration_cast<chrono::milliseconds>(fin - inicio).count()
	//	<< " milisegundos" << endl;

	//inicio = chrono::steady_clock::now();
	//for (int i = 0; i < 999; ++i) {
	//	v2 = traducir(g2, to_string(i));
	//	v22 = traducir(g2, to_string(i + 1));
	//	g2.eliminarArista(v2, v22);
	//}
	//fin = chrono::steady_clock::now();
	//cout << "Borrar Aristas 1k:"
	//	<< chrono::duration_cast<chrono::milliseconds>(fin - inicio).count()
	//	<< " milisegundos" << endl;
	//inicio = chrono::steady_clock::now();
	//for (int i = 0; i < 1999; ++i) {
	//	v3 = traducir(g3, to_string(i));
	//	v33 = traducir(g3, to_string(i + 1));
	//	g3.eliminarArista(v3, v33);
	//}
	//fin = chrono::steady_clock::now();
	//cout << "Borrar Aristas 2k:"
	//	<< chrono::duration_cast<chrono::milliseconds>(fin - inicio).count()
	//	<< " milisegundos" << endl;

	cin.ignore();
	return 0;
}
