#include <iostream>
#include <vector>
#include <utility> 
#include "utilidades.h"

MCS solucion;

//Devuelve el nodo de grado máximo
int nodo_max_grado(std::vector<int> lista, Grafo g){
  int max = lista[0];
  for (unsigned int i = 1; i < lista.size(); i++){	
   	if ( g.grados[max] < g.grados[lista[i]] ){
  	  max = lista[i];
    }				
  }
  return max;
}

void goloso (Grafo g1, std::vector<int> &vertices1, 
         Grafo g2, std::vector<int> &vertices2) {

  Isomorfismo iso;
  int max1 = nodo_max_grado(vertices1, g1);
  int max2 = nodo_max_grado(vertices2, g2);

  iso.push_back(std::make_pair(max1, max2));

  vertices1 = copiar_sin(vertices1, max1);
  vertices2 = copiar_sin(vertices2, max2);

  while ( vertices1.size() != 0){
    std::pair<int, int> par_mayor_deg = std::make_pair(vertices1[0], vertices2[0]);
  	for (const int u : vertices1) {
      for (const int v : vertices2) {
        Isomorfismo nuevo_iso = iso;
        nuevo_iso.push_back(std::make_pair(u, v));
        int aristas = contar_aristas_isomorfismo(g1, g2, nuevo_iso);
        if ( aristas > solucion.aristas){
          solucion.aristas = aristas;
          par_mayor_deg = std::make_pair(u,v);
        }
      }
  	}
  	iso.push_back(par_mayor_deg);
  	vertices1 = copiar_sin(vertices1,par_mayor_deg.first);
  	vertices2 = copiar_sin(vertices2,par_mayor_deg.second);
  }

  solucion.isomorfismo = iso;
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


int main() {
  Grafo g1, g2;

  std::cin >> g1.n >> g1.m >> g2.n >> g2.m;

  g1.adj_matrix = vector<vector<bool>>(g1.n, vector<bool>(g1.n, false));
  g2.adj_matrix = vector<vector<bool>>(g2.n, vector<bool>(g2.n, false));
  g1.grados = vector<int>(g1.n, 0);
  g2.grados = vector<int>(g2.n, 0);
  for (int i = 0; i < g1.m; i++) {
    int u, v;
    std::cin >> u >> v;
    g1.adj_matrix[u][v] = true;
    g1.adj_matrix[v][u] = true;
    g1.grados[u]++;
    g1.grados[v]++;
  }
  for (int i = 0; i < g2.m; i++) {
    int u, v;
    std::cin >> u >> v;
    g2.adj_matrix[u][v] = true;
    g2.adj_matrix[v][u] = true;
    g2.grados[u]++;
    g2.grados[v]++;
  }

  std::vector<int> vertices1, vertices2;
  for (int i = 0; i < g1.n; i++) {
    vertices1.push_back(i);
  }
  for (int i = 0; i < g2.n; i++) {
    vertices2.push_back(i);
  }

  solucion.aristas = 0;
  bool inverso;
  if (g1.n < g2.n) {
    goloso(g1, vertices1, g2, vertices2);
    inverso = false;
  } else {
    goloso(g2, vertices2, g1, vertices1);
    inverso = true;
  }

  std::vector<std::pair<int, int>> aristas = 
    generar_isomorfismo(g1, g2, solucion.isomorfismo);
    cout << "llegue" << endl;

  std::cout << solucion.isomorfismo.size() << " " << aristas.size() << std::endl;
  for (const auto p : solucion.isomorfismo) {
    if(!inverso) std::cout << p.first << " ";
    else std::cout << p.second << " ";
  }
  std::cout << std::endl;
  for (const auto p : solucion.isomorfismo) {
    if(!inverso) std::cout << p.second << " ";
    else std::cout << p.first << " ";
  }
  std::cout << std::endl;
  for (const auto p : aristas) {
    std::cout << p.first << " " << p.second << std::endl;
  }
}
