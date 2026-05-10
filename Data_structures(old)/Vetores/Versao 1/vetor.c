#include <stdio.h>
#include <stdlib.h>
#include "vetor.h"

/* Funções auxiliares para ordenação */
void Intercalar(tipo A[], int inicio, int meio, int fim) {
	tipo B[fim - inicio + 1];
	int i = inicio, j = meio + 1, n = 0;
	while (i <= meio && j <= fim) { 
		if (A[i] < A[j]) {
			B[n] = A[i];
			i++;
		}
		else {
			B[n] = A[j];
			j++;
		}
		n++;
	}
	while (i <= meio) {
		B[n] = A[i];
		i++;
		n++;
	}
	while (j <= fim) {
		B[n] = A[j];
		j++;
		n++;	
	}
	
	for (int k = 0; k < n; k++) {
		A[inicio] = B[k];
		inicio++;
	}
}

tipo mediana(tipo A, tipo B, tipo C) {
	tipo resultado;
	if ((C >= A && C <= B) || (C >= B && C <= A))
		resultado = C;
	else if ((A >= B && A <= C) || (A >= C && A <= B))
		resultado = A;
	else
		resultado = B;
	return resultado;
}

void Particionar(tipo A[], int inicio, int fim, tipo pivo, int* i, int* j) {
	*i = inicio; *j = fim;
	tipo aux;
	while (*i <= *j) {
		while (A[*i] < pivo) 
			(*i)++;
		while (A[*j] > pivo)
			(*j)--;
		if (*i <= *j) {
			aux = A[*i];
			A[*i] = A[*j];
			A[*j] = aux;
			(*i)++; (*j)--; 
		}
	
	}
}
/* Funções auxiliares para ordenação */


/* Funções para imprimir um vetor, inserir, buscar ou remover um elemento de um vetor */
void Imprimir(tipo vet[], int n) {  // Ok!
	printf("{");
	for (int i = 0; i < n; i++) {
		if (i < n - 1)
			printf(TIPO_FORMATO ", ", vet[i]);	
		else
			printf(TIPO_FORMATO, vet[i]);
	}	
	printf("}\n");
}

void Insere(tipo vet[], tipo x, int *n) { // Ok!   
	vet[*n] = x;
	(*n)++;
}

int Insere_Dinamico(tipo **vet, tipo x, int *n, int *N) {  // Ok!
	// Válido apenas se vet for de alocação dinâmica!
	if (*n >= *N) {
		*N = 2 * (*N);	
		tipo * novo_vetor = (tipo *)realloc(*vet, (*N) * sizeof(*vet));
		if (novo_vetor == NULL) {
			printf("Erro ao realocar o vetor!!\n");
			return 0;
		} 
		*vet = novo_vetor;
		
	}
	(*vet)[*n] = x;
	(*n)++;
	return 1;
}

void Insere_Ordenado(tipo vet[], tipo x, int *n) {  // Ok!
	int i = 0;
	while (i < *n && vet[i] < x) 
		i++;
	for (int j = *n - 1; j >= i; j--) 
		vet[j + 1] = vet[j];
	vet[i] = x;
	(*n)++;
}

int Insere_Ordenado_Dinamico(tipo ** vet, tipo x, int *n, int *N) {  // Ok!
	// Válido apenas se vet for de alocação dinâmica!
	if (*n >= *N) {
		*N = 2 * (*N);	
		tipo * novo_vetor = (tipo*)realloc(*vet, (*N) * sizeof(*vet));
		if (novo_vetor == NULL) {
			printf("Erro ao realocar o vetor!!\n");
			return 0;
		}
		*vet = novo_vetor;
	}
	Insere_Ordenado(*vet, x, n);
	return 1;
}

int Busca(tipo vet[], tipo x, int n) {  // Ok!
	for (int i = 0; i < n; i++) {
		if (vet[i] == x)
			return i;
	}
	printf("Elemento não encontrado!!\n");
	return -1;
}

int Busca_Binaria(tipo vet[], tipo x, int n) {  // Ok!
	// Válido apenas se vet for ordenado!
	int i = 0, j = n - 1;
	int media;
	
	while (i <= j) {
		media = (i + j) / 2;
		if (vet[media] == x)
			return media;
		else if (vet[media] < x)
			i = media + 1;
		else
			j = media - 1;
	}
	printf("Elemento não encontrado!!\n");
	return -1;
}

int Remove(tipo vet[], tipo x, int *n) {  // Ok!
	int i = Busca(vet, x, *n);
	if (i != -1) {
		vet[i] = vet[*n - 1];
		(*n)--;
		return 1;
	}
	return 0;		
}

int Remove_O(tipo vet[], tipo x, int *n) {  // Ok!
	int i = Busca(vet, x, *n);
	if (i != -1) {
		for (int j = i; j < *n; j++)
			vet[j] = vet[j + 1];
		(*n)--;
		return 1;
	}
	return 0;
}
/* Funções para imprimir um vetor, inserir, buscar ou remover um elemento de um vetor */


/* Funções para ordenar um vetor */
void BubbleSort(tipo vet[], int n) {   
	for (int i = n - 1; i >= 0; i--) {  // Aqui poderia ser: for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < i; j++) {	// Aqui poderia ser: for (int j = 0; j < n - i - 1; j++)
			if (vet[j] > vet[j + 1]) {
				tipo aux = vet[j];	
				vet[j] = vet[j + 1];
				vet[j + 1] = aux; 
			}
		}
	}
}

void BubbleSort_Recursivo(tipo vet[], int n) {
	if (n > 1) {
		for (int i = 1; i < n; i++) {
			if (vet[i - 1] > vet[i]) {
				tipo aux = vet[i - 1];
				vet[i - 1] = vet[i];
				vet[i] = aux;
			}	
		}
		BubbleSort_Recursivo(vet, n - 1);
	}
}

void SelectionSort(tipo vet[], int n) {
	for (int i = 0; i < n - 1; i++) {
		int posicao = i;
		for (int j = i + 1; j < n; j++) {
			if (vet[posicao] > vet[j]) 
				posicao = j;
		}	
		tipo aux = vet[posicao];
		vet[posicao] = vet[i];
		vet[i] = aux;
	}
}

void SelectionSort_Recursivo(tipo vet[], int n) {
	if (n > 1) {
		int posicao = 0;
		for (int i = 1; i < n; i++) {
			if (vet[posicao] < vet[i])
				posicao = i;
		}
		tipo aux = vet[n - 1];
		vet[n - 1] = vet[posicao]; 
		vet[posicao] = aux;
		
		SelectionSort_Recursivo(vet, n - 1);
	}
}

void InsertionSort(tipo vet[], int n) {
	if (n > 1) {
		InsertionSort(vet, n - 1);
		int i = n - 1;
		while (i > 0 && vet[i] < vet[i - 1]) {
			tipo aux = vet[i];
			vet[i] = vet[i - 1]; 
			vet[i - 1] = aux;
			i--;
		}
	}	
}

void MergeSort(tipo vet[], int inicio, int fim) {
	if (inicio < fim) {
		int meio = (inicio + fim) / 2;
		MergeSort(vet, inicio, meio);
		MergeSort(vet, meio + 1, fim);
		Intercalar(vet, inicio, meio, fim);
	}
}

void QuickSort(tipo vet[], int inicio, int fim) {
	if (inicio < fim) {
		int i, j;
		tipo pivo;
		if (fim - inicio + 1 == 2)  // Se só tiver 2 elementos no vetor
			pivo = vet[inicio];
		else {
			int meio = (inicio + fim) / 2;
			pivo = mediana(vet[inicio], vet[meio], vet[fim]);
		}
		Particionar(vet, inicio, fim, pivo, &i, &j);
		QuickSort(vet, inicio, j);
		QuickSort(vet, i, fim);  
	}
}	
/* Funções para ordenar um vetor */


