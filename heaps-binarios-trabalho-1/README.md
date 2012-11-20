Trabalho 1 (Heaps binários)
==========================

1. [Objetivos](#1-objetivos)
2. [Solução](#2-solução)
3. [Ambiente de testes](#3-ambiente-de-testes)
4. [Como executar e testar](#4-como-executar-e-testar)
5. [Experimentos e Resultados](#5-experimentos-e-resultados)

1 Objetivos
-----------
* Implementar um heap binário e verificar a complexidade das operações experimentalmente.
* Implementar o algoritmo de Dijkstra usando o heap implementado.
* Comparar a complexidade teórica pessimista com a complexidade real. Em particular verificar que a complexidade real respeita o limite teórico.

2 Solução
---------
Implementei o algoritmo de Dijkstra utilizando um heap binário de acordo com o material e pseudo algoritmos retirados do material do prof. [Marcus Ritt](http://www.inf.ufrgs.br/~mrpritt/doku.php?id=homepage "Marcus Riit").

TODO: Adicionar pseudo algoritmos aqui

3 Ambiente de testes
--------------------
Os resultados foram obtidos num desktop, com processador Intel Core 2 Duo E8400 de 3 GHz, e 4 GB de RAM. 
Rodando Fedora 16, Kernel Linux 3.6.6-1.fc16.x86\_64.

4 Como executar e testar
------------------------

Os programas fazem uso da biblioteca Boost de C++. Para compilar você precisa ter essa biblioteca instalada.

A implementação do algoritmo de Dijkstra aceita um grafo no formato da DIMACS challenge na entrada padrão (stdin) e os índices de dois vértices origem e destino na linha de comando. Ele imprime o valor do caminho mais curto na saída padrão (stdout). Caso não existo caminho entre os dois vértices imprimir “inf”. Exemplo (em UNIX):

  > ./dijkstra 1 2 < NY.gr
  > 803

### Compilando ###
Compile o gerador de teste:
  > c++ -o gen gen.cpp
Compile o programa dijkstra
  > c++ dijkstra dijkstra.cpp

### Script de testes ###
O script de testes gera grafos de testes (aleatorio) e executa dijkstra para o grafo resultante. Ele repete isso 10 vezes para cada uma das quantidades de vertices (100,200,300,...,2000) dado uma determinada probabilidade (input).

  > ./run\_tests.sh

O script de teste irá gerar os seguintes arquivos, para uma probabilidade de 0.5:
* experiment-0.5-time, contem o maior tempo de execução, a média e o menor tempo de execução para o determinado número de vertices.
* experiment-0.5-deletemin, contem o maior número de chamadas, a média e o menor número de chamadas a insert para o determinado número de vertices.
* experiment-0.5-insert, contem o maior número de chamadas, a média e o menor número de chamadas a insert para o determinado número de vertices. 
* experiment-0.5-update, contem o maior número de chamadas, a média e o menor número de chamadas a update para o determinado número de arestas. 


### Gerando casos de teste (grafos) ###
Para gerar casos de teste use gen.cpp, ex:
  > ./gen 100 0.4 > test.gr 
Esse comando gera um grafo no formato DIMACS challenge.

### Executando o algoritmo de Dijkstra  ###
Para rodar dijkstra, passe como argumentos o vertice inicial, vertice final e o arquivo do grafo na entrada padrão, ex:
  > ./dijkstra 1 2 < test.gr

### Gerando graficos com os resultados ###
Para gerar os resultados a partir dos arquivos resultantes dos testes, utilizando o programa gnuplot:
> gnuplot> set term svg enh
> Terminal type set to 'svg'
> Options are 'size 600,480 fixed enhanced fname 'Arial'  fsize 12 butt solid '
> gnuplot> set output "experiment-0.1-deletemin.svg"
> gnuplot> set ylabel "deletemin"
> gnuplot> set xlabel "number of vertices"
> gnuplot> set xtics border in nomirror rangelimit
> gnuplot> set ytics border in nomirror rangelimit
> gnuplot> set border 3 front linetype -1 linewidth 1.000
> gnuplot> set title "0.1 chance of existing edges between vertices - deletemin"
> gnuplot> plot "experiment-0.1-deletemin" using 1:2:(0):($4-$2) with vec nohead lt -1 notit, "" using 1:3 w p lt 1 ps 0.6 pt 7 notit
> gnuplot> exit


5 Experimentos e Resultados
---------------------------
Os dados foram gerados, randomicamente, utilizando o gerador de casos de testes fornecido (gen.cpp) com numero de vértices variando de 100, 200, 300,..., 2000 e a chance de existir arestas entre cada vertice 0.1, 0.5, 0.7 e 0.9.
Cada combinação de teste foi repetida 10 vezes, gerado a média, maxima e minima dos seguintes dados:
* Tempo de execução
* Chamadas a deletemin()
* Chamadas a insert()
* Chamadas a update()

### Chamadas a deletemin, insert e update ###
O algoritmo de Dijkstra possui complexidade:
  > O(n) + n x deletemin + n x insert + m x update. 

Por isso a utilização de uma boa estrutura de dados para a fila de prioridades utilizada no algoritmo de dijkstra é crucial para se obter complexidade melhor que quadrática. Utilizando um heap binário tem-se complexidade O(n log n + m log n). Isso porque é possivel realizar as operações de insert, deletemin e update em O(log n).

Veja abaixo os resultados das experimentações práticas.

#### deletemin ####
[0.1 chance of existing edges between vertices - deletemin](tests/10/experiment-0.1-deletemin.svg)
[0.5 chance of existing edges between vertices - deletemin](tests/50/experiment-0.5-deletemin.svg)
[0.7 chance of existing edges between vertices - deletemin](tests/70/experiment-0.7-deletemin.svg)
[0.9 chance of existing edges between vertices - deletemin](tests/90/experiment-0.9-deletemin.svg)

#### insert ####

#### update ####

### Tempo de execução ###
Abaixo os resultados dos tempos de execução medidos:


![Under Construction](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcSND5PcVVp5hZtD6up1CMsK4CwOyxoycX9CfGJlgL-OSYrRiETt)

