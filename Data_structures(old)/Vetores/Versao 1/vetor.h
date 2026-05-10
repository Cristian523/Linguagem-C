#ifndef VETOR_H
#define VETOR_H

typedef int tipo;  // Quando quiser mudar o tipo, mude aqui
#define TIPO_FORMATO "%d"  // Quando quiser mudar o especificador, mude aqui


/* Funções auxiliares para ordenação */
void Intercalar(tipo*, int, int, int);
tipo mediana(tipo, tipo, tipo);
void Particionar(tipo*, int, int, tipo, int*, int*);
/* Funções auxiliares para a ordenação */


/* Funções para imprimir um vetor, inserir, buscar e remover um elemento de um vetor */
void Imprimir(tipo*, int);
void Insere(tipo*, tipo, int*);
int Insere_Dinamico(tipo**, tipo, int*, int*);
void Insere_Ordenado(tipo*, tipo, int*);
int Insere_Ordenado_Dinamico(tipo**, tipo, int*, int*);
int Busca(tipo*, tipo, int);
int Busca_Binaria(tipo*, tipo, int);
int Remove(tipo*, tipo, int*);     // Precisa da função Busca().
int Remove_O(tipo*, tipo, int*);   // Precisa da função Busca().
/* Funções para imprimir um vetor, inserir, buscar e remover um elemento de um vetor */


/* Funções para ordenar um vetor */
void BubbleSort(tipo*, int);
void BubbleSort_Recursivo(tipo*, int);
void SelectionSort(tipo*, int);
void SelectionSort_Recursivo(tipo*, int);
void InsertionSort(tipo*, int);
void MergeSort(tipo*, int, int);  // Precisa da 1° função auxiliar.
void QuickSort(tipo*, int, int);  // Precisa da 2° e 3° funções auxiliares.
/* Funções para ordenar um vetor */

#endif
