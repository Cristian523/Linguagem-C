#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include "c_string.h"
#include "hash_table.h"

/* Protótipos das funções auxiliares de lista encadeada usando apenas apontadores de No_hash */
static bool insert_begin_list(No_hash**, tipo_key, tipo_value);   // Insere o par chave-valor no inicio da lista encadeada
static No_hash* search_list(No_hash*, tipo_key);   // Busca um determinada chave na lista encadeada
static bool remove_list(No_hash**, tipo_key);      // Remove uma chave da lista encadeada
static void free_list(No_hash**);     // Remove todos os elementos da lista encadeada
/* Protótipos das funções auxiliares de lista encadeada usando apenas apontadores de No_hash */

/* Protótipos de outras funções auxiliares */
static int number_comparation(tipo_key, tipo_key);   // comparação entre números
static bool is_primo(int);       // verifica se um dado inteiro é primo
static int proximo_primo(int);   // obtém o próximo primo comparado ao valor da função
static void QuickSort(KeyValue*, int, int);   // Ordenação para um array comum de KeyValue
/* Protótipos de outras funções auxiliares */

static No_hash** create_new_array(int new_capacity) {    // cria o array de apontadores de No
    No_hash** novo = (No_hash**) calloc(new_capacity, sizeof(No_hash*));
    return novo;
}

static int dispersal(int capacity, tipo_key K) {   // Função de dispersão para tipos primitivos
    const float A = 0.6180339887;  // Constante irracional. É a constante (sqrt(5) - 1) / 2
    int result = (int)(capacity * (K * A - (int)(K * A))); 
    return result < 0 ? result + capacity : result;
}


HashTable hash_table_new() {    // Cria uma HashTable com a capacidade padrão.
    HashTable tabela;
    
    tabela.vet = create_new_array(HASH_TABLE_DEFAULT_CAPACITY);
    if (tabela.vet == NULL) 
        tabela.capacity = 0;
    else
        tabela.capacity = HASH_TABLE_DEFAULT_CAPACITY;
    tabela.size = 0;
    
    return tabela;
}

HashTable hash_table_new_with_capacity(int capacidade) {  // Cria uma HashTable a partir de uma capacidade inicial
    if (capacidade <= 0)
        capacidade = HASH_TABLE_DEFAULT_CAPACITY;
    HashTable tabela;
    tabela.vet = create_new_array(capacidade);
    if (tabela.vet == NULL)
        tabela.capacity = 0;
    else
        tabela.capacity = capacidade;
    tabela.size = 0;
    return tabela;
}


HashTable hash_table_new_with_size(int n) {  // Cria uma HashTable a partir do número de elementos que deseja-se inserir
    HashTable tabela;
    int capacidade_atual;
    if (n <= 12)  // Assumo capacidade HASH_TABLE_MIN_CAPACITY para um n <= 12
        capacidade_atual = HASH_TABLE_MIN_CAPACITY;
    else {
        int aux = n / LOAD_FACTOR;
        capacidade_atual = proximo_primo(aux);
    }
    
    tabela.vet = create_new_array(capacidade_atual);
    if (tabela.vet == NULL) 
        tabela.capacity = 0;
    else
        tabela.capacity = capacidade_atual;
    tabela.size = 0;
    
    return tabela;
} 

bool hash_table_is_empty(const HashTable* tabela) {   // Verifica se a tabela é vazia
    if (tabela == NULL || tabela->vet == NULL || tabela->size == 0)
        return true;
    else
        return false;
}

int hash_table_size(const HashTable* tabela) {   // Retorna o número de elementos da tabela
    if (tabela == NULL)
        return 0;
    return tabela->size;
}

bool hash_table_put(HashTable* tabela, tipo_key chave, tipo_value valor) {  // Adiciona o par chave-valor na tabela
    if (tabela == NULL)
        return false;
    int pos;
    
    // Verifica primeiro se chave está na tabela. Se sim, aqui será apenas trocado o valor
    pos = dispersal(tabela->capacity, chave);
    No_hash* existe = search_list(tabela->vet[pos], chave);
    if (existe != NULL) {
        existe->value = valor;
        return true;
    }
    
    
    if ((float) tabela->size / tabela->capacity > LOAD_FACTOR) {  // Então será preciso realocar o tamanho antes da inserção;
        int capacidade_atual = 2 * tabela->size;
        if (!is_primo(capacidade_atual))
            capacidade_atual = proximo_primo(capacidade_atual);
        
        No_hash** aux = create_new_array(capacidade_atual);
        if (aux == NULL)
            return false;
        
        for (int i = 0; i < tabela->capacity; i++) {
            No_hash* p = tabela->vet[i];
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
    
    // Após essas condições, aqui sim é adicionado o par !!!!!!!!!
    pos = dispersal(tabela->capacity, chave); 
    if (!insert_begin_list(&tabela->vet[pos], chave, valor))
        return false;
    tabela->size++;
    return true;
}

bool hash_table_contains_key(const HashTable* tabela, tipo_key chave) {  // Verifica se a chave do segundo parâmetro existe na tabela
    if (hash_table_is_empty(tabela))
        return false;
    int posicao = dispersal(tabela->capacity, chave);
    No_hash* par = search_list(tabela->vet[posicao], chave);
    return par != NULL;
}


bool hash_table_get(const HashTable* tabela, tipo_key chave, tipo_value* retorno) {  // Retorna, no terceiro parâmetro, o valor da chave correspondente do segundo parâmetro
    if (hash_table_is_empty(tabela))
        return false;
    
    int posicao = dispersal(tabela->capacity, chave);
    No_hash* par = search_list(tabela->vet[posicao], chave);
    if (par == NULL)
        return false;
    *retorno = par->value;
    return true;
}

bool hash_table_remove(HashTable* tabela, tipo_key chave) {  // Remove o par chave-valor da tabela  
    if (hash_table_is_empty(tabela))
        return false;
    int posicao = dispersal(tabela->capacity, chave);
    if (remove_list(&tabela->vet[posicao], chave)) {
        tabela->size--;
        return true;
    }
    return false;
    
}

void hash_table_free(HashTable* tabela) {   // Libera a memória da tabela
    if (tabela != NULL || tabela->vet != NULL) {
        for (int i = 0; i < tabela->capacity; i++)
            free_list(&tabela->vet[i]);
        free(tabela->vet);
        tabela->vet = NULL;
        tabela->capacity = tabela->size = 0;
    }
}

tipo_key* hash_table_get_keys(const HashTable* tabela) {   // Retorna um vetor com todas as chaves da tabela
    if (hash_table_is_empty(tabela))
        return NULL;
    tipo_key* array = (tipo_key*) malloc(tabela->size * sizeof(tipo_key));
    if (array == NULL)
        return NULL;
    
    int j = 0;
    for (int i = 0; i < tabela->capacity; i++) {
        No_hash* p = tabela->vet[i];
        while (p != NULL) {
            array[j] = p->key;   j++;
            p = p->Prox;
        }
    }
    return array;
}

KeyValue* hash_table_get_keys_values(const HashTable* tabela) {  // Retorna um vetor com todos os pares chave-valor da tabela
    if (hash_table_is_empty(tabela))
        return NULL;
    KeyValue* array = (KeyValue*) malloc(tabela->size * sizeof(KeyValue));
    if (array == NULL)
        return NULL;
    
    int j = 0;
    for (int i = 0; i < tabela->capacity; i++) {
        No_hash* p = tabela->vet[i];
        while (p != NULL) {
            array[j].key = p->key;   
            array[j].value = p->value;
            j++;
            p = p->Prox;
        }
    }
    return array;
}

String hash_table_to_string(const HashTable* tabela) {  // Retorna uma representação da tabela como String
    if (hash_table_is_empty(tabela))
        return string_new_with_cstr("{}");
    
    String cadeia = string_new_with_size(6 * tabela->size + 2);   // Um tamanho não muito grande, mas não muito pequeno para uma possível realocação
    if (!string_is_valid(&cadeia))
        return string_new_with_cstr("{}");
    KeyValue* vet = hash_table_get_keys_values(tabela);
    if (vet == NULL) {
        string_free(&cadeia);
        return string_new_with_cstr("{}");
    }  
    QuickSort(vet, 0, tabela->size - 1);   // Ordenando para ter na String os pares chave-valor de forma ordenada
    String chave_str = string_new_empty();    string_free(&chave_str);
    String valor_str = string_new_empty();    string_free(&valor_str);
    
    string_append(&cadeia, '{');
    for (int i = 0; i < tabela->size; i++) {
        chave_str = TO_STRING_KEY(vet[i].key);
        valor_str = TO_STRING_VALUE(vet[i].value);
        if (!string_is_empty(&chave_str) && !string_is_empty(&valor_str)) {
            string_concat(&cadeia, &chave_str);
            string_concat_cstr(&cadeia, ": ");
            string_concat(&cadeia, &valor_str);
        }
        if (i < tabela->size - 1)
            string_concat_cstr(&cadeia, ", ");
        string_free(&chave_str);
        string_free(&valor_str);
    }
    string_append(&cadeia, '}');
    
    free(vet);
    return cadeia;
}

void hash_table_print(const HashTable* tabela) {  // Imprime a String obtida com a função anterior
    String cadeia = hash_table_to_string(tabela);
    string_print(&cadeia);
    string_free(&cadeia);
}

void hash_table_println(const HashTable* tabela) {  // Usa a função anterior e imprime um '\n' ao final
    hash_table_print(tabela);
    printf("\n");
}



/* Funções de lista encadeada usando apenas apontadores de No_hash */
static bool insert_begin_list(No_hash ** L, tipo_key K, tipo_value V) {   // Insere no inicio da lista encadeada L o par chave-valor
	if (L == NULL)
	    return false;
	No_hash * n = (No_hash*)malloc(sizeof(No_hash));
	if (n == NULL) {
		return false;
	}
	n->key = K;  n->value = V;
	n->Prox = *L;
	*L = n;
	return true;
}

static No_hash* search_list(No_hash * L, tipo_key K) {     // Procura se a chave K está na lista L
	No_hash* p = L;
	while (p != NULL) {
		if (p->key == K)	
			return p;
		else
			p = p->Prox;
	}
	return NULL;
}

static bool remove_list(No_hash ** L, tipo_key K) {   // Remove o par chave-valor está na lista L.
	if (L == NULL || *L == NULL)
	    return false;
	No_hash * p = *L;
	No_hash * pAnt = NULL;
	while (p != NULL && number_comparation(p->key, K) != 0) {
		pAnt = p;
		p = p->Prox;
	} 
	if (p != NULL) {
		if (pAnt != NULL)
			pAnt->Prox = p->Prox;
		else
			*L = p->Prox;
		free(p);
		return true;
	}
	return false;
}

static void free_list(No_hash ** L) {    // Libera a memória da lista encadeada
	if (L == NULL)
	    return;
	while (*L != NULL) {
		No_hash * p = *L;
		*L = (*L)->Prox;
		free(p);
	}
}
/* Funções de lista encadeada usando apenas apontadores de No_hash */

/* Outras funções auxiliares */
static int number_comparation(tipo_key A, tipo_key B) {
    if (A < B)
        return -1;
    else if (A > B)
        return 1;
    else
        return 0;
}

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
static tipo_key mediana(tipo_key A, tipo_key B, tipo_key C) {
	tipo_key resultado;
	if ((number_comparation(C, A) >= 0 && number_comparation(C, B) <= 0) || (number_comparation(C, B) >= 0 && number_comparation(C, A) <= 0))
		resultado = C;
	else if ((number_comparation(A, B) >= 0 && number_comparation(A, C) <= 0) || (number_comparation(A, C) >= 0 && number_comparation(A, B) <= 0))
		resultado = A;
	else
		resultado = B;
	return resultado;
}

static void Particionar(KeyValue A[], int inicio, int fim, tipo_key pivo, int* i, int* j) {
	*i = inicio; *j = fim;
	KeyValue aux;
	while (*i <= *j) {
		while (number_comparation(A[*i].key, pivo) < 0) 
			(*i)++;
		while (number_comparation(A[*j].key, pivo) > 0)
			(*j)--;
		if (*i <= *j) {
			aux = A[*i];
			A[*i] = A[*j];
			A[*j] = aux;
			(*i)++; (*j)--; 
		}
	
	}
}

static void QuickSort(KeyValue vet[], int inicio, int fim) {
	if (vet == NULL) return;
	if (inicio < fim) {
		int i, j;
		tipo_key pivo;
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

