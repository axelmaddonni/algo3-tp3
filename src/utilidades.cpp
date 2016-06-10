#include "utilidades.h"

std::vector<int> copiar_sin(std::vector<int> v, int x) {
  std::vector<int> v_copia;
  for (const auto y : v) {
    if (y != x) {
      v_copia.push_back(y);
    }
  }
  return v_copia;
}

int contar_aristas_isomorfismo(Grafo g1, Grafo g2, Isomorfismo iso) {
  int aristas = 0;
  for (const auto p : iso) {
    int vg1 = p.first;
    int vg2 = p.second;
    for (const auto q : iso) {
      int ug1 = q.first;
      int ug2 = q.second;

      if (g1.adj_matrix[vg1][ug1] && // ug1 y vg1 estan conectados.
          g2.adj_matrix[vg2][ug2]) { // ug2 y vg2 estan conectados.
        aristas++;
      }
    }
  }

  return aristas / 2; // conte todas 2 veces;
}

std::vector<std::pair<int, int>> hallar_aristas_isomorfismo(
    Grafo g1, Grafo g2, Isomorfismo iso) {
  std::vector<std::pair<int, int>> aristas;
  for (unsigned int i = 0; i < iso.size(); i++) {
    auto p = iso[i];
    for (unsigned int j = i + 1; j < iso.size(); j++) {
      auto q = iso[j];
      if (g1.adj_matrix[p.first][q.first] && 
          g2.adj_matrix[p.second][q.second]) {
        aristas.push_back(std::make_pair(i, j));
      }
    }
  }
  return aristas;
}

void imprimir_solucionH(bool inverso, std::vector<std::pair<int, int>> aristas, MCS solucion) { 
  std::cout << solucion.isomorfismo.size() << " " << aristas.size() << std::endl;
  for (const auto p : solucion.isomorfismo) {
    if(!inverso) std::cout << p.first << " ";
    else std::cout << p.second << " ";
  }
  std::cout << std::endl;
  for (const auto p : solucion.isomorfismo) {
    if(!inverso) std::cout << p.second << " ";
    else std::cout << p.first << " ";
  }
  std::cout << std::endl;
  for (const auto p : aristas) {
    std::cout << p.first << " " << p.second << std::endl;
  }
}

void leer_entrada(Grafo& g1, Grafo& g2) {
  std::cin >> g1.n >> g1.m >> g2.n >> g2.m;

  g1.adj_matrix = vector<vector<bool>>(g1.n, vector<bool>(g1.n, false));
  g2.adj_matrix = vector<vector<bool>>(g2.n, vector<bool>(g2.n, false));
  g1.grados = vector<int>(g1.n, 0);
  g2.grados = vector<int>(g2.n, 0);
  for (int i = 0; i < g1.m; i++) {
    int u, v;
    std::cin >> u >> v;
    g1.adj_matrix[u][v] = true;
    g1.adj_matrix[v][u] = true;
    g1.grados[u]++;
    g1.grados[v]++;
  }
  for (int i = 0; i < g2.m; i++) {
    int u, v;
    std::cin >> u >> v;
    g2.adj_matrix[u][v] = true;
    g2.adj_matrix[v][u] = true;
    g2.grados[u]++;
    g2.grados[v]++;
  }
}
