#include "GrafoListas.h"

Grafo::Vertice::ListaAristas::Arista::Arista() {
	siguiente = 0;
	vertice = 0;
	valArista = 0;
}

Grafo::Vertice::ListaAristas::Arista::Arista(Vertice * dest, double peso) {
	siguiente = 0;
	vertice = dest;
	valArista = peso;
}

Grafo::Vertice::ListaAristas::Arista::~Arista() {
	vertice = 0;
	if (siguiente) {
		delete siguiente;
	}
}

Grafo::Vertice::ListaAristas::ListaAristas() {
	primera = 0;
	ultima = 0;
	contAristas = 0;
}

Grafo::Vertice::ListaAristas::~ListaAristas() {
	ultima = 0;
	if (primera) {
		delete primera;
	}
}

//REQUIERE QUE LA ARISTA EXISTA O SE ESPICHA
Grafo::Vertice::ListaAristas::Arista* Grafo::Vertice::ListaAristas::buscarArista(Vertice* arista) {
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

Grafo::Vertice::Vertice() {
	siguiente = 0;
	etiqueta = "";
	sublista = new Vertice::ListaAristas();
}

Grafo::Vertice::Vertice(string etiq) {
	siguiente = 0;
	etiqueta = etiq;
	sublista = new Vertice::ListaAristas();
}

Grafo::Vertice::~Vertice() {
	if (sublista) {
		delete sublista;
	}
	if (siguiente) {
		delete siguiente;
	}
}

Grafo::Grafo() {
	primer = 0;
	ultimo = 0;
	contVertices = 0;
}

Grafo::~Grafo() {
	ultimo = 0;
	if (primer) {
		delete primer;
	}
}


Grafo::Vertice* Grafo::agregarVertice(string etiqueta){
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

void Grafo::eliminarVertice(Vertice* victima) {
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
	--contVertices;
	delete victima;
}

void Grafo::vaciar(){
	delete this;
}

int Grafo::vacio() {
	return (primer) ? 0 : 1 ;
}

void Grafo::modificarVertice(Vertice* actual, string etiq) {
	actual->etiqueta = etiq;
}

string Grafo::getEtiqueta(Vertice* actual) {
	return actual->etiqueta;
}

Grafo::Vertice::ListaAristas::Arista* Grafo::agregarArista(Vertice* origen, Vertice* dest, double peso) {
	Grafo::Vertice::ListaAristas::Arista* nueva = new Grafo::Vertice::ListaAristas::Arista(dest,peso);
	Grafo::Vertice::ListaAristas::Arista* simet = new Grafo::Vertice::ListaAristas::Arista(origen, peso);
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

void Grafo::eliminarArista(Vertice* origen, Vertice* dest) {
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
	--origen->sublista->contAristas;
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
	--dest->sublista->contAristas;
	delete victimaSimet;
}

void Grafo::modificarPeso(Vertice* origen, Vertice * dest, double peso) {
	Vertice::ListaAristas::Arista* pArista = origen->sublista->buscarArista(dest);
	Vertice::ListaAristas::Arista* pAristaSimet = dest->sublista->buscarArista(origen);
	pArista->valArista = peso;
	pAristaSimet->valArista = peso;
}

double Grafo::peso(Vertice* origen, Vertice* dest) {
	Vertice::ListaAristas::Arista* pArista = origen->sublista->buscarArista(dest);
	return pArista->valArista;
}

Grafo::Vertice * Grafo::primerVertice() {
	return primer;
}

Grafo::Vertice* Grafo::siguienteVertice(Vertice* actual) {
	return actual->siguiente;
}

Grafo::Vertice* Grafo::primerVerticeAdyacente(Vertice* actual) {
	return actual->sublista->primera->vertice;
}

Grafo::Vertice* Grafo::siguienteVerticeAdyacente(Vertice* origen, Vertice* arista) {
	Grafo::Vertice::ListaAristas::Arista* pArista = origen->sublista->buscarArista(arista);
	return pArista->siguiente->vertice;
}

int Grafo::existeArista(Vertice* origen, Vertice* dest) {
	Grafo::Vertice::ListaAristas::Arista* pArista = origen->sublista->buscarArista(dest);
	return (pArista) ? 1 : 0;
}

int Grafo::numAristas() {
	Vertice* actual = primerVertice();
	int acumAristas = 0;
	while (actual) {
		acumAristas += numVerticesAdyacentes(actual);
		actual = siguienteVertice(actual);
	}
	return acumAristas;
}

int Grafo::numVertices() {
	return contVertices;
}

int Grafo::numVerticesAdyacentes(Vertice* origen) {
	return origen->sublista->contAristas;
}
////////////VAMOS TIIM

ostream & Grafo::imprimir( ostream & salida){
	salida << "{ ";
	if(primer){
	   primer->imprimir(salida);
	}
	salida << " }";
	return salida;
}
ostream & Grafo::Vertice::imprimir( ostream & salida){
	salida << etiqueta << " ";
	if(siguiente){
		siguiente->imprimir(salida);
	}
	return salida;
}
