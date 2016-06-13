#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

#include "goloso.h"

typedef int Neighborhood;

MCS local_search(Grafo &g1, std::set<int> &vertices1, 
                 Grafo &g2, std::set<int> &vertices2, 
                 Neighborhood nh);


#endif
