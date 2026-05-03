#ifndef VECTOR_H
#define VECTOR_H

#define VECTOR_DEFAULT_CAPACITY 50
#include <stdbool.h>
#include "c_string.h"

/* MUDE O TIPO E A PRECISAO AQUI. NO CASO DO ÚLTIMO, A PRECISAO SERÁ USADA EM TIPOS FLOAT E DOUBLE APENAS */ 
#define PRECISION 2    // Mude a precisão de float e double aqui

//!!!!!!!!!!!!!!! Mude aqui qual tipo primitivo quer escolher !!!!!!!!!!!!!!!!!

#define TIPO_INT
// #define TIPO_LONG
// #define TIPO_LONG_LONG
// #define TIPO_FLOAT
// #define TIPO_DOUBLE
// #define TIPO_DOUBLE_G
// #define TIPO_CHAR


#if defined(TIPO_INT)

    typedef int tipo;
    #define TO_STRING(x) string_from_int((x))

#elif defined(TIPO_LONG)

    typedef long tipo;
    #define TO_STRING(x) string_from_long((x))

#elif defined(TIPO_LONG_LONG)

    typedef long long tipo;
    #define TO_STRING(x) string_from_long_long((x))

#elif defined(TIPO_FLOAT)

    typedef float tipo;
    #define TO_STRING(x) string_from_float((x), PRECISION)

#elif defined(TIPO_DOUBLE)

    typedef double tipo;
    #define TO_STRING(x) string_from_double((x), PRECISION)

#elif defined(TIPO_DOUBLE_G)

    typedef double tipo;
    #define TO_STRING(x) string_from_double_g((x))

#elif defined(TIPO_CHAR)

    typedef char tipo;
    #define TO_STRING(x) string_from_char((x))

#else
      #error "Defina UM tipo válido"

#endif

/* MUDE O TIPO E A PRECISAO AQUI. NO CASO DO ÚLTIMO, A PRECISAO SERÁ USADA EM TIPOS FLOAT E DOUBLE APENAS */ 


typedef struct Vector {
    tipo* vet;
    int length;
    int capacity;

} Vector;

typedef enum {
    BUBBLE, BUBBLE_REC, SELECTION, SELECTION_REC,
    INSERTION, MERGE, QUICK
} SortType;

Vector vector_new_with_size(int);               
// @ Inicializa um Vector com a capacidade passada como argumento na função. Se não conseguir alocar, será retornado um Vector com campo vet nulo.

Vector vector_new_with_cvet(const tipo*, int);   
// @ Inicializa um Vector com uma cópia de um vetor padrão da linguagem C com o seu respectivo tamanho. Se não conseguir, o campo vet de Vector será nulo.

Vector vector_new();                            
// @ Inicializa um Vector com a capacidade padrão de tamanho VECTOR_DEFAULT_CAPACITY (tamanho 50). Se não conseguir, o campo vet de Vector será nulo

bool vector_is_empty(const Vector*);            
// @ Verifica se o Vector é vazio. Se o Vector for nulo, o campo length for 0 ou o campo vet for nulo, será retornado true.

bool vector_append(Vector*, tipo);              
// @ Adiciona ao final de Vector o elemento do segundo parâmetro. Se o Vector ou o campo vet for nulo ou tiver problema de realocação de memória, será retornado false

bool vector_insert(Vector*, int, tipo);         
/* @ Adiciona o elemento do terceiro parâmetro na posicao indicada no segundo parâmetro. Se Vector ou o campo vet for nulo, tiver problema de realocação de memória, será retornado false.  
OBS: se for um índice inválido, essa função adicionará o elemento no fim ou no início de vet a depender de qual foi a posição passada */

bool vector_insert_ordered(Vector*, tipo);      
// @ Adiciona o elemento do segundo parâmetro em Vector de forma ordenada. Se Vector ou o campo vet for nulo ou tiver problemas de realocação de memória, será retornado false.

bool vector_at(const Vector*, int, tipo*);      
// @ Retorna no terceiro parâmetro o elemento da posição indicada no segundo parâmetro. Se Vector ou vet for nulo ou tiver sido passada uma posição inválida, será retornado false na função e o terceiro parâmetro não será modificado.

int vector_search(const Vector*, tipo);         
// @ Procura a primeira ocorrência do elemento indicado no segundo parâmetro em Vector. Se Vector ou o campo vet for nulo ou não encontrar o elemento indicado, será retornado -1, mas se encontrar o elemento, será retornado a sua respectiva posição.

int vector_binary_search(const Vector*, tipo);  
// @ Procura a primeira ocorrência do elemento indicado no segundo parâmetro em um Vector com o campo vet ordenado. Se Vector ou o campo vet for nulo ou não encontrar o elemento indicado, será retornado -1, mas se encontrar o elemento, será retornado a sua respectiva posição.

bool vector_pop(Vector*, tipo*);                
// @ Remove o elemento de Vector da última posição e retorna este elemento no segundo parâmetro. Se Vector ou o campo vet for nulo, será retornado false na função e o segundo parâmetro não será modificado.

bool vector_pop_at(Vector*, int, tipo*);        
// @ Remove o elemento de Vector da posição indicada no segundo parâmetro e este elemento é retornado no terceiro parâmetro. Se Vector ou o campo vet for nulo e a posição de remoção for inválida, será retornado false na função e o terceiro parâmetro não será modificado.

bool vector_remove(Vector*, tipo);              
// @ Remove a primeira ocorrência do elemento do segundo parâmetro em Vector. Se Vector ou o campo vet for nulo ou não encontrar este elemento, será retornado false.

int vector_length(const Vector*);               
// @ Retorna o número de elementos de Vector. Se Vector for nulo, será retornado 0.

int vector_count(const Vector*, tipo);          
// @ Retorna a quantidade de ocorrências que o elemento do segundo parâmetro aparece em Vector. Se Vector ou o campo vet for nulo, será retornado 0.

void vector_clear(Vector*);                     
// @ Considera todo dado disponível em Vector como lixo de memória, em outras palavras, "remove" todos os elementos sem liberar a respectiva memória, tornando o campo length igual a 0. Isso ocorrerá se Vector e o campo vet forem diferentes de nulo.

void vector_free(Vector*);                      
// @ Libera a memória de Vector e ajusta os campos length e capacity para 0 se Vector e o campo vet forem diferentes de nulo.

bool vector_copy_cvet(Vector*, const tipo*, int);  
// @ Copia os dados de vetor padrão da linguagem C para Vector. Se já tiver uma memória alocada para Vector, esta será liberada para ter a nova atribuição. Se Vector ou o vetor for nulo, o número de elementos do vetor (terceiro parâmetro) for menor ou igual a 0 ou então tiver problemas de alocação de memória, será retornado false.

bool vector_copy(Vector*, const Vector*);       
// @ Copia os dados do segundo parâmetro para o primeiro. Basicamente chamará a função vector_copy_cvet com o campo vet e seu respectivo tamanho do segundo parâmetro.

String vector_to_string(const Vector*);    
// @ Retorna a representação de Vector como String. Se a String de retorno não puder ser criada, será retornada uma String vazia.

void vector_print(const Vector*);        
// @ Imprime na tela uma representação de Vector usando a função vector_to_string.

void vector_println(const Vector*);      
// @ Usa a função vector_print e imprime adicionalmente um caractere '\n'

tipo* vector_to_cvet(const Vector*);     
// @ Retorna umam cópia do campo vet de Vector ou nulo se não conseguir

const tipo* vector_cvet(const Vector*);  
// @ Retorna o próprio campo de vet de Vector como constante, mas este campo NÃO deve ter a memória liberada com o free()


/* Algoritmos de Ordenação */
void BubbleSort(Vector*, int);
void BubbleSort_Recursivo(Vector*, int);
void SelectionSort(Vector*, int);
void SelectionSort_Recursivo(Vector*, int);
void InsertionSort(Vector*, int);
bool MergeSort(Vector*, int, int);
void QuickSort(Vector*, int, int);
/* Algoritmos de Ordenação */

void vector_sort(Vector*);                     
// @ Se o campo length for até de tamanho 16, será chamado o InsertionSort e se for maior que isso, será chamado o QuickSort.

bool vector_choose_sort(Vector*, SortType);    
/* @ Escolha a sua ordenação de preferência sem precisar se preocupar com os parâmetros dos algoritmos de ordenação. Recomendo usar esta função em comparação ao chamar cada uma delas manualmente. Se passar uma ordenação inválida ou Vector ou o campo vet for nulo, o Vector (se existir) não será ordenado e será retornará false. 
OBS1: as opções são as que estão no enum bem mais acima, mas deixarei aqui também explícito quais são ao passar como segundo argumento da função: BUBBLE, BUBBLE_REC, SELECTION, SELECTION_REC, INSERTION, MERGE e QUICK. 
OBS2: Esta função serve mais como uma comparação entre os algoritmos de ordenação se tiver curioso ou fizer questão de usar o MergeSort por exemplo. Se só quer ordenar, use a função acima vector_sort.
*/



#endif
