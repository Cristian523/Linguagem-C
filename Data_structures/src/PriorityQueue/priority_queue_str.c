#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "c_string.h"
#include "priority_queue_str.h"

#define FILHO_ESQ_STR(i) (2 * (i) + 1)
#define FILHO_DIR_STR(i) (2 * (i) + 2)
#define PAI_STR(i) (((i) - 1) / 2)

/* Funções auxiliares */
static bool increase_size(String**, int*);  // Realoca o tamanho do vetor
static void swap(String*, String*);  // Troca os valores entre os parâmetros
static void sobe_heap(String*, int);   // Função auxiliar para inserção
static void desce_heap(String*, int, int);  // Função auxiliar para remoção
/* Funções auxiliares */


PriorityQueue_str priority_queue_str_new_with_size(int n) {  // Inicializa uma PriorityQueue_str com um tamanho inicial
    if (n <= 0)
        n = PRIORITY_QUEUE_STR_DEFAULT_CAPACITY;
    PriorityQueue_str fila;
    fila.vet = (String*) calloc(n, sizeof(String));
    fila.capacity = fila.vet == NULL ? 0 : n;
    fila.length = 0;
    return fila;
}

PriorityQueue_str priority_queue_str_new_with_cvet(const String* vet, int n) {   // Inicializa uma PriorityQueue_str com o vetor da linguagem C do primeiro parâmetro com o seu respectivo tamamanho no segundo parâmetro.
    PriorityQueue_str fila;
    fila.vet = NULL;
    fila.capacity = fila.length = 0;
    if (vet == NULL || n <= 0)
        return fila;
    
    fila.vet = (String*) malloc(n * sizeof(String));
    if (fila.vet != NULL) { 
        fila.capacity = n;
        for (int i = 0; i < n; i++)
            priority_queue_str_enqueue(&fila, vet[i]);
    }
    return fila;
}

PriorityQueue_str priority_queue_str_new_with_cvet_cstr(const char** vet, int n) {   // Inicializa uma PriorityQueue_str com o vetor da linguagem C do primeiro parâmetro com o seu respectivo tamamanho no segundo parâmetro.
    PriorityQueue_str fila;
    fila.vet = NULL;
    fila.capacity = fila.length = 0;
    if (vet == NULL || *vet == NULL || n <= 0)
        return fila;
    
    fila.vet = (String*) malloc(n * sizeof(String));
    if (fila.vet != NULL) { 
        fila.capacity = n;
        for (int i = 0; i < n; i++)
            priority_queue_str_enqueue_cstr(&fila, vet[i]);
    }
    return fila;
}

PriorityQueue_str priority_queue_str_new() {  // Inicializa uma PriorityQueue_str com uma capacidade padrão
    return priority_queue_str_new_with_size(PRIORITY_QUEUE_STR_DEFAULT_CAPACITY);
}

bool priority_queue_str_is_empty(const PriorityQueue_str* fila) {   // Verifica se a fila de prioridade está vazia. 
    if (fila == NULL || fila->vet == NULL || fila->length <= 0)
        return true;
    return false;
}

int priority_queue_str_size(const PriorityQueue_str* fila) {  // Retorna o número de elementos da fila de prioridade.
    if (fila == NULL || fila->vet == NULL)
        return 0;
    return fila->length;
}

bool priority_queue_str_enqueue(PriorityQueue_str* fila, const String elemento) {   // Insere na fila de prioridade o elemento do segundo parâmetro.
    return priority_queue_str_enqueue_cstr(fila, string_cstr(&elemento));
}

bool priority_queue_str_enqueue_cstr(PriorityQueue_str* fila, const char* elemento) {    // Insere na fila de prioridade o elemento do segundo parâmetro.
    if (fila == NULL || fila->vet == NULL || elemento == NULL)  
        return false;
    if (fila->length >= fila->capacity) {
        if (!increase_size(&fila->vet, &fila->capacity))
            return false;
    }
    
    String aux = string_new_with_cstr(elemento);
    if (!string_is_valid(&aux))
        return false;
    fila->vet[fila->length] = aux;
    sobe_heap(fila->vet, fila->length);
    fila->length++;
    return true;
}

bool priority_queue_str_peek(const PriorityQueue_str* fila, String* retorno) {   // Retorna no segundo parâmetro o elemento no início da fila de prioridade. 
    if (priority_queue_str_is_empty(fila))
        return false;
    string_copy(retorno, &fila->vet[0]);
    return true;
}

bool priority_queue_str_dequeue(PriorityQueue_str* fila, String* retorno) {   // Remove o elemento do início da fila de prioridade e esse elemento é retornado no segundo parâmetro.
    if (priority_queue_str_is_empty(fila))
        return false;
        
     string_copy(retorno, &fila->vet[0]);
     swap(&fila->vet[0], &fila->vet[fila->length - 1]);
     string_free(&fila->vet[fila->length - 1]);
     fila->length--;
     desce_heap(fila->vet, fila->length, 0);
     return true;
}

void priority_queue_str_free(PriorityQueue_str* fila) {  // Libera a memória da fila de prioridade.
    if (fila != NULL && fila->vet != NULL) {
        for (int i = 0; i < fila->length; i++)
            string_free(&fila->vet[i]);
        free(fila->vet);
        fila->vet = NULL;
        fila->capacity = fila->length = 0;
    }
}

String priority_queue_str_to_string(const PriorityQueue_str* fila) { // Retorna uma representação da fila de prioridade como String. 
    if (priority_queue_str_is_empty(fila))
        return string_new_with_cstr("NULL");
    String cadeia = string_new_with_size(6 * fila->length);
    if (!string_is_valid(&cadeia))
        return string_new_with_cstr("NULL");
    
    string_append(&cadeia, '[');
    for (int i = 0; i < fila->length; i++) {
        string_concat(&cadeia, &fila->vet[i]);
        if (i < fila->length - 1)
            string_concat_cstr(&cadeia, ", ");
    }
    string_append(&cadeia, ']');
    return cadeia;
    
}

void priority_queue_str_print(const PriorityQueue_str* fila) {   // Imprime a String obtida com a função priority_queue_str_to_string().
    String cadeia = priority_queue_str_to_string(fila);
    string_print(&cadeia);
    string_free(&cadeia);
}

void priority_queue_str_println(const PriorityQueue_str* fila) {   // Usa a função anterior priority_queue_str_print() e imprime o caractere '\n' ao final
    priority_queue_str_print(fila);
    printf("\n");
}


/* Funções auxiliares */
static bool increase_size(String** vet, int* n) {   // Realoca o tamanho do vetor
    int length = 2 * (*n);
    String* array = (String*)realloc(*vet, length * sizeof(String));
    if (array == NULL)  
        return false;
    *vet = array;
    *n = length;
    return true;
}

static void swap(String* a, String* b) {  // Troca os valores entre os parâmetros
    String aux = *a;
    *a = *b;
    *b = aux;
}

static void sobe_heap(String* vet, int pos) {  // Função auxiliar para inserção
    int atual = pos;
    while (atual > 0 && string_compare(&vet[PAI_STR(atual)], &vet[atual]) > 0) {
        swap(&vet[PAI_STR(atual)], &vet[atual]);
        atual = PAI_STR(atual);
    }
}

static void desce_heap(String* vet, int n, int pos) {  // Função auxiliar para remoção
    int atual = pos;
    while ((FILHO_ESQ_STR(atual) < n && string_compare(&vet[FILHO_ESQ_STR(atual)], &vet[atual]) < 0) || (FILHO_DIR_STR(atual) < n && string_compare(&vet[FILHO_DIR_STR(atual)], &vet[atual]) < 0)) {
        int filho = FILHO_ESQ_STR(atual);
        if (FILHO_DIR_STR(atual) < n && string_compare(&vet[FILHO_DIR_STR(atual)], &vet[filho]) < 0) 
            filho = FILHO_DIR_STR(atual);
        swap(&vet[atual], &vet[filho]);
        atual = filho;
    }
}
/* Funções auxiliares */
