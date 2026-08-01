#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include "hash_table_sls.h"
#include "vector_edge.h"
#include "vector_str.h"
#include "c_string.h"

typedef struct Graph {
    HashTable_sls adjacencia;
    Vector_str vertices;
    Vector_edge arestas;
    HashTable_ew peso_aresta;
} Graph;

/* OBS: Em todos os algoritmos em que há cópia de elementos ou ter que olhar todos os caracteres de uma string, eu ignoro a complexidade de se fazer essa aço de cada string individualmente. 
Em outras palavras, para ser mais simples, considero que qualquer varredura dessa individualmente terá complexidade O(1), mesmo que a complexidade seja O(length(s)) sendo s a string
em questão. Prefiro deixar assim pois de forma geral será usado string em cada vértice com tamanho no máximo 3. */

/* Implementação de algoritmos da matéria de otimizações em grafos */

Graph graph_square(const Graph* grafo);    
// @ Retorna o grafo ao quadrado. Se o grafo for vazio, será retornado um grafo vazio.

Graph graph_transposed(const Graph*);
// @ Retorna um grafo novo transposto, isto é, com os mesmos vértices, mas as arestas são de direções opostas. Se o grafo for vazio, será retornado um grafo vazio.
// Obs: Esse algoritmo não é eficiente devido às várias inserções!!!!!


/* Implementação de algoritmos da matéria de algoritmos em grafos */
// Obs: essas implementações usam grafos com arestas sem peso e sem direção

int graph_min_degree(const Graph*);
// @ Retorna o grau mínimo de um grafo. Se o grafo for vazio, será retornado -1.

int graph_max_degree(const Graph*);
// @ Retorna o grau máximo de um grafo. Se o grafo for vazio, será retornado -1.

Graph graph_complement(const Graph*);
// @ Retorna o grafo complementar ao grafo do parâmetro fornecido. Se o parâmetro for nulo, essa função retornará um grafo vazio

void bfs(const Graph*, const char*);
// @ Implementação simples do algoritmo de busca em largura em que, no final, eu apenas imprimo o resultado do algoritmo.
// @ Obs: Se o grafo for vazio ou o vértice não for encontrado, será imprimido na tela "vértice não encontrado!!!"

bool graph_is_connected(const Graph*);
// @ Usa o algoritmo de busca em largura para verificar se o grafo é conexo. Se o grafo for vazio ou o grafo for desconexo, será retornado false.


void graph_greedy_coloring(const Graph*);
// @ Implementação simples de coloração gulosa de vértices de um grafo. Será impresso os vértices e suas respectivas cores de cores 0 a Δ + 1.
// @ Obs: Se o grafo for vazio, será impresso NULL




Graph graph_complete(int);
// @ Retorna um grafo k-completo. Se n <= 0, será retornado um grafo vazio.

Graph graph_bipartite_complete(int, int);
// @ Retorna um grafo bipartido completo. Se um dos parâmetros for menor ou igual a 0, será retornado um grafo vazio.

Graph graph_path(int);
// @ Retorna um grafo caminho. Se n <= 0, será retornado um grafo vazio.

Graph graph_cycle(int);
// @ Retorna um grafo ciclo. Se n < 3, será retornado um grafo vazio.

Graph graph_whell(int);
/* @ Retorna um grafo roda. Se n < 3, retorno um grafo vazio.
   OBS: Minha definição de grafo roda é o grafo ciclo com a adição do vértice que é adjacente aos demais vértices do ciclo.
*/

/* Implementação de algoritmos da matéria de algoritmos em grafos */




/* Funções básicas de grafos */

Graph graph_new();
// @ Inicializa um tipo Graph

bool graph_is_empty(const Graph*);    // O(1)
// @ Retorna true se o parâmetro for nulo ou o grafo não tiver vértices, caso contrário, será retornado false.

Vector_str graph_get_vertices(const Graph*);    // θ(n)
// @ Retorna uma cópia do Vector_str interno de vértices. Se o grafo estiver vazio, será retornado um Vector_str vazio.

Vector_edge graph_get_edges(const Graph*);      // θ(m)
// @ Retorna uma cópia do Vector_edge interno de arestas. Se o grafo estiver vazio ou o grafo não tiver arestas, será retornado um Vector_edge vazio.

int graph_vertex_degree(const Graph*, const char*);    // O(1)
// @ Retorna o grau de um determinado vértice. Se o grafo for vazio ou não encontrar o vértice, será retornado -1.

int graph_vertex_degree_str(const Graph*, const String);   // O(1)
// @ Mesma ideia da função anterior, mas aqui é usado como segundo parâmetro uma String

Vector_str graph_vertex_neighbors(const Graph*, const char*);   // θ(d(v)), com v sendo o vértice passado por parâmetro
// @ Retorna todos os vizinhos de um determinado vértice. Se o grafo for vazio, o vértice não existir ou o grau do vértice for 0, será retornado um Vector_str vazio.

Vector_str graph_vertex_neighbors_str(const Graph*, const String);    // θ(d(v)), com v sendo o vértice passado por parâmetro
// @ Mesma ideia da função anterior, mas é passado o segundo parâmetro sendo uma String

float graph_get_edge_weight(const Graph*, const char*, const char*);    // O(1)
// @ Retorna o peso da aresta se estiver presente no grafo. Se o grafo for vazio ou não encontrar essa aresta, será retornado -1.

float graph_get_edge_weight_str_str(const Graph*, const String, const String);    // O(1)
// @ Mesma ideia da função anterior, mas com duas Strings como parâmetros

float graph_get_edge_weight_edge(const Graph*, const Edge);    // O(1)
// @ Mesma ideia da função anterior, mas com um tipo Edge pasado como parâmetro.

bool graph_update_edge_weight(Graph*, const char*, const char*, float);    // O(m)
// @ Atualiza o peso de uma aresta do grafo, se existente. Se o grafo for vazio ou não encontrar essa aresta, será retornado false.

bool graph_update_edge_weight_str_str(Graph*, const String, const String, float);  // O(m)
// @ Atualiza o peso de uma aresta do grafo, se existente. Se o grafo for vazio ou não encontrar essa aresta, será retornado false.

bool graph_update_edge_weight_edge(Graph*, const Edge, float);   // O(m)
// @ Atualiza o peso de uma aresta do grafo, se existente. Se o grafo for vazio ou não encontrar essa aresta, será retornado false.

int graph_vertex_size(const Graph*);   // O(1)
// @ Retorna o número de vértices do grafo. Se o parâmetro for nulo, será retornado 0.

int graph_edge_size(const Graph*);     // O(1)
// @ Retorna o número de arestas do grafo. Se o parâmetro for nulo, será retornado 0.

bool graph_add_vertex(Graph*, const char*);   // O(1)
// @ Adiciona um vértice ao grafo. Se um dos dois parâmetros for nulo ou se o vértice já existir, será retornado false.

bool graph_add_vertex_str(Graph*, const String);  // O(1)
// @ Mesma ideia da função anterior, mas é passado como o segundo parâmetro uma String.

bool graph_add_edge(Graph*, const char*, const char*);   // O(1)
// @ Adiciona uma aresta ao grafo com peso sendo 0 e sem ser direcionada. Se um dos parâmetros for nulo, um dos vértices não estiver presente no grafo ou até mesmo já existir essa aresta, será retornado false.

bool graph_add_edge_str_str(Graph*, const String, const String);    // O(1)
// @ Mesma ideia da função anterior, mas é passado duas Strings para isso.

bool graph_add_edge_edge(Graph*, const Edge);   // O(1)
// @ Adiciona uma aresta com o tipo Edge. Se o primeiro parâmetro for nulo, será retornado false.

bool graph_add_edge_weight_direction(Graph*, const char*, const char*, float, bool);   // O(1)
// @ Adiciona uma aresta ao grafo. Se um dos parâmetros for nulo, um dos vértices não estiver presente no grafo ou até mesmo já existir essa aresta, será retornado false.

bool graph_add_edge_str_str_weight_direction(Graph*, const String, const String, float, bool);   // O(1)
// @ Mesma ideia da função anterior, mas os segundo e terceiro parâmetros são Strings

bool graph_contains_vertex(const Graph*, const char*);   // O(1)
// @ Verifica se um dado vértice existe no grafo. Se um dos parâmetros for nulo, o grafo for vazio ou se o vértice não estiver presente no grafo, será retornado false.

bool graph_contains_vertex_str(const Graph*, const String);    // O(1)
// @ Mesma ideia da função anterior, mas é passado como o segundo parâmetro uma String.

bool graph_contains_edge_n(const Graph*, const char*, const char*);    // O(1)
// @ Verifica se existe a aresta passada no grafo. Se um dos parâmetros for nulo, o grafo for vazio ou não encontrar essa aresta no grafo, será retornado false.

bool graph_contains_edge_n_str_str(const Graph*, const String, const String);   // O(1)
// @ Mesma ideia da função anterior, mas é passado como o segundo parâmetro e terceiro parâmetro uma String.

bool graph_contains_edge_n_edge(const Graph*, const Edge);    // O(1)
// @ Mesma ideia da função anterior, mas é passado um tipo Edge para isso

bool graph_contains_edge_w(const Graph*, float);    // O(m)
// @ Verifica se existe uma aresta com o peso passado no segundo parâmetro. Se o grafo for vazio ou não existir uma aresta com este peso, será retornado false.

bool graph_contains_edge_w_edge(const Graph*, const Edge);   // O(m)
// @ Verifica se o peso do tipo Edge passado existe no grafo. Se o grafo for vazio ou não existir uma aresta com este peso, será retornado false.

bool graph_remove_vertex(Graph*, const char*);    // O(n + m)
// @ Remove o vértice do grafo. Se um dos dois parâmetros for nulo ou o vértice do segundo parâmetro não existir no grafo, será retornado false.

bool graph_remove_vertex_str(Graph*, const String);   // O(n + m)
// @ Mesma ideia da função anterior, mas é passado como o segundo parâmetro uma String.

bool graph_remove_edge(Graph*, const char*, const char*);   // O(m)
// @ Remove uma aresta do grafo. Se um dos parâmetros for nulo, o grafo for vazio ou não encontrar essa aresta, será retornado false.

bool graph_remove_edge_str_str(Graph*, const String, const String);     // O(m)
// @ Mesma ideia da função anterior, mas são usadas Strings para isso.

bool graph_remove_edge_edge(Graph*, const Edge);    // O(m)
// @ Mesma ideia da função anterior, mas é passado a própria aresta que se deseja remover.

void graph_free(Graph*);    // O(n + m)
// @ Libera a memória de um grafo

String graph_to_string(const Graph*);
// @ Retorna como String uma representação do grafo. A representação aqui será o Vector_str interno de vértices e o Vector_edge interno de arestas. Se o grafo for vazio, será retornado "EMPTY"

String graph_to_string_alternative(const Graph*);
// @ Retorna como String uma representação do grafo. A representação aqui será a tabela adjacencia interna, isto é, cada vértice e seus respectivos vizinhos. Se o grafo for vazio, será retornado "EMPTY"

void graph_print(const Graph*);
// @ Imprime um grafo com a String obtida em graph_to_string()

void graph_println(const Graph*);
// @ Usa a função anterior graph_print() e imprime um caractere '\n' ao final.

void graph_print_alternative(const Graph*);
// @ Imprime um grafo com a String obtida em graph_to_string_alternative()

void graph_println_alternative(const Graph*);
// @ Usa a função anterior graph_print_alternative() e imprime um caractere '\n' ao final.

/* Funções básicas de grafos */

#endif
