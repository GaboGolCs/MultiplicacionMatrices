#include <iostream>
#include <stdlib.h>

using namespace std;

void multiplication(long **matriz, int columnas, int filas, long **matrizResultado){
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            matrizResultado[i][j] = 0;
            for(int n = 0; n < columnas; n++){
                matrizResultado[i][j] += matriz[i][n]*matriz[n][j];
            }
        }
    }
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++)
            matriz[i][j] = matrizResultado[i][j];
    }
}

int main(){
    int filas, columnas;
    do{
        cout << "Ingrese n° de filas: ";
        cin >> filas;
        cout << "Ingrese n° de columnas: ";
        cin >> columnas;
        if(filas != columnas)
            cout << "Dimensiones no congruentes para multiplicacion.\n";
    }while(filas < 0 || columnas < 0 || filas != columnas);

    // Asigna el espacio para las filas de la matriz
    long **matriz = (long**)malloc(filas * sizeof(long*));
    // Asigna el espacio para las columnas de la matriz
    for(int i = 0; i < columnas; i++){
        matriz[i] = (long*)malloc(columnas * sizeof(long));
    }

    // Asigna el espacio para las filas de la matriz resultado
    long **matrizResultado = (long**)malloc(filas * sizeof(long*));
    // Asigna el espacio para las columnas de la matriz resultado
    for(int i = 0; i < columnas; i++){
        matrizResultado[i] = (long*)malloc(columnas * sizeof(long));
    }

    // Asigna valores al inicio de la matriz
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            cout << "Ingrese valor posicion [" << i << "][" << j << "]: ";
            cin >> matriz[i][j];
            matrizResultado[i][j] = 0;
        }
        cout << "\n";
    }
    int x;
    do{
        do{
        cout << "Para iterar, ingrese 1.\n";
        cout << "Para terminar, ingrese 0.\n";
        cin >> x;
        cout << "\n";
        } while(x != 0 && x != 1);
        multiplication(matriz, columnas, filas, matrizResultado);
        // Muestra los valores del resultado
        for(int i = 0; i < filas; i++){
            for(int j = 0; j < columnas; j++){
                cout << matrizResultado[i][j] << "\t";
        }
        cout << "\n";
    }
    } while(x == 1);
    cout << "\n\n";

    for(int i = 0; i < columnas; i++){
        free(matrizResultado[i]);
    }
    for(int i = 0; i < columnas; i++){
        free(matriz[i]);
    }
    free(matriz);
    free(matrizResultado);

    return 0;
}
