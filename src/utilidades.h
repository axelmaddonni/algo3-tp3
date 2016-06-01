#include <vector>
#include <utility>  // pair 

using namespace std;

struct Grafo {
  int n;
  int m;
  std::vector<std::vector<bool>> adj_matrix;
  std::vector<int> grados;
};

typedef std::vector<std::pair<int, int>> Isomorfismo;

struct {
  Isomorfismo isomorfismo;
  int aristas;
} solucion;

std::vector<int> copiar_sin(std::vector<int> v, int x) {
  std::vector<int> v_copia;
  for (const auto y : v) {
    if (y != x) {
      v_copia.push_back(y);
    }
  }
  return v_copia;
}


bool lin_search(std::vector<int> v, int x) {
  for (const auto y : v) {
    if (x == y) {
      return true;
    }
  }
  return false;
}

int contar_aristas_isomorfismo(Grafo g1, Grafo g2, Isomorfismo iso) {
  int aristas = 0;
  for (const auto p : iso) {
    for (const auto q : iso) {
      int vg1 = p.first;
      int vg2 = p.second;
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
