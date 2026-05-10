#include <stdio.h>
#include "filas.h"

int main() {
	Fila F; Constroi_Fila(&F);
	Enfileira(&F, 8);
	Enfileira(&F, 5);
	Enfileira(&F, 10);
	int n = Tamanho_Fila(&F);
	printf("%d\n", Proximo(&F));
	for (int i = 0; i < n; i++) {
		if (i < n - 1)
			printf("[%d]  ", Desenfileira(&F));
		else
			printf("[%d]\n", Desenfileira(&F));
	}
	
	return 0;	
}
