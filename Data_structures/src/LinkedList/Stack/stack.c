#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "c_string.h"
#include "linked_list.h"
#include "stack.h"

Stack stack_new() {   // Inicializa uma Stack.
    Stack pilha;
    pilha.list = linked_list_new();
    return pilha;
}

bool stack_is_empty(const Stack* pilha) {   // Verifica se a pilha está vazia.
    if (pilha == NULL)
        return false;
    return linked_list_is_empty(&pilha->list);
}

int stack_size(const Stack* pilha) {   // Retorna o número de elementos da pilha.
    if (pilha == NULL)
        return 0;
    return linked_list_length(&pilha->list);
}

bool stack_push(Stack* pilha, tipo_linked_list elemento) {  // Adiciona na pilha o elemento do segundo parâmetro no topo
    if (pilha == NULL)
        return false;
    return linked_list_insert_begin(&pilha->list, elemento);
}

bool stack_peek(const Stack* pilha, tipo_linked_list* retorno) {   // Retorna no segundo parâmetro o elemento no topo da pilha. 
    if (stack_is_empty(pilha))
        return false;
    linked_list_first(&pilha->list, retorno);
    return true;
}

bool stack_pop(Stack* pilha, tipo_linked_list* retorno) {    // Remove o elemento que está no topo da pilha.
    if (stack_is_empty(pilha))
        return false;
    linked_list_first(&pilha->list, retorno);
    linked_list_pop_first(&pilha->list);
    return true;
}

void stack_free(Stack* pilha) {   // Libera a memória da pilha.
    if (!stack_is_empty(pilha))
        linked_list_free(&pilha->list);
}

String stack_to_string(const Stack* pilha) {
    if (stack_is_empty(pilha))
        return string_new_with_cstr("NULL");
        
    String aux = linked_list_to_string(&pilha->list);
    
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

void stack_print(const Stack* pilha) {    // Imprime na tela a String obtida pela função stack_to_string().
    String aux = stack_to_string(pilha);
    string_print(&aux);
    string_free(&aux);
}

void stack_println(const Stack* pilha) {  // Usa a função anterior stack_print() e imprime ao final um caractere '\n'.
    stack_print(pilha);
    printf("\n");
}
