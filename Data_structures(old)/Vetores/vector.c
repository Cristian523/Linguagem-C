#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vector.h"
#define VECTOR_DEFAULT_CAPACITY 50


Vector vector_new_with_size(int size) {
    Vector array;
    array.vet = (tipo*)malloc(size * sizeof(tipo));
    array.length = 0;
    array.Max_length = size;
    return array;
}

Vector vector_new_with_vet(tipo* vetor, int n) {    // Mais para testes!
    Vector array;
    array.vet = NULL;
    array.length = array.Max_length = 0;
    vector_copy(&array, vetor, n);
    return array;
}

Vector vector_new() {
    Vector array;
    array.vet = (tipo*)malloc(VECTOR_DEFAULT_CAPACITY * sizeof(tipo));
    array.length = 0;
    array.Max_length = VECTOR_DEFAULT_CAPACITY;
    return array;
}



bool increase_size(tipo** vet, int n) {
    tipo* array = (tipo*)realloc(*vet, n * sizeof(tipo));
    if (array == NULL)  
        return false;
    *vet = array;
    return true;
}


bool vector_append(Vector* array, tipo x) {
    if (array->vet == NULL)
        return false;
    int n = array->length;
    int N = array->Max_length;
    if (n >= N) {
        N *= 2;
        if (!increase_size(&(array->vet), N))
            return false;
    }

    array->vet[n] = x;
    array->length = ++n;
    array->Max_length = N;
    return true;
}

bool vector_insert(Vector* array, int posicao, tipo x) {
    if (array->vet == NULL)
        return false;
    int n = array->length;
    int N = array->Max_length;
    if (n >= N) {
        N *= 2;
        if (!increase_size(&(array->vet), N))
            return false;
    }

    if (posicao >= n) 
        posicao = n;
    else if (posicao < 0)
        posicao = 0;

    for (int i = n - 1; i >= posicao; i--) 
        array->vet[i + 1] = array->vet[i];
    
    array->vet[posicao] = x;
    array->length = ++n;
    array->Max_length = N;
    return true;
    
}

bool vector_insert_ordered(Vector* array, tipo x) {
    if (array->vet == NULL)
        return false;
    int n = array->length;
    int N = array->Max_length;
    if (n >= N) {
        N *= 2;
        if (!increase_size(&(array->vet), N))
            return false;
    }

    int posicao = 0;
    while (posicao < n && array->vet[posicao] < x)
        posicao++;

    for (int i = n - 1; i >= posicao; i--) 
        array->vet[i + 1] = array->vet[i];

    array->vet[posicao] = x;
    array->length = ++n;
    array->Max_length = N;
    return true;
}

int vector_search(Vector array, tipo x) {
    if (array.vet == NULL || array.length <= 0)
        return -1;
    int posicao = -1;
    for (int i = 0; i < array.length; i++) {
        if (array.vet[i] == x) {
            posicao = i;
            break;
        }    
    }
    return posicao;
}

int vector_binary_search(Vector array, tipo x) {
    // Válido apenas se array for ordenado!
	if (array.vet == NULL || array.length <= 0)
        return -1;
    int i = 0, j = array.length - 1;
	int media;
	
	while (i <= j) {
		media = (i + j) / 2;
		if (array.vet[media] == x)
			return media;
		else if (array.vet[media] < x)
			i = media + 1;
		else
			j = media - 1;
	}
	return -1;
}

bool vector_pop(Vector* array, tipo * retorno) {
    if (array->vet == NULL || array->length <= 0)
        return false;    
    *retorno = array->vet[array->length - 1];
    array->length--;
    return true;
}

bool vector_pop_at(Vector* array, int posicao, tipo * retorno) {
    if (array->vet == NULL || array->length <= 0)
        return false;
    else if (posicao < 0 || posicao >= array->length)
        return false;
    else {
        *retorno = array->vet[posicao];
        for (int i = posicao; i < array->length - 1; i++)
            array->vet[i] = array->vet[i + 1];
        
    }
    array->length--;
    return true;
    
}

bool vector_remove(Vector* array, tipo x) {
    if (array->vet == NULL || array->length <= 0)
        return false;
    int posicao = vector_search(*array, x);
    if (posicao == -1)
        return false;
    for (int i = posicao; i < array->length - 1; i++)
        array->vet[i] = array->vet[i + 1];

    array->length--;
    return true;
}

int vector_length(Vector array) {
    return array.length;
}

int vector_count(Vector array, tipo x) {
    if (array.vet == NULL)
        return 0;
    
    int count = 0;
    for (int i = 0; i < array.length; i++) {
        if (array.vet[i] == x)
            count++;
    }
    return count;
}

void vector_print(Vector array) {
    if (array.vet != NULL) {
        printf("[");
        for (int i = 0; i < array.length; i++) {
            if (i < array.length - 1)
                printf(FORMAT ", ", array.vet[i]);
            else
                printf(FORMAT, array.vet[i]);
        }
        printf("]\n");
    }
}

void vector_free(Vector* array) {
    if (array->vet != NULL) 
        free(array->vet);
    array->length = array->Max_length = 0;
}

bool vector_copy(Vector* array, tipo* vetor, int n) {
    if (vetor == NULL || n <= 0)
        return false;
    array->vet = (tipo*)malloc(n * sizeof(tipo));
    if (array->vet == NULL)
        return false;

    for (int i = 0; i < n; i++)
        array->vet[i] = vetor[i];

    array->length = array->Max_length = n;
    return true;
}

/* Ordenação */

bool Intercalar(tipo* A, int inicio, int meio, int fim) {
	tipo* B = (tipo*)malloc((fim - inicio + 1) * sizeof(tipo));
    if (B == NULL)
        return false;
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
    free(B);
    
    return true;
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

void Particionar(tipo* A, int inicio, int fim, tipo pivo, int* i, int* j) {
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

void BubbleSort(Vector* array, int n) {
    if (array->vet == NULL || array->length <= 0)
        return;
    
    for (int i = n - 1; i >= 0; i--) {  // Aqui poderia ser: for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < i; j++) {	// Aqui poderia ser: for (int j = 0; j < n - i - 1; j++)
			if (array->vet[j] > array->vet[j + 1]) {
				tipo aux = array->vet[j];	
				array->vet[j] = array->vet[j + 1];
				array->vet[j + 1] = aux; 
			}
		}
	}
}

void BubbleSort_Recursivo(Vector* array, int n) {
    if (array->vet == NULL || array->length <= 0)
        return;
    
	if (n > 1) {
		for (int i = 1; i < n; i++) {
			if (array->vet[i - 1] > array->vet[i]) {
				tipo aux = array->vet[i - 1];
				array->vet[i - 1] = array->vet[i];
				array->vet[i] = aux;
			}	
		}
		BubbleSort_Recursivo(array, n - 1);
	}
}

void SelectionSort(Vector* array, int n) {
    if (array->vet == NULL || array->length <= 0)
        return;
    
    for (int i = 0; i < n - 1; i++) {
		int posicao = i;
		for (int j = i + 1; j < n; j++) {
			if (array->vet[posicao] > array->vet[j]) 
				posicao = j;
		}	
		tipo aux = array->vet[posicao];
		array->vet[posicao] = array->vet[i];
		array->vet[i] = aux;
	}

}

void SelectionSort_Recursivo(Vector* array, int n) {
    if (array->vet == NULL || array->length <= 0)
        return;

    if (n > 1) {
		int posicao = 0;
		for (int i = 1; i < n; i++) {
			if (array->vet[posicao] < array->vet[i])
				posicao = i;
		}
		tipo aux = array->vet[n - 1];
		array->vet[n - 1] = array->vet[posicao]; 
		array->vet[posicao] = aux;
		
		SelectionSort_Recursivo(array, n - 1);
	}
}

void InsertionSort(Vector* array, int n) {
	if (array->vet == NULL || array->length <= 0)
        return;
    
    if (n > 1) {
		InsertionSort(array, n - 1);
		int i = n - 1;
		while (i > 0 && array->vet[i] < array->vet[i - 1]) {
			tipo aux = array->vet[i];
			array->vet[i] = array->vet[i - 1]; 
			array->vet[i - 1] = aux;
			i--;
		}
	}	
}


bool MergeSort(Vector* array, int inicio, int fim) {
	if (array->vet == NULL || array->length <= 0)
        return false;
    
    if (inicio < fim) {
		int meio = (inicio + fim) / 2;
		MergeSort(array, inicio, meio);
		MergeSort(array, meio + 1, fim);
		return Intercalar(array->vet, inicio, meio, fim);
	}
    return true;
}

void QuickSort(Vector* array, int inicio, int fim) {
	if (array->vet == NULL || array->length <= 0)
        return;
    
    if (inicio < fim) {
		int i, j;
		tipo pivo;
		if (fim - inicio + 1 == 2)  // Se só tiver 2 elementos no vetor
			pivo = array->vet[inicio];
		else {
			int meio = (inicio + fim) / 2;
			pivo = mediana(array->vet[inicio], array->vet[meio], array->vet[fim]);
		}
		Particionar(array->vet, inicio, fim, pivo, &i, &j);
		QuickSort(array, inicio, j);
		QuickSort(array, i, fim);
	}
}	

void vector_sort(Vector* array) {
    if (array->vet == NULL || array->length <= 0)
        return;
    else if (array->length <= 16) 
        InsertionSort(array, array->length);
    else
        QuickSort(array, 0, array->length - 1);
}

bool vector_choose_sort(Vector* array, SortType tipo) {
    if (array->vet == NULL || array->length <= 0)
        return false;

    switch(tipo) {
        case SORT_BUBBLE:
            BubbleSort(array, array->length);
            return true;
        case SORT_BUBBLE_REC:
            BubbleSort_Recursivo(array, array->length);
            return true;
        case SORT_SELECTION:
            SelectionSort(array, array->length);
            return true;
        case SORT_SELECTION_REC:
            SelectionSort_Recursivo(array, array->length);
            return true;
        case SORT_INSERTION:
            InsertionSort(array, array->length);
            return true;
        case SORT_MERGE:
            return MergeSort(array, 0, array->length - 1);
        case SORT_QUICK:
            QuickSort(array, 0, array->length - 1);
            return true;
        default:
            return false;
    }
}

/* Ordenação */
