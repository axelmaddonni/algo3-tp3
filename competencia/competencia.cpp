#include "utilidades.h"
#include "goloso.h"
#include <chrono>

MCS solucion;
std::chrono::time_point<std::chrono::system_clock> start, now;

void heuristica(Grafo g1, std::set<int> vertices_1, 
               Grafo g2, std::set<int> vertices_2) {
  
  std::vector<int> vertices;

  if(g1.n <= 250) {
    solucion = goloso(g1, vertices_1, g2, vertices_2);
    vertices = set_to_vector(vertices_2);
  } else {  
    std::vector<int> vertices1 = set_to_vector(vertices_1);
    vertices = set_to_vector(vertices_2);
    solucion = goloso2(g1, vertices1, g2, vertices);
  }

  bool mejore = true;
  unsigned int aristas;
  unsigned int max_solu = g1.m < g2.m ? g1.m : g2.m;

  now = std::chrono::system_clock::now(); /* Vemos cuánto pasó */
  while(std::chrono::duration<double>(now - start).count() < 14.82 &&
        mejore && 
        solucion.aristas < max_solu) {
    
    mejore = false;

    //cerr << "Entré al while! Con " << solucion.aristas << " aristas" << endl;

    //Refinamiento por swaps
    for (unsigned int i = 0; i < solucion.isomorfismo.size(); i++) {
      for (unsigned int j = 0; j < solucion.isomorfismo.size(); j++) {
        if(i != j) {
          std::swap(solucion.isomorfismo[i].first, solucion.isomorfismo[j].first);
          aristas = contar_aristas_isomorfismo(g1, g2, solucion.isomorfismo);
          if (aristas > solucion.aristas) {
            solucion.aristas = aristas;
            mejore = true;
          } else {
            //No me quiero mover a soluciones peores o iguales
            std::swap(solucion.isomorfismo[i].first, solucion.isomorfismo[j].first);
          }
        }
      now = std::chrono::system_clock::now(); /* Vemos cuánto pasó */
      if(std::chrono::duration<double>(now - start).count() > 14.82) return;
      }
    }

    //cerr << "Hice búsqueda 0!" << endl;

    now = std::chrono::system_clock::now(); /* Vemos cuánto pasó */
    if(std::chrono::duration<double>(now - start).count() > 14.82) return;

    //Refinamiento por reemplazo
    for(unsigned int i = 0; i < vertices.size(); i++) {
      for(unsigned int j = 0; j < solucion.isomorfismo.size(); j++) {
        std::swap(vertices[i], solucion.isomorfismo[j].second);
        aristas = contar_aristas_isomorfismo(g1, g2, solucion.isomorfismo);
        if (aristas > solucion.aristas) {
          solucion.aristas = aristas;
          mejore = true;
        } else {
          //No me quiero mover a soluciones peores o iguales
          std::swap(vertices[i], solucion.isomorfismo[j].second);
        }
      }
      now = std::chrono::system_clock::now(); /* Vemos cuánto pasó */
      if(std::chrono::duration<double>(now - start).count() > 14.82) return;
    }
    //cerr << "Hice búsqueda 1!" << endl;
    now = std::chrono::system_clock::now(); /* Vemos cuánto pasó */
  }
}


int main(int argc, const char* argv[]) {
  start = std::chrono::system_clock::now(); /* Empezamos medicion de tiempo */
  Grafo g1, g2;
  leer_entrada(g1, g2);

  std::set<int> vertices1, vertices2;
  for (int i = 0; i < g1.n; i++) {
    vertices1.insert(i);
  }
  for (int i = 0; i < g2.n; i++) {
    vertices2.insert(i);
  }
  
  if (g1.n < g2.n) {
    heuristica(g1, vertices1, g2, vertices2);
    std::vector<std::pair<int, int>> aristas = hallar_aristas_isomorfismo(g1, g2, solucion.isomorfismo);
    imprimir_solucionH(false, aristas, solucion);
  } else {
    heuristica(g2, vertices2, g1, vertices1);
    std::vector<std::pair<int, int>> aristas = hallar_aristas_isomorfismo(g2, g1, solucion.isomorfismo);
    imprimir_solucionH(true, aristas, solucion);
  }

  now = std::chrono::system_clock::now(); /* Vemos cuánto pasó */
  //cout << "Duración total: " << std::chrono::duration<double>(now - start).count() << endl;
  //cout << "Cantidad de aristas: " << solucion.aristas << endl;  

  return 0;
}
