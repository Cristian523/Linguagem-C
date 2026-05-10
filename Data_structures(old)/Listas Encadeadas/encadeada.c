#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "encadeada.h"

void Imprimir(No * L) {
	while (L != NULL) {
		printf("[" TIPO_FORMATO "] -> ", L->E);
		L = L->Prox;
	}
	printf("/\n");
}

bool Insere(No ** L, tipo x) {
	No * n = (No *)malloc(sizeof(No));
	if (n == NULL) {
		return false;
	}
	n->E = x;
	n->Prox = *L;
	*L = n;
	return true;
}

bool Insere_Final(No ** L, tipo x) {
	No * n = (No *)malloc(sizeof(No));
	if (n == NULL) {
		return false;
	}
	
	No * p = *L;
	while (p != NULL && p->Prox != NULL) 
		p = p->Prox;
	n->E = x;
	n->Prox = NULL;	
	if (p != NULL)
	 	p->Prox = n;
	else
		*L = n;
	return true;
}

bool Insere_Final_F(No ** L, tipo x, No ** f) {  // Cuidado!
	No * n = (No *)malloc(sizeof(No));
	if (n == NULL) {
		return false;
	}
	n->E = x;
	n->Prox = NULL;
	if (*f != NULL)
		(*f)->Prox = n;
	else
		(*L) = n;
	*f = n;
	return true;
}	

bool Insere_Ordenado(No ** L, tipo x) {
	No * p = *L;
	No * pAnt = NULL;
	while (p != NULL && p->E < x) {
		pAnt = p;
		p = p->Prox;
	}
	No * q = (No *)malloc(sizeof(No));
	if (q == NULL) {
		return false;
	}	
	q->E = x;
	q->Prox = p;
	if (pAnt != NULL)
		pAnt->Prox = q;
	else
		*L = q;
	return true;
}

bool Remove(No ** L, tipo x) {
	No * p = *L;
	No * pAnt = NULL;
	while (p != NULL && p->E != x) {
		pAnt = p;
		p = p->Prox;
	} 
	if (p != NULL) {
		if (pAnt != NULL)
			pAnt->Prox = p->Prox;
		else
			*L = p->Prox;
		free(p);
		return true;
	}
	return false;

}
void Excluir_Lista(No ** L) {
	while (*L != NULL) {
		No * p = *L;
		*L = (*L)->Prox;
		free(p);
	}
}

No * Busca(No * L, tipo x) {  
	while (L != NULL) {
		if (L->E == x)	
			return L;
		else
			L = L->Prox;
	}
	return NULL;
}

int Tamanho(No * L) {
	int count = 0;
	while (L != NULL) {
		count++;
		L = L->Prox;
	}
	return count;
} 

