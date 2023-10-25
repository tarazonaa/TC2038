#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

static const char hexDigits[] = "0123456789ABCDEF";

// FUNCION PARA HASHEAR EL STRING
string hashing(string fileName, int n) {
  // Se lee el archivo primero
  ifstream file(fileName);
  string c;
  string charString = "";
  int p = 31;
  int m = 1e9 + 9;
  int64 potencia = 1;
  // Se agregan los caracteres a un char array
  while (file >> c) {
    charString += c;
  }
  // Se agrega el padding
  while (charString.length() < n) {
    charString += "0";
  }
  // Se crea el arreglo para guardar las sumas de las columnas
  vector<int> sumas(n);
  // Se suman las columnas
  for (int i = 0; i < n; i++) {
    int suma = 0;
    for (int j = 0; j < charString.length(); j++) {
      suma += charString[j + 4 * i];
    }
    sumas[i] = suma % 256;
  }
  // Print sumas
  // Se crea el string final con hexadecimal
  string finalString = "";
  for (int i = 0; i < n / 4; i++) {
    finalString += hexDigits[sumas[i] / 16];
    finalString += hexDigits[sumas[i] % 16];
  }
  file.close();
  return finalString;
}

int main() {
  string s;
  int n;
  cout << "Ingrese el nombre del archivo: ";
  cin >> s;
  cout << "Ingrese el numero de columnas (múltiplo de 4 entre 16 y 64): ";
  cin >> n;
  string finalString = hashing(s, n);
  cout << finalString << endl;
}
