#include "localSearch.h"

MCS local_search(Grafo &g1, vector<int> &vertices1, 
                 Grafo &g2, vector<int> &vertices2, 
                 Neighborhood nh) {
  MCS source = goloso(g1, vertices1, g2, vertices2);
  if (nh == 0) {
    bool mejore = true;
    short iteracion = 0;
    while(mejore && iteracion < 100) {
      mejore = false;
      for (unsigned int i = 0; i < source.isomorfismo.size(); i++) {
        for (unsigned int j = 0; j < source.isomorfismo.size(); j++) {
          Isomorfismo iso_actual = source.isomorfismo;
          std::swap(iso_actual[i].first, iso_actual[j].first);
          int aristas = contar_aristas_isomorfismo(g1, g2, iso_actual);
          if (aristas > source.aristas) {
            source.aristas = aristas;
            source.isomorfismo = iso_actual;
            mejore = true;
          } else {
            std::swap(iso_actual[i].first, iso_actual[j].first);
          }                       
        }
      }
      iteracion++;
    }
  }
  else if (nh == 1) {
    bool mejore = true;
    short iteracion = 0;
    while(mejore && iteracion < 100) {
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
            std::swap(vertices2[i], iso_actual[j].second);
          }
        }
      }
      iteracion++;
    }
  }

  return source;
}