#ifndef GRAFO_MATRIZADYACENCIA
#define GRAFO_MATRIZADYACENCIA
#include <iostream>
#include <string>
#define pesoNulo 3.14159265358979323846
#define maxVertices 30 
using namespace std;


class Grafo{ // Implmentación con matriz de adyacencia
	class Vertice; // Prototipo Vertice
	typedef int vertice;
private:
	class Vertice {
	public:
		string etiqueta;
		int numVerticesAdyacentes;
		Vertice();
		Vertice(string);
		~Vertice();
		ostream& imprimir(ostream&);
	};
	
	Vertice vectorVertices[maxVertices];
	double matrizAdyacencia[maxVertices][maxVertices];
	int ultimoLleno;
	int contadorAristas;
public:
	Grafo();
	~Grafo();
	void vaciar();
	int vacio();
	void agregarVertice(string);
	void eliminarVertice(vertice);
	void modificarVertice(vertice, string);
	string getEtiqueta(vertice);
	void agregarArista(vertice, vertice, double);
	void eliminarArista(vertice, vertice);
	void modificarPeso(vertice, vertice, double);
	double peso(vertice, vertice);
	vertice primerVertice();
	vertice siguienteVertice(vertice);
	vertice primerVerticeAdyacente(vertice);
	vertice siguienteVerticeAdyacente(vertice, vertice);
	int verticeValido(vertice);
	int existeArista(vertice, vertice);
	int numAristas();
	int numVertices();
	int numVerticesAdyacentes(vertice);
	ostream& imprimir(ostream&);
};
#endif