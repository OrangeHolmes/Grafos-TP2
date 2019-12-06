#ifndef LISTA_LISTAS
#define LISTA_LISTAS
#include<iostream>
using namespace std;

class Grafo {	//LISTA DE VERTICES
	class Vertice;    // Prototipo de VERTICE
private:
	Vertice * primer;
	Vertice * ultimo;
	int contVertices;
	class Vertice { // VERTICE
		class ListaAristas; //Prototipo de LISTA DE ARISTAS

	public:
		Vertice * siguiente;
		string etiqueta;
		ListaAristas * sublista;
		Vertice();
		Vertice(string);
  		~Vertice();
  		ostream & imprimir( ostream &);

		class ListaAristas {  //LISTA DE ARISTAS
			class Arista; // ARISTA

		public:
			Arista * primera;
			Arista * ultima;
			int contAristas;
			ListaAristas();
			~ListaAristas();
			Arista* buscarArista(Vertice*);

			class Arista {
			public:
				Arista * siguiente;
				Vertice * vertice;
				double valArista;
				Arista();
				Arista(Vertice* , double);
				~Arista();
			};
		};
	};
public:
	typedef Vertice* vertice;
	Grafo();
	~Grafo();
	void vaciar();
	int vacio();
	void agregarVertice(string);
	void eliminarVertice(vertice);
	void modificarVertice(vertice, string);
	string getEtiqueta(vertice);
	void agregarArista(vertice, vertice,double);
	void eliminarArista(vertice, vertice);
	void modificarPeso(vertice, vertice, double);
	double peso(vertice, vertice);
	vertice primerVertice();
	vertice siguienteVertice(vertice);
	int verticeValido(vertice);
	vertice primerVerticeAdyacente(vertice);
	vertice siguienteVerticeAdyacente(vertice, vertice);
	int existeArista(vertice, vertice);
	int numAristas();
	int numVertices();
	int numVerticesAdyacentes(vertice);
	ostream & imprimir( ostream & );	
};
#endif
