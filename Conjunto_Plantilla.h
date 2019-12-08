#ifndef CONJ_PLANTILLA
#define CONJ_PLANTILLA
#include <iostream>
using namespace std;
template <class T>
class Conjunto{
  friend ostream & operator<<(ostream & salida, Conjunto & conjEntrada){
    return conjEntrada.imprimir(salida);
  }
  //class Celda;
private:
  class Celda {
     public:
       Celda * siguiente;
       T elemento;
       int id;
       Celda(T miElemento,int idEntrada){
       this->elemento = miElemento;
       this->id = idEntrada;
       siguiente = 0;

      }
       ~Celda(){
         if(siguiente){
         delete siguiente;
       }
     }
  };
  Celda * primera;
  Celda * ultima;
  int idGlobal;
public:
  Conjunto(){
    primera = 0;
    ultima = 0;
    idGlobal = 0;
  }
  ~Conjunto(){
     if(primera){
       delete primera;
     }
   }
  int vacia(){
    return !primera;
  }
  Conjunto & agregar(T newElemento){
    Celda * nueva = new Celda(newElemento,++idGlobal);
    if(vacia()){
      primera = nueva;
      ultima = nueva;
    }
    else{
      if(noExiste(newElemento)){
        ultima->siguiente = nueva;
        ultima = nueva;
      }
      else{
        delete nueva;
      }
    }
    return *this;
  }
  int aQueConjuntoPertenece(T elementoEntrada) {
      Celda* actual = primera;
      int idConjunto = -1;
      bool seguir = true;
      while (actual != 0 && seguir) {
          if (actual->elemento == elementoEntrada) {
              idConjunto = actual->id;
              seguir = false;
          }
          actual = actual->siguiente;
      }
      return idConjunto;
  }
  void unir(T elemento1, T elemento2) {
      Celda* actual = primera;
      int idUnion = ++idGlobal;
      while (actual != 0) {
          if (actual->elemento == elemento1) {
              actual->id = idUnion;
          }
          else if (actual->elemento == elemento2) {
              actual->id = idUnion;
          }
          actual = actual->siguiente;
      }
  }
  ostream & imprimir (ostream & salida){
    salida << "{";
    Celda * actual = primera;
    while(actual!=0){
      salida<< actual->elemento<<",";
      actual = actual->siguiente;
    }
    salida<<"}";
    return salida;
  }
  int noExiste(T newElemento){ // devuelve 1 si elemento no pertenece al conjunto
    Celda * actual = primera;
    int noExiste = 1;
    while (actual!=0){
      if(actual->elemento == newElemento){
        noExiste = 0;
      }
      actual = actual->siguiente;
    }
    return noExiste;
  }
  int operator==(Conjunto & conjuntoOtro){
    Celda * actual = primera;
    Celda * actualOtra = conjuntoOtro.primera;
    int iguales = 1;
    while (actual!=0 && actualOtra!=0){
      if(actual == 0 && actualOtra != 0){
        iguales = 0;
      }
      if(actual != 0 && actualOtra == 0){
        iguales = 0;
      }

      if(actual->elemento!=actualOtra->elemento){
        iguales = 0;
      }
      actual = actual->siguiente;
      actualOtra = actualOtra->siguiente;
    }
    return iguales;
  }
  int operator!=(Conjunto & conjuntoOtro){
    Celda * actual = primera;
    Celda * actualOtra = conjuntoOtro.primera;
    int iguales = 0;
    while (actual!=0 && actualOtra!=0){
      if(actual == 0 && actualOtra != 0){
        iguales = 1;
      }
      if(actual != 0 && actualOtra == 0){
        iguales = 1;
      }
      if(actual->elemento!=actualOtra->elemento){
        iguales = 1;
      }
      actual = actual->siguiente;
      actualOtra = actualOtra->siguiente;
    }
    return iguales;
  }
};
#endif