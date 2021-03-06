
#include "GrafoMatriz.h"
using namespace std;

Grafo::Vertice::Vertice() {
	etiqueta = "";
	numVerticesAdyacentes = 0;
}

Grafo::Vertice::Vertice(string etiquetaRecibida) {
	etiqueta = etiquetaRecibida;
	numVerticesAdyacentes = 0;
}

Grafo::Vertice::~Vertice(){}

Grafo::Grafo(){
	ultimoLleno = -1;
	contadorAristas = 0;
}

Grafo::~Grafo() {

}

void Grafo::vaciar() {
	ultimoLleno = -1;
}

int Grafo::vacio() {
	return (ultimoLleno == -1) ? 1 : 0;
}

void Grafo::agregarVertice(string etiquetaRecibida) {
	vectorVertices[++ultimoLleno] = Vertice(etiquetaRecibida);
	for (int i = 0; i < maxVertices; i++){
		matrizAdyacencia[ultimoLleno][i] = pesoNulo;
	}
	for (int i = 0; i < maxVertices; i++) {
		matrizAdyacencia[i][ultimoLleno] = pesoNulo;
	}
}

void Grafo::eliminarVertice(vertice verticeEntrada) {
	for (int i = verticeEntrada; i < ultimoLleno; ++i) {
		vectorVertices[i] = vectorVertices[i + 1];
	}
	--ultimoLleno;
	for (int i = 0; i < ultimoLleno; ++i) {
		for (int j = 0; j < ultimoLleno; ++j) {
			matrizAdyacencia[i][j] = matrizAdyacencia[i][j+1];
		}
	}
}

void Grafo::modificarVertice(vertice verticeEntrada, string etiquetaNueva) {
	vectorVertices[verticeEntrada] = etiquetaNueva;
}

string Grafo::getEtiqueta(vertice verticeEntrada){
	return vectorVertices[verticeEntrada].etiqueta;
}

void Grafo::agregarArista(vertice vOrigen, vertice vDestino, double pesoArista){
	matrizAdyacencia[vOrigen][vDestino] = pesoArista;
	matrizAdyacencia[vDestino][vOrigen] = pesoArista;
	++(vectorVertices[vOrigen].numVerticesAdyacentes);
	++(vectorVertices[vDestino].numVerticesAdyacentes);
	++contadorAristas;
}

void Grafo::eliminarArista(vertice vOrigen, vertice vDestino) {
	matrizAdyacencia[vOrigen][vDestino] = pesoNulo;
	matrizAdyacencia[vDestino][vOrigen] = pesoNulo;
	--vectorVertices[vOrigen].numVerticesAdyacentes;
	--vectorVertices[vDestino].numVerticesAdyacentes;
}


void Grafo::modificarPeso(vertice vOrigen, vertice vDestino, double pesoArista){
	matrizAdyacencia[vOrigen][vDestino] = pesoArista;
	matrizAdyacencia[vDestino][vOrigen] = pesoArista;
}

double Grafo::peso(vertice origen, vertice destino) {
	return matrizAdyacencia[origen][destino];
}


Grafo::vertice Grafo::primerVertice(){
	return 0;
}


Grafo::vertice Grafo::siguienteVertice(vertice verticeActual){
	return ++verticeActual;
}

Grafo::vertice Grafo::primerVerticeAdyacente(vertice vOrigen){
	Grafo::vertice verticeAdyacente = -1;
	for (int i = 0; i <= ultimoLleno; ++i){
		if (matrizAdyacencia[vOrigen][i] != pesoNulo) {
			verticeAdyacente = i;
			i = ultimoLleno + 1;
		}
	}
	return verticeAdyacente;
}


Grafo::vertice Grafo::siguienteVerticeAdyacente(vertice vOrigen, vertice vAdyacenteActual) {
	Grafo::vertice vAdyacenteSiguiente = -1;
	for (int i = vAdyacenteActual + 1; i <= ultimoLleno; ++i) {
		if (matrizAdyacencia[vOrigen][i] != pesoNulo) {
			vAdyacenteSiguiente = i;
			i = ultimoLleno + 1;
		}
	}
	return vAdyacenteSiguiente;

}


int Grafo::verticeValido(vertice vEntrada){
	return (0 <= vEntrada && vEntrada <= ultimoLleno) ? 1 : 0;
}

int Grafo::existeArista(vertice vOrigen, vertice vDestino) {
	return matrizAdyacencia[vOrigen][vDestino] != pesoNulo ? 1 : 0;
}


int Grafo::numAristas() {
	return contadorAristas;
}

int Grafo::numVertices(){
	return ultimoLleno+1;
}

int Grafo::numVerticesAdyacentes(vertice verticeEntrada){
	return vectorVertices[verticeEntrada].numVerticesAdyacentes;
}
ostream& Grafo::Vertice::imprimir(ostream& salida) {
	salida << etiqueta << " ";
	return salida;
}

ostream& Grafo::imprimir(ostream& salida) {
	salida << "Vertices:\n{";
	for (int i = 0; i <= ultimoLleno; ++i){
		vectorVertices[i].imprimir(salida);
	}
	salida << "}\nAristas:\n";
	for (int i = 0; i <= ultimoLleno; ++i) {
		for (int j = 0; j <= ultimoLleno; ++j) {
			if (matrizAdyacencia[i][j] != pesoNulo && i<j) {
				vectorVertices[i].imprimir(salida);
				salida << "----------("<< matrizAdyacencia[i][j] <<")----------";
				vectorVertices[j].imprimir(salida);
				cout << endl;
			}

		}
	}

	return salida;
}
