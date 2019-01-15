void MostrarCalles(Cola [], char, int, int);

void MostrarCalles(Cola dir[], char ts, int ns, int numCuadras)
{
    Color(Titulo);
    cout<<"\n Mostrando Calles de la Ciudad Habitadas: "<<endl;
    Color(Base);
    for(int i=0; i<numCuadras; i++)
            if(dir[i].tamanio() != 0){
                 cout<<" Calle";
                 Color(12);
                 if(dir[i].vi()<=9) cout<<" 0";
                 else cout<<" ";
                 cout<<dir[i].vi();
                 Color(Base);
                 cout<<"->";
                 Color(12);
                 if(dir[i].vf()<=9) cout<<"0";
                 cout<<dir[i].vf();
                 Color(Base);
                 cout<<": ";
                 dir[i].Imprimir(ts, ns);     
                 cout<<endl;
            }
    return;
}
