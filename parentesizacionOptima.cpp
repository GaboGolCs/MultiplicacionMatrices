#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

typedef long **Matriz;
typedef long *Arreglo;

void tipoEntradaInvalido(); // Muestra un error si el valor ingresado es incorrecto.
int min(int p, int q); // Determina el valor minimo entre p y q.
Matriz newMatriz(int filas, int columnas); // Devuelve una matriz con dimension "filas x columnas".
Matriz newMatriz(int dimension); // Devuelve una matriz con dimension "dimension x dimension".
  void llenarMatriz(Matriz matriz, int filas, int columnas); // Llena una matriz con valores enviados por el usuario.
void llenarMatriz(Matriz matriz, int filas, int columnas, int valor); // Llena una matriz con un valor especifico.
  void eliminaMatriz(Matriz matriz, int columnas); // Libera la memoria de una matriz dada.
void mostrarMatriz(Matriz matriz, int filas, int columnas); // Imprime una matriz.
void mostrarMatriz(Matriz matriz, int dimension); // Imprime una matriz.
void costoMin(vector<int> p, Matriz costo, Matriz k, int cantMatrices); // Rellena con el costo minimo y los valores "k".
void mostrarParentesis(Matriz k, int cantMatrices); // Muestra la manera optima de colocar parentesis a la cadena de matrices.
void generaParentesis(Matriz k, int cantMatrices, int i, int j, vector<string> *cadena); // Agrega parentesis usando concatenacion de strings.

int main()
{
    // Estos dos valores son del ejemplo del ppt, habria que hacer una funcion para ingresar estos datos.
    // ¿Una funcion para ingresar la cantidad de matrices, luego los tamaños y por ultimo su contenido?
    vector<int> p{30, 35, 15, 5, 10, 20, 25}; // Arreglo con los tamaños de las matrices A, Ai = p1*p2, Ai+1 = p2*p3... etc
    int cantMatrices = 6; // Cantidad de matrices A1*A2*A3*A4*A5*A6*... etc
    
    
    Matriz costo = newMatriz(cantMatrices); // Matriz de costo minimo para multiplicar desde Ai hasta Aj
    Matriz k = newMatriz(cantMatrices); // Matriz con la posicion del indice "k", en este indice se alcanza el
    // costo minimo de multiplicar Ai*Aj al separarse en Ai*Ak + Ak+1*Aj.

    // Inicia las matrices con 0.
    llenarMatriz(costo, cantMatrices, cantMatrices, 0);
    llenarMatriz(k, cantMatrices, cantMatrices, 0);
    
    // Rellena la matriz de costo y k
    costoMin(p, costo, k, cantMatrices);
    
    // Muestra las matrices
    cout << "\nCostos de la matriz:\n";
    mostrarMatriz(costo, cantMatrices);
    cout << "\nCortes optimos:\n";
    mostrarMatriz(k, cantMatrices);
    cout << "\nParentesis:\n";
    
    // Muestra la forma de asociar la cadena dada para optimizar su calculo
    mostrarParentesis(k, cantMatrices);

    return 0;
}

void tipoEntradaInvalido(){
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "\nEl valor ingresado es incorrecto, por favor ingreselo denuevo.\n";
}

int min(int p, int q){
    return p < q ? p : q;
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

Matriz newMatriz(int dimension){
    return newMatriz(dimension, dimension);
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

void llenarMatriz(Matriz matriz, int filas, int columnas, int valor){
    for(int i = 0; i < filas; i++){
        cout << "\n";
        for(int j = 0; j < columnas; j++){
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

void mostrarMatriz(Matriz matriz, int dimension){
    mostrarMatriz(matriz, dimension, dimension);
}

void costoMin(vector<int> p, Matriz costo, Matriz k, int cantMatrices){
    for (int u = 1; u < cantMatrices; u++){ // "u" es la diferencia entre Ai y Aj.
        for (int v = 0; v < cantMatrices-u; v++){ // "v" va desde A0 hasta A(total - diferencia)
            int i = v;
            int j = v+u;
            int kMin = i; // "k" minimo default en i
            int costoMin = costo[kMin+1][j] + p[i]*p[kMin+1]*p[j+1]; // Costo minimo default para "k" = i
            for (int k = i+1; k < j; k++){ // El ciclo comienza desde i+1 porque ya se tiene el costo default de i.
                int costoTest = costo[i][k] + costo[k+1][j] + p[i]*p[k+1]*p[j+1];
                costoMin = min(costoMin, costoTest);
                if (costoTest == costoMin){
                    kMin = k;
                }
            }
            costo[i][j] = costoMin;
            k[i][j] = kMin+1; // Como esta indexado en 0 se suma 1
        }
    }
}

void mostrarParentesis(Matriz k, int cantMatrices){
    vector<string> cadena(cantMatrices, "A");
    generaParentesis(k, cantMatrices, 0, cantMatrices-1, &cadena);
    for(int i = 0; i < cadena.size(); i++){
        cout << cadena[i];
    }
}

void generaParentesis(Matriz k, int cantMatrices, int i, int j, vector<string> *cadena){
    int tempk = k[i][j]-1;
    if(tempk != i){
        generaParentesis(k, cantMatrices, i, tempk, cadena);
    }
    if((tempk+1) != j){
        generaParentesis(k, cantMatrices, tempk+1, j, cadena);
    }
    cadena->at(i) = "(" + cadena->at(i);
    cadena->at(j) = cadena->at(j) + ")";
    if(j-i == 1){
        cadena->at(i) = cadena->at(i) + "*";
    }
}
