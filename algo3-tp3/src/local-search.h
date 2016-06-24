#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

#include "goloso.h"

typedef int Neighborhood;

/*
  argv[1] = 0 para INTERCAQMBIAR
            1 para REMPLAZAR
            2 para 3-ROTACION
*/

MCS local_search(Grafo &g1, std::set<int> &vertices1, 
                 Grafo &g2, std::set<int> &vertices2, 
                 Neighborhood nh);


#endif
