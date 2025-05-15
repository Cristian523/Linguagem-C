#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "encadeada.h"

// está incompleto!!!

bool Insere(No ** L, int x) {
	No * n = (No *) malloc(sizeof(No));
	if (n == NULL) {
		printf("Erro ao alocar o elemento!\n");
		return false;
	}
	n->E = x;
	
	if ((*L) != NULL) {
		n->Prox = *L;
		n->Ant = (*L)->Ant;
		(*L)->Ant->Prox = n;  // O "último" elemento aponta para n
		(*L)->Ant = n;
		
	}
	else {
		n->Ant = n;
		n->Prox = n;
	}
	*L = n;
	
	return true;
}

void Imprimir_Lista(No * L) {
	No * inicio = L;
	if (L != NULL) {
		printf(" <-> [%d] <-> ", L->E);
		L = L->Prox;
	}
	while (L != inicio) {
		printf("[%d] <-> ", L->E);
		L = L->Prox;
	}
	printf("\n");
}

void Excluir_Lista(No ** L) {
	No * antigo;
	if (*L != NULL)
		(*L)->Ant->Prox = NULL;  // O "último" No recebe Prox = NULL;
	while (*L != NULL) {
		antigo = *L;
		*L = (*L)->Prox;
		free(antigo);
	}
}


