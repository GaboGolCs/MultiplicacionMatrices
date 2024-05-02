#include <iostream>
#include <stdlib.h>
#include <limits>

using namespace std;

typedef long **Matriz;
typedef long *Arreglo;

void tipoEntradaInvalido(); // Muestra un error si el valor ingresado es incorrecto.
Matriz newMatriz(int filas, int columnas); // Devuelve una matriz con dimension "filas x columnas".
void llenarMatriz(Matriz matriz, int filas, int columnas); // Llena una matriz con valores enviados por el usuario.
void eliminaMatriz(Matriz matriz, int columnas); // Libera la memoria de una matriz dada.
void mostrarMatriz(Matriz matriz, int filas, int columnas); // Imprime una matriz.
void multiplication(Matriz matriz, int filas, int columnas, Matriz matrizResultado); // Multiplica una matriz y coloca el resultado en otra.

int main(){
    int filas, columnas;
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
        if(filas != columnas){
            cout << "Dimensiones no congruentes para multiplicacion.\n";
        }
    }while(filas < 0 || columnas < 0 || filas != columnas);

    // Crea la matriz a multiplicar y la matriz resultado
    Matriz matrizA = newMatriz(filas, columnas);
    Matriz matrizResultado = newMatriz(filas, columnas);

    // Asigna valores al inicio de la matriz
    llenarMatriz(matrizA, filas, columnas);
    
    int x;
    do{
        do{
            cout << "\nPara iterar, ingrese 1.\nPara terminar, ingrese 0.\n";
            while (!(cin >> x)) {
                tipoEntradaInvalido();
            }
            cout << "\n";
        } while(x != 0 && x != 1);
        
        multiplication(matrizA, filas, columnas, matrizResultado);
        mostrarMatriz(matrizA, filas, columnas);
        cout << "\n";
        
    } while(x == 1);
    cout << "\n\n";

    // Libera la memoria asignada a la matriz.
    eliminaMatriz(matrizA, columnas);
    eliminaMatriz(matrizResultado, columnas);

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
    // Asigna el espacio para las columnas de la matriz
    Matriz matriz = (Matriz)malloc(columnas * sizeof(Arreglo));
    // Asigna el espacio para las filas de la matriz
    for(int i = 0; i < filas; i++){
        matriz[i] = (Arreglo)malloc(filas * sizeof(long));
    }
    
    return matriz;
}

void llenarMatriz(Matriz matriz, int filas, int columnas){
    int valor;
    for(int i = 0; i < filas; i++){
        cout << "\n";
        for(int j = 0; j < columnas; j++){
            cout << "Ingrese valor posicion [" << i << "][" << j << "]: ";
            while (!(cin >> valor)) {
                tipoEntradaInvalido();
            }
            matriz[i][j] = valor;
        }
    }
}

void eliminaMatriz(Matriz matriz, int columnas){
    for(int i = 0; i < columnas; i++){
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
