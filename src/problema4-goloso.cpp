#include "goloso.h"
#include "utilidades.h"

#include <chrono>

int main() {
  Grafo g1, g2;
  leer_entrada(g1, g2);

  std::set<int> vertices1, vertices2;
  for (int i = 0; i < g1.n; i++) {
    vertices1.insert(i);
  }
  for (int i = 0; i < g2.n; i++) {
    vertices2.insert(i);
  }
  
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now(); /* Empezamos medicion de tiempo */

  MCS solucion;
  if (g1.n < g2.n) {
    solucion = goloso(g1, vertices1, g2, vertices2);
    std::vector<std::pair<int, int>> aristas = hallar_aristas_isomorfismo(g1, g2, solucion.isomorfismo);
    imprimir_solucionH(false, aristas, solucion);
  } else {
    solucion = goloso(g2, vertices2, g1, vertices1);
    std::vector<std::pair<int, int>> aristas = hallar_aristas_isomorfismo(g2, g1, solucion.isomorfismo);
    imprimir_solucionH(true, aristas, solucion);
  }

  return 0;
}
