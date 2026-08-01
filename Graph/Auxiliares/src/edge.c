#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include "c_string.h"
#include "edge.h"

static int number_comparation(float a, float b) {   // Comparador entre dois números float
    if (fabsf(a - b) < 1e-6f) 
        return 0;
    else if (a < b) 
        return -1;
    else 
        return 1;
}

Edge edge_new_empty() {   // Cria um tipo vazio
    Edge aresta;
    aresta.u = string_new_empty();
    aresta.v = string_new_empty();
    aresta.peso = 0;
    aresta.direcionado = false;
    return aresta;
}

Edge edge_new(const String a, const String b, float peso, bool dir) {      // Inicializa um novo tipo Edge
    return edge_new_cstr_cstr(string_cstr(&a), string_cstr(&b), peso, dir);
}

Edge edge_new_cstr_cstr(const char* a, const char* b, float peso, bool dir) {    // Inicializa um novo tipo Edge
    Edge aresta;
    String temp1 = string_new_empty();     String temp2 = string_new_empty();
    string_copy_cstr(&temp1, a);    string_copy_cstr(&temp2, b);
    
    if (dir) {
        aresta.u = temp1;   aresta.v = temp2;
    }
    else {
        if (string_compare(&temp1, &temp2) <= 0) {
            aresta.u = temp1;   aresta.v = temp2;
        }
        else {
            aresta.u = temp2;   aresta.v = temp1;
        }
    }
    
    aresta.peso = peso;
    aresta.direcionado = dir;
    return aresta;
}

void edge_free(Edge* aresta) {   // Libera a memória do conteúdo da aresta
    if (aresta != NULL) {
        string_free(&aresta->u);
        string_free(&aresta->v);
    }
}

bool edge_copy(Edge* aresta1, const Edge* aresta2) {   // Copia os dados do segundo parâmetro para o primeiro
    if (aresta1 == NULL || aresta2 == NULL)
        return false;
    
    String cadeia1 = string_new_empty();    string_copy(&cadeia1, &aresta2->u);
    if (!string_is_valid(&cadeia1)) 
        return false;
    
    String cadeia2 = string_new_empty();    string_copy(&cadeia2, &aresta2->v);
    if (!string_is_valid(&cadeia2)) {
        string_free(&cadeia1);
        return false;
    }
    
    edge_free(aresta1);
    aresta1->u = cadeia1;
    aresta1->v = cadeia2;
    aresta1->peso = aresta2->peso;
    aresta1->direcionado = aresta2->direcionado;
    return true;
}

int edge_compare_n(const Edge* aresta1, const Edge* aresta2) {   // Comparação entre arestas por nome
    if (aresta1 == NULL || aresta2 == NULL)
        return INT_MIN;  // retornando um número sem sentido
    return edge_compare_n_cstr_cstr(aresta1, string_cstr(&aresta2->u), string_cstr(&aresta2->v), aresta2->direcionado);
}

int edge_compare_n_cstr_cstr(const Edge* aresta, const char* u1, const char* u2, bool dir) {  // Comparação de uma aresta com uma (possível) aresta
    if (aresta == NULL)
        return INT_MIN;   // retornando um número sem sentido
    
    const char* aux1 = u1;
    const char* aux2 = u2;
    if (!dir && strcmp(aux1, aux2) > 0) {
        const char* temp = aux1;
        aux1 = aux2;
        aux2 = temp;
    }
    
    
    int i1 = string_compare_cstr(&aresta->u, aux1);
    int i2 = string_compare_cstr(&aresta->v, aux2);
    
    if (i1 < 0) return -1;
    else if (i1 > 0) return 1;
    else {
        if (i2 < 0) return -1;
        else if (i2 > 0) return 1;
        else return 0;
    }
}

int edge_compare_w(const Edge* aresta1, const Edge* aresta2) {
    if (aresta1 == NULL || aresta2 == NULL)
        return INT_MIN;  // retornando um número sem sentido
    return number_comparation(aresta1->peso, aresta2->peso);
        
}

int edge_compare_w_weight(const Edge* aresta, float peso) {
    if (aresta == NULL)
        return INT_MIN;  // retornando um número sem sentido
    return number_comparation(aresta->peso, peso);
}

bool edge_equals_n(const Edge* aresta1, const Edge* aresta2) {   // Verifica se as duas arestas são iguais em nome.
    if (aresta1 == NULL || aresta2 == NULL) 
        return false;
    return edge_compare_n_cstr_cstr(aresta1, string_cstr(&aresta2->u), string_cstr(&aresta2->v), aresta2->direcionado) == 0;
}

bool edge_equals_n_cstr_cstr(const Edge* aresta, const char* u1, const char* u2, bool dir) {  // Verifica se a aresta possui as mesmas extremidades u1 e u2
    return edge_compare_n_cstr_cstr(aresta, u1, u2, dir) == 0;
}

bool edge_equals_w(const Edge* aresta1, const Edge* aresta2) {
    if (aresta1 == NULL || aresta2 == NULL) 
        return false;
    return number_comparation(aresta1->peso, aresta2->peso) == 0;
}

bool edge_equals_w_weight(const Edge* aresta, float peso) {
    if (aresta == NULL)
        return false;
    return number_comparation(aresta->peso, peso) == 0;
}

String edge_to_string(const Edge* aresta) {
    if (aresta == NULL)
        return string_new_with_cstr("NULL");
    String number_str = string_from_float(aresta->peso, 2);
    if (string_is_empty(&number_str)) {
        string_free(&number_str);
        return string_new_with_cstr("NULL");
    }
    
    int tamanho = string_length(&aresta->u) + string_length(&aresta->v) + string_length(&number_str) + 4;
    String cadeia = string_new_with_size(tamanho);  // tamanho certinho da string de resultado, assim evita realocação
    if (!string_is_valid(&cadeia)) {
        string_free(&number_str);
        return string_new_with_cstr("NULL");
    }
    
    string_concat(&cadeia, &aresta->u);
    if (aresta->direcionado)
        string_concat_cstr(&cadeia, "->");
    else
        string_concat_cstr(&cadeia, "--");
    string_concat(&cadeia, &aresta->v);
    string_append(&cadeia, '(');
    string_concat(&cadeia, &number_str);
    string_append(&cadeia, ')');
    
    string_free(&number_str);
    return cadeia;
}

void edge_print(const Edge* aresta) {
    String cadeia = edge_to_string(aresta);
    string_print(&cadeia);
    string_free(&cadeia);
}

void edge_println(const Edge* aresta) {
    edge_print(aresta);
    printf("\n");
}



