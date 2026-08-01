#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "c_string.h"
#include "vector_edge.h"
#include "edge.h"

static bool increase_size(Edge** vet, int* n) {   // Realoca o tamanho do vetor
    int length = 2 * (*n);
    Edge* array = (Edge*)realloc(*vet, length * sizeof(Edge));
    if (array == NULL)  
        return false;
    *vet = array;
    *n = length;
    return true;
}



Vector_edge vector_edge_new_with_size(int tamanho) {    // Inicializa um Vector_edge com a capacidade passada como argumento na função
    if (tamanho <= 0)
        tamanho = VECTOR_EDGE_DEFAULT_CAPACITY;
    
    Vector_edge array;
    array.vet = (Edge*) calloc(tamanho, sizeof(Edge));
    if (array.vet == NULL)
        array.capacity = 0;
    else
        array.capacity = tamanho;
    array.length = 0;
    return array;
}

Vector_edge vector_edge_new_with_cvet(const Edge* vetor, int n) {  // Inicializa um Vector_edge com uma cópia de um vetor padrão da linguagem C com o seu respectivo tamanho
    Vector_edge array;
    array.vet = NULL;
    if (!vector_edge_copy_cvet(&array, vetor, n))
        array.capacity = array.length = 0;
    return array;
}

Vector_edge vector_edge_new() {    // Inicializa um Vector_edge com a capacidade padrão
    return vector_edge_new_with_size(VECTOR_EDGE_DEFAULT_CAPACITY);
}

float vector_edge_get_weight(const Vector_edge* array, const Edge aresta) {   // Procura se existe a aresta do segundo parâmetro e, se existir, será retornado o seu respectivo peso.
    if (vector_edge_is_empty(array))
        return -1;
    
    int posicao = vector_edge_search_n(array, aresta);
    if (posicao < 0)
        return -1;
    return array->vet[posicao].peso;
}

float vector_edge_get_weight_cstr_cstr(const Vector_edge* array, const char* u, const char* v) {  // Procura se existe a aresta com extremidades representadas pelo segundo e terceiro parâmetros e, se existir, será retornado o seu respectivo peso. 
    if (vector_edge_is_empty(array))
        return -1;
    
    int posicao = vector_edge_search_n_cstr_cstr(array, u, v);
    if (posicao < 0)
        return -1;
    return array->vet[posicao].peso;
}

bool vector_edge_update_weight(Vector_edge* array, const Edge aresta, float novo_peso) {  // Muda o peso de uma aresta, caso essa aresta exista em Vector_edge
    if (vector_edge_is_empty(array))
        return false;
    
    int posicao = vector_edge_search_n(array, aresta);
    if (posicao < 0)
        return false;
    array->vet[posicao].peso = novo_peso;
    return true;
}

bool vector_edge_update_weight_cstr_cstr(Vector_edge* array, const char* u1, const char* u2, float novo_peso) {  // Muda o peso de uma aresta, caso essa aresta exista em Vector_edge
    if (vector_edge_is_empty(array))
        return false;
    
    int posicao = vector_edge_search_n_cstr_cstr(array, u1, u2);
    if (posicao < 0)
        return false;
    array->vet[posicao].peso = novo_peso;
    return true;
}

bool vector_edge_contains_vertex(const Vector_edge* array, const char* vertice) {  // Verifica se um vértice aparece em alguma aresta.
    if (vector_edge_is_empty(array))
        return false;
    
    for (int i = 0; i < array->length; i++) {
        if (string_equals_cstr(&array->vet[i].u, vertice) || string_equals_cstr(&array->vet[i].v, vertice))
            return true;
    }
    return false;
}

Vector_edge vector_edge_get_edges_of(const Vector_edge* array, const char* vertice) {  // Retorna todas as arestas de um vértice. 
    if (vector_edge_is_empty(array))
        return vector_edge_new_with_size(1);
    
    Vector_edge arestas = vector_edge_new_with_size(array->length / 2);  // Um tamanho não muito grande
    for (int i = 0; i < array->length; i++) {
        if (string_equals_cstr(&array->vet[i].u, vertice) || string_equals_cstr(&array->vet[i].v, vertice))
            vector_edge_append(&arestas, array->vet[i]);
    }
    return arestas;
}



bool vector_edge_is_empty(const Vector_edge* array) {   // Verifica se o Vector_edge é vazio.
    if (array == NULL || array->vet == NULL || array->length == 0)
        return true;
    return false;
}

bool vector_edge_append(Vector_edge* array, const Edge aresta) {   // Adiciona ao final de Vector_edge o elemento do segundo parâmetro
    if (array == NULL || array->vet == NULL)
        return false;
    if (array->length >= array->capacity) {
        if (!increase_size(&(array->vet), &array->capacity))  
            return false;
    }
    
    array->vet[array->length] = edge_new_empty();
    edge_copy(&array->vet[array->length], &aresta);
    array->length++;
    return true;
}

bool vector_edge_append_cstr_cstr(Vector_edge* array, const char* u1, const char* u2) {  // Cria um tipo Edge com os últimos dois parâmetros e adiciona esse tipo ao final de array
    return vector_edge_append_cstr_cstr_weight_direction(array, u1, u2, 0, false);
}

bool vector_edge_append_cstr_cstr_weight_direction(Vector_edge* array, const char* u1, const char* u2, float peso, bool dir) {  // Cria um tipo Edge com os últimos quatro parâmetros e adiciona esse tipo ao final de array
    if (array == NULL || array->vet == NULL || u1 == NULL || u2 == NULL)
        return false;
     if (array->length >= array->capacity) {
        if (!increase_size(&(array->vet), &array->capacity))   
            return false;
    }
    
    Edge aresta = edge_new_cstr_cstr(u1, u2, peso, dir);
    array->vet[array->length] = aresta;
    array->length++;
    return true;
}

bool vector_edge_insert(Vector_edge* array, int posicao, const Edge aresta) {  // Adiciona o elemento do terceiro parâmetro na posicao indicada no segundo parâmetro
    if (array == NULL || array->vet == NULL)
        return false;
        
    return vector_edge_insert_cstr_cstr_weight_direction(array, posicao, string_cstr(&aresta.u), string_cstr(&aresta.v), aresta.peso, aresta.direcionado);
}

bool vector_edge_insert_cstr_cstr(Vector_edge* array, int posicao, const char* u1, const char* u2) {  // Cria um tipo Edge com os últimos dois parâmetros e adiciona esse tipo em array na posição indicada no segundo parâmetro
    return vector_edge_insert_cstr_cstr_weight_direction(array, posicao, u1, u2, 0, false);
}

bool vector_edge_insert_cstr_cstr_weight_direction(Vector_edge* array, int posicao, const char* u1, const char* u2, float peso, bool dir) {  // Cria um tipo Edge com os últimos quatro parâmetros e adiciona esse tipo em array na posição indicada no segundo parâmetro
    if (array == NULL || array->vet == NULL || u1 == NULL || u2 == NULL)
        return false;
    if (array->length >= array->capacity) {
        if (!increase_size(&(array->vet), &array->capacity))   
            return false;
    }
    if (posicao < 0) 
        posicao = 0;
    else if (posicao > array->length)
        posicao = array->length;
    
    for (int i = array->length - 1; i >= posicao; i--)
        array->vet[i + 1] = array->vet[i];

    array->vet[posicao] = edge_new_cstr_cstr(u1, u2, peso, dir);
    array->length++;
    return true;
}

bool vector_edge_insert_ordered_n(Vector_edge* array, const Edge aresta) {  // Adiciona o elemento do segundo parâmetro em Vector_edge de forma ordenada por nome das extremidades
    if (array == NULL || array->vet == NULL)
        return false;
    return vector_edge_insert_ordered_n_cstr_cstr_weight_direction(array, string_cstr(&aresta.u), string_cstr(&aresta.v), aresta.peso, aresta.direcionado);
}

bool vector_edge_insert_ordered_n_cstr_cstr(Vector_edge* array, const char* u1, const char* u2) {  // Cria um tipo Edge com os últimos dois parâmetros e adiciona esse tipo de forma ordenada por nome
    return vector_edge_insert_ordered_n_cstr_cstr_weight_direction(array, u1, u2, 0, false);
}

bool vector_edge_insert_ordered_n_cstr_cstr_weight_direction(Vector_edge* array, const char* u1, const char* u2, float peso, bool dir) {   // Cria um tipo Edge com os últimos quatro parâmetros e adiciona esse tipo de forma ordenada por nome
    if (array == NULL || array->vet == NULL || u1 == NULL || u2 == NULL)
        return false;
    if (array->length >= array->capacity) {
        if (!increase_size(&(array->vet), &array->capacity))   
            return false;
    }
    
    int posicao = 0;
    while (posicao < array->length && edge_compare_n_cstr_cstr(&array->vet[posicao], u1, u2, dir) < 0) {
        posicao++;
    }
    
    for (int i = array->length - 1; i >= posicao; i--)  
        array->vet[i + 1] = array->vet[i];

    array->vet[posicao] = edge_new_cstr_cstr(u1, u2, peso, dir);
    array->length++;
    return true;
    
}

bool vector_edge_insert_ordered_w(Vector_edge* array, const Edge aresta) {  // Adiciona o elemento do segundo parâmetro em Vector_edge de forma ordenada por peso
    if (array == NULL || array->vet == NULL)
        return false;
    return vector_edge_insert_ordered_w_cstr_cstr_weight_direction(array, string_cstr(&aresta.u), string_cstr(&aresta.v), aresta.peso, aresta.direcionado);
}

bool vector_edge_insert_ordered_w_cstr_cstr(Vector_edge* array, const char* u1, const char* u2) {  // Cria um tipo Edge com os últimos dois parâmetros e adiciona esse tipo de forma ordenada por peso
    return vector_edge_insert_ordered_w_cstr_cstr_weight_direction(array, u1, u2, 0, false);
}

bool vector_edge_insert_ordered_w_cstr_cstr_weight_direction(Vector_edge* array, const char* u1, const char* u2, float peso, bool dir) {   // Cria um tipo Edge com os últimos quatro parâmetros e adiciona esse tipo de forma ordenada por peso
    if (array == NULL || array->vet == NULL || u1 == NULL || u2 == NULL)
        return false;
    if (array->length >= array->capacity) {
        if (!increase_size(&(array->vet), &array->capacity))   
            return false;
    }
    
    int posicao = 0;
    while (posicao < array->length && edge_compare_w_weight(&array->vet[posicao], peso) < 0) {
        posicao++;
    }
    
    for (int i = array->length - 1; i >= posicao; i--)  
        array->vet[i + 1] = array->vet[i];

    array->vet[posicao] = edge_new_cstr_cstr(u1, u2, peso, dir);
    array->length++;
    return true;
}

bool vector_edge_at(const Vector_edge* array, int posicao, Edge* retorno) {   // Retorna no terceiro parâmetro uma cópia do elemento da posição indicada no segundo parâmetro.
    if (vector_edge_is_empty(array))
        return false;
    else if (posicao < 0 || posicao >= array->length)
        return false;
    edge_copy(retorno, &array->vet[posicao]);
    return true;
}

int vector_edge_search_n(const Vector_edge* array, const Edge aresta) {  // Procura a primeira ocorrência do elemento indicado no segundo parâmetro em Vector_edge como comparação sendo por nome
    if (vector_edge_is_empty(array))
        return -1;
    
    for (int i = 0; i < array->length; i++) {
        if (edge_equals_n(&array->vet[i], &aresta))
            return i;
    }
} 

int vector_edge_search_n_cstr_cstr(const Vector_edge* array, const char* u1, const char* u2) {  // Procura a primeira ocorrência de uma aresta com as extremidades u1 e u2.
    if (vector_edge_is_empty(array))
        return -1;
    
    for (int i = 0; i < array->length; i++) {
        if (edge_equals_n_cstr_cstr(&array->vet[i], u1, u2, true))
            return i;
    }
    return -1;
}
  
int vector_edge_search_w(const Vector_edge* array, const Edge aresta) { // Procura a primeira ocorrência do elemento indicado no segundo parâmetro em Vector_edge como comparação sendo por peso
    if (vector_edge_is_empty(array))
        return -1;
    return vector_edge_search_w_weight(array, aresta.peso);
}

int vector_edge_search_w_weight(const Vector_edge* array, float peso) {  // Mesma ideia da função anterior, mas é passado apenas o peso para a procura.
    if (vector_edge_is_empty(array))
        return -1;
    
    for (int i = 0; i < array->length; i++) {
        if (edge_equals_w_weight(&array->vet[i], peso))
            return i;
    }
    return -1;
}

int vector_edge_binary_search_n(const Vector_edge* array, const Edge aresta) {  // Procura a primeira ocorrência do elemento indicado no segundo parâmetro em um Vector_edge com o campo vet ordenado como comparação sendo por nome. 
        if (vector_edge_is_empty(array))
            return -1;
    
        int i = 0, j = array->length - 1;
        int media;
	
        while (i <= j) {
	        media = (i + j) / 2;
		int comp = edge_compare_n(&array->vet[media], &aresta);   // como não sei se a aresta é ou não direcionada, assumo que seja direcionada
		if (comp == 0)
			return media;
		else if (comp < 0)
			i = media + 1;
		else
			j = media - 1;
	}
	return -1;
} 

int vector_edge_binary_search_n_cstr_cstr(const Vector_edge* array, const char* u1, const char* u2) {  // Mesma ideia da função anterior, mas é passado apenas os nomes dos vértices para a procura.
        if (vector_edge_is_empty(array))
            return -1;
        int i = 0, j = array->length - 1;
	int media;
	
	while (i <= j) {
		media = (i + j) / 2;
		int comp = edge_compare_n_cstr_cstr(&array->vet[media], u1, u2, true);   // como não sei se a aresta é ou não direcionada, assumo que seja direcionada
		if (comp == 0)
			return media;
		else if (comp < 0)
			i = media + 1;
		else
			j = media - 1;
	}
	return -1;
}

int vector_edge_binary_search_w(const Vector_edge* array, const Edge aresta) {  // Procura a primeira ocorrência do elemento indicado no segundo parâmetro em um Vector_edge com o campo vet ordenado como comparação sendo por peso.
    if (vector_edge_is_empty(array))
        return -1;
    return vector_edge_binary_search_w_weight(array, aresta.peso);
}

int vector_edge_binary_search_w_weight(const Vector_edge* array, float peso) { // Mesma ideia da função anterior, mas é passado apenas o peso para a procura.
    if (vector_edge_is_empty(array))
            return -1;
        int i = 0, j = array->length - 1;
	int media;
	
	while (i <= j) {
		media = (i + j) / 2;
		int comp = edge_compare_w_weight(&array->vet[media], peso);
		if (comp == 0)
			return media;
		else if (comp < 0)
			i = media + 1;
		else
			j = media - 1;
	}
	return -1;
} 

bool vector_edge_pop(Vector_edge* array, Edge* retorno) {  // Remove o elemento de Vector_edge da última posição e retorna este elemento como cópia no segundo parâmetro
    if (vector_edge_is_empty(array))
        return false;
    
    edge_copy(retorno, &array->vet[array->length]);
    edge_free(&array->vet[array->length]);
    array->length--;
    return true;
}

bool vector_edge_pop_at(Vector_edge* array, int posicao, Edge* retorno) {  //  Remove o elemento de Vector_edge da posição indicada no segundo parâmetro e este elemento é retornado no terceiro parâmetro como cópia.
    if (vector_edge_is_empty(array) || posicao < 0 || posicao >= array->length)
        return false;
    
    edge_copy(retorno, &array->vet[posicao]);
    edge_free(&array->vet[posicao]);
    for (int i = posicao; i < array->length - 1; i++)
        array->vet[i] = array->vet[i + 1];
    array->length--;
    return true;
}

bool vector_edge_remove_n(Vector_edge* array, const Edge aresta) {   // Remove a primeira ocorrência do elemento do segundo parâmetro em Vector_edge como comparação sendo por nome.
    if (vector_edge_is_empty(array))
        return false;
    
    int posicao = -1;
    for (int i = 0; i < array->length; i++) {
        if (edge_equals_n(&array->vet[i], &aresta)) {
            posicao = i;
            break;
        }
    }
    if (posicao == -1)   // se for igual a -1, então não encontrou o elemento
        return false;
        
    edge_free(&array->vet[posicao]);   
    for (int i = posicao; i < array->length - 1; i++)
        array->vet[i] = array->vet[i + 1];
    array->length--;
    return true;
}

bool vector_edge_remove_n_cstr_cstr(Vector_edge* array, const char* u1, const char* u2) {  // Mesma ideia da função anterior, mas é passado apenas os nomes dos vértices para a remoção.
    if (vector_edge_is_empty(array))
        return false;
    
    int posicao = -1;
    for (int i = 0; i < array->length; i++) {
        if (edge_equals_n_cstr_cstr(&array->vet[i], u1, u2, true)) {
            posicao = i;
            break;
        }
    }
    if (posicao == -1)   // se for igual a -1, então não encontrou o elemento
        return false;
        
    edge_free(&array->vet[posicao]);   
    for (int i = posicao; i < array->length - 1; i++)
        array->vet[i] = array->vet[i + 1];
    array->length--;
    return true;
}

bool vector_edge_remove_w(Vector_edge* array, const Edge aresta) {  // Remove a primeira ocorrência do elemento do segundo parâmetro em Vector_edge como comparação sendo por peso.
    if (vector_edge_is_empty(array))
        return false;
    return vector_edge_remove_w_weight(array, aresta.peso);
}

bool vector_edge_remove_w_weight(Vector_edge* array, float peso) {  // Mesma ideia da função anterior, mas é passado apenas o peso para a remoção
    if (vector_edge_is_empty(array))
        return false;
    
    int posicao = -1;
    for (int i = 0; i < array->length; i++) {
        if (edge_equals_w_weight(&array->vet[i], peso)) {
            posicao = i;
            break;
        }
    }
    if (posicao == -1)   // se for igual a -1, então não encontrou o elemento
        return false;
        
    edge_free(&array->vet[posicao]);   
    for (int i = posicao; i < array->length - 1; i++)
        array->vet[i] = array->vet[i + 1];
    array->length--;
    return true;
}

int vector_edge_length(const Vector_edge* array) {  // Retorna o número de elementos de Vector_edge.
    if (array == NULL)
        return 0;
    return array->length;
}

int vector_edge_size(const Vector_edge* array) {  // Mesma ideia da função anterior
    if (array == NULL)
        return 0;
    return array->length;
}

int vector_edge_count_w(const Vector_edge* array, float peso) {  // Retorna a quantidade de ocorrências que o peso do segundo parâmetro aparece em Vector_edge
    if (vector_edge_is_empty(array))
        return 0;
    
    int count = 0;
    for (int i = 0; i < array->length; i++) {
        if (edge_equals_w_weight(&array->vet[i], peso))
            count++;
    }
    return count; 
}

void vector_edge_clear(Vector_edge* array) {    // Considera todo dado disponível em Vector_edge como lixo de memória
     if (array == NULL || array->vet == NULL)
        return;
    
    for (int i = 0; i < array->length; i++) 
        edge_free(&array->vet[i]);
    array->length = 0;
}

void vector_edge_free(Vector_edge* array) {   // Libera a memória de Vector_edge
    if (array == NULL || array->vet == NULL)
        return;
    
    for (int i = 0; i < array->length; i++) 
        edge_free(&array->vet[i]);
    free(array->vet);      
    array->vet = NULL;
    array->capacity = array->length = 0;
   
}

bool vector_edge_copy_cvet(Vector_edge* array, const Edge* vetor, int n) { // Copia os dados de vetor padrão da linguagem C para Vector_edge.
    if (array == NULL || vetor == NULL || n <= 0)
        return false;
    Edge* aux = (Edge*) calloc(n, sizeof(Edge));
    if (aux == NULL)
        return false;
    
    for (int i = 0; i < n; i++) {
        if (!edge_copy(&aux[i], &vetor[i])) {   // Se falhar, então é preciso liberar a memória auxiliar
            for (int j = 0; j < n; j++)
                edge_free(&aux[i]);
            free(aux);
            return false;
        }   
    }
    
    if (array->vet != NULL)  // Se já tiver alguma alocação, então libera a memória antiga
        vector_edge_free(array);
    
    array->vet = aux;
    array->capacity = array->length = n;
    return true;
}

bool vector_edge_copy(Vector_edge* array1, const Vector_edge* array2) {   // Copia os dados do segundo parâmetro para o primeiro.
    if (array1 == NULL || array2 == NULL || array2->vet == NULL)
        return false;
    return vector_edge_copy_cvet(array1, array2->vet, array2->length);
} 

String vector_edge_to_string(const Vector_edge* array) {  // Retorna a representação de Vector_edge como String.
    if (vector_edge_is_empty(array))
        return string_new_with_cstr("[]");
    
    String cadeia = string_new_with_size(6 * array->length + 2);
    if (!string_is_valid(&cadeia))
        return string_new_with_cstr("[]");
    
    String edge_str;
    string_append(&cadeia, '[');
    for (int i = 0; i < array->length; i++) {
        edge_str = edge_to_string(&array->vet[i]);
        string_concat(&cadeia, &edge_str);
        if (i < array->length - 1) 
            string_concat_cstr(&cadeia, ", ");
         string_free(&edge_str); 
    }
    string_append(&cadeia, ']');
    return cadeia;
}

void vector_edge_print(const Vector_edge* array) {  // Imprime na tela uma representação de Vector_edge usando a função vector_edge_to_string().
    String cadeia = vector_edge_to_string(array);
    string_print(&cadeia);
    string_free(&cadeia);
}

void vector_edge_println(const Vector_edge* array) {   // Usa a função vector_edge_print() e imprime adicionalmente um caractere '\n' ao final
    vector_edge_print(array);
    printf("\n");
}

Edge* vector_edge_to_cvet(const Vector_edge* array) {  // Retorna uma cópia do campo vet de Vector_edge ou nulo se não conseguir.
    if (array == NULL)
        return NULL;
    Edge* retorno = (Edge*) calloc(array->length, sizeof(Edge));
    if (retorno == NULL)
        return NULL;
    
    for (int i = 0; i < array->length; i++)
        edge_copy(&retorno[i], &array->vet[i]);
    return retorno;
}

const Edge* vector_edge_cvet(const Vector_edge* array) {  // Retorna o próprio campo de vet de Vector_edge como constante,
    if (array == NULL)
        return NULL;
    return array->vet;
}


/* Algoritmos e funções auxiliares para ordenação */
static bool Intercalar_n(Edge* A, int inicio, int meio, int fim) {    // Função privada auxiliar para o MergeSort_n */
    Edge* B = (Edge*)malloc((fim - inicio + 1) * sizeof(Edge));
    if (B == NULL)
        return false;
    int i = inicio, j = meio + 1, n = 0;
	while (i <= meio && j <= fim) { 
		if (edge_compare_n(&A[i], &A[j]) < 0) {
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

static bool Intercalar_w(Edge* A, int inicio, int meio, int fim) {    // Função privada auxiliar para o MergeSort_w */
    Edge* B = (Edge*)malloc((fim - inicio + 1) * sizeof(Edge));
    if (B == NULL)
        return false;
    int i = inicio, j = meio + 1, n = 0;
	while (i <= meio && j <= fim) { 
		if (edge_compare_w(&A[i], &A[j]) < 0) {
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

static Edge mediana_n(const Edge* A, const Edge* B, const Edge* C) {    // Função privada auxiliar para o QuickSort_n */
	Edge resultado;
	bool A_menor_que_B = edge_compare_n(A, B) <= 0 ? true : false;
	bool A_maior_que_B = !A_menor_que_B;
	bool A_menor_que_C = edge_compare_n(A, C) <= 0 ? true : false;
	bool A_maior_que_C = !A_menor_que_C;
	bool B_menor_que_C = edge_compare_n(B, C) <= 0 ? true : false;
	bool B_maior_que_C = !B_menor_que_C;
	
	if ((A_menor_que_C && B_maior_que_C) || (B_menor_que_C && A_maior_que_C))
		resultado = *C;
	else if ((A_maior_que_B && A_menor_que_C) || (A_maior_que_C && A_menor_que_B))
		resultado = *A;
	else
		resultado = *B;
	return resultado; 
}

static Edge mediana_w(const Edge* A, const Edge* B, const Edge* C) {    // Função privada auxiliar para o QuickSort_w */
	Edge resultado;
	bool A_menor_que_B = edge_compare_w(A, B) <= 0 ? true : false;
	bool A_maior_que_B = !A_menor_que_B;
	bool A_menor_que_C = edge_compare_w(A, C) <= 0 ? true : false;
	bool A_maior_que_C = !A_menor_que_C;
	bool B_menor_que_C = edge_compare_w(B, C) <= 0 ? true : false;
	bool B_maior_que_C = !B_menor_que_C;
	
	if ((A_menor_que_C && B_maior_que_C) || (B_menor_que_C && A_maior_que_C))
		resultado = *C;
	else if ((A_maior_que_B && A_menor_que_C) || (A_maior_que_C && A_menor_que_B))
		resultado = *A;
	else
		resultado = *B;
	return resultado; 
}

static void Particionar_n(Edge* A, int inicio, int fim, const Edge pivo, int* i, int* j) {    // Função privada auxiliar para o QuickSort_n */
	*i = inicio; *j = fim;
	Edge aux;
	while (*i <= *j) {
		while (edge_compare_n(&A[*i], &pivo) < 0) 
			(*i)++;
		while (edge_compare_n(&A[*j], &pivo) > 0)
			(*j)--;
		if (*i <= *j) {
			aux = A[*i];
			A[*i] = A[*j];
			A[*j] = aux;
			(*i)++; (*j)--; 
		}
	
	}
}

static void Particionar_w(Edge* A, int inicio, int fim, const Edge pivo, int* i, int* j) {    // Função privada auxiliar para o QuickSort_w*/
	*i = inicio; *j = fim;
	Edge aux;
	while (*i <= *j) {
		while (edge_compare_w(&A[*i], &pivo) < 0) 
			(*i)++;
		while (edge_compare_w(&A[*j], &pivo) > 0)
			(*j)--;
		if (*i <= *j) {
			aux = A[*i];
			A[*i] = A[*j];
			A[*j] = aux;
			(*i)++; (*j)--; 
		}
	
	}
}


static void InsertionSort_edge_n(Vector_edge* array, int n) {
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return;
    
    if (n > 1) {
		InsertionSort_edge_n(array, n - 1);
		int i = n - 1;
		while (i > 0 && edge_compare_n(&array->vet[i], &array->vet[i - 1]) < 0) {
			Edge aux = array->vet[i];
			array->vet[i] = array->vet[i - 1]; 
			array->vet[i - 1] = aux;
			i--;
		}
	}	
}

static void InsertionSort_edge_w(Vector_edge* array, int n) {
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return;
    
    if (n > 1) {
		InsertionSort_edge_w(array, n - 1);
		int i = n - 1;
		while (i > 0 && edge_compare_w(&array->vet[i], &array->vet[i - 1]) < 0) {
			Edge aux = array->vet[i];
			array->vet[i] = array->vet[i - 1]; 
			array->vet[i - 1] = aux;
			i--;
		}
	}
}

static bool MergeSort_edge_n(Vector_edge* array, int inicio, int fim) {
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return false;
    
    if (inicio < fim) {
		int meio = (inicio + fim) / 2;
		MergeSort_edge_n(array, inicio, meio);
		MergeSort_edge_n(array, meio + 1, fim);
		return Intercalar_n(array->vet, inicio, meio, fim);
    }
    return true;
}

static bool MergeSort_edge_w(Vector_edge* array, int inicio, int fim) {
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return false;
    
    if (inicio < fim) {
		int meio = (inicio + fim) / 2;
		MergeSort_edge_w(array, inicio, meio);
		MergeSort_edge_w(array, meio + 1, fim);
		return Intercalar_w(array->vet, inicio, meio, fim);
    }
    return true;
}

static void QuickSort_edge_n(Vector_edge* array, int inicio, int fim) {
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return;
    
    if (inicio < fim) {
		int i, j;
		Edge pivo;
		if (fim - inicio + 1 == 2)  // Se só tiver 2 elementos no vetor
			pivo = array->vet[inicio];
		else {
			int meio = (inicio + fim) / 2;
			pivo = mediana_n(&array->vet[inicio], &array->vet[meio], &array->vet[fim]);
		}
		Particionar_n(array->vet, inicio, fim, pivo, &i, &j);
		QuickSort_edge_n(array, inicio, j);
		QuickSort_edge_n(array, i, fim);
	}
}

static void QuickSort_edge_w(Vector_edge* array, int inicio, int fim) {
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return;
    
    if (inicio < fim) {
		int i, j;
		Edge pivo;
		if (fim - inicio + 1 == 2)  // Se só tiver 2 elementos no vetor
			pivo = array->vet[inicio];
		else {
			int meio = (inicio + fim) / 2;
			pivo = mediana_w(&array->vet[inicio], &array->vet[meio], &array->vet[fim]);
		}
		Particionar_w(array->vet, inicio, fim, pivo, &i, &j);
		QuickSort_edge_w(array, inicio, j);
		QuickSort_edge_w(array, i, fim);
	}
}


void vector_edge_sort_n(Vector_edge* array) {    // Ordenação padrão
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return;
    else if (array->length <= 16) 
        InsertionSort_edge_n(array, array->length);
    else
        QuickSort_edge_n(array, 0, array->length - 1);
}

void vector_edge_sort_w(Vector_edge* array) {    // Ordenação padrão                     
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return;
    else if (array->length <= 16) 
        InsertionSort_edge_w(array, array->length);
    else
        QuickSort_edge_w(array, 0, array->length - 1);
}

bool vector_edge_choose_short(Vector_edge* array, SortType_edge opcao) {    // Ordenação com a escolha passada no segundo parâmetro
    if (array == NULL || array->vet == NULL || array->length <= 0)
        return false;
    switch (opcao) {
        case INSERTION_EDGE_N:
            InsertionSort_edge_n(array, array->length);
            return true;
            break;
        case INSERTION_EDGE_W:
            InsertionSort_edge_w(array, array->length);
            return true;
            break;
        case MERGE_EDGE_N:
            return MergeSort_edge_n(array, 0, array->length - 1);
            break;
        case MERGE_EDGE_W:
            return MergeSort_edge_w(array, 0, array->length - 1);
            break;
        case QUICK_EDGE_N:
            QuickSort_edge_w(array, 0, array->length - 1);
            return true;
            break;
        case QUICK_EDGE_W:
            QuickSort_edge_w(array, 0, array->length - 1);
            return true;
            break;
        default:
            break;
    }
    return false;
}

/* Algoritmos e funções auxiliares para ordenação */


