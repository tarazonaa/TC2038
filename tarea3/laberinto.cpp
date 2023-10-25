/*
 *
 * Andrés Tarazona Solloa
 * A01023332
 * BRANCH AND BOUND Y BACKTRACKING
 */
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::vector<int>> mapa;
std::vector<std::vector<int>> mapaCopia;
std::vector<std::vector<int>> salida;
std::vector<std::vector<bool>> visitados;

struct Cell {
  int x, y, pasos;
  std::pair<int, int> prev;
  Cell(int x, int y, int pasos, std::pair<int, int> prev = {-1, -1})
      : x(x), y(y), pasos(pasos), prev(prev) {}
};

void leeArchivo(std::string nombre) {
  std::ifstream archivo(nombre);
  if (!archivo.is_open()) {
    std::cout << "No se pudo abrir el archivo" << std::endl;
    return;
  }
  int n, m;
  archivo >> n >> m;
  mapa.resize(n);
  for (int i = 0; i < n; i++) {
    mapa[i].resize(m);
    for (int j = 0; j < m; j++) {
      archivo >> mapa[i][j];
    }
  }
  salida.resize(n);
  for (int i = 0; i < n; i++) {
    salida[i].resize(m);
  }
  std::cout << "Mapa de entrada: " << std::endl;
  for (int i = 0; i < mapa.size(); i++) {
    for (int j = 0; j < mapa[i].size(); j++) {
      std::cout << mapa[i][j] << " ";
    }
    std::cout << std::endl;
  }
  mapaCopia = mapa;
  archivo.close();
}

// FUNCION CON BACKTRACKING
bool backtracking(int i, int j) {
  // Se llama recursivamente a la funcion backtracking
  // primero se verifica si se llego a la salida
  int n = mapa.size();
  int m = mapa[0].size();
  if (i < 0 || i >= n || j < 0 || j >= m || mapa[i][j] != 1) {
    return false;
  }
  if (i == n - 1 && j == m - 1) {
    salida[i][j] = 1;
    return true;
  }
  // Se van a checar las cuatro direcciones, por lo tanto bloqueamos el camino
  // que ya llevamos.
  salida[i][j] = 1;
  mapa[i][j] = 0;

  // Se pueden checar todas las direcciones al mismo momento.
  if (backtracking(i + 1, j) || backtracking(i - 1, j) ||
      backtracking(i, j + 1) || backtracking(i, j - 1)) {
    return true;
  }

  // Se quita la marca de la solucion si no se regresa true:
  salida[i][j] = 0;
  mapa[i][j] = 1;

  return false;
}

// FUNCION CON BRANCH AND BOUND
void branchAndBound() {
  int n = mapa.size();
  int m = mapa[0].size();

  // Matriz para controlar las celdas visitadas
  std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));

  // Inicializar la matriz de salida con ceros
  salida.assign(n, std::vector<int>(m, 0));

  std::queue<Cell> q;
  q.push({0, 0, 0, {-1, -1}});
  visited[0][0] = true; // Marcar la celda de inicio como visitada de inmediato

  std::vector<Cell> path;

  while (!q.empty()) {
    Cell current = q.front();
    q.pop();

    // Si se ha llegado a la celda de destino
    if (current.x == n - 1 && current.y == m - 1) {
      // Se guarda el camino
      while (current.prev.first != -1 && current.prev.second != -1) {
        path.push_back(current);
        current = {current.prev.first,
                   current.prev.second,
                   current.pasos - 1,
                   {-1, -1}};
      }
      break;
    } else {
      // Se guarda el camino

      path.push_back(current);
    }

    static int dx[] = {-1, 1, 0, 0};
    static int dy[] = {0, 0, -1, 1};

    for (int dir = 0; dir < 4; ++dir) {
      int newX = current.x + dx[dir];
      int newY = current.y + dy[dir];

      if (newX >= 0 && newX < n && newY >= 0 && newY < m &&
          !visited[newX][newY] && mapa[newX][newY] == 1) {
        visited[newX][newY] = true; // Marcar la celda como visitada aquí mismo
        q.push({newX, newY, current.pasos + 1, {current.x, current.y}});
      }
    }
  }

  // Se recorre la salida para marcar el camino
  for (int i = 0; i < path.size(); i++) {
    salida[path[i].x][path[i].y] = 1;
  }
}

void imprimeSoluciones() {
  backtracking(0, 0);
  std::cout << "Solucion con Backtracking:" << std::endl;
  for (int i = 0; i < salida.size(); i++) {
    for (int j = 0; j < salida[i].size(); j++) {
      std::cout << salida[i][j] << " ";
    }
    std::cout << std::endl;
  }
  // Reiniciamos el mapa original.
  mapa = mapaCopia;
  branchAndBound();
  std::cout << "Solucion con Branch and Bound:" << std::endl;
  for (int i = 0; i < salida.size(); i++) {
    for (int j = 0; j < salida[i].size(); j++) {
      std::cout << salida[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

int main() {
  leeArchivo("data.txt");
  imprimeSoluciones();
  return 0;
}
