#include "local-search.h"

MCS local_search(Grafo &g1, std::set<int> &vertices1,
                 Grafo &g2, std::set<int> &vertices2,
                 Neighborhood nh) {

  MCS source = goloso(g1, vertices1, g2, vertices2);
  
  //INTERCAMBIAR
  //Estrategia que consiste en probar distintas permutaciones de
  //los vértices de g1 en el mapeo. Las permutaciones se arman
  //a partir de swappear mapeos de a pares en la solución fuente,
  //por lo que no se comprueban las n! permutaciones, sino O(n^2).
  if (nh == 0) {
    bool mejore = true;
    while(mejore) {
      mejore = false;
      for (unsigned int i = 0; i < source.isomorfismo.size(); i++) {
        for (unsigned int j = 0; j < source.isomorfismo.size(); j++) {
          if(i != j) {
            std::swap(source.isomorfismo[i].first, source.isomorfismo[j].first);
            int aristas = contar_aristas_isomorfismo(g1, g2, source.isomorfismo);
            if (aristas > source.aristas) {
              source.aristas = aristas;
              mejore = true;
            } else {
              //No me quiero mover a soluciones peores o iguales
              std::swap(source.isomorfismo[i].first, source.isomorfismo[j].first);
            }
          }
        }
      }
    }
  }

  //REMPLAZAR
  //Estrategia que consiste en ver qué pasa cuando usamos nodos de
  //vertices2 que no habíamos puesto en la solución fuente 
  //(asumimos #vertices1 < #vertices2) mapeándolos con cada uno de 
  //los vértices de g1.
  //Notar que si #vertices1 = #vertices2 el algoritmo termina en O(1)
  else if (nh == 1) {
    bool mejore = true;
    Isomorfismo iso_actual;
    vector<int> vertices = set_to_vector(vertices2);
    while(mejore) {
      mejore = false;
      for(unsigned int i = 0; i < vertices.size(); i++) {
        for(unsigned int j = 0; j < source.isomorfismo.size(); j++) {
          std::swap(vertices[i], source.isomorfismo[j].second);
          int aristas = contar_aristas_isomorfismo(g1, g2, source.isomorfismo);
          if (aristas > source.aristas) {
            source.aristas = aristas;
            mejore = true;
          } else {
            //No me quiero mover a soluciones peores o iguales
            std::swap(vertices[i], source.isomorfismo[j].second);
          }
        }
      }
    }
  }

  //3-ROTACION
  //Estrategia que consiste en probar distintas permutaciones de
  //los vértices de g1 en el mapeo. Las permutaciones se arman
  //a partir de rotaciones de a 3 en la solución fuente,
  //por lo que no se comprueban las n! permutaciones, sino O(n^3).
  //En particular se siguen comprobando los swaps de 2 elementos.
  else if (nh == 2) {
    bool mejore = true;
    Isomorfismo iso_actual;
    while(mejore) {
      mejore = false;
      for (unsigned int i = 0; i < source.isomorfismo.size(); i++) {
        for (unsigned int j = 0; j < source.isomorfismo.size(); j++) {
          if(i != j) {
            for (unsigned int k = 0; k < source.isomorfismo.size(); k++) {
              std::swap(source.isomorfismo[i].first, source.isomorfismo[k].first);
              std::swap(source.isomorfismo[k].first, source.isomorfismo[j].first);
              int aristas = contar_aristas_isomorfismo(g1, g2, source.isomorfismo);
              if (aristas > source.aristas) {
                source.aristas = aristas;
                mejore = true;
              } else {
                //No me quiero mover a soluciones peores o iguales
                std::swap(source.isomorfismo[k].first, source.isomorfismo[j].first);
                std::swap(source.isomorfismo[i].first, source.isomorfismo[k].first);
              }
            }
          }
        }
      }
    }
  }

  return source;
}
