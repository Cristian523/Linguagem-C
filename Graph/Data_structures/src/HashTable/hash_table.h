#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h>
#include "c_string.h"
#define HASH_TABLE_DEFAULT_CAPACITY 31
#define HASH_TABLE_MIN_CAPACITY 17
#define LOAD_FACTOR 0.75

/* MUDE O TIPO_KEY, TIPO_VALUE E A PRECISAO AQUI. NO CASO DO ÚLTIMO, A PRECISAO SERÁ USADA EM FLOAT E DOUBLE APENAS */ 
#define PRECISION_KEY 2    // Mude a precisão de float e double aqui
#define PRECISION_VALUE 2    // Mude a precisão de float e double aqui

//!!!!!!!!!!!!!!! Mude aqui qual tipo_key primitivo quer escolher !!!!!!!!!!!!!!!!!

// #define TIPO_KEY_INT
// #define TIPO_KEY_LONG
// #define TIPO_KEY_LONG_LONG
// #define TIPO_KEY_FLOAT
// #define TIPO_KEY_DOUBLE
#define TIPO_KEY_DOUBLE_G
// #define TIPO_KEY_CHAR

#if defined(TIPO_KEY_INT)

    typedef int tipo_key;
    #define TO_STRING_KEY(x) string_from_int((x))

#elif defined(TIPO_KEY_LONG)

    typedef long tipo_key;
    #define TO_STRING_KEY(x) string_from_long((x))

#elif defined(TIPO_KEY_LONG_LONG)

    typedef long long tipo_key;
    #define TO_STRING_KEY(x) string_from_long_long((x))

#elif defined(TIPO_KEY_FLOAT)

    typedef float tipo_key;
    #define TO_STRING_KEY(x) string_from_float((x), PRECISION_KEY)

#elif defined(TIPO_KEY_DOUBLE)

    typedef double tipo_key;
    #define TO_STRING_KEY(x) string_from_double((x), PRECISION_KEY)

#elif defined(TIPO_KEY_DOUBLE_G)

    typedef double tipo_key;
    #define TO_STRING_KEY(x) string_from_double_g((x))

#elif defined(TIPO_KEY_CHAR)

    typedef char tipo_key;
    #define TO_STRING_KEY(x) string_from_char((x))

#else
      #error "Defina UM tipo_key válido em hast_table.h"
#endif

//!!!!!!!!!!!!!!! Mude aqui qual tipo_value primitivo quer escolher !!!!!!!!!!!!!!!!!

// #define TIPO_VALUE_INT
// #define TIPO_VALUE_LONG
// #define TIPO_VALUE_LONG_LONG
// #define TIPO_VALUE_FLOAT
// #define TIPO_VALUE_DOUBLE
#define TIPO_VALUE_DOUBLE_G
// #define TIPO_VALUE_CHAR

#if defined(TIPO_VALUE_INT)

    typedef int tipo_value;
    #define TO_STRING_VALUE(x) string_from_int((x))

#elif defined(TIPO_VALUE_LONG)

    typedef long tipo_value;
    #define TO_STRING_VALUE(x) string_from_long((x))

#elif defined(TIPO_VALUE_LONG_LONG)

    typedef long long tipo_value;
    #define TO_STRING_VALUE(x) string_from_long_long((x))

#elif defined(TIPO_VALUE_FLOAT)

    typedef float tipo_value;
    #define TO_STRING_VALUE(x) string_from_float((x), PRECISION_VALUE)

#elif defined(TIPO_VALUE_DOUBLE)

    typedef double tipo_value;
    #define TO_STRING_VALUE(x) string_from_double((x), PRECISION_VALUE)

#elif defined(TIPO_VALUE_DOUBLE_G)

    typedef double tipo_value;
    #define TO_STRING_VALUE(x) string_from_double_g((x))

#elif defined(TIPO_VALUE_CHAR)

    typedef char tipo_value;
    #define TO_STRING_VALUE(x) string_from_char((x))

#else
      #error "Defina UM tipo_value válido em hast_table.h"
#endif
/* MUDE O TIPO_KEY, TIPO_VALUE E A PRECISAO AQUI. NO CASO DO ÚLTIMO, A PRECISAO SERÁ USADA EM FLOAT E DOUBLE APENAS */



typedef struct KeyValue {
    tipo_key key;
    tipo_value value;
} KeyValue;

typedef struct No_hash {
    tipo_key key;
    tipo_value value;
    struct No_hash* Prox;
} No_hash;

typedef struct HashTable {
    No_hash** vet;
    int size;
    int capacity;
} HashTable;

HashTable hash_table_new();
// @ Cria uma HashTable com a capacidade HASH_TABLE_DEFAULT_CAPACITY.

HashTable hash_table_new_with_capacity(int);
// @ Cria uma HashTable a partir de uma capacidade inicial. Se essa capacidade for menor ou igual a que 0, essa função vai assumir a capacidade HASH_TABLE_DEFAULT_CAPACITY

HashTable hash_table_new_with_size(int);
/* @ Cria uma HashTable a partir de um número de elementos. A capacidade será calculada a partir desse parâmetro.
   OBS: Se esse parâmetro for menor ou igual a 12, essa função vai assumir capacidade sendo HASH_TABLE_MIN_CAPACITY.
*/

bool hash_table_is_empty(const HashTable*);
// @ Verifica se a tabela está vazia. Se o parâmetro for nulo ou o campo size for 0, será retornado true, caso o contrário, será retornado false.

int hash_table_size(const HashTable*);
// @ Retorna o número de elementos da tabela. Se o parâmetro for nulo, será retornado 0, caso o contrário, será retornado o campo size.

bool hash_table_put(HashTable*, tipo_key, tipo_value);
/* @ Adiciona o par chave-valor a tabela. Se a chave já existir, apenas o valor será alterado na chave já existente.
   OBS: Qualquer um dos problemas a seguir acarretará no retorno sendo false, isto é, na não inserção do par chave-valor:
   1) Se o primeiro parâmetro for nulo.
   2) Se a realocação da tabela falhar, seja por não conseguir alocar o novo array de No_hash* ou na impossibilidade de trasferir todos os atuais elementos do array antigo para o atual
   3) Se a inserção do par chave-valor falhar após o passo 2)
*/

bool hash_table_contains_key(const HashTable* tabela, tipo_key chave);
// @ Retorna um valor lógico indicando se a chave do segundo parâmetro existe na tabela. Caso o primeiro parâmetro seja nulo ou a tabela seja vazia, será retornado false.

bool hash_table_get(const HashTable*, tipo_key, tipo_value*);
// @ Retorna, no terceiro parâmetro da função, o valor da chave passado no segundo parâmetro. Se o primeiro parâmetro for nulo, a tabela for vazia ou não encontrar a chave passada no segundo parâmetro da função, será retornado false e o terceiro parâmetro não será alterado.

bool hash_table_remove(HashTable*, tipo_key);
// @ Remove o par chave-valor da tabela usando a chave passada no segundo parâmetro. Se o primeiro parâmetro for nulo, a tabela for vazia ou não encontrar a chave passada no segundo parâmetro da função, será retornado false.

void hash_table_free(HashTable*);
// @ Libera a memória da tabela. Se o parâmetro for nulo ou a tabela for vazia, será feito nada.

tipo_key* hash_table_get_keys(const HashTable*);
/* @ Retorna, em um vetor comum da linguagem C de tamanho sendo hash_table_size(), todas as chaves de tabela. Se o primeiro parâmetro for nulo ou a tabela for vazia, será retornado um vetor nulo.
   OBS: esse vetor será construído usando alocação dinâmica, então será necessário usar o free() manualmente.
*/

KeyValue* hash_table_get_keys_values(const HashTable*);
/* @ Retorna, em um vetor comum da linguagem C de tamanho sendo hash_table_size(), todos os pares chave-valor da tabela. Se o primeiro parâmetro for nulo ou a tabela for vazia, será retornado um vetor nulo.
   OBS: esse vetor será construído usando alocação dinâmica, então será necessário usar o free() manualmente.
*/

String hash_table_to_string(const HashTable*);
// @ Retorna uma representação da tabela em String. Se ocorrer problema de memória para alocar o primeiro espaço da String ou o parâmetro for nulo ou para obter todos os pares chave-valor com a função hash_table_get_keys_values(), será retornado uma representação de que a tabela é vazia, isto é, será retornado "{}".

void hash_table_print(const HashTable*);
// @ Usa o retorno da função anterior hash_table_to_string() para imprimir os elementos.

void hash_table_println(const HashTable*);
// @ Imprime os elementos da tabela usando a função anterior acrescido de um caractere '\n' ao final.


#endif
