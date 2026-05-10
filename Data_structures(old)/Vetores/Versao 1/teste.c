#include <stdio.h>
#include <stdlib.h>
#include "vetor.h"

int main() {
	int N = 10;
	int n;
	tipo * vet = (tipo *)malloc(N * sizeof(tipo));
	tipo j;
	for (int i = 0; i < 16; i++) {
		scanf(TIPO_FORMATO, &j);
		Insere_Ordenado_Dinamico(&vet, j, &n, &N);
	}
	Imprimir(vet, n);
	// QuickSort(vet, 0, n - 1);
	Remove_O(vet, 9, &n);
	Remove(vet, 1, &n);
	Imprimir(vet, n);
	
	return 0;
}
