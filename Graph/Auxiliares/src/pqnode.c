#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "c_string.h"
#include "pqnode.h"

PQNode pqnode_new(const String cadeia, float numero) {   // Inicializa um novo PQNode com String e float, sempre usando String como cópia
    return pqnode_new_cstr(string_cstr(&cadeia), numero);
}

PQNode pqnode_new_cstr(const char* caracteres, float numero) {  // Mesma ideia da função anterior, mas com o primeiro parâmetro sendo vetor de caracteres
    PQNode node;
    node.vertice = string_new_with_cstr(caracteres);
    node.distancia = numero;
    return node;
}

PQNode pqnode_new_empty() {  // Inicializa um PQNode vazio 
    PQNode node;
    node.vertice = string_new_empty();
    node.distancia = 0;
    return node;
}

void pqnode_free(PQNode* node) {  // Libera a memória do conteúdo antigo
    if (node != NULL) 
        string_free(&node->vertice);
}

bool pqnode_copy(PQNode* node1, const PQNode* node2) {   // Copia todo o conteúdo do segundo parâmetro para o primeiro e libera a memória do conteúdo antigo.
    if (node1 == NULL || node2 == NULL)
        return false;
    string_copy(&node1->vertice, &node2->vertice);
    node1->distancia = node2->distancia;
    return true;
}

String pqnode_to_string(const PQNode* node) {  // Retorna uma representação de PQNode como String.
    if (node == NULL)
        return string_new_empty();
    String aux1 = string_new_empty();
    string_copy(&aux1, &node->vertice);
    String aux2 = string_from_float(node->distancia, 2);
    
    String cadeia = string_new_with_size(string_size(&aux1) + string_size(&aux2) + 2);
    
    string_concat(&cadeia, &aux1);
    string_append(&cadeia, '(');
    string_concat(&cadeia, &aux2);
    string_append(&cadeia, ')');
    
    string_free(&aux1);
    string_free(&aux2);
    return cadeia;
}

void pqnode_print(const PQNode* node) { // Imprime a String obtida com a função anterior.
    String cadeia = pqnode_to_string(node);
    string_print(&cadeia);
    string_free(&cadeia);
}

void pqnode_println(const PQNode* node) {  // Usa a função anterior e imprime ao final o caractere '\n'.
    pqnode_print(node);
    printf("\n");
}
