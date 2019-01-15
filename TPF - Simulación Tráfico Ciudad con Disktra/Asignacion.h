void Asignacion(int*, Cola [], int, Camino []);

void Asignacion(int* cV[3], Cola dir[], int NumCuadras, Camino camino[])
{
     int k=0, aleatorio, aleatorioDes, num, prioridad;
     int autos, ambulancias, policias, cantV, arista; 
     char tipo;
     
     autos= *cV[0];
     ambulancias= *cV[1];
     policias= *cV[2];
     Color(Titulo);
     cout<<"\n Asignando Vehiculos y Caminos:";
     Color(Base);
	
     for(int I=0; I<3;I++)
     {
         switch(I)
         {
          case 0: cantV=autos; tipo='a'; prioridad=3; break;
          case 1: cantV=ambulancias; tipo='h'; prioridad=1; break;
          case 2: cantV=policias; tipo='p'; prioridad=2; break;
         }
         num=1;
         cout<<"\n Asignando ";
         if(tipo=='a') cout<<"autos. ";
         if(tipo=='p') cout<<"policias. ";
         if(tipo=='h') cout<<"ambulancias. ";
         cout<<"Hay "<<cantV<<" para repartir. ";
         
         srand ( time(NULL) );              //Genera semilla para numeros aleatorios.
         //Recorre cada calle.
		 for(int i=0; i<NumCuadras; i++)
         {
         		 arista= dir[i].arista();
                 //Genera un numero aleatorio para cada cuadra
                 do{
                      aleatorio = rand()%(arista+1);        //Usa la semilla de srad().
                 }while( aleatorio>cantV || aleatorio>(arista-dir[i].tamanio()) ); //Mientras no haya autos o lugar.
                 //Encola tantos vehículos como la cantidad dada por "aleatorio" 
                 for(int j=0;j<aleatorio;j++)
                 { 
                          //Encolar 1 vehiculo
                          vehiculo *v;
                          v = new vehiculo();
                          v->numID = num;
                          v->tipo = tipo;
                          v->prioridad= prioridad;
                          dir[i].encolar(v);
                        
                          //Asignar 1 camino
                          Camino *cam;
                          cam = new Camino();
                          cam->numID = num;
                          cam->tipo = tipo;
                          cam->ori = &dir[i];
                          aleatorioDes = rand()%NumCuadras;
                          cam->Destino= dir[aleatorioDes].vf();
                          camino[k]=*cam;     
                          k++; num++;                    
                 }
                 cantV=cantV-aleatorio;
         }
         cout<<"\n   Sobran "<<cantV;
         if(tipo=='a') { cout<<" autos. \n"; *cV[0]=k; } //Guardar las cantidades realmente asignadas.
         if(tipo=='h') { cout<<" policias. \n"; *cV[1]=k-*cV[0]; }
         if(tipo=='p') { cout<<" ambulancias. \n";  *cV[2]=k-*cV[0]-*cV[1]; }
     }
     cout<<"\n Caminos asignados: "<<k<<endl;  
     return;
}
