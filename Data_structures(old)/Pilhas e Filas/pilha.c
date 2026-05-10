#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pilha.h"

/* Observação: aonde tem  (*P).  eu poderia ter colocado  P->  */

void Constroi_Pilha(Pilha * P) {
	(*P).Topo = NULL; (*P).N = 0;
}

bool Empilha(Pilha * P, tipo * x) {
	No * novo = (No *)malloc(sizeof(No));
	if (novo == NULL) {
		return false;
	}
	novo->E = *x;
	novo->Prox = (*P).Topo;
	(*P).Topo = novo;
	(*P).N++;
	return true;
}
bool Desempilha(Pilha * P, tipo * valor) { 
	if (P->Topo == NULL || (*P).N <= 0) {
		return false;
	}
	*valor = (*P).Topo->E;
	No * antigo = (*P).Topo;
	(*P).Topo = (*P).Topo->Prox;

	free(antigo);
	(*P).N--;
	return true;
}

bool Topo(Pilha * P, tipo * valor) {
	if (P->Topo != NULL && (*P).N > 0) {
		*valor = (*P).Topo->E;
		return true;
	}
	else {
		return false;
	}
}

int Tamanho_Pilha(Pilha * P) {
	return (*P).N;
}

