#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>

using namespace std;
class dijkstraGraph {
    int verticeDeReferencias;
    vector <vector < int>> distancia;
    vector < vector < pair <int, int>>> adj;
    vector < vector < int >> prev;
     //Lista de adjacência com pares (vértice, peso)
    public:
        dijkstraGraph(int quantidadeDeVertices);
        void adicionarArco(int v, int w, int peso);
        void dijkstra();
        void imprimirCaminho(int origem, int destino);
};


int main(int argc, char* argv[])
{
    ifstream arquivoDeEntrada;
    ofstream arquivoDeSaida;
    int verticeInicial;

    for(int i = 1; i < argc; i++)
    {
        if(string(argv[i]) == "-h")
        {
            // Passo a Passo do algoritmo de Dijkstra
            return 0;
        }
        else if(string(argv[i]) == "-f")
        {

        }
        else if(string(argv[i]) == "-v")
        {
            verticeInicial = stoi(argv[++i]);
        }
        else{
            // MESMO QUE O HELP
        }
    }
}