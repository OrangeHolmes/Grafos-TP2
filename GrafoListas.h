#ifndef LISTA_LISTAS
#define LISTA_LISTAS
#include<iostream>
using namespace std;

class ListaVertices {	//LISTA DE VERTICES
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
				Arista(Vertice*,double);
				~Arista();
			};
		};
	};
public:
	ListaVertices();
	~ListaVertices();
	void vaciar();
	Vertice* agregarVertice(string);
	void eliminarVertice(Vertice*);
	void modificarVertice(Vertice*, string);
	string getEtiqueta(Vertice*);
	Vertice::ListaAristas::Arista* agregarArista(Vertice*, Vertice*,double);
	void eliminarArista(Vertice*, Vertice*);
	void modificarPeso(Vertice*, Vertice*, double);
	double peso(Vertice*, Vertice*);
	Vertice * primerVertice();
	Vertice * siguienteVertice(Vertice*);
	Vertice::ListaAristas::Arista * primerVerticeAdyacente(Vertice*);
	Vertice::ListaAristas::Arista * siguienteVerticeAdyacente(Vertice*, Vertice*);
	int existeArista(Vertice*, Vertice*);
	int numAristas();
	int numVertices();
	int numVerticesAdyacentes(Vertice*);
	ostream & imprimir( ostream & );
	
};
#endif
