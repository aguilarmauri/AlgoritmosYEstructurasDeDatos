/*******************************************************************************************
  Nombre:  Metodos de Ordenamiento mediante listas
  Autores: Aguilar Mauricio - Tarazi Pedro
  Fecha: 31/05/12
  Descripcion: Implementar los algoritmos de ordenamiento de Burbuja, Insercion y 
               Seleccion basados en listas enlazadas simples, basandose en el codigo 
               dado en el item anterior, y usando solamente las funciones de mover e 
               intercambiar punteros (no datos). Ud. debera agregar al codigo provisto, 
               las funciones que resuelvan el problema, y modificar el main para que 
               trabaje acorde.
********************************************************************************************/
#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

typedef int tipolista;

class Nodo{
    protected: 
        tipolista dato;
        Nodo *next;
    public:
        Nodo() {next=NULL;};
        Nodo(tipolista a) {dato=a; next=NULL;};
        void set_dato(tipolista a) {dato=a; };
        void set_next(Nodo *n) {next=n; };
        tipolista get_dato() {return dato; };
        Nodo *get_next() {return next; };
        bool es_vacio() {return next==NULL;};
        
};

class Lista{
    protected: Nodo *czo;
    public:
            Lista() {czo=new Nodo();};
            Lista(Nodo *n) {czo=n;};
            void del(void);
            void add(tipolista d);
            bool esvacia(void);
//            tipolista cabeza(void);
            Nodo *cabeza(void);
            Lista *resto(void);
            string toPrint();   
            Nodo *get_czo(void){return czo;}
            void movepointers(Nodo *des,Nodo *ori);
            void swappointers(Nodo *des,Nodo *ori);
            void swapdata(Nodo *p,Nodo *s);
};

void Lista::del(void)
{    Nodo *aux;
     aux=czo;
     czo=czo->get_next();
     delete aux;
}

void Lista::movepointers(Nodo *des,Nodo *ori) // ambos son los anteriores
//pone ori->next a continuacion de des->next
{  
     Nodo *aux=ori->get_next();  
     ori->set_next(aux->get_next());
     aux->set_next(des->get_next());
     des->set_next(aux);             
}

void Lista::swappointers(Nodo *des,Nodo *ori) // ambos son los anteriores
//swap de des y ori
{  
     bool consec = (des->get_next() == ori);
     movepointers(des,ori);
     if (!consec) { 
        movepointers(ori,des->get_next());
     }
}

void Lista::swapdata(Nodo *p,Nodo *s)
{  
     tipolista aux=p->get_dato();
     p->set_dato(s->get_dato());
     s->set_dato(aux);
}

void Lista::add(tipolista d)
{  
     Nodo *nuevo=new Nodo(d);
     nuevo->set_next(czo);
     czo=nuevo;
}
bool Lista::esvacia(void)
{   
    return czo->es_vacio();
}
Nodo *Lista::cabeza(void)
{ 
  if(esvacia()){
                cout<<" Error, Cabeza de lista vacia - Programa abortado";
                system("PAUSE");
                abort();
  }
  return czo;
}

Lista *Lista::resto(void)
{ 
      Lista *l=new Lista(czo->get_next());
      return (l);
}

string Lista::toPrint()
{ 
     if (this->esvacia()) {
        return "";
     } else {
       std::ostringstream stm;
       stm << this->cabeza()->get_dato()<<"-"<< this->resto()->toPrint();
       return stm.str();
     }
}



void Insercion(Lista *l);
void Seleccion(Lista *l);
void Burbuja(Lista *l);
void Agregar(Lista *l, int, int);
void Borrar(Lista *l, int);

#define MAX 7

int main(){
    Lista *l=new Lista();
    int opcion, SEMILLA=3;
    
    for(;;){
            cout<<"\n Metodos de ordenamientos aplicando listas."<<endl
                <<" __________________________________________"<<endl<<endl
                <<" Ingrese una Semilla para generar la lista: ";
            cin>>SEMILLA;
     
           //Ingresar lista
           Agregar(l,MAX, SEMILLA);
           
           cout<<"\n Lista: "<<l->toPrint()<<endl<<endl
               <<" Ordenando lista..."<<endl<<endl
               <<"\t\t    Comparaciones\tMovimientos\tLista Resultante\n";
               
               cout<<"\n Insercion\t\t";
               Insercion(l);
               Borrar(l,MAX);
               
               Agregar(l,MAX, SEMILLA);
               cout<<"\n Seleccion\t\t";
               Seleccion(l);
               Borrar(l,MAX);
               
               Agregar(l,MAX, SEMILLA);
               cout<<"\n Burbuja\t\t";
               Burbuja(l);
               Borrar(l,MAX);                      
          
           cout<<endl<<endl<<" ";              
           system("PAUSE");system("CLS");
     }
     return EXIT_SUCCESS;    
}

//ORDENAMIENTO POR INSERCION
void Insercion(Lista *l)
{
     Nodo *aux=l->cabeza();
     Nodo *des;
     Nodo *ori;
     l->add(0);              //Se agrega un elemento TRANSITORIO
     int bandera=0;
     int c=0,m=0;
     c++;
     while(aux->get_next() != NULL){                    //Recorre la lista hasta el final
         if(bandera==0){ 
              c++;                             
              if(aux->get_dato() > aux->get_next()->get_dato()){ // Paso 1: Busca el 1º no ordenado.
                       ori=aux;                  //Guarda el 1º no ordenado
                       aux=l->cabeza();          //Resetea aux
                       bandera++;
              }
         }
         if(bandera==1){
              c++;                               
              if(aux->get_dato() < ori->get_dato()){             // Paso 2: Busca el punto de insercion.
              
                       des=aux;                                      //Guarda el punto de insercion.
                       l->movepointers(des,ori);                 m++; //Mueve el siguiente a ORI hasta el siguiente de DES.
                       aux=l->cabeza();     //Resetea bandera y aux.
                       bandera=0;
              }
         }       
         aux=aux->get_next();                               //Recorre la lista.
     }
     l->del();                                              //Borra el TRANSITORIO.
     cout<<c<<"\t\t    "<<m<<"\t\t"<<l->toPrint()<<endl;       
     return ;
}

//ORDENAMIENTO POR SELECCION
void Seleccion(Lista *l) 
{
     
     Nodo *aux=l->cabeza(), *posicion;
     Nodo *des;
     Nodo *ori;
     l->add(0);              //Se agrega un elemento TRANSITORIO 
     int menor, actual,c=0,m=0;
     menor=aux->get_dato();
     posicion=l->cabeza();     
     while(posicion->get_next()!= NULL)     //Recorre la lista hasta el final
     {
              while(aux->get_next()!= NULL)           //Recorre la lista hasta el final
              {
                          actual=aux->get_next()->get_dato();   c++;
                          if(actual < menor)                     //Compara menor con el valor siguiente
                          {                                   
                              menor=actual;                      
                              ori=aux;
                          }
                          aux=aux->get_next(); 
              }
              des=posicion;
              if(des->get_next() != ori->get_next())             //Si ORI y DES son distintos.
              {
                                 m++;
                                 l->swappointers(des,ori);       //Intercambia el siguiente de ORI con el siguiente de DES.
              }
              posicion=posicion->get_next();              
              aux=posicion;                               //Resetea AUX hasta el valor de POSICION
              menor=posicion->get_next()->get_dato();     //Resetea MENOR dandole el valor siguiente de POSICION
              ori=aux;                                    //Resetea ORI dandole el valor de AUX
              if(posicion->get_next()->get_next() == NULL)
              {
                                    break;
              }
     }
     l->del();                      //Se elimina el elemento TRANSITORIO.
     cout<<c<<"\t\t    "<<m<<"\t\t"<<l->toPrint()<<endl;               
}


//ORDENAMIENTO POR BURBUJA
void Burbuja(Lista *l)
{
     Nodo *ant, *aux=l->cabeza(), *pos;
     Nodo *des, *ori;
     int c=0, m=0, i=0, largo=0;
     
     while(aux->get_next()!=NULL) //Calcular el largo de la lista,
     {                            // ya sea ingresada manual o aleatoriamente, o en combinacion
       largo++;
       pos=aux;
       aux=aux->get_next();
     }

     aux=l->cabeza();
     l->add(0);
     while(largo>1){             //Recorre la lista cada vez hasta uno menos
       ant=l->cabeza();
       ori=ant;
       aux=ant->get_next();
       des=aux;i=0;
       while(i<largo){           //Recorre la lista hasta "largo" y intercambia si es necesario
               c++;
               if(aux->get_next()->get_dato()  <  aux->get_dato()){ 
                   ori=aux;                       
                   des=ant;                       
                   l->movepointers(des,ori);                        m++;
               }
               ant=ant->get_next();
               aux=ant->get_next();
               i++;
       }
      largo--;
      pos=ant;
     }
     l->del();                     //Se elimina el elemento transitorio e imprime
     cout<<c<<"\t\t    "<<m<<"\t\t"<<l->toPrint()<<endl;  
}

void Agregar(Lista *l, int max, int SEMILLA)
{   
       srand(SEMILLA);
       int A[max]; 
       for(int i=0;i<max;i++)
       {
               A[i]=rand()/1000;
       }
       for(int i=0;i<max;i++)
       {
            l->add(A[i]);
       }
}

void Borrar(Lista *l,int max)
{
     for(int i=0;i<max;i++)
     {
             l->del();
     }
}
             
