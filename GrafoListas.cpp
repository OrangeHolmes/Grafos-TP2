#include "GrafoListas.h"

ListaVertices::Vertice::ListaAristas::Arista::Arista() {
	anterior = 0;
	siguiente = 0;
	vertice = 0;
	valArista = 0;
}

ListaVertices::Vertice::ListaAristas::Arista::Arista(Vertice * dest, int peso) {
	anterior = 0;
	siguiente = 0;
	vertice = dest;
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

//REQUIERE QUE LA ARISTA EXISTA O SE ESPICHA
ListaVertices::Vertice::ListaAristas::Arista* ListaVertices::Vertice::ListaAristas::buscarArista(Vertice* arista) {
	Arista* actual = primera;
	if (actual) {
		int seguir = 1;
		while (actual && seguir) {
			if (actual->vertice == arista) {
				seguir = 0;
			}
			else {
				actual = actual->siguiente;
			}
		}
	}
	return actual;
}

ListaVertices::Vertice::Vertice() {
	anterior = 0;
	siguiente = 0;
	etiqueta = "";
	sublista = new Vertice::ListaAristas();
}

ListaVertices::Vertice::Vertice(string etiq) {
	anterior = 0;
	siguiente = 0;
	etiqueta = etiq;
	sublista = new Vertice::ListaAristas();
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


ListaVertices::Vertice* ListaVertices::agregarVertice(string etiqueta){
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
	return nueva;
}

void ListaVertices::eliminarVertice(Vertice* victima) {
	if (victima->anterior) {
		victima->anterior->siguiente = victima->siguiente;
	}
	if (victima->siguiente) {
		victima->siguiente->anterior = victima->anterior;
	}
	victima->siguiente = 0;
	delete victima;
}

void ListaVertices::vaciar(){
	delete this;
}

void ListaVertices::modificarVertice(Vertice* actual, string etiq) {
	actual->etiqueta = etiq;
}

string ListaVertices::getEtiqueta(Vertice* actual) {
	return actual->etiqueta;
}

ListaVertices::Vertice::ListaAristas::Arista* ListaVertices::agregarArista(Vertice* origen, Vertice* dest, int peso) {
	ListaVertices::Vertice::ListaAristas::Arista* nueva = new ListaVertices::Vertice::ListaAristas::Arista(dest,peso);
	if (origen->sublista->primera) {
		origen->sublista->ultima->siguiente = nueva;
		nueva->anterior = origen->sublista->ultima;
	}
	else {
		origen->sublista->primera = nueva;
	}
	origen->sublista->ultima = nueva;
	++origen->sublista->contAristas;
	return nueva;
}

void ListaVertices::eliminarArista(Vertice* origen, Vertice* dest) {
	Vertice::ListaAristas::Arista* victima = origen->sublista->buscarArista(dest);
	if (victima->anterior) {
		victima->anterior->siguiente = victima->siguiente;
	}
	if (victima->siguiente) {
		victima->siguiente->anterior = victima->anterior;
	}
	victima->siguiente = 0;
	delete victima;
}

void ListaVertices::modificarPeso(Vertice* origen, Vertice * dest, int peso) {
	Vertice::ListaAristas::Arista* pArista = origen->sublista->buscarArista(dest);
	pArista->valArista = peso;
}

int ListaVertices::peso(Vertice* origen, Vertice* dest) {
	Vertice::ListaAristas::Arista* pArista = origen->sublista->buscarArista(dest);
	return pArista->valArista;
}

ListaVertices::Vertice * ListaVertices::primerVertice() {
	return primer;
}

ListaVertices::Vertice* ListaVertices::siguienteVertice(Vertice* actual) {
	return actual->siguiente;
}

ListaVertices::Vertice::ListaAristas::Arista * ListaVertices::primerVerticeAdyacente(Vertice* actual) {
	return actual->sublista->primera;
}

ListaVertices::Vertice::ListaAristas::Arista* ListaVertices::siguienteVerticeAdyacente(Vertice* origen, Vertice* arista) {
	ListaVertices::Vertice::ListaAristas::Arista* pArista = origen->sublista->buscarArista(arista);
	return pArista->siguiente;
}

int ListaVertices::existeArista(Vertice* origen, Vertice* dest) {
	ListaVertices::Vertice::ListaAristas::Arista* pArista = origen->sublista->buscarArista(dest);
	return (pArista) ? 1 : 0;
}

int ListaVertices::numAristas(Vertice* origen) {
	return origen->sublista->contAristas;
}

int ListaVertices::numVertices() {
	return contVertices;
}

int ListaVertices::numVerticesAdyacentes(Vertice* origen) {
	return numAristas(origen);
}
////////////VAMOS TIIM

ostream & ListaVertices::imprimir( ostream & salida){
	salida << "{ ";
	if(primer){
	   primer->imprimir(salida);
	}
	salida << " }";
	return salida;
}
ostream & ListaVertices::Vertice::imprimir( ostream & salida){
	salida << etiqueta << " ";
	if(siguiente){
		siguiente->imprimir(salida);
	}
	return salida;
}
