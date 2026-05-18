#ifndef HASH_TABLE_SN_H
#define HASH_TABLE_SN_H

#include <stdbool.h>
#include "c_string.h"
#define HASH_TABLE_SN_DEFAULT_CAPACITY 23
#define HASH_TABLE_SN_MIN_CAPACITY 13
#define LOAD_FACTOR_SN 0.75

// OBS: O sufixo "sn" usado refere-se que a chave é String (por isso esse "s") e o valor é um número (por isso esse "n"), por isso, ao juntar os dois, "sn". Como a linguagem C trata char como inteiro, ele também faz parte da lista de número aqui presente.

/* MUDE O TIPO_VALUE_NUMBER E A PRECISAO AQUI. NO CASO DO ÚLTIMO, A PRECISAO SERÁ USADA EM FLOAT E DOUBLE APENAS */ 
#define PRECISION_VALUE_NUMBER 2    // Mude a precisão de float e double aqui

#define TIPO_VALUE_NUMBER_INT
// #define TIPO_VALUE_NUMBER_LONG
// #define TIPO_VALUE_NUMBER_LONG_LONG
// #define TIPO_VALUE_NUMBER_FLOAT
// #define TIPO_VALUE_NUMBER_DOUBLE
// #define TIPO_VALUE_NUMBER_DOUBLE_G
// #define TIPO_VALUE_NUMBER_CHAR

#if defined(TIPO_VALUE_NUMBER_INT)

    typedef int tipo_value_number;
    #define TO_STRING_VALUE_NUMBER(x) string_from_int((x))

#elif defined(TIPO_VALUE_NUMBER_LONG)

    typedef long tipo_value_number;
    #define TO_STRING_VALUE_NUMBER(x) string_from_long((x))

#elif defined(TIPO_VALUE_NUMBER_LONG_LONG)

    typedef long long tipo_value_number;
    #define TO_STRING_VALUE_NUMBER(x) string_from_long_long((x))

#elif defined(TIPO_VALUE_NUMBER_FLOAT)

    typedef float tipo_value_number;
    #define TO_STRING_VALUE_NUMBER(x) string_from_float((x), PRECISION_VALUE_NUMBER)

#elif defined(TIPO_VALUE_NUMBER_DOUBLE)

    typedef double tipo_value_number;
    #define TO_STRING_VALUE_NUMBER(x) string_from_double((x), PRECISION_VALUE_NUMBER)

#elif defined(TIPO_VALUE_NUMBER_DOUBLE_G)

    typedef double tipo_value_number;
    #define TO_STRING_VALUE_NUMBER(x) string_from_double_g((x))

#elif defined(TIPO_VALUE_NUMBER_CHAR)

    typedef char tipo_value_number;
    #define TO_STRING_VALUE_NUMBER(x) string_from_char((x))

#else
      #error "Defina UM tipo_value_number válido em hast_table_sn.h"
#endif
/* MUDE O TIPO_VALUE_NUMBER E A PRECISAO AQUI. NO CASO DO ÚLTIMO, A PRECISAO SERÁ USADA EM FLOAT E DOUBLE APENAS */ 


typedef struct KeyValue_sn {
    String key;
    tipo_value_number value;
} KeyValue_sn;

typedef struct No_hash_sn {
    String key;
    tipo_value_number value;
    struct No_hash_sn* Prox;
} No_hash_sn;

typedef struct HashTable_sn {
    No_hash_sn** vet;
    int size;
    int capacity;
} HashTable_sn;


HashTable_sn hash_table_sn_new();
// @ Cria uma HashTable_sn com a capacidade HASH_TABLE_SN_DEFAULT_CAPACITY.

HashTable_sn hash_table_sn_new_with_capacity(int);
// @ Cria uma HashTable_sn a partir de uma capacidade inicial. Se essa capacidade for menor ou igual a que 0, essa função vai assumir a capacidade HASH_TABLE_SN_DEFAULT_CAPACITY

HashTable_sn hash_table_sn_new_with_size(int);
/* @ Cria uma HashTable_sn a partir de um número de elementos. A capacidade será calculada a partir desse parâmetro.
   OBS: Se esse parâmetro for menor ou igual a 12, essa função vai assumir capacidade sendo HASH_TABLE_SN_MIN_CAPACITY.
*/

bool hash_table_sn_is_empty(const HashTable_sn*);
// @ Verifica se a tabela está vazia. Se o parâmetro for nulo ou o campo size for 0, será retornado true, caso o contrário, será retornado false.

int hash_table_sn_size(const HashTable_sn*);
// @ Retorna o número de elementos da tabela. Se o parâmetro for nulo, será retornado 0, caso o contrário, será retornado o campo size.

bool hash_table_sn_put(HashTable_sn*, const String, tipo_value_number);
/* @ Adiciona o par chave-valor a tabela. Se a chave já existir, apenas o valor será alterado na chave já existente.
   OBS: Qualquer um dos problemas a seguir acarretará no retorno sendo false, isto é, na não inserção do par chave-valor:
   1) Se o primeiro parâmetro for nulo.
   2) Se a realocação da tabela falhar, seja por não conseguir alocar o novo array de No_hash* ou na impossibilidade de trasferir todos os atuais elementos do array antigo para o atual
   3) Se a inserção do par chave-valor falhar após o passo 2)
*/

bool hash_table_sn_put_cstr(HashTable_sn*, const char*, tipo_value_number);
// @ Mesma ideia da função anterior, mas com o segundo parâmetro sendo um vetor de caracteres

bool hash_table_sn_contains_key(const HashTable_sn* tabela, const String chave);
// @ Retorna um valor lógico indicando se a chave do segundo parâmetro existe na tabela. Caso o primeiro parâmetro seja nulo ou a tabela seja vazia, será retornado false.

bool hash_table_sn_contains_key_cstr(const HashTable_sn* tabela, const char*);
// @ Mesma ideia da função anterior, mas com o segundo parâmetro sendo um vetor de caracteres

bool hash_table_sn_get(const HashTable_sn*, const String, tipo_value_number*);
// @ Retorna, no terceiro parâmetro da função, o valor da chave passado no segundo parâmetro. Se o primeiro parâmetro for nulo, a tabela for vazia ou não encontrar a chave passada no segundo parâmetro da função, será retornado false e o terceiro parâmetro não será alterado.

bool hash_table_sn_get_cstr(const HashTable_sn*, const char*, tipo_value_number*);
// @ Mesma ideia da função anterior, mas com o segundo parâmetro sendo um vetor de caracteres

bool hash_table_sn_remove(HashTable_sn*, const String);
// @ Remove o par chave-valor da tabela usando a chave passada no segundo parâmetro. Se o primeiro parâmetro for nulo, a tabela for vazia ou não encontrar a chave passada no segundo parâmetro da função, será retornado false.

bool hash_table_sn_remove_cstr(HashTable_sn*, const char*);
// @ Mesma ideia da função anterior, mas com o segundo parâmetro sendo um vetor de caracteres

void hash_table_sn_free(HashTable_sn*);
// @ Libera a memória da tabela. Se o parâmetro for nulo ou a tabela for vazia, será feito nada.

String* hash_table_sn_get_keys(const HashTable_sn*);
/* @ Retorna, em um vetor comum da linguagem C de tamanho sendo hash_table_sn_size(), todas as chaves de tabela. Se o primeiro parâmetro for nulo ou a tabela for vazia, será retornado um vetor nulo.
   OBS: esse vetor será construído usando alocação dinâmica, então será necessário liberar a memória de cada string usando o string_free() e depois usar o free() manualmente no vetor.
*/

KeyValue_sn* hash_table_sn_get_keys_values(const HashTable_sn*);
/* @ Retorna, em um vetor comum da linguagem C de tamanho sendo hash_table_sn_size(), todos os pares chave-valor da tabela. Se o primeiro parâmetro for nulo ou a tabela for vazia, será retornado um vetor nulo.
   OBS: esse vetor será construído usando alocação dinâmica, então será necessário usar o string_free() em cada chave e depois usar free() manualmente no vetor.
*/

String hash_table_sn_to_string(const HashTable_sn*);
// @ Retorna uma representação da tabela em String. Se ocorrer problema de memória para alocar o primeiro espaço da String ou o parâmetro for nulo ou para obter todos os pares chave-valor com a função hash_table_sn_get_keys_values(), será retornado uma representação de que a tabela é vazia, isto é, será retornado "{}".

void hash_table_sn_print(const HashTable_sn*);
// @ Usa o retorno da função anterior hash_table_sn_to_string() para imprimir os elementos.

void hash_table_sn_println(const HashTable_sn*);
// @ Imprime os elementos da tabela usando a função anterior acrescido de um caractere '\n' ao final.





#endif
