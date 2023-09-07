/*
 * Nombre: Andrés Tarazona Solloa
 * Matricula: A01023332
 */
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

// FUNCIONES QUE IMPLEMENTA EL ALGORITMO DE MERGESORT.
// Se decalara el auxiliar afuera de las dos funciones parte de mergesort:
// FUNCION AUXILAR PARA MERGEAR LOS DATOS.
void merge(vector<int> datos, int inicio, int mitad, int fin) {
    // Se crean copias de los arrays que se van a mergear.
    vector<int> copiaIzq, copiaDer;

    // Se calcula el tamaño de los arrays copia.
    int tamIzq = mitad - inicio + 1;
    int tamDer = fin - mitad;

    // Se copian los datos de los arrays a los arrays copia.
    for (int i = inicio; i <= mitad; i++) {
        copiaIzq.push_back(datos[i]);
    }
    for (int i = mitad + 1; i <= fin; i++) {
        copiaDer.push_back(datos[i]);
    }

    // Se inicializan los indices de los arrays copia.
    int indiceIzq = 0, indiceDer = 0;
    // Se inicializa el indice del array original.
    int indiceOriginal = inicio;

    // Se itera hasta que se llegue al final de alguno de los arrays copia.
    while (indiceIzq < tamIzq && indiceDer < tamDer) {
        // Si el elemento del array izquierdo es menor o igual al del array derecho, se guarda en el array original.
        if (copiaIzq[indiceIzq] <= copiaDer[indiceDer]) {
            datos[indiceOriginal] = copiaIzq[indiceIzq];
            indiceIzq++;
        }
        // Si el elemento del array derecho es menor o igual al del array izquierdo, se guarda en el array original.
        else {
            datos[indiceOriginal] = copiaDer[indiceDer];
            indiceDer++;
        }
        indiceOriginal++;
    }

    // Se copian los elementos restantes del array restante.
    while (indiceIzq < tamIzq) {
        datos[indiceOriginal] = copiaIzq[indiceIzq];
        indiceIzq++;
        indiceOriginal++;
    }
    while (indiceDer < tamDer) {
        datos[indiceOriginal] = copiaDer[indiceDer];
        indiceDer++;
        indiceOriginal++;
    }

}

void mergeSort(vector<int> datos, int inicio, int fin) {
    if (fin <= inicio) return;
    int mitad = inicio + (fin - inicio) / 2;
    mergeSort(datos, inicio, mitad);
    mergeSort(datos, mitad + 1, fin);
    merge(datos, inicio, mitad, fin);
}

vector<int> quickSort(vector<int> datos) {
    return datos;
}

vector<int> leeDatos(string nombreArchivo) {
    // Se inicializan todas las variables necesarias para leer el archivo.
    vector<int> datos;
    int dato;
    // Se abre el archivo con la libreria fstream.
    ifstream archivo(nombreArchivo);
    // El operador >> es un operador de extracción de un archivo, regresa true por cada linea con un dato.
    while (archivo >> dato) {
        datos.push_back(dato);
    }
    return datos;
}

void imprimeDatos(vector<int> datos) {
    // Itera cada elemento del vector e imprime el elemento.
    cout<<"Datos: \n";
    for (int i = 0; i < datos.size(); i++) {
        cout << datos[i] << "\n";
    }
}

int main(){

     vector<int> datos, datosOrdenados;

     datos = leeDatos("datos.txt");

     imprimeDatos(datos); // datos desordenados

     cout << "\nSe ordenan los datos con mergeSort: \n";

    mergeSort(datos, 0, datos.size() - 1);

     imprimeDatos(datos); // datos ordenados con Merge Sort


     cout << "\nPrimero se muestran desordenados otra vez:\n";

     datosOrdenados = quickSort(datos); 

     cout << "\nSe ordenan los datos con quickSort: \n";

     imprimeDatos(datosOrdenados); // datos ordenados con Quick Sort

     return 0;

}
