#include <bits/stdc++.h>
#include <functional>

using namespace std;
class dijkstraGraph {
    ofstream *arquivoDeSaida;
    int verticeDeReferencia;
    vector <int> distanciaParaVerticeInicial;
    vector < vector < pair <int, int>>> adj;
     //Lista de adjacência com pares (vértice, peso)
    public:
        dijkstraGraph(int quantidadeDeVertices, int verticeReferencia, ofstream* arquivoDeSaida);
        void adicionarArcoPonderado(int verticeOrigem, int verticeDestino, int peso);
        void dijkstra();
        void imprimirDistancias();
        void gambiarra();
};

dijkstraGraph::dijkstraGraph(int quantidadeDeVertices, int verticeDeReferencia, ofstream* arquivoDeSaida)
{
    this -> distanciaParaVerticeInicial.resize(quantidadeDeVertices);
    this -> adj.resize(quantidadeDeVertices);
    this -> verticeDeReferencia = verticeDeReferencia;
    this -> arquivoDeSaida = arquivoDeSaida;
}

void dijkstraGraph::adicionarArcoPonderado(int verticeOrigem, int verticeDestino, int peso)
{
    adj[verticeOrigem].push_back({peso, verticeDestino});
    adj[verticeDestino].push_back({peso, verticeOrigem});
}

void dijkstraGraph::dijkstra()
{
    fill(distanciaParaVerticeInicial.begin(), distanciaParaVerticeInicial.end(), INT_MAX);

    distanciaParaVerticeInicial[verticeDeReferencia] = 0;

    
    //Fila de prioridade mínima para os vértices a serem passados na busca.
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> fila;
    
    fila.push({0, verticeDeReferencia}); //Peso é o primeiro elemento para a prioridade funcionar
    

    while(!fila.empty())
    {
        int i = fila.top().second;
        int distanciaAtual = fila.top().first;
        if (distanciaAtual > distanciaParaVerticeInicial[i]) {
            continue;
        }
        fila.pop();
        
        for(pair<int, int> vizinho: this -> adj[i])
        {   

            int pesoAteVizinho = vizinho.first;
            int w = vizinho.second;
            if(distanciaParaVerticeInicial[w] > distanciaParaVerticeInicial[i] + pesoAteVizinho)
            {   
                distanciaParaVerticeInicial[w] = distanciaParaVerticeInicial[i] + pesoAteVizinho;
                fila.push({distanciaParaVerticeInicial[w] , w});
            }
        }
    }
}

void dijkstraGraph::imprimirDistancias(){
    for(int i = 0; i < distanciaParaVerticeInicial.size(); i++)
    {
        if(arquivoDeSaida){
            *arquivoDeSaida << i + 1 << ":" << (distanciaParaVerticeInicial[i] == INT_MAX ? -1 : distanciaParaVerticeInicial[i]);
        }
        else{
            cout << i + 1 << ":" << (distanciaParaVerticeInicial[i] == INT_MAX ? -1 : distanciaParaVerticeInicial[i]);
        }
        if(i + 1 == distanciaParaVerticeInicial.size())
        {
            arquivoDeSaida ? *arquivoDeSaida << endl : cout << endl;
        }
        else
        {   
            arquivoDeSaida ? *arquivoDeSaida << " " : cout << " ";
        }
    }
}



int main(int argc, char* argv[])
{
    ifstream arquivoDeEntrada;
    ofstream arquivoDeSaida;
    int verticeDeReferencia = 0, numeroDeVertices, numeroDeArestas;

    for(int i = 1; i < argc; i++)
    {
        if(string(argv[i]) == "-h")
        {
            // Passo a Passo do algoritmo de Dijkstra
            return 0;
        }
        else if(string(argv[i]) == "-o")
        {
            arquivoDeSaida.open(argv[++i]);
        }
        else if(string(argv[i]) == "-f")
        {
            arquivoDeEntrada.open(argv[++i]);
        }
        else if(string(argv[i]) == "-i")
        {
            verticeDeReferencia = stoi(argv[++i]);
            verticeDeReferencia--;
        }
        else{
            // MESMO QUE O 
        }
    }
    arquivoDeEntrada >> numeroDeVertices >> numeroDeArestas;
    dijkstraGraph g(numeroDeVertices, verticeDeReferencia, arquivoDeSaida.is_open() ? &arquivoDeSaida : nullptr);
    
    for(int i = 0; i < numeroDeArestas; i++)
    {
        int v, w, peso;
        arquivoDeEntrada >> v >> w >> peso;
        g.adicionarArcoPonderado(v - 1, w - 1, peso);
    }

    g.dijkstra();
    g.imprimirDistancias();
    
    arquivoDeEntrada.close();
    if(arquivoDeSaida.is_open())
    {
        arquivoDeSaida.close();
    }

    return 0;
}