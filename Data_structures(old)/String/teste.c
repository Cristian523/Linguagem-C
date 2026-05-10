#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "c_string.h"

int main() {
	String cadeia = string_new();
	printf("Digite aqui seu número ponto flutuante: ");
	
	double n;
	if (string_nextDouble(&n))
		printf("Seu número é: %lf\n", n);
	else
		printf("Número inválido!\n");
	
	
	printf("Digite aqui sua string: ");
	string_input(&cadeia);
	string_print(cadeia);
	
	printf("O número de caracteres 'a's é: %d\n", string_count(cadeia, 'a'));
	
	string_remove_all(&cadeia, ' ');
	
	string_print(cadeia);
	
	printf("O tamanho da string atual é: %d\n", string_length(cadeia));
	
	string_append(&cadeia, 'A');
	
	string_print(cadeia);
	printf("Novo tamanho da string: %d\n", string_length(cadeia));
	
	string_destroy(&cadeia);
	
	int numero;
	cadeia = string_new_with_size(5);
	
	printf("Digite seu número inteiro: ");
	if (string_nextInt(&numero))
		printf("Seu número é: %d\n", numero);
	else
		printf("Número inválido!\n");
		
	string_destroy(&cadeia);
	
	cadeia = string_new_with_str("bat", 3);
	string_print(cadeia);
	string_append(&cadeia, 'A');
	string_append(&cadeia, 'T');
	string_append(&cadeia, 'A');
	string_append(&cadeia, 'B');
	
	string_print(cadeia);
	string_destroy(&cadeia);
	
	
}
