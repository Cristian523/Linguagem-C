#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

void RemoverMeu(No**, int);
void RemoverNoMeu(No**);

int main() {
	No * T = NULL;
	int x;
	for (int i = 0; i < 15; i++) {
		scanf("%d", &x);
		Insere(&T, x);
	}
	No * p = Busca(T, 6);
	if (p)
		printf("%d\n", p->E);
	else
		puts("Elemento não encontrado");
	p = NULL;
	
	Remove(&T, 8);
	ImprimirArvore_Detalhada(T);
	Destroi(&T);
	return 0;
}

/*
void RemoverNoMeu(No** X) {
	No * R = *X;
	if ((*X)->Esq == NULL) 
		*X = (*X)->Dir;
	else {
		No ** M = &((*X)->Esq);
		while ((*M)->Dir != NULL)
			M = &((*M)->Dir);   
		No * Mrem = *M;
		*M = (*M)->Esq;      
		*X = Mrem;
		Mrem->Esq = R->Esq;
		Mrem->Dir = R->Dir;
	}
	free(R);
}

void RemoverMeu(No** T, int x) {
	if ((*T) != NULL) {
		if (x == (*T)->E) 
			RemoverNoMeu(T);
		else if (x < (*T)->E)
			RemoverMeu(&((*T)->Esq), x);
		else
			RemoverMeu(&((*T)->Dir), x);
	}
}	
*/
