#ifndef VECTOR_STR_H
#define VECTOR_STR_H

#define VECTOR_STR_DEFAULT_CAPACITY 20 
#include <stdbool.h>
#include "c_string.h"

typedef struct Vector_str {
    String* vet;
    int length;
    int capacity;

} Vector_str;

typedef enum {
    BUBBLE_STR, BUBBLE_REC_STR, SELECTION_STR, SELECTION_REC_STR,
    INSERTION_STR, MERGE_STR, QUICK_STR
} SortType_str;

/* 
@@@  OBS1: Aqui eu uso as funções de string supondo que nem sempre deem errado, sendo principalmente as que tratam de alocação, como string_copy e string_new_with_size
@@@  OBS2: Funções como vector_str_pop, vector_str_pop_at, vector_str_remove, vector_str_clear e vector_str_free vão remover as strings que forem necessárias para não ter lixo de memória. As 2 primeiras funções terão como retorno de string (no parâmetro de função já indicado em cada uma delas) uma cópia do conteúdo a ser obtido, e não o próprio conteúdo de string de Vector_str.
*/

Vector_str vector_str_new_with_size(int);               
// @ Inicializa um Vector_str com a capacidade passada como argumento na função. Se não conseguir alocar, será retornado um Vector_str com campo vet nulo.

Vector_str vector_str_new_with_cvet(const String*, int);   
// @ Inicializa um Vector_str com uma cópia de um vetor padrão da linguagem C com o seu respectivo tamanho, mas aqui é um vetor de String. Se não conseguir, o campo vet de Vector_str será nulo.

Vector_str vector_str_new_with_cvet_cstr(const char**, int);   
// @ Inicializa um Vector_str com uma cópia de um vetor padrão da linguagem C com o seu respectivo tamanho, mas aqui é um vetor de char*. Se não conseguir, o campo vet de Vector_str será nulo.

Vector_str vector_str_new();                            
// @ Inicializa um Vector_str com a capacidade padrão de tamanho VECTOR_STR_DEFAULT_CAPACITY (tamanho 20). Se não conseguir, o campo vet de Vector_str será nulo

bool vector_str_is_empty(const Vector_str*);            
// @ Verifica se o Vector_str é vazio. Se o Vector_str for nulo, o campo length for 0 ou o campo vet for nulo, será retornado true.

bool vector_str_append(Vector_str*, const String);              
// @ Adiciona ao final de Vector_str o elemento do segundo parâmetro. Se o Vector_str ou o campo vet for nulo ou tiver problema de realocação de memória, será retornado false

bool vector_str_append_cstr(Vector_str*, const char*);     
// @ Chama a função anterior append criando um novo tipo String a partir desse vetor de caracteres do segundo parâmetro. Em problemas de criar a String, será retornado false, além dos problemas da função usada.

bool vector_str_insert(Vector_str*, int, const String);         
/* @ Adiciona o elemento do terceiro parâmetro na posicao indicada no segundo parâmetro. Se Vector_str ou o campo vet for nulo, tiver problema de realocação de memória, será retornado false.  OBS: se for um índice inválido, essa função adicionará o elemento no fim ou no início de vet a depender de qual foi a posição passada  */

bool vector_str_insert_cstr(Vector_str*, int, const char*);  
// @ Chama a função anterior insert criando um novo tipo String a partir desse vetor de caracteres do terceiro parâmetro. Em problemas de criar a String, será retornado false, além dos problemas da função usada.

bool vector_str_insert_ordered(Vector_str*, const String);      
// @ Adiciona o elemento do segundo parâmetro em Vector_str de forma ordenada. Se Vector_str ou o campo vet for nulo ou tiver problemas de realocação de memória, será retornado false.

bool vector_str_insert_ordered_cstr(Vector_str*, const char*);  
// @ Chama a função anterior insert_ordered criando um novo tipo String a partir desse vetor de caracteres do terceiro parâmetro. Em problemas de criar a String, será retornado false, além dos problemas da função usada.

bool vector_str_at(const Vector_str*, int, String*);     
// @ Retorna no terceiro parâmetro o elemento da posição indicada no segundo parâmetro. Se Vector_str ou vet for nulo ou tiver sido passada uma posição inválida, será retornado false na função e o terceiro parâmetro não será modificado.

int vector_str_search(const Vector_str*, const String);         
// @ Procura a primeira ocorrência do elemento indicado no segundo parâmetro em Vector_str. Se Vector_str ou o campo vet for nulo ou não encontrar o elemento indicado, será retornado -1, mas se encontrar o elemento, será retornado a sua respectiva posição.

int vector_str_search_cstr(const Vector_str*, const char*);  
// @ Usa a função anterior search com o segundo parâmetro se tornando uma String. Se falhar nessa transformação, será retornado -1.

int vector_str_binary_search(const Vector_str*, const String);  
// @ Procura a primeira ocorrência do elemento indicado no segundo parâmetro em um Vector_str com o campo vet ordenado. Se Vector_str ou o campo vet for nulo ou não encontrar o elemento indicado, será retornado -1, mas se encontrar o elemento, será retornado a sua respectiva posição.

int vector_str_binary_search_cstr(const Vector_str*, const char*);  
// @ Usa a função anterior binary_search com o segundo parâmetro se tornando uma String. Se falhar nessa transformação, será retornado -1.

bool vector_str_pop(Vector_str*, String*);                
// @ Remove o elemento de Vector_str da última posição e retorna este elemento no segundo parâmetro. Se Vector_str ou o campo vet for nulo, será retornado false na função e o segundo parâmetro não será modificado.

bool vector_str_pop_at(Vector_str*, int, String*);        
// @ Remove o elemento de Vector_str da posição indicada no segundo parâmetro e este elemento é retornado no terceiro parâmetro. Se Vector_str ou o campo vet for nulo e a posição de remoção for inválida, será retornado false na função e o terceiro parâmetro não será modificado.

bool vector_str_remove(Vector_str*, const String);        
// @ Remove a primeira ocorrência do elemento do segundo parâmetro em Vector_str. Se Vector_str ou o campo vet for nulo ou não encontrar este elemento, será retornado false.

bool vector_str_remove_cstr(Vector_str*, const char*);    
// @ Usa a função anterior de remoção com o segundo parâmetro se tornando uma String. Se falhar nessa transformação, será retornado false.

int vector_str_length(const Vector_str*);               
// @ Retorna o número de elementos de Vector_str. Se Vector_str for nulo, será retornado 0.

int vector_str_size(const Vector_str*);
// @ Mesma ideia da função anterior.

int vector_str_count(const Vector_str*, const String);          
// @ Retorna a quantidade de ocorrências que o elemento do segundo parâmetro aparece em Vector_str. Se Vector_str ou o campo vet for nulo, será retornado 0.

int vector_str_count_cstr(const Vector_str*, const char*);          
// @ Chama a função anterior com o segundo vetor de caracteres se transformando em String. Se não conseguir, será retornado -1.

void vector_str_clear(Vector_str*);                     
// @ Considera todo dado disponível em Vector_str como lixo de memória, em outras palavras, "remove" todos os elementos sem liberar a respectiva memória de Vector (as Strings sim), tornando o campo length igual a 0. Isso ocorrerá se Vector_str e o campo vet forem diferentes de nulo.

void vector_str_free(Vector_str*);                      
// @ Libera a memória de Vector_str e ajusta os campos length e capacity para 0 se Vector_str e o campo vet forem diferentes de nulo.

bool vector_str_copy_cvet(Vector_str*, const String*, int);  
// @ Copia os dados de vetor padrão da linguagem C para Vector_str. Se já tiver uma memória alocada para Vector_str, esta será liberada para ter a nova atribuição. Se Vector_str ou o vetor de String for nulo, o número de elementos do vetor de String (terceiro parâmetro) for menor ou igual a 0 ou então tiver problemas de alocação de memória, será retornado false.

bool vector_str_copy_cvet_cstr(Vector_str*, const char**, int);
/* @ Mesma ideia da função anterior, mas, a fim de ficar mais prático, é passado um vetor de apontador de caracteres mesmo. Se o segundo parâmetro for nulo ou acontecer os problemas de forma semelhante a função anterior, será retornado false.
OBS: Se alguma string padrão de C for nula no vetor passado do segundo parâmetro, então colocarei, na respectiva posição de Vector_str, a string "NULL"
*/
bool vector_str_copy(Vector_str*, const Vector_str*);       
// @ Copia os dados do segundo parâmetro para o primeiro. Basicamente chamará a função Vector_str_copy_cvet com o campo vet e seu respectivo tamanho do segundo parâmetro.

String vector_str_to_string(const Vector_str*);    
// @ Retorna a representação de Vector_str como String. Se a String de retorno não puder ser criada, será retornado "[]".

void vector_str_print(const Vector_str*);        
// @ Imprime na tela uma representação de Vector_str usando a função vector_str_to_string.

void vector_str_println(const Vector_str*);      
// @ Usa a função vector_str_print e imprime adicionalmente um caractere '\n'

String* vector_str_to_cvet(const Vector_str*);           
// @ Retorna uma cópia do campo vet de Vector_str ou nulo se não conseguir

const String* vector_str_cvet(const Vector_str*);        
// @ Retorna o próprio campo de vet de Vector como constante, mas este campo NÃO deve ter a memória liberada com o free()


/* Algoritmos de Ordenação */
void BubbleSort_str(Vector_str*, int);
void BubbleSort_Recursivo_str(Vector_str*, int);
void SelectionSort_str(Vector_str*, int);
void SelectionSort_Recursivo_str(Vector_str*, int);
void InsertionSort_str(Vector_str*, int);
bool MergeSort_str(Vector_str*, int, int);
void QuickSort_str(Vector_str*, int, int);
/* Algoritmos de Ordenação */

void vector_str_sort(Vector_str*);                     
// @ Se o campo length for até de tamanho 16, será chamado o InsertionSort_str e se for maior que isso, será chamado o QuickSort_str.

bool vector_str_choose_sort(Vector_str*, SortType_str);    
/* @ Escolha a sua ordenação de preferência sem precisar se preocupar com os parâmetros dos algoritmos de ordenação. Recomendo usar esta função em comparação ao chamar cada uma delas manualmente. Se passar uma ordenação inválida ou Vector_str ou o campo vet for nulo, o Vector_str (se existir) não será ordenado e será retornará false. 
OBS1: As opções são as que estão no enum bem mais acima, mas deixarei aqui também explícito quais são ao passar como segundo argumento da função: BUBBLE_STR, BUBBLE_REC_STR, SELECTION_STR, SELECTION_REC_STR, INSERTION_STR, MERGE_STR e QUICK_STR. 
OBS2: Esta função serve mais como uma comparação entre os algoritmos de ordenação se tiver curioso ou fizer questão de usar o MergeSort_str por exemplo. Se só quer ordenar, use a função acima vector_str_sort.
*/


#endif
