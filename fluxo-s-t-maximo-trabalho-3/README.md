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



3 Ambiente de testes
--------------------
Os resultados foram obtidos num desktop, com processador Intel Core 2 Duo E8400 de 3 GHz, e 4 GB de RAM. Rodando Fedora 16, Kernel Linux 3.6.6-1.fc16.x86\_64.

4 Como executar e testar
------------------------

### Para gerar grafos para os testes

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


Exemplo:
Para Mesh Graph com 5 linhas e 5 colunas, capacidade maxima 100 e escreve no arquivo "teste"
> ./gengraph 1 5 5 100 teste


### Programa para verificação da resposta

maxflow.cpp



5 Experimentos e Resultados
---------------------------




