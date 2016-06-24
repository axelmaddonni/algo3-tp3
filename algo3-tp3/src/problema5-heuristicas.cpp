#include "utilidades.h"
#include "goloso.h"
#include "local-search.h"

/*
  argv[1] = 0 para INTERCAQMBIAR
            1 para REMPLAZAR
            2 para 3-ROTACION
*/

int main(int argc, const char* argv[]) {
  Grafo g1, g2;
  leer_entrada(g1, g2);

  std::set<int> vertices1, vertices2;
  for (int i = 0; i < g1.n; i++) {
    vertices1.insert(i);
  }
  for (int i = 0; i < g2.n; i++) {
    vertices2.insert(i);
  }
  
  Neighborhood nh = atoi(argv[1]);
  MCS solucion;
  if (g1.n < g2.n) {
    solucion = local_search(g1, vertices1, g2, vertices2, nh);
    std::vector<std::pair<int, int>> aristas = hallar_aristas_isomorfismo(g1, g2, solucion.isomorfismo);
    imprimir_solucionH(false, aristas, solucion);
  } else {
    solucion = local_search(g2, vertices2, g1, vertices1, nh);
    std::vector<std::pair<int, int>> aristas = hallar_aristas_isomorfismo(g2, g1, solucion.isomorfismo);
    imprimir_solucionH(true, aristas, solucion);
  }

  return 0;
}
