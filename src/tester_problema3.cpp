#include "problema3-cografos.h"

#include <assert.h>
#include <iostream>
#include <string>

#include "problema2-exacto.h"

using std::string;

int testearCorrectitudMCS(const CographTree& cografo, int tamGrafoCompleto, const Grafo_adjlist& mcs){
	solucion.aristas = 0;
	Grafo g1;
	Grafo g2;

	g1.n = cografo.size();
	g1.m = cografo.aristas();
	g1.adj_matrix = vector<vector<bool>>(g1.n, vector<bool>(g1.n, false));
	g1.grados = vector<int>(g1.n, 0);
	for (auto arista: cografo.getAristas()){
		g1.adj_matrix[arista.first-1][arista.second-1] = true;
		g1.adj_matrix[arista.second-1][arista.first-1] = true;
		g1.grados[arista.first-1]++;
		g1.grados[arista.second-1]++;
	}

	g2.n = tamGrafoCompleto;
	g2.m = g2.n * ((g2.n)-1) / 2;
	g2.adj_matrix = vector<vector<bool>>(g2.n, vector<bool>(g2.n, true));
	for (int i = 0; i < g2.n; ++i) {
		g2.adj_matrix[i][i] = false;
	}
	g2.grados = vector<int>(g2.n, (g2.n)-1);

	vector<int> vertices1, vertices2;
	for (int i = 0; i < g1.n; i++) {
	  vertices1.push_back(i);
	}
	for (int i = 0; i < g2.n; i++) {
	  vertices2.push_back(i);
	}

	if (g1.n < g2.n) {
	  bt(g1, vertices1, g2, vertices2, Isomorfismo());
	} else {
	  bt(g2, vertices2, g1, vertices1, Isomorfismo());
	}

	if (solucion.aristas == mcs.m) {
		return 1;
	} else {
		cout << "La sol era: " << solucion.aristas << endl;
		return 0;
	}
}

int main(int argc, char const *argv[]) {

	srand (time(NULL));

	string opt;
	if (argc >= 2) {
		opt = argv[1];
	}

	if ( argc < 2 || (opt.compare("correctitud") == 0) ){
		
		Grafo_adjlist g;
		int tamGrafoCompleto;
		int aristasGrafoCompleto;

		cin >> g.n >> g.m >> tamGrafoCompleto >> aristasGrafoCompleto ;

		for (int i = 1; i <= g.n; i++) {
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
	
		if (opt.compare("correctitud") == 0){
			int s = testearCorrectitudMCS(cografo, tamGrafoCompleto, mcs);

			if (s == 1) {
				cout << "Solucion correcta!" << endl;
			} else {
				cout << "Solucion INCORRECTA para grafo de entrada." << endl;
			}
		} else {
			imprimirSolucion(mcs);
		}

	} else if ( opt.compare("random") == 0  && argc == 4){

		int n = atoi(argv[2]);
		int tamGrafoCompleto = atoi(argv[3]);

		CographTree cografo(n, 1);

		Grafo_adjlist mcs = subgrafoInducido(cografo.representacionGrafo(), cografo.nodosMCS(tamGrafoCompleto));
	
		int s = testearCorrectitudMCS(cografo, tamGrafoCompleto, mcs);

		if (s == 1) {
			cout << "Solucion correcta!" << endl;
		} else {
			cout << "Solucion INCORRECTA para grafo de n = " << n << " y tamGrafoCompleto = " << tamGrafoCompleto << endl;
			cout << "Grafo de prueba que fallo: " << endl;
			imprimirGrafo(cografo.representacionGrafo());
		}

	} else if ( opt.compare("nrandom") == 0  && argc == 5){

		int cantCografos = atoi(argv[2]);
		int tamCografo = atoi(argv[3]);
		int cantGrafosCompletos = atoi(argv[4]);
		int solcorrectas = 0;
		int solincorrectas = 0;

		for (int n = 1; n <= cantCografos; n++){

			CographTree cografo(tamCografo, 1);

			std::vector<int> tamanos;
			for (int k = 1; k <= cantGrafosCompletos; k++){

				int t = (rand() % tamCografo+1) + 1;
				tamanos.push_back(t);

				for (int tamGrafoCompleto: tamanos){

					Grafo_adjlist mcs = subgrafoInducido(cografo.representacionGrafo(), cografo.nodosMCS(tamGrafoCompleto));

					int s = testearCorrectitudMCS(cografo, tamGrafoCompleto, mcs);
					if (s == 1){
						solcorrectas++;
						cout << "Solucion correcta! con n = " << tamCografo << " y tamGrafoCompleto = " << t << endl;
					} else {
						solincorrectas++;
						cout << "Sol INCORRECTA con n = " << tamCografo << " y tamGrafoCompleto = " << t << endl;
						cout << "Grafo de prueba que fallo: " << endl;
						imprimirGrafo(cografo.representacionGrafo());
					}
				}
			}
		}
		cout << "Soluciones correctas: " << solcorrectas << endl;
		cout << "Soluciones incorrectas: " << solincorrectas << endl;
	} else {
		cout << "ERROR EN LOS PARAMETROS. Modo de uso: " << endl;
		cout << " ./testerproblema3 (correctitud) < test.in" << endl;
		cout << " ./testerproblema3 random <tamCografo> <tamGrafoCompleto>" << endl;
		cout << " ./testerproblema3 nrandom <cantCografos> <tamCografo> <cantGrafosCompletos>" << endl;
	}
}
