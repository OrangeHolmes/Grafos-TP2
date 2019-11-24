#include "GrafoListas.h"

ListaVertices::Vertice::ListaAristas::Arista::Arista() {
	anterior = 0;
	siguiente = 0;
	vertice = 0;
	valArista = 0;
}

ListaVertices::Vertice::ListaAristas::Arista::Arista(Vertice * vert2, int peso) {
	anterior = 0;
	siguiente = 0;
	vertice = vert2;
	valArista = peso;
}

ListaVertices::Vertice::ListaAristas::Arista::~Arista() {
	anterior = 0;
	vertice = 0;
	if (siguiente) {
		delete siguiente;
	}
}

ListaVertices::Vertice::ListaAristas::ListaAristas() {
	primera = 0;
	ultima = 0;
	contAristas = 0;
}

ListaVertices::Vertice::ListaAristas::~ListaAristas() {
	ultima = 0;
	if (primera) {
		delete primera;
	}
}

ListaVertices::Vertice::Vertice() {
	anterior = 0;
	siguiente = 0;
	etiqueta = "";
	sublista = 0;
}

ListaVertices::Vertice::Vertice(string etiq) {
	anterior = 0;
	siguiente = 0;
	etiqueta = etiq;
	sublista = 0;
}

ListaVertices::Vertice::~Vertice() {
	anterior = 0;
	if (sublista) {
		delete sublista;
	}
	if (siguiente) {
		delete siguiente;
	}
}

ListaVertices::ListaVertices() {
	primer = 0;
	ultimo = 0;
	contVertices = 0;
}

ListaVertices::~ListaVertices() {
	ultimo = 0;
	if (primer) {
		delete primer;
	}
}


void ListaVertices::agregarVertice(string etiqueta){
	Vertice * nueva = new Vertice(etiqueta);
	if(ultimo) {
		nueva->anterior = ultimo;
		ultimo->siguiente = nueva;
	}
	else {
		primer = nueva;
	}
	ultimo = nueva;
	++contVertices;
}

void ListaVertices::vaciar(){
	delete this;
}


////////////VAMOS TIIM

ostream & ListaVertices::Vertice::imprimir( ostream & salida){
	salida << etiqueta << " ";
	if(siguiente){
		siguiente->imprimir(salida);
	}
	return salida;
}
ostream & ListaVertices::imprimir( ostream & salida){
	salida << "{ ";
	if(primer){
	   primer->imprimir(salida);
	}
	salida << " }";
	return salida;
}
