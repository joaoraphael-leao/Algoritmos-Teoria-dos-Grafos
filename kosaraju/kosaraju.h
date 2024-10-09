// kosarajuGraph.h
#ifndef KOSARAJUGRAPH_H
#define KOSARAJUGRAPH_H

#include <iostream>
#include <vector>
#include <stack>
#include <fstream>

using namespace std; // Adicionado aqui
/**
 * @class kosarajuGraph
 * @brief Classe que representa um grafo direcionado e diversos utilitários para o Algoritmo de Kosaraju.
 * 
 * @param size Número de vértices do grafo.
 */ 
class kosarajuGraph {
private:
    /**
     * @brief Número De Vértices do Grafo.
     */
    int size;
    /**
     * @brief Lista de Adjacência do Grafo G original.
     */

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

#endif // KOSARAJUGRAPH_H
