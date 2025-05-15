#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "encadeada.h"

int main() {
	No * L = NULL; 
	int n, elemento;
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		scanf(" %d", &elemento);
		Insere_Final(&L, elemento);
	}
	Imprimir(L);
	Remove(&L, 6);
	Imprimir(L);
	Excluir_Lista(&L);
	
	return 0;
}
