#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "c_string.h"
#include "linked_list.h"

static int number_comparation(tipo_linked_list a, tipo_linked_list b) {
    #if defined(TIPO_LINKED_LIST_FLOAT)
        if (fabsf(a - b) < 1e-6f) return 0;
    #elif defined(TIPO_LINKED_LIST_DOUBLE) || defined(TIPO_LINKED_LIST_DOUBLE_G)
        if (fabs(a - b) < 1e-9) return 0;
    #endif
    
    if (a < b) return -1;
    else if (a > b) return 1;
    else return 0;
}

LinkedList linked_list_new() {     // Inicializador de LinkedList
    LinkedList list;
    list.inicio = list.fim = list.atual = NULL;
    list.length = 0;
    
    return list;
}

int linked_list_length(const LinkedList* list) {    // Retorna o número de elementos 
    if (list == NULL) return 0;
    else return list->length;
}

int linked_list_size(const LinkedList* list) {    // Mesma ideia da função anterior
    if (list == NULL) return 0;
    else return list->length;
}

bool linked_list_is_empty(const LinkedList* list) {  // Verifica se é uma LinkedList vazia
    if (list == NULL || list->length == 0 || list->inicio == NULL) return true;
    else return false;
}

bool linked_list_reset(LinkedList* list) {        //  Reseta o interador interamente para apontar para o primeiro elemento da lista
    if (list == NULL || list->inicio == NULL)
        return false;
    list->atual = list->inicio;
    return true;
}

bool linked_list_has_next(const LinkedList* list) {   //  Retorna true se o campo atual tiver o ponteiro Prox diferente de nulo.
    if (list == NULL || list->inicio == NULL || list->atual == NULL || list->atual->Prox == NULL)
        return false;
    else
        return true;
}

bool linked_list_next(LinkedList* list) {   //  Retorna true se o campo atual conseguir avançar para o próximo elemento da lista
    if (linked_list_has_next(list)) {
        list->atual = list->atual->Prox;
        return true;
    }
    else
        return false;
}

bool linked_list_current(const LinkedList* list, tipo_linked_list* retorno) {   // Retorna no segundo parâmetro o elemento no ponteiro atual
    if (list == NULL || list->inicio == NULL || list->atual == NULL)
        return false;
    *retorno = list->atual->E;
    return true;
}

bool linked_list_insert_begin(LinkedList* list, tipo_linked_list x) {    // Insere o elemento no início da lista
    if (list == NULL)
        return false;
    No* novo = (No*) malloc(sizeof(No));
    if (novo == NULL)
        return false;
    novo->E = x;
    
    novo->Prox = list->inicio;
    list->inicio = novo;
    if (list->fim == NULL)
        list->fim = novo;    // O primeiro elemento é justamente o último
        
    list->length++;
    return true;
}

bool linked_list_insert_end(LinkedList* list, tipo_linked_list x) {    // Insere o elemento no fim da lista
    if (list == NULL)
        return false;
    No* novo = (No*) malloc(sizeof(No));
    if (novo == NULL)
        return false;
    novo->E = x;
    
    novo->Prox = NULL;
    if (list->inicio == NULL)   // se a lista estava vazia, então este será o primeiro elemento
        list->inicio = list->fim = novo;
    else {
        list->fim->Prox = novo;
        list->fim = novo;
    }
    
    list->length++;
    return true;
}

bool linked_list_insert_ordered(LinkedList* list, tipo_linked_list x) {    // Insere o elemento na lista de forma ordenada
    if (list == NULL)
        return false;
    No* novo = (No*) malloc(sizeof(No));
    if (novo == NULL)
        return false;
    novo->E = x;
    
    No* p = list->inicio;
    No* pAnt = NULL;
    
    while (p != NULL && number_comparation(p->E, x) < 0) {    // encontrando a posição que tem que inserir
        pAnt = p;
        p = p->Prox;
    }
    
    // Com o objetivo de não ficar confuso, decidi separar a lógica do que pode acontecer em cada caso
    if (list->inicio == NULL) {   // a lista está vazia até então, logo este será o primeiro elemento
        list->inicio = list->fim = novo;
        novo->Prox = NULL;
    }
    else if (pAnt == NULL) {     // então tem que inserir no início
        novo->Prox = list->inicio;
        list->inicio = novo;
    }
    else if (p == NULL) {  // então tem que inserir no fim
        list->fim->Prox = novo;
        list->fim = novo;
        novo->Prox = NULL;
    }
    else {  // caso mais geral
        novo->Prox = p;
        pAnt->Prox = novo;
    }
    
    list->length++;
    return true;
}

bool linked_list_first(const LinkedList* list, tipo_linked_list* retorno) {  // Retorna no segundo parâmetro o primeiro elemento da lista
    if (list == NULL || list->inicio == NULL)
        return false;
    *retorno = list->inicio->E;
    return true;
    
}

bool linked_list_last(const LinkedList* list, tipo_linked_list* retorno) {   //  Retorna no segundo parâmetro o ultimo elemento da lista.
    if (list == NULL || list->inicio == NULL)
        return false;
    *retorno = list->fim->E;
    return true;
}

bool linked_list_search(const LinkedList* list, tipo_linked_list elemento) {  //  Procura a primeira ocorrência do elemento do segundo parâmetro na lista e retorna true se conseguir encontrar.
    if (list == NULL || list->inicio == NULL)
        return false;
    
    No* p = list->inicio;
    while (p != NULL) {
        if (number_comparation(p->E, elemento) == 0)
            return true;
        else
            p = p->Prox;
    }
    return false;
    
}

int linked_list_count(const LinkedList* list, tipo_linked_list elemento) {   //  Retorna a quantidade de elementos do segundo parâmetro encontrado na lista.
    if (list == NULL || list->inicio == NULL)
        return 0;
        
    No* p = list->inicio;
    int count = 0;
    while (p != NULL) {
        if (number_comparation(p->E, elemento) == 0)
            count++;
        p = p->Prox;
    }
    return count;
}

bool linked_list_pop_first(LinkedList* list) {  //  Remove o primeiro elemento da lista
    if (list == NULL || list->inicio == NULL)
        return false;
    
    if (list->fim == list->inicio)    // então só há 1 elemento
        list->fim = NULL;
    if (list->atual != NULL && list->atual == list->inicio)    // então o ponteiro atual apontará para o próximo elemento
        list->atual = list->atual->Prox;
    
    No* antigo = list->inicio;
    list->inicio = list->inicio->Prox;
    free(antigo);
    list->length--;
    
    return true;
}

bool linked_list_pop_last(LinkedList* list) {   //  Remove o ultimo elemento da lista
    if (list == NULL || list->inicio == NULL)
        return false;
    
    No* penultimo = list->inicio;
    if (penultimo->Prox == NULL) {  // então este é o único elemento da lista
        free(penultimo);
        list->inicio = list->fim = list->atual = NULL;
    }
    else {
        while (penultimo->Prox != list->fim) 
            penultimo = penultimo->Prox;
        
        if (list->atual != NULL && list->atual == list->fim)
            list->atual = NULL;
        No* antigo = list->fim;
        list->fim = penultimo;
        list->fim->Prox = NULL;
        free(antigo);
    }
    
    list->length--;
    return true;
}

bool linked_list_pop_current(LinkedList* list) {  //  Remove o elemento que está localizado na posição do ponteiro atual
    if (list == NULL || list->inicio == NULL || list->atual == NULL)
        return false;

    if (list->inicio == list->fim) {  // Só existe 1 elemento na lista
        free(list->inicio);
        list->inicio = list->atual = list->fim = NULL;
    }
    else {
        No* p = list->inicio;
        if (list->atual == list->inicio) {   // tem mais de 1 elemento, mas o primeiro já é o elemento a ser removido
            list->inicio = list->inicio->Prox;
            No* antigo = list->atual;
            list->atual = list->inicio;
            free(antigo);
        }
        else {
            while (p->Prox != list->atual)     // procurando o elemento anterior ao atual
                p = p->Prox;
        
            if (list->fim == list->atual)    // tem mais de 1 elemento, mas o ultmo é o elemento a ser removido
                list->fim = p;      // agora o ponteiro fim aponta para o penúltimo elemento
                
            No* antigo = list->atual;
            list->atual = list->atual->Prox;
            p->Prox = list->atual;
            
            free(antigo);
        }        
    }
    
    list->length--;
    
    return true;
}

bool linked_list_remove(LinkedList* list, tipo_linked_list elemento) {  //  Remove a primeira ocorrencia do elemento do segundo parâmetro da lista.
    if (list == NULL || list->inicio == NULL)
        return false;
    
    No* p = list->inicio;
    No* pAnt = NULL;
    
    while (p != NULL && number_comparation(p->E, elemento) != 0) {
        pAnt = p;
        p = p->Prox;
    }
    
    if (p == NULL)   // então o elemento não foi encontrado
        return false;
    else {
        if (list->fim == p)   // então list->fim passará a ser o pAnt, pois p é o elemento a ser removido
            list->fim = pAnt;
        if (list->atual != NULL && list->atual == p)  // então list->atual apontará para o próximo, pois p é o elemento a ser removido
            list->atual = list->atual->Prox;
        
        
        if (pAnt != NULL)       // então o pAnt apontará para o proximo elemento que não será removido
            pAnt->Prox = p->Prox;
        else                   // então o list->inicio apontará para o próximo elemento que não será removido
            list->inicio = p->Prox;
        
        free(p);
        list->length--;
    }
    return true;
}

bool linked_list_copy(LinkedList* list1, const LinkedList* list2) {    // Copia todos os elementos da lista do segundo parâmetro para o primeiro
    if (list1 == NULL || list2 == NULL)
        return false;
      
    LinkedList aux = linked_list_new();
    
    No* p = list2->inicio;
    while (p != NULL) {
        if (!linked_list_insert_end(&aux, p->E)) {     // Se tiver problema com alocação de memória, libera toda a memória auxilar e retorna false
            linked_list_free(&aux);
            return false;
        }   
        p = p->Prox;
    }
    
    if (!linked_list_is_empty(list1))   // então libera a memória antiga
        linked_list_free(list1);
    
    // Copiando as informações obtidas
    list1->inicio = aux.inicio;
    list1->atual = aux.atual;
    list1->fim = aux.fim;
    list1->length = aux.length;
    
    return true;
}

void linked_list_free(LinkedList* list) {    // Remove todos os elementos de LinkedList. 
    if (list != NULL && list->length > 0) {
        No* antigo;
        while (list->inicio != NULL) {
            antigo = list->inicio;
            list->inicio = list->inicio->Prox;
            free(antigo);    
        }
        list->inicio = list->fim = list->atual = NULL;
        list->length = 0;
    }
}


String linked_list_to_string(const LinkedList* list) {   // Retorna uma representação de String de uma LinkedList
    String cadeia;
    if (list == NULL || list->inicio == NULL)
        return string_new_with_cstr("NULL");
    cadeia = string_new_with_size(6 * list->length + 4);   // um tamanho não muito grande, mas não muito pequeno para uma possível realocação

    if (string_is_valid(&cadeia)) {
        String elemento = string_new_empty();
        string_free(&elemento);    // liberando a memória da String representado pelo caractere '\0'
        string_append(&cadeia, '[');
        No* L = list->inicio;
        
        while (L != NULL) {
            elemento = TO_STRING_LINKED_LIST(L->E);
            if (!string_is_empty(&elemento)) {
                string_concat(&cadeia, &elemento);
                if (L->Prox != NULL)
                    string_concat_cstr(&cadeia, "]->[");
            }
            L = L->Prox;
            string_free(&elemento);
        }
        string_concat_cstr(&cadeia, "]->NULL");
    }
    else
        cadeia = string_new_with_cstr("NULL");

    return cadeia;
}

void linked_list_print(const LinkedList* list) {
    String cadeia = linked_list_to_string(list);
    string_print(&cadeia);
    string_free(&cadeia);
}

void linked_list_println(const LinkedList* list) {
    linked_list_print(list);
    printf("\n"); 
}

