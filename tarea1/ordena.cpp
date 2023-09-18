/*
 * Nombre: Andrés Tarazona Solloa
 * Matricula: A01023332
 */
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

vector<int> leeDatos(string nombreArchivo) {
    // Se inicializan todas las variables necesarias para leer el archivo.
    vector<int> datos;
    int dato;
    int n;
    // Se abre el archivo con la libreria fstream.
    ifstream archivo(nombreArchivo);
    // El operador >> es un operador de extracción de un archivo, regresa true por cada linea con un dato.
    // Se leen solamente N numero de datos.
    archivo >> n;
    for (int i = 0; i < n; i++) {
        if (archivo >> dato) {
            datos.push_back(dato);
        } else {
            cout << "Error al leer el archivo";
        }
    }
    // Se cierra el archivo.
    archivo.close();
    return datos;
}

void imprimeDatos(vector<int> datos) {
    // Itera cada elemento del vector e imprime el elemento.
    cout << "Datos: \n";
    for (int i = 0; i < datos.size(); i++) {
        cout << datos[i] << "\n";
    }
}

void merge(vector<int>& datos, int inicio, int mitad, int fin) {
    // Se declara el vector auxiliar que se va a regresar
    vector<int> datosOrdenados;

    // Se crean copias de los arrays que se van a mergear.
    vector<int> copiaIzq, copiaDer;

    // Se calcula el tamaño de los arrays copia.
    int tamIzq = mitad - inicio + 1;
    int tamDer = fin - mitad;

    // Se copian los datos de los arrays a los arrays copia.
    for (int i = 0; i < tamIzq; i++) {
        copiaIzq.push_back(datos[inicio + i]);
    }
    for (int i = 0; i < tamDer; i++) {
        copiaDer.push_back(datos[mitad + 1 + i]);
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

void mergeSort(vector<int>& datos, int inicio, int fin) {
    if (inicio >= fin) {
        return;
    }
    int mitad = inicio + (fin - inicio) / 2;
    mergeSort(datos, inicio, mitad);
    mergeSort(datos, mitad + 1, fin);
    merge(datos, inicio, mitad, fin);
}

// FUNCION AUXILIAR PARA PARTIR EL VECTOR EN DOS SEGÚN EL PIVOTE
int partition(vector<int>& datos, int low, int high) {
    // Se selecciona el pivote (en este caso, el primer elemento)
    int pivot = datos[low];
    // Índice para identificar la posición correcta del pivote
    int i = high + 1;
    for (int j = high; j > low; j--) {
        // Si el elemento actual es mayor o igual al pivote
        if (datos[j] >= pivot) {
            i--;
            swap(datos[i], datos[j]);
        }
    }
    swap(datos[i - 1], datos[low]);
    return (i - 1);
}

// FUNCION PRINCIPAL DE QUICKSORT
void quickSort(vector<int>& datos, int low, int high) {
    if (low < high) {
        // pos es la posición de particionamiento, los datos[pos] ahora están en el lugar correcto
        int pos = partition(datos, low, high);

        // Llama a quickSort para los dos subvectores
        // antes y después de pos
        quickSort(datos, low, pos - 1);
        quickSort(datos, pos + 1, high);
    }
}

int main() {
    vector<int> datos;

    datos = leeDatos("datos.txt");
    imprimeDatos(datos); // datos desordenados

    cout << "\nSe ordenan los datos con mergeSort: \n";
    mergeSort(datos, 0, datos.size() - 1);
    imprimeDatos(datos); // datos ordenados with Merge Sort

    cout << "\nPrimero se muestran desordenados otra vez:\n";
    datos = leeDatos("datos.txt");
    imprimeDatos(datos); // datos desordenados

    cout << "\nSe ordenan los datos con quickSort: \n";
    quickSort(datos, 0, datos.size() - 1);
    imprimeDatos(datos); // datos ordenados with Quick Sort

    return 0;
}
