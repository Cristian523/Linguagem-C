#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include "c_string.h"
#include "hash_table_sn.h"

/* Protótipos das funções auxiliares de lista encadeada usando apenas apontadores de No_hash_sn */
static bool insert_begin_list(No_hash_sn**, const String, tipo_value_number);   // Insere o par chave-valor no inicio da lista encadeada
static bool insert_begin_list_cstr(No_hash_sn**, const char*, tipo_value_number);   // Insere o par chave-valor no inicio da lista encadeada
static No_hash_sn* search_list(No_hash_sn*, const String);   // Busca um determinada chave na lista encadeada
static No_hash_sn* search_list_cstr(No_hash_sn*, const char*);   // Busca um determinada chave na lista encadeada
static bool remove_list(No_hash_sn**, const String);      // Remove uma chave da lista encadeada
static bool remove_list_cstr(No_hash_sn**, const char*);      // Remove uma chave da lista encadeada
static void free_list(No_hash_sn**);     // Remove todos os elementos da lista encadeada
/* Protótipos das funções auxiliares de lista encadeada usando apenas apontadores de No_hash_sn */

/* Protótipos de outras funções auxiliares */
static bool is_primo(int);       // verifica se um dado inteiro é primo
static int proximo_primo(int);   // obtém o próximo primo comparado ao valor da função
static void QuickSort(KeyValue_sn*, int, int);   // Ordenação para um array comum de KeyValue_sn
/* Protótipos de outras funções auxiliares */

static No_hash_sn** create_new_array(int new_capacity) {    // cria o array de apontadores de No
    No_hash_sn** novo = (No_hash_sn**) calloc(new_capacity, sizeof(No_hash_sn*));
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

static int dispersal(int capacity, const String K) {   // Função de dispersão para String
    return dispersal_cstr(capacity, string_cstr(&K));
}





HashTable_sn hash_table_sn_new() {   // Cria uma HashTable_sn com a capacidade HASH_TABLE_SN_DEFAULT_CAPACITY.
    return hash_table_sn_new_with_capacity(HASH_TABLE_SN_DEFAULT_CAPACITY);
}

HashTable_sn hash_table_sn_new_with_capacity(int capacidade) {  // Cria uma HashTable_sn a partir de uma capacidade inicial
    if (capacidade < 0)
        capacidade = HASH_TABLE_SN_DEFAULT_CAPACITY;
    HashTable_sn tabela;
    tabela.vet = create_new_array(capacidade);
    if (tabela.vet == NULL)
        tabela.capacity = 0;
    else
        tabela.capacity = capacidade;
    tabela.size = 0;
    return tabela;
}

HashTable_sn hash_table_sn_new_with_size(int n) {  //  Cria uma HashTable_sn a partir de um número de elementos
    int capacidade;
    if (n <= 12)
        capacidade = HASH_TABLE_SN_MIN_CAPACITY;
    else {
        capacidade = n / LOAD_FACTOR_SN;
        capacidade = proximo_primo(capacidade);
    }
    return hash_table_sn_new_with_capacity(capacidade);
}

bool hash_table_sn_is_empty(const HashTable_sn* tabela) {   // Verifica se a tabela está vazia.
    if (tabela == NULL || tabela->vet == NULL || tabela->size == 0)
        return true;
    return false;
}

int hash_table_sn_size(const HashTable_sn* tabela) {   // Retorna o número de elementos da tabela
    if (tabela == NULL)
        return 0;
    return tabela->size;
}

bool hash_table_sn_put(HashTable_sn* tabela, const String K, tipo_value_number V) {   // Adiciona o par chave-valor a tabela.
    return hash_table_sn_put_cstr(tabela, string_cstr(&K), V);
}

bool hash_table_sn_put_cstr(HashTable_sn* tabela, const char* chave, tipo_value_number valor) {  // Adiciona o par chave-valor a tabela.
    if (tabela == NULL)
        return false;
    
    // Verifica primeiro se chave está na tabela. Se sim, aqui será apenas trocado o valor
    int pos = dispersal_cstr(tabela->capacity, chave);
    No_hash_sn* existe = search_list_cstr(tabela->vet[pos], chave);
    if (existe != NULL) {
        existe->value = valor;
        return true;
    }
    
    
    if ((float) tabela->size / tabela->capacity > LOAD_FACTOR_SN) {  // Então será preciso realocar o tamanho antes da inserção;
        int capacidade_atual = 2 * tabela->size;
        if (!is_primo(capacidade_atual))
            capacidade_atual = proximo_primo(capacidade_atual);
        
        No_hash_sn** aux = create_new_array(capacidade_atual);
        if (aux == NULL)
            return false;
        
        for (int i = 0; i < tabela->capacity; i++) {
            No_hash_sn* p = tabela->vet[i];
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
    
    pos = dispersal_cstr(tabela->capacity, chave);
    if (!insert_begin_list_cstr(&tabela->vet[pos], chave, valor))
        return false;
    tabela->size++;
    return true;
}

bool hash_table_sn_contains_key(const HashTable_sn* tabela, const String chave) {  // Verifica se a chave do segundo parâmetro existe na tabela
    return hash_table_sn_contains_key_cstr(tabela, string_cstr(&chave));
}

bool hash_table_sn_contains_key_cstr(const HashTable_sn* tabela, const char* chave) {  // Verifica se a chave do segundo parâmetro existe na tabela
    if (hash_table_sn_is_empty(tabela))
        return false;
        
    int posicao = dispersal_cstr(tabela->capacity, chave);    
    No_hash_sn* p = search_list_cstr(tabela->vet[posicao], chave);
    return p != NULL;
}

bool hash_table_sn_get(const HashTable_sn* tabela, const String chave, tipo_value_number* retorno) {  // Retorna, no terceiro parâmetro, a chave do segundo parâmetro da tabela
    return hash_table_sn_get_cstr(tabela, string_cstr(&chave), retorno);
}

bool hash_table_sn_get_cstr(const HashTable_sn* tabela, const char* chave, tipo_value_number* retorno) {  // Retorna, no terceiro parâmetro, a chave do segundo parâmetro da tabela
    if (hash_table_sn_is_empty(tabela))
        return false;
        
    int posicao = dispersal_cstr(tabela->capacity, chave);    
    No_hash_sn* p = search_list_cstr(tabela->vet[posicao], chave);
    if (p == NULL)
        return false;
    *retorno = p->value;
    return true;
}

bool hash_table_sn_remove(HashTable_sn* tabela, const String K) {  // Remove o par chave-valor da tabela usando a chave passada no segundo parâmetro
    return hash_table_sn_remove_cstr(tabela, string_cstr(&K));
}

bool hash_table_sn_remove_cstr(HashTable_sn* tabela, const char* K) {  // Remove o par chave-valor da tabela usando a chave passada no segundo parâmetro
    if (hash_table_sn_is_empty(tabela))
        return false;
    int posicao = dispersal_cstr(tabela->capacity, K);
    if (remove_list_cstr(&tabela->vet[posicao], K)) {
        tabela->size--;
        return true;
    }
    return false;
}

void hash_table_sn_free(HashTable_sn* tabela) {   // Libera a memória da tabela
    if (tabela != NULL || tabela->vet != NULL) {
        for (int i = 0; i < tabela->capacity; i++) 
            free_list(&tabela->vet[i]);
        free(tabela->vet);
        tabela->vet = NULL;
        tabela->capacity = tabela->size = 0;
    }
}

String* hash_table_sn_get_keys(const HashTable_sn* tabela) {   // Retorna todas as chaves da tabela
    if (hash_table_sn_is_empty(tabela))
        return NULL;
    String* vetor = (String*) calloc(tabela->size, sizeof(String));
    if (vetor == NULL)
        return NULL;
    
    int j = 0;
    for (int i = 0; i < tabela->capacity; i++) {
        No_hash_sn* p = tabela->vet[i];
        while (p != NULL) {
            string_copy(&vetor[j], &p->key);   // suponho que essa atribuição sempre funcionará
            p = p->Prox;
            j++;
        }
    }
    return vetor;
}

KeyValue_sn* hash_table_sn_get_keys_values(const HashTable_sn* tabela) {  // Retorna todos os pares chave-valor da tabela
    if (hash_table_sn_is_empty(tabela))
        return NULL;
    KeyValue_sn* vetor = (KeyValue_sn*) calloc(tabela->size, sizeof(KeyValue_sn));
    if (vetor == NULL)
        return NULL;
    
    int j = 0;
    for (int i = 0; i < tabela->capacity; i++) {
        No_hash_sn* p = tabela->vet[i];
        while (p != NULL) {
            string_copy(&vetor[j].key, &p->key);   // suponho que essa atribuição sempre funcionará
            vetor[j].value = p->value;
            p = p->Prox;
            j++;
        }
    }
    return vetor;
}

String hash_table_sn_to_string(const HashTable_sn* tabela) {   // Retorna uma representação da tabela como String
    if (hash_table_sn_is_empty(tabela))
        return string_new_with_cstr("{}");
    
    String cadeia = string_new_with_size(6 * tabela->size + 2);   // Um tamanho não muito grande, mas não muito pequeno para uma possível realocação
    if (!string_is_valid(&cadeia))
        return string_new_with_cstr("{}");
    KeyValue_sn* vet = hash_table_sn_get_keys_values(tabela);
    if (vet == NULL) {
        string_free(&cadeia);
        return string_new_with_cstr("{}");
    }
    QuickSort(vet, 0, tabela->size - 1);   // Ordenando para ter na String os pares chave-valor de forma ordenada
    String valor_str = string_new_empty();    string_free(&valor_str);
    
    string_append(&cadeia, '{');
    for (int i = 0; i < tabela->size; i++) {
        valor_str = TO_STRING_VALUE_NUMBER(vet[i].value);
        if (!string_is_empty(&valor_str)) {
            string_concat(&cadeia, &vet[i].key);
            string_concat_cstr(&cadeia, ": ");
            string_concat(&cadeia, &valor_str);
        }
        if (i < tabela->size - 1)
            string_concat_cstr(&cadeia, ", ");
        string_free(&valor_str);
    }
    string_append(&cadeia, '}');
    
    for (int i = 0; i < tabela->size; i++)
        string_free(&vet[i].key);
    free(vet);
    return cadeia;
}

void hash_table_sn_print(const HashTable_sn* tabela) {   // Imprime a String da função anterior
    String cadeia = hash_table_sn_to_string(tabela);
    string_print(&cadeia);
    string_free(&cadeia);
}

void hash_table_sn_println(const HashTable_sn* tabela) {   // Usa a função anterior e imprime o caractere '\n' no final
    hash_table_sn_print(tabela);
    printf("\n");
}




/* Funções de lista encadeada usando apenas apontadores de No_hash_sn */
static bool insert_begin_list(No_hash_sn ** L, const String K, tipo_value_number V) {   // Insere no inicio da lista encadeada L o par chave-valor
	return insert_begin_list_cstr(L, string_cstr(&K), V);
}

static bool insert_begin_list_cstr(No_hash_sn ** L, const char* K, tipo_value_number V) {
        if (L == NULL)
	    return false;
	No_hash_sn * n = (No_hash_sn*)calloc(1, sizeof(No_hash_sn));
	if (n == NULL)
		return false;
	string_copy_cstr(&n->key, K);      // Suponho que sempre funcionará
	n->value = V; 
        n->Prox = *L;
	*L = n;
	return true;
}

static No_hash_sn* search_list(No_hash_sn * L, String K) {     // Procura se a chave K está na lista L
	return search_list_cstr(L, string_cstr(&K));
}

static No_hash_sn* search_list_cstr(No_hash_sn * L, const char* K) {
        No_hash_sn* p = L;
	while (p != NULL) {
		if (string_equals_cstr(&p->key, K))	
			return p;
		else
			p = p->Prox;
	}
	return NULL;
}

static bool remove_list(No_hash_sn ** L, String K) {   // Remove o par chave-valor está na lista L.
	return remove_list_cstr(L, string_cstr(&K));
}

static bool remove_list_cstr(No_hash_sn ** L, const char* K) {
        if (L == NULL || *L == NULL)
	    return false;
	No_hash_sn * p = *L;
	No_hash_sn * pAnt = NULL;
	while (p != NULL && string_compare_cstr(&p->key, K) != 0) {
		pAnt = p;
		p = p->Prox;
	} 
	if (p != NULL) {
		if (pAnt != NULL)
			pAnt->Prox = p->Prox;
		else
			*L = p->Prox;
		string_free(&p->key);
		free(p);
		return true;
	}
	return false;
}

static void free_list(No_hash_sn ** L) {    // Libera a memória da lista encadeada
	if (L == NULL)
	    return;
	while (*L != NULL) {
		No_hash_sn * p = *L;
		*L = (*L)->Prox;
		string_free(&p->key);
		free(p);
	}
}
/* Funções de lista encadeada usando apenas apontadores de No_hash_sn */



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
static String mediana(String A, String B, String C) {
	String resultado;
	if ((string_compare(&C, &A) >= 0 && string_compare(&C, &B) <= 0) || (string_compare(&C, &B) >= 0 && string_compare(&C, &A) <= 0))
		resultado = C;
	else if ((string_compare(&A, &B) >= 0 && string_compare(&A, &C) <= 0) || (string_compare(&A, &C) >= 0 && string_compare(&A, &B) <= 0))
		resultado = A;
	else
		resultado = B;
	return resultado;
}

static void Particionar(KeyValue_sn A[], int inicio, int fim, const String pivo, int* i, int* j) {
	*i = inicio; *j = fim;
	KeyValue_sn aux;
	while (*i <= *j) {
		while (string_compare(&A[*i].key, &pivo) < 0) 
			(*i)++;
		while (string_compare(&A[*j].key, &pivo) > 0)
			(*j)--;
		if (*i <= *j) {
			aux = A[*i];
			A[*i] = A[*j];
			A[*j] = aux;
			(*i)++; (*j)--; 
		}
	
	}
}

static void QuickSort(KeyValue_sn vet[], int inicio, int fim) {
	if (vet == NULL) return;
	if (inicio < fim) {
		int i, j;
		String pivo;
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

