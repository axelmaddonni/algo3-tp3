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
    end = std::chrono::system_clock::now(); /* Terminamos medicion de tiempo */
#ifdef TOMAR_TIEMPO
    std::cerr << std::chrono::duration<double>(end - start).count();
#endif
    imprimir_solucionH(
        false, // inverso
        hallar_aristas_isomorfismo(g1, g2, solucion.isomorfismo),
        solucion);
  } else {
    solucion = goloso(g2, vertices2, g1, vertices1);
    end = std::chrono::system_clock::now(); /* Terminamos medicion de tiempo */
#ifdef TOMAR_TIEMPO
    std::cerr << std::chrono::duration<double>(end - start).count();
#endif
    imprimir_solucionH(
        true, // inverso
        hallar_aristas_isomorfismo(g2, g1, solucion.isomorfismo),
        solucion);
  }

  return 0;
}
