/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>

using namespace std;


int ingreso(int c1, int f1, int c2, int f2);



int main()
{
    
    int c1,f1,c2,f2;
    
    cout<<"Ingrese tamaño de la fila de la MATRIZ A: "<<endl;
    cin>>f1;
    
    cout<<"Ingrese tamaño de la columna de la MATRIZ A: "<<endl;
    cin>>c1;    
    
    cout<<"Ingrese tamaño de la fila de la MATRIZ B: "<<endl;
    cin>>f2;    
    
    cout<<"Ingrese tamaño de la columna de la MATRIZ B: "<<endl;
    cin>>c2;    
    
    ingreso(f1,c1,f2,c2);

}


int ingreso(int c1, int f1, int c2, int f2){
    
    int A[f1][c1];
    int B[f2][c2];
    int R[f2][c1];
    cout << "Tamaño resultado = " << f2 << " y " << c1;
    
    
    llenado(A, f1, c1)
    llenado(B, f1, c1)
    
}

int llenado(int M, fila, columna){
    for(int i = 0, i < fila, i++){
        for(int j = 0, j < columna, j++){
            cout << "Ingrese posicion [" << i << "][" << j << "]";
        }
    }
}



