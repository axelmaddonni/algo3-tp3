#include "problema2-exacto.h"

#include <chrono>

int main() {
  Grafo g1, g2;
  leer_entrada(g1, g2);

  std::vector<int> vertices1, vertices2;
  for (int i = 0; i < g1.n; i++) {
    vertices1.push_back(i);
  }
  for (int i = 0; i < g2.n; i++) {
    vertices2.push_back(i);
  }

  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now(); /* Empezamos medicion de tiempo */
  solucion.aristas = 0;
  if (g1.n < g2.n) {
    bt(g1, vertices1, g2, vertices2, Isomorfismo());
    imprimir_solucion(
        false, // inverso
        hallar_aristas_isomorfismo(g1, g2, solucion.isomorfismo));
  } else {
    bt(g2, vertices2, g1, vertices1, Isomorfismo());
    imprimir_solucion(
        true, // inverso
        hallar_aristas_isomorfismo(g2, g1, solucion.isomorfismo));
  }
  end = std::chrono::system_clock::now(); /* Terminamos medicion de tiempo */
  #ifdef TOMAR_TIEMPO
  std::cerr << std::chrono::duration<double>(end - start).count();
  #endif

}
