#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vector_str.h"
#include "c_string.h"


static bool increase_size_vector_str(String** vet, int n) {              
    String* array = (String*)realloc(*vet, n * sizeof(String));
    if (array == NULL)  
        return false;
    *vet = array;
    return true;
}

Vector_str vector_str_new_with_size(int size) {            // Inicializa um Vector_str com a capacidade passada como argumento na função
    Vector_str array;
    if (size <= 0)
        size = VECTOR_STR_DEFAULT_CAPACITY;
    
    array.vet = (String*)calloc(size, sizeof(String));
    array.capacity = size;
    
    if (array.vet == NULL)
        array.capacity = 0;
      
    array.length = 0;
    return array;
}

Vector_str vector_str_new_with_cvet(const String* vetor, int n) {    // Inicializa um Vector_str com uma cópia de um vetor padrão da linguagem C com o seu respectivo tamanho.
    Vector_str array;
    array.vet = NULL;
    array.length = array.capacity = 0;
    if (vetor != NULL)
        vector_str_copy_cvet(&array, vetor, n);
    return array;
    
}

Vector_str vector_str_new_with_cvet_cstr(const char** vetor, int n) {  // Inicializa uma string copiando todo o conteúdo de um vetor de caracteres padrão da linguagem C, mas aqui é um vetor de char*
    Vector_str array;
    array.vet = NULL;
    array.length = array.capacity = 0;
    if (vetor != NULL)
        vector_str_copy_cvet_cstr(&array, vetor, n);
    return array;
}


Vector_str vector_str_new() {                                     // Inicializa um Vector_str com a capacidade padrão
    return vector_str_new_with_size(VECTOR_STR_DEFAULT_CAPACITY);
}

bool vector_str_is_empty(const Vector_str* array) {
    if (array == NULL || array->length == 0 || array->vet == NULL) return true;
    else return false;
}

bool vector_str_append(Vector_str* array, const String x) {               // Adiciona ao final de array o elemento do segundo parâmetro.
    if (array == NULL || array->vet == NULL)
        return false;
    int n = array->length;
    int N = array->capacity;
    if (n >= N) {
        N *= 2;
        if (!increase_size_vector_str(&(array->vet), N))
            return false;
    }

    string_copy(&array->vet[n], &x);
    array->length = ++n;
    array->capacity = N;
    return true;
}

bool vector_str_append_cstr(Vector_str* array, const char* caracteres) {     // Chama a função anterior
    String cadeia = string_new_with_cstr(caracteres);
    if (!string_is_valid(&cadeia)) {
        string_free(&cadeia);
        return false;
    }
    else if (!vector_str_append(array, cadeia)) {
        string_free(&cadeia);
        return false;
    }
    string_free(&cadeia);
    return true;
}

bool vector_str_insert(Vector_str* array, int posicao, const String x) {  // Adiciona o elemento do terceiro parâmetro na posicao indicada no segundo parâmetro.
    if (array == NULL || array->vet == NULL)
        return false;
    int n = array->length;
    int N = array->capacity;
    if (n >= N) {
        N *= 2;
        if (!increase_size_vector_str(&(array->vet), N))
            return false;
    }

    if (posicao >= n)      // Se for uma posição maior que o tamanho de vet, vai inserir no fim
        posicao = n;
    else if (posicao < 0)  // Se for uma posição menor que 0, vai inserir no inicio
        posicao = 0;
    
    for (int i = n - 1; i >= posicao; i--) {    
        array->vet[i+1] = array->vet[i];
    }
    
    array->vet[posicao] = string_new_empty();  // Estava tendo problema gravissimo com a linha de baixo, por isso essa atribuição aqui foi necessária. Melhor isto do que varios string_copy's no loop acima.
    string_copy(&array->vet[posicao], &x);    // Problema gravíssimo
    
    array->length = ++n;
    array->capacity = N;
    return true;
    
}

bool vector_str_insert_cstr(Vector_str* array, int posicao, const char* caracteres) {    // Chama a função anterior
    String cadeia = string_new_with_cstr(caracteres);
    if (!string_is_valid(&cadeia)) {
        string_free(&cadeia);
        return false;
    }
    else if (!vector_str_insert(array, posicao, cadeia)) {
        string_free(&cadeia);
        return false;
    }
    string_free(&cadeia);
    return true;
}

bool vector_str_insert_ordered(Vector_str* array, const String x) {   // Adiciona o elemento do segundo parâmetro em Vector_str de forma ordenada
    if (array == NULL || array->vet == NULL)
        return false;
    int n = array->length;
    int N = array->capacity;
    if (n >= N) {
        N *= 2;
        if (!increase_size_vector_str(&(array->vet), N))
            return false;
    }

    int posicao = 0;
    while (posicao < n && string_compare(&array->vet[posicao], &x) < 0)
        posicao++;

    for (int i = n - 1; i >= posicao; i--) 
        array->vet[i + 1] = array->vet[i];
  
    array->vet[posicao] = string_new_empty();  // Estava tendo problema gravissimo com a linha de baixo, por isso essa atribuição aqui foi necessária. Melhor isto do que varios string_copy's no loop acima.
    string_copy(&array->vet[posicao], &x);     
    
    array->length = ++n;
    array->capacity = N;
    return true;
}

bool vector_str_insert_ordered_cstr(Vector_str* array, const char* caracteres) {     // Chama a função anterior
    String cadeia = string_new_with_cstr(caracteres);
    if (!string_is_valid(&cadeia)) {
        string_free(&cadeia);
        return false;
    }
    else if (!vector_str_insert_ordered(array, cadeia)) {
        string_free(&cadeia);
        return false;
    }
    string_free(&cadeia);
    return true;
}

bool vector_str_at(const Vector_str* array, int posicao, String* retorno) {     // Retorna o elemento na posicao indicada 
    if (array == NULL || array->vet == NULL || posicao < 0 || posicao >= array->length)
        return false;
    string_copy(retorno, &array->vet[posicao]);
    return true;
}

int vector_str_search(const Vector_str* array, const String x) {    // Procura a primeira ocorrência em Vector_str do elemento do segundo parâmetro.
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return -1;
    int posicao = -1;
    for (int i = 0; i < array->length; i++) {
        if (string_compare(&array->vet[i], &x) == 0) {
            posicao = i;
            break;
        }    
    }
    return posicao;
}

int vector_str_search_cstr(const Vector_str* array, const char* caracteres) {     // Chama a função anterior
    String cadeia = string_new_with_cstr(caracteres);
    if (!string_is_valid(&cadeia)) {
        string_free(&cadeia);
        return -1;
    }
    int posicao = vector_str_search(array, cadeia);
    string_free(&cadeia);
    return posicao;
}

int vector_str_binary_search(const Vector_str* array, const String x) {    // Procura a primeira ocorrência em Vector_str do elemento indicado no segundo parâmetro. Só funciona corretamente se o campo vet estiver ordenado!
    // Válido apenas se array for ordenado!
        if (array == NULL || array->vet == NULL || array->length <= 0)
            return -1;
        int i = 0, j = array->length - 1;
	int media;
	
	while (i <= j) {
		media = (i + j) / 2;
		if (string_compare(&array->vet[media], &x) == 0)
			return media;
		else if (string_compare(&array->vet[media], &x) < 0)
			i = media + 1;
		else
			j = media - 1;
	}
	return -1;
}

int vector_str_binary_search_cstr(const Vector_str* array, const char* caracteres) {    // Chama a função anterior
     String cadeia = string_new_with_cstr(caracteres);
     if (!string_is_valid(&cadeia)) {
        string_free(&cadeia);
        return -1;
     }
    
    int posicao = vector_str_binary_search(array, cadeia);
    string_free(&cadeia);
    return posicao;
}

bool vector_str_pop(Vector_str* array, String * retorno) {         // Remove o elemento de Vector_str da última posição e retorna este elemento no segundo parâmetro.
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return false;    
    string_copy(retorno, &array->vet[array->length - 1]);
    string_free(&array->vet[array->length - 1]);
    array->length--;
    return true;
}

bool vector_str_pop_at(Vector_str* array, int posicao, String * retorno) {    // Remove o elemento de Vector_str da posição indicada no segundo parâmetro e é retornado este elemento no terceiro parâmetro.
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return false;
    else if (posicao < 0 || posicao >= array->length)
        return false;
    else {
        string_copy(retorno, &array->vet[posicao]);
        string_free(&array->vet[posicao]);
        for (int i = posicao; i < array->length - 1; i++)
            array->vet[i] = array->vet[i + 1];
        
    }
    array->length--;
    return true;
    
}

bool vector_str_remove(Vector_str* array, const String x) {             // Remove a primeira ocorrência do elemento do segundo parâmetro em Vector_str.
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return false;
    int posicao = -1;
    
    for (int i = 0; i < array->length; i++) {
        if (string_compare(&array->vet[i], &x) == 0) {
            posicao = i;
            break;
        }    
    }
    
    if (posicao == -1)
        return false;
    string_free(&array->vet[posicao]);
    for (int i = posicao; i < array->length - 1; i++)
        array->vet[i] = array->vet[i + 1];

    array->length--;
    return true;
}

bool vector_str_remove_cstr(Vector_str* array, const char* caracteres) {     // Chama a função anterior
    String cadeia = string_new_with_cstr(caracteres);
    if (!string_is_valid(&cadeia)) {
        string_free(&cadeia);
        return false;
    }
    else if (!vector_str_remove(array, cadeia)) {
        string_free(&cadeia);
        return false;
    }
    string_free(&cadeia);
    return true;
}

int vector_str_length(const Vector_str* array) {          // Retorna o número de elementos de Vector_str. 
    if (array == NULL) return 0;
    return array->length;
}

int vector_str_size(const Vector_str* array) {     // Mesma ideia da função anterior 
    if (array == NULL) return 0;
    return array->length;
}

int vector_str_count(const Vector_str* array, const String x) {    // Retorna a quantidade de ocorrências que o elemento do segundo parâmetro aparece em Vector_str
    if (array == NULL || array->vet == NULL)
        return 0;
    
    int count = 0;
    for (int i = 0; i < array->length; i++) {
        if (string_compare(&array->vet[i], &x) == 0)
            count++;
    }
    return count;
}

int vector_str_count_cstr(const Vector_str* array, const char* caracteres) {   // Chama a função anterior
    String cadeia = string_new_with_cstr(caracteres);
    if (!string_is_valid(&cadeia)) {
        string_free(&cadeia);
        return -1;
    }
    int count = vector_str_count(array, cadeia);
    
    string_free(&cadeia);
    return count;
}

void vector_str_clear(Vector_str* array) {        // Considera todo dado disponível em Vector_str como lixo de memória, em outras palavras, "remove" todos os elementos sem liberar a respectiva memória de Vector (as strings sim)
    if (array != NULL && array->vet != NULL) {
        for (int i = 0; i < array->length; i++)
            string_free(&array->vet[i]);
        array->length = 0;
    }
}

void vector_str_free(Vector_str* array) {                  // Libera a memória de Vector_str.
    if (array != NULL && array->vet != NULL) {
        for (int i = 0; i < array->length; i++)
            string_free(&array->vet[i]);
        free(array->vet);
        array->vet = NULL;
        array->length = array->capacity = 0;
    }
}

bool vector_str_copy_cvet(Vector_str* array, const String* vetor, int n) {     // Copia os dados de vetor para Vector_str. Se já tiver uma memória alocada para Vector_str, esta será liberada para ter a nova atribuição.
    if (array == NULL || vetor == NULL || n <= 0)
        return false;
        
    String* vetor_aux = (String*) calloc(n, sizeof(String));      
    if (vetor_aux == NULL)
        return false;

    for (int i = 0; i < n; i++) {
        if (!string_copy(&vetor_aux[i], &vetor[i])) {
            for (int j = 0; j <= i; i++)
                string_free(&vetor_aux[i]);
            free(&vetor_aux);
            return false;
        }
            
    }
    
    if (array->vet != NULL)  {     // Se tiver já algum vetor, libera a memória para atribuir ao novo vetor alocado
        for (int i = 0; i < array->length; i++)
            string_free(&array->vet[i]);
        free(array->vet); 
    }
    array->vet = vetor_aux;
    array->length = array->capacity = n;
    return true;
}

bool vector_str_copy_cvet_cstr(Vector_str* array, const char** vetor, int n) {  // Mesma ideia da função anterior, mas, a fim de ficar mais prático, é passado um vetor de apontador de caracteres mesmo
    if (array == NULL || vetor == NULL || n <= 0)
        return false;
        
    String* vetor_aux = (String*) calloc(n, sizeof(String));      
    if (vetor_aux == NULL)
        return false;

    for (int i = 0; i < n; i++) {
        if (vetor[i] != NULL)
            string_copy_cstr(&vetor_aux[i], vetor[i]);
        else 
            string_copy_cstr(&vetor_aux[i], "NULL");
        
    }
    
    if (array->vet != NULL)  {     // Se tiver já algum vetor, libera a memória para atribuir ao novo vetor alocado
        for (int i = 0; i < array->length; i++)
            string_free(&array->vet[i]);
        free(array->vet); 
    }
    array->vet = vetor_aux;
    array->length = array->capacity = n;
    return true;
}

bool vector_str_copy(Vector_str* array1, const Vector_str* array2) {    // Copia os dados do segundo parâmetro para o primeiro.
    if (array2 == NULL)
        return false;
    return vector_str_copy_cvet(array1, array2->vet, array2->length);
}

String vector_str_to_string(const Vector_str* array) {  // Retorna uma representação de Vector_str como String.
    if (array == NULL || array->vet == NULL || array->length == 0)
        return string_new_with_cstr("[]");
    
    String cadeia = string_new_with_size(4 * array->length);
    
    if (string_is_valid(&cadeia)) {
        string_append(&cadeia, '[');
        String string_aux = string_new_empty();
        string_free(&string_aux);     // liberando a memória da String representado pelo caractere '\0'
        
        for (int i = 0; i < array->length; i++) {
            string_copy(&string_aux, &array->vet[i]);
            if (!string_is_empty(&string_aux)) {
                string_concat(&cadeia, &string_aux);
                if (i < array->length - 1) {
                    string_append(&cadeia, ',');
                    string_append(&cadeia, ' ');
                }
            }
            string_free(&string_aux);
        }
        string_append(&cadeia, ']');
    }
    else
        cadeia = string_new_with_cstr("[]");
    
    return cadeia;
}

void vector_str_print(const Vector_str* array) {
    String cadeia = vector_str_to_string(array);
    string_print(&cadeia);
    string_free(&cadeia);
}

void vector_str_println(const Vector_str* array) {
    vector_str_print(array);
    printf("\n");
}

String* vector_str_to_cvet(const Vector_str* array) {
    String* vet_aux = (String*) calloc(array->length, sizeof(String));
    if (vet_aux == NULL)
        return NULL;
    
    for (int i = 0; i < array->length; i++)
        string_copy(&vet_aux[i], &array->vet[i]);
    return vet_aux;
}

const String* vector_str_cvet(const Vector_str* array) {
    return array->vet;
}
    

/* Ordenação */

static bool Intercalar(String* A, int inicio, int meio, int fim) {    // Função privada auxiliar para o MergeSort */
    String* B = (String*)malloc((fim - inicio + 1) * sizeof(String));
    if (B == NULL)
        return false;
    int i = inicio, j = meio + 1, n = 0;
	while (i <= meio && j <= fim) { 
		if (string_compare(&A[i], &A[j]) < 0) {
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

static String mediana(const String* A, const String* B, const String* C) {    // Função privada auxiliar para o QuickSort */
	String resultado;
	bool A_menor_que_B = string_compare(A, B) <= 0 ? true : false;
	bool A_maior_que_B = !A_menor_que_B;
	bool A_menor_que_C = string_compare(A, C) <= 0 ? true : false;
	bool A_maior_que_C = !A_menor_que_C;
	bool B_menor_que_C = string_compare(B, C) <= 0 ? true : false;
	bool B_maior_que_C = !B_menor_que_C;
	
	if ((A_menor_que_C && B_maior_que_C) || (B_menor_que_C && A_maior_que_C))
		resultado = *C;
	else if ((A_maior_que_B && A_menor_que_C) || (A_maior_que_C && A_menor_que_B))
		resultado = *A;
	else
		resultado = *B;
	return resultado; 
}

static void Particionar(String* A, int inicio, int fim, const String pivo, int* i, int* j) {    // Função privada auxiliar para o QuickSort */
	*i = inicio; *j = fim;
	String aux;
	while (*i <= *j) {
		while (string_compare(&A[*i], &pivo) < 0) 
			(*i)++;
		while (string_compare(&A[*j], &pivo) > 0)
			(*j)--;
		if (*i <= *j) {
			aux = A[*i];
			A[*i] = A[*j];
			A[*j] = aux;
			(*i)++; (*j)--; 
		}
	
	}
}

void BubbleSort_str(Vector_str* array, int n) {
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return;
    
    for (int i = n - 1; i >= 0; i--) {  // Aqui poderia ser: for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < i; j++) {	// Aqui poderia ser: for (int j = 0; j < n - i - 1; j++)
			if (string_compare(&array->vet[j], &array->vet[j + 1]) > 0) {
				String aux = array->vet[j];	
				array->vet[j] = array->vet[j + 1];
				array->vet[j + 1] = aux; 
			}
		}
	}
}

void BubbleSort_Recursivo_str(Vector_str* array, int n) {
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return;
    
	if (n > 1) {
		for (int i = 1; i < n; i++) {
			if (string_compare(&array->vet[i - 1], &array->vet[i]) > 0) {
				String aux = array->vet[i - 1];
				array->vet[i - 1] = array->vet[i];
				array->vet[i] = aux;
			}	
		}
		BubbleSort_Recursivo_str(array, n - 1);
	}
}

void SelectionSort_str(Vector_str* array, int n) {
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return;
    
    for (int i = 0; i < n - 1; i++) {
		int posicao = i;
		for (int j = i + 1; j < n; j++) {
			if (string_compare(&array->vet[posicao], &array->vet[j]) > 0)  // Olhe aqui com cuidadoooo! Atenção cuidado totallll
				posicao = j;
		}	
		String aux = array->vet[posicao];
		array->vet[posicao] = array->vet[i];
		array->vet[i] = aux;
	}

}

void SelectionSort_Recursivo_str(Vector_str* array, int n) {
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return;

    if (n > 1) {
		int posicao = 0;
		for (int i = 1; i < n; i++) {
			if (string_compare(&array->vet[posicao], &array->vet[i]) < 0)
				posicao = i;
		}
		String aux = array->vet[n - 1];
		array->vet[n - 1] = array->vet[posicao]; 
		array->vet[posicao] = aux;
		
		SelectionSort_Recursivo_str(array, n - 1);
	}
}

void InsertionSort_str(Vector_str* array, int n) {
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return;
    
    if (n > 1) {
		InsertionSort_str(array, n - 1);
		int i = n - 1;
		while (i > 0 && string_compare(&array->vet[i], &array->vet[i - 1]) < 0) {
			String aux = array->vet[i];
			array->vet[i] = array->vet[i - 1]; 
			array->vet[i - 1] = aux;
			i--;
		}
	}	
}


bool MergeSort_str(Vector_str* array, int inicio, int fim) {
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return false;
    
    if (inicio < fim) {
		int meio = (inicio + fim) / 2;
		MergeSort_str(array, inicio, meio);
		MergeSort_str(array, meio + 1, fim);
		return Intercalar(array->vet, inicio, meio, fim);
	}
    return true;
}

void QuickSort_str(Vector_str* array, int inicio, int fim) {
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return;
    
    if (inicio < fim) {
		int i, j;
		String pivo;
		if (fim - inicio + 1 == 2)  // Se só tiver 2 elementos no vetor
			pivo = array->vet[inicio];
		else {
			int meio = (inicio + fim) / 2;
			pivo = mediana(&array->vet[inicio], &array->vet[meio], &array->vet[fim]);
		}
		Particionar(array->vet, inicio, fim, pivo, &i, &j);
		QuickSort_str(array, inicio, j);
		QuickSort_str(array, i, fim);
	}
}	

void vector_str_sort(Vector_str* array) {
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return;
    else if (array->length <= 16) 
        InsertionSort_str(array, array->length);
    else
        QuickSort_str(array, 0, array->length - 1);
}

bool vector_str_choose_sort(Vector_str* array, SortType_str escolha) {
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return false;

    switch(escolha) {
        case BUBBLE_STR:
            BubbleSort_str(array, array->length);
            return true;
        case BUBBLE_REC_STR:
            BubbleSort_Recursivo_str(array, array->length);
            return true;
        case SELECTION_STR:
            SelectionSort_str(array, array->length);
            return true;
        case SELECTION_REC_STR:
            SelectionSort_Recursivo_str(array, array->length);
            return true;
        case INSERTION_STR:
            InsertionSort_str(array, array->length);
            return true;
        case MERGE_STR:
            return MergeSort_str(array, 0, array->length - 1);
        case QUICK_STR:
            QuickSort_str(array, 0, array->length - 1);
            return true;
        default:
            return false;
    }
}

/* Ordenação */
