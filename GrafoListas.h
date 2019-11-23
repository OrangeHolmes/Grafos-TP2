#ifndef _LISTATWEETS
#define _LISTATWEETS
#include<iostream>
using namespace std;
class Lista {
   class Celda;    // Prototipo
   private:
      Celda * primera;
	    Celda * ultima;
      class Celda{
	     public:
        char * usuario;
  		  int cantidadMenciones; // Nos va a ayudar a llevar un conteo de la cantidad de veces que un usuario ha sido mencionado por otro
  			Celda * anterior;
  			Celda * siguiente;
  			Cekda * abajo;
  			Celda( char* , int );
        void liberadorColumnas();
  			~Celda();
  			ostream & imprimir( ostream &);
	     };
	public:
		Lista();
		~Lista();
		Lista & pushFront(char *, int);
		Lista & pushBack(char *, int);
    int vacia();
    int compararNombres(char *, char *);
    int existeEscritor(char *, char *);
    int existeMencion(char *, char *);
    Lista & insertar(char *, int);
    Lista & insertarMencion(char *, char *);
    void ordenarLista();
		ostream & imprimir( ostream & );
};
#endif
