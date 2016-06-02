#include "utilidades.h"
#include "greedy.h"
#include "localSearch.h"

int main(int argc, const char* argv[]) {
  //argv[1] = tipo de heuristica: GOLOSO, LOCAL o TABU
  //argv[2] = si argv[1] == LOCAL, es el vecindario
  string heuristica = argv[1];
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
  
  MCS solucion;
  bool inverso;
  if (heuristica == "GOLOSO") {
    if (g1.n < g2.n) {
      solucion = goloso(g1, vertices1, g2, vertices2);
      inverso = false;
    } else {
      solucion = goloso(g2, vertices2, g1, vertices1);
      inverso = true;
    }
  }
  else if (heuristica == "LOCAL") {
    Neighborhood nh = atoi(argv[2]);
    if (g1.n < g2.n) {
      solucion = local_search(g1, vertices1, g2, vertices2, nh);
      inverso = false;
    } else {
      solucion = local_search(g2, vertices2, g1, vertices1, nh);
      inverso = true;
    }
  }
  else if (heuristica == "TABU") {
    inverso = false;
  } 
  else {
    cout << "Opción inválida" << endl;
    return 0;
  }

  std::vector<std::pair<int, int>> aristas = 
    generar_isomorfismo(g1, g2, solucion.isomorfismo);

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

  return 0;
}