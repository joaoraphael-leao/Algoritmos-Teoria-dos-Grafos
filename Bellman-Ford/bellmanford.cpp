#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <unistd.h>
using namespace std;

const char TEXTO_DE_AJUDA[] =
    "Uso: <nome_do_programa> [opções] <arquivo>\n"
    "Este programa calcula o caminho mínimo em um grafo usando o algoritmo de Bellman-Ford.\n\n"
    "Opções:\n"
    "  -o <arquivo>: especifica o arquivo de saída\n"
    "  -f <arquivo>: especifica o arquivo de entrada que contém o grafo\n"
    "  -i <vértice>: especifica o vértice inicial\n"
    "  -h: exibe esta ajuda\n";

struct aresta_grafo {
    int u, v, w;
};

void bellmanFord(const vector<aresta_grafo>& arestas, vector<int>& distancia, int n, int inicial) {
    distancia[inicial] = 0;
    bool atualizou = false;

    for (int i = 0; i < n - 1; i++) {
        atualizou = false;
        for (const auto& aresta_grafo : arestas) {
            if (distancia[aresta_grafo.u] != numeric_limits<int>::max() && 
                distancia[aresta_grafo.u] + aresta_grafo.w < distancia[aresta_grafo.v]) {
                distancia[aresta_grafo.v] = distancia[aresta_grafo.u] + aresta_grafo.w;
                atualizou = true;
            }
        }
        if (!atualizou) break;
    }

    for (const auto& aresta_grafo : arestas) {
        if (distancia[aresta_grafo.u] != numeric_limits<int>::max() && 
            distancia[aresta_grafo.u] + aresta_grafo.w < distancia[aresta_grafo.v]) {
            cerr << "Esse grafo possui um ciclo de peso negativo!" << endl;
            return;
        }
    }
}

int main(int argc, char *argv[]) 
{
    string nomearquivo_entrada, nomearquivo_saida;
    int inicial = 0;
    int option;

    while ((option = getopt(argc, argv, "ho:i:f:")) != -1) {
        switch (option) {
            case 'h':
                cout << TEXTO_DE_AJUDA;
                return 0;
            case 'o':
                nomearquivo_saida = optarg;
                break;
            case 'f':
                nomearquivo_entrada = optarg;
                break;
            case 'i':
                inicial = stoi(optarg) - 1;
                break;
            default:
                cerr << "Opção desconhecida! Use -h para ajuda." << endl;
                return 1;
        }
    }

    ifstream arquivo_entrada(nomearquivo_entrada);
    if (!arquivo_entrada.is_open()) {
        cerr << "Não foi possível abrir o arquivo de entrada" << endl;
        return 1;
    }

    int n, m;
    arquivo_entrada >> n >> m;
    vector<aresta_grafo> arestas(m);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        arquivo_entrada >> u >> v >> w;
        arestas[i] = {u - 1, v - 1, w};
    }

    vector<int> distancia(n, numeric_limits<int>::max());
    bellmanFord(arestas, distancia, n, inicial);

    if (nomearquivo_saida.empty()) {
        for (int i = 0; i < n; i++) {
            if (i > 0) cout << ", ";
            cout << (i + 1) << ":";
            if (distancia[i] == numeric_limits<int>::max())
                cout << "infinito";
            else
                cout << distancia[i];
        }
        cout << endl;
    } else {
        ofstream arquivo_saida(nomearquivo_saida);
        if (arquivo_saida.is_open()) {
            for (int i = 0; i < n; i++) {
                if (i > 0) arquivo_saida << ", ";
                arquivo_saida << (i + 1) << ":";
                if (distancia[i] == numeric_limits<int>::max())
                    arquivo_saida << "infinito";
                else
                    arquivo_saida << distancia[i];
            }
            arquivo_saida << endl;
        } else {
            cerr << "Não foi possível abrir o arquivo de saída" << endl;
            return 1;
        }
    }

    return 0;
}