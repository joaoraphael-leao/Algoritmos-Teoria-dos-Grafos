#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>

class dijkstraGraph {
    int V;
    std::vector<std::vector<std::pair<int, int>>> adj; //Lista de adjacência com pares (vértice, peso)
    public:
        dijkstraGraph(int V);
        void adicionarArco(int v, int w, int peso);
        void dijkstra(int origem);
        void imprimirCaminho(int origem, int destino);
};