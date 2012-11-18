Trabalho 1 (Heaps binários)
==========================

1. [Objetivos](#1-objetivos)
2. [Casos de Testes](#2-casos-de-teste)
3. [Observações](#3-observações)
4. [Convenções](#4-convenções)
5. [Como Testar](#5-como-executar-e-testar)
6. [Avaliação e Resultados](#6-avaliação-e-resultados)

1 Objetivos
--------

  * Implementar um heap binário e verificar a complexidade das operações experimentalmente.
  * Implementar o algoritmo de Dijkstra usando o heap implementado.
  * Comparar a complexidade teórica pessimista com a complexidade real. Em particular verificar que a complexidade real respeita o limite teórico.

2 Casos de teste
--------------

  * O caso de teste é o rede de trânsito de New York, que pode ser baixado na página do DIMACS challenge.
  * Para testar: Gerar um número suficiente (>100) de pares aleatórias de vértices origem e destino e medir o tempo de execução e o número de operações “insert”, “deletemin” e “decreasekey”.

3 Observações
-----------

  * Como o grafo possui 264346 vértices é necessário usar uma representação esparsa. Uma matriz de adjacência, em particular, não serve.

4 Convenções
----------

  * As implementações do algoritmo de Dijkstra devem aceitar um grafo no formato da DIMACS challenge na entrada padrão (stdin), os índices de dois vértices origem e destino na linha de comando e imprimir o valor do caminho mais curto na saída padrão (stdout). Caso não existo caminho entre os dois vértices imprimir “inf”. Exemplo (em UNIX)

  > ./dijkstra 1 2 < NY.gr
  803

5 Como executar e testar
---------------------
Os programas fazem uso da biblioteca Boost de C++. Para compilar você precisa ter essa biblioteca instalada.

### Compilando ###
* Compile o gerador de teste:
  c++ -o gen gen.cpp
* Compile o programa dijkstra
  c++ dijkstra dijkstra.cpp

### Script de testes ###
O script de testes gera grafos de testes (aleatorio) e executa dijkstra para o grafo resultante. Ele repete isso 10 vezes para cada uma das quantidades de vertices (100,200,300,...,3000) dado uma determinada probabilidade (input).
  ./run\_tests.sh

### Gerando casos de teste (grafos) ###
Para gerar casos de teste use gen.cpp, ex:
  ./gen 100 0.4 > test.gr 
Esse comando gera um grafo no formato DIMACS challenge.

### Executando o algoritmo de Dijkstra  ###
Para rodar dijkstra, passe como argumentos o vertice inicial, vertice final e o arquivo do grafo na entrada padrão, ex:
  ./dijkstra 1 2 < test.gr

6 Avaliação e Resultados
----------------------
Comming soon...
Under construction xD
