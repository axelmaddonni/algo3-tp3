#ifndef GREEDY_H
#define GREEDY_H

#include "utilidades.h"

void sort_adj(std::vector<int> &lista, Grafo g);

MCS goloso(
    Grafo g1, std::vector<int> &vertices1,
    Grafo g2, std::vector<int> &vertices2);

#endif
