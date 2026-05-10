#ifndef VECTOR_H
#define VECTOR_H

typedef int tipo;       // Se quiser mudar o tipo, mude aqui!
#define FORMAT "%d"     // Se quiser mudar o formato, mude aqui!

typedef struct Vector {
    tipo* vet;
    int length;
    int Max_length;

} Vector;

typedef enum {
    SORT_BUBBLE, SORT_BUBBLE_REC, SORT_SELECTION, SORT_SELECTION_REC,
    SORT_INSERTION, SORT_MERGE, SORT_QUICK
} SortType;

Vector vector_new_with_size(int);
Vector vector_new_with_vet(tipo*, int);   // Mais para testes!
Vector vector_new();
bool increase_size(tipo**, int);
bool vector_append(Vector*, tipo);
bool vector_insert(Vector*, int, tipo);
bool vector_insert_ordered(Vector*, tipo);
int vector_search(Vector, tipo);
int vector_binary_search(Vector, tipo);
bool vector_pop(Vector*, tipo*);
bool vector_pop_at(Vector*, int, tipo*);
bool vector_remove(Vector*, tipo);
int vector_length(Vector);
int vector_count(Vector, tipo);
void vector_print(Vector);
void vector_free(Vector*);
bool vector_copy(Vector*, tipo*, int);


/* Ordenação */
bool Intercalar(tipo*, int, int, int);
tipo mediana(tipo, tipo, tipo);
void Particionar(tipo*, int, int, tipo, int*, int*);
void BubbleSort(Vector*, int);
void BubbleSort_Recursivo(Vector*, int);
void SelectionSort(Vector*, int);
void SelectionSort_Recursivo(Vector*, int);
void InsertionSort(Vector*, int);
bool MergeSort(Vector*, int, int);
void QuickSort(Vector*, int, int);
void vector_sort(Vector*);
bool vector_choose_sort(Vector*, SortType);
/* Ordenação */


#endif
