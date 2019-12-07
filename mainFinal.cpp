#include <iostream>
#include <stdlib.h> //Para usar system("cls");
#include <conio.h> //Para usar _getch();
#include <unordered_set>
#include <queue>
#include <map>
#include <vector>
#include <utility> 

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

// iv. Dijkstra.
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

void dijkstra(Grafo & grafo, Grafo::vertice inicio) {
	vector<double> valoresMinimos;
	vector<string> masCercano;
	vector<bool> recorridos;
	map<int, Grafo::vertice> relacion;
	Grafo::vertice verticeActual = grafo.primerVertice();

	for (int i = 0; i < grafo.numVertices(); ++i) {
		relacion.insert(pair<int, Grafo::vertice>(i, verticeActual));
		valoresMinimos.push_back(double(100.0));
		masCercano.push_back("-");
		recorridos.push_back(false);
		if (grafo.getEtiqueta(inicio) == grafo.getEtiqueta(verticeActual)) {
			valoresMinimos[i] = 0;
		}
		verticeActual = grafo.siguienteVertice(verticeActual);
	}

	for (int j = 0; j < grafo.numVertices()-1 ; ++j) {
		int min = determinarMin(valoresMinimos, recorridos);
		recorridos[min] = true;
		Grafo::vertice vMin = relacion[min];
		for (int k = 0; k < grafo.numVertices(); ++k) {
			Grafo::vertice vK = relacion[k];
			if (grafo.getEtiqueta(vMin) != grafo.getEtiqueta(vK) && grafo.existeArista(vMin, vK)) {
				if (grafo.peso(vMin, vK) + valoresMinimos[min] < valoresMinimos[k]) {    //si el peso de la arista j,k es menor a el valor al que se llegaba a k, se modifica el valor
					valoresMinimos[k] = grafo.peso(vMin, vK) + valoresMinimos[min];
					masCercano[k] = grafo.getEtiqueta(vMin);
					cout << valoresMinimos[k] << endl;
				}
			}
		}
	}
	for (int i = 0; i < valoresMinimos.size(); ++i) {
		if (grafo.getEtiqueta(relacion[i]) != grafo.getEtiqueta(inicio)) {
			cout << "La distancia minima para llegar al vertice " << grafo.getEtiqueta(relacion[i]) << " desde " << grafo.getEtiqueta(inicio) <<
				" es de " << valoresMinimos[i] << endl;
		}
	}
}

//v. Floyd													*-*-*-* SIRVE
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
			if (!recorridos[k] && grafo.existeArista(vMin,vK) ){
				if (grafo.peso(vMin, vK) < menorCosto[k]) {    //si el peso de la arista j,k es menor a el valor al que se llegaba a k, se modifica el valor
					menorCosto[k] = grafo.peso(vMin, vK);
					masCercano[k] = grafo.getEtiqueta(vMin);
				}
			}
		}
	}
	for (int i = 1; i < menorCosto.size(); ++i) {
		cout << "Llegamos al vertice " <<grafo.getEtiqueta(relacion[i])<< ", a partir del vertice "<< masCercano[i] << ", con un valor de "<< menorCosto[i] << endl;
	}
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

void operadoresBasicos(Grafo& g) {
	int opcion = 0;
	do {
		system("cls");
		cout << "\n\t ---- Grafo No Dirigido ---\n\n 1. Preguntar si el grafo esta vacio\n 2. Vaciar el grafo\n 3. Insertar Vertice\n 4. Borrar Vertice\n 5. Modificar Vertice\n"
			<< " 6. Verificar Etiqueta \n 7. Agregar Arista\n 8. Eliminar Arista\n 9. Modificar Peso\n 10. Recuperar Peso\n 11. Recuperar Primer Vertice\n 12. Recuperar Siguiente Vertice\n"
			<< " 13.Recuperar Primer Vertice Adyacente\n 14. Recuperar Siguiente Vertice Adyacente\n 15. Existe Arista\n 16. Contar Aristas del Grafo\n 17. Contar Vertices\n 18. Contar Aristas de un Vertice\n 19. Regresar \n\n  -Digite una opcion: ";
		cin >> opcion;
		string eti, eti2;
		Grafo::vertice v1, v2;
		switch (opcion)
		{
		case 1:
			system("cls");
			g.vacio() ? cout << "\n\t ---- Grafo No Dirigido ---\n\n -Esta vacio" : cout << "\n\t ---- Grafo No Dirigido ---\n\n -No esta vacio" << endl;
			cout << "\n\n\tPulsa una tecla para continuar...";
			_getch();
			break;
		case 2: {
			system("cls");
			char opc = 'N';
			cout << "\n\t ---- Grafo No Dirigido ---\n\n -Desea vaciar el grafo?(S/N) ";
			cin >> opc;
			if ((opc == 'S' || opc == 's') && !g.vacio()) {
				g.vaciar();
				cout << "\n ---Grafo vaciado correctamente --- ";
			}
			else {
				cout << "\n ---NO se hicieron cambios --- ";
			}
			_getch();
			break;
		}
		case 3:
			system("cls");
			cout << "\n\t ---- Grafo No Dirigido ---\n\n -Que etiqueta desea insertar?: ";
			cin >> eti;
			g.agregarVertice(eti);
			g.imprimir(cout);
			cout << "\n\n\tPulsa una tecla para continuar...";
			_getch();
			break;
		case 4:
			system("cls");
			cout << "\n\t ---- Grafo No Dirigido ---\n\n -Que etiqueta desea borrar?: ";
			cin >> eti;
			v1 = traducir(g, eti);
			if (g.verticeValido(v1)) {
				if (g.numVerticesAdyacentes(v1)) {
					cout << "\n El vertice debe estar aislado!";
				}
				else {
					g.eliminarVertice(v1);
				}
				g.imprimir(cout);
			}
			else {
				cout << "\n El vertice no existe!";
			}
			cout << "\n\n\tPulsa una tecla para continuar...";
			_getch();
			break;
		case 5:
			system("cls");
			cout << "\n\t ---- Grafo No Dirigido ---\n\n -Que etiqueta desea modificar?: ";
			cin >> eti;
			v1 = traducir(g, eti);
			if (g.verticeValido(v1)) {
				cout << "\n -Digite la nueva etiqueta: ";
				cin >> eti2;
				g.modificarVertice(v1, eti2);
				g.imprimir(cout);
			}
			else {
				cout << "\n El vertice no existe!";
			}
			cout << "\n\n\tPulsa una tecla para continuar...";
			_getch();
			break;
		case 6:
			system("cls");
			cout << "\n\t ---- Grafo No Dirigido ---\n\n -Que etiqueta desea verificar?: ";
			cin >> eti;
			v1 = traducir(g, eti);
			if (g.verticeValido(v1)) {
				cout << "\n\n El vertice: " << g.getEtiqueta(v1) << " existe!" << endl;
			}
			else {
				cout << "\n\n El vertice: " << eti << " NO existe!" << endl;
			}
			cout << "\n\n\tPulsa una tecla para continuar...";
			_getch();
			break;
		case 7: {
			double peso = 0.0;
			system("cls");
			cout << "\n\t ---- Grafo No Dirigido ---\n\n -Digite un vertice a conectar: ";
			cin >> eti;
			cout << "\n -Digite el otro vertice a conectar: ";
			cin >> eti2;
			cout << "\n -Digite el peso de la arista: ";
			cin >> peso;
			v1 = traducir(g, eti);
			v2 = traducir(g, eti2);
			if (g.verticeValido(v1) && g.verticeValido(v2)) {
				g.agregarArista(v1, v2, peso);
				cout << "\n\t Arista creada!\n";
				g.imprimir(cout);
			}
			else {
				cout << "\n\t Datos invalidos! NO agregado";
			}
			cout << "\n\n\tPulsa una tecla para continuar...";
			_getch();
			break;
		}
		case 8: {
			double peso = 0.0;
			system("cls");
			cout << "\n\t ---- Grafo No Dirigido ---\n\n -Digite un vertice a desconectar: ";
			cin >> eti;
			cout << "\n -Digite el otro vertice a desconectar: ";
			cin >> eti2;
			v1 = traducir(g, eti);
			v2 = traducir(g, eti2);
			if (g.verticeValido(v1) && g.verticeValido(v2)) {
				g.eliminarArista(v1, v2);
				cout << "\n\t Arista Eliminada!";
				g.imprimir(cout);
			}
			else {
				cout << "\n\t Datos invalidos! NO eliminado";
			}
			cout << "\n\n\tPulsa una tecla para continuar...";
			_getch();
			break;
		}
		case 9:
		{
			double peso = 0.0;
			system("cls");
			cout << "\n\t ---- Grafo No Dirigido ---\n\n -Digite un vertice de la arista: ";
			cin >> eti;
			cout << "\n -Digite el otro vertice de la arista: ";
			cin >> eti2;
			cout << "\n -Digite el nuevo peso: ";
			cin >> peso;
			v1 = traducir(g, eti);
			v2 = traducir(g, eti2);
			if (g.verticeValido(v1) && g.verticeValido(v2)) {
				g.modificarPeso(v1, v2, peso);
				cout << "\n\t Peso modificado!\n";
				g.imprimir(cout);
			}
			else {
				cout << "\n\t Datos invalidos! NO eliminado";
			}
			cout << "\n\n\tPulsa una tecla para continuar...";
			_getch();
			break;
		}
		case 10:
			system("cls");
			cout << "\n\t ---- Grafo No Dirigido ---\n\n -Digite un vertice de la arista: ";
			cin >> eti;
			cout << "\n -Digite el otro vertice de la arista: ";
			cin >> eti2;
			v1 = traducir(g, eti);
			v2 = traducir(g, eti2);
			if (g.verticeValido(v1) && g.verticeValido(v2)) {
				cout << "\n\n La arista tiene un peso de: " << g.peso(v1, v2) << endl;
			}
			else {
				cout << "\n\t Datos invalidos!";
			}
			cout << "\n\n\tPulsa una tecla para continuar...";
			_getch();
			break;
		case 11:
			system("cls");
			cout << "\n\t ---- Grafo No Dirigido ---\n\n";
			if (g.primerVertice()) {
				cout << " -El primer vertice es: " << g.getEtiqueta(g.primerVertice()) << endl;
			}
			else {
				cout << " -El grafo esta vacio" << endl;
			}
			cout << "\n\n\tPulsa una tecla para continuar...";
			_getch();
			break;
		case 12:
			system("cls");
			cout << "\n\t ---- Grafo No Dirigido ---\n\n -De cual vertice desea conocer el siguiente? ";
			cin >> eti;
			v1 = traducir(g, eti);
			if (g.verticeValido(g.siguienteVertice(v1))) {
				cout << "\n\n -El siguiente vertice es: " << g.getEtiqueta(g.siguienteVertice(v1)) << endl;
			}
			else {
				cout << "\n\n -El vertice no tiene siguiente" << endl;
			}
			cout << "\n\n\tPulsa una tecla para continuar...";
			_getch();
			break;
		case 13:
			system("cls");
			cout << "\n\t ---- Grafo No Dirigido ---\n\n -De cual vertice desea conocer su primer arista? ";
			cin >> eti;
			v1 = traducir(g, eti);
			if (g.verticeValido(g.primerVerticeAdyacente(v1))) {
				cout << "\n\n -La primer arista es con: " << g.getEtiqueta(g.primerVerticeAdyacente(v1)) << endl;
			}
			else {
				cout << "\n\n -El vertice no tiene aristas" << endl;
			}
			cout << "\n\n\tPulsa una tecla para continuar...";
			_getch();
			break;
		case 14:
			system("cls");
			cout << "\n\t ---- Grafo No Dirigido ---\n\n -De cual vertice desea conocer la arista? ";
			cin >> eti;
			cout << "\nDe cual arista desea la siguiente? " << endl;
			cin >> eti2;
			v1 = traducir(g, eti);
			v2 = traducir(g, eti2);
			if (g.verticeValido(g.siguienteVerticeAdyacente(v1, v2))) {
				cout << "\n\n -La siguiente arista de " << g.getEtiqueta(v1) << " es con: " << g.getEtiqueta(g.siguienteVerticeAdyacente(v1, v2)) << endl;
			}
			else {
				cout << "\n\n -El vertice no tiene mas aristas" << endl;
			}
			cout << "\n\n\tPulsa una tecla para continuar...";
			_getch();
			break;
		case 15:
			system("cls");
			cout << "\n\t ---- Grafo No Dirigido ---\n\n -Digite un vertice de la arista: ";
			cin >> eti;
			cout << "\n -Digite el otro vertice de la arista: ";
			cin >> eti2;
			v1 = traducir(g, eti);
			v2 = traducir(g, eti2);
			if (g.existeArista(v1, v2)) {
				cout << "\n\n -La arista existe!" << endl;
			}
			else {
				cout << "\n\n -La arista NO existe" << endl;
			}
			cout << "\n\n\tPulsa una tecla para continuar...";
			_getch();
			break;
		case 16:
			system("cls");
			cout << "\n\t ---- Grafo No Dirigido ---\n\n -El grafo tiene " << g.numAristas() << " aristas" << endl;
			cout << "\n\n\tPulsa una tecla para continuar...";
			_getch();
			break;
		case 17:
			system("cls");
			cout << "\n\t ---- Grafo No Dirigido ---\n\n -El grafo tiene " << g.numVertices() << " vertices" << endl;
			cout << "\n\n\tPulsa una tecla para continuar...";
			_getch();
			break;
		case 18:
			system("cls");
			cout << "\n\t ---- Grafo No Dirigido ---\n\n -Digite el vertice: ";
			cin >> eti;
			v1 = traducir(g, eti);
			if (g.verticeValido(v1)) {
				cout << "\n\n El vertice tiene " << g.numVerticesAdyacentes(v1) << " aristas" << endl;
			}
			else {
				cout << " Vertice no existe!";
			}
			cout << "\n\n\tPulsa una tecla para continuar...";
			_getch();
			break;
		case 19:
			break;
		default:
			cout << "\n Opcion Invalida";
			_getch();
			break;
		}
		if (opcion != 19) {
			cin.clear();
			cin.ignore(100, '\n');
		}
	} while (opcion != 19);
}

void algoritmos(Grafo& g) {
	int opcion = 0;
	do {
		system("cls");
		cout << "\n\t ---- Grafo No Dirigido ---\n\n 1. Recorrido en Ancho Primero\n 2. Recorrido en Profundidad Primero\n 3. El grafo tiene ciclos?\n 4. Algoritmo de Dijkstra\n 5.Algoritmo de Floyd\n"
			<< " 6. Circuito Hamilton de Menor Costo\n 7. Colorear Grafo\n 8. Algoritmo de Prim\n 9. Algoritmo de Kruskal\n 10. Aislar un vértice\n 11. Puntos de articulación del grafo\n 12. Es conexo?\n 13. Regresar \n\n  -Digite una opcion: ";
		cin >> opcion;
		string eti, eti2;
		Grafo::vertice v1, v2;
		switch (opcion)
		{
		case 1:
			system("cls");
			cout << "\n\t ---- Grafo No Dirigido ---\n\n ";
			anchoPrimero(g);
			cout << "\n\n\tPulsa una tecla para continuar...";
			_getch();
			break;
		case 2:
			system("cls");
			cout << "\n\t ---- Grafo No Dirigido ---\n\n ";		
			profPrimero(g);
			cout << "\n\n\tPulsa una tecla para continuar...";
			_getch();
			break;
		case 3:
			system("cls");
			cout << "\n\t ---- Grafo No Dirigido ---\n\n ";
			tieneCiclos(g) ? cout << "\n\t ---- Grafo No Dirigido ---\n\n - Tiene ciclos!" : cout << "\n\t ---- Grafo No Dirigido ---\n\n -NO tiene ciclos!" << endl;
			cout << "\n\n\tPulsa una tecla para continuar...";
			_getch();
			break;
		case 4:
			system("cls");
			cout << "\n\t ---- Grafo No Dirigido ---\n\n ";
			dijkstra(g);
			cout << "\n\n\tPulsa una tecla para continuar...";
			_getch();
			break;
		case 5:
			system("cls");
			cout << "\n\t ---- Grafo No Dirigido ---\n\n ";
			floyd(g);
			cout << "\n\n\tPulsa una tecla para continuar...";
			_getch();
			break;
		case 6:
			//vi.Encontrar Circuito de Hamilton de Menor Costo.
			break;
		case 7:
			//vii.Colorear el grafo, usando la menor cantidad de colores posible.
			break;
		case 8:
			system("cls");
			cout << "\n\t ---- Grafo No Dirigido ---\n\n ";
			floyd(g);
			cout << "\n\n\tPulsa una tecla para continuar...";
			_getch();
			break;
		case 9:
			//ix.Kruskal
			break;
		case 10:
			system("cls");
			cout << "\n\t ---- Grafo No Dirigido ---\n\n -Que vertice desea aislar?: ";
			cin >> eti;
			v1 = traducir(g, eti);
			if (g.verticeValido(v1)) {
				aislarVertice(g,v1);
				cout << "\n Vertice aislado!";
			}
			else {
				cout << "\n El vertice no existe!";
			}
			cout << "\n\n\tPulsa una tecla para continuar...";
			_getch();
			break;
		case 11:
			//xi.Encontrar los puntos de articulación del grafo
			break;
		case 12:
			system("cls");
			caminoEntreTodos(g) ? cout << "\n\t ---- Grafo No Dirigido ---\n\n -Existe camino entre todos!" : cout << "\n\t ---- Grafo No Dirigido ---\n\n -NO existe camino entre todos!" << endl;
			cout << "\n\n\tPulsa una tecla para continuar...";
			_getch();
			break;
		case 13:
			break;
		default:
			cout << "Opcion Invalida" << endl;
			_getch();
			break;
		}
		if (opcion != 13) {
			cin.clear();
			cin.ignore(100, '\n');
		}
	} while (opcion != 13);
}

int main()
{
	Grafo g = Grafo();
	int op = 0;
	do {
		system("cls");
		cout << "\n\t ----- Menu Principal ----- \n\n 1-) Operadores Basicos\n 2-) Algoritmos\n 3-) Salir\n\n  -Digite una opcion: ";
		cin >> op;
		switch (op)
		{
		case 1:
			operadoresBasicos(g);
			break;
		case 2:
			algoritmos(g);
			break;
		case 3:
			cout << "Programa terminado con exito!" << endl;
			break;
		default:
			cout << "Opcion Invalida" << endl;
			_getch();
			break;
		}
		if (op != 3) {
			cin.clear();
			cin.ignore(100, '\n');
		}
	} while (op != 3);
	return 0;
}
