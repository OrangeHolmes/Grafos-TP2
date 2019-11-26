#include "GrafoListas.h"

ListaVertices::Vertice::ListaAristas::Arista::Arista() {
	siguiente = 0;
	vertice = 0;
	valArista = 0;
}

ListaVertices::Vertice::ListaAristas::Arista::Arista(Vertice * dest, double peso) {
	siguiente = 0;
	vertice = dest;
	valArista = peso;
}

ListaVertices::Vertice::ListaAristas::Arista::~Arista() {
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
	siguiente = 0;
	etiqueta = "";
	sublista = new Vertice::ListaAristas();
}

ListaVertices::Vertice::Vertice(string etiq) {
	siguiente = 0;
	etiqueta = etiq;
	sublista = new Vertice::ListaAristas();
}

ListaVertices::Vertice::~Vertice() {
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
	Vertice* actual = primerVertice();
	if (victima == primer) {
		primer = victima->siguiente;
		if (victima == ultimo) {
			ultimo = 0;
		}
	}
	else {
		while(actual->siguiente && actual->siguiente->etiqueta.compare(victima->etiqueta) != 0) {
			actual = actual->siguiente;
		}
		actual->siguiente = victima->siguiente;
		if (victima == ultimo) {
			ultimo = actual;
		}
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

ListaVertices::Vertice::ListaAristas::Arista* ListaVertices::agregarArista(Vertice* origen, Vertice* dest, double peso) {
	ListaVertices::Vertice::ListaAristas::Arista* nueva = new ListaVertices::Vertice::ListaAristas::Arista(dest,peso);
	ListaVertices::Vertice::ListaAristas::Arista* simet = new ListaVertices::Vertice::ListaAristas::Arista(origen, peso);
	if (origen->sublista->primera) {
		origen->sublista->ultima->siguiente = nueva;
	}
	else {
		origen->sublista->primera = nueva;
	}
	origen->sublista->ultima = nueva;
	++origen->sublista->contAristas;

	if (dest->sublista->primera) {
		dest->sublista->ultima->siguiente = simet;
	}
	else {
		dest->sublista->primera = simet;
	}
	dest->sublista->ultima = simet;
	++dest->sublista->contAristas;
	return nueva;
}

void ListaVertices::eliminarArista(Vertice* origen, Vertice* dest) {
	Vertice::ListaAristas::Arista* victima = origen->sublista->buscarArista(dest);
	Vertice::ListaAristas::Arista* victimaSimet = dest->sublista->buscarArista(origen);
	Vertice::ListaAristas::Arista* actual = origen->sublista->primera;

	if (victima == origen->sublista->primera) {
		origen->sublista->primera  = victima->siguiente;
		if (victima == origen->sublista->ultima) {
			origen->sublista->ultima = 0;
		}
	}
	else {
		while (actual->siguiente && actual->siguiente->vertice != dest) {
			actual = actual->siguiente;
		}
		actual->siguiente = victima->siguiente;
		if (victima == origen->sublista->ultima) {
			origen->sublista->ultima = actual;
		}
	}
	victima->siguiente = 0;
	delete victima;

	actual = dest->sublista->primera;
	if (victimaSimet == dest->sublista->primera) {
		dest->sublista->primera = victimaSimet->siguiente;
		if (victimaSimet == dest->sublista->ultima) {
			dest->sublista->ultima = 0;
		}
	}
	else {
		while (actual->siguiente && actual->siguiente->vertice != origen) {
			actual = actual->siguiente;
		}
		actual->siguiente = victimaSimet->siguiente;
		if (victimaSimet == dest->sublista->ultima) {
			dest->sublista->ultima = actual;
		}
	}
	victimaSimet->siguiente = 0;
	delete victimaSimet;
}

void ListaVertices::modificarPeso(Vertice* origen, Vertice * dest, double peso) {
	Vertice::ListaAristas::Arista* pArista = origen->sublista->buscarArista(dest);
	Vertice::ListaAristas::Arista* pAristaSimet = dest->sublista->buscarArista(origen);
	pArista->valArista = peso;
	pAristaSimet->valArista = peso;
}

double ListaVertices::peso(Vertice* origen, Vertice* dest) {
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

int ListaVertices::numAristas() {
	Vertice* actual = primerVertice();
	int acumAristas = 0;
	while (actual) {
		acumAristas += numVerticesAdyacentes(actual);
		actual = siguienteVertice(actual);
	}
	return acumAristas;
}

int ListaVertices::numVertices() {
	return contVertices;
}

int ListaVertices::numVerticesAdyacentes(Vertice* origen) {
	return origen->sublista->contAristas;
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
