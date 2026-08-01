#ifndef QUEUE_STR_H
#define QUEUE_STR_H

#include <stdbool.h>
#include "c_string.h"
#include "linked_list_str.h"

typedef struct Queue_str {
    LinkedList_str list;
} Queue_str;

Queue_str queue_str_new();
// @ Inicializa uma Queue_str. Basicamente inicializa a LinkedList_str internamente

bool queue_str_is_empty(const Queue_str*);
// @ Verifica se a fila está vazia. Se o parâmetro for nulo ou a fila realmente não tiver elementos, será retornado true, caso o contrário, será retornado false.

int queue_str_size(const Queue_str*);
// @ Retorna o número de elementos da fila. Se o parâmetro for nulo ou a fila for vazia, será retornado 0.

bool queue_str_enqueue(Queue_str*, const String);
// @ Adiciona o elemento do segundo parâmetro no fim da fila. Se o primeiro parâmetro for nulo ou tiver problema de memória ao inserir o elemento, será retornado false.

bool queue_str_enqueue_cstr(Queue_str*, const char*);
// @ Usa a função anterior queue_str_enqueue() com o segundo parâmetro sendo passado uma conversão provisória do vetor de caracteres para String. Se essa conversão falhar ou obtiver qualquer outro problema com a função anterior, será retornado false.

bool queue_str_peek(const Queue_str*, String*);
// @ Retorna no segundo parâmetro o elemento no inicio da fila. Se o primeiro parâmetro for nulo ou a fila for vazia, será retornado false e o segundo parâmetro não será modificado.

bool queue_str_dequeue(Queue_str*, String*);
// @ Remove o elemento que está no inicio da fila e o retorna no segundo parâmetro. Se o primeiro parâmetro for nulo ou a fila for vazia, será retornado false e o segundo parâmetro não será modificado.

void queue_str_free(Queue_str*);
// @ Libera a memória da fila. Se o parâmetro for nulo ou a fila já estiver vazia, será feito nada.

String queue_str_to_string(const Queue_str*);
// @ Retorna uma representação da fila como String. Se falhar na criação da String de retorno, o parâmetro for nulo ou a fila estiver vazia, será retornado uma String como representação de que a fila é vazia, isto é, será retornado "NULL"

void queue_str_print(const Queue_str*);
// @ Imprime na tela a String obtida pela função queue_str_to_string().

void queue_str_println(const Queue_str*);
// @ Usa a função anterior queue_str_print() e imprime ao final um caractere '\n'.

#endif
