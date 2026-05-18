#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include "c_string.h"
#include "linked_list_str.h"
#include "hash_table_sls.h"

/* Protótipos das funções auxiliares de lista encadeada usando apenas apontadores de No_hash_sls */
static LinkedList_str linked_list_str_from_cvet_cstr(const char**, int n);  // Retorna uma LinkedList_str a partir de um vetor de apontadores de caracteres. Em caso de falhas será retornado uma lista vazia
static bool insert_begin_list(No_hash_sls**, const String, const String);  // Adiciona na chave um único elemento no valor
static bool insert_begin_list_cstr_cstr(No_hash_sls**, const char*, const char*);   // Adiciona na chave um único elemento no valor
static bool insert_begin_list_key_value(No_hash_sls**, const String, const LinkedList_str);   // Insere o par chave-valor no inicio da lista encadeada
static bool insert_begin_list_key_value_cstr_cvet_cstr(No_hash_sls**, const char*, const char**, int);  // Adiciona chave sendo String e valor sendo LinkedList_str adaptando os parâmetros passados.
static No_hash_sls* search_list(No_hash_sls*, const String);   // Busca um determinada chave na lista encadeada
static No_hash_sls* search_list_cstr(No_hash_sls*, const char*);  // Busca um determinada chave na lista encadeada
static bool remove_list(No_hash_sls**, const String, const String, int*);  // Remove apenas um elemento da lista encadeada do valor de uma determinada chave
static bool remove_list_cstr_cstr(No_hash_sls**, const char*, const char*, int*);  // Remove apenas um elemento da lista encadeada do valor de uma determinada chave
static bool remove_list_key_value(No_hash_sls**, const String);      // Remove uma chave da lista encadeada
static bool remove_list_key_value_cstr(No_hash_sls**, const char*);   // Remove uma chave da lista encadeada
static void free_list(No_hash_sls**);     // Remove todos os elementos da lista encadeada
/* Protótipos das funções auxiliares de lista encadeada usando apenas apontadores de No_hash_sls */

/* Protótipos de outras funções auxiliares */
static bool is_primo(int);       // verifica se um dado inteiro é primo
static int proximo_primo(int);   // obtém o próximo primo comparado ao valor da função
static void QuickSort(KeyValue_sls*, int, int);   // Ordenação para um array comum de KeyValue_sls
/* Protótipos de outras funções auxiliares */

static No_hash_sls** create_new_array(int new_capacity) {    // cria o array de apontadores de No
    No_hash_sls** novo = (No_hash_sls**) calloc(new_capacity, sizeof(No_hash_sls*));
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

static bool increase_hash_table(HashTable_sls * tabela) {   // Aumenta de tamanho a tabela
    if (tabela == NULL)
        return false;
    int capacidade_atual = 2 * tabela->size;
    if (!is_primo(capacidade_atual))
        capacidade_atual = proximo_primo(capacidade_atual);
        
    No_hash_sls** aux = create_new_array(capacidade_atual);
    if (aux == NULL)
        return false;
        
    for (int i = 0; i < tabela->capacity; i++) {
        No_hash_sls* p = tabela->vet[i];
        while (p != NULL) {
            int posicao = dispersal(capacidade_atual, p->key);
            if (!insert_begin_list_key_value(&aux[posicao], p->key, p->value)) {   // Se não for possível inserir, libero a memória auxiliar e retorno false
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
    return true;
}




HashTable_sls hash_table_sls_new() {  // Cria uma HashTable_sls com a capacidade HASH_TABLE_SLS_DEFAULT_CAPACITY.
    HashTable_sls tabela;
    tabela.vet = create_new_array(HASH_TABLE_SLS_DEFAULT_CAPACITY);
    
    if (tabela.vet == NULL) 
        tabela.capacity = 0;
    else
        tabela.capacity = HASH_TABLE_SLS_DEFAULT_CAPACITY;
    tabela.size = 0;
    return tabela;
}

HashTable_sls hash_table_sls_new_with_capacity(int capacidade) {   // Cria uma HashTable_sls a partir de uma capacidade inicial.
    if (capacidade <= 0)
        capacidade = HASH_TABLE_SLS_DEFAULT_CAPACITY;
    HashTable_sls tabela;
    tabela.vet = create_new_array(capacidade);
    
    if (tabela.vet == NULL) 
        tabela.capacity = 0;
    else
        tabela.capacity = capacidade;
    tabela.size = 0;
    return tabela;
}

HashTable_sls hash_table_sls_new_with_size(int n) {  // Cria uma HashTable_sls a partir de um número de elementos
    int capacidade;
    if (n <= 12)
        capacidade = HASH_TABLE_SLS_MIN_CAPACITY;
     else {
        int aux = n / LOAD_FACTOR_SLS;
        capacidade = proximo_primo(aux);
    }
    return hash_table_sls_new_with_capacity(capacidade);
}

bool hash_table_sls_is_empty(const HashTable_sls* tabela) {    // Verifica se a tabela está vazia
    if (tabela == NULL || tabela->vet == NULL || tabela->size == 0)
        return true;
    else
        return false;
}

int hash_table_sls_size(const HashTable_sls* tabela) {    // Retorna o número de elementos da tabela.
    if (tabela == NULL)
        return 0;
    return tabela->size;
}


bool hash_table_sls_put(HashTable_sls* tabela, const String chave, const String valor) {  // Adiciona um único valor à chave passada
    return hash_table_sls_put_cstr_cstr(tabela, string_cstr(&chave), string_cstr(&valor));
}

bool hash_table_sls_put_cstr_cstr(HashTable_sls* tabela, const char* chave, const char* valor) {  // Adiciona um único valor à chave passada
    if (tabela == NULL)
        return false;
    int posicao = dispersal_cstr(tabela->capacity, chave);
    No_hash_sls* p = search_list_cstr(tabela->vet[posicao], chave);
    if (p != NULL) {   // Verificando se a chave já existe
        linked_list_str_insert_ordered_cstr(&p->value, valor);  // supondo que sempre funcionará
        return true;
    }
    if ((float) tabela->size / tabela->capacity > LOAD_FACTOR_SLS) {   // Aumentando o tamanho da tabela se necessário
        if (!increase_hash_table(tabela))
            return false;
    }
    
    posicao = dispersal_cstr(tabela->capacity, chave);
    // Adicionando a chave e um único valor caso não exista
    if (!insert_begin_list_cstr_cstr(&tabela->vet[posicao], chave, valor))
        return false;
    tabela->size++;
    return true;
}

bool hash_table_sls_put_key_value(HashTable_sls* tabela, const String chave, const LinkedList_str valor) {  // Adiciona o par chave-valor a tabela
    if (tabela == NULL)
        return false;
    int posicao = dispersal(tabela->capacity, chave);
    No_hash_sls* p = search_list(tabela->vet[posicao], chave);
    if (p != NULL) {   // Verificando se a chave já existe
        linked_list_str_copy(&p->value, &valor);   // supondo que essa atribuição sempre funcionará
        return true;
    }
    if ((float) tabela->size / tabela->capacity > LOAD_FACTOR_SLS) {   // Aumentando o tamanho da tabela se necessário
        if (!increase_hash_table(tabela))
            return false;
    }
    
    posicao = dispersal(tabela->capacity, chave);
    // Adicionando a chave e valor caso não exista
    if (!insert_begin_list_key_value(&tabela->vet[posicao], chave, valor))
        return false;
    tabela->size++;
    return true;
    
}

bool hash_table_sls_put_key_value_cstr_cvet_cstr(HashTable_sls* tabela, const char* chave, const char** valor, int n) {  // Adiciona o par chave-valor a tabela
    if (tabela == NULL)
        return false;
    int posicao = dispersal_cstr(tabela->capacity, chave);
    No_hash_sls* p = search_list_cstr(tabela->vet[posicao], chave);
    if (p != NULL) {   // Verificando se a chave já existe
        LinkedList_str lista = linked_list_str_from_cvet_cstr(valor, n);
        if (linked_list_str_is_empty(&lista))
            return false;
        
        linked_list_str_free(&p->value);   // Removendo a memória antiga
        p->value = lista;   // atribuindo o novo valor
        return true;
    }
    if ((float) tabela->size / tabela->capacity > LOAD_FACTOR_SLS) {   // Aumentando o tamanho da tabela se necessário
        if (!increase_hash_table(tabela))
            return false;
    }
    
    posicao = dispersal_cstr(tabela->capacity, chave);
    // Adicionando a chave e valor caso não exista
    if (!insert_begin_list_key_value_cstr_cvet_cstr(&tabela->vet[posicao], chave, valor, n))
        return false;
    tabela->size++;
    return true;
    
}


bool hash_table_sls_contains_key(const HashTable_sls* tabela, const String chave) {  // Verifica se a chave exister na tabela
    return hash_table_sls_contains_key_cstr(tabela, string_cstr(&chave));
}

bool hash_table_sls_contains_key_cstr(const HashTable_sls* tabela, const char* chave) {  // Verifica se a chave existe na tabela
    if (hash_table_sls_is_empty(tabela))
        return false;
    int posicao = dispersal_cstr(tabela->capacity, chave);
    No_hash_sls* p = search_list_cstr(tabela->vet[posicao], chave);
    return p != NULL;
}

bool hash_table_sls_get(const HashTable_sls* tabela, const String chave, LinkedList_str* retorno) {  // Retorna, no terceiro parâmetro, o valor da respectiva chave passado no segundo parâmetro
    return hash_table_sls_get_cstr(tabela, string_cstr(&chave), retorno);
}

bool hash_table_sls_get_cstr(const HashTable_sls* tabela, const char* chave, LinkedList_str* retorno) {  // Retorna, no terceiro parâmetro, o valor da respectiva chave passado no segundo parâmetro
    if (hash_table_sls_is_empty(tabela))
        return false;
    int posicao = dispersal_cstr(tabela->capacity, chave);
    No_hash_sls* p = search_list_cstr(tabela->vet[posicao], chave);
    if (p == NULL)
        return false;
    linked_list_str_copy(retorno, &p->value);
    return true;
}

bool hash_table_sls_remove(HashTable_sls* tabela, const String chave, const String valor) {  // Remove um único valor da respectiva chave, se ambos existirem
    return hash_table_sls_remove_cstr_cstr(tabela, string_cstr(&chave), string_cstr(&valor));
}

bool hash_table_sls_remove_cstr_cstr(HashTable_sls* tabela, const char* chave, const char* valor) {  // Remove um único valor da respectiva chave, se ambos existirem
    if (hash_table_sls_is_empty(tabela))
        return false;
    
    int posicao = dispersal_cstr(tabela->capacity, chave);
    if (remove_list_cstr_cstr(&tabela->vet[posicao], chave, valor, &tabela->size)) {
        return true;
    }
    return false;
}

bool hash_table_sls_remove_key_value(HashTable_sls* tabela, const String chave)  {  // Remove o par chave-valor da tabela
    return hash_table_sls_remove_key_value_cstr(tabela, string_cstr(&chave));
}

bool hash_table_sls_remove_key_value_cstr(HashTable_sls* tabela, const char* chave)  {  // Remove o par chave-valor da tabela
    if (hash_table_sls_is_empty(tabela))
        return false;
    
    int posicao = dispersal_cstr(tabela->capacity, chave);
    if (remove_list_key_value_cstr(&tabela->vet[posicao], chave)) {
        tabela->size--;
        return true;
    }
    return false;
}

void hash_table_sls_free(HashTable_sls* tabela) {   // Libera a memória da tabela. 
    if (tabela != NULL && tabela->vet != NULL) {
        for (int i = 0; i < tabela->capacity; i++)
            free_list(&tabela->vet[i]);
        free(tabela->vet);
        tabela->vet = NULL;
        tabela->capacity = tabela->size = 0;
    }
}

String* hash_table_sls_get_keys(const HashTable_sls* tabela) {  // Retorna, em um vetor comum da linguagem C de tamanho sendo hash_table_sls_size(), todas as chaves da tabela.
    if (hash_table_sls_is_empty(tabela))
        return NULL;
    String* vetor = (String*) calloc(tabela->size, sizeof(String));
    if (vetor == NULL)
        return NULL;
    
    int j = 0;
    for (int i = 0; i < tabela->capacity; i++) {
        No_hash_sls* p = tabela->vet[i];
        while (p != NULL) {
            string_copy(&vetor[j], &p->key);  // Assumindo que sempre dará certo
            p = p->Prox;
            j++;
        }
    }
    return vetor;
}

KeyValue_sls* hash_table_sls_get_keys_values(const HashTable_sls* tabela) {  // Retorna, em um vetor comum da linguagem C de tamanho sendo hash_table_sls_size(), todos os pares chave-valor da tabela
    if (hash_table_sls_is_empty(tabela))
        return NULL;
    KeyValue_sls* vetor = (KeyValue_sls*) calloc(tabela->size, sizeof(KeyValue_sls));   
    if (vetor == NULL)
        return NULL;
    
    int j = 0;
    for (int i = 0; i < tabela->capacity; i++) {
        No_hash_sls* p = tabela->vet[i];
        while (p != NULL) {
            string_copy(&vetor[j].key, &p->key);  // Assumindo que sempre dará certo
            linked_list_str_copy(&vetor[j].value, &p->value);
            p = p->Prox;
            j++;
        }
    }
    return vetor;
}

String hash_table_sls_to_string(const HashTable_sls* tabela) {  // Retorna uma representação da tabela como String
    if (hash_table_sls_is_empty(tabela))
        return string_new_with_cstr("EMPTY");
    String cadeia = string_new_with_size(8 * tabela->size);   // Um tamanho razoável para uma possível realocação
    
    if (string_is_valid(&cadeia)) {
        KeyValue_sls* pares = hash_table_sls_get_keys_values(tabela);
        if (pares == NULL) {
            string_free(&cadeia);
            return string_new_with_cstr("EMPTY");
        }
        QuickSort(pares, 0, tabela->size - 1);  // Ordenando os pares chave-valor
        
        String aux_valor = string_new_empty();
        for (int i = 0; i < tabela->size; i++) {
            string_concat(&cadeia, &pares[i].key);   // assumo que vai sempre funciona
            string_concat_cstr(&cadeia, ": ");
            
            string_free(&aux_valor);  
            aux_valor = linked_list_str_to_string(&pares[i].value);   // assumo que vai sempre funcionar
            string_concat(&cadeia, &aux_valor);   // assumo que vai sempre funciona
            if (i < tabela->size - 1)
                string_append(&cadeia, '\n');
        }
        string_free(&aux_valor);      
    
        for (int i = 0; i < tabela->size; i++) {  // liberando a memória do vetor de chave-valor
            string_free(&pares[i].key);
            linked_list_str_free(&pares[i].value);
        }
        free(pares);
    }
    else
        cadeia = string_new_with_cstr("EMPTY");
    return cadeia;
}


void hash_table_sls_print(const HashTable_sls* tabela) {  // Imprime a tabela usando a função hash
    String cadeia = hash_table_sls_to_string(tabela);
    string_print(&cadeia);
    string_free(&cadeia);
}

void hash_table_sls_println(const HashTable_sls* tabela) {
    hash_table_sls_print(tabela);
    printf("\n");
}







/* Funções de lista encadeada usando apenas apontadores de No_hash_sls */
static LinkedList_str linked_list_str_from_cvet_cstr(const char** vet, int n) {  // Retorna uma LinkedList_str a partir de um vetor de apontadores de caracteres
    LinkedList_str list = linked_list_str_new();
    if (vet == NULL || n < 0)
        return list;
    for (int i = 0; i < n; i++) {
        if (!linked_list_str_insert_end_cstr(&list, vet[i])) {
            linked_list_str_free(&list);
            break;
        }
    }
    return list;

}

static bool insert_begin_list(No_hash_sls** L, const String K, const String cadeia) {  // Adiciona na chave um único elemento no valor
    return insert_begin_list_cstr_cstr(L, string_cstr(&K), string_cstr(&cadeia));
}

static bool insert_begin_list_cstr_cstr(No_hash_sls** L, const char* K, const char* caracteres) {  // Adiciona na chave um único elemento no valor
    if (L == NULL)
        return false;
    String aux_key = string_new_with_cstr(K);
    if (!string_is_valid(&aux_key))
        return false;
    
    No_hash_sls * n = (No_hash_sls*)calloc(1, sizeof(No_hash_sls));
    if (n == NULL) {
        string_free(&aux_key);
        return false;
    }
    n->key = aux_key;
    n->value = linked_list_str_new();  
    if (!linked_list_str_insert_begin_cstr(&n->value, caracteres)) {
        string_free(&aux_key);
        linked_list_str_free(&n->value);
        free(n);
        return false;
    }
    n->Prox = *L;
    *L = n;
    return true;
}

static bool insert_begin_list_key_value(No_hash_sls ** L, const String K, const LinkedList_str V) {   // Insere no inicio da lista encadeada L o par chave-valor
	if (L == NULL)
	    return false;
	No_hash_sls * n = (No_hash_sls*)calloc(1, sizeof(No_hash_sls));
	if (n == NULL) {
		return false;
	}
	string_copy(&n->key, &K);  linked_list_str_copy(&n->value, &V);    // Estou supondo que essas cópias sempre funcionaram
	n->Prox = *L;
	*L = n;
	return true;
}

static bool insert_begin_list_key_value_cstr_cvet_cstr(No_hash_sls** L, const char* caracteres, const char** vet, int n) {  // Adiciona chave sendo String e valor sendo LinkedList_str adaptando os parâmetros passados
        if (L == NULL || caracteres == NULL || vet == NULL || n < 0)
                return false;
        LinkedList_str list = linked_list_str_from_cvet_cstr(vet, n);
        if (linked_list_str_is_empty(&list))
                return false;
        
        No_hash_sls * novo = (No_hash_sls*)calloc(1, sizeof(No_hash_sls));
	if (novo == NULL) {
	        linked_list_str_free(&list);
		return false;
	}
	string_copy_cstr(&novo->key, caracteres);    // Estou supondo que essa cópia sempre funcionará
	novo->value = list;  
	novo->Prox = *L;
	*L = novo;
	return true;
}

static No_hash_sls* search_list(No_hash_sls * L, String K) {     // Procura se a chave K está na lista L
	No_hash_sls* p = L;
	while (p != NULL) {
		if (string_compare(&p->key, &K) == 0)	
			return p;
		else
			p = p->Prox;
	}
	return NULL;
}

static No_hash_sls* search_list_cstr(No_hash_sls* L, const char* caracteres) {  // Busca um determinada chave na lista encadeada
        No_hash_sls* p = L;
	while (p != NULL) {
		if (string_compare_cstr(&p->key, caracteres) == 0)	
			return p;
		else
			p = p->Prox;
	}
	return NULL;
}

static bool remove_list(No_hash_sls** L, const String K, const String cadeia, int* size_hash) {  // Remove apenas um elemento da lista encadeada do valor de uma determinada chave
    return remove_list_cstr_cstr(L, string_cstr(&K), string_cstr(&cadeia), size_hash);
}

static bool remove_list_cstr_cstr(No_hash_sls** L, const char* K, const char* caracteres, int* size_hash) {  // Remove apenas um elemento da lista encadeada do valor de uma determinada chave
    if (L == NULL || *L == NULL)
        return false;
    No_hash_sls * p = *L;
    No_hash_sls * pAnt = NULL;
    while (p != NULL && string_compare_cstr(&p->key, K) != 0) {
	pAnt = p;
	p = p->Prox;
    } 
    if (p != NULL) {
	if (!linked_list_str_remove_cstr(&p->value, caracteres))
	    return false;
	if (linked_list_str_is_empty(&p->value)) {
	    if (pAnt != NULL)
	        pAnt->Prox = p->Prox;
	    else
	        *L = p->Prox;
	    linked_list_str_free(&p->value);
	    string_free(&p->key);
	    *size_hash = *size_hash - 1;
	    free(p);   
	}
	return true;
    }
    return false;
}

static bool remove_list_key_value(No_hash_sls ** L, const String K) {   // Remove o par chave-valor está na lista L.
	if (L == NULL || *L == NULL)
	    return false;
	No_hash_sls * p = *L;
	No_hash_sls * pAnt = NULL;
	while (p != NULL && string_compare(&p->key, &K) != 0) {
		pAnt = p;
		p = p->Prox;
	} 
	if (p != NULL) {
		if (pAnt != NULL)
			pAnt->Prox = p->Prox;
		else
			*L = p->Prox;
		string_free(&p->key);
		linked_list_str_free(&p->value);
		free(p);
		return true;
	}
	return false;
}

static bool remove_list_key_value_cstr(No_hash_sls ** L, const char* caracteres) {   // Remove o par chave-valor está na lista L.
	if (L == NULL || *L == NULL)
	    return false;
	No_hash_sls * p = *L;
	No_hash_sls * pAnt = NULL;
	while (p != NULL && string_compare_cstr(&p->key, caracteres) != 0) {
		pAnt = p;
		p = p->Prox;
	} 
	if (p != NULL) {
		if (pAnt != NULL)
			pAnt->Prox = p->Prox;
		else
			*L = p->Prox;
		string_free(&p->key);
		linked_list_str_free(&p->value);
		free(p);
		return true;
	}
	return false;
}

static void free_list(No_hash_sls ** L) {    // Libera a memória da lista encadeada
	if (L == NULL)
	    return;
	while (*L != NULL) {
		No_hash_sls * p = *L;
		*L = (*L)->Prox;
		string_free(&p->key);
		linked_list_str_free(&p->value);
		free(p);
	}
}
/* Funções de lista encadeada usando apenas apontadores de No_hash_sls */

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

static void Particionar(KeyValue_sls A[], int inicio, int fim, const String pivo, int* i, int* j) {
	*i = inicio; *j = fim;
	KeyValue_sls aux;
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

static void QuickSort(KeyValue_sls vet[], int inicio, int fim) {
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

