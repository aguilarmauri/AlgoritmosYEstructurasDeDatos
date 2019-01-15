#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <time.h>
#include <string>
#include <cmath>
#include <windows.h>
#include <stdio.h>
#define Base 15
#define Titulo 11

using namespace std;

void Color(int);

void Color(int num)
{
    HANDLE Manejador;
    Manejador = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(Manejador, num);
}

struct vehiculo{
       int numID, prioridad;
       char tipo; // a=auto ; p=policia ; h=ambulancia
       };
          
// DEFINIMOS LOS METODOS PARA MANIPULAR NODOS
class Nodo{
    protected: 
        vehiculo *dato;
        Nodo *next;
    public:
        Nodo() {next=NULL;};
        Nodo(vehiculo *a) {dato=a; next=NULL;};
        void set_dato(vehiculo *a) {dato=a; };
        void set_next(Nodo *n) {next=n; };
        vehiculo * get_dato() {return dato; };
        Nodo *get_next() {return next; };
        bool es_vacio() {return next==NULL;};
        
};

// CLASE LISTA
class Lista{
    protected: Nodo *czo;
               int numCola, vi, vf, arista;
    public:
            Lista() {czo=new Nodo(); arista=8;  };
            Lista(Nodo *n) {czo=n;};
            void del(void);
            void add(vehiculo *d);
            bool esvacia(void);
            vehiculo * cabeza(void);
            Lista *resto(void);
            void toPrint(char ts, int ns);
            Nodo *get_czo(void){return czo;}
            int get_tam();
            int num();
            int numvi();
            int numvf();
            int verArista() {return arista;};
            int ModArista(int numero) {arista=numero;};
            void addN(int numero){numCola=numero; return;};
            void addVI(int numero){vi=numero; return;};
            void addVF(int numero){vf=numero; return;};

};
// CLASE COLA
class Cola{
      private:
              Lista *l;
              Nodo *czoq;
              void update_start(Lista *l,Nodo *p);
              void do_desencolar(Nodo *p,Nodo *s);
      public:
      Cola(void){l=new Lista();update_start(l,NULL);};
      ~Cola(void) {delete(l);};
      vehiculo * tope();
      int colavacia() { return l->esvacia();};
      void encolar(vehiculo *a) ;
      void desencolar();
      int Ultimo();
      int tamanio(){return l->get_tam();};
      void Imprimir(char ts, int ns){l->toPrint(ts, ns);}; 
      int numero(){l->num();};
      int vi(){l->numvi();};
      int vf(){l->numvf();};
      int arista(){l->verArista();};
      void modArista(int numero) {l->ModArista(numero);};
      void addnum(int numero){l->addN(numero);};
      void addvi(int numero){l->addVI(numero);};
      void addvf(int numero){l->addVF(numero);};
};
 
            //METODOS DE LA CLASE LISTA QUE SE USARAN EN LA PILA
            int Lista::num()
            {
                return numCola;
            } 
            int Lista::numvi()
            {
                return vi;
            }
            int Lista::numvf()
            {
                return vf;
            }
            void Lista::del(void)
            {    Nodo *aux;
                 aux=czo;
                 czo=czo->get_next();
                 delete aux;
            }
            void Lista::add(vehiculo *d)
            {  
                 Nodo *nuevo=new Nodo(d);
                 nuevo->set_next(czo);
                 czo=nuevo;
            }
            bool Lista::esvacia(void)
            {   
                return czo->es_vacio(); //devuelve un cero si el next es NULL
            }
            
            vehiculo * Lista::cabeza(void) 
            { 
              if(esvacia()){
                            cout<<" Error, Cabeza de pila vacia";
                            return NULL;
              }
              return czo->get_dato(); //devuelve *dato
            }
            
            Lista *Lista::resto(void)
            { 
                  Lista *l=new Lista(czo->get_next());
                  return (l);
            }
            
            void Lista::toPrint(char ts, int ns)
            { 
                 if (this->esvacia()) {return;}
                 else{
                    vehiculo *u= this->cabeza();
                    if(u!=NULL){
                      if( (this->cabeza())->tipo == ts && (this->cabeza())->numID == ns ){
                       Color(14);
                       cout << (this->cabeza())->tipo << (this->cabeza())->numID ;
                       Color(Base);
                       cout << ".";
                      }
                      else
                         cout << (this->cabeza())->tipo << (this->cabeza())->numID << ".";
                    }//End If
                    this->resto()->toPrint(ts, ns);
                    return; 
                    
                 }//End Else
            }
                         
            // METODOS DE LA CLASE COLA
            int Lista::get_tam()
            {
                      Nodo *aux;
                      aux=czo;
                      int tam = 0;
                      while(aux->get_next() != NULL)
                      {
                          aux=aux->get_next();
                          tam++;
                      }
                      return tam;
            }
            vehiculo * Cola::tope() {
                       if (colavacia()){
                          cout<<"Error: Cola vacia"<<endl;
                          return NULL;
                       } 
                       else
                          return czoq->get_dato();
            }
            void Cola::encolar(vehiculo *a) {
                 l->add(a);
                 if (czoq==NULL) {
                    update_start(l,czoq);
                 }
            }
            void Cola::desencolar() {
                       if (colavacia())
                          cout<<"Error: Cola vacia"<<endl;
                       else {
                          do_desencolar(l->get_czo(),NULL);
                          update_start(l,NULL);
                       }
            }      
            void Cola::do_desencolar(Nodo *p,Nodo *s){
                 if (p->get_next()==NULL) {
                     if (s!=NULL) {
                        s->set_next(NULL);
                     }
                     delete(p);
                 }else {
                     this->do_desencolar(p->get_next(),p);
                 }
            }
            void Cola::update_start(Lista *l,Nodo *p){
                 if (l->esvacia()) {
                      czoq=p;
                 }else {
                      this->update_start(l->resto(),l->get_czo());
                 }
            }
            
struct Camino {
       int numID, Destino;
       char tipo;
       Cola *ori, *CamCorto[250];
       bool NoSeMovio;
};

struct Etiqueta {
       int D, iteracion; 
       bool marcado;
       Cola *NodoAnterior;
       Etiqueta (){iteracion=0;};
};
