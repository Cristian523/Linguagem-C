#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arvoreAVL.h"

int main() {
	No * T = NULL;
	int n;
	scanf("%d", &n);
	int elemento;
	for (int i = 0; i < n; i++) {
		scanf(" %d", &elemento);
		Insere_AVL(&T, elemento);
	}
	ImprimirArvore_Detalhada(T);
	/*
	printf("\n");
	Remove_AVL(&T, 7);
	Remove_AVL(&T, 9);
	Remove_AVL(&T,14);
	printf("\n");
	ImprimirArvore_Detalhada(T);
	*/
	printf("O número de elementos é: %d\n", NumeroElementos(T));
	No * p = Busca(T, 6);
	if (p != NULL) 
		printf("O valor é %d e a sua respectiva altura é %d\n", p->E, p->altura); 
	else
		printf("Valor não encontrado!\n");
	Destroi(&T);
	return 0;
}
