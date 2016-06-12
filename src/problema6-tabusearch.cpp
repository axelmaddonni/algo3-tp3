#include "utilidades.h"
#include "goloso.h"

std::size_t computar_hash(Isomorfismo iso) {
  // http://stackoverflow.com/questions/20511347/a-good-hash-function-for-a-vector
  std::size_t seed = iso.size();
  for(auto& i : iso) {
    seed ^= (i.first + i.second) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
  }
  return seed;
}

bool busqueda_lineal(
    std::vector<std::pair<std::size_t, int>> lista_tabu,
    std::size_t hash,
    int* resultado) {
  for (int i = 0; i < lista_tabu.size(); i++) {
    if (lista_tabu[i].first == hash) {
      *resultado = lista_tabu[i].second;
      return true;
    }
  }
  return false;
}


MCS tabu_search(Grafo &g1, vector<int> &vertices1,
                Grafo &g2, vector<int> &vertices2) {

  MCS source = goloso(g1, vertices1, g2, vertices2);  
  std::vector<std::pair<std::size_t, int>> lista_tabu(1000, std::make_pair(0, 0));
  int indice_lista_tabu = 0;

  int iteraciones_sin_mejorar = 0;
  while (iteraciones_sin_mejorar < 100000) {
    //std::cerr << "source.aristas = " << source.aristas
    //          << " (" << iteraciones_sin_mejorar << ")" << std::endl;
    MCS mejor_tabu = {.isomorfismo = Isomorfismo(), .aristas = 0};
    MCS mejor_solucion = {.isomorfismo = Isomorfismo(), .aristas = 0};
    if (g1.n < g2.n) {
      // Estrategia que consiste en ver qué pasa cuando usamos nodos de
      // vertices2 que no habíamos puesto en la solución fuente 
      // (asumimos #vertices1 < #vertices2) mapeándolos con cada uno de 
      // los vértices de g1.
      // Notar que si #vertices1 = #vertices2 el algoritmo termina en O(1)
      // Caso bueno: 3
      for (unsigned int i = 0; i < vertices2.size(); i++) {
        for (unsigned int j = 0; j < source.isomorfismo.size(); j++) {
          Isomorfismo iso_actual = source.isomorfismo;
          std::swap(vertices2[i], iso_actual[j].second);

          int aristas = 0;
          if (busqueda_lineal(lista_tabu, computar_hash(iso_actual), &aristas) &&
              aristas > mejor_tabu.aristas) {
            mejor_tabu = { .isomorfismo = iso_actual, .aristas = aristas };
            continue;
          }

          aristas = contar_aristas_isomorfismo(g1, g2, iso_actual);
          if (aristas > mejor_solucion.aristas) {
            mejor_solucion = { .isomorfismo = iso_actual, .aristas = aristas };
          }
        }
      }
    } else {
      for (unsigned int i = 0; i < source.isomorfismo.size(); i++) {
        for (unsigned int j = 0; j < source.isomorfismo.size(); j++) {
          if (i == j) {
            continue;
          }
          Isomorfismo iso_actual = source.isomorfismo;
          std::swap(iso_actual[i].second, iso_actual[j].second);

          int aristas = 0;
          if (busqueda_lineal(lista_tabu, computar_hash(iso_actual), &aristas) &&
              aristas > mejor_tabu.aristas) {
            mejor_tabu = { .isomorfismo = iso_actual, .aristas = aristas };
            continue;
          }

          aristas = contar_aristas_isomorfismo(g1, g2, iso_actual);
          if (aristas > mejor_solucion.aristas) {
            mejor_solucion = { .isomorfismo = iso_actual, .aristas = aristas };
          }
        }
      }
    }
    if (mejor_solucion.aristas == 0) { // Funcion de aspiracion, todo es tabu
      if (mejor_tabu.aristas < source.aristas) {
        iteraciones_sin_mejorar = 0;
      } else {
        iteraciones_sin_mejorar++;
      }
      source  = mejor_tabu;
    } else if (mejor_solucion.aristas < source.aristas) {
      source = mejor_solucion;
      iteraciones_sin_mejorar = 0;
    } else {
      iteraciones_sin_mejorar++;
    }
  }


  return source;
}
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
  
  MCS solucion;
  if (g1.n < g2.n) {
    solucion = tabu_search(g1, vertices1, g2, vertices2);
    imprimir_solucionH(
        false, // inverso
        hallar_aristas_isomorfismo(g1, g2, solucion.isomorfismo),
        solucion);
  } else {
    solucion = tabu_search(g2, vertices2, g1, vertices1);
    imprimir_solucionH(
        true, // inverso
        hallar_aristas_isomorfismo(g2, g1, solucion.isomorfismo),
        solucion);
  }

  return 0;
}
