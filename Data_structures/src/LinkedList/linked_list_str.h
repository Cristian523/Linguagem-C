#ifndef LINKED_LIST_STR_H
#define LINKED_LIST_STR_H

#include <stdbool.h>
#include "c_string.h"

typedef struct No_str {
    String E;
    struct No_str * Prox;
} No_str;

typedef struct LinkedList_str {
    No_str* inicio;
    No_str* atual;   // iterador interno
    No_str* fim;
    int length;
} LinkedList_str;



LinkedList_str linked_list_str_new();   
// @ Inicializador de LinkedList_str. Basicamente deixa inicio, fim e atual nulos e length sendo 0

int linked_list_str_length(const LinkedList_str*); 
// @ Retorna o número de elementos 

int linked_list_str_size(const LinkedList_str*);
// @ Mesma ideia da função anterior

bool linked_list_str_is_empty(const LinkedList_str*); 
// @ Verifica se é uma LinkedList_str vazia. Se o parâmetro for nulo, o campo length for 0 ou o campo inicio for nulo, será retornado true.

bool linked_list_str_reset(LinkedList_str*);
/* @ Reseta o iterador interamente (o ponteiro atual) para apontar para o primeiro elemento da lista. Caso o parâmetro seja nulo ou a lista esteja vazia, retornará false.
  OBS: Sempre chame esta função antes de navegar pela lista!!!   
*/

bool linked_list_str_has_next(const LinkedList_str*);
/* @ Retorna true se o campo representado pelo ponteiro atual tiver o ponteiro Prox diferente de nulo. Se isso não ocorrer, o parâmetro for nulo, a lista estiver vazia ou atual for nulo, será retornado false.
   OBS: Chame a função linked_list_str_reset() se quiser que o campo atual seja diferente de nulo, caso a lista tenha elementos.
*/

bool linked_list_str_next(LinkedList_str*);
/* @ Retorna true se o campo atual conseguir avançar para o próximo elemento da lista, isto é, quando Prox for diferente de nulo. Se isso não for possível, o parâmetro for nulo ou a lista for vazia, será retornado false.
   OBS: Chame a função linked_list_str_reset() se quiser que o campo atual seja diferente de nulo, caso a lista tenha elementos.
*/

bool linked_list_str_current(const LinkedList_str*, String*);
/* @ Retorna no segundo parâmetro o elemento no ponteiro atual como cópia, isto é, no campo E de atual como cópia. Se o primeiro parâmetro for nulo, a lista for vazia ou o ponteiro atual for nulo, será retornado false e o segundo parâmetro não será alterado.
   OBS: Chame a função linked_list_str_reset() se quiser que o campo atual seja diferente de nulo, caso a lista tenha elementos.
*/

bool linked_list_str_insert_begin(LinkedList_str*, const String);
/* @ Insere o elemento do segundo parâmetro no início da lista. Se não conseguir por problema de memória ou parâmetro for inválido, será retornado false
   OBS: Será feito uma cópia da String antes de fazer a inserção e essa cópia que será usada.
*/

bool linked_list_str_insert_begin_cstr(LinkedList_str*, const char*);
// @ Usa a função anterior linked_list_str_insert_begin(), mas no segundo parâmetro será passado uma conversão provisória do apontador de char aqui passado para String. Se essa String não puder ser criada ou for obtido qualquer outro problema citado na função anterior, será retornado false.

bool linked_list_str_insert_end(LinkedList_str*, const String);
/* @ Insere o elemento do segundo parâmetro no fim da lista. Se não conseguir por problema de memória ou parâmetro for inválido, será retornado false
   OBS1: Será feito uma cópia da String antes de fazer a inserção e essa cópia que será usada.
   OBS2: Essa função funciona em tempo contante devido ao ponteiro interno fim.
*/

bool linked_list_str_insert_end_cstr(LinkedList_str*, const char*);
// @ Usa a função anterior linked_list_str_insert_end(), mas no segundo parâmetro será passado uma conversão provisória do apontador de char aqui passado para String. Se essa String não puder ser criada ou for obtido qualquer outro problema citado na função anterior, será retornado false.

bool linked_list_str_insert_ordered(LinkedList_str*, const String);
/* @ Insere o elemento do segundo parâmetro na lista de forma ordenada. Se não conseguir por problema de memória ou parâmetro inválido, será retornado false
   OBS1: Se a lista não estiver ordenada, então essa inserção não funcionará direito.
   OBS2: Será feito uma cópia da String antes de fazer a inserção e essa cópia que será usada.
*/

bool linked_list_str_insert_ordered_cstr(LinkedList_str*, const char*);
// @ Usa a função anterior linked_list_str_insert_ordered(), mas no segundo parâmetro será passado uma conversão provisória do apontador de char aqui passado para String. Se essa String não puder ser criada ou for obtido qualquer outro problema citado na função anterior, será retornado false.

bool linked_list_str_first(const LinkedList_str*, String*);
// @ Retorna no segundo parâmetro o primeiro elemento da lista como cópia. Se o primeiro parâmetro for nulo ou a lista for vazia, será retornado false e o segundo parâmetro não será alterado.
 
bool linked_list_str_last(const LinkedList_str*, String*);
// @ Retorna no segundo parâmetro o ultimo elemento da lista como cópia. Se o primeiro parâmetro for nulo ou a lista for vazia, será retornado false e o segundo parâmetro não será alterado.

bool linked_list_str_search(const LinkedList_str*, const String);
// @ Procura a primeira ocorrência do elemento do segundo parâmetro na lista e retorna true se conseguir encontrar. Se o primeiro parâmetro for nulo, a lista for vazia ou não encontrar o elemento, será retornado false.

bool linked_list_str_search_cstr(const LinkedList_str*, const char*);
// @ Usa a função anterior linked_list_str_search(), mas no segundo parâmetro será passado uma conversão provisória do apontador de char aqui passado para String. Se essa String não puder ser criada ou for obtido qualquer outro problema citado na função anterior, será retornado false.

int linked_list_str_count(const LinkedList_str*, const String);
// @ Retorna a quantidade de elementos do segundo parâmetro encontrado na lista. Se o primeiro parâmetro for nulo ou a lista for vazia, será retornado 0;

int linked_list_str_count_cstr(const LinkedList_str*, const char*);
// @ Usa a função anterior linked_list_str_count(), mas no segundo parâmetro será passado uma conversão provisória do apontador de char aqui passado para String. Se essa String não puder ser criada ou for obtido qualquer outro problema citado na função anterior, será retornado false.

bool linked_list_str_pop_first(LinkedList_str*);
/* @ Remove o primeiro elemento da lista. Se o parâmetro for nulo ou a lista for vazia, será retornado false
   OBS: Após remover o elemento na qual atual apontava (se for o caso), atual passará apontar para o próximo elemento. Caso atual apontava para o último No_str, então atual passará a ser nulo após a remoção.
*/

bool linked_list_str_pop_last(LinkedList_str*);
/* @ Remove o ultimo elemento da lista. Se o parâmetro for nulo ou a lista for vazia, será retornado false
   OBS1: Esta função navegará até o penúltimo elemento para conseguir remover sem problemas, logo essa função terá que percorrer todos os elementos. Sendo assim, não funciona em tempo constante
   OBS2: Após remover o elemento na qual atual apontava (se for o caso), atual passará apontar para o próximo elemento. Caso atual apontava para o último No_str, então atual passará a ser nulo após a remoção.
*/

bool linked_list_str_pop_current(LinkedList_str*);
/* @ Remove o elemento que está localizado na posicao do ponteiro atual. Se o parâmetro for nulo, a lista for vazia ou o ponteiro atual for nulo, será retornado false.
   OBS1: Chame a função linked_list_str_reset() se quiser que o campo atual seja diferente de nulo, caso a lista tenha elementos.
   OBS2: Após remover o elemento na qual atual apontava, atual passará apontar para o próximo elemento. Caso atual apontava para o último No_str, então atual passará a ser nulo após a remoção.
   OBS3: No pior caso (com o ponteiro atual apontando para o ultimo elemento da lista), essa função navegará até o penúltimo elemento para ajustar corretamente o ponteiro fim. Sendo assim, não funciona em tempo constante.
*/

bool linked_list_str_remove(LinkedList_str*, const String);
/* @ Remove a primeira ocorrencia do elemento do segundo parâmetro da lista. Se o primeiro parâmetro for nulo, a lista for vazia ou não conseguir encontrar o elemento, será retornado false.
   OBS: Se o ponteiro atual for exatamento o elemento a ser removido, este apontará para o próximo elemento. Se atual for o último elemento e for o elemento a ser removido, este apontará para nulo.
*/

bool linked_list_str_remove_cstr(LinkedList_str*, const char*);
// @ Usa a função anterior linked_list_str_remove(), mas no segundo parâmetro será passado uma conversão provisória do apontador de char aqui passado para String. Se essa String não puder ser criada ou for obtido qualquer outro problema citado na função anterior, será retornado false.

bool linked_list_str_copy(LinkedList_str*, const LinkedList_str*);
/* @ Copia todos os elementos da lista do segundo parâmetro para o primeiro. Se um dos parâmetros for nulo ou tiver problemas com alocação de memória, será retornado false e o primeiro parâmetro não será alterado.
   OBS1: Se o primeiro parâmetro já tiver elementos e a cópia for bem sucedida, então o conteúdo antigo será removido automaticamente
   OBS2: Por padrão, a lista nova obtida pela cópia terá o ponteiro atual sendo nulo, então cabe ao programaddor chamar a função linked_list_str_reset() para ajustar isso caso queira navegar pela lista
*/

void linked_list_str_free(LinkedList_str*);    
// @ Remove todos os elementos de LinkedList_str. Se a lista já for vazia ou o parâmetro for nulo, será feito nada

String linked_list_str_to_string(const LinkedList_str* list); 
/* @ Retorna uma representação de String de uma LinkedList_str. 
   OBS: Se falhar por parâmetro nulo ou se a lista for vazia, será retornado uma String como representação de que a lista é nula, isto é, será retornado a String "NULL"
*/

void linked_list_str_print(const LinkedList_str* list);
// @ Imprime na tela uma LinkedList_str usando como base a String obtida com a função acima linked_list_str_to_string() e esta mesma String é impressa com o string_print().

void linked_list_str_println(const LinkedList_str* list);
// @ Usa a função acima linked_list_str_print() e acrescenta um caractere '\n' na impressão.

#endif
