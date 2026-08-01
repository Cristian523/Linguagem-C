#ifndef PRIORITY_QUEUE_PQNODE_H
#define PRIORITY_QUEUE_PQNODE_H

#include <stdbool.h>
#include "c_string.h"
#include "pqnode.h"
#define PRIORITY_QUEUE_PQNODE_DEFAULT_CAPACITY 30

typedef struct PriorityQueue_pqnode {
    PQNode* vet;
    int capacity;
    int length;
} PriorityQueue_pqnode;

PriorityQueue_pqnode priority_queue_pqnode_new_with_size(int);
// @ Inicializa uma PiorityQueue_pqnode com um tamanho inicial. Se não for possível, o campo vet interno será nulo

PriorityQueue_pqnode priority_queue_pqnode_new_with_cvet(const PQNode*, int);
// @ Inicializa uma PriorityQueue_pqnode com o vetor da linguagem C do primeiro parâmetro com o seu respectivo tamamanho no segundo parâmetro. Se não for possível, o campo interno vet será nulo.

PriorityQueue_pqnode priority_queue_pqnode_new();
// @ Inicializa uma PriorityQueue_pqnode com o tamanho inicial sendo PRIORITY_QUEUE_PQNODE_DEFAULT_CAPACITY. Se não for possível, o campo vet interno será nulo.

bool priority_queue_pqnode_is_empty(const PriorityQueue_pqnode*);
// @ Verifica se a fila de prioridade está vazia. Se o parâmetro ou o campo vet for nulo ou length for 0, será retornado true.

int priority_queue_pqnode_size(const PriorityQueue_pqnode*);
// @ Retorna o número de elementos da fila de prioridade. Se o parâmetro for nulo, será retornado 0.

bool priority_queue_pqnode_enqueue(PriorityQueue_pqnode*, PQNode);
// @ Insere na fila de prioridade o elemento do segundo parâmetro. Se o primeiro parâmetro for nulo, o campo vet for nulo ou não for possível realocar o campo vet interno, será retornado false.

bool priority_queue_pqnode_enqueue_str_distance(PriorityQueue_pqnode*, const String, float);
// @ Mesma ideia da função anterior, mas com o segundo e terceiro parâmetro será criado um PQNode para a inserção na fila

bool priority_queue_pqnode_enqueue_cstr_distance(PriorityQueue_pqnode*, const char*, float);
// @ Mesma ideia da função anterior, mas com o segundo e terceiro parâmetro será criado um PQNode para a inserção na fila

bool priority_queue_pqnode_peek(const PriorityQueue_pqnode*, PQNode*);
// @ Retorna no segundo parâmetro o elemento no início da fila de prioridade. Se o primeiro parâmetro for nulo ou a fila for vazia, será retornado false e o segundo parâmetro não será modificado.

bool priority_queue_pqnode_dequeue(PriorityQueue_pqnode*, PQNode*);
// @ Remove o elemento do início da fila de prioridade e esse elemento é retornado no segundo parâmetro. Se o primeiro parâmetro for nulo ou a fila for vazia, será retornado false e o segundo parâmetro não será modificado.

void priority_queue_pqnode_free(PriorityQueue_pqnode*);
// @ Libera a memória da fila de prioridade.

String priority_queue_pqnode_to_string(const PriorityQueue_pqnode*);
// @ Retorna uma representação da fila de prioridade como String. Se o parâmetro for nulo, a fila de prioridade for vazia ou não for possível criar a String inicial de retorno, será retornado a String "NULL".

void priority_queue_pqnode_print(const PriorityQueue_pqnode*);
// @ Imprime a String obtida com a função priority_queue_pqnode_to_string().

void priority_queue_pqnode_println(const PriorityQueue_pqnode*);
// @ Usa a função anterior priority_queue_pqnode_print() e imprime o caractere '\n' ao final

#endif
