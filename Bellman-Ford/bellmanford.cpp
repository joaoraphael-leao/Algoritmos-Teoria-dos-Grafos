#include <iostream>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <limits>
using namespace std;

const char TEXTO_DE_AJUDA[] =
    "Uso: <nome_do_programa> [opções] <arquivo>\n"
    "Este programa calcula o caminho mínimo em um grafo usando o algoritmo de Bellman-Ford.\n\n"
    "Opções:\n"
    "  -o <arquivo>: especifica o arquivo de saída\n"
    "  -f <arquivo>: especifica o arquivo de entrada que contém o grafo\n"
    "  -i <vértice>: especifica o vértice inicial\n"
    "  -h: exibe esta ajuda\n";


typedef struct aresta_grafo 
{
    int u;
    int v;
    int w;
} aresta_grafo;

void bellmanFord (vector<aresta_grafo> &arestas, vector<int> &distancia, int n, int inicial) 
{
    int i, u, v, w;

    distancia[inicial] = 0;

    for (i = 0; i < n; i++) 
    {
        for (const auto &aresta : arestas) 
        {
            u = aresta.u;
            v = aresta.v;
            w = aresta.w;

            if (distancia[u] != numeric_limits<int>::max() && distancia[u] + w < distancia[v])
            {
                distancia[v] = distancia[u] + w;
            }
        }
    }

    for (const auto &aresta : arestas) 
    {
        u = aresta.u;
        v = aresta.v;
        w = aresta.w;

        if (distancia[u] != numeric_limits<int>::max() && distancia[u] + w < distancia[v]) 
        {
            cerr << "The graph has a negative weight cycle!" << endl;
            return;
        }
    }
}

int main(int argc, char *argv[]) 
{
    string nomearquivo_entrada;
    string nomearquivo_saida;
    int option;
    int inicial;
    int fluxo_saida;
    int n, m, u, v, w;

    inicial = 0; 
    fluxo_saida = 0;

    while ((option = getopt(argc, argv, "ho:i:f:")) != -1) 
    {
        switch (option) 
        {
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
            case 'i':
                inicial = stoi(optarg) - 1;
                break;
            default:
                cerr << "Unknown flag! Use -h for help instead." << endl;
                return 1;
        }
    }

    ifstream arquivo_entrada(nomearquivo_entrada);

    if (!arquivo_entrada.is_open()) 
    {
        cerr << "Unable to open input file" << endl;

        return 1;
    }

    bool grafo_direcionado = false;

    arquivo_entrada >> n >> m;

    if(m < 0)
    {
        grafo_direcionado = true;
        m = (-1 * m);
    }

    vector<aresta_grafo> arestas;

    for (int i = 0; i < m; i++) 
    {
        arquivo_entrada >> u >> v >> w;

        if(grafo_direcionado) arestas.push_back({u - 1, v - 1, w});
        else
        {
            arestas.push_back({u - 1, v - 1, w});
            arestas.push_back({v - 1, u - 1, w});
        }
    }

    vector<int> distancia(n, numeric_limits<int>::max());

    bellmanFord(arestas, distancia, n, inicial);

    for (size_t i = 0; i < distancia.size(); ++i) 
    {
        cout << i + 1 << ":" << distancia[i] << " ";
    }

    if (fluxo_saida) 
    {
        ofstream output_file(nomearquivo_saida, ios::out);

        if (output_file.is_open()) 
        {
            for (size_t i = 0; i < distancia.size(); ++i) 
            {
                output_file << i + 1 << ":" << distancia[i] << " ";
            }
        } 
        else 
        {
            cerr << "Unable to open output file" << endl;
            return 1;
        }
    }

    arquivo_entrada.close();
    
    return 0;
}
