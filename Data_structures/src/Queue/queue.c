#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "c_string.h"
#include "linked_list.h"
#include "queue.h"

Queue queue_new() {     // Inicializa uma Queue.
    Queue fila;
    fila.list = linked_list_new();
    return fila;
}

bool queue_is_empty(const Queue* fila) {    // Verifica se a fila está vazia.
    if (fila == NULL)
        return false;
    return linked_list_is_empty(&fila->list);
}

int queue_size(const Queue* fila) {    // Retorna o número de elementos da fila.
    if (fila == NULL)
        return 0;
    return linked_list_length(&fila->list);
}

bool queue_enqueue(Queue* fila, tipo_linked_list elemento) {   // Insere o elemento do segundo parâmetro no fim da fila
    if (fila == NULL)
        return false;
    return linked_list_insert_end(&fila->list, elemento);
}

bool queue_peek(const Queue* fila, tipo_linked_list* retorno) {   // Retorna no segundo parâmetro o elemento no início da fila
    if (queue_is_empty(fila))
        return false;
    linked_list_first(&fila->list, retorno);
    return true;
}

bool queue_dequeue(Queue* fila, tipo_linked_list* retorno) {   // Remove o elemento que está no inicio da fila e o retorna no segundo parâmetro
    if (queue_is_empty(fila))
        return false;
    linked_list_first(&fila->list, retorno);
    linked_list_pop_first(&fila->list);
    return true;
}

void queue_free(Queue* fila) {    // Libera a memória da fila.
    if (!queue_is_empty(fila))
        linked_list_free(&fila->list);
}

String queue_to_string(const Queue* fila) {   // Retorna uma representação da fila como String
    if (queue_is_empty(fila))
        return string_new_with_cstr("NULL");
        
    String aux = linked_list_to_string(&fila->list);
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

void queue_print(const Queue* fila) {     // Imprime na tela a String obtida pela função queue_to_string().
    String cadeia = queue_to_string(fila);
    string_print(&cadeia);
    string_free(&cadeia);
}

void queue_println(const Queue* fila) {    // Usa a função anterior queue_print() e imprime ao final um caractere '\n'.
    queue_print(fila);
    printf("\n");
}

