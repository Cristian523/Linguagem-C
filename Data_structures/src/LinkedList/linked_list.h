#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include "c_string.h"

/* MUDE O TIPO_LINKED_LIST E A PRECISAO AQUI. NO CASO DO ÚLTIMO, A PRECISAO SERÁ USADA EM FLOAT E DOUBLE APENAS */ 
#define PRECISION_LINKED_LIST 2    // Mude a precisão de float e double aqui

//!!!!!!!!!!!!!!! Mude aqui qual tipo_linked_list primitivo quer escolher !!!!!!!!!!!!!!!!!

// #define TIPO_LINKED_LIST_INT
// #define TIPO_LINKED_LIST_LONG
// #define TIPO_LINKED_LIST_LONG_LONG
// #define TIPO_LINKED_LIST_FLOAT
// #define TIPO_LINKED_LIST_DOUBLE
#define TIPO_LINKED_LIST_DOUBLE_G
// #define TIPO_LINKED_LIST_CHAR


#if defined(TIPO_LINKED_LIST_INT)

    typedef int tipo_linked_list;
    #define TO_STRING_LINKED_LIST(x) string_from_int((x))

#elif defined(TIPO_LINKED_LIST_LONG)

    typedef long tipo_linked_list;
    #define TO_STRING_LINKED_LIST(x) string_from_long((x))

#elif defined(TIPO_LINKED_LIST_LONG_LONG)

    typedef long long tipo_linked_list;
    #define TO_STRING_LINKED_LIST(x) string_from_long_long((x))

#elif defined(TIPO_LINKED_LIST_FLOAT)

    typedef float tipo_linked_list;
    #define TO_STRING_LINKED_LIST(x) string_from_float((x), PRECISION_LINKED_LIST)

#elif defined(TIPO_LINKED_LIST_DOUBLE)

    typedef double tipo_linked_list;
    #define TO_STRING_LINKED_LIST(x) string_from_double((x), PRECISION_LINKED_LIST)

#elif defined(TIPO_LINKED_LIST_DOUBLE_G)

    typedef double tipo_linked_list;
    #define TO_STRING_LINKED_LIST(x) string_from_double_g((x))

#elif defined(TIPO_LINKED_LIST_CHAR)

    typedef char tipo_linked_list;
    #define TO_STRING_LINKED_LIST(x) string_from_char((x))

#else
      #error "Defina UM tipo_linked_list válido em linked_list.h"

#endif

/* MUDE O TIPO_LINKED_LIST E A PRECISAO AQUI. NO CASO DO ÚLTIMO, A PRECISAO SERÁ USADA EM FLOAT E DOUBLE APENAS */ 

typedef struct No {
    tipo_linked_list E;
    struct No * Prox;
} No;

typedef struct LinkedList {
    No* inicio;
    No* atual;   // iterador interno
    No* fim;
    int length;
} LinkedList;



LinkedList linked_list_new();   
// @ Inicializador de LinkedList. Basicamente deixa inicio, fim e atual nulos e length sendo 0

int linked_list_length(const LinkedList*); 
// @ Retorna o número de elementos 

int linked_list_size(const LinkedList*);
// @ Mesma ideia da função anterior

bool linked_list_is_empty(const LinkedList*); 
// @ Verifica se é uma LinkedList vazia. Se o parâmetro for nulo, o campo length for 0 ou o campo inicio for nulo, será retornado true.

bool linked_list_reset(LinkedList*);
/* @ Reseta o iterador interamente (o ponteiro atual) para apontar para o primeiro elemento da lista. Caso o parâmetro seja nulo ou a lista esteja vazia, retornará false.
  OBS: Sempre chame esta função antes de navegar pela lista!!!   
*/

bool linked_list_has_next(const LinkedList*);
/* @ Retorna true se o campo representado pelo ponteiro atual tiver o ponteiro Prox diferente de nulo. Se isso não ocorrer, o parâmetro for nulo, a lista estiver vazia ou atual for nulo, será retornado false.
   OBS: Chame a função linked_list_reset() se quiser que o campo atual seja diferente de nulo, caso a lista tenha elementos.
*/

bool linked_list_next(LinkedList*);
/* @ Retorna true se o campo atual conseguir avançar para o próximo elemento da lista, isto é, quando Prox for diferente de nulo. Se isso não for possível, o parâmetro for nulo ou a lista for vazia, será retornado false.
   OBS: Chame a função linked_list_reset() se quiser que o campo atual seja diferente de nulo, caso a lista tenha elementos.
*/

bool linked_list_current(const LinkedList*, tipo_linked_list*);
/* @ Retorna no segundo parâmetro o elemento no ponteiro atual, isto é, no campo E de atual. Se o primeiro parâmetro for nulo, a lista for vazia ou o ponteiro atual for nulo, será retornado false e o segundo parâmetro não será alterado.
   OBS: Chame a função linked_list_reset() se quiser que o campo atual seja diferente de nulo, caso a lista tenha elementos.
*/

bool linked_list_insert_begin(LinkedList*, tipo_linked_list);
// @ Insere o elemento do segundo parâmetro no início da lista. Se não conseguir por problema de memória ou parâmetro for inválido, será retornado false

bool linked_list_insert_end(LinkedList*, tipo_linked_list);
// @ Insere o elemento do segundo parâmetro no fim da lista. Se não conseguir por problema de memória ou parâmetro for inválido, será retornado false

bool linked_list_insert_ordered(LinkedList*, tipo_linked_list);
/* @ Insere o elemento do segundo parâmetro na lista de forma ordenada. Se não conseguir por problema de memória ou parâmetro inválido, será retornado false
   OBS: Se a lista não estiver ordenada, então essa inserção não funcionará direito.
*/

bool linked_list_first(const LinkedList*, tipo_linked_list*);
// @ Retorna no segundo parâmetro o primeiro elemento da lista. Se o primeiro parâmetro for nulo ou a lista for vazia, será retornado false e o segundo parâmetro não será alterado.

bool linked_list_last(const LinkedList*, tipo_linked_list*);
// @ Retorna no segundo parâmetro o ultimo elemento da lista. Se o primeiro parâmetro for nulo ou a lista for vazia, será retornado false e o segundo parâmetro não será alterado.

bool linked_list_search(const LinkedList*, tipo_linked_list);
// @ Procura a primeira ocorrência do elemento do segundo parâmetro na lista e retorna true se conseguir encontrar. Se o primeiro parâmetro for nulo, a lista for vazia ou não encontrar o elemento, será retornado false.

int linked_list_count(const LinkedList*, tipo_linked_list);
// @ Retorna a quantidade de elementos do segundo parâmetro encontrado na lista. Se o primeiro parâmetro for nulo ou a lista for vazia, será retornado 0;

bool linked_list_pop_first(LinkedList*);
/* @ Remove o primeiro elemento da lista. Se o parâmetro for nulo ou a lista for vazia, será retornado false
  OBS: Após remover o elemento na qual atual apontava (se for o caso), atual passará apontar para o próximo elemento. Caso atual apontava para o último No, então atual passará a ser nulo após a remoção.
*/

bool linked_list_pop_last(LinkedList*);
/* @ Remove o ultimo elemento da lista. Se o parâmetro for nulo ou a lista for vazia, será retornado false
   OBS1: Esta função navegará até o penúltimo elemento para conseguir remover sem problemas, logo essa função terá que percorrer todos os elementos. Sendo assim, não funciona em tempo constante
   OBS2: Após remover o elemento na qual atual apontava (se for o caso), atual passará apontar para o próximo elemento. Caso atual apontava para o último No, então atual passará a ser nulo após a remoção.
*/

bool linked_list_pop_current(LinkedList*);
/* @ Remove o elemento que está localizado na posicao do ponteiro atual. Se o parâmetro for nulo, a lista for vazia ou o ponteiro atual for nulo, será retornado false.
   OBS1: Chame a função linked_list_reset() se quiser que o campo atual seja diferente de nulo, caso a lista tenha elementos.
   OBS2: Após remover o elemento na qual atual apontava, atual passará apontar para o próximo elemento. Caso atual apontava para o último No, então atual passará a ser nulo após a remoção.
   OBS3: No pior caso (com o ponteiro atual apontando para o ultimo elemento da lista), essa função navegará até o penúltimo elemento para ajustar corretamente o ponteiro fim. Sendo assim, não funciona em tempo constante.
*/

bool linked_list_remove(LinkedList*, tipo_linked_list);
/* @ Remove a primeira ocorrencia do elemento do segundo parâmetro da lista. Se o primeiro parâmetro for nulo, a lista for vazia ou não conseguir encontrar o elemento, será retornado false.
   OBS: Se o ponteiro atual for exatamento o elemento a ser removido, este apontará para o próximo elemento. Se atual for o último elemento e for o elemento a ser removido, este apontará para nulo.
*/

bool linked_list_copy(LinkedList*, const LinkedList*);
/* @ Copia todos os elementos da lista do segundo parâmetro para o primeiro. Se um dos parâmetros for nulo ou tiver problemas com alocação de memória, será retornado false e o primeiro parâmetro não será alterado.
   OBS1: Se o primeiro parâmetro já tiver elementos e a cópia for bem sucedida, então o conteúdo antigo será removido automaticamente
   OBS2: Por padrão, a lista nova obtida pela cópia terá o ponteiro atual sendo nulo, então cabe ao programaddor chamar a função linked_list_reset() para ajustar isso caso queira navegar pela lista
*/

void linked_list_free(LinkedList*);    
// @ Remove todos os elementos de LinkedList. Se a lista já for vazia ou o parâmetro for nulo, será feito nada

String linked_list_to_string(const LinkedList* list); 
/* @ Retorna uma representação de String de uma LinkedList. 
   OBS: Se falhar por parâmetro nulo ou se a lista for vazia, será retornado uma String como representação de que a lista é nula, isto é, será retornado a String "NULL"
*/

void linked_list_print(const LinkedList* list);
// @ Imprime na tela uma LinkedList usando como base a String obtida com a função acima linked_list_to_string() e esta mesma String é impressa com o string_print().

void linked_list_println(const LinkedList* list);
// @ Usa a função acima linked_list_print() e acrescenta um caractere '\n' na impressão.

#endif
