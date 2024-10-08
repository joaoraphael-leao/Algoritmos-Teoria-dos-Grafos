#!/bin/bash

# Binários
kosaraju=./kosaraju.bin  # Caminho para o executável do algoritmo de Kosaraju
#prim=./prim.bin          # Caminho para o executável do algoritmo de Prim
#kruskal=./kruskal.bin    # Caminho para o executável do algoritmo de Kruskal
dijkstra=./dijkstra.bin  # Caminho para o executável do algoritmo de Dijkstra

echo "Testando algoritmo de Kosaraju"
for i in instances_scc/*.dat  # Para cada arquivo .dat na pasta instances_scc
do
    echo -e "\e[33mInstância $i\e[0m";  # Exibe a instância atual em amarelo
    $kosaraju -f $i | ./ordena.sh > temp;  # Executa o algoritmo de Kosaraju e ordena a saída, salvando em temp

    j=$(basename $i);  # Obtém o nome base do arquivo
    diff -w temp ./scc/$j > /dev/null ;  # Compara a saída com o arquivo de referência na pasta scc
    if [ $? -eq 0 ]; then  # Se não houver diferenças
        echo -e "\e[32mOK\e[0m"  # Exibe "OK" em verde
    else
        echo -e "\e[31mErro\e[0m";  # Exibe "Erro" em vermelho
    fi
    rm temp;  # Remove o arquivo temporário

done

echo "Testando algoritmo de Kruskal"
for i in instances/*.mtx  # Para cada arquivo .mtx na pasta instances
do
    echo -e "\e[33mInstância $i\e[0m";  # Exibe a instância atual em amarelo
    val=$($kruskal -f $i);  # Executa o algoritmo de Kruskal e salva o valor do custo
    correto=$(grep $i gabarito_agm.txt | cut -d ' ' -f 2);  # Obtém o valor correto do custo do arquivo gabarito_agm.txt
    [ $val -eq $correto ] && echo -e "Custo \e[32mOK\e[0m" || echo  -e "\e[31mCusto incorreto\e[0m";  # Compara os valores e exibe o resultado

    $kruskal -f $i -s | sed -e 's/ /\n/g' -e 's/,/ /g' -e 's/[()]//g' | ./agm $i  # Verifica se a árvore gerada é um subgrafo válido
    if [ $? -eq 0 ]; then  # Se for um subgrafo válido
        echo -e "\e[32mOK\e[0m"  # Exibe "OK" em verde
    else
        echo -e "\e[31mNão é um subgrafo\e[0m";  # Exibe "Não é um subgrafo" em vermelho
    fi

done

echo -e "\n\n";

echo "Testando algoritmo de Prim"
for i in instances/*.mtx  # Para cada arquivo .mtx na pasta instances
do
    echo -e "\e[33mInstância $i\e[0m";  # Exibe a instância atual em amarelo
    val=$($prim -f $i);  # Executa o algoritmo de Prim e salva o valor do custo
    correto=$(grep $i gabarito_agm.txt | cut -d ' ' -f 2);  # Obtém o valor correto do custo do arquivo gabarito_agm.txt
    [ $val -eq $correto ] && echo -e "Custo \e[32mOK\e[0m" || echo  -e "\e[31mCusto incorreto\e[0m";  # Compara os valores e exibe o resultado

    $prim -f $i -s | sed -e 's/ /\n/g' -e 's/,/ /g' -e 's/[()]//g' | ./agm $i  # Verifica se a árvore gerada é um subgrafo válido
    if [ $? -eq 0 ]; then  # Se for um subgrafo válido
        echo -e "\e[32mOK\e[0m"  # Exibe "OK" em verde
    else
        echo -e "\e[31mNão é um subgrafo\e[0m";  # Exibe "Não é um subgrafo" em vermelho
    fi

done

echo "Testando algoritmo de Dijkstra"
for i in instances/*.mtx  # Para cada arquivo .mtx na pasta instances
do
    echo -e "\e[33mInstância $i\e[0m";  # Exibe a instância atual em amarelo
    $dijkstra -f $i > temp;  # Executa o algoritmo de Dijkstra e salva a saída em temp

    j=$(basename $i);  # Obtém o nome base do arquivo
    diff -w temp ./sp/$j > /dev/null ;  # Compara a saída com o arquivo de referência na pasta sp
    if [ $? -eq 0 ]; then  # Se não houver diferenças
        echo -e "\e[32mOK\e[0m"  # Exibe "OK" em verde
    else
        echo -e "\e[31mErro\e[0m";  # Exibe "Erro" em vermelho
    fi
    rm temp;  # Remove o arquivo temporário

done