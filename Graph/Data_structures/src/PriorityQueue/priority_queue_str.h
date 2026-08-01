#ifndef PRIORITY_QUEUE_STR_H
#define PRIORITY_QUEUE_STR_H

#include <stdbool.h>
#include "c_string.h"
#define PRIORITY_QUEUE_STR_DEFAULT_CAPACITY 30

// ***** OBS: Essa implementação de PriorityQueue_str tem como prioridade sempre os elementos de menor valor. *****

typedef struct PriorityQueue_str {
    String* vet;
    int capacity;
    int length;
} PriorityQueue_str;

PriorityQueue_str priority_queue_str_new_with_size(int);
// @ Inicializa uma PriorityQueue com um tamanho inicial. Se não for possível, o campo vet interno será nulo

PriorityQueue_str priority_queue_str_new_with_cvet(const String*, int);
// @ Inicializa uma PriorityQueue_str com o vetor da linguagem C do primeiro parâmetro com o seu respectivo tamamanho no segundo parâmetro. Se não for possível, o campo interno vet será nulo.

PriorityQueue_str priority_queue_str_new_with_cvet_cstr(const char**, int);
// @ Mesma ideia da função anterior, mas com o primeiro parâmetro sendo um vetor de vetor de caracteres.

PriorityQueue_str priority_queue_str_new();
// @ Inicializa uma PriorityQueue_str com o tamanho inicial sendo PRIORITY_QUEUE_STR_DEFAULT_CAPACITY. Se não for possível, o campo vet interno será nulo.

bool priority_queue_str_is_empty(const PriorityQueue_str*);
// @ Verifica se a fila de prioridade está vazia. Se o parâmetro ou o campo vet for nulo ou length for 0, será retornado true.

int priority_queue_str_size(const PriorityQueue_str*);
// @ Retorna o número de elementos da fila de prioridade. Se o parâmetro for nulo, será retornado 0.

bool priority_queue_str_enqueue(PriorityQueue_str*, const String);
// @ Insere na fila de prioridade o elemento do segundo parâmetro. Se o primeiro parâmetro for nulo, o campo vet for nulo ou não for possível realocar o campo vet interno, será retornado false.

bool priority_queue_str_enqueue_cstr(PriorityQueue_str*, const char*);
// @ Mesma ideia da função anterior, mas com o segundo parâmetro sendo um vetor de caracteres.

bool priority_queue_str_peek(const PriorityQueue_str*, String*);
// @ Retorna no segundo parâmetro o elemento no início da fila de prioridade. Se o primeiro parâmetro for nulo ou a fila for vazia, será retornado false e o segundo parâmetro não será modificado.

bool priority_queue_str_dequeue(PriorityQueue_str*, String*);
// @ Remove o elemento do início da fila de prioridade e esse elemento é retornado no segundo parâmetro. Se o primeiro parâmetro for nulo ou a fila for vazia, será retornado false e o segundo parâmetro não será modificado.

void priority_queue_str_free(PriorityQueue_str*);
// @ Libera a memória da fila de prioridade.

String priority_queue_str_to_string(const PriorityQueue_str*);
// @ Retorna uma representação da fila de prioridade como String. Se o parâmetro for nulo, a fila de prioridade for vazia ou não for possível criar a String inicial de retorno, será retornado a String "NULL".

void priority_queue_str_print(const PriorityQueue_str*);
// @ Imprime a String obtida com a função priority_queue_str_to_string().

void priority_queue_str_println(const PriorityQueue_str*);
// @ Usa a função anterior priority_queue_str_print() e imprime o caractere '\n' ao final

#endif
