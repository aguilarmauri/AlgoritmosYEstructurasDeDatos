/*
A partir de un texto de más de 100 caracteres, deberá consideralo como un puntero a Char y aplicar aritmetica
de punteros. Deberá contar cuantas veces se repite cada letra, cuantas son vocales, cuantas consonantes y cuantos
blancos, en una única pasada, mediante una funcion recursiva final. 
Deberá escribir como comentario del codigo, cuales son los tipos y las funciones que intervienen en la definicion
recursiva.
Deberá transformarla según dichos parametros en una función iterativa que calcule lo mismo. Ambas deben retornar
un arreglo con los valores encontrados para cada letra, las vocales, las consonantes y los blancos.
Es decir, que deberá programar dos funciones que devuelvan el mismo resultado, una recursiva final y otra iterativa. 
Disponible en:	Tuesday, 3 de April de 2012, 21:15
Fecha de entrega:	Sunday, 15 de April de 2012, 23:55


Integrantes del Grupo:
Aguilar Mauricio - DNI: 34496071
Tarazi Pedro Esequiel - DNI: 35035736

Fecha de Entrega: 15/04/2012
*/


#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

// PROTOTIPOS DE FUNCIONES.
int Iterativa(char [], int, int []);
int Recursiva(char [], int, int, int [], int, int, int, int []);

int main()
{
    int i;
    int resultados[3]={0};
    int resultadosR[3]={0};
    int RepLetra[27]={0};
    string nombre_archivo="cadena.txt";
    ifstream archivo_entrada;
    long lon=0;
    int J;
    
    //LECTURA DE ARCHIVO ------------------------------------------------------
    
    //Abrir el archivo
    archivo_entrada.open(nombre_archivo.c_str());
    
    //Comprobar el éxito de la apertura
    if (archivo_entrada.fail())
    {
     cout<<"\nEl archivo no se abrio con exito."
         <<"\nPor favor compruebe que el archivo existe en realidad."
         <<"\nPresione una tecla para salir"<<endl<<endl<<endl;
         system("PAUSE");
         exit(1);
     }
     
     //Calcular la longitud de la cadena
     archivo_entrada.seekg(0L, ios::end);
     lon = archivo_entrada.tellg();
     archivo_entrada.seekg(0L, ios::beg);
     
     //Crear un arreglo llamado cadena, con esa longitud
     char Cadena[lon]; int I=0;
     
     //Leer archivo letra por letra y guardar en un array
     archivo_entrada>>noskipws>>Cadena[0];
     while(archivo_entrada.good())
     {
      I++;
      archivo_entrada>>noskipws>>Cadena[I];
     } 

     //Mostrar cadena guardada en el arreglo
     cout<<"El texto es: ";
     for(J=0; J<I; J++)
     {
      cout<<Cadena[J];
     }
     cout<<endl<<endl;

    //Cerrar archivo     
    archivo_entrada.close();
    
    //FIN DE LECTURA DE ARCHIVO ---------------------------------------------
    
     
    cout<<"MODO RECURSIVO"<<endl;
    Recursiva(Cadena,sizeof(Cadena), -1, resultadosR, 0,0,0,RepLetra);              // LLAMADA A LA FUNCION RECURSIVA.
    cout<<"\nResultado: [ "<<resultadosR[0]<<","<<resultadosR[1]<<","<<resultadosR[2]<<" ]"<<endl;
    cout<<"La cantidad de letras vocales son: "<<resultadosR[0]<<endl;
    cout<<"La cantidad de espacios son: "<<resultadosR[1]<<endl;
    cout<<"La cantidad de consonantes son: "<<resultadosR[2]<<endl; 
    cout<<endl<<"***********************************"<<endl<<endl;    

    cout<<"MODO ITERATIVO"<<endl;  
    Iterativa(Cadena,sizeof(Cadena),resultados);                                    // LLAMADA A LA FUNCION ITERATIVA.
    cout<<endl<<"***********************************"<<endl<<endl;


   
    cout<<endl<<endl<<endl;
    system("PAUSE");
    return 0;
}

// DEFINICION DE LA FUNCION RECURSIVA.
int Recursiva(char *Cadena, int N,int J, int *resultadosR,int X,int Y,int Z,int RepLetra[])
{
    int C;
    char Letra[27]="abcdefghijklmnopqrstuvwxyz";
    J++;
    C = tolower(Cadena[J]); 
    
    if (C==97 || C==101 || C==105 || C==111 || C==117 )
    {
       resultadosR[0]=(1 + X);
       X++;
       switch(C)
       {
            case 'a': RepLetra[0]++; break;
            case 'e': RepLetra[4]++; break;
            case 'i': RepLetra[8]++; break;
            case 'o': RepLetra[14]++; break;
            case 'u': RepLetra[20]++; break;
       }

       Recursiva(Cadena,N,J,resultadosR,X,Y,Z,RepLetra);
    }
    
    else if (C==32)
    {
         resultadosR[1]=(1 + Y);
         Y++;
         Recursiva(Cadena,N,J,resultadosR,X,Y,Z,RepLetra);
    }
    else if (C>=97 && C<=122)
    {
         resultadosR[2]=(1 + Z);
         Z++;
         switch(C)
         {   
            case 'b': RepLetra[1]++;  break;
            case 'c': RepLetra[2]++;  break;
            case 'd': RepLetra[3]++;  break;
            case 'f': RepLetra[5]++;  break;
            case 'g': RepLetra[6]++;  break;
            case 'h': RepLetra[7]++;  break;
            case 'j': RepLetra[9]++;  break;
            case 'k': RepLetra[10]++;  break;
            case 'l': RepLetra[11]++;  break;
            case 'm': RepLetra[12]++;  break;
            case 'n': RepLetra[13]++;  break;
            case 'p': RepLetra[15]++;  break;
            case 'q': RepLetra[16]++;  break;
            case 'r': RepLetra[17]++;  break;
            case 's': RepLetra[18]++;  break;
            case 't': RepLetra[19]++;  break;
            case 'v': RepLetra[21]++;  break;
            case 'w': RepLetra[22]++;  break;
            case 'x': RepLetra[23]++;  break;
            case 'y': RepLetra[24]++; break;
            case 'z': RepLetra[25]++; break;
         }
         Recursiva(Cadena,N,J,resultadosR,X,Y,Z,RepLetra);
    }
    else if(C==0)
    {
         cout << "Letra" << "    Cantidad de Veces que repite" << endl;
         for(int I=0;I<26;I++)
         {
                 cout<<"  "<<Letra[I];
                 cout<<setw(10)<<RepLetra[I]<<" veces"<<endl;
         }
         return 0; 
    } 
    else
    {
        Recursiva(Cadena,N,J,resultadosR,X,Y,Z,RepLetra);
    } 
}
  
// DEFINICION DE LA FUNCION ITERATIVA.         
int Iterativa(char Cadena[],int N,int *resultados)
{
   int I,C,cuentaVocales = 0,cuentaEspacios = 0,cuentaConsonantes = 0;
   char Letra[27]="abcdefghijklmnopqrstuvwxyz";
   int RepLetra[27]={0};                                      
   
   for (I=0;I<N/*(N-1)*/;I++)
   {
       C = tolower(Cadena[I]);
       switch(C)
       {
            case 'a': RepLetra[0]++; cuentaVocales++; break;
            case 'e': RepLetra[4]++; cuentaVocales++; break;
            case 'i': RepLetra[8]++; cuentaVocales++; break;
            case 'o': RepLetra[14]++; cuentaVocales++; break;
            case 'u': RepLetra[20]++; cuentaVocales++; break;
                           
            case ' ':cuentaEspacios++;break;
                          
            case 'b': RepLetra[1]++; cuentaConsonantes++; break;
            case 'c': RepLetra[2]++; cuentaConsonantes++; break;
            case 'd': RepLetra[3]++; cuentaConsonantes++; break;
            case 'f': RepLetra[5]++; cuentaConsonantes++; break;
            case 'g': RepLetra[6]++; cuentaConsonantes++; break;
            case 'h': RepLetra[7]++; cuentaConsonantes++; break;
            case 'j': RepLetra[9]++; cuentaConsonantes++; break;
            case 'k': RepLetra[10]++; cuentaConsonantes++; break;
            case 'l': RepLetra[11]++; cuentaConsonantes++; break;
            case 'm': RepLetra[12]++; cuentaConsonantes++; break;
            case 'n': RepLetra[13]++; cuentaConsonantes++; break;
            case 'p': RepLetra[15]++; cuentaConsonantes++; break;
            case 'q': RepLetra[16]++; cuentaConsonantes++; break;
            case 'r': RepLetra[17]++; cuentaConsonantes++; break;
            case 's': RepLetra[18]++; cuentaConsonantes++; break;
            case 't': RepLetra[19]++; cuentaConsonantes++; break;
            case 'v': RepLetra[21]++; cuentaConsonantes++; break;
            case 'w': RepLetra[22]++; cuentaConsonantes++; break;
            case 'x': RepLetra[23]++; cuentaConsonantes++; break;
            case 'y': RepLetra[24]++; cuentaConsonantes++; break;
            case 'z': RepLetra[25]++; cuentaConsonantes++; break;
       }
   }
   
   resultados[0]=cuentaVocales;
   resultados[1]=cuentaEspacios;
   resultados[2]=cuentaConsonantes;
   
   cout<<"Letra       Cantidad de Veces que repite"<<endl;
   
   for(I=0;I<26;I++)
   {
        cout<<"  "<<Letra[I];
        cout<<setw(10)<<RepLetra[I]<<" veces"<<endl;
   }
   cout<<"\nResultado: [ "<<resultados[0]<<","<<resultados[1]<<","<<resultados[2]<<" ]"<<endl;
   cout<<"La cantidad de letras vocales son: "<<resultados[0]<<endl;
   cout<<"La cantidad de espacios son: "<<resultados[1]<<endl;
   cout<<"La cantidad de consonantes son: "<<resultados[2]<<endl;  
   cout<<endl;
   
   return 0;
}


//COMENTARIOS:

/*
Para realizar la funcion recursiva, le enviamos un apuntador a la cadena ingresada,
un entero N que contiene la cantidad de caracteres de la cadena, un entero J que usamos
para recorrer la cadena, un apuntador a un arreglo para guardar los resultados, tres enteros
X,Y y Z que llevan la cuenta de cuantas vocales, espacios en blanco y consonantes tiene 
la cadena y un arreglo RepLetra que contiene la cantidad de repeticiones que tiene cada
letra del abecedario.
*/
