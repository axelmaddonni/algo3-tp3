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
