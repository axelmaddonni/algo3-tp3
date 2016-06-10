
#include "utilidades.h"
#include "goloso.h"

int main(int argc, const char* argv[]) {
  string heuristica = argv[1];
  Grafo g1, g2;

  leer_entrada(g1, g2);

  std::vector<int> vertices1, vertices2;
  for (int i = 0; i < g1.n; i++) {
    vertices1.push_back(i);
  }
  for (int i = 0; i < g2.n; i++) {
    vertices2.push_back(i);
  }
  
  MCS solucion;
  if (g1.n < g2.n) {
    solucion = goloso(g1, vertices1, g2, vertices2);
    imprimir_solucionH(
        false, // inverso
        hallar_aristas_isomorfismo(g1, g2, solucion.isomorfismo),
        solucion);
  } else {
    solucion = goloso(g2, vertices2, g1, vertices1);
    imprimir_solucionH(
        true, // inverso
        hallar_aristas_isomorfismo(g2, g1, solucion.isomorfismo),
        solucion);
  }

  return 0;
}
