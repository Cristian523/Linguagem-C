#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fila.h"

/* Observação: Aonde tem   (*F).  eu poderia ter colocado F->  */

void Constroi_Fila(Fila * F) {
	(*F).Inicio = NULL;  (*F).Fim = NULL;
	(*F).N = 0;
}

bool Enfileira(Fila * F, tipo * x) {
	No * novo = (No *)malloc(sizeof(No));
	if (novo == NULL) {
		return false;
	}
	
	novo->E = *x;
	novo->Prox = NULL;
	if ((*F).Fim != NULL) 
		(*F).Fim->Prox = novo;
	else
		(*F).Inicio = novo;
	(*F).Fim = novo;
	(*F).N++;
	
	return true;
}

bool Desenfileira(Fila * F, tipo * valor) {
	if (F->Inicio == NULL || (*F).N <= 0) {
		return false;
	}
	
	*valor = (*F).Inicio->E;	
	No * antigo = (*F).Inicio;
	(*F).Inicio = (*F).Inicio->Prox;
	if ((*F).Inicio == NULL) 
		(*F).Fim = NULL;
	
	(*F).N--;
	free(antigo);
	return true;
}

bool Proximo(Fila * F, tipo * valor) {
	if (F->Inicio != 0 && (*F).N > 0) {
		*valor = (*F).Inicio->E;	
		return true;		
	}
	else {
		return false;
	}
}

int Tamanho_Fila(Fila * F) {
	return (*F).N;
}


