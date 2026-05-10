#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tabela.h"

/* Funções de Lista Encadeada */

void Imprimir_Lista(No * L) {
	while (L != NULL) {
		printf("["FORMATO"] -> ", L->E);
		L = L->Prox;
	}
	printf("/\n");
}

bool Insere_Lista(No ** L, tipo x) {
	No * n = (No *)malloc(sizeof(No));
	if (n == NULL) {
		return false;
	}
	n->E = x;
	n->Prox = *L;
	*L = n;
	return true;
}

bool Insere_Ordenado_Lista(No ** L, tipo x) {
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

No * Busca_Lista(No * L, tipo x) {  
	while (L != NULL) {
		if (L->E == x)	
			return L;
		else
			L = L->Prox;
	}
	return NULL;
}

bool Remove_Lista(No ** L, tipo x) {
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

/* Funções de Lista Encadeada */


/* Funções de Tabela de Dispersão */

bool Constroi_Tabela(Tabela * T, int M) {
	(*T).H = (No**)malloc(M * sizeof(No*));
	if ((*T).H == NULL) {
		return false;
	}
	
	for (int i = 0; i < M; i++)
		(*T).H[i] = NULL;
	(*T).N = 0;
	(*T).M = M;
	return true;
}

int Dispersao(Tabela T, tipo x) {
	const float A = 0.6180339887;  // Constante irracional. É a constante (sqrt(5) - 1) / 2
    return (int)(T.M * (x * A - (int)(x * A)));  // Parte fracionária de x * A multiplicada por M
}

bool Insere(Tabela * T, tipo x) {
	int posicao = Dispersao(*T, x);
	bool deu_certo = Insere_Lista(&((*T).H[posicao]), x);
	if (deu_certo)
		(*T).N++;
	return deu_certo;
}

bool Insere_Ordenado(Tabela * T, tipo x) {
	int posicao = Dispersao(*T, x);
	bool deu_certo = Insere_Ordenado_Lista(&((*T).H[posicao]), x);
	if (deu_certo)
		(*T).N++;
	return deu_certo;
}

No* Busca(Tabela T, tipo x) {
	int posicao = Dispersao(T, x);	
	return Busca_Lista(T.H[posicao], x);

}

bool Remove(Tabela * T, tipo x) {
	int posicao = Dispersao(*T, x);
	bool deu_certo = Remove_Lista(&((*T).H[posicao]), x);
	if (deu_certo)
		(*T).N--;
	return deu_certo;
}

void Excluir_Tabela(Tabela * T) {
	for (int i = 0; i < T->M; i++)
		Excluir_Lista(&(T->H[i]));
	free(T->H);
	T->N = 0;
	T->M = 0;
}

void Imprimir_Tabela(Tabela T) {
	for (int i = 0; i < T.M; i++) {
		printf("Posição %d: ", i);
		Imprimir_Lista(T.H[i]);
	}
} 

int Tamanho_Tabela(Tabela T) {
	return T.N;
}
/* Funções de Tabela de Dispersão */


