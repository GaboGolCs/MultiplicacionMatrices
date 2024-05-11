#include <iostream>
#include <stdlib.h>
#include <limits>
#include <time.h>

using namespace std;

typedef long **Matriz;
typedef long *Arreglo;

void tipoEntradaInvalido(); // Muestra un error si el valor ingresado es incorrecto.
Matriz newMatriz(int filas, int columnas); // Devuelve una matriz con dimension "filas x columnas".
void llenarMatriz(Matriz matriz, int filas, int columnas); // Llena una matriz con valores enviados por el usuario.
void eliminaMatriz(Matriz matriz, int filas); // Libera la memoria de una matriz dada.
void mostrarMatriz(Matriz matriz, int filas, int columnas); // Imprime una matriz.
void multiplication(Matriz matriz, int filas, int columnas, Matriz matrizResultado); // Multiplica una matriz y coloca el resultado en otra.
void multiplicationRectangular(Matriz matriz, int filas, int columnas, Matriz matriz2, Matriz matrizResultado); // Multiplica una matriz y coloca el resultado en otra.

int main(){
    int filas, columnas;
    int filas2, columnas2;
    // Ingreso de datos de la matriz, las filas y columnas deben ser iguales ya que si se multiplica la cantidad de filas
    // debe ser la misma que la cantidad de columnas de la matriz por la que se multiplica
    do{
        cout << "Ingrese n° de filas: ";
        while (!(cin >> filas)) {
                tipoEntradaInvalido();
            }
        cout << "Ingrese n° de columnas: ";
        while (!(cin >> columnas)) {
                tipoEntradaInvalido();
            }
            
        if(filas != columnas){ // se asigna las dimensiones para la matriz rectangular
            filas2 = columnas;
            cout << "Ingrese n° de columnas para la segunda matriz: ";
            while (!(cin >> columnas2)) { 
                tipoEntradaInvalido();
            }
        }
    }while(filas < 0 || columnas < 0 || columnas2 < 0);

    // Crea la matriz a multiplicar y la matriz resultado
    Matriz matrizA;
    Matriz matrizB;
    
    int x;
    
    if(filas == columnas){
        // Crea la matriz a multiplicar y la matriz resultado
        matrizA = newMatriz(filas, columnas);
        matrizB = newMatriz(filas, columnas);

        // Asigna valores al inicio de la matriz
        llenarMatriz(matrizA, filas, columnas);
    
        
        do{
            do{
                cout << "\nPara iterar, ingrese 1.\nPara terminar, ingrese 0.\n";
                while (!(cin >> x)) {
                    tipoEntradaInvalido();
                }
                cout << "\n";
            } while(x != 0 && x != 1);
        
            multiplication(matrizA, filas, columnas, matrizB);
            mostrarMatriz(matrizA, filas, columnas);
            cout << "\n";
        
        } while(x == 1);
    cout << "\n\n";

        // Libera la memoria asignada a la matriz.
        eliminaMatriz(matrizA, filas);
        eliminaMatriz(matrizB, filas);
    }
    
    // Caso de ser matrices rectangulares
    else{
        matrizA = newMatriz(filas, columnas);
        matrizB = newMatriz(filas2, columnas2);
        
        // resultado de la multiplicacion de matrices
        Matriz matrizResultado;

        // Asigna valores al inicio de la matriz
        cout << "ingrese los valores para la primera matriz" << endl;
        llenarMatriz(matrizA, filas, columnas);
        
        cout << "ingrese los valores para la segunda matriz" << endl;
        llenarMatriz(matrizB,filas2, columnas2);
    
        do{
            do{
                cout << "\nPara iterar, ingrese 1.\nPara terminar, ingrese 0.\n";
                while (!(cin >> x)) {
                    tipoEntradaInvalido();
                }
                cout << "\n";
            } while(x != 0 && x != 1);
        
            matrizResultado = newMatriz(filas, columnas2);

            multiplicationRectangular(matrizA, filas , columnas2, matrizB, matrizResultado);
               
            // se elimina la matriz para ser reutilizada
            eliminaMatriz(matrizA, filas);
            eliminaMatriz(matrizB,filas2); 
            
            // Nuevas dimenciones para poder realizar la multiplicacion
            columnas = columnas2;
            filas2 = columnas2;
            
            mostrarMatriz(matrizResultado, filas, columnas);
                
            // A La matrizA se le asigna todos los valores asociados a matrizResultado
            matrizA = newMatriz(filas,columnas);
                
            // Reemplaza los valores de la matriz por la del resultado
            for(int i = 0; i < filas; i++){
                for(int j = 0; j < columnas; j++)
                    matrizA[i][j] = matrizResultado[i][j];
            }
                
            eliminaMatriz(matrizResultado,filas);
                
            
            cout << "\nIngrese nueva dimencion de columnas para la nueva matriz.\n ";
            while (!(cin >> columnas2)) {
                    tipoEntradaInvalido();
                }
            
            matrizB = newMatriz(filas2, columnas2); // nuevo tamaño de la matriz  
            llenarMatriz(matrizB,filas2, columnas2);
              
            cout << "\nValores asignados a la nueva matriz.\n ";
            mostrarMatriz(matrizB, filas2, columnas2);
  
            cout << "\n";
        
        } while(x == 1);
    cout << "\n\n";

        // Libera la memoria asignada a la matriz.
        eliminaMatriz(matrizA, filas);
        eliminaMatriz(matrizB, filas2);
    }
  

    return 0;
}

void tipoEntradaInvalido(){
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "\nEl valor ingresado es incorrecto, por favor ingreselo denuevo.\n";
}

Matriz newMatriz(int filas, int columnas){
    try {
        if (filas <= 0 || columnas <= 0){
            throw 0;
        }
    }
    catch (...){
        cout << "\nLa matriz debe tener dimensiones mayores a 0.\n";
        // devuelve las dimensiones menores a 1 como 1
        filas = filas <= 0 ? 1 : filas;
        columnas = columnas <= 0 ? 1 : columnas;
    }
    
    // Primero asigna columnas y luego filas para mayor claridad al escribir Matriz[filas][columnas]
    // Asigna el espacio para las filas de la matriz
    Matriz matriz = (Matriz)malloc(filas * sizeof(Arreglo));
    // Asigna el espacio para las columnas de la matriz
    for(int i = 0; i < filas; i++){
        matriz[i] = (Arreglo)malloc(columnas * sizeof(long));
    }
    
    return matriz;
}

void llenarMatriz(Matriz matriz, int filas, int columnas){
    int valor;
    for(int i = 0; i < filas; i++){
        cout << "\n";
        for(int j = 0; j < columnas; j++){
            cout << "Ingrese valor posicion [" << i + 1 << "][" << j + 1 << "]: ";
            while (!(cin >> valor)) {
                tipoEntradaInvalido();
            }
            matriz[i][j] = valor;
        }
    }
}

void eliminaMatriz(Matriz matriz, int filas){
    for(int i = 0; i < filas; i++){
        free(matriz[i]);
    }
    free(matriz);
}

void mostrarMatriz(Matriz matriz, int filas, int columnas){
    for (int i = 0; i < filas; i++){
        for (int j = 0; j < columnas; j++){
            cout << matriz[i][j] << "\t";
        }
        cout << "\n";
    }
}

void multiplication(Matriz matriz, int filas, int columnas, Matriz matrizResultado){
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            // Vacia la posicion de la matriz resultado para asignarle el valor de la multiplicacion
            matrizResultado[i][j] = 0;
            // Este hace el calculo, se multiplica cada fila por la columna y se va sumando por la cantidad que haya de columnas, podría haber
            // sido fila pero realmente no importa ya que deben ser iguales.
            for(int n = 0; n < columnas; n++){
                matrizResultado[i][j] += matriz[i][n]*matriz[n][j];
            }
        }
    }
    // Reemplaza los valores de la matriz por la del resultado
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++)
            matriz[i][j] = matrizResultado[i][j];
    }
}

void multiplicationRectangular(Matriz matriz, int filas, int columnas, Matriz matriz2, Matriz matrizResultado){
    
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            matrizResultado[i][j] = 0;
            // Este hace el calculo, se multiplica cada fila por la columna y se va sumando por la cantidad que haya de columnas, podría haber
            // sido fila pero realmente no importa ya que deben ser iguales.
            for(int n = 0; n < columnas; n++){
                matrizResultado[i][j] += matriz[i][n]*matriz2[n][j];
            }
        }
    }
    
}