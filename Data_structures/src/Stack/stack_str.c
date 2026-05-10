#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "c_string.h"
#include "linked_list_str.h"
#include "stack_str.h"

Stack_str stack_str_new() {   // @ Inicializa uma Stack_str.
    Stack_str pilha;
    pilha.list = linked_list_str_new();
    return pilha;
}

bool stack_str_is_empty(const Stack_str* pilha) {   // Verifica se a pilha está vazia.
    if (pilha == NULL)
        return false;
    return linked_list_str_is_empty(&pilha->list);
}

int stack_str_size(const Stack_str* pilha) {   // Retorna o número de elementos da pilha.
    if (pilha == NULL)
        return false;
    return linked_list_str_length(&pilha->list);
}

bool stack_str_push(Stack_str* pilha, const String elemento) {  // Adiciona na pilha o elemento do segundo parâmetro no topo
    if (pilha == NULL)
        return false;
    return linked_list_str_insert_begin(&pilha->list, elemento);
}

bool stack_str_push_cstr(Stack_str* pilha, const char* caracteres) { 
    if (pilha == NULL)
        return false;
    return linked_list_str_insert_begin_cstr(&pilha->list, caracteres);
}

bool stack_str_peek(const Stack_str* pilha, String* retorno) {   // Retorna no segundo parâmetro o elemento no topo da pilha. 
    if (stack_str_is_empty(pilha))
        return false;
    linked_list_str_first(&pilha->list, retorno);
    return true;
}

bool stack_str_pop(Stack_str* pilha, String* retorno) {    // Remove o elemento que está no topo da pilha.
    if (stack_str_is_empty(pilha))
        return false;
    linked_list_str_first(&pilha->list, retorno);
    linked_list_str_pop_first(&pilha->list);
    return true;
}

void stack_str_free(Stack_str* pilha) {   // Libera a memória da pilha.
    if (!stack_str_is_empty(pilha))
        linked_list_str_free(&pilha->list);
}

String stack_str_to_string(const Stack_str* pilha) {
    if (stack_str_is_empty(pilha))
        return string_new_with_cstr("NULL");
        
    String aux = linked_list_str_to_string(&pilha->list);
    if (string_compare_cstr(&aux, "NULL") == 0) {    // se obteve falha na criação inicial
        string_free(&aux);
        return string_new_with_cstr("NULL");
    }
    
    String cadeia = string_concat_new_cstr_str("TOP=>", &aux);
    if (string_is_empty(&cadeia)) {
        string_free(&aux);
        string_free(&cadeia);
        return string_new_with_cstr("NULL");
    }
    
    string_free(&aux);
    return cadeia;
}

void stack_str_print(const Stack_str* pilha) {    // Imprime na tela a String obtida pela função stack_to_string().
    String aux = stack_str_to_string(pilha);
    string_print(&aux);
    string_free(&aux);
}

void stack_str_println(const Stack_str* pilha) {  // Usa a função anterior stack_print() e imprime ao final um caractere '\n'.
    stack_str_print(pilha);
    printf("\n");
}


