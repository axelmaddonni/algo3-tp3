#include "greedy.h"

//Ordena los vertices de mayor a menor grado
void sort_adj(std::vector<int> &lista, Grafo g){
  int aux;
  for (unsigned int i = 0; i < lista.size(); i++){		
    for (unsigned int j = 0; j < lista.size()-1; j++){
      if ( g.grados[lista[j]] < g.grados[lista[j+1]] ){
        aux = lista[j];
	      lista[j] = lista[j+1];				
	      lista[j+1] = aux;
      }			
    }
  }
}

MCS goloso (Grafo g1, std::vector<int> &vertices1, 
         Grafo g2, std::vector<int> &vertices2) {

  MCS solucion;
  solucion.aristas = 0;

  sort_adj(vertices1, g1);
  sort_adj(vertices2, g2);

  solucion.isomorfismo.push_back(make_pair(vertices1[0], vertices2[0]));

  vertices1 = copiar_sin(vertices1, vertices1[0]);
  vertices2 = copiar_sin(vertices2, vertices2[0]);

  while ( vertices1.size() != 0){
    pair<int, int> par_mayor_deg = make_pair(vertices1[0], vertices2[0]);
  	for (const int u : vertices1) {
      for (const int v : vertices2) {
        Isomorfismo nuevo_iso = solucion.isomorfismo;
        nuevo_iso.push_back(make_pair(u, v));
        int aristas = contar_aristas_isomorfismo(g1, g2, nuevo_iso);
        if ( aristas > solucion.aristas){
          solucion.aristas = aristas;
          par_mayor_deg = make_pair(u,v);
        }
      }
  	}
  	solucion.isomorfismo.push_back(par_mayor_deg);
  	vertices1 = copiar_sin(vertices1,par_mayor_deg.first);
  	vertices2 = copiar_sin(vertices2,par_mayor_deg.second);
  }

  return solucion;
}

std::vector<std::pair<int, int>> generar_isomorfismo(
  Grafo g1, Grafo g2, Isomorfismo iso) {
  std::vector<std::pair<int, int>> aristas;
  for (unsigned int i = 0; i < iso.size(); i++) {
      auto p = iso[i];
    for (unsigned int j = i + 1; j < iso.size(); j++) {
      auto q = iso[j];
      if (g1.adj_matrix[p.first][q.first] && 
          g2.adj_matrix[p.second][q.second]) {
        aristas.push_back(std::make_pair(i, j));
      }
    }
  }
  return aristas;
}

