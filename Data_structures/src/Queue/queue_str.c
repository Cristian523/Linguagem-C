#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "c_string.h"
#include "linked_list_str.h"
#include "queue_str.h"

Queue_str queue_str_new() {   // Inicializa uma Queue_str.
    Queue_str fila;
    fila.list =linked_list_str_new(&fila.list);
    return fila;
}

bool queue_str_is_empty(const Queue_str* fila) {    // Verifica se a fila está vazia.
    if (fila == NULL)
        return false;
    return linked_list_str_is_empty(&fila->list);
}

int queue_str_size(const Queue_str* fila) {    // Retorna o número de elementos da fila.
    if (fila == NULL)
        return 0;
    return linked_list_str_length(&fila->list);
}

bool queue_str_enqueue(Queue_str* fila, const String elemento) {   // Insere o elemento do segundo parâmetro no fim da fila
    if (fila == NULL)
        return false;
    return linked_list_str_insert_end(&fila->list, elemento);
}

bool queue_str_enqueue_cstr(Queue_str* fila, const char* caracteres) {   // Usa a função anterior 
    if (fila == NULL)
        return 0;
    return linked_list_str_insert_end_cstr(&fila->list, caracteres);
}

bool queue_str_peek(const Queue_str* fila, String* retorno) {   // Retorna no segundo parâmetro o elemento no início da fila
    if (queue_str_is_empty(fila))
        return false;
    linked_list_str_first(&fila->list, retorno);
    return true;
}

bool queue_str_dequeue(Queue_str* fila, String* retorno) {    // Remove o elemento que está no inicio da fila e o retorna no segundo parâmetro
    if (queue_str_is_empty(fila))
        return false;
    linked_list_str_first(&fila->list, retorno);
    linked_list_str_pop_first(&fila->list);
    return true;
}

void queue_str_free(Queue_str* fila) {    // Libera a memória da fila.
    if (!queue_str_is_empty(fila))
        linked_list_str_free(&fila->list);
}

String queue_str_to_string(const Queue_str* fila) {   // Retorna uma representação da fila como String
    if (queue_str_is_empty(fila))
        return string_new_with_cstr("NULL");
        
    String aux = linked_list_str_to_string(&fila->list);
    if (string_compare_cstr(&aux, "NULL") == 0) {    // se obteve falha na criação inicial
        string_free(&aux);
        return string_new_with_cstr("NULL");
    }
    
    String cadeia = string_concat_new_cstr_str("FRONT=>", &aux);
    if (string_is_empty(&cadeia)) {
        string_free(&aux);
        string_free(&cadeia);
        return string_new_with_cstr("NULL");
    }
    
    // Removendo a ultima substring "->NULL" de cadeia e colocando no lugar "=>BACK"
    for (int i = 1; i <= 6; i++)
        string_pop(&cadeia);
    string_concat_cstr(&cadeia, "=>BACK");   // Foi retirado anteriormente 6 caracteres, então repor 6 caracteres não trará problemas aqui
    string_free(&aux);
    return cadeia;
}


void queue_str_print(const Queue_str* fila) {     // Imprime na tela a String obtida pela função queue_str_to_string().
    String cadeia = queue_str_to_string(fila);
    string_print(&cadeia);
    string_free(&cadeia);
}

void queue_str_println(const Queue_str* fila) {    // Usa a função anterior queue_str_print() e imprime ao final um caractere '\n'.
    queue_str_print(fila);
    printf("\n");
}

