#include <iostream>
#include <utility> 
#include <vector>

#include "utilidades.h"

#define MIN(a,b) ((a)<(b)?(a):(b))

MCS solucion;

inline bool ordenado_asc(const Isomorfismo& iso) {
  if (iso.size() < 2) {
    return true;
  }
  for (unsigned int i = 1; i < iso.size(); i++) {
    if (iso[i-1].first >= iso[i].first) {
      return false;
    }
  }
  return true;
}

void imprimir_solucion(bool inverso, std::vector<std::pair<int, int>> aristas) { 
  std::cout << solucion.isomorfismo.size() << " " << aristas.size() << std::endl;
  for (const auto p : solucion.isomorfismo) {
    if(inverso) std::cout << p.first << " ";
    else std::cout << p.second << " ";
  }
  std::cout << std::endl;
  for (const auto p : solucion.isomorfismo) {
    if(inverso) std::cout << p.second << " ";
    else std::cout << p.first << " ";
  }
  std::cout << std::endl;
  for (const auto p : aristas) {
    std::cout << p.first << " " << p.second << std::endl;
  }
}

void bt (Grafo g1, std::vector<int> vertices1, 
         Grafo g2, std::vector<int> vertices2,
         Isomorfismo iso) {
  if (solucion.aristas == MIN(g1.m, g2.m)) {
    return;
  }
  if (!ordenado_asc(iso)) {
    // Si iso = [(a0,b0), (a1,b1), ..., (an,bn)] y [a0, ..., an] no esta ordenado
    // ascendientemente, podemos considerar el reordenamiento
    //      [(a'0,b'0), (a'1,b'1), ..., (a'n,b'n)]
    // que es el mismo que antes solo que ahora a'0 < a'1 < ... < a'n. De esta
    // manera, nos ahorramos considerar el mismo isomorfismo varias veces, y
    // analizando solo la version en la que la primera coordenada esta ordenada
    // ascendientemente.
    return;
  }
  if ((int) iso.size() == g1.n) {
    int aristas = contar_aristas_isomorfismo(g1, g2, iso);
    if (aristas > solucion.aristas) {
      solucion.isomorfismo = iso;
      solucion.aristas = aristas;

      /*
      std::cerr << "Actualizando solucion." << std::endl;
      std::cerr << "\tIso: {";
      for (int i = 0; i < iso.size(); i++) {
        std::cerr << "(" << iso[i].first << ", " << iso[i].second << ") ";
      }
      std::cerr << "} [aristas = "  << aristas << "]" << std::endl;
      std::vector<std::pair<int, int>> e_ = 
        hallar_aristas_isomorfismo(g1, g2, solucion.isomorfismo);
      imprimir_solucion(false, e_);
      */
    }
    return;
  }

  for (const int u : vertices1) {
    for (const int v : vertices2) {
      Isomorfismo nuevo_iso = iso;
      nuevo_iso.push_back(std::make_pair(u, v));
      bt(g1, copiar_sin(vertices1, u),
         g2, copiar_sin(vertices2, v),
         nuevo_iso);
    }
  }
}


