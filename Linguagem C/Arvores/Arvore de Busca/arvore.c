#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arvore.h"

void DesalocarNo(No ** X) {
	No * Antigo = *X;
	if ((*X)->Esq == NULL) 
		*X = (*X)->Dir;
	else {
		No ** M = &((*X)->Esq);
		while ((*M)->Dir != NULL) 
			M = &((*M)->Dir);
		No * Mrem = *M;
		*M = (*M)->Esq;
		*X = Mrem;
		Mrem->Esq = Antigo->Esq;
		Mrem->Dir = Antigo->Dir;		
	}
	free(Antigo);
}

bool Insere(No ** T, int x) {
	if ((*T) == NULL) {
		No * novo = (No *)malloc(sizeof(No));
		if (novo == NULL) {
			printf("Erro ao alocar o elemento!!\n");
			return false;
		}
		novo->E = x;
		novo->Esq = NULL;  novo->Dir = NULL;
		*T = novo;
		return true;
	}
	else {
		if (x < (*T)->E)
			return Insere(&((*T)->Esq), x);	
		else if (x > (*T)->E)
			return Insere(&((*T)->Dir), x);
		else {
			printf("Este valor já está na árvore!!\n");
			return false;
		}
	}
}

No * Busca(No * T, int x) {
	while (T != NULL && T->E != x) {
		if (x < T->E)
			T = T->Esq;
		else
			T = T->Dir;
	}
	return T;
}

bool Remove(No ** T, int x) {
	if ((*T) == NULL) {
		printf("Elemento não encontrado!!\n");
		return false;
	}
	else {
		if (x == (*T)->E) {
			DesalocarNo(T);
			return true;
		}	
		else if (x < (*T)->E) 
			return Remove(&((*T)->Esq), x);
		else
			return Remove(&((*T)->Dir), x);
	}
}

void Destroi(No ** T) {
	if ((*T) != NULL) {
		Destroi(&((*T)->Esq));
		Destroi(&((*T)->Dir));
		(*T)->Esq = (*T)->Dir = NULL;
		free(*T);
	}
}

void ImprimirArvore_Ordenado(No * T) {
	if (T != NULL) {
		ImprimirArvore_Ordenado(T->Esq);
		printf("%d\n", T->E); 
		ImprimirArvore_Ordenado(T->Dir);
	}
}
		
void ImprimirArvore_Detalhada(No *T) {   // Não fui eu que fiz! Foi o ChatGPT.
    if (T != NULL) {
        if (T->Esq != NULL)
            printf("No %d -> Esquerdo: %d\n", T->E, T->Esq->E);
        else
            printf("No %d -> Esquerdo: NULL\n", T->E);
        
        if (T->Dir != NULL)
            printf("No %d -> Direito: %d\n", T->E, T->Dir->E);
        else
            printf("No %d -> Direito: NULL\n", T->E);
        
        // Recursão nos filhos
        ImprimirArvore_Detalhada(T->Esq);
        ImprimirArvore_Detalhada(T->Dir);
    }
}

int NumeroElementos(No * T) {
	if (T == NULL)
		return 0;
	else {
		int e = NumeroElementos(T->Esq);
		int d = NumeroElementos(T->Dir);
		return (e + d + 1);	
	}
}	

int Altura(No * T) {
	if (T == NULL)
		return -1;
	else {
		int e = Altura(T->Esq);
		int d = Altura(T->Dir);
		if (e > d)
			return e + 1;
		else
			return d + 1;
	}
}





