#include <iostream>
#include <map>
#include <vector>

using namespace std;

/*
 *
 * Andrés Tarazona Solloa - A01023332
 * Programación Dinámica y Algoritmos Avaros
 * 28/09/2023
 *
 */

// FUNCION AVARO: Complejidad O(n)

vector<int> minNumMonGR(vector<int> coins, int p, int q) {
  // Un vector para tener a las monedas que se usan como respuesta
  vector<int> resp;
  int cambio = q - p;
  int i = 0;
  // Solo se usa un while, porque se va a agarrar la moneda mas grande que
  // quepa.
  while (cambio > 0) {
    if (coins[i] <= cambio) {
      resp.push_back(coins[i]);
      cambio -= coins[i];
    } else {
      i++;
    }
  }
  return resp;
}

// FUNCION DINAMICA: Complejidad O(n*m), donde m es el cambio.

vector<int> minNumMonPD(vector<int> coins, int p, int q) {
  // Se hace tag de los pasos que se van haciendo
  map<int, pair<int, int>> pasosConTag;
  vector<int> resp;
  int cambio = q - p;
  // Se inicializa el tag con 0 monedas y 0 pasos.
  pasosConTag[0] = make_pair(0, 0);
  for (int i = 1; i <= cambio; i++) {
    // Primero se usa un valor muy grande para el minimo.
    int min = 1000000000;
    int moneda = 0;
    for (int j = 0; j < coins.size(); j++) {
      if (coins[j] <= i) {
        if (pasosConTag[i - coins[j]].first + 1 < min) {
          min = pasosConTag[i - coins[j]].first + 1;
          moneda = coins[j];
        }
      }
    }
    pasosConTag[i] = make_pair(min, moneda);
  }

  int i = cambio;
  while (i > 0) {
    resp.push_back(pasosConTag[i].second);
    i -= pasosConTag[i].second;
  }

  return resp;
}

// FUNCIONES AUXILIARES

void excribeRespuesta(vector<int> coins, int p, int q) {
  // Ordenamos las monedas de mayor a menor
  sort(coins.begin(), coins.end(), greater<int>());
  // Hacemos el print de las monedas con el algoritmo avaro.
  cout << "Utilizando un algoritmo avaro: " << endl;
  vector<int> greedy = minNumMonGR(coins, p, q);
  for (int i = 0; i < coins.size(); i++) {
    int count = 0;
    // Se usa un range-based for loop.
    for (int coin : greedy) {
      if (coin == coins[i]) {
        count++;
      }
    }
    if (count > 0) {
      cout << count << " monedas de " << coins[i] << "." << endl;
    }
  }
  cout << endl;
  // Hacemos el print de las monedas con el algoritmo dinamico.
  cout << "Utilizando programacion dinamica: " << endl;
  vector<int> dinamica = minNumMonPD(coins, p, q);
  for (int i = 0; i < coins.size(); i++) {
    int count = 0;
    // Se usa un range-based for loop.
    for (int coin : dinamica) {
      if (coin == coins[i]) {
        count++;
      }
    }
    if (count > 0) {
      cout << count << " monedas de " << coins[i] << "." << endl;
    }
  }
  cout << endl;
}

int main() {
  // Creamos el vector de monedas
  vector<int> coins;
  // Declaramos nuestras variables a pedir
  int n, p, q;
  cout << "Ingrese el numero de monedas: ";
  cin >> n;
  for (int i = 0; i < n; i++) {
    int x;
    cout << "Ingrese el valor de la moneda " << i + 1 << ": ";
    cin >> x;
    coins.push_back(x);
  }
  cout << "Ingrese el valor del producto: ";
  cin >> p;
  cout << "Ingrese el valor de pago: ";
  cin >> q;
  // Llamamos a la funcion que nos da la respuesta
  excribeRespuesta(coins, p, q);
  return 0;
}
