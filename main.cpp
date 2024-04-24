/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <stdlib.h>

using namespace std;


void ingreso(int c1, int f1);
void llenado(int fila,int columna, int M[f1][c1]);


int main()
{
    
    int c1,f1,c2,f2;
    
    ingreso(&f1,&c1);  // tamaño de la matriz
    ingreso(&f2,&c2);
    
    int Matriz1 [f1][c1], Matriz2 [][];
    
    return 0;
}


void ingreso(int f1, int c1){
    
    cout<<"Ingrese tamaño de la fila de la MATRIZ: "<<endl;
    cin>>f1;
    
    cout<<"Ingrese tamaño de la columna de la MATRIZ: "<<endl;
    cin>>c1;   
    
}

void llenado(int fila, int columna, int M[][]){
    for(int i = 0; i < fila; i++){
        for(int j = 0; j < columna; j++){
            cout << "Ingrese posicion [" << i << "][" << j << "]";
        }
    }
}



