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
		Vertice * anterior;
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

			class Arista {
			public:
				Arista * anterior;
				Arista * siguiente;
				Vertice * vertice;
				int valArista;
				Arista();
				Arista(Vertice*,int);
				~Arista();
			};
		};
	};
public:
	ListaVertices();
	~ListaVertices();
	void vaciar();
	void agregarVertice(string);
	void eliminarVertice(Vertice*);
	void modificarVertice(Vertice*, string);
	string getEtiqueta(Vertice*);
	void agregarArista(Vertice*, Vertice*,int);
	void eliminarArista(Vertice*, Vertice*);
	void modificarPeso(Vertice*, Vertice*, int);
	int peso(Vertice*, Vertice*);
	Vertice * primerVertice();
	Vertice * siguienteVertice(Vertice*);
	Vertice * primerVerticeAdyacente(Vertice*);
	Vertice * siguienteVerticeAdyacente(Vertice*, Vertice*);
	int existeArista(Vertice*, Vertice*);
	int numAristas(Vertice*);
	int numVertices();
	int numVerticesAdyacentes(Vertice*);

	ostream & imprimir( ostream & );
	
};
#endif
