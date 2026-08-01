#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "c_string.h"
#include "priority_queue.h"

#define FILHO_ESQ(i) (2 * (i) + 1)
#define FILHO_DIR(i) (2 * (i) + 2)
#define PAI(i) (((i) - 1) / 2)

/* Funções auxiliares */
static int number_comparation(tipo_priority_queue, tipo_priority_queue);  // Comparação entre números
static bool increase_size(tipo_priority_queue**, int*);  // Realoca o tamanho do vetor
static void swap(tipo_priority_queue*, tipo_priority_queue*);  // Troca os valores entre os parâmetros
static void sobe_heap(tipo_priority_queue*, int);   // Função auxiliar para inserção
static void desce_heap(tipo_priority_queue*, int, int);  // Função auxiliar para remoção
/* Funções auxiliares */


PriorityQueue priority_queue_new_with_size(int n) {  // Inicializa uma PriorityQueue com um tamanho inicial
    if (n <= 0)
        n = PRIORITY_QUEUE_DEFAULT_CAPACITY;
    PriorityQueue fila;
    fila.vet = (tipo_priority_queue*) calloc(n, sizeof(tipo_priority_queue));
    fila.capacity = fila.vet == NULL ? 0 : n;
    fila.length = 0;
    return fila;
}

PriorityQueue priority_queue_new_with_cvet(const tipo_priority_queue* vet, int n) {   // Inicializa uma PriorityQueue com o vetor da linguagem C do primeiro parâmetro com o seu respectivo tamamanho no segundo parâmetro.
    PriorityQueue fila;
    fila.vet = NULL;
    fila.capacity = fila.length = 0;
    if (vet == NULL || n <= 0)
        return fila;
    
    fila.vet = (tipo_priority_queue*) malloc(n * sizeof(tipo_priority_queue));
    if (fila.vet != NULL) { 
        fila.capacity = n;
        for (int i = 0; i < n; i++)
            priority_queue_enqueue(&fila, vet[i]);
    }
    return fila;
}

PriorityQueue priority_queue_new() {  // Inicializa uma PriorityQueue com uma capacidade padrão
    return priority_queue_new_with_size(PRIORITY_QUEUE_DEFAULT_CAPACITY);
}

bool priority_queue_is_empty(const PriorityQueue* fila) {   // Verifica se a fila de prioridade está vazia. 
    if (fila == NULL || fila->vet == NULL || fila->length <= 0)
        return true;
    return false;
}

int priority_queue_size(const PriorityQueue* fila) {  // Retorna o número de elementos da fila de prioridade.
    if (fila == NULL || fila->vet == NULL)
        return 0;
    return fila->length;
}

bool priority_queue_enqueue(PriorityQueue* fila, tipo_priority_queue elemento) {   // Insere na fila de prioridade o elemento do segundo parâmetro.
    if (fila == NULL || fila->vet == NULL)
        return false;
    if (fila->length >= fila->capacity) {
        if (!increase_size(&fila->vet, &fila->capacity))
            return false;
    }
    
    fila->vet[fila->length] = elemento;
    sobe_heap(fila->vet, fila->length);
    fila->length++;
    return true;
}

bool priority_queue_peek(const PriorityQueue* fila, tipo_priority_queue* retorno) {   // Retorna no segundo parâmetro o elemento no início da fila de prioridade. 
    if (priority_queue_is_empty(fila))
        return false;
    tipo_priority_queue aux = fila->vet[0];
    *retorno = aux;
    return true;
}

bool priority_queue_dequeue(PriorityQueue* fila, tipo_priority_queue* retorno) {   // Remove o elemento do início da fila de prioridade e esse elemento é retornado no segundo parâmetro.
    if (priority_queue_is_empty(fila))
        return false;
        
     tipo_priority_queue aux = fila->vet[0];
     *retorno = aux;
     swap(&fila->vet[0], &fila->vet[fila->length - 1]);
     fila->length--;
     desce_heap(fila->vet, fila->length, 0);
     return true;
}

void priority_queue_free(PriorityQueue* fila) {  // Libera a memória da fila de prioridade.
    if (fila != NULL && fila->vet != NULL) {
        free(fila->vet);
        fila->vet = NULL;
        fila->capacity = fila->length = 0;
    }
}

String priority_queue_to_string(const PriorityQueue* fila) { // Retorna uma representação da fila de prioridade como String. 
    if (priority_queue_is_empty(fila))
        return string_new_with_cstr("NULL");
    String cadeia = string_new_with_size(4 * fila->length);
    if (!string_is_valid(&cadeia))
        return string_new_with_cstr("NULL");
    
    string_append(&cadeia, '[');
    String aux_num;
    for (int i = 0; i < fila->length; i++) {
        aux_num = TO_STRING_PRIORITY_QUEUE(fila->vet[i]);
        string_concat(&cadeia, &aux_num);
        if (i < fila->length - 1)
            string_concat_cstr(&cadeia, ", ");
        string_free(&aux_num);
    }
    string_append(&cadeia, ']');
    return cadeia;
    
}

void priority_queue_print(const PriorityQueue* fila) {   // Imprime a String obtida com a função priority_queue_to_string().
    String cadeia = priority_queue_to_string(fila);
    string_print(&cadeia);
    string_free(&cadeia);
}

void priority_queue_println(const PriorityQueue* fila) {   // Usa a função anterior priority_queue_print() e imprime o caractere '\n' ao final
    priority_queue_print(fila);
    printf("\n");
}


/* Funções auxiliares */
static int number_comparation(tipo_priority_queue a, tipo_priority_queue b) {     // Comparação entre números
    #if defined(TIPO_PRIORITY_QUEUE_FLOAT)
        if (fabsf(a - b) < 1e-6f) return 0;
    #elif defined(TIPO_PRIORITY_QUEUE_DOUBLE) || defined(TIPO_PRIORITY_QUEUE_DOUBLE_G)
        if (fabs(a - b) < 1e-9) return 0;
    #endif
    
    if (a < b) return -1;
    else if (a > b) return 1;
    else return 0;
}

static bool increase_size(tipo_priority_queue** vet, int* n) {   // Realoca o tamanho do vetor
    int length = 2 * (*n);
    tipo_priority_queue* array = (tipo_priority_queue*)realloc(*vet, length * sizeof(tipo_priority_queue));
    if (array == NULL)  
        return false;
    *vet = array;
    *n = length;
    return true;
}

static void swap(tipo_priority_queue* a, tipo_priority_queue* b) {  // Troca os valores entre os parâmetros
    tipo_priority_queue aux = *a;
    *a = *b;
    *b = aux;
}

static void sobe_heap(tipo_priority_queue* vet, int pos) {  // Função auxiliar para inserção
    int atual = pos;
    while (atual > 0 && number_comparation(vet[PAI(atual)], vet[atual]) > 0) {
        swap(&vet[PAI(atual)], &vet[atual]);
        atual = PAI(atual);
    }
}

static void desce_heap(tipo_priority_queue* vet, int n, int pos) {  // Função auxiliar para remoção
    int atual = pos;
    while ((FILHO_ESQ(atual) < n && number_comparation(vet[FILHO_ESQ(atual)], vet[atual]) < 0) || (FILHO_DIR(atual) < n && number_comparation(vet[FILHO_DIR(atual)], vet[atual]) < 0)) {
        int filho = FILHO_ESQ(atual);
        if (FILHO_DIR(atual) < n && number_comparation(vet[FILHO_DIR(atual)], vet[filho]) < 0) 
            filho = FILHO_DIR(atual);
        swap(&vet[atual], &vet[filho]);
        atual = filho;
    }
}
/* Funções auxiliares */

