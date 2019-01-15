void Heapsort(Cola [], int, Camino, int*, char, int );

void Heapsort(Cola dir[], int numCuadras, Camino camino[], int* cV[],char ts, int ns)
{
  Color(Titulo);
  cout<<"\n Dando prioridad a ambulancias y policias con Heapsort...";
  Color(Base);
  
  int nV;
  vehiculo *A[17], *v_actual, *temp;
  Cola *Ordenado;
  bool EsLaCalle= false;
  
  //Buscar el camino asociado a ese auto
  int g=0;                       
  while( camino[g].numID != ns  || camino[g].tipo != ts ){
    g++; 
    if( g>(*cV[0]+*cV[1]+*cV[2]) ) break;
  }
  
  //Recorremos cuadra por cuadra para que se ordenen
  for(int c=0; c<=numCuadras; c++)
  {
    Ordenado = new Cola();
    Ordenado->addvi( dir[c].vi() );
    Ordenado->addvf( dir[c].vf() );
    Ordenado->addnum( dir[c].numero() );
    if(dir[c].colavacia())
     continue;
     
    while(!Ordenado->colavacia())
     Ordenado->desencolar();
    
    //cout<<"\n\n >Calle "<<dir[c].vi()<<"->"<<dir[c].vf()<<": ";
    
    //Asignacion de vehiculos al arreglo con el que se ordena
    nV= dir[c].tamanio();
    for(int v=1; v<=nV; v++)
    {
      A[v]=dir[c].tope();
      dir[c].desencolar();
      //Se modifica temporalmente la prioridad para evitar que intercambie los del mismo tipo
      switch(A[v]->prioridad){
       case 1: A[v]->prioridad+=(1+v); break;
       case 2: A[v]->prioridad+=(100+v); break;
       case 3: A[v]->prioridad+=(1000+v); break;
      }
      
      //Si se trata del auto que estamos siguiendo, mostrar calle donde está.
      if( camino[g].numID == A[v]->numID && camino[g].tipo == A[v]->tipo && camino[g].numID == ns  && camino[g].tipo == ts ){
        cout<<"\n El vehiculo "; Color(14); cout<<ts<<ns; Color(Base);
        cout<<" esta en la calle "<<dir[c].vi()<<"->"<<dir[c].vf()<<": ";
        EsLaCalle= true;
      }
    }
    //Muestra los vehiculos que esta en la calle
    if( EsLaCalle ){
        for(int p=nV; p>=1; p--){
         if( A[p]->numID == ns && A[p]->tipo == ts ) Color(14);
         cout<<A[p]->tipo<<A[p]->numID<<" ";
         if( A[p]->numID == ns && A[p]->tipo == ts ) Color(Base);
        }
    }
    
    //Ordenamiento de la cola actual
    for(int k=nV;k>0;k--)
    {
        for(int i=1;i<=k;i++)
        {
            v_actual=A[i];
            int padre=i/2;
            while(padre>0 && A[padre]->prioridad < v_actual->prioridad)
            {
                A[i] = A[padre];
                i=padre;
                padre=padre/2;
            }
            A[i] = v_actual;
        }
        temp = A[1];
        A[1] = A[k];
        A[k] = temp;
    }
    
    //Encolar cola ordenada en el puntero Ordenado
    for(int v=1; v<=nV; v++)
      Ordenado->encolar(A[v]);
    Ordenado->modArista( dir[c].arista() );

    //Se reestablece la prioridad
    for(int p=1; p<=nV; p++){
      switch(A[p]->tipo){
        case 'h': A[p]->prioridad=1; break;
        case 'p': A[p]->prioridad=2; break;
        case 'a': A[p]->prioridad=3; break;
      }
    }
    
    //Remplazar cola actual por la cola ordenada
    dir[c] = *Ordenado;
    
    //Si se trata de la calle del auto a seguir, mostrarla
    if( EsLaCalle ){
      cout<<"\n Calle ordenada: ";
      dir[c].Imprimir(ts,ns);
      EsLaCalle= false;
    }
    
  }
  cout<<"\n Finished Heapsort.\n";
  return;
}

/*Lineas que se pueden descomentar:
	34 -> Muestra la calle actual de cada vehiculo
	Si se comentan las lineas 103, 106 y 107, se muestran las calles ordenadas.
*/  
