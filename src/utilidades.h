#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <algorithm>  // std::swap
#include <iostream>
#include <set>
#include <utility>  // pair
#include <vector>

using namespace std;

struct Grafo {
  int n;
  int m;
  std::vector<std::vector<bool>> adj_matrix;
  std::vector<int> grados;
};

typedef std::vector<std::pair<int, int>> Isomorfismo;

struct MCS{
  Isomorfismo isomorfismo;
  int aristas;
};

std::vector<int> copiar_sin(std::vector<int> v, int x);

int contar_aristas_isomorfismo(Grafo g1, Grafo g2, Isomorfismo iso);

std::vector<std::pair<int, int>> hallar_aristas_isomorfismo(
    Grafo g1, Grafo g2, Isomorfismo iso);

void imprimir_solucionH(bool inverso,
    std::vector<std::pair<int, int>> aristas, MCS solucion);

void leer_entrada(Grafo& g1, Grafo& g2);

std::set<int> vector_to_set(std::vector<int> v);

#endif
