#ifndef EDGE_H
#define EDGE_H

#include <stdbool.h>
#include "c_string.h"

typedef struct Edge {
    String u;
    String v;
    float peso;
    bool direcionado;
} Edge;

Edge edge_new_empty();
// @ Inicializa um tipo Edge vazio, isto é, com os campos u e v sendo strings vazias, peso sendo 0 e direcionado sendo false. Utilize esse inicializador para servir de retorno funções em que se tenha um parâmetro Edge* como retorno.

Edge edge_new(const String, const String, float, bool);
/* @ Inicializa um novo tipo Edge com os parâmetros, do primeiro ao ultimo, sendo, respectivamente, para os campos u, v, peso e direcionado.
   Obs: Se for criado um Edge não direcionado e a segunda string "for maior" que a primeira, o campo u assumirá o segundo parâmetro e o campo v assumirá o primeiro parâmetro.
*/

Edge edge_new_cstr_cstr(const char*, const char*, float, bool);
// @ Mesma ideia do inicializador anterior, mas os dois primeiros parâmetros são de vetor de caracteres.

void edge_free(Edge*);
// @ Libera a memória da aresta

bool edge_copy(Edge*, const Edge*);
// @ Copia os dados do segundo parâmetro para o primeiro. Em caso de problemas de memória ou de algum parâmetro ser nulo, o primeiro parâmetro não será alterado e a função retornará false.

int edge_compare_n(const Edge*, const Edge*);
// @ Comparação entre duas arestas pelo nome.

int edge_compare_n_cstr_cstr(const Edge*, const char*, const char*, bool);
// @ Compara uma aresta com as extremidades de uma (possível) aresta

int edge_compare_w(const Edge*, const Edge*);
// @ Comparação entre duas arestas pelo peso.

int edge_compare_w_weight(const Edge*, float);
// @ Comparação entre o peso da aresta com o número do segundo parâmetro representando um possível peso.

bool edge_equals_n(const Edge*, const Edge*);
// @ Verifica se as duas arestas possuem o mesmo nome.

bool edge_equals_n_cstr_cstr(const Edge*, const char*, const char*, bool);
// @ Verifica se o nome da aresta do primeiro parâmetro corresponde a aresta representada pelo segundo e pelo terceiro parâmetro

bool edge_equals_w(const Edge*, const Edge*);
// @ Verifica se as duas arestas possuem o mesmo peso.

bool edge_equals_w_weight(const Edge*, float);
// @ Verifica se a aresta do primeiro parâmetro possui exatamente o segundo parâmetro como peso.

String edge_to_string(const Edge*);
/* @ Retorna uma representação de Edge como String. Se o parâmetro for nulo ou não conseguir retornar a String desejada por falta de memória, será retornada a String "NULL".
   OBS: A String retornada, se bem sucedida, terá um dos seguintes formatos:
      1) u--v(weight)
      2) u->v(weight)
      
      u e v são as Strings que representam as extremidades da aresta e weight o peso. Se for uma aresta direcionada, entre as duas extremidades, será retornado esse "->" entre as duas extremidades como em 2), caso contrário, será retornado esse "--" entre as duas extremidades como em 1)
*/

void edge_print(const Edge*);
// @ Imprime uma representação da aresta usando a String obtida com o edge_to_string().

void edge_println(const Edge*);
// @ Usa a função anterior edge_print() e imprime o caractere "\n" ao final.

#endif
