#include <iostream>    // Para std::cout, std::cin
#include <fstream>     // Para std::ifstream, std::ofstream
#include <vector>      // Para std::vector
#include <queue>       // Para std::priority_queue
#include <limits>      // Para std::numeric_limits
#include <string>      // Para std::string

using namespace std;

class dijkstraGraph {
    ofstream *arquivoDeSaida;
    int verticeDeReferencia;
    vector<int> distanciaParaVerticeInicial;
    vector<vector<pair<int, int>>> adj; 
    // Lista de adjacência com pares (vértice, peso)

public:
    dijkstraGraph(int quantidadeDeVertices, int verticeReferencia, ofstream* arquivoDeSaida);
    void adicionarArcoPonderado(int verticeOrigem, int verticeDestino, int peso);
    void dijkstra();
    void imprimirDistancias();
    void gambiarra();
};

dijkstraGraph::dijkstraGraph(int quantidadeDeVertices, int verticeDeReferencia, ofstream* arquivoDeSaida) {
    this->distanciaParaVerticeInicial.resize(quantidadeDeVertices);
    this->adj.resize(quantidadeDeVertices);
    this->verticeDeReferencia = verticeDeReferencia;
    this->arquivoDeSaida = arquivoDeSaida;
}

void dijkstraGraph::adicionarArcoPonderado(int verticeOrigem, int verticeDestino, int peso) {
    adj[verticeOrigem].push_back({peso, verticeDestino});
    adj[verticeDestino].push_back({peso, verticeOrigem});
}

void dijkstraGraph::dijkstra() {
    // Inicializa todas as distâncias como infinito
    fill(distanciaParaVerticeInicial.begin(), distanciaParaVerticeInicial.end(), numeric_limits<int>::max());

    distanciaParaVerticeInicial[verticeDeReferencia] = 0;

    // Fila de prioridade mínima
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> fila;
    fila.push({0, verticeDeReferencia}); // Peso é o primeiro elemento para a prioridade funcionar

    while (!fila.empty()) {
        int i = fila.top().second;
        int distanciaAtual = fila.top().first;
        fila.pop();

        if (distanciaAtual > distanciaParaVerticeInicial[i]) {
            continue;
        }

        for (pair<int, int> vizinho : adj[i]) {
            int pesoAteVizinho = vizinho.first;
            int w = vizinho.second;
            if (distanciaParaVerticeInicial[w] > distanciaParaVerticeInicial[i] + pesoAteVizinho) {
                distanciaParaVerticeInicial[w] = distanciaParaVerticeInicial[i] + pesoAteVizinho;
                fila.push({distanciaParaVerticeInicial[w], w});
            }
        }
    }
}

void dijkstraGraph::imprimirDistancias() {
    for (int i = 0; i < distanciaParaVerticeInicial.size(); i++) {
        if (arquivoDeSaida) {
            *arquivoDeSaida << i + 1 << ":" 
                            << (distanciaParaVerticeInicial[i] == numeric_limits<int>::max() ? -1 : distanciaParaVerticeInicial[i]);
        } else {
            cout << i + 1 << ":" 
                 << (distanciaParaVerticeInicial[i] == numeric_limits<int>::max() ? -1 : distanciaParaVerticeInicial[i]);
        }
        if (i + 1 == distanciaParaVerticeInicial.size()) {
            arquivoDeSaida ? *arquivoDeSaida << endl : cout << endl;
        } else {
            arquivoDeSaida ? *arquivoDeSaida << " " : cout << " ";
        }
    }
}

int main(int argc, char* argv[]) {
    ifstream arquivoDeEntrada;
    ofstream arquivoDeSaida;
    int verticeDeReferencia = 0, numeroDeVertices, numeroDeArestas;

    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "-h") {
            // Exibe ajuda sobre o algoritmo
            return 0;
        } else if (string(argv[i]) == "-o") {
            arquivoDeSaida.open(argv[++i]);
        } else if (string(argv[i]) == "-f") {
            arquivoDeEntrada.open(argv[++i]);
        } else if (string(argv[i]) == "-i") {
            verticeDeReferencia = stoi(argv[++i]);
            verticeDeReferencia--;
        }
    }

    arquivoDeEntrada >> numeroDeVertices >> numeroDeArestas;
    dijkstraGraph g(numeroDeVertices, verticeDeReferencia, arquivoDeSaida.is_open() ? &arquivoDeSaida : nullptr);

    for (int i = 0; i < numeroDeArestas; i++) {
        int v, w, peso;
        arquivoDeEntrada >> v >> w >> peso;
        g.adicionarArcoPonderado(v - 1, w - 1, peso);
    }

    g.dijkstra();
    g.imprimirDistancias();

    arquivoDeEntrada.close();
    if (arquivoDeSaida.is_open()) {
        arquivoDeSaida.close();
    }

    return 0;
}