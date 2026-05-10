#include <stdio.h>
#include <stdlib.h>
#include "filas.h"

// Observação: Aonde tem (*F).  poderia ter usado F->

void Constroi_Fila(Fila * F) {
	(*F).N = 0;	
	(*F).Inicio = NULL; (*F).Fim = NULL;
}

void Enfileira(Fila * F, tipo x) {
	No * n = (No *) malloc(sizeof(No));
	n->E = x;
	n->Prox = NULL;
	if ((*F).Fim != NULL)
		(*F).Fim->Prox = n;
	else
		(*F).Inicio = n;
	(*F).Fim = n;
	(*F).N++;
}

tipo Desenfileira(Fila * F) {
	No * n = (*F).Inicio;  tipo x = n->E;
	(*F).Inicio = (*F).Inicio->Prox;
	if ((*F).Inicio == NULL)
		(*F).Fim = NULL;
	free(n);
	(*F).N--;
	return x;
}

tipo Proximo(Fila * F) {
	return (*F).Inicio->E;
}

int Tamanho_Fila(Fila * F) {
	return (*F).N;
}
