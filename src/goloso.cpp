#include "greedy.h"

//Ordena los vertices de mayor a menor grado
void sort_adj(std::vector<int> &lista, Grafo g){
  for (unsigned int i = 1; i < lista.size(); i++){		
    int v = lista[i];
    int j = i - 1;
    while(j >= 0 && g.grados[v] > g.grados[lista[j]]) {
      lista[j + 1] = lista[j];
      j--; 		
    }
    lista[j+1] = v;
  }
}

// MCS goloso (Grafo g1, std::vector<int> &vertices1, 
//          Grafo g2, std::vector<int> &vertices2) {

//   MCS solucion;
//   solucion.aristas = 0;

//   sort_adj(vertices1, g1);
//   sort_adj(vertices2, g2);

//   solucion.isomorfismo.push_back(make_pair(vertices1[0], vertices2[0]));

//   vertices1 = copiar_sin(vertices1, vertices1[0]);
//   vertices2 = copiar_sin(vertices2, vertices2[0]);

//   while ( vertices1.size() != 0){
//     pair<int, int> par_mayor_deg = make_pair(vertices1[0], vertices2[0]);
//   	for (const int u : vertices1) {
//       for (const int v : vertices2) {
//         Isomorfismo nuevo_iso = solucion.isomorfismo;
//         nuevo_iso.push_back(make_pair(u, v));
//         int aristas = contar_aristas_isomorfismo(g1, g2, nuevo_iso);
//         if ( aristas > solucion.aristas){
//           solucion.aristas = aristas;
//           par_mayor_deg = make_pair(u,v);
//         }
//       }
//   	}
//   	solucion.isomorfismo.push_back(par_mayor_deg);
//   	vertices1 = copiar_sin(vertices1,par_mayor_deg.first);
//   	vertices2 = copiar_sin(vertices2,par_mayor_deg.second);
//   }

//   return solucion;
// }

MCS goloso (Grafo g1, std::vector<int> &vertices1, 
         Grafo g2, std::vector<int> &vertices2){

  sort_adj(vertices1, g1);
  sort_adj(vertices2, g2);

  MCS solucion;

  for (unsigned int i = 0; i < vertices1.size(); i++) {
      solucion.isomorfismo.push_back(std::make_pair(vertices1[i], vertices2[i]));
  }

  int aristas = contar_aristas_isomorfismo(g1, g2, solucion.isomorfismo);
  solucion.aristas = aristas;

  return solucion;
}


