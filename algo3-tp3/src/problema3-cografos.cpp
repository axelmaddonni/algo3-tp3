#include "problema3-cografos.h"

#include <assert.h>
#include <iostream>
#include <string>

int main(int argc, char const *argv[]) {

	Grafo_adjlist g;
	int tamGrafoCompleto;
	int aristasGrafoCompleto;

	cin >> g.n >> g.m >> tamGrafoCompleto >> aristasGrafoCompleto ;

	for (int i = 0; i < g.n; i++) {
		g.adj_list.insert(pair<int,vector<int>>(i, vector<int>()));
	}

	for (int i = 0; i < g.m; i++) {
		int u, v;
		cin >> u >> v;
		g.adj_list[u].push_back(v);
		g.adj_list[v].push_back(u);
	}

	CographTree cografo(g); 
	Grafo_adjlist mcs = subgrafoInducido(g, cografo.nodosMCS(tamGrafoCompleto));

	imprimirSolucion(mcs);

	return 0;
}