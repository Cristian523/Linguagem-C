#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "vector.h"
#include "c_string.h"

/* Comparação */
static int number_comparation(tipo_vector a, tipo_vector b) {
    #if defined(TIPO_VECTOR_FLOAT)
        if (fabsf(a - b) < 1e-6f) return 0;
    #elif defined(TIPO_VECTOR_DOUBLE) || defined(TIPO_VECTOR_DOUBLE_G)
        if (fabs(a - b) < 1e-9) return 0;
    #endif
    
    if (a < b) return -1;
    else if (a > b) return 1;
    else return 0;
}
/* Comparação */

static bool increase_size_vector(tipo_vector** vet, int n) {              
    tipo_vector* array = (tipo_vector*)realloc(*vet, n * sizeof(tipo_vector));
    if (array == NULL)  
        return false;
    *vet = array;
    return true;
}

Vector vector_new_with_size(int size) {            // Inicializa um vector com a capacidade passada como argumento na função
    Vector array;
    if (size <= 0)
        size = VECTOR_DEFAULT_CAPACITY;
    
    array.vet = (tipo_vector*)calloc(size, sizeof(tipo_vector));
    array.capacity = size;
    
    if (array.vet == NULL)
        array.capacity = 0;
    
    array.length = 0;
    return array;
}

Vector vector_new_with_cvet(const tipo_vector* vetor, int n) {    // Inicializa um vector com uma cópia de um vetor padrão da linguagem C com o seu respectivo tamanho.
    Vector array;
    array.vet = NULL;
    array.length = array.capacity = 0;
    if (vetor != NULL)
        vector_copy_cvet(&array, vetor, n);
    return array;
}

Vector vector_new() {                                     // Inicializa um vector com a capacidade padrão
    return vector_new_with_size(VECTOR_DEFAULT_CAPACITY);
}

bool vector_is_empty(const Vector* array) {
    if (array == NULL || array->length == 0 || array->vet == NULL) return true;
    else return false;
}

bool vector_append(Vector* array, tipo_vector x) {               // Adiciona ao final de array o elemento do segundo parâmetro.
    if (array == NULL || array->vet == NULL)
        return false;
    int n = array->length;
    int N = array->capacity;
    if (n >= N) {
        N *= 2;
        if (!increase_size_vector(&(array->vet), N))
            return false;
    }

    array->vet[n] = x;
    array->length = ++n;
    array->capacity = N;
    return true;
}

bool vector_insert(Vector* array, int posicao, tipo_vector x) {  // Adiciona o elemento do terceiro parâmetro na posicao indicada no segundo parâmetro.
    if (array == NULL || array->vet == NULL)
        return false;
    int n = array->length;
    int N = array->capacity;
    if (n >= N) {
        N *= 2;
        if (!increase_size_vector(&(array->vet), N))
            return false;
    }

    if (posicao >= n)      // Se for uma posição maior que o tamanho de vet, vai inserir no fim
        posicao = n;
    else if (posicao < 0)  // Se for uma posição menor que 0, vai inserir no inicio
        posicao = 0;

    for (int i = n - 1; i >= posicao; i--) 
        array->vet[i + 1] = array->vet[i];
    
    array->vet[posicao] = x;
    array->length = ++n;
    array->capacity = N;
    return true;
    
}

bool vector_insert_ordered(Vector* array, tipo_vector x) {   // Adiciona o elemento do segundo parâmetro em Vector de forma ordenada
    if (array == NULL || array->vet == NULL)
        return false;
    int n = array->length;
    int N = array->capacity;
    if (n >= N) {
        N *= 2;
        if (!increase_size_vector(&(array->vet), N))
            return false;
    }

    int posicao = 0;
    while (posicao < n && number_comparation(array->vet[posicao], x) < 0)
        posicao++;

    for (int i = n - 1; i >= posicao; i--) 
        array->vet[i + 1] = array->vet[i];

    array->vet[posicao] = x;
    array->length = ++n;
    array->capacity = N;
    return true;
}

bool vector_at(const Vector* array, int posicao, tipo_vector* retorno) {     // Retorna o elemento na posicao indicada 
    if (array == NULL || array->vet == NULL || posicao < 0 || posicao >= array->length)
        return false;
    *retorno = array->vet[posicao];
    return true;
}

int vector_search(const Vector* array, tipo_vector x) {    // Procura a primeira ocorrência em Vector do elemento do segundo parâmetro.
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return -1;
    int posicao = -1;
    for (int i = 0; i < array->length; i++) {
        if (number_comparation(array->vet[i], x) == 0) {
            posicao = i;
            break;
        }    
    }
    return posicao;
}

int vector_binary_search(const Vector* array, tipo_vector x) {    // Procura a primeira ocorrência em Vector do elemento indicado no segundo parâmetro. Só funciona corretamente se o campo vet estiver ordenado!
    // Válido apenas se array for ordenado!
        if (array == NULL || array->vet == NULL || array->length <= 0)
            return -1;
        int i = 0, j = array->length - 1;
	int media;
	
	while (i <= j) {
		media = (i + j) / 2;
		if (number_comparation(array->vet[media], x) == 0)
			return media;
		else if (number_comparation(array->vet[media], x) < 0)
			i = media + 1;
		else
			j = media - 1;
	}
	return -1;
}

bool vector_pop(Vector* array, tipo_vector * retorno) {         // Remove o elemento de Vector da última posição e retorna este elemento no segundo parâmetro.
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return false;    
    *retorno = array->vet[array->length - 1];
    array->length--;
    return true;
}

bool vector_pop_at(Vector* array, int posicao, tipo_vector * retorno) {    // Remove o elemento de Vector da posição indicada no segundo parâmetro e é retornado este elemento no terceiro parâmetro.
    if (array == NULL || array->vet == NULL || array->length <= 0)
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

bool vector_remove(Vector* array, tipo_vector x) {             // Remove a primeira ocorrência do elemento do segundo parâmetro em Vector.
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return false;
    int posicao = -1;
    
    for (int i = 0; i < array->length; i++) {
        if (number_comparation(array->vet[i], x) == 0) {
            posicao = i;
            break;
        }    
    }
    
    if (posicao == -1)
        return false;
    for (int i = posicao; i < array->length - 1; i++)
        array->vet[i] = array->vet[i + 1];

    array->length--;
    return true;
}

int vector_length(const Vector* array) {          // Retorna o número de elementos de Vector. 
    if (array == NULL) return 0;
    return array->length;
}

int vector_size(const Vector* array) {
    if (array == NULL) return 0;
    return array->length;
}

int vector_count(const Vector* array, tipo_vector x) {    // Retorna a quantidade de ocorrências que o elemento do segundo parâmetro aparece em Vector
    if (array == NULL || array->vet == NULL)
        return 0;
    
    int count = 0;
    for (int i = 0; i < array->length; i++) {
        if (number_comparation(array->vet[i], x) == 0)
            count++;
    }
    return count;
}

void vector_clear(Vector* array) {                 // Considera todo dado disponível em Vector como lixo de memória, em outras palavras, "remove" todos os elementos sem liberar a respectiva memória
    if (array != NULL && array->vet != NULL)
        array->length = 0;
}

void vector_free(Vector* array) {                  // Libera a memória de Vector.
    if (array != NULL && array->vet != NULL) {
        free(array->vet);
        array->vet = NULL;
        array->length = array->capacity = 0;
    }
}

bool vector_copy_cvet(Vector* array, const tipo_vector* vetor, int n) {     // Copia os dados de vetor para Vector. Se já tiver uma memória alocada para Vector, esta será liberada para ter a nova atribuição.
    if (array == NULL || vetor == NULL || n <= 0)
        return false;
        
    tipo_vector* vetor_aux = (tipo_vector*) malloc(n * sizeof(tipo_vector));      
    if (vetor_aux == NULL)
        return false;

    for (int i = 0; i < n; i++)
        vetor_aux[i] = vetor[i];
    
    if (array->vet != NULL)        // Se tiver já algum vetor, libera a memória para atribuir ao novo vetor alocado
        free(array->vet); 
    
    array->vet = vetor_aux;
    array->length = array->capacity = n;
    return true;
}

bool vector_copy(Vector* array1, const Vector* array2) {    // Copia os dados do segundo parâmetro para o primeiro.
    if (array2 == NULL)
        return false;
    return vector_copy_cvet(array1, array2->vet, array2->length);
}

String vector_to_string(const Vector* array) {  // Retorna uma representação de Vector como String.
    if (array == NULL || array->vet == NULL || array->length == 0)
        return string_new_with_cstr("[]");
    
    String cadeia = string_new_with_size(4 * array->length);    // Colocando um tamanho razoável
    
    if (string_is_valid(&cadeia)) {
        string_append(&cadeia, '[');
        String string_number = string_new_empty();
        string_free(&string_number);    // liberando a String representado pelo caractere '\0'
        
        for (int i = 0; i < array->length; i++) {
            string_number = TO_STRING_VECTOR(array->vet[i]);
            if (!string_is_empty(&string_number)) {
                string_concat(&cadeia, &string_number);
                if (i < array->length - 1) {
                    string_append(&cadeia, ',');
                    string_append(&cadeia, ' ');
                }
            }
            string_free(&string_number);
        }
        string_append(&cadeia, ']');
    }
    else
        cadeia = string_new_with_cstr("[]");
    
    return cadeia;
}

void vector_print(const Vector* array) {
    String cadeia = vector_to_string(array);
    string_print(&cadeia);
    string_free(&cadeia);
}

void vector_println(const Vector* array) {
    vector_print(array);
    printf("\n");
}

tipo_vector* vector_to_cvet(const Vector* array) {
  tipo_vector* vet_aux = (tipo_vector*) malloc(array->length * sizeof(tipo_vector));
  if (vet_aux == NULL)
      return NULL;
      
  for (int i = 0; i < array->length; i++)
      vet_aux[i] = array->vet[i];
      
  return vet_aux;
}

const tipo_vector* vector_cvet(const Vector* array) {
    return array->vet;
}
    

/* Ordenação */

static bool Intercalar(tipo_vector* A, int inicio, int meio, int fim) {    // Função privada auxiliar para o MergeSort */
    tipo_vector* B = (tipo_vector*)malloc((fim - inicio + 1) * sizeof(tipo_vector));
    if (B == NULL)
    return false;
    int i = inicio, j = meio + 1, n = 0;
        while (i <= meio && j <= fim) { 
		if (number_comparation(A[i], A[j]) < 0) {
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

static tipo_vector mediana(tipo_vector A, tipo_vector B, tipo_vector C) {    // Função privada auxiliar para o QuickSort */
	tipo_vector resultado;
	if ((number_comparation(C, A) >= 0 && number_comparation(C, B) <= 0) || (number_comparation(C, B) >= 0 && number_comparation(C, A) <= 0))
		resultado = C;
	else if ((number_comparation(A, B) >= 0 && number_comparation(A, C) <= 0) || (number_comparation(A, C) >= 0 && number_comparation(A, B) <= 0))
		resultado = A;
	else
		resultado = B;
	return resultado;
}

static void Particionar(tipo_vector* A, int inicio, int fim, tipo_vector pivo, int* i, int* j) {    // Função privada auxiliar para o QuickSort */
	*i = inicio; *j = fim;
	tipo_vector aux;
	while (*i <= *j) {
		while (number_comparation(A[*i], pivo) < 0) 
			(*i)++;
		while (number_comparation(A[*j], pivo) > 0)
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
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return;
    
    for (int i = n - 1; i >= 0; i--) {  // Aqui poderia ser: for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < i; j++) {	// Aqui poderia ser: for (int j = 0; j < n - i - 1; j++)
			if (number_comparation(array->vet[j], array->vet[j + 1]) > 0) {
				tipo_vector aux = array->vet[j];	
				array->vet[j] = array->vet[j + 1];
				array->vet[j + 1] = aux; 
			}
		}
	}
}

void BubbleSort_Recursivo(Vector* array, int n) {
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return;
    
	if (n > 1) {
		for (int i = 1; i < n; i++) {
			if (number_comparation(array->vet[i - 1], array->vet[i]) > 0) {
				tipo_vector aux = array->vet[i - 1];
				array->vet[i - 1] = array->vet[i];
				array->vet[i] = aux;
			}	
		}
		BubbleSort_Recursivo(array, n - 1);
	}
}

void SelectionSort(Vector* array, int n) {
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return;
    
    for (int i = 0; i < n - 1; i++) {
		int posicao = i;
		for (int j = i + 1; j < n; j++) {
			if (number_comparation(array->vet[posicao], array->vet[j]) > 0)  // Olhe aqui com cuidadoooo! Atenção cuidado totallll
				posicao = j;
		}	
		tipo_vector aux = array->vet[posicao];
		array->vet[posicao] = array->vet[i];
		array->vet[i] = aux;
	}

}

void SelectionSort_Recursivo(Vector* array, int n) {
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return;

    if (n > 1) {
		int posicao = 0;
		for (int i = 1; i < n; i++) {
			if (number_comparation(array->vet[posicao], array->vet[i]) < 0)
				posicao = i;
		}
		tipo_vector aux = array->vet[n - 1];
		array->vet[n - 1] = array->vet[posicao]; 
		array->vet[posicao] = aux;
		
		SelectionSort_Recursivo(array, n - 1);
	}
}

void InsertionSort(Vector* array, int n) {
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return;
    
    if (n > 1) {
		InsertionSort(array, n - 1);
		int i = n - 1;
		while (i > 0 && number_comparation(array->vet[i], array->vet[i - 1]) < 0) {
			tipo_vector aux = array->vet[i];
			array->vet[i] = array->vet[i - 1]; 
			array->vet[i - 1] = aux;
			i--;
		}
	}	
}


bool MergeSort(Vector* array, int inicio, int fim) {
    if (array == NULL || array->vet == NULL || array->length <= 0)
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
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return;
    
    if (inicio < fim) {
		int i, j;
		tipo_vector pivo;
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
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return;
    else if (array->length <= 16) 
        InsertionSort(array, array->length);
    else
        QuickSort(array, 0, array->length - 1);
}

bool vector_choose_sort(Vector* array, SortType escolha) {
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return false;

    switch(escolha) {
        case BUBBLE:
            BubbleSort(array, array->length);
            return true;
        case BUBBLE_REC:
            BubbleSort_Recursivo(array, array->length);
            return true;
        case SELECTION:
            SelectionSort(array, array->length);
            return true;
        case SELECTION_REC:
            SelectionSort_Recursivo(array, array->length);
            return true;
        case INSERTION:
            InsertionSort(array, array->length);
            return true;
        case MERGE:
            return MergeSort(array, 0, array->length - 1);
        case QUICK:
            QuickSort(array, 0, array->length - 1);
            return true;
        default:
            return false;
    }
}

/* Ordenação */
