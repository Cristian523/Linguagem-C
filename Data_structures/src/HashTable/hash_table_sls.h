#ifndef HASH_TABLE_SLS_H
#define HASH_TABLE_SLS_H

#include <stdbool.h>
#include "c_string.h"
#include "linked_list_str.h"
#define HASH_TABLE_SLS_DEFAULT_CAPACITY 23
#define HASH_TABLE_SLS_MIN_CAPACITY 13
#define LOAD_FACTOR_SLS 0.75

// OBS: Essa sigla "sls" que deixei nas structs e nas funções é para significar que tem como chave String (por isso o "s") e valor como LinkedList_str (por isso o "ls") que, junado os dois, fica esse "sls", isto é, String para LinkedList_str.

typedef struct KeyValue_sls {
    String key;
    LinkedList_str value;
} KeyValue_sls;

typedef struct No_hash_sls {
    String key;
    LinkedList_str value;
    struct No_hash_sls* Prox;
} No_hash_sls;

typedef struct HashTable_sls {
    No_hash_sls** vet;
    int size;
    int capacity;
} HashTable_sls;

HashTable_sls hash_table_sls_new();
// @ Cria uma HashTable_sls com a capacidade HASH_TABLE_SLS_DEFAULT_CAPACITY.

HashTable_sls hash_table_sls_new_with_capacity(int);
// @ Cria uma HashTable_sls a partir de uma capacidade inicial. Se essa capacidade for menor ou igual a que 0, essa função vai assumir a capacidade HASH_TABLE_SLS_DEFAULT_CAPACITY

HashTable_sls hash_table_sls_new_with_size(int);
/* @ Cria uma HashTable_sls a partir de um número de elementos. A capacidade será calculada a partir desse parâmetro.
   OBS: Se esse parâmetro for menor ou igual a 12, essa função vai assumir capacidade sendo HASH_TABLE_SLS_MIN_CAPACITY.
*/

int hash_table_sls_value_size(const HashTable_sls*, const String);
// @ Retorna o número de elementos da lista encadeada de valores da chave passada no segundo parâmetro. Se a tabela for vazia ou não encontrar essa chave, será retornado -1. 

int hash_table_sls_value_size_cstr(const HashTable_sls*, const char*);
// @ Mesma ideia da função anterior, mas o segundo parâmetro é um vetor de caracteres

bool hash_table_sls_is_empty(const HashTable_sls*);
// @ Verifica se a tabela está vazia. Se o parâmetro for nulo ou o campo size for 0, será retornado true, caso o contrário, será retornado false.

int hash_table_sls_size(const HashTable_sls*);
// @ Retorna o número de elementos da tabela. Se o parâmetro for nulo, será retornado 0, caso o contrário, será retornado o campo size.

bool hash_table_sls_put(HashTable_sls*, const String, const String);
/* @ Adiciona 1 valor do terceiro parâmetro na LinkedList_str de valor da chave passada do segundo parâmetro. Se essa chave não existir na tabela, então será adicionada essa chave na tabela e adicionará esse único elemento na LinkedList_str de valor.
   OBS: Qualquer um dos problemas a seguir acarretará no retorno sendo false, isto é, na não inserção do valor:
   1) Se o primeiro parâmetro for nulo.
   2) Se a realocação da tabela falhar, seja por não conseguir alocar o novo array de No_hash_sls* ou na impossibilidade de trasferir todos os atuais elementos do array antigo para o atual
   3) Se a inserção do valor falhar após o passo 2)
*/

bool hash_table_sls_put_cstr_cstr(HashTable_sls*, const char*, const char*);
/* @ Mesma ideia da função anterior, mas os segundo e terceiro parâmetros serão transformados em String primeiro. Se essa transformação falhar, será retornado false.
*/

bool hash_table_sls_put_key_value(HashTable_sls*, const String, const LinkedList_str);
/* @ Adiciona o par chave-valor a tabela. Se a chave já existir, apenas o valor será alterado na chave já existente (será substituído).
   OBS: Qualquer um dos problemas a seguir acarretará no retorno sendo false, isto é, na não inserção do par chave-valor:
   1) Se o primeiro parâmetro for nulo.
   2) Se a realocação da tabela falhar, seja por não conseguir alocar o novo array de No_hash_sls* ou na impossibilidade de trasferir todos os atuais elementos do array antigo para o atual
   3) Se a inserção do par chave-valor falhar após o passo 2)
   
   OBS: Recomendo que a LinkedList_str esteja ordenada, para que, caso faça novas inserções com hash_table_sls_put() ou hash_table_put_cstr_cstr() com a mesma chave, será inserido, na LinkedList_str de valor, o valor de forma ordenada.
*/

bool hash_table_sls_put_key_value_cstr_cvet_cstr(HashTable_sls*, const char*, const char**, int);
// @ Mesma ideia da função anterior, mas o segundo parâmetro será transformado em uma String provisória e o terceiro parâmetro, de tamanho passado no quarto parâmetro, será transformado em uma LinkedList_str também provisória para inserir os dados na tabela. 

bool hash_table_sls_contains_key(const HashTable_sls*, const String);
// @ Retorna um valor lógico indicando se a chave do segundo parâmetro existe na tabela. Caso o primeiro parâmetro seja nulo ou a tabela seja vazia, será retornado false.

bool hash_table_sls_contains_key_cstr(const HashTable_sls*, const char*);
// @ Mesma ideia da função anterior, porém o segundo parâmetro como vetor de caracteres.

bool hash_table_sls_get(const HashTable_sls*, const String, LinkedList_str*);
// @ Retorna, no terceiro parâmetro da função, o valor da chave passado no segundo parâmetro como cópia. Se o primeiro parâmetro for nulo, a tabela for vazia ou não encontrar a chave passada no segundo parâmetro da função, será retornado false e o terceiro parâmetro não será alterado.

bool hash_table_sls_get_cstr(const HashTable_sls*, const char*, LinkedList_str*);
// @ Mesma ideia da função anterior, porém o segundo parâmetro como vetor de caracteres.

bool hash_table_sls_remove(HashTable_sls*, const String, const String);
/* @ Remove  *um único valor*  passado no terceiro parâmetro da LinkedList_str de valores da chave do segundo parâmetro, se ambos existirem. Se existir apenas 1 elemento da LinkedList_str de valores e justamente esse elemento for o elemento a ser removido, então esta função removerá a sua respectiva chave junto.
   Se o primeiro parâmetro for nulo, a tabela for vazia, não encontrar a chave ou não encontrar o valor na LinkedList_str de valores da respectiva chave, então será retornado false.
*/

bool hash_table_sls_remove_cstr_cstr(HashTable_sls*, const char*, const char*);
// @ Mesma ideia da função anterior, mas com os segundo e terceiro parâmetros sendo vetores de caractere.

bool hash_table_sls_remove_key_value(HashTable_sls*, const String);
// @ Remove o par chave-valor da tabela usando a chave passada no segundo parâmetro. Se o primeiro parâmetro for nulo, a tabela for vazia ou não encontrar a chave passada no segundo parâmetro da função, será retornado false.

bool hash_table_sls_remove_key_value_cstr(HashTable_sls*, const char*);
// @ Mesma ideia da função anterior, mas com o segundo parâmetro sendo um vetor de caracteres

void hash_table_sls_free(HashTable_sls*);
// @ Libera a memória da tabela. Se o parâmetro for nulo ou a tabela for vazia, será feito nada.

String* hash_table_sls_get_keys(const HashTable_sls*);
/* @ Retorna, em um vetor comum da linguagem C de tamanho sendo hash_table_sls_size(), todas as chaves de tabela. Se o primeiro parâmetro for nulo ou a tabela for vazia, será retornado um vetor nulo.
   OBS: esse vetor será construído usando alocação dinâmica, então será necessário usar o string_free() manualmente em cada posição desse vetor e posteriormente usar free() no vetor.
*/

KeyValue_sls* hash_table_sls_get_keys_values(const HashTable_sls*);
/* @ Retorna, em um vetor comum da linguagem C de tamanho sendo hash_table_sls_size(), todos os pares chave-valor da tabela. Se o primeiro parâmetro for nulo ou a tabela for vazia, será retornado um vetor nulo.
   OBS: esse vetor será construído usando alocação dinâmica, então será necessário usar o string_free() e o linkedList_str_free() nos campos key e value, respectivamente, em cada posição de memória do vetor, além de usar o free() manualmente no vetor posteriormente.
*/

String hash_table_sls_to_string(const HashTable_sls*);
// @ Retorna uma representação da tabela em String. Se ocorrer problema de memória para alocar o primeiro espaço da String ou o parâmetro for nulo ou para obter todos os pares chave-valor com a função hash_table_sls_get_keys_values(), será retornado uma representação de que a tabela é vazia, isto é, será retornado "EMPTY".

void hash_table_sls_print(const HashTable_sls*);
// @ Usa o retorno da função anterior hash_table_sls_to_string() para imprimir os elementos.

void hash_table_sls_println(const HashTable_sls*);
// @ Imprime os elementos da tabela usando a função anterior acrescido de um caractere '\n' ao final.


#endif
