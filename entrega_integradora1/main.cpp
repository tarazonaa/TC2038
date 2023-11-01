#include <iostream>
#include <fstream>
#include <string>


using namespace std;

// Función para leer el contenido de un archivo en una cadena
string readFile(const string& filename) {
    ifstream file(filename);
    string content, line;
    while (getline(file, line)) {
        content += line;
    }
    file.close();
    return content;
}

// Función para determinar si una cadena contiene a otra
int contains(const string& str, const string& substr) {
    size_t pos = str.find(substr);
    if (pos != string::npos) {
        return pos + 1;  
    }
    return false;
    
}


int main() {

    string transmission1 = readFile("transmission1.txt");
    string transmission2 = readFile("transmission2.txt");
    string mcode1 = readFile("mcode1.txt");
    string mcode2 = readFile("mcode2.txt");
    string mcode3 = readFile("mcode3.txt");


    cout << (contains(transmission1, mcode1) != false) << " " << contains(transmission1, mcode1) << endl;
    cout << (contains(transmission1, mcode2) != false) << " " << contains(transmission1, mcode2) << endl;
    cout << (contains(transmission1, mcode3) != false) << " " << contains(transmission1, mcode3) << endl;
    cout << (contains(transmission2, mcode1) != false) << " " << contains(transmission2, mcode1) << endl;
    cout << (contains(transmission2, mcode2) != false) << " " << contains(transmission2, mcode2) << endl;
    cout << (contains(transmission2, mcode3) != false) << " " << contains(transmission2, mcode3) << endl;

  return 0;
}

