#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Función para leer el contenido de un archivo en una cadena
string readFile(const string &filename) {
  ifstream file(filename);
  string content, line;
  while (getline(file, line)) {
    content += line;
  }
  file.close();
  return content;
}

// Función para determinar si una cadena contiene a otra
int contains(const string &str, const string &substr) {
  // Inicializamos variables
  int strLen = str.length();
  int substrLen = substr.length();
  // Recorremos la cadena
  for (int i = 0; i <= strLen - substrLen; i++) {
    bool found = true;
    // Recorremos la subcadena
    for (int j = 0; j < substrLen; j++) {
      // Si no se cumple la condición, se rompe el ciclo
      if (str[i + j] != substr[j]) {
        found = false;
        break;
      }
    }
    if (found)
      return i + 1;
  }
  return -1;
}

// Función de algoritmo de manacher, que devuelve la posicion y el tamaño del
// palindromo mas largo Y recibe como parametro la cadena a analizar
pair<int, int> manacher(string s) {
  // Inicializamos variables
  string T;
  int n = s.size();
  // Agregamos valores especiales a la cadena
  for (int i = 0; i <= 2 * n; i++) {
    if (i % 2 == 0)
      T += "#";
    else
      T += s[i / 2];
  }
  // Inicializamos el vector de longitudes
  vector<int> L(2 * n + 1, 0);
  L[1] = 1;
  int maxLong = 0;
  int maxCenter = 0;
  int C = 1;
  int Ri = 0;
  int Li = 0;
  // Llenamos el vector de longitudes
  for (Ri = 2; Ri < 2 * n; Ri++) {
    Li = C - (Ri - C);
    bool expand = false;
    // Casos
    if (Ri < C + L[C]) {
      // Caso 1
      if (L[Li] < (C + L[C] - Ri)) {
        L[Ri] = L[Li];
        // Caso 2
      } else if ((L[Li] == (C + L[C] - Ri)) && (C + L[C]) == 2 * n) {
        L[Ri] = L[Li];
        // Caso 3
      } else if ((L[Li] == (C + L[C] - Ri)) && (C + L[C]) < 2 * n) {
        L[Ri] = L[Li];
        expand = true;
        // Caso 4
      } else if ((L[Li] > (C + L[C] - Ri)) && (C + L[C]) < 2 * n) {
        L[Ri] = C + L[C] - Ri;
        expand = true;
        // Si no se cumple ninguno de los casos anteriores
      } else {
        L[Ri] = 0;
        expand = true;
      }
    } else {
      L[Ri] = 0;
      expand = true;
    }
    // Expandimos el palindromo
    if (expand) {
      while (Ri + L[Ri] < 2 * n + 1 && Ri - L[Ri] > 0 &&
             T[Ri - L[Ri] - 1] == T[Ri + L[Ri] + 1])
        L[Ri]++;
    }
    if (Ri + L[Ri] > C + L[C]) {
      C = Ri;
    }
    if (L[Ri] > maxLong) {
      maxLong = L[Ri];
      maxCenter = Ri;
    }
  }
  // Encontramos la posicion de inicio del palindromo
  int start = (maxCenter - maxLong) / 2;
  int m = maxLong;
  // Valores que se regresan
  return make_pair(start, m);
}

// Longest Common Substring
pair<int, int> lcs(string t1, string t2) {
  // Inicializamos variables
  int n = t1.size();
  int m = t2.size();
  int start_pos = 0;
  int length = 0;
  int maxLong = 0;
  // Inicializamos la matriz de LCS
  vector<vector<int>> LCS(n, vector<int>(m, 0));
  // Llenamos la primera fila y columna
  for (int i = 0; i < n; i++) {
    if (t1[i] == t2[0]) {
      LCS[i][0] = 1;
      maxLong = 1;
    }
  }
  // Llenamos la primera columna
  for (int j = 0; j < m; j++) {
    if (t1[0] == t2[j]) {
      LCS[0][j] = 1;
      maxLong = 1;
    }
  }
  // Llenamos el resto de la matriz
  for (int i = 1; i < n; i++) {
    for (int j = 1; j < m; j++) {
      if (t1[i] == t2[j]) {
        LCS[i][j] = LCS[i - 1][j - 1] + 1;
        if (LCS[i][j] > maxLong) {
          maxLong = LCS[i][j];
        }
      } else {
        LCS[i][j] = 0;
      }
    }
  }
  // Encontramos la posicion de inicio del substring
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m - maxLong; j++) {
      if (LCS[i][j] == maxLong) {
        start_pos = i;
      }
    }
  }
  // Valores que se regresan
  length = maxLong;
  return make_pair(start_pos, length);
}

int main() {
  string transmission1 = readFile("transmission1.txt");
  string transmission2 = readFile("transmission2.txt");
  string mcode1 = readFile("mcode1.txt");
  string mcode2 = readFile("mcode2.txt");
  string mcode3 = readFile("mcode3.txt");

  cout << endl;
  int result1 = contains(transmission1, mcode1);
  cout << "mcode1.txt en transmission1.txt:" << endl;
  cout << (result1 != -1 ? "true" : "false") << " en pos. " << result1 << endl;

  cout << endl;
  int result2 = contains(transmission1, mcode2);
  cout << "mcode2.txt en transmission1.txt:" << endl;
  cout << (result2 != -1 ? "true" : "false") << " en pos. " << result2 << endl;

  cout << endl;
  int result3 = contains(transmission1, mcode3);
  cout << "mcode3.txt en transmission1.txt:" << endl;
  cout << (result3 != -1 ? "true" : "false") << " en pos. " << result3 << endl;

  cout << endl;
  int result4 = contains(transmission2, mcode1);
  cout << "mcode1.txt en transmission2.txt:" << endl;
  cout << (result4 != -1 ? "true" : "false") << " en pos. " << result4 << endl;

  cout << endl;
  int result5 = contains(transmission2, mcode2);
  cout << "mcode2.txt en transmission2.txt:" << endl;
  cout << (result5 != -1 ? "true" : "false") << " en pos. " << result5 << endl;

  cout << endl;
  int result6 = contains(transmission2, mcode3);
  cout << "mcode3.txt en transmission2.txt:" << endl;
  cout << (result6 != -1 ? "true" : "false") << " en pos. " << result6 << endl;

  cout << endl;
  pair<int, int> p = manacher(transmission1);
  int start = p.first;
  int m = p.second;
  cout << "El palindromo mas largo en transmission1 empieza en: " << start
       << " y tiene longitud: " << m << endl;
  cout << endl;
  pair<int, int> p2 = manacher(transmission2);
  int start2 = p2.first;
  int m2 = p2.second;
  cout << "El palindromo mas largo en transmission2 empieza en: " << start2
       << " y tiene longitud: " << m2 << endl;

  // SECCION DE LONGEST COMMON SUBSTRING
  cout << endl;
  pair<int, int> p3 = lcs(transmission1, transmission2);
  int lcs_start = p3.first;
  int lcs_length = p3.second;
  cout << "El substring común más largo entre los dos archivos empieza en: "
       << lcs_start - lcs_length + 1
       << " y tiene posición final:" << lcs_start + 1 << endl;

  return 0;
}
