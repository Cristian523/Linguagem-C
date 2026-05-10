#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include "c_string.h"
#include "linked_list.h"

typedef struct Stack {
    LinkedList list;
} Stack;


Stack stack_new();
// @ Inicializa uma Stack. Basicamente inicializa a LinkedList internamente

bool stack_is_empty(const Stack*);
// @ Verifica se a pilha está vazia. Se o parâmetro for nulo ou a pilha realmente não tiver elementos, será retornado true, caso o contrário, será retornado false.

int stack_size(const Stack*);
// @ Retorna o número de elementos da pilha. Se o parâmetro for nulo ou a pilha for vazia, será retornado 0.

bool stack_push(Stack*, tipo_linked_list);
// @ Adiciona na pilha o elemento no segundo parâmetro no topo. Se o primeiro parâmetro for nulo ou tiver problema de memória ao inserir o elemento, será retornado false.

bool stack_peek(const Stack*, tipo_linked_list*);
// @ Retorna no segundo parâmetro o elemento no topo da pilha. Se o primeiro parâmetro for nulo ou a pilha for vazia, será retornado false e o segundo parâmetro não será modificado.

bool stack_pop(Stack*, tipo_linked_list*);
// @ Remove o elemento que está no topo da pilha e o retorna no segundo parâmetro. Se o primeiro parâmetro for nulo ou a pilha for vazia, será retornado false e o segundo parâmetro não será modificado.

void stack_free(Stack*);
// @ Libera a memória da pilha. Se o parâmetro for nulo ou a pilha já estiver vazia, será feito nada.

String stack_to_string(const Stack*);
// @ Retorna uma representação da pilha como String. Se falhar na criação da String de retorno, o parâmetro for nulo ou a pilha estiver vazia, será retornado uma String como representação de que a pilha é vazia, isto é, será retornado "NULL"

void stack_print(const Stack*);
// @ Imprime na tela a String obtida pela função stack_to_string().

void stack_println(const Stack*);
// @ Usa a função anterior stack_print() e imprime ao final um caractere '\n'.

#endif
