#include <stdio.h>
#include <stdlib.h>
#include "pilhas.h"

// Observação: Aonde tem (*P).  poderia ter usado P->

void Constroi_Pilha(Pilha * P) {
	(*P).Topo = NULL; (*P).N = 0;
}
void Empilha(Pilha * P, tipo x) {
	No * n =(No *) malloc(sizeof(No));
	n->E = x;
	n->Prox = (*P).Topo;
	(*P).Topo = n;
	(*P).N++; 
}
	
tipo Desempilha(Pilha * P) {
	No * n = (*P).Topo;  tipo x = n->E;
	(*P).Topo = (*P).Topo->Prox;
	(*P).N--;
	free(n);
	return x;
}

tipo Topo(Pilha * P) {
	return (*P).Topo->E;
}

int Tamanho_Pilha(Pilha * P) {
	return (*P).N;
}
