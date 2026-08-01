#ifndef HASH_TABLE_EW_H
#define HASH_TABLE_EW_H


#include <stdbool.h>
#include "c_string.h"
#include "edge.h"
#define HASH_TABLE_EW_DEFAULT_CAPACITY 31
#define HASH_TABLE_EW_MIN_CAPACITY 23
#define LOAD_FACTOR_EW 0.75

// OBS: O sufixo "ew" aqui usado se refere a chave sendo um Edge e o valor sendo o peso da aresta.


typedef struct KeyValue_ew {
    Edge key;
    float value;
} KeyValue_ew;

typedef struct No_hash_ew {
    Edge key;
    float value;
    struct No_hash_ew* Prox;
} No_hash_ew;

typedef struct HashTable_ew {
    No_hash_ew** vet;
    int size;
    int capacity;
} HashTable_ew;



HashTable_ew hash_table_ew_new();
// @ Cria uma HashTable_ew com a capacidade HASH_TABLE_EW_DEFAULT_CAPACITY.

HashTable_ew hash_table_ew_new_with_capacity(int);
// @ Cria uma HashTable_ew a partir de uma capacidade inicial. Se essa capacidade for menor ou igual a que 0, essa função vai assumir a capacidade HASH_TABLE_EW_DEFAULT_CAPACITY

HashTable_ew hash_table_ew_new_with_size(int);
/* @ Cria uma HashTable_ew a partir de um número de elementos. A capacidade será calculada a partir desse parâmetro.
   OBS: Se esse parâmetro for menor ou igual a 12, essa função vai assumir capacidade sendo HASH_TABLE_EW_MIN_CAPACITY.
*/

bool hash_table_ew_is_empty(const HashTable_ew*);
// @ Verifica se a tabela está vazia. Se o parâmetro for nulo ou o campo size for 0, será retornado true, caso o contrário, será retornado false.

int hash_table_ew_size(const HashTable_ew*);
// @ Retorna o número de elementos da tabela. Se o parâmetro for nulo, será retornado 0, caso o contrário, será retornado o campo size.

bool hash_table_ew_put(HashTable_ew*, const Edge, float);
/* @ Adiciona o par chave-valor a tabela. Se a chave já existir, apenas o valor será alterado na chave já existente.
   OBS: Qualquer um dos problemas a seguir acarretará no retorno sendo false, isto é, na não inserção do par chave-valor:
   1) Se o primeiro parâmetro for nulo.
   2) Se a realocação da tabela falhar, seja por não conseguir alocar o novo array de No_hash* ou na impossibilidade de trasferir todos os atuais elementos do array antigo para o atual
   3) Se a inserção do par chave-valor falhar após o passo 2)
*/

bool hash_table_ew_contains_key(const HashTable_ew*, const Edge);
// @ Retorna um valor lógico indicando se a chave do segundo parâmetro existe na tabela. Caso o primeiro parâmetro seja nulo ou a tabela seja vazia, será retornado false.

bool hash_table_ew_contains_key_cstr_cstr(const HashTable_ew*, const char*, const char*);
// @ Mesma ideia da função anterior, mas os dois últimos parâmetros representam o nome de uma aresta, se existente.

bool hash_table_ew_contains_key_str_str(const HashTable_ew*, const String, const String);
// @ Mesma ideia da função anterior, mas os dois últimos parâmetros representam o nome de uma aresta, se existente.

bool hash_table_ew_get(const HashTable_ew*, const Edge, float*);
// @ Retorna, no terceiro parâmetro da função, o valor da chave passado no segundo parâmetro. Se o primeiro parâmetro for nulo, a tabela for vazia ou não encontrar a chave passada no segundo parâmetro da função, será retornado false e o terceiro parâmetro não será alterado.

bool hash_table_ew_get_str_str(const HashTable_ew*, const String, const String, float*);
// @ Mesma ideia da função anterior, mas com os parâmetros do meio representando uma aresta.
// OBS: Só será verificado a aresta como ida, isto é, se a aresta uv existe no grafo com u sendo o segundo parâmetro e v o terceiro parâmetro. Então certifique-se de que u <= v para uma saída correta.

bool hash_table_ew_get_cstr_cstr(const HashTable_ew*, const char*, const char*, float*);
// @ Mesma ideia da função anterior, mas com os parâmetros do meio representando uma aresta.
// OBS: Só será verificado a aresta como ida, isto é, se a aresta uv existe no grafo com u sendo o segundo parâmetro e v o terceiro parâmetro. Então certifique-se de que u <= v para uma saída correta.


bool hash_table_ew_remove(HashTable_ew*, const Edge);
// @ Remove o par chave-valor da tabela usando a chave passada no segundo parâmetro. Se o primeiro parâmetro for nulo, a tabela for vazia ou não encontrar a chave passada no segundo parâmetro da função, será retornado false.


void hash_table_ew_free(HashTable_ew*);
// @ Libera a memória da tabela. Se o parâmetro for nulo ou a tabela for vazia, será feito nada.

Edge* hash_table_ew_get_keys(const HashTable_ew*);
/* @ Retorna, em um vetor comum da linguagem C de tamanho sendo hash_table_ew_size(), todas as chaves de tabela. Se o primeiro parâmetro for nulo ou a tabela for vazia, será retornado um vetor nulo.
   OBS: esse vetor será construído usando alocação dinâmica, então será necessário liberar a memória de cada string usando o edge_free() e depois usar o free() manualmente no vetor.
*/

KeyValue_ew* hash_table_ew_get_keys_values(const HashTable_ew*);
/* @ Retorna, em um vetor comum da linguagem C de tamanho sendo hash_table_ew_size(), todos os pares chave-valor da tabela. Se o primeiro parâmetro for nulo ou a tabela for vazia, será retornado um vetor nulo.
   OBS: esse vetor será construído usando alocação dinâmica, então será necessário usar o edge_free() em cada chave e depois usar free() manualmente no vetor.
*/

String hash_table_ew_to_string(const HashTable_ew*);
// @ Retorna uma representação da tabela em String. Se ocorrer problema de memória para alocar o primeiro espaço da String ou o parâmetro for nulo ou para obter todos os pares chave-valor com a função hash_table_ew_get_keys_values(), será retornado uma representação de que a tabela é vazia, isto é, será retornado "{}".

void hash_table_ew_print(const HashTable_ew*);
// @ Usa o retorno da função anterior hash_table_ew_to_string() para imprimir os elementos.

void hash_table_ew_println(const HashTable_ew*);
// @ Imprime os elementos da tabela usando a função anterior acrescido de um caractere '\n' ao final.



#endif
