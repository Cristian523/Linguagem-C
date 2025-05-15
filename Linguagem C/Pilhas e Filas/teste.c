#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fila.h"

int main() {
	int n;
	int elemento;
	int elemento_removido;
	scanf("%d", &n);

	Fila F; Constroi_Fila(&F);
	
	for (int i = 0; i < n; i++) {
		scanf(" %d", &elemento);
		Enfileira(&F, &elemento);
	}

	n = Tamanho_Fila(&F);
	for (int i = 0; i < n; i++) {
		Desenfileira(&F, &elemento_removido);
		if (i < n - 1)
			printf("%d ", elemento_removido);
		else
			printf("%d\n", elemento_removido);
	}
	

	return 0;
}
