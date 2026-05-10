#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tabela.h"

int main() {
	int M, N;
	
	tipo elemento;
	scanf("%d", &N);
	M = 2*N / 3;
	Tabela T; Constroi_Tabela(&T, M);
	for (int i = 0; i < N; i++) {
		scanf(" %d", &elemento);   // Mude aqui depois
		Insere_Ordenado(&T, elemento);	
	}	
		
	//Imprimir_Tabela(T);
	/* 
	No* p = Busca(T, 3.33);
	if (p != NULL)
		printf("Elemento encontrado: "FORMATO"\n", p->E);
	else
		printf("Elemento não encontrado\n");
	*/
	Imprimir_Tabela(T);
	printf("O tamanho da tabela é: %d\n", Tamanho_Tabela(T));
	Excluir_Tabela(&T);
	return 0;
}
