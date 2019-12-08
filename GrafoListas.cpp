#include "GrafoListas.h"

Grafo::Vertice::ListaAristas::Arista::Arista() {
	siguiente = 0;
	vertice = 0;
	valArista = 0;
}

Grafo::Vertice::ListaAristas::Arista::Arista(Vertice* dest, double peso) {
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
	totAristas = 0;
}

Grafo::~Grafo() {
	ultimo = 0;
	if (primer) {
		delete primer;
	}
	primer = 0;
}


void Grafo::agregarVertice(string etiqueta){
	vertice nueva = new Vertice(etiqueta);
	if(ultimo) {
		ultimo->siguiente = nueva;
	}
	else {
		primer = nueva;
	}
	ultimo = nueva;
	++contVertices;
}

void Grafo::eliminarVertice(vertice victima) {
	vertice actual = primerVertice();
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
	delete primer;
	primer = 0;
	ultimo = 0;
}

int Grafo::vacio() {
	return (primer) ? 0 : 1 ;
}

void Grafo::modificarVertice(vertice actual, string etiq) {
	actual->etiqueta = etiq;
}

string Grafo::getEtiqueta(vertice actual) {
	return actual->etiqueta;
}


//NO VALIDA QUE LA ARISTA NO EXISTA PREVIAMENTE
void Grafo::agregarArista(vertice origen, vertice dest, double peso) {
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
	++totAristas;
}

void Grafo::eliminarArista(vertice origen, vertice dest) {
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
	--totAristas;
}

void Grafo::modificarPeso(vertice origen, vertice dest, double peso) {
	Vertice::ListaAristas::Arista* pArista = origen->sublista->buscarArista(dest);
	Vertice::ListaAristas::Arista* pAristaSimet = dest->sublista->buscarArista(origen);
	pArista->valArista = peso;
	pAristaSimet->valArista = peso;
}

double Grafo::peso(vertice origen, vertice dest) {
	Vertice::ListaAristas::Arista* pArista = origen->sublista->buscarArista(dest);
	return pArista->valArista;
}

Grafo::Vertice * Grafo::primerVertice() {
	return primer;
}

Grafo::vertice Grafo::siguienteVertice(vertice actual) {
	return actual->siguiente;
}

int Grafo::verticeValido(vertice actual) {
	return (actual) ? 1 : 0;
}

Grafo::vertice Grafo::primerVerticeAdyacente(vertice actual) {
	return actual->sublista->primera->vertice;
}

Grafo::vertice Grafo::siguienteVerticeAdyacente(vertice origen, vertice arista) {
	Grafo::Vertice::ListaAristas::Arista* pArista = origen->sublista->buscarArista(arista);
	if (pArista->siguiente)
		return pArista->siguiente->vertice;
	else
		return 0;
}

int Grafo::existeArista(vertice origen, vertice dest) {
	Grafo::Vertice::ListaAristas::Arista* pArista = origen->sublista->buscarArista(dest);
	return (pArista) ? 1 : 0;
}

int Grafo::numAristas() {
	return totAristas;
}

int Grafo::numVertices() {
	return contVertices;
}

int Grafo::numVerticesAdyacentes(vertice origen) {
	return origen->sublista->contAristas;
}
////////////VAMOS TIIM

ostream& Grafo::imprimir(ostream& salida) {
	vertice actual = primer;
	salida << "Vertices:\n{";
	for (int i = 0; i < contVertices; ++i) {
		salida << actual->etiqueta << " ";
		actual = actual->siguiente;
	}
	salida << "}\nAristas:\n";
	actual = primer;
	Vertice::ListaAristas::Arista *  arista;
	for (int i = 0; i < contVertices; ++i) {
		arista = actual->sublista->primera;
		for (int j = 0; j < actual->sublista->contAristas; ++j) {
			salida << actual->etiqueta;
			salida << "----------(" << arista->valArista << ")----------";
			salida <<arista->vertice->etiqueta;
			cout << endl;
			arista = arista->siguiente;
		}
		actual = actual->siguiente;
	}
	return salida;
}
