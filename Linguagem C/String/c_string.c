#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "c_string.h"
#define STRING_DEFAULT_CAPACITY 50

String string_new_with_size(int size) {
	String cadeia;
	cadeia.str = NULL;
	cadeia.Max_length = size;
	cadeia.length = 0;
	return cadeia;
}

String string_new_with_str(char* vet, int max_size) {
	String cadeia;
	cadeia.str = NULL;
	cadeia.Max_length = max_size;
	cadeia.length = strlen(vet);
	string_copy(&cadeia, vet, cadeia.length);
	return cadeia;
}

String string_new() {
	String cadeia;
	cadeia.str = NULL;
	cadeia.Max_length = cadeia.length = 0;
	return cadeia;
}

bool increase_size(char** vet, int* N) {
	(*N) *= 2;
	char* novo_vet = (char*) realloc(*vet, (*N) * sizeof(char));
	if (novo_vet == NULL)
		return false;
	*vet = novo_vet;
	return true;
}

bool string_input(String* cadeia) {
	char* aux, *novo_aux;
	char x;
	int N, n = 0;
	// Se existir uma string antes, libere a memória.
	if (cadeia->str != NULL) {
		free(cadeia->str);
		cadeia->str = NULL;
		cadeia->length = cadeia->Max_length = 0;
	}
	// Tamanho máximo da string atual
	N = cadeia->Max_length;
	if (N <= 0) 
		N = STRING_DEFAULT_CAPACITY;
	
	// Alocar o vetor para a nova string
	aux = (char*)malloc(N * sizeof(char));
	if (aux == NULL)
		return false;
	
	// Lê os caracteres até encontrar o '\n'
	while (scanf("%c", &x) == 1) {
		if (x == '\n')
			break;
		
		if (n >= N) {  // Se estiver cheio, aumente o tamanho
			if (increase_size(&aux, &N) == false) { // Aqui vai tentar dobrar o tamanho
				free(aux);
				return false;
			}
		}
		aux[n] = x;
		n++;
	}
	// Aumenta o tamanho caso necessário e coloca o '\0' ao final da string
	if (n >= N) {
		if (increase_size(&aux, &N) == false) { // Aqui vai tentar dobrar o tamanho
			free(aux);
			return false;
		}
	}
	aux[n] = '\0';
	
	// Atribuindo a nova string
	cadeia->Max_length = N;
	cadeia->length = n;
	cadeia->str = aux;
	return true;
}

int string_length(String cadeia) {
	return cadeia.length;
}

bool string_append(String* cadeia, char x) {
	// Caso esta função seja chamada com nenhum tamanho inicial máximo.
	if (cadeia->Max_length <= 0)
		cadeia->Max_length = STRING_DEFAULT_CAPACITY; 
	if (cadeia->str == NULL) {
		cadeia->str = malloc(cadeia->Max_length * sizeof(char));
    	if (cadeia->str == NULL) 
    		return false;
	}
	
	// Aumenta o tamanho da string, caso necessário
	if (cadeia->length + 1 >= cadeia->Max_length) {
		if (increase_size(&(cadeia->str), &(cadeia->Max_length)) == false)  // Tenta dobrar o tamanho
			return false;
	}
	cadeia->str[cadeia->length] = x;
	(cadeia->length)++;
	cadeia->str[cadeia->length] = '\0';
	return true;
}

void string_destroy(String* cadeia) {
	if (cadeia->str != NULL) {
		free(cadeia->str);
		cadeia->str = NULL;
		cadeia->length = cadeia->Max_length = 0;
	}
}

bool string_remove(String* cadeia, char x) {
	if (cadeia->str == NULL)
		return false;
	int posicao = -1;
	for (int i = 0; i < cadeia->length; i++) {
		if (cadeia->str[i] == x) {
			posicao = i;
			break;
		}			
	}
	if (posicao != -1) {
		for (int i = posicao; i < cadeia->length - 1; i++) {
			cadeia->str[i] = cadeia->str[i + 1];
		}
		cadeia->str[cadeia->length - 1] = '\0';
		(cadeia->length)--;
		return true;
	}
	return false;
}

bool string_remove_all(String* cadeia, char x) {
	if (cadeia->str == NULL)
		return false;
	int i, j = 0;
	char aux;
	for (i = 0; i < cadeia->length; i++) {
		if (cadeia->str[i] != x) {
			cadeia->str[j] = cadeia->str[i];
			j++;
		}
	}
	cadeia->str[j] = '\0';
	cadeia->length = j;
	return true;
}

int string_search(String cadeia, char x) {
	if (cadeia.str == NULL)
		return -1;
	for (int i = 0; i < cadeia.length; i++) {
		if (cadeia.str[i] == x)
			return i; 
	}
	return -1;
}

int string_count(String cadeia, char x) {
	int count = 0;
	for (int i = 0; i < cadeia.length; i++) {
		if (cadeia.str[i] == x)
			count++;
	}
	return count;
}

void string_print(String cadeia) {
	for (int i = 0; i < cadeia.length; i++) 
		printf("%c", cadeia.str[i]);
	printf("\n");
}

bool string_parseInt(String cadeia, int* numero) {
	if (cadeia.length <= 0 || cadeia.str == NULL)	
		return false;
	char c;
	int n, potencia = 1, x = 0;
	for(int i = cadeia.length - 1; i >= 0; i--) {
		if(i == 0 && (cadeia.str[i] == '-' || cadeia.str[i] == '+'))   // Se for um número negativo ou positivo (+)
			continue;
		c = cadeia.str[i];
		if (c >= '0' && c <= '9') {
			n = (int) (c - '0');
			x += n * potencia;
			potencia *= 10;   
		}
		else
			return false;
	}
	if (cadeia.str[0] == '-') // Se for um número negativo
		x *= -1;
	*numero = x;
	return true;
}

bool string_parseFloat(String cadeia, float* numero) {
	if (cadeia.length <= 0 || cadeia.str == NULL) 
		return false;
	
	char c;
	int ponto_posicao = -1;
	int n;
	float potencia_1 = 1, potencia_2 = 0.1;
	float x = 0.0;
	
	for (int i = 0; i < cadeia.length; i++) {  // Procurando o caractere '.'
		 if (cadeia.str[i] == '.') {
		 	ponto_posicao = i;
		 	break;
		}
	}
	if (ponto_posicao == -1)    // Se o float digitado não tem casas decimais
		ponto_posicao = cadeia.length;
	
	
	for (int i = ponto_posicao - 1; i >= 0; i--) {   // Convertendo os números antes do '.'
		if (i == 0 && (cadeia.str[i] == '-' || cadeia.str[i] == '+'))  // Se for um número negativo ou positivo (+)
			continue;
		
		c = cadeia.str[i];
		if (c >= '0' && c <= '9') {
			n = (int) (c - '0');
			x += (float) (n * potencia_1);
			potencia_1 *= 10; 
		}
		else
			return false;
	}
	
	for (int i = ponto_posicao + 1; i < cadeia.length; i++) { // Convertendo os números após o '.'
		c = cadeia.str[i];
		if (c >= '0' && c <= '9') {
			n = (int) (c - '0');
			x += n * potencia_2;
			potencia_2 /= 10; 
		}
		else
			return false;
	}
	if (cadeia.str[0] == '-') // Se for um número negativo
		x *= -1;
	*numero = x;
	return true;
}

bool string_parseDouble(String cadeia, double* numero) {
	if (cadeia.length <= 0 || cadeia.str == NULL) 
		return false;
	
	char c;
	int ponto_posicao = -1;
	int n;
	double potencia_1 = 1, potencia_2 = 0.1;
	double x = 0.0;
	
	for (int i = 0; i < cadeia.length; i++) {  // Procurando o caractere '.'
		 if (cadeia.str[i] == '.') {
		 	ponto_posicao = i;
		 	break;
		}
	}
	if (ponto_posicao == -1)    // Se o double digitado não tem casas decimais
		ponto_posicao = cadeia.length;
	
	
	for (int i = ponto_posicao - 1; i >= 0; i--) {   // Convertendo os números antes do '.'
		if (i == 0 && (cadeia.str[i] == '-' || cadeia.str[i] == '+'))  // Se for um número negativo ou positivo (+)
			continue;
		
		c = cadeia.str[i];
		if (c >= '0' && c <= '9') {
			n = (int) (c - '0');
			x += (double) (n * potencia_1);
			potencia_1 *= 10; 
		}
		else
			return false;
	}
	
	for (int i = ponto_posicao + 1; i < cadeia.length; i++) { // Convertendo os números após o '.'
		c = cadeia.str[i];
		if (c >= '0' && c <= '9') {
			n = (int) (c - '0');
			x += n * potencia_2;
			potencia_2 /= 10; 
		}
		else
			return false;
	}
	
	if (cadeia.str[0] == '-') // Se for um número negativo
		x *= -1;
	*numero = x;
	return true;
}

bool string_copy(String* cadeia, char* vet, int n) {
	int N = cadeia->Max_length;
	char* aux;
	if (N <= n)
		N = n + 1;
	aux = (char*)malloc(N * sizeof(char));
	if (aux == NULL)
		return false;
		
	for (int i = 0; i < n; i++) 
		aux[i] = vet[i];
	aux[n] = '\0';
	
	if (cadeia->str != NULL)
		free(cadeia->str);	
	
	cadeia->str = aux;
	cadeia->Max_length = N;
	cadeia->length = n;
	return true;	
}

bool string_nextInt(int* numero) {
	String cadeia = string_new_with_size(20);
	bool ehNumero = false;
	if (string_input(&cadeia)) {
		ehNumero = string_parseInt(cadeia, numero);
		string_destroy(&cadeia);
	}	
	return ehNumero;
}

bool string_nextFloat(float* numero){
	String cadeia = string_new();
	bool ehNumero = false;
	if (string_input(&cadeia)) {
		ehNumero = string_parseFloat(cadeia, numero);
		string_destroy(&cadeia);
	}	
	return ehNumero;	
}

bool string_nextDouble(double* numero) {
	String cadeia = string_new();
	bool ehNumero = false;
	if (string_input(&cadeia)) {
		ehNumero = string_parseDouble(cadeia, numero);
		string_destroy(&cadeia);
	}	
	return ehNumero;
}
	



