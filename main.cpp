#include <iostream>
#include <vector>
#include <algorithm> 
#include <string.h> 
using namespace std;

class Aresta
{
	int vertice1, vertice2, peso;

public:

	Aresta(int v1, int v2, int peso)
	{
		vertice1 = v1;
		vertice2 = v2;
		this->peso = peso;
	}

	int obterVertice1()
	{
		return vertice1;
	}

	int obterVertice2()
	{
		return vertice2;
	}

	int obterPeso()
	{
		return peso;
	}

	// sobrescrita do operador "<"
	bool operator < (const Aresta& aresta2)
	{
		return (peso < aresta2.peso);
	}
};

class grafo
{
	int V; // número de vértices
	vector<Aresta> arestas; // vetor de arestas

public:

	grafo(int V)
	{
		this->V = V;
	}

	// função que adiciona uma aresta
	void novaAresta(int v1, int v2, int peso)
	{
		Aresta aresta(v1, v2, peso);
		arestas.push_back(aresta);
	}

	// função que busca o subconjunto de um elemento "i"
	int buscar(int subconj[], int i)
	{
		if(subconj[i] == -1)
			return i;
		return buscar(subconj, subconj[i]);
	}

	// função para unir dois subconjuntos em um único subconjunto
	void unir(int subconj[], int v1, int v2)
	{
		int v1_conj = buscar(subconj, v1);
		int v2_conj = buscar(subconj, v2);
		subconj[v1_conj] = v2_conj;
	}

	/// função que roda o algoritmo de Kruskal
	void kruskal()
	{
		vector<Aresta> arvore;
		int tam_arestas = arestas.size();

		// ordena as arestas pelo menor peso
		sort(arestas.begin(), arestas.end());

		// aloca memória para criar "V" subconjuntos
		int * subconj = new int[V];

		// inicializa todos os subconjuntos como conjuntos de um único elemento
		memset(subconj, -1,sizeof(int) * V);

		for(int i = 0; i <tam_arestas; i++)
		{
			int v1 = buscar(subconj, arestas[i].obterVertice1());
			int v2 = buscar(subconj, arestas[i].obterVertice2());

			if(v1 != v2)
			{
				// se forem diferentes é porque NÃO forma ciclo, insere no vetor
				arvore.push_back(arestas[i]);
				unir(subconj, v1, v2); // faz a união
			}
		}

		int tamanho_arvore = arvore.size();

		// mostra as arestas selecionadas com seus respectivos pesos
		for(int i = 0; i < tamanho_arvore; i++)
		{
			char vert1 = 'A' + arvore[i].obterVertice1();
			char vert2 = 'A' + arvore[i].obterVertice2();
			cout << "(" << vert1 << ", " << vert2 << ") de peso " << arvore[i].obterPeso() << endl;
		}
	}
};

int main()
{
	grafo g(13); // grafo
	
	// adiciona as arestas
g.novaAresta(0, 1, 10);
g.novaAresta(0, 2, 18);
g.novaAresta(0, 3, 12);
g.novaAresta(1, 2, 19);
g.novaAresta(1, 4, 39);
g.novaAresta(2, 3, 20);
g.novaAresta(2, 5, 4);
g.novaAresta(2, 6, 1);
g.novaAresta(2, 7, 2);
g.novaAresta(3, 8, 8);
g.novaAresta(4, 5, 10);
g.novaAresta(4, 9, 12);
g.novaAresta(5, 6, 1);
g.novaAresta(5, 10, 3);
g.novaAresta(6, 7, 7);
g.novaAresta(6, 10, 1);
g.novaAresta(7, 8, 7);
g.novaAresta(7, 10, 2);
g.novaAresta(8, 11, 20);
g.novaAresta(9, 10, 9);
g.novaAresta(9, 12, 13);
g.novaAresta(10, 11, 10);
g.novaAresta(10, 12, 15);
g.novaAresta(11, 12, 14);
g.kruskal(); // roda o algoritmo de Kruskal
	
	return 0;
}