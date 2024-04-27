/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <stdlib.h>

using namespace std;



int Inicializador(int **&, int&, int&);
int Llenado(int **&, int, int);


int main()
{
    int **puntero_Matriz,fila,columna;  // creamos el puntero doble que apunta a el inicio de la MATRIZ ademas de el numero de filas y columnas
    
    
    Inicializador(puntero_Matriz, fila, columna);
    Llenado(puntero_Matriz,fila,columna);
    
    return 0;
}


int Inicializador(int **&puntero_Matriz, int &fila, int &columna){              //Le enviamos todo por referencia para poder ser modificados en ejecucion y haer la funcion modular
                                                                                            
    

    cout<<"Ingrese tamaño de la fila de la MATRIZ: "<<endl;         //pedimos fila
    cin>>fila;
    
    cout<<"Ingrese tamaño de la columna de la MATRIZ: "<<endl;      //Pedimos columna
    cin>>columna;   
    
    
    puntero_Matriz = new int* [fila];               //Asignamos memoria a las filas 
    
    for (int i =0; i<fila; i++){
        
        puntero_Matriz[i] = new int [columna];      //Asignamos memoria a las columnas 
        
    }
    
    

    return 0;
    
}

// debemos entender que el doble puntero sinifica que es un puntero apuntando a otro puntero, en este caso se usa para apuntar a el array de punteros que representan las filas  
// cada  celda en el array fila contiene el puntero a un array donde se contiene todos los valores de las comlumna


/*
Le pedi al chat gpt que hiciera una representacion grafica de el asunto


+-----------------+      +------------+------------+ ... +------------+
|   Puntero a     | ---> |    Fila    |    Fila    |     |    Fila    |
|   la primera    |      +------------+------------+ ... +------------+
|    fila (ptr)   |      | Elemento 0 | Elemento 1 |     | Elemento n |
+-----------------+      +------------+------------+ ... +------------+
                           | Elemento 0 | Elemento 1 |     | Elemento n |
                           +------------+------------+ ... +------------+
                           |     ...    |     ...    |     |     ...    |
                           +------------+------------+ ... +------------+



*/

int Llenado(int **&puntero_Matriz, int f, int c){   //solo pasamos por referencia la MATRIZ ya que es lo unico que necesitamos cambiar en este caso
    
    for(int i = 0; i < f; i++){
        
        for(int j = 0; j < c; j++){
            
            cout << "Ingrese posición [" << i+1 << "][" << j+1 << "]: ";
            cin >> *(*(puntero_Matriz+i)+j);        // Equivalente a MATRIZ[i][j]
            
        }
    }
    return 0;
}


