Trabalho 1 (Heaps binários)
==========================

[Objetivos](#objetivos)
[Casos de Testes](#casos_testes)
[Observações](#observacoes)
[Convenções](#convencoes)
[Como Testar](#como_testar)
[Avaliação e Resultados](#avaliacao)

<a id="objetivos"/>
Objetivos
--------

  * Implementar um heap binário e verificar a complexidade das operações experimentalmente.
  * Implementar o algoritmo de Dijkstra usando o heap implementado.
  * Comparar a complexidade teórica pessimista com a complexidade real. Em particular verificar que a complexidade real respeita o limite teórico.

<a id="casos_testes"/>
Casos de teste
--------------

  * O caso de teste é o rede de trânsito de New York, que pode ser baixado na página do DIMACS challenge.
  * Para testar: Gerar um número suficiente (>100) de pares aleatórias de vértices origem e destino e medir o tempo de execução e o número de operações “insert”, “deletemin” e “decreasekey”.

<a id="observacoes"/>
Observações
-----------

  * Como o grafo possui 264346 vértices é necessário usar uma representação esparsa. Uma matriz de adjacência, em particular, não serve.

<a id="convencoes"/>
Convenções
----------

  * As implementações do algoritmo de Dijkstra devem aceitar um grafo no formato da DIMACS challenge na entrada padrão (stdin), os índices de dois vértices origem e destino na linha de comando e imprimir o valor do caminho mais curto na saída padrão (stdout). Caso não existo caminho entre os dois vértices imprimir “inf”. Exemplo (em UNIX)

  > ./dijkstra 1 2 < NY.gr
  803

<a id="como_testar"/>
Como executar e testar
---------------------
Os programas fazem uso da biblioteca Boost de C++. Para compilar você precisa ter essa biblioteca instalada.

### Compilando ###
  * Compile o gerador de teste:
    c++ -o gen gen.cpp
  * Compile o programa dijkstra
    c++ dijkstra dijkstra.cpp

### Script de testes ###
O script de testes 

### Gerando casos de teste (grafos) ###
Para gerar casos de teste use gen.cpp, ex:
  ./gen 100 0.4 > test.gr 
Esse comando gera um grafo no formato DIMACS challenge.

### Executando o algoritmo de Dijkstra  ###
Para rodar dijkstra, passe como argumentos o vertice inicial, vertice final e o arquivo do grafo na entrada padrão, ex:
  ./dijkstra 1 2 < test.gr

<a id="avaliacao"/>
Avaliação e Resultados
----------------------
Comming soon...
Under construction xD
