#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <fstream>
//adj = Lista de adjacência

using namespace std;

class kosarajuGraph {
    int size;
    vector<vector<int>> adj;
    vector<vector<int>> adjInverso;
    stack<int> pilha; // Pilha utilizada para a vista em pós-ordem
    ofstream* arquivoDeSaida; // Ponteiro para o arquivo de saída

public:
    kosarajuGraph(int V, ofstream* arquivoDeSaida = nullptr);
    void adicionarArco(int v, int w);
    void DFSrec(vector<vector<int>>& listaAdj, int v, vector<bool>& visited);
    void DFSPostOrder(vector<vector<int>>& listaAdj, int v, vector<bool>& visited);
    void imprimirComponentesFortementeConexas();
};

kosarajuGraph::kosarajuGraph(int size, ofstream* arquivoDeSaida) {
    this->size = size;
    this->arquivoDeSaida = arquivoDeSaida;
    adj.resize(size);
    adjInverso.resize(size);
}

// Ao mesmo tempo que se coloca um arco v->w no grafo, coloca-se w->v no grafo inverso
void kosarajuGraph::adicionarArco(int v, int w) {
    adj[v].push_back(w);
    adjInverso[w].push_back(v);
}

// Função para realizar uma visita em pós-ordem no grafo
// Só se coloca na pilha depois que tudo for percorrido, ou seja, quando não houver mais vértices adjacentes
void kosarajuGraph::DFSPostOrder(vector<vector<int>>& listaAdj, int v, vector<bool>& visited) {
    visited[v] = true;
    for (int i : listaAdj[v]) {
        if (!visited[i]) {
            DFSPostOrder(listaAdj, i, visited);
        }
    }
    pilha.push(v);
}
// dfsRec padrão
void kosarajuGraph::DFSrec(vector<vector<int>>& listaAdj, int v, vector<bool>& visited) {
    visited[v] = true;
    if (arquivoDeSaida) {
        *arquivoDeSaida << v + 1 << " ";
    } else {
        cout << v + 1 << " ";
    }

    for (int u : listaAdj[v]) {
        if (!visited[u]) {
            DFSrec(listaAdj, u, visited);
        }
    }
}
// Função para imprimir as componentes fortemente conexas
void kosarajuGraph::imprimirComponentesFortementeConexas() {
    int numVertices = adj.size();
    vector<bool> visited(numVertices, false);
    // Passo 1: Preencher a pilha com a ordem de finalização dos vértices
    for (int i = 0; i < size; i++) {
        if (!visited[i]) {
            DFSPostOrder(adjInverso, i, visited);
        }
    }

    // Passo 2: Inverter o grafo já foi feito na função adicionarArco

    // Passo 3: Executar uma DFS no grafo invertido na ordem dos vértices na pilha
    fill(visited.begin(), visited.end(), false); // Resetar o vetor de visitados
    while (!pilha.empty()) {
        int v = pilha.top();
        pilha.pop();
        if (!visited[v]) {
            DFSrec(adj, v, visited);
            if (arquivoDeSaida) {
                *arquivoDeSaida << endl;
            } else {
                cout << endl;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    ifstream arquivoDeEntrada;
    ofstream arquivoDeSaida;
    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "-h") {
            // Passo a Passo do algoritmo de Kosaraju
            return 0;
        } else if (string(argv[i]) == "-o") {
            // Incrementa o valor do i para que o nome do arquivo de entrada não seja lido pelo loop
            arquivoDeSaida.open(argv[++i]);
            // Colocar arquivo de saída
        } else if (string(argv[i]) == "-f") {
            // Incrementa o valor do i para que o nome do arquivo de entrada não seja lido pelo loop
            arquivoDeEntrada.open(argv[++i]);
            // Referenciar arquivo de entrada
        } else {
            cout << "Argumento inválido! Utilize -h para ajuda" << endl;
            return -1;
            // EXIBIR MENSAGEM DE ERRO!
        }
    }

    int numeroVertices, numeroArestas;
    arquivoDeEntrada >> numeroVertices >> numeroArestas;

    kosarajuGraph g(numeroVertices, arquivoDeSaida.is_open() ? &arquivoDeSaida : nullptr);
    for (int i = 0; i < numeroArestas; i++) {
        int verticeOrigem, verticeDestino;
        arquivoDeEntrada >> verticeOrigem >> verticeDestino;
        g.adicionarArco(verticeOrigem - 1, verticeDestino - 1);
    }
    g.imprimirComponentesFortementeConexas();

    arquivoDeEntrada.close();
    if(arquivoDeSaida.is_open())
    {
        arquivoDeSaida.close();
    }
    return 0;
}