#include "utilidades.h"
#include "goloso.h"
#include <list>

std::size_t computar_hash(Isomorfismo iso) {
  // http://stackoverflow.com/questions/20511347/a-good-hash-function-for-a-vector
  std::size_t seed = iso.size();
  for(auto& i : iso) {
    seed ^= (i.first + i.second) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
  }
  return seed;
}

bool busqueda_lineal(
    const std::list<std::pair<std::size_t, int>>& lista_tabu,
    std::size_t hash,
    int* resultado) {
  for (const auto& x : lista_tabu) {
    if (x.first == hash) {
      *resultado = x.second;
      return true;
    }
  }
  return false;
}


MCS tabu_search(Grafo &g1, std::set<int> &vertices1,
                Grafo &g2, std::set<int> &vertices2) {

  MCS source = goloso(g1, vertices1, g2, vertices2); 
  int lista_tabu_limite = 200;
  std::list<std::pair<std::size_t, int>> lista_tabu;

  int iteraciones_sin_mejorar = 0;
  int iteraciones_totales = 0;
  while (iteraciones_sin_mejorar < 500) {
  // while (iteraciones_totales < 2000) {
    MCS mejor_tabu = {.isomorfismo = Isomorfismo(), .aristas = 0};
    MCS mejor_solucion = {.isomorfismo = Isomorfismo(), .aristas = 0};
    if (g1.n < g2.n) {
      // Algoritmo REMPLAZAR
      vector<int> vertices = set_to_vector(vertices2);
      for (unsigned int i = 0; i < vertices.size(); i++) {
        for (unsigned int j = 0; j < source.isomorfismo.size(); j++) {
          Isomorfismo iso_actual = source.isomorfismo;
          std::swap(vertices[i], iso_actual[j].second);

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
    if (mejor_solucion.aristas > 0) {
      lista_tabu.push_back(std::make_pair(
            computar_hash(mejor_solucion.isomorfismo),
            mejor_solucion.aristas));
      if (lista_tabu.size() > lista_tabu_limite) { 
        lista_tabu.pop_front();
      }
    }
    if (mejor_solucion.aristas == 0) { // Funcion de aspiracion, todo es tabu
      if (mejor_tabu.aristas < source.aristas) {
        iteraciones_sin_mejorar = 0;
      } else {
        iteraciones_sin_mejorar++;
      }
      source  = mejor_tabu;
    } else if (mejor_solucion.aristas > source.aristas) {
      source = mejor_solucion;
      iteraciones_sin_mejorar = 0;
    } else {
      iteraciones_sin_mejorar++;
    }
    iteraciones_totales++;
  }


  return source;
}

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
  
  MCS solucion;
  if (g1.n < g2.n) {
    solucion = tabu_search(g1, vertices1, g2, vertices2);
    std::vector<std::pair<int, int>> aristas = hallar_aristas_isomorfismo(g1, g2, solucion.isomorfismo); 
    imprimir_solucionH(false, aristas, solucion);
  } else {
    solucion = tabu_search(g2, vertices2, g1, vertices1);
    std::vector<std::pair<int, int>> aristas = hallar_aristas_isomorfismo(g2, g1, solucion.isomorfismo);
    imprimir_solucionH(true, aristas, solucion);
  }

  return 0;
}
