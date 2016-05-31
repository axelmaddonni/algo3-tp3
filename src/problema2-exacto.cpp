#include <iostream>
#include <vector>
#include <utility> 

struct Grafo {
  int n;
  int m;
  std::vector<std::vector<int>> adj_list;
};

typedef std::vector<std::pair<int, int>> Isomorfismo;

struct {
  Isomorfismo isomorfismo;
  int aristas;
} solucion;

std::vector<int> copiar_sin(std::vector<int> v, int x) {
  std::vector<int> v_copia;
  for (const auto y : v) {
    if (y != x) {
      v_copia.push_back(y);
    }
  }
  return v_copia;
}


bool lin_search(std::vector<int> v, int x) {
  for (const auto y : v) {
    if (x == y) {
      return true;
    }
  }
  return false;
}

int contar_aristas_isomorfismo(Grafo g1, Grafo g2, Isomorfismo iso) {
  int aristas = 0;
  for (const auto p : iso) {
    for (const auto q : iso) {
      int vg1 = p.first;
      int vg2 = p.second;
      int ug1 = q.first;
      int ug2 = q.second;

      if (lin_search(g1.adj_list[vg1], ug1) && // ug1 y vg1 estan conectados.
          lin_search(g2.adj_list[vg2], ug2)) { // ug2 y vg2 estan conectados.
        aristas++;
      }
    }
  }

  return aristas / 2; // conte todas 2 veces;
}


inline bool ordenado_asc(const Isomorfismo& iso) {
  if (iso.size() < 2) {
    return true;
  }
  for (unsigned int i = 1; i < iso.size(); i++) {
    if (iso[i-1].first >= iso[i].first) {
      return false;
    }
  }
  return true;
}

void bt (Grafo g1, std::vector<int> vertices1, 
         Grafo g2, std::vector<int> vertices2,
         Isomorfismo iso) {
  if (!ordenado_asc(iso)) {
    // Si iso = [(a0,b0), (a1,b1), ..., (an,bn)] y [a0, ..., an] no esta ordenado
    // ascendientemente, podemos considerar el reordenamiento
    //      [(a'0,b'0), (a'1,b'1), ..., (a'n,b'n)]
    // que es el mismo que antes solo que ahora a'0 < a'1 < ... < a'n. De esta
    // manera, nos ahorramos considerar el mismo isomorfismos varias veces, y
    // analizando solo la version en la que la primera coordenada esta ordenada
    // ascendientemente.
    return;
  }
  int aristas = contar_aristas_isomorfismo(g1, g2, iso);
  if (aristas > solucion.aristas) {
    solucion.isomorfismo = iso;
    solucion.aristas = aristas;
  }

  for (const int u : vertices1) {
    for (const int v : vertices2) {
      Isomorfismo nuevo_iso = iso;
      nuevo_iso.push_back(std::make_pair(u, v));
      bt(g1, copiar_sin(vertices1, u),
         g2, copiar_sin(vertices2, v),
         nuevo_iso);
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
      if (lin_search(g1.adj_list[p.first], q.first) && 
          lin_search(g2.adj_list[p.second], q.second)) {
        aristas.push_back(std::make_pair(i, j));
      }
    }
  }
  return aristas;
}


int main() {
  Grafo g1, g2;

  std::cin >> g1.n >> g1.m >> g2.n >> g2.m;
  g1.adj_list.resize(g1.n);
  g2.adj_list.resize(g2.n);
  for (int i = 0; i < g1.m; i++) {
    int u, v;
    std::cin >> u >> v;
    g1.adj_list[u].push_back(v);
    g1.adj_list[v].push_back(u);
  }
  for (int i = 0; i < g2.m; i++) {
    int u, v;
    std::cin >> u >> v;
    g2.adj_list[u].push_back(v);
    g2.adj_list[v].push_back(u);
  }

  std::vector<int> vertices1, vertices2;
  for (int i = 0; i < g1.n; i++) {
    vertices1.push_back(i);
  }
  for (int i = 0; i < g2.n; i++) {
    vertices2.push_back(i);
  }

  solucion.aristas = 0;
  if (g1.n < g2.n) {
    bt(g1, vertices1, g2, vertices2, Isomorfismo());
  } else {
    bt(g2, vertices2, g1, vertices1, Isomorfismo());
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


