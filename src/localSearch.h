#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

#include "greedy.h"

typedef int Neighborhood;

MCS local_search(Grafo &g1, vector<int> &vertices1, 
                 Grafo &g2, vector<int> &vertices2, 
                 Neighborhood nh);


#endif