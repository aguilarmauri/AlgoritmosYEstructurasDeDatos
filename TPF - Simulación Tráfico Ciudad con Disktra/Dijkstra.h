void Dijkstra(int [289][289], Cola [], int, Camino [], int*, char, int);

void Dijkstra(int matriz[289][289],Cola dir[],int numCuadras,int numVertices,Camino camino[],int* cV[3], char ts, int ns)
{
   int NodoInicial, NodoActual=-1, NodoDestino=-1, NodoActualAnterior;
   int k=0, J=0, INFINITO=666, It_aux;
   int NodoAdyacente, CantidadVehiculos=(*cV[0]+*cV[1]+*cV[2]), Daux;
   bool  ExistanNodosLibres, NoSeMostroCamCorto=true;
   Cola Vacia, *adyacente[4], *CuadraActual, *CamCortoAux[289];
   Etiqueta Etiqueta[289], EtiquetaAux;
   
   Vacia.addnum(-1);
   Color(Titulo);
   cout<<"\n Calculando el camino mas corto con Dijkstra... ";
   Color(Base);
   //Recorre vehiculo por vehiculo. Vehiculo actual: camino[J]
   for(J=0; J<CantidadVehiculos; J++) 
   {
   	 //0- Mostrar Vehiculo, Origen y Destino
      /*cout<<"\n ______________________________________________________________________________"
          <<"\n / Vehiculo: "<<camino[J].tipo<<camino[J].numID
          <<" / Nodo Origen: "<<camino[J].ori->vf()<<" / Nodo Destino: "<<camino[J].Destino
          <<"\n ______________________________________________________________________________"<<endl;*/
   	
     //1- Inicializar distancias y nodos visitados para cada auto
     for(int i=0; i<289; i++){
        Etiqueta[i].D= INFINITO;
        Etiqueta[i].NodoAnterior= &Vacia;
        Etiqueta[i].marcado= false;
     }    
	 
     //2- Definir Nodos Inicial, Actual y Destino
     NodoInicial= camino[J].ori->vf();
     NodoActual= NodoInicial;
     Etiqueta[NodoActual].D= 0;
     Etiqueta[NodoActual].marcado= true;
     NodoDestino= camino[J].Destino;
     
     //3- Borrar el camino mas corto del vehiculo actual
     for(int i=0; i<250; i++)  
      camino[J].CamCorto[i]=&Vacia;
     
     //4- Si el Origen es igual al Destino, pasar al siguiente auto.
     if( NodoInicial == NodoDestino ){
         continue;
     }
	 
     ExistanNodosLibres=true;
     while( ExistanNodosLibres )
     {
          //5- Reseteo el vector adyacente
          for(int i=0; i<4; i++) {
            adyacente[i]=&Vacia;
          }
          //6- Busca calles adyacentes no marcados y los guarda en adyacente[]
          k=0;
          for(int i=0; i<numCuadras; i++){
            if(NodoActual == dir[i].vi() && Etiqueta[dir[i].vf()].marcado==false)
            {
              adyacente[k]=&dir[i];
              k++;
            }
          }
          
          //7- Si tiene adyacentes no marcados.
          if( adyacente[0]->numero()!=-1 ){
            for(int i=0; i<k; i++)
            {
                  NodoAdyacente= adyacente[i]->vf();
                  EtiquetaAux.D= Etiqueta[NodoActual].D + adyacente[i]->tamanio();
                  for( int i=0; i<numCuadras; i++ )
                    if( NodoActual==dir[i].vi() && dir[i].vf()==NodoAdyacente ){
                        CuadraActual= &dir[i];  //NodoActual -> NodoAdyacente
                        break;
                    }
                  EtiquetaAux.NodoAnterior= CuadraActual;           
                  //Crea etiqueta, compara y deja la menor para cada nodo.
                  if( ( EtiquetaAux.D < Etiqueta[NodoAdyacente].D ) || 
				      ( EtiquetaAux.D == Etiqueta[NodoAdyacente].D && 
					    EtiquetaAux.iteracion < Etiqueta[NodoAdyacente].iteracion ) ) {
	                       Etiqueta[NodoAdyacente].D= EtiquetaAux.D;
	                       Etiqueta[NodoAdyacente].NodoAnterior= EtiquetaAux.NodoAnterior;
	                       Etiqueta[NodoAdyacente].iteracion= Etiqueta[Etiqueta[NodoAdyacente].NodoAnterior->vi()].iteracion+1;
            	       }
            }
		  }
          
          //8- Recorrer todos los nodos
          ExistanNodosLibres= false;
          for(int i=0; i<289; i++)
                //Si encuentra un nodo etiquetado y no marcado, entonces existen nodos libres.
                if( Etiqueta[i].marcado==false && Etiqueta[i].D!=INFINITO )
                    ExistanNodosLibres= true;
          
          //9- Recorre todos los nodos Etiquetados y no marcados. 
		  //Toma el nodo con el menor D acumulado. Lo declara NodoActual y lo marca.
          Daux=INFINITO;
          It_aux=INFINITO;
          for( int Nodo=0; Nodo<289; Nodo++)
                if( Etiqueta[Nodo].marcado==false && Etiqueta[Nodo].D!=INFINITO )
                   if( (Etiqueta[Nodo].D < Daux) ||
				       (Etiqueta[Nodo].D == Daux && Etiqueta[Nodo].iteracion < It_aux )){
	                     Daux= Etiqueta[Nodo].D;
	                     NodoActual= Nodo;
	                     It_aux= Etiqueta[Nodo].iteracion;
                   }
          Etiqueta[NodoActual].marcado= true;

     }  //End While

     //Si el NodoActual no tiene adyacentes, pasar al siguiente vechiculo. Ejemplo: Vertice 8.
     if( adyacente[0]->numero()==-1 && NodoActual==NodoInicial )
       continue;
     else{
         //Guardar camino mas corto en una auxiliar.
         int g=0;
         CuadraActual= Etiqueta[NodoDestino].NodoAnterior;
         while(CuadraActual->vi() != NodoInicial){
            CamCortoAux[g]= CuadraActual;
            CuadraActual= Etiqueta[CuadraActual->vi()].NodoAnterior;
            g++;
         }
         CamCortoAux[g++]= CuadraActual;
         CuadraActual= Etiqueta[CuadraActual->vi()].NodoAnterior;
         
         //Guardar camino mas corto en CamCorto
         int f=g;
         for(int i=0; i<g; i++){
            camino[J].CamCorto[i]= CamCortoAux[--f];
            camino[J].CamCorto[i]->addnum(123);
            }
         
         //Mostrar el Camino corto guardado
        /*cout<<endl<<"  CamCorto: ";
         for(int i=0; i<250; i++){
            if( camino[J].CamCorto[i]->numero()==123 )
              {cout<<camino[J].CamCorto[i]->vi()<<"->"<<camino[J].CamCorto[i]->vf()<<"   ";}
         }*/
     }//En Else
     
     //Si se trata del auto a seguir, mostrar su camino mas corto 
     if( camino[J].numID==ns && camino[J].tipo==ts && NoSeMostroCamCorto ){
       cout<<"\n El vehiculo "; Color(14); cout<<ts<<ns; Color(Base);
       cout<<" tiene como camino mas corto al siguiente:\n ";
       for(int i=0; i<250; i++){
          if( camino[J].CamCorto[i]->numero()==123 ){
          	 Color(12); cout<<camino[J].CamCorto[i]->vi(); Color(Base);
			 cout<<"->";
			 Color(12); cout<<camino[J].CamCorto[i]->vf()<<"   "; Color(Base);
		  }
       }
       NoSeMostroCamCorto=false;
     }
     
   }//End For autos
    cout<<"\n Finished Dijkstra.\n";
} //End Dijkstra

/*Lineas que se pueden descomentar:
	20 a 23 -> Mostrar Vehiculo, Origen y Destino
	134 a 138 -> Muestra el camino mas corto para cada vehiculo
*/
