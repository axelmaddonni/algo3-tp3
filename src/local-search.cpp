#include "local-search.h"

MCS local_search(Grafo &g1, vector<int> &vertices1,
                 Grafo &g2, vector<int> &vertices2,
                 Neighborhood nh) {

  MCS source = goloso(g1, vertices1, g2, vertices2);
  
  //Estrategia que consiste en probar distintas permutaciones de
  //los vértices de g1 en el mapeo. Las permutaciones se arman
  //a partir de swappear mapeos de a pares en la solución fuente,
  //por lo que no se comprueban las n! permutaciones, sino O(n^2).
  //Caso bueno: 5-2
  if (nh == 0) {
    bool mejore = true;
    short iteracion = 0;
    while(mejore) {
      mejore = false;
      for (unsigned int i = 0; i < source.isomorfismo.size(); i++) {
        for (unsigned int j = 0; j < source.isomorfismo.size(); j++) {
          if(i != j) {
            Isomorfismo iso_actual = source.isomorfismo;
            std::swap(iso_actual[i].first, iso_actual[j].first);
            int aristas = contar_aristas_isomorfismo(g1, g2, iso_actual);
            if (aristas > source.aristas) {
              source.aristas = aristas;
              source.isomorfismo = iso_actual;
              mejore = true;
            }
          }
        }
      }
      iteracion++;
    }
  }

  //Estrategia que consiste en ver qué pasa cuando usamos nodos de
  //vertices2 que no habíamos puesto en la solución fuente 
  //(asumimos #vertices1 < #vertices2) mapeándolos con cada uno de 
  //los vértices de g1.
  //Notar que si #vertices1 = #vertices2 el algoritmo termina en O(1)
  //Caso bueno: 3
  else if (nh == 1) {
    bool mejore = true;
    short iteracion = 0;
    while(mejore) {
      mejore = false;
      for(unsigned int i = 0; i < vertices2.size(); i++) {
        for(unsigned int j = 0; j < source.isomorfismo.size(); j++) {
          Isomorfismo iso_actual = source.isomorfismo;
          std::swap(vertices2[i], iso_actual[j].second);
          int aristas = contar_aristas_isomorfismo(g1, g2, iso_actual);
          if (aristas > source.aristas) {
            source.aristas = aristas;
            source.isomorfismo = iso_actual;
            mejore = true;
          } else {
            //No quiero moverme a soluciones peores y, en principio,
            //no me interesa moverme a soluciones equivalentes.
            std::swap(vertices2[i], iso_actual[j].second);
          }
        }
      }
      iteracion++;
    }
  }

  else if (nh == 2) {
    bool mejore = true;
    short iteracion = 0;
    while(mejore) {
      mejore = false;
      for (unsigned int i = 0; i < source.isomorfismo.size(); i++) {
        for (unsigned int j = 0; j < source.isomorfismo.size(); j++) {
          if(i != j) {
            for (unsigned int k = 0; k < source.isomorfismo.size(); k++) {
              Isomorfismo iso_actual = source.isomorfismo;
              std::swap(iso_actual[i].first, iso_actual[k].first);
              std::swap(iso_actual[k].first, iso_actual[j].first);
              int aristas = contar_aristas_isomorfismo(g1, g2, iso_actual);
              if (aristas > source.aristas) {
                source.aristas = aristas;
                source.isomorfismo = iso_actual;
                mejore = true;
              }
            }
          }
        }
      }
      iteracion++;
    }
  }

  return source;
}
