#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

//adj = Lista de adjacência

using namespace std;

class kosarajuGraph {
    int V;
    vector<vector<int>> adj;
    vector<vector<int>> adjInverso;
    stack <int> pilha; //Pilha utilizada para a vista em pós-ordem
    public:
        kosarajuGraph(int V);
        void adicionarArco(int v, int w);
        void DFSrec(vector<vector<int>> & listaAdj, int v, vector<bool> &visited);
        void DFSPostOrder(vector<vector<int>> & listaAdj, int v, vector<bool> & visited);
        void imprimirComponentesFortementeConexas();
        void imprimirPilha();
        void imprimirAdj();
};
void kosarajuGraph::imprimirAdj(){
    for(int i = 0; i < adj.size(); i++){
        cout << i + 1<< " ";
        for(int j = 0; j < adj[i].size(); j++){
            cout << adj[i][j] + 1 << " ";
        }
        cout << endl;
    }
}
void kosarajuGraph::imprimirPilha(){
    while(!pilha.empty()){
        cout << pilha.top() << " ";
        pilha.pop();
    }
};
kosarajuGraph::kosarajuGraph(int V) {
    this->V = V;
    adj.resize(V);
    adjInverso.resize(V);
}

//Ao mesmo tempo que se coloca um arco v->w no grafo, coloca-se w->v no grafo inverso
void kosarajuGraph::adicionarArco(int v, int w) {
    adj[v].push_back(w);
    adjInverso[w].push_back(v);
}

// Função para realizar uma visita em pós-ordem no grafo
//Só se coloca na pilha depois que tudo for percorrido, ou seja, quando não houver mais vértices adjacentes
void kosarajuGraph::DFSPostOrder(vector<vector<int>> & listaAdj, int v, vector<bool>& visited) {
    visited[v] = true;
    for (int i : listaAdj[v]) {
        if (!visited[i]) {
            DFSPostOrder(listaAdj, i, visited);
        }
    }
    pilha.push(v);
}
//dfsRec padrao
void kosarajuGraph::DFSrec(vector<vector<int>> & listaAdj,int v, vector<bool>& visited) {
    visited[v] = true;
    cout << v + 1<< " ";

    for (int u : listaAdj[v]) {
        if (!visited[u]) {
            DFSrec(listaAdj, u, visited);
        }
    }
}

// Função para imprimir as componentes fortemente conexas
void kosarajuGraph::imprimirComponentesFortementeConexas() {
    int numVertices = adj.size();
    vector <bool> visited(numVertices, false);
    // Passo 1: Preencher a pilha com a ordem de finalização dos vértices
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            DFSPostOrder(adj, i, visited);
        }
    }

    // Passo 2: Inverter o grafo já foi feito na função adicionarArco

    // Passo 3: Executar uma DFS no grafo invertido na ordem dos vértices na pilha
    fill(visited.begin(), visited.end(), false);
     // Resetar o vetor de visitados
    while (!pilha.empty()) 
    {
        int v = pilha.top();
        pilha.pop();
        if (!visited[v]) {
            DFSrec(adjInverso, v, visited);
            cout << endl;
        }
    }
}

int main(){
    int numeroVertices, numeroArestas;
    cin >> numeroVertices >> numeroArestas;


    kosarajuGraph g(numeroVertices);
    for(int i = 0; i < numeroArestas; i++){
        int verticeOrigem, verticeDestino;
        cin >> verticeOrigem >> verticeDestino;
        g.adicionarArco(verticeOrigem - 1, verticeDestino - 1);
    }
    g.imprimirComponentesFortementeConexas();
    
    return 0;
}