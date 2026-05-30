#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "c_string.h"
#include "tree.h"

/* Funções auxiliares usando apenas No_tree */
static bool insert_no_tree(No_tree**, tipo_tree);  // Insere o elemento na árvore.
static void free_no_tree(No_tree**);   // Desaloca o nó específico passado como parâmetro
static void free_all_no_tree(No_tree**);  // Libera a memória de todos os nós.
static void to_string_all_no_tree(No_tree*, String*);  // Retorna no segundo parâmetro uma representação dos nós como String de forma básica
static void to_string_all_detailed_no_tree(No_tree*, String*);  // Retorna no segundo parâmetro uma representação dos nós como String de forma detalhada
static int height_no_tree(No_tree*);  // retorna a altura de um determinado nó da árvore, se existente
static void cvet_from_all_no_tree(No_tree*, tipo_tree*, int*);  // Retorna um vetor da linguagem no segundo parâmetro com todos os elementos da árvore  
/* Funções auxiliares usando apenas No_tree */

static int number_comparation(tipo_tree a, tipo_tree b) {     // Comparação enre números
    #if defined(TIPO_TREE_FLOAT)
        if (fabsf(a - b) < 1e-6f) return 0;
    #elif defined(TIPO_TREE_DOUBLE) || defined(TIPO_TREE_DOUBLE_G)
        if (fabs(a - b) < 1e-9) return 0;
    #endif
    
    if (a < b) return -1;
    else if (a > b) return 1;
    else return 0;
}


Tree tree_new() {  // Inicializa um tipo Tree.
    Tree arvore;
    arvore.T = NULL;
    arvore.size = 0;
    return arvore;
}

bool tree_is_empty(const Tree* arvore) {  // Verifica se é uma árvore vazia. 
    if (arvore == NULL || arvore->T == NULL || arvore->size <= 0)
        return true;
    return false;
}

int tree_size(const Tree* arvore) {  // Retorna o número de elementos da árvore
    if (arvore == NULL || arvore->T == NULL)
        return 0;
    return arvore->size;
}

bool tree_insert(Tree* arvore, tipo_tree elemento) {  // Insere o elemento do segundo parâmetro.
    if (arvore == NULL)
        return false;
    
    if (insert_no_tree(&arvore->T, elemento)) {
        arvore->size++;
        return true;
    }
    return false;
}

bool tree_search(const Tree* arvore, tipo_tree elemento) {  // Busca se o elemento do segundo parâmetro está na árvore.
    if (tree_is_empty(arvore))
        return false;
    No_tree* p = arvore->T;
    while (p != NULL) {
        int comp = number_comparation(elemento, p->E);
        if (comp == 0)
            return true;
        else if (comp < 0)
            p = p->Esq;
        else
            p = p->Dir;
    }
    return false;
}

bool tree_remove(Tree* arvore, tipo_tree elemento) { // Remove o elemento do terceiro parâmetro se ele estiver presente na árvore. 
    if (tree_is_empty(arvore))
        return false;
    
    No_tree** p = &arvore->T;
    while (*p != NULL) {
        int comp = number_comparation(elemento, (*p)->E);
        if (comp == 0) {
            if ((*p)->Q > 1) {
                (*p)->Q--;
                arvore->size--;
                return true;
            }
            break;
        }
        else if (comp < 0)
            p = &((*p)->Esq);
        else
            p = &((*p)->Dir);
    }
    if (*p == NULL)
        return false;
    
    free_no_tree(p);
    arvore->size--;
    return true;
}

void tree_free(Tree* arvore) {  // Libera a memória da árvore.
    if (arvore == NULL || arvore->T == NULL)
        return;
    free_all_no_tree(&arvore->T);
    arvore->T = NULL;
    arvore->size = 0;
}

String tree_to_string(const Tree* arvore) {   // Retorna uma representação básica dos elementos da árvore como String.
    if (tree_is_empty(arvore))
        return string_new_with_cstr("NULL");
    String cadeia = string_new_with_size(6 * arvore->size);
    if (!string_is_valid(&cadeia))
        return string_new_with_cstr("NULL");
    to_string_all_no_tree(arvore->T, &cadeia);
    string_pop(&cadeia);   // remove o caractere " " adicionado ao final
    return cadeia;
}

String tree_to_string_detailed(const Tree* arvore) {  // Retorna uma representação detalhada da árvore como String.
    if (tree_is_empty(arvore))
        return string_new_with_cstr("NULL");
    String cadeia = string_new_with_size(47 * arvore->size);   // Um tamanho bem grande, mas necessário
    if (!string_is_valid(&cadeia))
        return string_new_with_cstr("NULL");
    to_string_all_detailed_no_tree(arvore->T, &cadeia);
    string_pop(&cadeia);   // remove um caractere "\n" adicionado ao final
    return cadeia;
}

void tree_print(const Tree* arvore) {  // Imprime a String obtida com a função tree_to_string().
    String cadeia = tree_to_string(arvore);
    string_print(&cadeia);
    string_free(&cadeia);
}

void tree_print_detailed(const Tree* arvore) {  // Imprime a String obtida com a função tree_to_string_detailed().
    String cadeia = tree_to_string_detailed(arvore);
    string_print(&cadeia);
    string_free(&cadeia);
}

void tree_println(const Tree* arvore) {  // Usa a função tree_print() e imprime o caractere '\n' ao final.
    tree_print(arvore);
    printf("\n");
}

void tree_println_detailed(const Tree* arvore) {  // Usa a função tree_print_detailed() e imprime o caractere '\n' ao final.
    tree_print_detailed(arvore);
    printf("\n");
}

int tree_no_height(const Tree* arvore, tipo_tree elemento) {    // Retorna a altura de um nó específico, se ele existir
    if (tree_is_empty(arvore))
        return -1;
    No_tree* p = arvore->T;
    while (p != NULL) {
        int comp = number_comparation(elemento, p->E);
        if (comp == 0)
            break;
        else if (comp < 0)
            p = p->Esq;
        else
            p = p->Dir;
    }
    if (p == NULL)
        return -1;
        
    return height_no_tree(p);
}

int tree_height(const Tree* arvore) {    // Retorna a altura da árvore
    if (tree_is_empty(arvore))
        return -1;
    return height_no_tree(arvore->T);
}

tipo_tree* tree_to_cvet(const Tree* arvore) {  // retorna todos os elementos da árvore em um vetor de tamanho arvore->size
    if (tree_is_empty(arvore))
        return NULL;
    tipo_tree* vet = (tipo_tree*) malloc(arvore->size * sizeof(tipo_tree));
    if (vet == NULL)
        return NULL;
    int i = 0;
    cvet_from_all_no_tree(arvore->T, vet, &i);
    return vet;
}




/* Funções auxiliares usando apenas No_tree */
static bool insert_no_tree(No_tree** T, tipo_tree elemento) {   // Insere o elemento na árvore
    if (*T == NULL) {
        No_tree* p = (No_tree*) malloc(sizeof(No_tree));
        if (p == NULL)
            return false;
        p->E = elemento;
        p->Q = 1;
        p->Esq = p->Dir = NULL;
        *T = p;
        return true;
    }
    
    int comp = number_comparation(elemento, (*T)->E);
    if (comp == 0) {
        (*T)->Q++;
        return true;   
    }
    else if (comp < 0)
        return insert_no_tree(&((*T)->Esq), elemento);
    else
        return insert_no_tree(&((*T)->Dir), elemento);
    
}

static void free_no_tree(No_tree** X) {   // Desaloca o nó específico passado como parâmetro
    No_tree* Antigo = *X;
    if ((*X)->Esq == NULL)
        *X = (*X)->Dir;
    else {
        No_tree** M = &((*X)->Esq);
        while ((*M)->Dir != NULL)
            M = &((*M)->Dir);
        No_tree * Mrem = *M;
	*M = (*M)->Esq;
	*X = Mrem;
	Mrem->Esq = Antigo->Esq;
	Mrem->Dir = Antigo->Dir;
    }
    free(Antigo);
}

static void free_all_no_tree(No_tree** T) {  // Libera a memória de todos os nós.
    if (*T != NULL) {
        free_all_no_tree(&((*T)->Esq));
        free_all_no_tree(&((*T)->Dir));
        (*T)->Esq = (*T)->Dir = NULL;
        free(*T);
        *T = NULL;
    }
}
static void to_string_all_no_tree(No_tree* T, String* cadeia) {  // Retorna no segundo parâmetro uma representação dos nós como String de forma básica
    if (T != NULL) {
        to_string_all_no_tree(T->Esq, cadeia);
        for (int i = 1; i <= T->Q; i++) {
            string_append(cadeia, '[');
        
            String aux = TO_STRING_TREE(T->E);
            string_concat(cadeia, &aux);   // Assumo que sempre funcionará
            string_free(&aux);
        
            string_concat_cstr(cadeia, "] ");
        }
        to_string_all_no_tree(T->Dir, cadeia);
    }
}
static void to_string_all_detailed_no_tree(No_tree* T, String* cadeia) {  // Retorna no segundo parâmetro uma representação dos nós como String de forma detalhada
    if (T != NULL) {
        String aux_raiz;
        String aux_esq;
        String aux_dir;
        String aux_q;
        
        aux_raiz = TO_STRING_TREE(T->E);
        aux_esq = T->Esq != NULL ? TO_STRING_TREE(T->Esq->E) : string_new_with_cstr("NULL");
        aux_dir = T->Dir != NULL ? TO_STRING_TREE(T->Dir->E) : string_new_with_cstr("NULL");
        aux_q = string_from_int(T->Q);
            
        /* Assumo que sempre funcionará */
        string_concat_cstr(cadeia, "No ");
        string_concat(cadeia, &aux_raiz);
        string_concat_cstr(cadeia, " ->  Esq: ");
        string_concat(cadeia, &aux_esq);
        string_concat_cstr(cadeia, "  ;  Dir: ");
        string_concat(cadeia, &aux_dir);
        string_concat_cstr(cadeia, "  ;  Q: ");
        string_concat(cadeia, &aux_q);
        string_concat_cstr(cadeia, "\n\n");
            
        string_free(&aux_raiz);
        string_free(&aux_esq);
        string_free(&aux_dir);
        string_free(&aux_q);
        /* Assumo que sempre funcionará */
        
        
        to_string_all_detailed_no_tree(T->Esq, cadeia);
        to_string_all_detailed_no_tree(T->Dir, cadeia);
    }
}

static int height_no_tree(No_tree* p) {  // retorna a altura de um determinado nó da árvore árvore, se existente
    if (p == NULL)
          return -1;
    int alt_esq = height_no_tree(p->Esq);
    int alt_dir = height_no_tree(p->Dir);
    if (alt_esq > alt_dir)
        return alt_esq + 1;
    else
        return alt_dir + 1;
}

static void cvet_from_all_no_tree(No_tree* T, tipo_tree* array, int* i) {  // Retorna um vetor da linguagem C no segundo parâmetro com todos os elementos da árvore  
    if (T != NULL) {
        cvet_from_all_no_tree(T->Esq, array, i);   
        for (int j = 1; j <= T->Q; j++) {    
            array[*i] = T->E;  
            (*i)++;
        }
        cvet_from_all_no_tree(T->Dir, array, i);
    }
}

/* Funções auxiliares usando apenas No_tree */
