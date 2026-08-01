#ifndef VECTOR_EDGE_H
#define VECTOR_EDGE_H

#define VECTOR_EDGE_DEFAULT_CAPACITY 20
#include <stdbool.h>
#include "c_string.h"
#include "edge.h"

typedef enum {
    INSERTION_EDGE_N, INSERTION_EDGE_W, MERGE_EDGE_N, MERGE_EDGE_W, QUICK_EDGE_N, QUICK_EDGE_W
} SortType_edge;

typedef struct Vector_edge {
    Edge* vet;
    int length;
    int capacity;
} Vector_edge;

Vector_edge vector_edge_new_with_size(int);               
// @ Inicializa um Vector_edge com a capacidade passada como argumento na função. Se não conseguir alocar, será retornado um Vector_edge com campo vet nulo.

Vector_edge vector_edge_new_with_cvet(const Edge*, int);   
// @ Inicializa um Vector_edge com uma cópia de um vetor padrão da linguagem C com o seu respectivo tamanho. Se não conseguir, o campo vet de Vector_edge será nulo.

Vector_edge vector_edge_new();                            
// @ Inicializa um Vector_edge com a capacidade padrão de tamanho VECTOR_EDGE_DEFAULT_CAPACITY (tamanho 20). Se não conseguir, o campo vet de Vector_edge será nulo

float vector_edge_get_weight(const Vector_edge*, const Edge);
// @ Procura se existe a aresta do segundo parâmetro e, se existir, será retornado o seu respectivo peso. Se Vector_edge for nulo, vazio ou não encontrar a aresta, será retornado -1.

float vector_edge_get_weight_cstr_cstr(const Vector_edge*, const char*, const char*);
// @ Procura se existe a aresta com extremidades representadas pelo segundo e terceiro parâmetros e, se existir, será retornado o seu respectivo peso. Se Vector_edge for nulo, vazio ou não encontrar a aresta, será retornado -1.

bool vector_edge_update_weight(Vector_edge*, const Edge, float);
// @ Procura se existe a aresta do segundo parâmetro em Vector_edge e, se existente, mudará o seu respectivo peso pelo número fornecido no terceiro parâmetro. Se Vector_edge for nulo, o vetor for vazio ou não encontrar a aresta, será retornado false.

bool vector_edge_update_weight_cstr_cstr(Vector_edge*, const char*, const char*, float);
// @ Procura se existe uma aresta em Vector_edge que possui as extremidades do segundo parâmetro e do terceiro parâmetro e, se existente, mudará o seu respectivo peso pelo número fornecido no quarto parâmetro. Se Vector_edge for nulo, o vetor for vazio ou não encontrar a aresta, será retornado false.

bool vector_edge_contains_vertex(const Vector_edge*, const char*);
// @ Verifica se um vértice aparece em alguma aresta. Se Vector_edge for vazio ou não encontrar qualquer aresta com esse respectivo vértice, será retornado false.

Vector_edge vector_edge_get_edges_of(const Vector_edge*, const char*);
// @ Retorna todas as arestas de um vértice. Se Vector_edge for vazio ou não encontrar qualquer aresta com o vértice passado, será retornado um Vector_edge vazio.

bool vector_edge_is_empty(const Vector_edge*);            
// @ Verifica se o Vector_edge é vazio. Se o Vector_edge for nulo, o campo length for 0 ou o campo vet for nulo, será retornado true.

bool vector_edge_append(Vector_edge*, const Edge);              
// @ Adiciona ao final de Vector_edge o elemento do segundo parâmetro. Se o Vector_edge ou o campo vet for nulo ou tiver problema de realocação de memória, será retornado false

bool vector_edge_append_cstr_cstr(Vector_edge*, const char*, const char*);
/* @ Com o segundo e com o terceiro parâmetro, será criado um tipo Edge e esse tipo será adicionado ao final de Vector_edge. Se Vector_edge ou o campo vet for nulo, tiver problemas de realocação de memória ou falhar na criação de Edge será retornado false.
   OBS: Com esses dois últimos parâmetros, o campo u de Edge será o segundo parâmetro, o campo v será o terceiro parâmetro (se u <= v), o campo peso será 0 e o campo direcionado será false.
*/

bool vector_edge_append_cstr_cstr_weight_direction(Vector_edge*, const char*, const char*, float, bool);
/* @ Com os últimos quatro parâmetros, será criado um tipo Edge e esse tipo será adicionado ao final de Vector_edge. Se Vector_edge ou o campo vet for nulo, tiver problemas de realocação de memória será retornado false.
   OBS: Com esses quatro últimos parâmetros, o campo u de Edge será o segundo parâmetro, o campo v será o terceiro parâmetro (se u <= v), o campo peso será o quarto parâmetro e o campo direcionado será o quinto parâmetro.
*/

bool vector_edge_insert(Vector_edge*, int, const Edge);         
/* @ Adiciona o elemento do terceiro parâmetro na posicao indicada no segundo parâmetro. Se Vector_edge ou o campo vet for nulo, tiver problema de realocação de memória, será retornado false.  
OBS: se for um índice inválido, essa função adicionará o elemento no fim ou no início de vet a depender de qual foi a posição passada */

bool vector_edge_insert_cstr_cstr(Vector_edge*, int, const char*, const char*);
// @ Mesma ideia da função anterior, mas antes será criado um tipo Edge com o campo u sendo o segundo parâmetro, o campo v sendo o terceiro parâmetro (se u <= v), o peso sendo 0 e o campo direcionado sendo false. Qualquer falha dita anteriormente essa função retornará retornará false.

bool vector_edge_insert_cstr_cstr_weight_direction(Vector_edge*, int, const char*, const char*, float, bool);
// @ Mesma ideia da função anterior, mas antes será criado um tipo Edge com o campo u sendo o segundo parâmetro, o campo v sendo o terceiro parâmetro (se u <= v), o peso sendo o quarto parâmetro e o campo direcionado sendo o quinto parâmetro. Qualquer falha dita anteriormente essa função retornará retornará false.

bool vector_edge_insert_ordered_n(Vector_edge*, const Edge);      
/* @ Adiciona o elemento do segundo parâmetro em Vector_edge de forma ordenada por nome dos vértices u e v. Se Vector_edge ou o campo vet for nulo ou tiver problemas de realocação de memória, será retornado false.
   OBS: Se Vector_edge não estiver ordenado, então essa inserção não funcionará direito
*/

bool vector_edge_insert_ordered_n_cstr_cstr(Vector_edge*, const char*, const char*);      
/* @ Mesma ideia da função anterior, mas essa função usará o segundo e o terceiro parâmetro para ser os campos u e v de um tipo Edge que será criado na execução. Qualquer falha dita anteriormente essa função retornará retornará false.
   OBS1: O campo peso será 0 e direcionado será false nesse tipo Edge criado durante a execução
   OBS2: Se o segundo parâmetro "for maior" que o terceiro, então u será o terceiro parâmetro e o v será o segundo parâmetro
*/

bool vector_edge_insert_ordered_n_cstr_cstr_weight_direction(Vector_edge*, const char*, const char*, float, bool);      
// @ Mesma ideia da função anterior, mas essa função usará os últimos quatro parâmetros para ser os campos u, v, peso e direcionado, respectivamente, de um tipo Edge que será criado na execução. Qualquer falha dita anteriormente essa função retornará retornará false.

bool vector_edge_insert_ordered_w(Vector_edge*, const Edge);      
/* @ Adiciona o elemento do segundo parâmetro em Vector_edge de forma ordenada por pesos das arestas. Se Vector_edge ou o campo vet for nulo ou tiver problemas de realocação de memória, será retornado false.
   OBS1: Se Vector_edge não estiver ordenado, então essa inserção não funcionará direito
   OBS2: Se o segundo parâmetro "for maior" que o tercero, então u será o terceiro parâmetro e o v será o segundo parâmetro
*/

bool vector_edge_insert_ordered_w_cstr_cstr(Vector_edge*, const char*, const char*);      
/* @ Mesma ideia da função anterior, mas essa função usará o segundo e o terceiro parâmetro para ser os campos u e v de um tipo Edge que será criado na execução. Qualquer falha dita anteriormente essa função retornará retornará false.
   OBS: O campo peso será 0 e direcionado será false nesse tipo Edge criado durante a execução
*/

bool vector_edge_insert_ordered_w_cstr_cstr_weight_direction(Vector_edge*, const char*, const char*, float, bool);      
// @ Mesma ideia da função anterior, mas essa função usará os últimos quatro parâmetros para ser os campos u, v, peso e direcionado, respectivamente, de um tipo Edge que será criado na execução. Qualquer falha dita anteriormente essa função retornará retornará false.

bool vector_edge_at(const Vector_edge*, int, Edge*);      
// @ Retorna no terceiro parâmetro uma cópia do elemento da posição indicada no segundo parâmetro. Se Vector_edge ou vet for nulo ou tiver sido passada uma posição inválida, será retornado false na função e o terceiro parâmetro não será modificado.

int vector_edge_search_n(const Vector_edge*, const Edge);         
// @ Procura a primeira ocorrência do elemento indicado no segundo parâmetro em Vector_edge como comparação sendo por nome. Se Vector_edge ou o campo vet for nulo ou não encontrar o elemento indicado, será retornado -1, mas se encontrar o elemento, será retornado a sua respectiva posição.

int vector_edge_search_n_cstr_cstr(const Vector_edge*, const char*, const char*);         
// @ Mesma ideia da função anterior, mas é passado apenas os nomes dos vértices para a procura.

int vector_edge_search_w(const Vector_edge*, const Edge);         
// @ Procura a primeira ocorrência do elemento indicado no segundo parâmetro em Vector_edge como comparação sendo por peso. Se Vector_edge ou o campo vet for nulo ou não encontrar o elemento indicado, será retornado -1, mas se encontrar o elemento, será retornado a sua respectiva posição.

int vector_edge_search_w_weight(const Vector_edge*, float);         
// @ Mesma ideia da função anterior, mas é passado apenas o peso para a procura.

int vector_edge_binary_search_n(const Vector_edge*, const Edge);  
// @ Procura a primeira ocorrência do elemento indicado no segundo parâmetro em um Vector_edge com o campo vet ordenado como comparação sendo por nome. Se Vector_edge ou o campo vet for nulo ou não encontrar o elemento indicado, será retornado -1, mas se encontrar o elemento, será retornado a sua respectiva posição.

int vector_edge_binary_search_n_cstr_cstr(const Vector_edge*, const char*, const char*);  
// @ Mesma ideia da função anterior, mas é passado apenas os nomes dos vértices para a procura.

int vector_edge_binary_search_w(const Vector_edge*, const Edge);  
// @ Procura a primeira ocorrência do elemento indicado no segundo parâmetro em um Vector_edge com o campo vet ordenado como comparação sendo por peso. Se Vector_edge ou o campo vet for nulo ou não encontrar o elemento indicado, será retornado -1, mas se encontrar o elemento, será retornado a sua respectiva posição.

int vector_edge_binary_search_w_weight(const Vector_edge*, float);  
// @ Mesma ideia da função anterior, mas é passado apenas o peso para a procura.

bool vector_edge_pop(Vector_edge*, Edge*);                
// @ Remove o elemento de Vector_edge da última posição e retorna este elemento como cópia no segundo parâmetro. Se Vector_edge ou o campo vet for nulo, será retornado false na função e o segundo parâmetro não será modificado.

bool vector_edge_pop_at(Vector_edge*, int, Edge*);        
// @ Remove o elemento de Vector_edge da posição indicada no segundo parâmetro e este elemento é retornado no terceiro parâmetro como cópia. Se Vector_edge ou o campo vet for nulo e a posição de remoção for inválida, será retornado false na função e o terceiro parâmetro não será modificado.

bool vector_edge_remove_n(Vector_edge*, const Edge);              
// @ Remove a primeira ocorrência do elemento do segundo parâmetro em Vector_edge como comparação sendo por nome. Se Vector_edge ou o campo vet for nulo ou não encontrar este elemento, será retornado false.

bool vector_edge_remove_n_cstr_cstr(Vector_edge*, const char*, const char*);
// @ Mesma ideia da função anterior, mas é passado apenas os nomes dos vértices para a remoção.

bool vector_edge_remove_w(Vector_edge*, const Edge);   
// @ Remove a primeira ocorrência do elemento do segundo parâmetro em Vector_edge como comparação sendo por peso. Se Vector_edge ou o campo vet for nulo ou não encontrar este elemento, será retornado false.

bool vector_edge_remove_w_weight(Vector_edge*, float); 
// @ Mesma ideia da função anterior, mas é passado apenas o peso para a remoção.

int vector_edge_length(const Vector_edge*);               
// @ Retorna o número de elementos de Vector_edge. Se Vector_edge for nulo, será retornado 0.

int vector_edge_size(const Vector_edge*);
// @ Mesma ideia da função anterior.

int vector_edge_count_w(const Vector_edge*, float);          
// @ Retorna a quantidade de ocorrências que o peso do segundo parâmetro aparece em Vector_edge. Se Vector_edge ou o campo vet for nulo, será retornado 0.

void vector_edge_clear(Vector_edge*);                     
// @ Considera todo dado disponível em Vector_edge como lixo de memória, em outras palavras, "remove" todos os elementos sem liberar a respectiva memória (do vetor em si, mas dos elementos sim serão removidos), tornando o campo length igual a 0. Isso ocorrerá se Vector_edge e o campo vet forem diferentes de nulo.

void vector_edge_free(Vector_edge*);                      
// @ Libera a memória de Vector_edge e ajusta os campos length e capacity para 0 se Vector_edge e o campo vet forem diferentes de nulo.

bool vector_edge_copy_cvet(Vector_edge*, const Edge*, int);  
// @ Copia os dados de vetor padrão da linguagem C para Vector_edge. Se já tiver uma memória alocada para Vector_edge e conseguir copiar os dados, esta memória será liberada para ter a nova atribuição. Se Vector_edge ou o vetor for nulo, o número de elementos do vetor (terceiro parâmetro) for menor ou igual a 0 ou então tiver problemas de alocação de memória, será retornado false.

bool vector_edge_copy(Vector_edge*, const Vector_edge*);       
// @ Copia os dados do segundo parâmetro para o primeiro. Basicamente chamará a função vector_edge_copy_cvet() com o campo vet e seu respectivo tamanho do segundo parâmetro.

String vector_edge_to_string(const Vector_edge*);    
// @ Retorna a representação de Vector_edge como String. Se a String inicial de retorno não puder ser criada, será retornado "[]".

void vector_edge_print(const Vector_edge*);        
// @ Imprime na tela uma representação de Vector_edge usando a função vector_edge_to_string().

void vector_edge_println(const Vector_edge*);      
// @ Usa a função vector_edge_print() e imprime adicionalmente um caractere '\n' ao final

Edge* vector_edge_to_cvet(const Vector_edge*);     
// @ Retorna uma cópia do campo vet de Vector_edge ou nulo se não conseguir. Será retornado uma alocação dinâmica, então tem que remover cada elemento individualmente e depois liberar a memória do vetor em si com o free().

const Edge* vector_edge_cvet(const Vector_edge*);  
// @ Retorna o próprio campo de vet de Vector_edge como constante, mas este campo NÃO deve ter a memória liberada com o free() ou liberar a memória dos elementos internos


/* Algoritmos de Ordenação */
// OBS: sufixo n indica que a ordenação será por nomes das arestas, já sufixo w indica que será por pesos.

void vector_edge_sort_n(Vector_edge*);                     
// @ Se o campo length for até de tamanho 16, será chamado o InsertionSort_edge_n e se for maior que isso, será chamado o QuickSort_edge_n.

void vector_edge_sort_w(Vector_edge*);                     
// @ Se o campo length for até de tamanho 16, será chamado o InsertionSort_edge_w e se for maior que isso, será chamado o QuickSort_edge_w.

bool vector_edge_choose_sort(Vector_edge*, SortType_edge);
/* @ Escolha a sua ordenação de preferência sem precisar se preocupar com os parâmetros dos algoritmos de ordenação. Recomendo usar esta função em comparação ao chamar cada uma delas manualmente. Se passar uma ordenação inválida ou Vector_edge ou o campo vet for nulo, o Vector_edge (se existir) não será ordenado e será retornará false. 
   OBS: As opções são as que estão no enum bem mais acima, mas deixarei aqui também explícito quais são ao passar como segundo argumento da função: INSERTION_EDGE_N, INSERTION_EDGE_W, MERGE_EDGE_N, MERGE_EDGE_W, QUICK_EDGE_N e QUICK_EDGE_W. 
*/

#endif
