#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include "c_string.h"
#include "linked_list.h"

typedef struct Queue {
    LinkedList list;
} Queue;

Queue queue_new();
// @ Inicializa uma Queue. Basicamente inicializa a LinkedList internamente

bool queue_is_empty(const Queue*);
// @ Verifica se a fila está vazia. Se o parâmetro for nulo ou a fila realmente não tiver elementos, será retornado true, caso o contrário, será retornado false.

int queue_size(const Queue*);
// @ Retorna o número de elementos da fila. Se o parâmetro for nulo ou a fila for vazia, será retornado 0.

bool queue_enqueue(Queue*, tipo_linked_list);
// @ Adiciona o elemento do segundo parâmetro no fim da fila. Se o primeiro parâmetro for nulo ou tiver problema de memória ao inserir o elemento, será retornado false.

bool queue_peek(const Queue*, tipo_linked_list*);
// @ Retorna no segundo parâmetro o elemento no inicio da fila. Se o primeiro parâmetro for nulo ou a fila for vazia, será retornado false e o segundo parâmetro não será modificado.

bool queue_dequeue(Queue*, tipo_linked_list*);
// @ Remove o elemento que está no inicio da fila e o retorna no segundo parâmetro. Se o primeiro parâmetro for nulo ou a fila for vazia, será retornado false e o segundo parâmetro não será modificado.

void queue_free(Queue*);
// @ Libera a memória da fila. Se o parâmetro for nulo ou a fila já estiver vazia, será feito nada.

String queue_to_string(const Queue*);
// @ Retorna uma representação da fila como String. Se falhar na criação da String de retorno, o parâmetro for nulo ou a fila estiver vazia, será retornado uma String como representação de que a fila é vazia, isto é, será retornado "NULL"

void queue_print(const Queue*);
// @ Imprime na tela a String obtida pela função queue_to_string().

void queue_println(const Queue*);
// @ Usa a função anterior queue_print() e imprime ao final um caractere '\n'.

#endif
