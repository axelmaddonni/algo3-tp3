#include <iostream>
#include <vector>
#include <utility> 
#include "utilidades.h"

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

void bt (Grafo g1, std::vector<int> vertices1, 
         Grafo g2, std::vector<int> vertices2,
         Isomorfismo iso, int n_iteracion) {
  int aristas = contar_aristas_isomorfismo(g1, g2, iso);
  int parada = 6; 
  if (aristas == -1 || n_iteracion > parada) {
    return;
  } else if (aristas > solucion.aristas) {
    solucion.isomorfismo = iso;
    solucion.aristas = aristas;
  }
  for (const int u : vertices1) {
    for (const int v : vertices2) {
      n_iteracion++;
      Isomorfismo nuevo_iso = iso;
      nuevo_iso.push_back(std::make_pair(u, v));
      bt(g1, copiar_sin(vertices1, u),
         g2, copiar_sin(vertices2, v),
         nuevo_iso, n_iteracion);
    }
  }
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

  sort_adj(vertices1, g1);
  sort_adj(vertices2, g2);

  solucion.aristas = 0;
  if (g1.n < g2.n) {
    bt(g1, vertices1, g2, vertices2, Isomorfismo(), 0);
  } else {
    bt(g2, vertices2, g1, vertices1, Isomorfismo(), 0);
  }

  std::vector<std::pair<int, int>> aristas = 
    generar_isomorfismo(g1, g2, solucion.isomorfismo);

  std::cout << solucion.isomorfismo.size() << " " << aristas.size() << std::endl;
  for (const auto p : solucion.isomorfismo) {
    std::cout << p.first << " ";
  }
  std::cout << std::endl;
  for (const auto p : solucion.isomorfismo) {
    std::cout << p.second << " ";
  }
  std::cout << std::endl;
  for (const auto p : aristas) {
    std::cout << p.first << " " << p.second << std::endl;
  }
}
