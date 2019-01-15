/************************************************************************************
	Nombre: Simulación de una ciudad mediante el uso del Algoritmo de Dijkstra.
	Autores: Aguilar, Mauricio
			 Tarazi, Pedro Esequiel
	Fecha: 08/03/13
	Descripción: El trabajo consiste en simular el tráfico en una ciudad. Ud. conduce
	             un vehículo desde un punto de la ciudad a otro, y desea hacerlo de
				 la manera más rápida posible. 
				 Deberá   utilizar   un   grafo   para   representar   la   ciudad, 
				 una   cola   de   prioridad   por   semáforo (implementada con una 
				 heap en arreglo),  y deberá determinar  el  camino más corto para 
				 cada vehiculo, el cual definirá su recorrido. Para su vehículo, 
				 deberá redefinir dicho recorrido cada 2 iteraciones, teniendo en 
				 cuenta el  estado de  “saturación”  del   tráfico.  Deberá generar  
				 por  cada iteración un  “ranking”  de  los semáforos más saturados 
				 a  los efectos de habilitarlos según ese orden. Al final de cada 
				 iteración deberá mostrar el estado de cada semáforo por pantalla o 
				 sobre un archivo, a los fines de realizar el seguimiento de la
				 simulación.
************************************************************************************/

#include "Estructuras.h"
#include "matriz.h"
#include "Asignacion.h"
#include "Dijkstra.h"
#include "MostrarCalles.h"
#include "Mover.h"
#include "Heapsort.h"

using namespace std;

int main()
{
    int numCuadras, numManzanas, cant_vehiculos, n, m, autos, policias, ambulancias;
	int cant_vertices, x,z,i,k,ns, *cV[3];
    char ts='n';
    bool CiudadEsTransitada;
	Color(Base);
    SetConsoleTitleA("Algoritmos y Estructuras de Datos - Simulacion de una Ciudad");
    Color(14);
    cout<<"  ____________________________________________________________________________"
        <<"\n |                                 ";
    Color(Base);				cout<<"BIENVENIDO";							Color(14);
    cout<<"                                 |"
        <<"\n |____________________________________________________________________________|"
        <<"\n_|_                                                                          _|_"<<endl;
    Color(Base);
 
    //________________Leer archivo de configuración________________________//
        string nombre_archivo="config.txt";
        ifstream archivo_entrada;
        
        //Abrir el archivo
        archivo_entrada.open(nombre_archivo.c_str());
        //Comprobar el éxito de la apertura
        if (archivo_entrada.fail())
        {
           cout<<"\n El archivo no se abrio con exito."
               <<"\n Por favor compruebe que el archivo existe en realidad."
               <<endl<<endl;
               system("PAUSE");
               exit(1);
        }
        else
            cout<<"\n Se cargo la configuracion de la ciudad correctamente."<<endl;
    
        while(archivo_entrada.good())
        {      
              archivo_entrada>>n;
              archivo_entrada>>m;
              archivo_entrada>>cant_vehiculos;
        }
    
	    //Cerrar el archivo
        archivo_entrada.close();
    //___________________Fin lectura de Configuración_____________________________//
    
	//Condiciones de Seguridad
    if(cant_vehiculos >1000){ 
      cout<<" La cantidad de vehiculos supera la maxima.\n Fue modificada automaticamente."<<endl<<endl;
      cant_vehiculos=1000;
    }
    if(n>16){
      cout<<" La cantidad de manzanas es mayor al maximo posible.\n Fue modificado automaticamente."<<endl<<endl;
      n=16;
    }
    if(m>16){
      cout<<" La cantidad de manzanas es mayor al maximo posible.\n Fue modificado automaticamente."<<endl<<endl;
      m=16;
    }
    
    //___Cálcular cantidades___//
    Camino camino[cant_vehiculos];
    numCuadras= (2*m*n + m + n)*2;
    numManzanas= n*m;
    if(cant_vehiculos < 50)
    {
    	ambulancias= 1;
    	policias= 1;
    	autos= cant_vehiculos-ambulancias-policias;
    }
    else{
    	cant_vehiculos++;
    	autos= int(cant_vehiculos*0.95);
 		ambulancias= int(cant_vehiculos*0.02);
  	    policias= int(cant_vehiculos*0.03);
    }
    cV[0]=&autos;
    cV[1]=&ambulancias;
    cV[2]=&policias;

    //___Crear las cuadras y guardar en un arreglo sus direcciones___//
    cant_vertices=((n+1)*(m+1)), i=0,x=0,z=0;
    CiudadEsTransitada= true;  
	Cola dir[numCuadras];
    for(int a=0; a<=18*n; a++)
    {
        for(int b=0; b<=18*n; b++)
        {  
          if(mat_ady[a][b]==1){
                 Cola *calle;
                 calle = new Cola();
                 dir[i]= *calle;
                 calle->addvi(a);
                 calle->addvf(b);
                 calle->addnum(b);
                 i++;
                 if(mat_ady[a][b]==mat_ady[b][a])
                  calle->modArista(16);
          }
          x++;
          if(x==n+1){b+=16-n; x=0;}
        }
        z++;
        if(z==m+1){a+=16-m; z=0;}
    }
    numCuadras=i;

    //___Asignar autos a las cuadras___//
    Asignacion(cV, dir, numCuadras, camino);
	
	Color(11);
	cout<<"\n\n Ciudad de "<<n<<"x"<<m<<" con "<<numManzanas<<" manzanas en la que circulan:\n ";
	Color(Base);
    cout<<"                    _______                    "<<endl
	    <<"     ____         __/|      |        _0__      "<<endl
        <<"  __/_|__\\__     |       H  |     __/____\\__ "<<endl
        <<" |__________|    |__________|    |__________|  "<<endl
        <<"    O   O           O    O          O   O      "<<endl
		<<"   "<<autos<<" Autos      "<<ambulancias<<" Ambulancias    "<<policias<<" Policias\n\n";
	cout<<"_______________________________________"; system("PAUSE");
	
    //___Imprimir contenido de calles___//
    MostrarCalles(dir, ts, ns, numCuadras);
    cout<<"_______________________________________"; system("PAUSE");
    
    //___Elegir auto a seguir___//
    Color(11);
    cout<<"\n Que vehiculo desea seguir?: ";
    Color(Base);
    Color(14); cin>>ts>>ns; Color(Base);

    //Buscar el camino asociado a ese auto
    k=0;
    int NewNodoDestino;
	char rta;                       
    while( camino[k].numID != ns  || camino[k].tipo != ts ){
      k++; 
      if( k>(*cV[0]+*cV[1]+*cV[2]) ) break;
    }
    if( camino[k].numID == ns  && camino[k].tipo == ts ){
       cout<<" El vehiculo ";
       Color(14); cout<<ts<<ns; Color(Base);
       cout<<" tiene como origen al vertice "<<camino[k].ori->vf()
           <<" y como destino al vertice "<<camino[k].Destino<<endl;
       /*
	   cout<<" Desea reasignar un destino? Y o N: ";
       cin>>rta;
       if(rta=='y' || rta=='Y')
       {
       	cout<<" Ingrese Nodo Destino: ";
       	cin>>NewNodoDestino;
		camino[k].Destino= NewNodoDestino;
       }*/
    }
    else
        cout<<" El vehiculo que ingreso no se encuentra en las calles de la ciudad."<<endl;
   
    cout<<"_______________________________________"; system("PAUSE");
    
    do{
        //___Calcular el camino apropiado para cada auto con Dijkstra___//
        Dijkstra(mat_ady, dir, numCuadras, cant_vertices, camino, cV, ts, ns);
        cout<<"_______________________________________"; system("PAUSE");
       
        //___Ordenar la cola con Heapsort___//
        Heapsort(dir, numCuadras, camino, cV, ts, ns);
        cout<<"_______________________________________"; system("PAUSE");
        
        //___Iterar 2 veces. Realizar movimientos___//
        Mover(dir, camino, numCuadras, cV, ts, ns);
        cout<<"_______________________________________"; system("PAUSE");

        if( *cV[0]+*cV[1]+*cV[2] == 0 )
           CiudadEsTransitada= false;
    }while( CiudadEsTransitada );
    
    Color(10); cout<<endl<<endl<<"Fin del programa. :)"<<endl; Color(Base);
    system("PAUSE");
    return 0;
}
/*Lineas que se pueden descomentar:
	175 a 183 -> Se puede reasignar un nuevo destino
*/
