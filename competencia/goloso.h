#ifndef GREEDY_H
#define GREEDY_H

#include "utilidades.h"
#include <set>

int mayor_adj(std::set<int>& lista, Grafo g);

MCS goloso(
    Grafo g1, std::set<int> &vertices1,
    Grafo g2, std::set<int> &vertices2);

MCS goloso2(
    Grafo g1, std::vector<int> &vertices1,
    Grafo g2, std::vector<int> &vertices2);

#endif
