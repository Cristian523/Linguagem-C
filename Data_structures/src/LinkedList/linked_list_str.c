#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "c_string.h"
#include "linked_list_str.h"

LinkedList_str linked_list_str_new() {     // Inicializador de LinkedList_str
    LinkedList_str list;
    list.inicio = list.fim = list.atual = NULL;
    list.length = 0;
    
    return list;
}

int linked_list_str_length(const LinkedList_str* list) {    // Retorna o número de elementos 
    if (list == NULL) return 0;
    else return list->length;
}

bool linked_list_str_is_empty(const LinkedList_str* list) {  // Verifica se é uma LinkedList_str vazia
    if (list == NULL || list->length == 0 || list->inicio == NULL) return true;
    else return false;
}

bool linked_list_str_reset(LinkedList_str* list) {        //  Reseta o interador interamente para apontar para o primeiro elemento da lista
    if (list == NULL || list->inicio == NULL)
        return false;
    list->atual = list->inicio;
    return true;
}

bool linked_list_str_has_next(const LinkedList_str* list) {   //  Retorna true se o campo atual tiver o ponteiro Prox diferente de nulo.
    if (list == NULL || list->inicio == NULL || list->atual == NULL || list->atual->Prox == NULL)
        return false;
    else
        return true;
}

bool linked_list_str_next(LinkedList_str* list) {   //  Retorna true se o campo atual conseguir avançar para o próximo elemento da lista
    if (linked_list_str_has_next(list)) {
        list->atual = list->atual->Prox;
        return true;
    }
    else
        return false;
}

bool linked_list_str_current(const LinkedList_str* list, String* retorno) {   // Retorna no segundo parâmetro o elemento no ponteiro atual
    if (list == NULL || list->inicio == NULL || list->atual == NULL)
        return false;
    *retorno = string_new_empty();
    string_free(retorno);
    string_copy(retorno, &list->atual->E);
    return true;
}

bool linked_list_str_insert_begin(LinkedList_str* list, const String x) {    // Insere o elemento no início da lista
    if (list == NULL)
        return false;
    No_str* novo = (No_str*) malloc(sizeof(No_str));
    if (novo == NULL)
        return false;
    novo->E = string_new_empty();
    string_free(&novo->E);
    string_copy(&novo->E, &x);
    
    novo->Prox = list->inicio;
    list->inicio = novo;
    if (list->fim == NULL)
        list->fim = novo;    // O primeiro elemento é justamente o último
        
    list->length++;
    return true;
}

bool linked_list_str_insert_begin_cstr(LinkedList_str* list, const char* vet) {  // Usa a função anterior 
    if (list == NULL)
        return false;
    String cadeia = string_new_with_cstr(vet);
    bool logico = true;
    if (!string_is_valid(&cadeia))
        logico = false;
    else if (!linked_list_str_insert_begin(list, cadeia))
        logico = false;
    string_free(&cadeia);
    return logico;
}

bool linked_list_str_insert_end(LinkedList_str* list, const String x) {    // Insere o elemento no fim da lista
    if (list == NULL)
        return false;
    No_str* novo = (No_str*) malloc(sizeof(No_str));
    if (novo == NULL)
        return false;
    novo->E = string_new_empty();
    string_free(&novo->E);
    string_copy(&novo->E, &x);
    
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

bool linked_list_str_insert_end_cstr(LinkedList_str* list, const char* vet) {  // Usa a função anterior 
    if (list == NULL)
        return false;
    String cadeia = string_new_with_cstr(vet);
    bool logico = true;
    if (!string_is_valid(&cadeia))
        logico = false;
    else if (!linked_list_str_insert_end(list, cadeia))
        logico = false;
    string_free(&cadeia);
    return logico;
}

bool linked_list_str_insert_ordered(LinkedList_str* list, const String x) {    // Insere o elemento na lista de forma ordenada
    if (list == NULL)
        return false;
    No_str* novo = (No_str*) malloc(sizeof(No_str));
    if (novo == NULL)
        return false;
    novo->E = string_new_empty();
    string_free(&novo->E);
    string_copy(&novo->E, &x);
    
    No_str* p = list->inicio;
    No_str* pAnt = NULL;
    
    while (p != NULL && string_compare(&p->E, &x) < 0) {    // encontrando a posição que tem que inserir
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

bool linked_list_str_insert_ordered_cstr(LinkedList_str* list, const char* vet) {  // Usa a função anterior 
    if (list == NULL)
        return false;
    String cadeia = string_new_with_cstr(vet);
    bool logico = true;
    if (!string_is_valid(&cadeia))
        logico = false;
    else if (!linked_list_str_insert_ordered(list, cadeia))
        logico = false;
    string_free(&cadeia);
    return logico;
}

bool linked_list_str_first(const LinkedList_str* list, String* retorno) {  // Retorna no segundo parâmetro o primeiro elemento da lista
    if (list == NULL || list->inicio == NULL)
        return false;
    *retorno = string_new_empty();
    string_free(retorno);
    string_copy(retorno, &list->inicio->E);
    return true;
    
}

bool linked_list_str_last(const LinkedList_str* list, String* retorno) {   //  Retorna no segundo parâmetro o ultimo elemento da lista.
    if (list == NULL || list->inicio == NULL)
        return false;
    *retorno = string_new_empty();
    string_free(retorno);
    string_copy(retorno, &list->fim->E);
    return true;
}

bool linked_list_str_search(const LinkedList_str* list, String elemento) {  //  Procura a primeira ocorrência do elemento do segundo parâmetro na lista e retorna true se conseguir encontrar.
    if (list == NULL || list->inicio == NULL)
        return false;
    
    No_str* p = list->inicio;
    while (p != NULL) {
        if (string_compare(&p->E, &elemento) == 0)
            return true;
        else
            p = p->Prox;
    }
    return false;
    
}

bool linked_list_str_search_cstr(const LinkedList_str* list, const char* vet) {  // Usa a função anterior 
    if (list == NULL || list->inicio == NULL)
        return false;
    String cadeia = string_new_with_cstr(vet);
    bool logico = true;
    if (!string_is_valid(&cadeia))
        logico = false;
    else if (!linked_list_str_search(list, cadeia))
        logico = false;
    string_free(&cadeia);
    return logico;
}

int linked_list_str_count(const LinkedList_str* list, String elemento) {   //  Retorna a quantidade de elementos do segundo parâmetro encontrado na lista.
    if (list == NULL || list->inicio == NULL)
        return 0;
        
    No_str* p = list->inicio;
    int count = 0;
    while (p != NULL) {
        if (string_compare(&p->E, &elemento) == 0)
            count++;
        p = p->Prox;
    }
    return count;
}

int linked_list_str_count_cstr(const LinkedList_str* list, const char* vet) {  // Usa a função anterior 
    if (list == NULL || list->inicio == NULL)
        return false;
    String cadeia = string_new_with_cstr(vet);
    bool logico = true;
    if (!string_is_valid(&cadeia))
        logico = false;
    else if (!linked_list_str_count(list, cadeia))
        logico = false;
    string_free(&cadeia);
    return logico;
}

bool linked_list_str_pop_first(LinkedList_str* list) {  //  Remove o primeiro elemento da lista
    if (list == NULL || list->inicio == NULL)
        return false;
    
    if (list->fim == list->inicio)    // então só há 1 elemento
        list->fim = NULL;
    if (list->atual != NULL && list->atual == list->inicio)    // então o ponteiro atual apontará para o próximo elemento
        list->atual = list->atual->Prox;
    
    No_str* antigo = list->inicio;
    list->inicio = list->inicio->Prox;
    string_free(&antigo->E);    // libera a memória da String antes de liberar a memória do ponteiro
    free(antigo);
    list->length--;
    
    return true;
}

bool linked_list_str_pop_last(LinkedList_str* list) {   //  Remove o ultimo elemento da lista
    if (list == NULL || list->inicio == NULL)
        return false;
    
    No_str* penultimo = list->inicio;
    if (penultimo->Prox == NULL) {  // então este é o único elemento da lista
        string_free(&penultimo->E);   // libera a memória da String antes de liberar a memória do ponteiro
        free(penultimo);
        list->inicio = list->fim = list->atual = NULL;
    }
    else {
        while (penultimo->Prox != list->fim) 
            penultimo = penultimo->Prox;
        
        if (list->atual != NULL && list->atual == list->fim)
            list->atual = NULL;
        No_str* antigo = list->fim;
        list->fim = penultimo;
        list->fim->Prox = NULL;
        string_free(&antigo->E);   // libera a memória da String antes de liberar a memória do ponteiro
        free(antigo);
    }
    
    list->length--;
    return true;
}

bool linked_list_str_pop_current(LinkedList_str* list) {  //  Remove o elemento que está localizado na posição do ponteiro atual
    if (list == NULL || list->inicio == NULL || list->atual == NULL)
        return false;

    if (list->inicio == list->fim) {  // Só existe 1 elemento na lista
        string_free(&list->inicio->E);   // libera a memória da String antes de liberar a memória do ponteiro
        free(list->inicio);
        list->inicio = list->atual = list->fim = NULL;
    }
    else {
        No_str* p = list->inicio;
        if (list->atual == list->inicio) {   // tem mais de 1 elemento, mas o primeiro já é o elemento a ser removido
            list->inicio = list->inicio->Prox;
            No_str* antigo = list->atual;
            list->atual = list->inicio;
            string_free(&antigo->E);   // libera a memória da String antes de liberar a memória do ponteiro
            free(antigo);
        }
        else {
            while (p->Prox != list->atual)     // procurando o elemento anterior ao atual
                p = p->Prox;
        
            if (list->fim == list->atual)    // tem mais de 1 elemento, mas o ultmo é o elemento a ser removido
                list->fim = p;      // agora o ponteiro fim aponta para o penúltimo elemento
                
            No_str* antigo = list->atual;
            list->atual = list->atual->Prox;
            p->Prox = list->atual;
            string_free(&antigo->E);   // libera a memória da String antes de liberar a memória do ponteiro
            free(antigo);
        }        
    }
    
    list->length--;
    
    return true;
}

bool linked_list_str_remove(LinkedList_str* list, String elemento) {  //  Remove a primeira ocorrencia do elemento do segundo parâmetro da lista.
    if (list == NULL || list->inicio == NULL)
        return false;
    
    No_str* p = list->inicio;
    No_str* pAnt = NULL;
    
    while (p != NULL && string_compare(&p->E, &elemento) != 0) {
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
        
        string_free(&p->E);   // libera a memória da String antes de liberar a memória do ponteiro
        free(p);
        list->length--;
    }
    return true;
}

bool linked_list_str_remove_cstr(LinkedList_str* list, const char* vet) {  // Usa a função anterior 
    if (list == NULL || list->inicio == NULL)
        return false;
    String cadeia = string_new_with_cstr(vet);
    bool logico = true;
    if (!string_is_valid(&cadeia))
        logico = false;
    else if (!linked_list_str_remove(list, cadeia))
        logico = false;
    string_free(&cadeia);
    return logico;
}

bool linked_list_str_copy(LinkedList_str* list1, const LinkedList_str* list2) {    // Copia todos os elementos da lista do segundo parâmetro para o primeiro
    if (list1 == NULL || list2 == NULL)
        return false;
      
    LinkedList_str aux = linked_list_str_new();
    
    No_str* p = list2->inicio;
    while (p != NULL) {
        if (!linked_list_str_insert_end(&aux, p->E)) {     // Se tiver problema com alocação de memória, libera toda a memória auxilar e retorna false
            linked_list_str_free(&aux);
            return false;
        }   
        p = p->Prox;
    }
    
    if (!linked_list_str_is_empty(list1))   // então libera a memória antiga
        linked_list_str_free(list1);
    
    // Copiando as informações obtidas
    list1->inicio = aux.inicio;
    list1->atual = aux.atual;
    list1->fim = aux.fim;
    list1->length = aux.length;
    
    return true;
}

void linked_list_str_free(LinkedList_str* list) {    // Remove todos os elementos de LinkedList_str. 
    if (list != NULL && list->length > 0) {
        No_str* antigo;
        while (list->inicio != NULL) {
            antigo = list->inicio;
            list->inicio = list->inicio->Prox;
            string_free(&antigo->E);       // Liberando a memória da String antes de liberar a memória do No
            free(antigo);    
        }
        list->inicio = list->fim = list->atual = NULL;
        list->length = 0;
    }
}


String linked_list_str_to_string(const LinkedList_str* list) {   // Retorna uma representação de String de uma LinkedList_str
    String cadeia;
    if (list == NULL || list->inicio == NULL)
        return string_new_with_cstr("NULL");
    cadeia = string_new_with_size(6 * list->length + 4);   // um tamanho não muito grande, mas não muito pequeno para uma possível realocação

    if (string_is_valid(&cadeia)) {
        String elemento = string_new_empty();
        string_free(&elemento);    // liberando a memória da String representado pelo caractere '\0'
        string_append(&cadeia, '[');
        No_str* L = list->inicio;
        
        while (L != NULL) {
            string_copy(&elemento, &L->E);
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

void linked_list_str_print(const LinkedList_str* list) {
    String cadeia = linked_list_str_to_string(list);
    string_print(&cadeia);
    string_free(&cadeia);
}

void linked_list_str_println(const LinkedList_str* list) {
    linked_list_str_print(list);
    printf("\n"); 
}

