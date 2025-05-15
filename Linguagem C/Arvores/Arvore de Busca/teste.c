#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arvore.h"

int main() {
	No * T = NULL;
	int n, elemento;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf(" %d", &elemento);
		Insere(&T, elemento);
	}
	//Remove(&T, 7);
	ImprimirArvore_Ordenado(T);
	printf("\n");
	No * p = Busca(T, 3);
	printf("%d\n%d\n", Altura(T), Altura(p));
	printf("O número de elementos é: %d\n", NumeroElementos(T));
	
	Destroi(&T);
	return 0;
}
