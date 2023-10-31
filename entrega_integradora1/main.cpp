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


int main() {
  std::cout << "Hello World!" << std::endl;
  return 0;
}
