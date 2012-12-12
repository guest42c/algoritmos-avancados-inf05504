Fluxo s-t máximo
===============

1. [Objetivos](#1-objetivos)
2. [Solução](#2-solução)
3. [Ambiente de testes](#3-ambiente-de-testes)
4. [Como executar e testar](#4-como-executar-e-testar)
5. [Experimentos e Resultados](#5-experimentos-e-resultados)


1 Objetivos
--------

* Implementar o algoritmo de Ford-Fulkerson com a estratégia do “caminho mais gordo” (fattest path) s-t.
* Verificar a complexidade do algoritmo experimentalmente.


2 Solução
---------

Foi implementado o algoritmo de Ford-Fulkerson que busca o caminho de maior gargalo para aumentar o fluxo. Essa busca foi implementada com uma modificação do algoritmo de Dijkstra, que ao invez de buscar pelo menor somatório das distâncias, busca o maior entre as menores distancias dos caminhos. 

Poucas alterações foram necessárias para isso. No momento de realizar insert ou update, o valor da distancia deve ser o menor entre o atual e a distance entre os nodos (altera linhas 11 e 14 do algoritmo 1.3 das notas de aula). Alem disso o heap foi alterado para ser um max heap (basicamente inverter as comparações).

Com isso, sendo U o limite superior da capacidade de um arco, o algoritmo termina em no máximo O(m log mU) passos.

3 Ambiente de testes
--------------------
Os resultados foram obtidos num notebook, com processador Intel® Core™ i3-2310M CPU @ 2.10GHz × 4, e 4 GB de RAM. Rodando Ubuntu 12.10 64bits.

4 Como executar e testar
------------------------

Os programas fazem uso da biblioteca Boost de C++. Para compilar você precisa ter essa biblioteca instalada.

A implementação aceita um grafo no formato da DIMACS challenge na entrada padrão (stdin). Ele imprime o valor do fluxo máximo na saída padrão (stdout). Exemplo (em UNIX):

  > ./ford-fulkerson < example.gr
  > 803

### Compilando ###
Compile o gerador de teste:
  > gcc -o gengraph washington.c
Compile o programa ford-fulkerson
  > g++ -o ford-fulkerson ford-fulkerson.cpp

### Script de testes ###
O script de testes gera grafos de testes (aleatorios) aumentado gradualmente os valores passados como dim1 e dim2, em um total de 10 passos, até o ultimo grafo que possue as dimensões dim1 e dim2 (ver tópico Gerando grafos para os testes). Para cada um desses grafos ele executa10 vezes o algoritmo e tira uma média dos resultados (iterações e tempo de execução).

Exemplo:
  > ./run\_tests.sh
  > type:
  > 1
  > dim1:
  > 50
  > dim2:
  > 50
  > range:
  > 100

O script de teste irá gerar os seguintes arquivos:
* experiment-dim1-dim2-range-time, contem o maior tempo de execução, a média e o menor tempo de execução para o determinado numero de arestas.
* experiment-dim1-dim2-range-iter, contem o maior número de iterações do laço principal de ford-fulkerson, a média e o menor número. Junto com o número de arestas e o limite superior U da capacidade de um arco.
* experiment-dim1-dim2-range-all, contem os dados experimentais de cada uma das execuções.

### Gerando grafos para os testes

To use:  cc washington.c -o gengraph
                      gengraph function arg1 arg2 arg3

             Command line arguments have the following meanings:

                      function:           index of desired graph type
                      arg1, arg2, arg3:   meanings depend on graph type
                                          (briefly listed below: see code
                                           comments for more info)

                 Mesh Graph:          1 rows  cols  maxcapacity
                 Random Level Graph:  2 rows  cols  maxcapacity
                 Random 2-Level Graph:3 rows  cols  maxcapacity
                 Matching Graph:      4 vertices  degree
                 Square Mesh:         5 side  degree  maxcapacity
                 Basic Line:          6 rows  cols  degree
                 Exponential Line:    7 rows  cols  degree
                 Double Exponential   8 rows  cols  degree
                 DinicBadCase:        9 vertices
                      (causes n augmentation phases)
                 GoldBadCase         10 vertices
                 Cheryian            11 dim1 dim2  range
                      (last 2 are bad for goldberg's algorithm)

TODO: inserir tabela (imagem) com descrição do tipo de funções

Exemplo:
Para Mesh Graph com 5 linhas e 5 colunas, capacidade maxima 100 e escreve no arquivo "teste"
> ./gengraph 1 5 5 100 teste

### Programa para verificação da resposta

maxflow.cpp



5 Experimentos e Resultados
---------------------------






