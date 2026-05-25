#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdbool.h>
#include "c_string.h"

/* MUDE O TIPO_AVL_TREE E A PRECISAO AQUI. NO CASO DO ÚLTIMO, A PRECISAO SERÁ USADA EM FLOAT E DOUBLE APENAS */ 
#define PRECISION_AVL_TREE 2    // Mude a precisão de float e double aqui

//!!!!!!!!!!!!!!! Mude aqui qual tipo_avl_tree primitivo quer escolher !!!!!!!!!!!!!!!!!

// #define TIPO_AVL_TREE_INT
// #define TIPO_AVL_TREE_LONG
// #define TIPO_AVL_TREE_LONG_LONG
// #define TIPO_AVL_TREE_FLOAT
// #define TIPO_AVL_TREE_DOUBLE
#define TIPO_AVL_TREE_DOUBLE_G
// #define TIPO_AVL_TREE_CHAR


#if defined(TIPO_AVL_TREE_INT)

    typedef int tipo_avl_tree;
    #define TO_STRING_AVL_TREE(x) string_from_int((x))

#elif defined(TIPO_AVL_TREE_LONG)

    typedef long tipo_avl_tree;
    #define TO_STRING_AVL_TREE(x) string_from_long((x))

#elif defined(TIPO_AVL_TREE_LONG_LONG)

    typedef long long tipo_avl_tree;
    #define TO_STRING_AVL_TREE(x) string_from_long_long((x))

#elif defined(TIPO_AVL_TREE_FLOAT)

    typedef float tipo_avl_tree;
    #define TO_STRING_AVL_TREE(x) string_from_float((x), PRECISION_TREE)

#elif defined(TIPO_AVL_TREE_DOUBLE)

    typedef double tipo_avl_tree;
    #define TO_STRING_AVL_TREE(x) string_from_double((x), PRECISION_TREE)

#elif defined(TIPO_AVL_TREE_DOUBLE_G)

    typedef double tipo_avl_tree;
    #define TO_STRING_AVL_TREE(x) string_from_double_g((x))

#elif defined(TIPO_AVL_TREE_CHAR)

    typedef char tipo_avl_tree;
    #define TO_STRING_AVL_TREE(x) string_from_char((x))

#else
      #error "Defina UM tipo_avl_tree válido em avl_tree.h"

#endif
/* MUDE O TIPO_AVL_TREE E A PRECISAO AQUI. NO CASO DO ÚLTIMO, A PRECISAO SERÁ USADA EM FLOAT E DOUBLE APENAS */


typedef struct No_avl_tree {
    tipo_avl_tree E;
    struct No_avl_tree* Esq;
    struct No_avl_tree* Dir;
    int altura;
} No_avl_tree;

typedef struct AvlTree {
    No_avl_tree* T;
    int size;
} AvlTree;



AvlTree avl_tree_new();
// @ Inicializa um tipo AvlTree.

bool avl_tree_is_empty(const AvlTree*);
// @ Verifica se é uma árvore vazia. Se o parâmetro ou o campo T for nulo, será retornado true.

int avl_tree_size(const AvlTree*);
// @ Retorna o número de elementos da árvore. Se o parâmetro for nulo, será retornado 0.

bool avl_tree_insert(AvlTree*, tipo_avl_tree);
// @ Insere o elemento do segundo parâmetro se ele não existir na árvore. Se o primeiro parâmetro for nulo ou o elemento já existir na árvore, será retornado false.

bool avl_tree_search(const AvlTree*, tipo_avl_tree);
// @ Busca se o elemento do segundo parâmetro está na árvore. Se o primeiro parâmetro for nulo, a árvore for vazia ou não encontrar o elemento, será retornado false.

bool avl_tree_remove(AvlTree*, tipo_avl_tree);
// @ Remove o elemento do terceiro parâmetro se ele estiver presente na árvore. Se o primeiro parâmetro for nulo, a árvore for vazia ou não encontrar o elemento a ser removido, será retornado false.

void avl_tree_free(AvlTree*);
// @ Libera a memória da árvore.

String avl_tree_to_string(const AvlTree*);
// @ Retorna uma representação básica dos elementos da árvore como String. Se o parâmetro for nulo, a árvore for vazia ou não for possível criar a primeira alocação da String, será retornada a String "NULL".

String avl_tree_to_string_detailed(const AvlTree*);
// @ Retorna uma representação detalhada da árvore como String, isto é, retorna todos os nós, com cada nó mostrando o elemento atual, o elemento do ponteiro Esq (se não existir ficará "NULL") e o elemento do ponteiro Dir (se não existir ficará "NULL"). Se o parâmetro for nulo, a árvore for vazia ou não for possível criar a primeira alocação da String, será retornada a String "NULL".

void avl_tree_print(const AvlTree*);
// @ Imprime a String obtida com a função avl_tree_to_string().

void avl_tree_print_detailed(const AvlTree*);
// @ Imprime a String obtida com a função avl_tree_to_string_detailed().

void avl_tree_println(const AvlTree*);
// @ Usa a função avl_tree_print() e imprime o caractere '\n' ao final.

void avl_tree_println_detailed(const AvlTree*);
// @ Usa a função avl_tree_print_detailed() e imprime o caractere '\n' ao final.

int avl_tree_no_height(const AvlTree*, tipo_avl_tree);
// @ Se o elemento do segundo parâmetro for encontrado na árvore, será retornado a sua respectiva altura; caso o contrário, será retornado -1. Se o primeiro parâmetro for nulo ou a árvore for vazia, também será retornado -1.

int avl_tree_height(const AvlTree*);
// @ Retorna a altura da árvore. Se o parâmetro for nulo ou a árvore for vazia, será retornado -1.

tipo_avl_tree* avl_tree_to_cvet(const AvlTree*);
// @ Retorna todos os elementos na árvore em um vetor da linguagem C de tamanho sendo o campo size da árvore. Se o parâmetro for nulo, a árvore for vazia ou não for possível alocar espaço para o vetor, será retornado um vetor nulo.

#endif

