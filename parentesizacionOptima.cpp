#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cstdlib>
#include <time.h>

using namespace std;

typedef long **Matriz;
typedef long *Arreglo;

const string salto = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

// Utilidades
void limpiarCin(); // Limpia el buffer si hay un error en la entrada de datos.
void error(string error); // Muestra un error si el valor ingresado es incorrecto.
int min(int p, int q); // Determina el valor minimo entre p y q.
void pausa(); // Pausa hasta tocar ENTER.
vector<int> split(string str, char delimitador); // Separa un string en varios enteros y los coloca en un vector.
string soloDigitos(string str, char delimitador); // Deja solo digitos y delimitadores en un string.

// Matrices
Matriz newMatriz(int filas, int columnas); // Devuelve una matriz con dimension "filas x columnas".
Matriz newMatriz(int dimension); // Devuelve una matriz con dimension "dimension x dimension".
void llenarMatriz(Matriz matriz, int filas, int columnas); // Llena una matriz con valores enviados por el usuario.
void llenarMatriz(Matriz matriz, int filas, int columnas, int valor); // Llena una matriz con un valor especifico.
void llenarMatriz(Matriz matriz, int filas, int columnas, int (*func)(int)); // Llena una matriz segun una funcion.
void eliminaMatriz(Matriz matriz, int filas); // Libera la memoria de una matriz dada.
void mostrarMatriz(Matriz matriz, int filas, int columnas); // Imprime una matriz.
void mostrarMatriz(Matriz matriz, int dimension); // Imprime una matriz.

// Algoritmo de costos minimos
void costoMin(vector<int> p, Matriz costo, Matriz k, int cantMatrices); // Rellena con el costo minimo y los valores "k".
void mostrarParentesis(Matriz k, int cantMatrices); // Muestra la manera optima de colocar parentesis a la cadena de matrices.
void generaParentesis(Matriz k, int i, int j, vector<string> *cadena); // Agrega parentesis usando concatenacion de strings.

int main()
{
    int opcion;
    bool salir = false;
    bool ejecutarAlgoritmo = true;
    srand(time(0));
    
    do{
        vector<int> p;
        vector<Matriz> cadenaMatrices;
        string tamañoMatrices;
        int cantMatrices;
        ejecutarAlgoritmo = true;
        
        cout << "\nEliga una opcion para visualizar el algoritmo de costos minimos para la multiplicacion de una secuencia de matrices:";
        cout << "\n--------------------------------------------------------------------------------------------------------------------";
        cout << "\n1: Invoca el algoritmo con los parametros de ejemplo indicados en el informe.";
        cout << "\n2: Invoca al algoritmo utilizando parametros aleatorios.";
        cout << "\n3: Invoca al algoritmo y le pide al usuario ingresar los parametros.";
        cout << "\n4: Salir del programa.";
        cout << "\n";
        while(!(cin >> opcion)){
            limpiarCin();
            error("Opcion invalida, debe ser un numero entre 1 y 4.");
        }
        limpiarCin();
        cout << salto << "Se ha ingresado a la opcion N°" << opcion;
        
        switch(opcion){
            case 1:
                cout << "\nInvoca el algoritmo con los parametros de ejemplo indicados en el informe:\n";
                p.insert(p.end(), {10, 15, 5, 2, 4});
                cantMatrices = p.size()-1;
                break;
            case 2:
                cout << "\nInvoca al algoritmo utilizando parametros aleatorios:\n";
                cantMatrices = (rand()%4)+3; // Entre 3 y 6 matrices.
                for(int i = 0; i <= cantMatrices; i++){
                    p.push_back((rand()%31)+5); // Entre 5 y 35.
                }
                break;
            case 3:
                cout << "\nInvoca al algoritmo y le pide al usuario ingresar los parametros:\n";
                cout << "\nIngrese tamaño de las matrices separandolas con una coma \",\" (Entre 1-256)\tEjemplo: 10, 15, 5, 2, 4\n";
                do{
                    salir = true;
                    getline(cin, tamañoMatrices);
                    p = split(tamañoMatrices, ',');
                    if(p.size() < 2){
                        error("Debe haber almenos un tamaño para la fila y otro para la columna.");
                        salir = false;
                    }
                    for(int i = 0; i < p.size(); i++){
                        if((p[i] <= 0 || p[i] >= 257) && salir == true){
                            error("Los tamaños deben ser mayores que 0 y menores que 257");
                            salir = false;
                        }
                    }
                }while(!salir);
                cantMatrices = p.size()-1;
                salir = false;
                break;
            case 4:
                cout << "\nSaliendo del programa. . .\n";
                salir = true;
                break;
            default:
                error("Opcion invalida, debe ser un numero entre 1 y 4.");
                ejecutarAlgoritmo = false;
        }
        
        if(salir == true){
            break;
        }
        
        if(ejecutarAlgoritmo == true){
            cout << "\nTamaño de las matrices:\n";
            for(int i = 0; i < cantMatrices; i++){
                cout << "Matriz N° " << i+1 << ": " << p[i] << "x" << p[i+1] << "\n";
            }
            
            Matriz costo = newMatriz(cantMatrices); // Matriz de costo minimo para multiplicar desde Ai hasta Aj
            Matriz k = newMatriz(cantMatrices); // Matriz con la posicion del indice "k", en este indice se alcanza el
            // costo minimo de multiplicar Ai*Aj al separarse en Ai*Ak + Ak+1*Aj.
            
            // Inicia las matrices con 0.
            llenarMatriz(costo, cantMatrices, cantMatrices, 0);
            llenarMatriz(k, cantMatrices, cantMatrices, 0);
            
            // Ejecuta el algoritmo de costo minimo
            costoMin(p, costo, k, cantMatrices);
            
            // Muestra las matrices de costo y k
            cout << "\nCostos de la matriz:\n";
            mostrarMatriz(costo, cantMatrices);
            cout << "\nCortes optimos:\n";
            mostrarMatriz(k, cantMatrices);
            
            // Muestra la forma de asociar la cadena dada para optimizar su calculo
            cout << "\nParentesis:\n";
            mostrarParentesis(k, cantMatrices);
            
            eliminaMatriz(costo, cantMatrices);
            eliminaMatriz(k, cantMatrices);
            
            pausa();
        }
    }while(true);
    return 0;
}

void limpiarCin(){
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void error(string error){
    cout << "\nERROR: " << error << "\n";
}

int min(int p, int q){
    return p < q ? p : q;
}

void pausa(){
    cout << "\n\nPresiona ENTER para continuar. . .";
    limpiarCin();
    cout << salto;
}

vector<int> split(string str, char delimitador)
{
    vector<int> vec;
    int inicio = 0;
    int indice;
    int tamaño;
    string aux;
    
    // Elimina todos los caracteres que no sean digitos o comas.
    str = soloDigitos(str, ',');

    // Guarda los substring dentro del vector.
    if (!str.empty()){
        do{
            // Encuentra el indice en el que comienza el delimitador.
            indice = str.find(delimitador, inicio);
            if (indice == string::npos){
                aux = str.substr(inicio);
                if (aux != ""){
                    vec.push_back(stoi(aux));
                }
                break;
            }
            // Crea un substring auxiliar desde el delimitador inicial hasta el delimitador final.
            // Luego añade el substring como entero al vector.
            tamaño = indice - inicio;
            // Si el tamaño es 0, significa que la persona ingreso un valor invalido, por lo que se salta al siguiente.
            if (tamaño > 0){
                aux = str.substr(inicio, tamaño);
                vec.push_back(stoi(aux));
            }
            inicio = indice + 1;
        }while (true);
    }
    return vec;
}

string soloDigitos(string str, char delimitador){
    int newIndice = 0;
    for (int indice = 0; indice < str.size(); indice++){
        if (isdigit(str[indice]) || str[indice] == delimitador){
            str[newIndice++] = str[indice];
        }
    }
    str.resize(newIndice);
    return str;
}

Matriz newMatriz(int filas, int columnas){
    try {
        if (filas <= 0 || columnas <= 0){
            throw 0;
        }
    }
    catch (...){
        error("La matriz debe tener dimensiones mayores a 0.");
        // devuelve las dimensiones menores a 1 como 1
        filas = filas <= 0 ? 1 : filas;
        columnas = columnas <= 0 ? 1 : columnas;
    }
    
    // Asigna el espacio para las filas de la matriz
    Matriz matriz = (Matriz)malloc(filas * sizeof(Arreglo));
    // Asigna el espacio para las columnas de la matriz
    for(int i = 0; i < filas; i++){
        matriz[i] = (Arreglo)malloc(columnas * sizeof(long));
    }
    
    return matriz;
}

Matriz newMatriz(int dimension){
    return newMatriz(dimension, dimension);
}

void llenarMatriz(Matriz matriz, int filas, int columnas){
    string aux;
    vector<int> filaCompleta;
    for(int i = 0; i < filas; i++){
        cout << "Ingrese " << columnas << " valor/es para la fila N° " << i << " separandolas con una coma \",\"\tEjemplo: 10, 15, 5, 2, 4\n";
        do{
            getline(cin, aux);
            filaCompleta = split(aux, ',');
            if(filaCompleta.size() < columnas){
                error("La cantidad de datos ingresados es menor al esperado.");
            }
            if(filaCompleta.size() > columnas){
                filaCompleta.resize(columnas);
            }
        }while(filaCompleta.size() != columnas);
        for(int j = 0; j < columnas; j++){
            matriz[i][j] = filaCompleta[j];
        }
    }
}

void llenarMatriz(Matriz matriz, int filas, int columnas, int valor){
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            matriz[i][j] = valor;
        }
    }
}

void llenarMatriz(Matriz matriz, int filas, int columnas, int (*func)(int)){
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            matriz[i][j] = func(columnas*i+j);
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
    for (int i = 0; i < columnas; i++){
        cout << "\t#" << i;
    }
    cout << "\n";
    for (int i = 0; i < filas; i++){
        cout << "#" << i << "\t";
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
    generaParentesis(k, 0, cantMatrices-1, &cadena);
    for(int i = 0; i < cadena.size(); i++){
        cout << cadena[i];
    }
}

void generaParentesis(Matriz k, int i, int j, vector<string> *cadena){
    // Agrega parentesis al inicio y al final de la sub-cadena
    cadena->at(i) = "(" + cadena->at(i);
    cadena->at(j) = cadena->at(j) + ")";
    
    int tempk = k[i][j]-1;
    if(tempk != i){
        generaParentesis(k, i, tempk, cadena);
    }
    if((tempk+1) != j){
        generaParentesis(k, tempk+1, j, cadena);
    }
    if(j-i == 1){
        cadena->at(i) = cadena->at(i) + "*";
    }
}
