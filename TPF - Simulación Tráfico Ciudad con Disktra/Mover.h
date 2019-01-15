void Mover(Cola [], Camino [], int, int*, char , int);

void Mover(Cola dir[], Camino camino[], int numCuadras, int* cV[], char ts, int ns)
{
  Color(Titulo);
  cout<<"\n Realizando Movimientos..."<<endl;
  Color(Base);
  
  Cola *CalleSiguiente, *satur[numCuadras], Vacia;
  vehiculo *v;
  int aux, capSiguiente, k, nCuadra, nVehiculos, n, NodoDestino, numMovimientos=2;
  nVehiculos= ( *cV[0] + *cV[1] + *cV[2] );
  Camino CopiaCamino[nVehiculos], Nulo;
  
  Vacia.addnum(-1); Vacia.addvf(-2); Vacia.modArista(-5);
  Nulo.tipo='z'; Nulo.numID=999;
  
  for(int m=0; m<numMovimientos; m++)
  {
      cout<<"\n Movimiento "<<m+1<<"................................................"<<endl;
      aux=0;
      //Reordenar calles de mas a menos ocupadas, en satur[0,...,aux] 
      for(int j=16; j>0; j--)
         for(int i=0; i<numCuadras; i++)
           if(dir[i].tamanio() == j){
            satur[aux] = &dir[i];
            aux++;
           }     
      
      /*cout<<"\n Que calles tienen las cuadras del satur:"<<endl;
      for(int t=0; t<aux; t++)
       cout<<" "<<satur[t]->vi()<<"->"<<satur[t]->vf()<<endl;*/
      
	  //Se resetea el indicador de movimiento de cada vehiculo.
	  for(int i=0; i<nVehiculos; i++)
	      camino[i].NoSeMovio=true;
	      
	  //Recorrer calle por calle de mas ocupadas a menos ocupadas
      for(int i=0; i<aux; i++)
      {
       //cout<<"\n  Moviendo de la calle "<<satur[i]->vi()<<"->"<<satur[i]->vf()<<" los vehiculos: ";
       int tam_calle=(satur[i]->tamanio());
		
       //Recorrer vehiculo por vehiculo de la calle actual
       for(int j=0; j<tam_calle; j++)
       {
          v = satur[i]->tope();            //Hacer una copia del vehiculo
          //cout<<v->tipo <<v->numID <<" ";
                 
          //Buscar el camino asociado a ese auto
          k=0;                       
          while( (camino[k].numID != v->numID  || camino[k].tipo != v->tipo) && k<nVehiculos )
            k++;
		   
          //Si no tiene calles hacia donde moverse, calculadas por Dijkstra, desencola. (Si CamCorto es nulo)
          if(camino[k].CamCorto[m]->numero() != 123){
             satur[i]->desencolar(); 
             //Elimina el camino asociado.
			 for(int i=0; i<nVehiculos; i++){
                  CopiaCamino[i]= camino[i];
                  camino[i]=Nulo;
                 }  
             n=0;
             for(int x=0; x<nVehiculos; x++){
                if( CopiaCamino[x].numID != v->numID || CopiaCamino[x].tipo != v->tipo ){
                  camino[n++]= CopiaCamino[x];
                }
          	 }
          	         	 
             if(v->tipo=='a') *cV[0]-=1;
             if(v->tipo=='h') *cV[1]-=1;
             if(v->tipo=='p') *cV[2]-=1;
             if( v->numID == ns   &&   v->tipo == ts ){
              	Color(172);
                      cout<<"\n El vehiculo "; cout<<ts<<ns;
                      cout<<" ha llegado a destino y salido de la simulacion.";}
                Color(Base);
           }
           else{ 
              //Asignar calles
              CalleSiguiente = camino[k].CamCorto[m];          
              NodoDestino = camino[k].Destino;
              capSiguiente = CalleSiguiente->arista() - CalleSiguiente->tamanio(); //Calcular espacio disponible

               //Si tiene espacio, encolar el auto actual y desenconlarlo de la cola donde estaba
               if( capSiguiente>0  &&  camino[k].NoSeMovio){
               	   //Desencolar vehiculo de la calle
				   satur[i]->desencolar();
				   camino[k].NoSeMovio= false;
				   
                   //Si la calle no es el destino, encolar.
                   if( CalleSiguiente->vf() != NodoDestino ){
                   	   CalleSiguiente->encolar(v);
                   	   camino[k].ori = CalleSiguiente;  //Redefine el origen del vehiculo actual.
				   }
                   else{ //Llego a destino.
                     //cout<<" \n   El auto "<<v->tipo<<v->numID<<" llego a destino y queda fuera de la simulacion.\n";
                     
					 //Eliminar camino asociado                   
                     for(int i=0; i<nVehiculos; i++){
                      CopiaCamino[i]= camino[i];
                      camino[i]=Nulo;
                     }
                     n=0;
                     for(int x=0; x<nVehiculos; x++)
                      if( CopiaCamino[x].numID != v->numID || CopiaCamino[x].tipo != v->tipo )
                       camino[n++]= CopiaCamino[x];
                    
                     if(v->tipo=='a') *cV[0]-=1;
                     if(v->tipo=='h') *cV[1]-=1;
                     if(v->tipo=='p') *cV[2]-=1;
                     if(v->numID == ns   &&   v->tipo == ts ){
                     	Color(172);
                        cout<<"\n El vehiculo "; cout<<ts<<ns; 
                        cout<<" ha llegado a destino y salido de la simulacion.";
                        Color(Base);
                     }
                   }
               }
               else{
                    //cout<<"\n No hay lugar en la calle "<<CalleSiguiente->vi()<<"->"<<CalleSiguiente->vf();
                    break;
               }
           }
       }//End for autos
      }//End for calles  
	
      MostrarCalles(dir, ts, ns, numCuadras);
  } //End For Movimientos
 
 cout<<"\n Finished Mover.\n";
 return;
}

/*Lineas que se pueden descomentar:
	30 a 32 -> Con esto se pueden ver las calles por orden de saturacion
	41 -> Calles con vehiculos en movimiento
	48 -> Vehiculos en movimiento
	97 -> Indica el vehiculo que llego a destino
	121 -> Avisador de cuando no hay lugar en una calle
*/
