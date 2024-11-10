//Prim
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <limits>
#include <queue>
#include <bits/stdc++.h>
#include <functional>
using namespace std;

const char TEXTO_DE_AJUDA[] =
    "Uso: <nome_do_programa> [opções] <arquivo>\n"
    "Este programa calcula a árvore geradora mínima de um grafo usando o algoritmo de Prim.\n\n"
    "Opções:\n"
    "  -o <arquivo>: especifica o arquivo de saída\n"
    "  -f <arquivo>: especifica o arquivo de entrada que contém o grafo\n"
    "  -i <vértice>: especifica o vértice inicial\n"
    "  -s: mostra a solução\n"
    "  -h: exibe esta ajuda\n";

int prim(vector<vector<pair<int, int>>> &lista_adjacencia, vector<int> &pai, int fonte, int i)
{
    int tam_agm = 0;
    vector<int> custo(i, numeric_limits<int>::max());
    vector<bool> visitados(i, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;
    
    custo[fonte] = 0;

    min_heap.push({custo[fonte], fonte});

    while(!min_heap.empty())
    {
        int peso_aresta = min_heap.top().first;
        int u = min_heap.top().second;

        min_heap.pop();

        if(!visitados[u])
        {
            visitados[u] = true;
            tam_agm += peso_aresta;

            for(const auto& vizinhos : lista_adjacencia[u]) { 
                int v = vizinhos.first;
                int w = vizinhos.second;

                if(custo[v] > w)
                {
                    custo[v] = w;
                    pai[v] = u;

                    min_heap.push({custo[v], v});
                }
            }
        }
    }

    return tam_agm;
}

int main(int argc, char *argv[]) 
{
    int option;
    string nomearquivo_saida;
    string nomearquivo_entrada;
    int fonte = 0;
    int fluxo_saida = 0;
    int solucao = 0;

    while ((option = getopt(argc, argv, "hso:i:f:")) != -1) 
    {
        switch (option) 
        {
            case 'h':
                cout << TEXTO_DE_AJUDA;
                break;
            case 'o':
                nomearquivo_saida = optarg;
                fluxo_saida = 1;
                break;
            case 'f':
                nomearquivo_entrada = optarg;
                break;
            case 'i':
                fonte = stoi(optarg) - 1;
                break;
            case 's':
                solucao = 1;
                break;
            default:
                cerr << "Unknown flag! Use -h for help instead." << std::endl;
                return 1;
        }
    }

    ifstream arquivo_entrada(nomearquivo_entrada);

    int n;
    int m;
    int u;
    int v;
    int w;
    int i;
    int tam_agm;

    arquivo_entrada >> n >> m;

    vector<vector<pair<int, int>>> lista_adjacencia(n);


    for(i = 0; i < m; i++)
    {
        arquivo_entrada >> u >> v >> w;
        
        if((u > n) || (v > n))
        {
            lista_adjacencia.resize(max(u, v));
        }
        
        lista_adjacencia[u-1].push_back({v-1, w});
        lista_adjacencia[v-1].push_back({u-1, w});
    }
    
    vector<int> pai(n, -1);
    tam_agm = prim(lista_adjacencia, pai, fonte, n);
    
    if(solucao)
    {
        for(i = 0; i < n; i++)
        {
            if(i != fonte)
            {
                cout << "(" << pai[i]+1 << "," << i+1 << ") ";
            }
        }
    }
    else
    {
        cout << tam_agm << endl;
    }
    
    if(fluxo_saida)
    {
        ofstream output_file(nomearquivo_saida, ios::out);
        if(!output_file.is_open())
        {
            return 1;
        }
        
        if(solucao)
        {
            for(i = 0; i < n; i++)
            {
                if(i != fonte)
                {
                    output_file << "(" << pai[i]+1 << "," << i+1 << ") ";
                }
            }
        }
        else
        {
            output_file << tam_agm << endl;
        }
    }

    arquivo_entrada.close();

    return 0;
}
