#ifndef STACK_STR_H
#define STACK_STR_H

#include <stdbool.h>
#include "c_string.h"
#include "linked_list_str.h"

typedef struct Stack_str {
    LinkedList_str list;
} Stack_str;


Stack_str stack_str_new();
// @ Inicializa uma Stack_str. Basicamente inicializa a LinkedList_str internamente

bool stack_str_is_empty(const Stack_str*);
// @ Verifica se a pilha está vazia. Se o parâmetro for nulo ou a pilha realmente não tiver elementos, será retornado true, caso o contrário, será retornado false.

int stack_str_size(const Stack_str*);
// @ Retorna o número de elementos da pilha. Se o parâmetro for nulo ou a pilha for vazia, será retornado 0.

bool stack_str_push(Stack_str*, const String);
// @ Adiciona na pilha o elemento no segundo parâmetro como cópia. Se o primeiro parâmetro for nulo ou tiver problema de memória ao inserir o elemento, será retornado false e o segundo parâmetro não será modificado.

bool stack_str_push_cstr(Stack_str*, const char*);
// @ Usa a função anterior stack_str_push() com o segundo parâmetro sendo passado uma conversão provisória do vetor de caracteres para String. Se essa conversão falhar ou obtiver qualquer outro problema com a função anterior, será retornado false.

bool stack_str_peek(const Stack_str*, String*);
// @ Retorna no segundo parâmetro o elemento no topo da pilha como cópia. Se o primeiro parâmetro for nulo ou a pilha for vazia, será retornado false.

bool stack_str_pop(Stack_str*, String*);
// @ Remove o elemento que está no topo da pilha e o retorna no segundo parâmetro como cópia. Se o primeiro parâmetro for nulo ou a pilha for vazia, será retornado false e o segundo parâmetro não será modificado.

void stack_str_free(Stack_str*);
// @ Libera a memória da pilha. Se o parâmetro for nulo ou a pilha já estiver vazia, será feito nada.

String stack_str_to_string(const Stack_str*);
// @ Retorna uma representação da pilha como String. Se falhar na criação da String de retorno, o parâmetro for nulo ou a pilha estiver vazia, será retornado uma String como representação de que a pilha é vazia, isto é, será retornado "NULL"

void stack_str_print(const Stack_str*);
// @ Imprime na tela a String obtida pela função stack_str_to_string().

void stack_str_println(const Stack_str*);
// @ Usa a função anterior stack_str_print() e imprime ao final um caractere '\n'.

#endif
