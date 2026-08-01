#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "c_string.h"
#include "priority_queue_pqnode.h"

#define FILHO_ESQ_PQNODE(i) (2 * (i) + 1)
#define FILHO_DIR_PQNODE(i) (2 * (i) + 2)
#define PAI_PQNODE(i) (((i) - 1) / 2)

/* Funções auxiliares */
static int number_comparation(float, float);   // Comparação entre números de tipo float
static bool increase_size(PQNode**, int*);  // Realoca o tamanho do vetor
static void swap(PQNode*, PQNode*);  // Troca os valores entre os parâmetros
static void sobe_heap(PQNode*, int);   // Função auxiliar para inserção
static void desce_heap(PQNode*, int, int);  // Função auxiliar para remoção
/* Funções auxiliares */



PriorityQueue_pqnode priority_queue_pqnode_new_with_size(int n) {  // Inicializa uma PiorityQueue_pqnode com um tamanho inicial. 
    PriorityQueue_pqnode fila;
    fila.vet = (PQNode*) calloc(n, sizeof(PQNode));
    fila.capacity = fila.vet == NULL ? 0 : n;
    fila.length = 0;
    return fila;
}

PriorityQueue_pqnode priority_queue_pqnode_new_with_cvet(const PQNode* vet, int n) {  // Inicializa uma PriorityQueue_pqnode com o vetor da linguagem C do primeiro parâmetro com o seu respectivo tamamanho no segundo parâmetro. 
    PriorityQueue_pqnode fila;
    fila.vet = NULL;
    fila.capacity = fila.length = 0;
    if (vet == NULL || n <= 0)
        return fila;
    
    fila.vet = (PQNode*) malloc(n * sizeof(PQNode));
    if (fila.vet != NULL) { 
        fila.capacity = n;
        for (int i = 0; i < n; i++)
            priority_queue_pqnode_enqueue(&fila, vet[i]);
    }
    return fila;
}

PriorityQueue_pqnode priority_queue_pqnode_new() {  // Inicializa uma PriorityQueue_pqnode com o tamanho inicial sendo PRIORITY_QUEUE_PQNODE_DEFAULT_CAPACITY. 
    return priority_queue_pqnode_new_with_size(PRIORITY_QUEUE_PQNODE_DEFAULT_CAPACITY);
}

bool priority_queue_pqnode_is_empty(const PriorityQueue_pqnode* fila) {  // Verifica se a fila de prioridade está vazia.
    if (fila == NULL || fila->vet == NULL || fila->length <= 0)
        return true;
    return false;
}

int priority_queue_pqnode_size(const PriorityQueue_pqnode* fila) {  // Retorna o número de elementos da fila de prioridade. 
    if (fila == NULL || fila->vet == NULL)
        return 0;
    return fila->length;
}

bool priority_queue_pqnode_enqueue(PriorityQueue_pqnode* fila, PQNode elemento) {  // Insere na fila de prioridade o elemento do segundo parâmetro. 
    return priority_queue_pqnode_enqueue_cstr_distance(fila, string_cstr(&elemento.vertice), elemento.distancia);
}

bool priority_queue_pqnode_enqueue_str_distance(PriorityQueue_pqnode* fila, const String v, float f) {   // Mesma ideia da função anterior, mas com o segundo e terceiro parâmetro será criado um PQNode para a inserção na fila
    return priority_queue_pqnode_enqueue_cstr_distance(fila, string_cstr(&v), f);
}

bool priority_queue_pqnode_enqueue_cstr_distance(PriorityQueue_pqnode* fila, const char* v, float f) {   // Mesma ideia da função anterior, mas com o segundo e terceiro parâmetro será criado um PQNode para a inserção na fila
    if (fila == NULL || fila->vet == NULL)
        return false;
    if (fila->length >= fila->capacity) {
        if (!increase_size(&fila->vet, &fila->capacity))
            return false;
    }
    
    PQNode node = pqnode_new_cstr(v, f);
    fila->vet[fila->length] = node;
    sobe_heap(fila->vet, fila->length);
    fila->length++;
    return true;
}

bool priority_queue_pqnode_peek(const PriorityQueue_pqnode* fila, PQNode* retorno) {   // Retorna no segundo parâmetro o elemento no início da fila de prioridade. 
    if (priority_queue_pqnode_is_empty(fila))
        return false;
    pqnode_copy(retorno, &fila->vet[0]);
    return true;
}

bool priority_queue_pqnode_dequeue(PriorityQueue_pqnode* fila, PQNode* retorno) {  // Remove o elemento do início da fila de prioridade e esse elemento é retornado no segundo parâmetro. 
    if (priority_queue_pqnode_is_empty(fila))
        return false;
        
     pqnode_copy(retorno, &fila->vet[0]);
     swap(&fila->vet[0], &fila->vet[fila->length - 1]);
     pqnode_free(&fila->vet[fila->length - 1]);
     fila->length--;
     desce_heap(fila->vet, fila->length, 0);
     return true;
}

void priority_queue_pqnode_free(PriorityQueue_pqnode* fila) {  // Libera a memória da fila de prioridade.
    if (fila != NULL && fila->vet != NULL) {
        for (int i = 0; i < fila->length; i++)
            pqnode_free(&fila->vet[i]);
        free(fila->vet);
        fila->vet = NULL;
        fila->capacity = fila->length = 0;
    }
}

String priority_queue_pqnode_to_string(const PriorityQueue_pqnode* fila) {   // Retorna uma representação da fila de prioridade como String. 
    if (priority_queue_pqnode_is_empty(fila))
        return string_new_with_cstr("NULL");
    String cadeia = string_new_with_size(7 * fila->length);
    if (!string_is_valid(&cadeia))
        return string_new_with_cstr("NULL");
    
    String aux;
    string_append(&cadeia, '[');
    for (int i = 0; i < fila->length; i++) {
        aux = pqnode_to_string(&fila->vet[i]);
        string_concat(&cadeia, &aux);
        if (i < fila->length - 1)
            string_concat_cstr(&cadeia, ", ");
        string_free(&aux);
    }
    string_append(&cadeia, ']');
    return cadeia;
}

void priority_queue_pqnode_print(const PriorityQueue_pqnode* fila) {  // Imprime a String obtida com a função priority_queue_pqnode_to_string().
    String cadeia = priority_queue_pqnode_to_string(fila);
    string_print(&cadeia);
    string_free(&cadeia);
}

void priority_queue_pqnode_println(const PriorityQueue_pqnode* fila) {  // Usa a função anterior priority_queue_pqnode_print() e imprime o caractere '\n' ao final
    priority_queue_pqnode_print(fila);
    printf("\n");
}


/* Funções auxiliares */
static int number_comparation(float a, float b) {   // Comparador entre dois números float
    if (fabsf(a - b) < 1e-6f) 
        return 0;
    else if (a < b) 
        return -1;
    else 
        return 1;
}

static bool increase_size(PQNode** vet, int* n) {   // Realoca o tamanho do vetor
    int length = 2 * (*n);
    PQNode* array = (PQNode*)realloc(*vet, length * sizeof(PQNode));
    if (array == NULL)  
        return false;
    *vet = array;
    *n = length;
    return true;
}

static void swap(PQNode* a, PQNode* b) {  // Troca os valores entre os parâmetros
    PQNode aux = *a;
    *a = *b;
    *b = aux;
}

static void sobe_heap(PQNode* vet, int pos) {  // Função auxiliar para inserção
    int atual = pos;
    while (atual > 0 && number_comparation(vet[PAI_PQNODE(atual)].distancia, vet[atual].distancia) > 0) {
        swap(&vet[PAI_PQNODE(atual)], &vet[atual]);
        atual = PAI_PQNODE(atual);
    }
}

static void desce_heap(PQNode* vet, int n, int pos) {  // Função auxiliar para remoção
    int atual = pos;
    while ((FILHO_ESQ_PQNODE(atual) < n && number_comparation(vet[FILHO_ESQ_PQNODE(atual)].distancia, vet[atual].distancia) < 0) || (FILHO_DIR_PQNODE(atual) < n && number_comparation(vet[FILHO_DIR_PQNODE(atual)].distancia, vet[atual].distancia) < 0)) {
        int filho = FILHO_ESQ_PQNODE(atual);
        if (FILHO_DIR_PQNODE(atual) < n && number_comparation(vet[FILHO_DIR_PQNODE(atual)].distancia, vet[filho].distancia) < 0) 
            filho = FILHO_DIR_PQNODE(atual);
        swap(&vet[atual], &vet[filho]);
        atual = filho;
    }
}

/* Funções auxiliares */

