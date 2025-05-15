#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

// Observação: as funções aqui implantadas são para árvores de busca.

int Numero_Elementos(No * T) {
	if (T == NULL)
		return 0;
	else {
		int e = Numero_Elementos(T->Esq);
		int d = Numero_Elementos(T->Dir); 
		return (e + d + 1);
	}
}

void Insere(No ** T, int x) {  // Insere apenas elementos que não estão na árvore (sem repetição).
	if (*T == NULL) {
		*T = (No *)malloc(sizeof(No));
		(*T)->Esq = NULL; (*T)->Dir = NULL;
		(*T)->E = x;
	}
	else {	
		if (x < (*T)->E) 
			Insere(&((*T)->Esq), x);
		else if (x > (*T)->E)
			Insere(&((*T)->Dir), x);
	}
}

No* Busca(No * T, int x) {  
	if (T == NULL)
		return NULL;
	else {
		if (x == T->E)	
			return T;
		else if (x < T->E) 
			return Busca(T->Esq, x);	
		else
			return Busca(T->Dir, x);
	}
}

void Destroi(No ** T) {
	if (*T != NULL) {
		Destroi(&((*T)->Esq));	
		Destroi(&((*T)->Dir));	
		(*T)->Esq = NULL; (*T)->Dir = NULL;
		free(*T);
		*T = NULL;
	}
}

void ImprimirArvore(No * T) {
	if (T != NULL) {
		printf("%d\n", T->E);
		ImprimirArvore(T->Esq);
		ImprimirArvore(T->Dir);
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

void RemoveNo(No ** X) {   // Não fui eu quem fiz!
    // remove o nó *X
	No * Xrem = *X;
    if ((*X)->Esq == NULL) {
        *X = (*X)->Dir;
    } else {
        No ** M =  &((*X)->Esq);
        while ((*M)->Dir != NULL) {
             M = &((*M)->Dir);
        }
        No * Mrem = *M;
        *M = (*M)->Esq;
        *X = Mrem;
        Mrem->Esq = Xrem->Esq;
        Mrem->Dir = Xrem->Dir;
    }
    free(Xrem);
}

void Remove(No **T, int x) {  // Não fui eu quem fiz!
    // remove o nó associado ao elemento x, se existente
    if (*T != NULL) {
    	if ((*T)->E == x) {
    	    RemoveNo(T);
   	 	} else if ((*T)->E > x) {
			Remove(&((*T)->Esq), x);
		} else {
			Remove(&((*T)->Dir), x);
		}
	}
}


