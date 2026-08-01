#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include "c_string.h"
#include "hash_table_ew.h"

/* Protótipos das funções auxiliares de lista encadeada usando apenas apontadores de No_hash_ew */
static bool insert_begin_list(No_hash_ew**, const Edge, float);   // Insere o par chave-valor no inicio da lista encadeada
static No_hash_ew* search_list(No_hash_ew*, const Edge);   // Busca um determinada chave na lista encadeada
static No_hash_ew* search_list_str_str(No_hash_ew*, const String, const String);   // Busca um determinada chave na lista encadeada
static bool remove_list(No_hash_ew**, const Edge);      // Remove uma chave da lista encadeada
static void free_list(No_hash_ew**);     // Remove todos os elementos da lista encadeada
/* Protótipos das funções auxiliares de lista encadeada usando apenas apontadores de No_hash_ew */

/* Protótipos de outras funções auxiliares */
static bool is_primo(int);       // verifica se um dado inteiro é primo
static int proximo_primo(int);   // obtém o próximo primo comparado ao valor da função
static void QuickSort(KeyValue_ew*, int, int);   // Ordenação para um array comum de KeyValue_ew
/* Protótipos de outras funções auxiliares */


static No_hash_ew** create_new_array(int new_capacity) {    // cria o array de apontadores de No
    No_hash_ew** novo = (No_hash_ew**) calloc(new_capacity, sizeof(No_hash_ew*));
    return novo;
}

static int dispersal_cstr(int capacity, const char* caracteres) {  // Função de dispersão para String
    unsigned long hash = 5381;
    int i = 0;
    while (caracteres[i] != '\0') {
        hash = hash * 33 + caracteres[i];
        i++;
    }
    int result = (int)(hash % capacity);
    return result;
}

static int dispersal(int capacity, const Edge K) {   // Função de dispersão para Edge
    String aux_str = string_concat_new_str_cstr(&K.u, "|");
    string_concat(&aux_str, &K.v);
    int inteiro = dispersal_cstr(capacity, string_cstr(&aux_str));
    string_free(&aux_str);
    return inteiro;
}


HashTable_ew hash_table_ew_new() {  // Cria uma HashTable_ew com a capacidade HASH_TABLE_EW_DEFAULT_CAPACITY.
     return hash_table_ew_new_with_capacity(HASH_TABLE_EW_DEFAULT_CAPACITY);
}

HashTable_ew hash_table_ew_new_with_capacity(int capacidade) {  // Cria uma HashTable_ew a partir de uma capacidade inicial. 
    if (capacidade < 0)
        capacidade = HASH_TABLE_EW_DEFAULT_CAPACITY;
    HashTable_ew tabela;
    tabela.vet = create_new_array(capacidade);
    if (tabela.vet == NULL)
        tabela.capacity = 0;
    else
        tabela.capacity = capacidade;
    tabela.size = 0;
    return tabela;
}

HashTable_ew hash_table_ew_new_with_size(int n) {  // Cria uma HashTable_ew a partir de um número de elementos. 
    int capacidade;
    if (n <= 12)
        capacidade = HASH_TABLE_EW_MIN_CAPACITY;
    else {
        capacidade = n / LOAD_FACTOR_EW;
        capacidade = proximo_primo(capacidade);
    }
    return hash_table_ew_new_with_capacity(capacidade);
}

bool hash_table_ew_is_empty(const HashTable_ew* tabela) {   // Verifica se a tabela está vazia. 
    if (tabela == NULL || tabela->vet == NULL || tabela->size == 0)
        return true;
    return false;
}

int hash_table_ew_size(const HashTable_ew* tabela) {  // Retorna o número de elementos da tabela. 
    if (tabela == NULL)
        return 0;
    return tabela->size;
}

bool hash_table_ew_put(HashTable_ew* tabela, const Edge chave, float valor) {  // Adiciona o par chave-valor a tabela. 
    if (tabela == NULL)
        return false;
    
    // Verifica primeiro se chave está na tabela. Se sim, aqui será apenas trocado o valor
    int pos = dispersal(tabela->capacity, chave);
    No_hash_ew* existe = search_list(tabela->vet[pos], chave);
    if (existe != NULL) {
        existe->value = valor;
        return true;
    }
    
    
    if ((float) tabela->size / tabela->capacity > LOAD_FACTOR_EW) {  // Então será preciso realocar o tamanho antes da inserção;
        int capacidade_atual = 2 * tabela->size;
        if (!is_primo(capacidade_atual))
            capacidade_atual = proximo_primo(capacidade_atual);
        
        No_hash_ew** aux = create_new_array(capacidade_atual);
        if (aux == NULL)
            return false;
        
        for (int i = 0; i < tabela->capacity; i++) {
            No_hash_ew* p = tabela->vet[i];
            while (p != NULL) {
                int posicao = dispersal(capacidade_atual, p->key);
                if (!insert_begin_list(&aux[posicao], p->key, p->value)) {   // Se não for possível inserir, libero a memória auxiliar e retorno false
                    for (int j = 0; j < capacidade_atual; j++)
                        free_list(&aux[j]);
                    free(aux);
                    return false;
                }
                p = p->Prox;
            }
        }
        
        for (int i = 0; i < tabela->capacity; i++)  // Liberando a memória antiga
            free_list(&tabela->vet[i]);
        free(tabela->vet);
        
        // Atribuindo a nova memória alocada
        tabela->vet = aux;
        tabela->capacity = capacidade_atual;
    }
    
    pos = dispersal(tabela->capacity, chave);
    if (!insert_begin_list(&tabela->vet[pos], chave, valor))
        return false;
    tabela->size++;
    return true;
}

bool hash_table_ew_contains_key(const HashTable_ew* tabela, const Edge chave) {  // Retorna um valor lógico indicando se a chave do segundo parâmetro existe na tabela.
     if (hash_table_ew_is_empty(tabela))
        return false;
        
    int posicao = dispersal(tabela->capacity, chave);    
    No_hash_ew* p = search_list(tabela->vet[posicao], chave);
    return p != NULL;
}

bool hash_table_ew_contains_key_cstr_cstr(const HashTable_ew* tabela, const char* a, const char* b) {  // @ Mesma ideia da função anterior, 
    String aux1 = string_new_with_cstr(a);
    String aux2 = string_new_with_cstr(b);
    
    bool resultado = hash_table_ew_contains_key_str_str(tabela, aux1, aux2);
    string_free(&aux1);    string_free(&aux2);
    return resultado;
}

bool hash_table_ew_contains_key_str_str(const HashTable_ew* tabela, const String a, const String b) {  // @ Mesma ideia da função anterior, 
    if (hash_table_ew_is_empty(tabela))
        return false;
        
    String aux = string_concat_new_str_cstr(&a, "|");
    string_concat(&aux, &b);
    int posicao = dispersal_cstr(tabela->capacity, string_cstr(&aux));
    string_free(&aux);
    No_hash_ew* p = search_list_str_str(tabela->vet[posicao], a, b);
    return p != NULL;
}

bool hash_table_ew_get(const HashTable_ew* tabela, const Edge chave, float* retorno) {  // Retorna, no terceiro parâmetro da função, o valor da chave passado no segundo parâmetro. 
    if (hash_table_ew_is_empty(tabela))
        return false;
        
    int posicao = dispersal(tabela->capacity, chave);    
    No_hash_ew* p = search_list(tabela->vet[posicao], chave);
    if (p == NULL)
        return false;
    *retorno = p->value;
    return true;
}

bool hash_table_ew_get_str_str(const HashTable_ew* tabela, const String a, const String b, float* retorno) {  // Mesma ideia da função anterior, mas com os parâmetros do meio representando uma aresta.
    if (hash_table_ew_is_empty(tabela))
        return false;
        
    String aux = string_concat_new_str_cstr(&a, "|");
    string_concat(&aux, &b);
    int posicao = dispersal_cstr(tabela->capacity, string_cstr(&aux));  
    string_free(&aux);
    
    No_hash_ew* p = search_list_str_str(tabela->vet[posicao], a, b);
    if (p == NULL)
        return false;
    *retorno = p->value;
    return true;
}

bool hash_table_ew_get_cstr_cstr(const HashTable_ew* tabela, const char* a, const char* b, float* retorno) {  // Mesma ideia da função anterior, mas com os parâmetros do meio representando uma aresta.
    if (hash_table_ew_is_empty(tabela))
        return false;
        
    String aux = string_concat_new_cstr_cstr(a, "|");
    string_concat_cstr(&aux, b);
    int posicao = dispersal_cstr(tabela->capacity, string_cstr(&aux));  
    string_free(&aux);
    
    String a_aux = string_new_with_cstr(a);
    String b_aux = string_new_with_cstr(b);
    
    No_hash_ew* p = search_list_str_str(tabela->vet[posicao], a_aux, b_aux);
    string_free(&a_aux);
    string_free(&b_aux);
    
    if (p == NULL)
        return false;
    *retorno = p->value;
    return true;
}

bool hash_table_ew_remove(HashTable_ew* tabela, const Edge K) {  // Remove o par chave-valor da tabela usando a chave passada no segundo parâmetro. 
    if (hash_table_ew_is_empty(tabela))
        return false;
    int posicao = dispersal(tabela->capacity, K);
    if (remove_list(&tabela->vet[posicao], K)) {
        tabela->size--;
        return true;
    }
    return false;
}

void hash_table_ew_free(HashTable_ew* tabela) {  // Libera a memória da tabela. 
    if (tabela != NULL || tabela->vet != NULL) {
        for (int i = 0; i < tabela->capacity; i++) 
            free_list(&tabela->vet[i]);
        free(tabela->vet);
        tabela->vet = NULL;
        tabela->capacity = tabela->size = 0;
    }
}

Edge* hash_table_ew_get_keys(const HashTable_ew* tabela) {  // Retorna todas as chaves de tabela. 
    if (hash_table_ew_is_empty(tabela))
        return NULL;
    Edge* vetor = (Edge*) calloc(tabela->size, sizeof(Edge));
    if (vetor == NULL)
        return NULL;
    
    int j = 0;
    for (int i = 0; i < tabela->capacity; i++) {
        No_hash_ew* p = tabela->vet[i];
        while (p != NULL) {
            edge_copy(&vetor[j], &p->key);   
            p = p->Prox;
            j++;
        }
    }
    return vetor;
}

KeyValue_ew* hash_table_ew_get_keys_values(const HashTable_ew* tabela) {  // Retorna todos os pares chave-valor da tabela. 
    if (hash_table_ew_is_empty(tabela))
        return NULL;
    KeyValue_ew* vetor = (KeyValue_ew*) calloc(tabela->size, sizeof(KeyValue_ew));
    if (vetor == NULL)
        return NULL;
    
    int j = 0;
    for (int i = 0; i < tabela->capacity; i++) {
        No_hash_ew* p = tabela->vet[i];
        while (p != NULL) {
            edge_copy(&vetor[j].key, &p->key);   // suponho que essa atribuição sempre funcionará
            vetor[j].value = p->value;
            p = p->Prox;
            j++;
        }
    }
    return vetor;
}

String hash_table_ew_to_string(const HashTable_ew* tabela) {   // Retorna uma representação da tabela como String
    if (hash_table_ew_is_empty(tabela))
        return string_new_with_cstr("{}");
    
    String cadeia = string_new_with_size(6 * tabela->size + 2);   // Um tamanho não muito grande, mas não muito pequeno para uma possível realocação
    if (!string_is_valid(&cadeia))
        return string_new_with_cstr("{}");
    KeyValue_ew* vet = hash_table_ew_get_keys_values(tabela);
    if (vet == NULL) {
        string_free(&cadeia);
        return string_new_with_cstr("{}");
    }
    QuickSort(vet, 0, tabela->size - 1);   // Ordenando para ter na String os pares chave-valor de forma ordenada
    String valor_str = string_new_empty();    string_free(&valor_str);
    String chave_str = string_new_empty();    string_free(&chave_str);
    
    string_append(&cadeia, '{');
    for (int i = 0; i < tabela->size; i++) {
        valor_str = string_from_float(vet[i].value, 2);
        chave_str = edge_to_string(&vet[i].key);
        if (!string_is_empty(&valor_str) && !string_is_empty(&chave_str)) {
            string_concat(&cadeia, &chave_str);
            string_concat_cstr(&cadeia, ": ");
            string_concat(&cadeia, &valor_str);
        }
        if (i < tabela->size - 1)
            string_concat_cstr(&cadeia, ", ");
        string_free(&valor_str);
        string_free(&chave_str);
    }
    string_append(&cadeia, '}');
    
    for (int i = 0; i < tabela->size; i++)
        edge_free(&vet[i].key);
    free(vet);
    return cadeia;
}

void hash_table_ew_print(const HashTable_ew* tabela) {   // Imprime a String da função anterior
    String cadeia = hash_table_ew_to_string(tabela);
    string_print(&cadeia);
    string_free(&cadeia);
}

void hash_table_ew_println(const HashTable_ew* tabela) {   // Usa a função anterior e imprime o caractere '\n' no final
    hash_table_ew_print(tabela);
    printf("\n");
}



/* Funções de lista encadeada usando apenas apontadores de No_hash_ew */
static bool insert_begin_list(No_hash_ew ** L, const Edge K, float V) {   // Insere no inicio da lista encadeada L o par chave-valor
        if (L == NULL)
	    return false;
	No_hash_ew * n = (No_hash_ew*)calloc(1, sizeof(No_hash_ew));
	if (n == NULL)
		return false;
	edge_copy(&n->key, &K);      
	n->value = V; 
        n->Prox = *L;
	*L = n;
	return true;
}


static No_hash_ew* search_list(No_hash_ew * L, const Edge K) {    // Busca um determinada chave na lista encadeada
        No_hash_ew* p = L;
	while (p != NULL) {
		if (edge_equals_n(&p->key, &K))	
			return p;
		else
			p = p->Prox;
	}
	return NULL;
}

static No_hash_ew* search_list_str_str(No_hash_ew * L, const String u, const String v) {    // Busca um determinada chave na lista encadeada
        No_hash_ew* p = L;
	while (p != NULL) {
		if (edge_equals_n_cstr_cstr(&p->key, string_cstr(&u), string_cstr(&v), true))	
			return p;
		else
			p = p->Prox;
	}
	return NULL;
}


static bool remove_list(No_hash_ew ** L, const Edge K) {    // Remove o par chave-valor está na lista L.
        if (L == NULL || *L == NULL)
	    return false;
	No_hash_ew * p = *L;
	No_hash_ew * pAnt = NULL;
	while (p != NULL && edge_compare_n(&p->key, &K) != 0) {
		pAnt = p;
		p = p->Prox;
	} 
	if (p != NULL) {
		if (pAnt != NULL)
			pAnt->Prox = p->Prox;
		else
			*L = p->Prox;
		edge_free(&p->key);
		free(p);
		return true;
	}
	return false;
}

static void free_list(No_hash_ew ** L) {    // Libera a memória da lista encadeada
	if (L == NULL)
	    return;
	while (*L != NULL) {
		No_hash_ew * p = *L;
		*L = (*L)->Prox;
		edge_free(&p->key);
		free(p);
	}
}
/* Funções de lista encadeada usando apenas apontadores de No_hash_ew */










/* Outras funções auxiliares */
static bool is_primo(int n) {    // Verifica se n é um número primo usando a ideia de n pode ser primo até um i <= √n
    if (n <= 1)   // O objetivo aqui é saber apenas para inteiros positivos maiores que 1
        return false;
    int raiz = sqrt(n);
    for (int i = 2; i <= raiz; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

static int proximo_primo(int n) {   // Procura o próximo primo
    if (n < 0)
        return -1;    // O objetivo aqui é obter primos positivos
    n++;
    while (n <= INT_MAX) {
        if (is_primo(n))
            return n;
        n++;
    }
    return -1;     // Não conseguiu encontrar o próximo primo
}




/* Implementação do QuickSort para um array comum */
static Edge mediana(Edge A, Edge B, Edge C) {
	Edge resultado;
	if ((edge_compare_n(&C, &A) >= 0 && edge_compare_n(&C, &B) <= 0) || (edge_compare_n(&C, &B) >= 0 && edge_compare_n(&C, &A) <= 0))
		resultado = C;
	else if ((edge_compare_n(&A, &B) >= 0 && edge_compare_n(&A, &C) <= 0) || (edge_compare_n(&A, &C) >= 0 && edge_compare_n(&A, &B) <= 0))
		resultado = A;
	else
		resultado = B;
	return resultado;
}

static void Particionar(KeyValue_ew A[], int inicio, int fim, const Edge pivo, int* i, int* j) {
	*i = inicio; *j = fim;
	KeyValue_ew aux;
	while (*i <= *j) {
		while (edge_compare_n(&A[*i].key, &pivo) < 0) 
			(*i)++;
		while (edge_compare_n(&A[*j].key, &pivo) > 0)
			(*j)--;
		if (*i <= *j) {
			aux = A[*i];
			A[*i] = A[*j];
			A[*j] = aux;
			(*i)++; (*j)--; 
		}
	
	}
}

static void QuickSort(KeyValue_ew vet[], int inicio, int fim) {
	if (vet == NULL) return;
	if (inicio < fim) {
		int i, j;
		Edge pivo;
		if (fim - inicio + 1 == 2)  // Se só tiver 2 elementos no vetor
			pivo = vet[inicio].key;
		else {
			int meio = (inicio + fim) / 2;
			pivo = mediana(vet[inicio].key, vet[meio].key, vet[fim].key);
		}
		Particionar(vet, inicio, fim, pivo, &i, &j);
		QuickSort(vet, inicio, j);
		QuickSort(vet, i, fim);  
	}
}
/* Implementação do QuickSort para um array comum */
/* Outras funções auxiliares */





