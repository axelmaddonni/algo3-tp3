#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <algorithm> // min

using std::cin;
using std::cout;
using std::pair;
using std::vector;
using std::map;
using std::queue;
using std::set;

// Funciones generales para grafos definidos con adj_list representada como map

struct Grafo_adjlist {
	int n;
	int m;
	map<int, vector<int>> adj_list;
};

vector<int> nodosIds (const Grafo_adjlist& g);
Grafo_adjlist subgrafoInducido(Grafo_adjlist g, vector<int> nodos);
vector<vector<int> > obtenerComponentesCografo(const Grafo_adjlist& g, bool esJoin);
vector<int> adyacentes (Grafo_adjlist g, int s);
vector<int> noAdyacentes (Grafo_adjlist g, int s);
int nodoNoVisitado(map<int, bool> visited);
vector<int> unirNodos (const vector<int> nodosIzq, const vector<int> nodosDer);
void imprimirGrafo(Grafo_adjlist g);
void imprimirSolucion(Grafo_adjlist g); // Dado un MCS imprime la solución dado el formato de salida


class CographTree {
public:
	CographTree();
	CographTree(const Grafo_adjlist& g); // construye un cografo a partir de un Grafo_adjlist
	CographTree(int size, int nodoInicial); // construye un cografo aleatorio
	// ~CographTree();
	
	bool esUnion() const { return tipo == uniondisjunta; };
	bool esJoin() const { return tipo == join; };
	bool esTrivial() const { return tipo == trivial; }
	CographTree* izquierdo() const { return izq; };
	CographTree* derecho() const { return der; };
	int size() const { return n; };
	int aristas() const { return m; };

	vector<int> nodosIdsCografo() const { return nodos; };
	vector<pair<int,int> > getAristas() const;
	Grafo_adjlist representacionGrafo() const; 

	vector<int> nodosMCS(int tamGrafoCompleto); // devuelve el conjunto de nodos del MCS entre el cografo y un Kn de tamaño tamGrafoCompleto
	// Nota: Para reducir la complejidad, para no calcular la representacionGrafo del cografo, se devuelven solo los nodos. (VER MAIN)

	Grafo_adjlist mcs(int tamGrafoCompleto);

	enum TipoCografo { uniondisjunta, join, trivial };

private:
	TipoCografo tipo;
	CographTree* izq;
	CographTree* der;
	int n;
	int m;
	vector<int> nodos;

	typedef pair<int, vector<int> > Solucion;
	// Solucion corresponde a una tupla de:
	//		< 	int: Cantidad de aristas de la solucion,
	//			vector<int>: Nodos correspondientes a la Solucion 	>
	vector< pair<bool, Solucion> > sol; // vector de soluciones de tamaño n+1


	Solucion mcs_Sol (int cantNodos, int tamGrafoCompleto);
};

CographTree::CographTree(const Grafo_adjlist& g){
	n = g.n;
	m = g.m;
	nodos = nodosIds(g);
	sol = vector< pair<bool, Solucion> >(n+1);
	for (auto isol: sol) {
		isol.first = false;
	}
	vector<vector<int> > componentes = obtenerComponentesCografo(g, false);
	if (componentes.size() == 2) {
		// esUnion
		tipo = uniondisjunta;
		izq = new CographTree(subgrafoInducido(g, componentes[0]));
		der = new CographTree(subgrafoInducido(g, componentes[1]));
	} else {
		if (componentes[0].size() == 1) {
			// esTrivial
			tipo = trivial;
			izq = NULL;
			der = NULL;
		} else {
			tipo = join;
			vector<vector<int> > componentesJoin = obtenerComponentesCografo(g, true);
			izq = new CographTree(subgrafoInducido(g, componentesJoin[0]));
			der = new CographTree(subgrafoInducido(g, componentesJoin[1]));
		}
	}
}


CographTree::CographTree(int size, int nodoInicial) {
	n = size;

	nodos = vector<int>();
	for (int i = nodoInicial; i < nodoInicial + size; ++i)	{
		nodos.push_back(i);
	}

	sol = vector< pair<bool, Solucion> >(n+1);
	for (auto isol: sol) {
		isol.first = false;
	}

	if (size == 1) {
		tipo = trivial;
		izq = NULL;
		der = NULL;
		m = 0;
	} else {
		int nodosIzq = (rand() % (n-1)) + 1;
		int nodosDer = n - nodosIzq;

		izq = new CographTree(nodosIzq, nodoInicial);
		der = new CographTree(nodosDer, nodoInicial + nodosIzq);

		int trand = rand() % 2;
		if (trand == 0){
			tipo = uniondisjunta;
			m = izq->aristas() + der->aristas();
		} else {
			tipo = join;
			m = izq->aristas() + der->aristas() + (nodosIzq * nodosDer);
		}
	}	
}

Grafo_adjlist CographTree::representacionGrafo() const {
	Grafo_adjlist g;
	g.n = n;
	g.m = m;

	map<int, vector<int>> adj_list;
	for (int nodo: nodos){
		adj_list.insert(pair<int, vector<int>>(nodo, vector<int>() ));
	}

	for (auto arista: getAristas()){
		adj_list[arista.first].push_back(arista.second);
		adj_list[arista.second].push_back(arista.first);
	}
	g.adj_list = adj_list;

	return g;
}

vector<pair<int,int>> CographTree::getAristas() const {
	vector<pair<int,int>> aristas;

	if (tipo != trivial){
		vector<pair<int,int>> aristasIzq = izq->getAristas();
		vector<pair<int,int>> aristasDer = der->getAristas();
		for (auto a: aristasIzq) {
			aristas.push_back(a);
		}
		for (auto a: aristasDer) {
			aristas.push_back(a);
		}
		if (tipo == join){
			for (int nizq: izq->nodosIdsCografo()){
				for (int nder: der->nodosIdsCografo()){
					aristas.push_back(pair<int,int>(nizq,nder));
				}
			}
		}
	}
	return aristas;
}

vector<int> CographTree::nodosMCS(int tamGrafoCompleto) {
	Solucion sol = mcs_Sol(std::min(n, tamGrafoCompleto), tamGrafoCompleto);

	return sol.second;
}

Grafo_adjlist CographTree::mcs(int tamGrafoCompleto) {
	return subgrafoInducido(representacionGrafo(), nodosMCS(tamGrafoCompleto));
}

CographTree::Solucion CographTree::mcs_Sol (int cantNodos, int tamGrafoCompleto) { 
	if (cantNodos > n){
		return mcs_Sol(n, tamGrafoCompleto);

	} else {
		int cantAristasSol;
		vector<int> nodosSol;

		if (cantNodos == 0) {
			cantAristasSol = 0;

		} else if ( sol[cantNodos].first ) {
			return sol[cantNodos].second;

		} else if (cantNodos == 1) {
			cantAristasSol = 0;
			nodosSol.push_back(nodos[0]); // devuelvo cualquiera?

		} else if (n <= tamGrafoCompleto && cantNodos == n) {
			cantAristasSol = m;
			nodosSol = nodos;

		} else if (tipo == trivial)	{
			cantAristasSol = 0;
			nodosSol.push_back(nodos[0]);

		} else  { 	// tipo == join o union
			int maxAristas = 0 ;
			vector<int> nodosSolIzq;
			vector<int> nodosSolDer;
			for (int i = 0; i <= cantNodos; i++) {
				Solucion solIzq = izq->mcs_Sol(i, tamGrafoCompleto);
				Solucion solDer = der->mcs_Sol(cantNodos-i, tamGrafoCompleto);
				int aristas = solIzq.first + solDer.first;
				if (tipo == join) { aristas += solIzq.second.size() * solDer.second.size(); }
				if (aristas > maxAristas) {
					maxAristas = aristas;
					nodosSolIzq = solIzq.second;
					nodosSolDer = solDer.second;
				}
			}
			cantAristasSol = maxAristas;
			if (cantAristasSol == 0){
				for (int i = 0; i < cantNodos; ++i) {
					nodosSol.push_back(nodos[i]);
				}
			} else {
				nodosSol = unirNodos(nodosSolIzq, nodosSolDer);
			}

		} 
		Solucion s (cantAristasSol, nodosSol);
		(sol[cantNodos]).first = true;
		(sol[cantNodos]).second = s;
		
		// FOR DEBUGGING
		// cout << "nodos: ";
		// for (int n: nodos){
		// 	cout << n << " ";
		// }
		// cout << "cantNodos: " << cantNodos << " tamGrafoCompleto: " << tamGrafoCompleto;
		// cout << std::endl;
		// cout << "sol: " << cantAristasSol << std::endl;
		// cout << "nodosSol: " ;
		// for (int n:nodosSol){
		// 	cout << n << " ";
		// }
		// cout << std::endl;

		return s;

	}
}

// Funciones generales para grafos

vector<int> nodosIds (const Grafo_adjlist& g) {
	vector<int> ids;
	for(auto imap: g.adj_list) {
		ids.push_back(imap.first);
	}
	return ids;
}

vector<int> unirNodos (const vector<int> nodosIzq, const vector<int> nodosDer) {
	vector<int> res(nodosIzq.size() + nodosDer.size());
	std::merge(nodosIzq.begin(), nodosIzq.end(), nodosDer.begin(), nodosDer.end(), res.begin());
	return res;
}


Grafo_adjlist subgrafoInducido(Grafo_adjlist g, vector<int> nodos) {
	Grafo_adjlist s;
	s.n = nodos.size();
	int m = 0;
	map<int, vector<int>> adj_list;
	for (int n: nodos){
		vector<int> nuevosAdyacentes;
		for (int ady: g.adj_list[n]) {
			if ( std::find(nodos.begin(), nodos.end(), ady) != nodos.end() ) {
				nuevosAdyacentes.push_back(ady);
			}
		}
		m += nuevosAdyacentes.size();
		adj_list.insert(pair<int, vector<int> >(n, nuevosAdyacentes));
	}
	s.m = m / 2;
	s.adj_list = adj_list;
	return s;
}

// obtenerComponentesCografo : devuelve una componente en caso que sea conexo, sino devuelve dos componentes disconexas
//	En caso de que esJoin == true, devuelve las dos componentes del join
vector<vector<int> > obtenerComponentesCografo(const Grafo_adjlist& g, bool esJoin) {

	map<int, bool> visited = map<int,bool>();
	for (int nodo: nodosIds(g)) {
		visited.insert( pair<int, bool>(nodo, false) );
	}

	queue<int> queue;
	vector<vector<int> > componentes;

	int s = nodoNoVisitado(visited);
	visited[s] = true;
	queue.push(s);

	vector<int> componente;

	while(!queue.empty()) {
		s = queue.front();
		componente.push_back(s);
		queue.pop();
		
		vector<int> nodosMarcar;
		if (!esJoin){
			nodosMarcar = adyacentes(g, s);
		} else {
			nodosMarcar = noAdyacentes(g, s);
		}

		for (int nodo: nodosMarcar) {
			if(!visited[nodo]) {
				visited[nodo] = true;
				queue.push(nodo);
			}
		}
	}

	componentes.push_back(componente);

	if (componente.size() != (unsigned int)g.n) {
		vector<int> componente2;
		for(int nodo: nodosIds(g)) {
			if ( std::find(componente.begin(), componente.end(), nodo) == componente.end() ) {
				componente2.push_back(nodo);
			}
		}
		componentes.push_back(componente2);
	}

	return componentes;
}

int nodoNoVisitado(map<int, bool> visited) {
	for(auto imap: visited) {
		if (!imap.second) return imap.first;
	}
	return -1;
}

vector<int> adyacentes (Grafo_adjlist g, int s) {
	return g.adj_list[s];
}

vector<int> noAdyacentes (Grafo_adjlist g, int s) {
	vector<int> noAdyacentes;
	for (int n: nodosIds(g)) {
		bool found = false;
		for (int ady: adyacentes(g, s)) {
			if (ady == n) {
				found = 1;
				break;
			} 
		}
		if (!found) noAdyacentes.push_back(n);
	}
	return noAdyacentes;
}

void imprimirGrafo(Grafo_adjlist g) {
	cout << g.n << " " << g.m << std::endl;

	set<int> impresos;
	for (auto imap: g.adj_list) {
		for (int ady: g.adj_list[imap.first]) {
			if (impresos.count(ady) == 0)
				cout << imap.first << " " << ady << std::endl; 
		}
		impresos.insert(imap.first);
	}
}

void imprimirSolucion(Grafo_adjlist g) {
	cout << g.n << " " << g.m << std::endl;

	map<int, int> isomorfismo; // < valor del nodo en G, valor del nodo en MCS >

	// Imprimo isomorfismo con G
	for (unsigned int i = 0; i < nodosIds(g).size(); ++i) {
		cout << nodosIds(g)[i];	
		isomorfismo.insert(pair<int,int>(nodosIds(g)[i], i+1));
		if ( i != nodosIds(g).size()-1 ) {
			cout << " ";
		} else {
			cout << std::endl;
		}
	}

	// Imprimo cualquier isomorfismo porque es un Grafo_adjlist completo
	for (int i = 1; i <= g.n; ++i) {
		cout << i;
		if ( i != g.n ) {
			cout << " ";
		} else {
			cout << std::endl;
		}
	}

	// Imprimo aristas del MCS
	set<int> impresos;
	for (auto imap: g.adj_list) {
		for (int ady: g.adj_list[imap.first]) {
			if (impresos.count(ady) == 0)
				cout << isomorfismo[imap.first] << " " << isomorfismo[ady] << std::endl; 
		}
		impresos.insert(imap.first);
	}
}
