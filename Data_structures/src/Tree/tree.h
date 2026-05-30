#ifndef TREE_H
#define TREE_H

#include <stdbool.h>
#include "c_string.h"

/* MUDE O TIPO_TREE E A PRECISAO AQUI. NO CASO DO ÚLTIMO, A PRECISAO SERÁ USADA EM FLOAT E DOUBLE APENAS */ 
#define PRECISION_TREE 2    // Mude a precisão de float e double aqui

//!!!!!!!!!!!!!!! Mude aqui qual tipo_tree primitivo quer escolher !!!!!!!!!!!!!!!!!

// #define TIPO_TREE_INT
// #define TIPO_TREE_LONG
// #define TIPO_TREE_LONG_LONG
// #define TIPO_TREE_FLOAT
// #define TIPO_TREE_DOUBLE
#define TIPO_TREE_DOUBLE_G
// #define TIPO_TREE_CHAR


#if defined(TIPO_TREE_INT)

    typedef int tipo_tree;
    #define TO_STRING_TREE(x) string_from_int((x))

#elif defined(TIPO_TREE_LONG)

    typedef long tipo_tree;
    #define TO_STRING_TREE(x) string_from_long((x))

#elif defined(TIPO_TREE_LONG_LONG)

    typedef long long tipo_tree;
    #define TO_STRING_TREE(x) string_from_long_long((x))

#elif defined(TIPO_TREE_FLOAT)

    typedef float tipo_tree;
    #define TO_STRING_TREE(x) string_from_float((x), PRECISION_TREE)

#elif defined(TIPO_TREE_DOUBLE)

    typedef double tipo_tree;
    #define TO_STRING_TREE(x) string_from_double((x), PRECISION_TREE)

#elif defined(TIPO_TREE_DOUBLE_G)

    typedef double tipo_tree;
    #define TO_STRING_TREE(x) string_from_double_g((x))

#elif defined(TIPO_TREE_CHAR)

    typedef char tipo_tree;
    #define TO_STRING_TREE(x) string_from_char((x))

#else
      #error "Defina UM tipo_tree válido em tree.h"

#endif
/* MUDE O TIPO_TREE E A PRECISAO AQUI. NO CASO DO ÚLTIMO, A PRECISAO SERÁ USADA EM FLOAT E DOUBLE APENAS */


typedef struct No_tree {
    tipo_tree E;
    int Q;
    struct No_tree* Esq;
    struct No_tree* Dir;
} No_tree;

typedef struct Tree {
    No_tree* T;
    int size;
} Tree;



Tree tree_new();
// @ Inicializa um tipo Tree.

bool tree_is_empty(const Tree*);
// @ Verifica se é uma árvore vazia. Se o parâmetro ou o campo T for nulo, será retornado true.

int tree_size(const Tree*);
// @ Retorna o número de elementos da árvore. Se o parâmetro for nulo, será retornado 0.

bool tree_insert(Tree*, tipo_tree);
// @ Insere o elemento do segundo parâmetro. Se o primeiro parâmetro for nulo, será retornado false.

bool tree_search(const Tree*, tipo_tree);
// @ Busca se o elemento do segundo parâmetro está na árvore. Se o primeiro parâmetro for nulo, a árvore for vazia ou não encontrar o elemento, será retornado false.

bool tree_remove(Tree*, tipo_tree);
// @ Remove o elemento do terceiro parâmetro se ele estiver presente na árvore. Se o primeiro parâmetro for nulo, a árvore for vazia ou não encontrar o elemento a ser removido, será retornado false.

void tree_free(Tree*);
// @ Libera a memória da árvore.

String tree_to_string(const Tree*);
// @ Retorna uma representação básica dos elementos da árvore como String. Se o parâmetro for nulo, a árvore for vazia ou não for possível criar a primeira alocação da String, será retornada a String "NULL".

String tree_to_string_detailed(const Tree*);
// @ Retorna uma representação detalhada da árvore como String, isto é, retorna todos os nós, com cada nó mostrando o elemento atual, o elemento do ponteiro Esq (se não existir ficará "NULL") e o elemento do ponteiro Dir (se não existir ficará "NULL"). Se o parâmetro for nulo, a árvore for vazia ou não for possível criar a primeira alocação da String, será retornada a String "NULL".

void tree_print(const Tree*);
// @ Imprime a String obtida com a função tree_to_string().

void tree_print_detailed(const Tree*);
// @ Imprime a String obtida com a função tree_to_string_detailed().

void tree_println(const Tree*);
// @ Usa a função tree_print() e imprime o caractere '\n' ao final.

void tree_println_detailed(const Tree*);
// @ Usa a função tree_print_detailed() e imprime o caractere '\n' ao final.

int tree_no_height(const Tree*, tipo_tree);
// @ Se o elemento do segundo parâmetro for encontrado na árvore, será retornado a sua respectiva altura; caso o contrário, será retornado -1. Se o primeiro parâmetro for nulo ou a árvore for vazia, também será retornado -1.

int tree_height(const Tree*);
// @ Retorna a altura da árvore. Se o parâmetro for nulo ou a árvore for vazia, será retornado -1.

tipo_tree* tree_to_cvet(const Tree*);
// @ Retorna todos os elementos na árvore em um vetor da linguagem C de tamanho sendo o campo size da árvore. Se o parâmetro for nulo, a árvore for vazia ou não for possível alocar espaço para o vetor, será retornado um vetor nulo.



#endif
