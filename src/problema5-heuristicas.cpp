#include "utilidades.h"
#include "goloso.h"
#include "local-search.h"

int main(int argc, const char* argv[]) {
  Grafo g1, g2;
  leer_entrada(g1, g2);

  std::vector<int> vertices1, vertices2;
  for (int i = 0; i < g1.n; i++) {
    vertices1.push_back(i);
  }
  for (int i = 0; i < g2.n; i++) {
    vertices2.push_back(i);
  }
  
  // TODO: Ver como cambiar esto.
  Neighborhood nh = 0;
  MCS solucion;
  if (g1.n < g2.n) {
    solucion = local_search(g1, vertices1, g2, vertices2, nh);
    imprimir_solucionH(
        false, // inverso
        hallar_aristas_isomorfismo(g1, g2, solucion.isomorfismo),
        solucion);
  } else {
    solucion = local_search(g2, vertices2, g1, vertices1, nh);
    imprimir_solucionH(
        true, // inverso
        hallar_aristas_isomorfismo(g2, g1, solucion.isomorfismo),
        solucion);
  }

  return 0;
}
