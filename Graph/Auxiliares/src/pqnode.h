#ifndef PQNODE_H
#define PQNODE_H

#include <stdbool.h>
#include "c_string.h"

typedef struct PQNode {
    String vertice;
    float distancia;
} PQNode;

PQNode pqnode_new(const String, float);
// @ Inicializa um novo PQNode com String e float, sempre usando String como cópia

PQNode pqnode_new_cstr(const char*, float);
// @ Mesma ideia da função anterior, mas com o primeiro parâmetro sendo vetor de caracteres

PQNode pqnode_new_empty();
// @ Inicializa um PQNode com o campo String sendo uma string vazia e o campo float sendo 0. Use essa função para usar de retorno em outras funções quando esse retorno for feito por parâmetro.

void pqnode_free(PQNode*);
// @ Libera a memória do conteúdo antigo

bool pqnode_copy(PQNode*, const PQNode*);
// @ Copia todo o conteúdo do segundo parâmetro para o primeiro e libera a memória do conteúdo antigo. Se um dos parâmetros for nulo, essa função retornará false e o primeiro parâmetro não será modificado.

String pqnode_to_string(const PQNode*);
// @ Retorna uma representação de PQNode como String.

void pqnode_print(const PQNode*);
// @ Imprime a String obtida com a função anterior.

void pqnode_println(const PQNode*);
// @ Usa a função anterior e imprime ao final o caractere '\n'.

#endif
