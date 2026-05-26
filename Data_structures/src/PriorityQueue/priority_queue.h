#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdbool.h>
#include "c_string.h"
#define PRIORITY_QUEUE_DEFAULT_CAPACITY 50

// ***** OBS: Essa implementação de PriorityQueue tem como prioridade sempre os elementos de menor valor. *****

/* MUDE O TIPO_PRIORITY_QUEUE E A PRECISAO AQUI. NO CASO DO ÚLTIMO, A PRECISAO SERÁ USADA EM FLOAT E DOUBLE APENAS */ 
#define PRECISION_PRIORITY_QUEUE 2    // Mude a precisão de float e double aqui

//!!!!!!!!!!!!!!! Mude aqui qual tipo_priority_queue primitivo quer escolher !!!!!!!!!!!!!!!!!

// #define TIPO_PRIORITY_QUEUE_INT
// #define TIPO_PRIORITY_QUEUE_LONG
// #define TIPO_PRIORITY_QUEUE_LONG_LONG
// #define TIPO_PRIORITY_QUEUE_FLOAT
// #define TIPO_PRIORITY_QUEUE_DOUBLE
#define TIPO_PRIORITY_QUEUE_DOUBLE_G
// #define TIPO_PRIORITY_QUEUE_CHAR


#if defined(TIPO_PRIORITY_QUEUE_INT)

    typedef int tipo_priority_queue;
    #define TO_STRING_PRIORITY_QUEUE(x) string_from_int((x))

#elif defined(TIPO_PRIORITY_QUEUE_LONG)

    typedef long tipo_priority_queue;
    #define TO_STRING_PRIORITY_QUEUE(x) string_from_long((x))

#elif defined(TIPO_PRIORITY_QUEUE_LONG_LONG)

    typedef long long tipo_priority_queue;
    #define TO_STRING_PRIORITY_QUEUE(x) string_from_long_long((x))

#elif defined(TIPO_PRIORITY_QUEUE_FLOAT)

    typedef float tipo_priority_queue;
    #define TO_STRING_PRIORITY_QUEUE(x) string_from_float((x), PRECISION_PRIORITY_QUEUE)

#elif defined(TIPO_PRIORITY_QUEUE_DOUBLE)

    typedef double tipo_priority_queue;
    #define TO_STRING_PRIORITY_QUEUE(x) string_from_double((x), PRECISION_PRIORITY_QUEUE)

#elif defined(TIPO_PRIORITY_QUEUE_DOUBLE_G)

    typedef double tipo_priority_queue;
    #define TO_STRING_PRIORITY_QUEUE(x) string_from_double_g((x))

#elif defined(TIPO_PRIORITY_QUEUE_CHAR)

    typedef char tipo_priority_queue;
    #define TO_STRING_PRIORITY_QUEUE(x) string_from_char((x))

#else
      #error "Defina UM tipo_priority_queue válido em priority_queue.h"

#endif
/* MUDE O TIPO_PRIORITY_QUEUE E A PRECISAO AQUI. NO CASO DO ÚLTIMO, A PRECISAO SERÁ USADA EM FLOAT E DOUBLE APENAS */

typedef struct PriorityQueue {
    tipo_priority_queue* vet;
    int capacity;
    int length;
} PriorityQueue;

PriorityQueue priority_queue_new_with_size(int);
// @ Inicializa uma PriorityQueue com um tamanho inicial. Se não for possível, o campo vet interno será nulo

PriorityQueue priority_queue_new_with_cvet(const tipo_priority_queue*, int);
// @ Inicializa uma PriorityQueue com o vetor da linguagem C do primeiro parâmetro com o seu respectivo tamamanho no segundo parâmetro. Se não for possível, o campo interno vet será nulo.

PriorityQueue priority_queue_new();
// @ Inicializa uma PriorityQueue com o tamanho inicial sendo PRIORITY_QUEUE_DEFAULT_CAPACITY. Se não for possível, o campo vet interno será nulo.

bool priority_queue_is_empty(const PriorityQueue*);
// @ Verifica se a fila de prioridade está vazia. Se o parâmetro ou o campo vet for nulo ou length for 0, será retornado true.

int priority_queue_size(const PriorityQueue*);
// @ Retorna o número de elementos da fila de prioridade. Se o parâmetro for nulo, será retornado 0.

bool priority_queue_enqueue(PriorityQueue*, tipo_priority_queue);
// @ Insere na fila de prioridade o elemento do segundo parâmetro. Se o primeiro parâmetro for nulo, o campo vet for nulo ou não for possível realocar o campo vet interno, será retornado false.

bool priority_queue_peek(const PriorityQueue*, tipo_priority_queue*);
// @ Retorna no segundo parâmetro o elemento no início da fila de prioridade. Se o primeiro parâmetro for nulo ou a fila for vazia, será retornado false e o segundo parâmetro não será modificado.

bool priority_queue_dequeue(PriorityQueue*, tipo_priority_queue*);
// @ Remove o elemento do início da fila de prioridade e esse elemento é retornado no segundo parâmetro. Se o primeiro parâmetro for nulo ou a fila for vazia, será retornado false e o segundo parâmetro não será modificado.

void priority_queue_free(PriorityQueue*);
// @ Libera a memória da fila de prioridade.

String priority_queue_to_string(const PriorityQueue*);
// @ Retorna uma representação da fila de prioridade como String. Se o parâmetro for nulo, a fila de prioridade for vazia ou não for possível criar a String inicial de retorno, será retornado a String "NULL".

void priority_queue_print(const PriorityQueue*);
// @ Imprime a String obtida com a função priority_queue_to_string().

void priority_queue_println(const PriorityQueue*);
// @ Usa a função anterior priority_queue_print() e imprime o caractere '\n' ao final

#endif
