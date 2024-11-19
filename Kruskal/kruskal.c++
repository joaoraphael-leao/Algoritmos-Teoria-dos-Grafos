#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <getopt.h>
#include <utility>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const char TEXTO_DE_AJUDA[] =
    "Uso: <nome_do_programa> [opções] <arquivo>\n"
    "Este programa calcula a árvore geradora mínima de um grafo usando o algoritmo de Kruskal.\n\n"
    "Opções:\n"
    "  -o <arquivo>:  redireciona a saida para o ‘‘arquivo’’\n"
    "  -f <arquivo>:  indica o ‘‘arquivo’’ que contém o grafo de entrada\n"
    "  -s: mostra a solução\n"
    "  -h: mostra o help\n";

class UnionFind {
private:
    vector<int> parent, rank;

public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int findSet(int i) {
        if (parent[i] != i) {
            parent[i] = findSet(parent[i]);
        }
        return parent[i];
    }

    bool isSameSet(int i, int j) {
        return findSet(i) == findSet(j);
    }

    void unionSet(int i, int j) {
        int x = findSet(i);
        int y = findSet(j);
        if (x != y) {
            if (rank[x] > rank[y]) {
                parent[y] = x;
            } else {
                parent[x] = y;
                if (rank[x] == rank[y]) {
                    rank[y]++;
                }
            }
        }
    }
};

int main(int argc, char *argv[]) {
    int option;
    string nomearquivo_saida, nomearquivo_entrada;
    int fluxo_saida = 0, solucao = 0;

    while ((option = getopt(argc, argv, "hso:f:")) != -1) {
        switch (option) {
            case 'h':
                cout << TEXTO_DE_AJUDA;
                return 0;
            case 'o':
                nomearquivo_saida = optarg;
                fluxo_saida = 1;
                break;
            case 'f':
                nomearquivo_entrada = optarg;
                break;
            case 's':
                solucao = 1;
                break;
            default:
                cerr << "Unknown flag! Use -h for help instead." << endl;
                return 1;
        }
    }

    ifstream arquivo_entrada(nomearquivo_entrada);
    if (!arquivo_entrada.is_open()) {
        cerr << "Erro ao abrir o arquivo de entrada." << endl;
        return 1;
    }

    int n, m;
    arquivo_entrada >> n >> m;

    vector<pair<ll, ii>> edgeList;
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        arquivo_entrada >> u >> v >> w;
        edgeList.push_back({w, {u - 1, v - 1}});
    }
    arquivo_entrada.close();

    sort(edgeList.begin(), edgeList.end());
    UnionFind UF(n);
    ll custo_total = 0;
    vector<ii> mst;

    for (const auto &edge : edgeList) {
        ll peso = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;
        if (!UF.isSameSet(u, v)) {
            custo_total += peso;
            mst.push_back({u, v});
            UF.unionSet(u, v);
        }
    }

    if (fluxo_saida) {
        ofstream output_file(nomearquivo_saida);
        if (!output_file.is_open()) {
            cerr << "Erro ao abrir o arquivo de saída." << endl;
            return 1;
        }
        if (solucao) {
            for (const auto &edge : mst) {
                output_file << "(" << edge.first + 1 << "," << edge.second + 1 << ") ";
            }
        } else {
            output_file << custo_total << endl;
        }
    }

    if (solucao) {
        for (const auto &edge : mst) {
            cout << "(" << edge.first + 1 << "," << edge.second + 1 << ") ";
        }
    } else {
        cout << custo_total << endl;
    }

    return 0;
}
