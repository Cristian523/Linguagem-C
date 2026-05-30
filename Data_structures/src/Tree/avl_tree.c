#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "c_string.h"
#include "avl_tree.h"


/* Funções auxiliares para Inserção e Remoção de nó's */
static int alt_NO(No_avl_tree*);   // Retorna a altura do atual nó
static int fatorBalanceamento(No_avl_tree*);    // Retorna um inteiro a depender de como estar o balanceamento
static int maior(int, int);     // Retorna qual é o maior inteiro entre os dois passados por parâmetro
static No_avl_tree * ProcuraMenor(No_avl_tree*);  // Procura o menor nó, isto é, o nó mais à esquerda
static void RotacaoLL(No_avl_tree**);    // Rotação esquerda-esquerda
static void RotacaoRR(No_avl_tree**);    // Rotação direita-direita
static void RotacaoLR(No_avl_tree**);    // Rotação esquerda-direita
static void RotacaoRL(No_avl_tree**);    // Rotação direita-esquerda
/* Funções auxiliares para Inserção e Remoção de nó's */

/* Inserção e Remoção */
static bool Insere_AVL(No_avl_tree**, tipo_avl_tree);    // Insere o elemento na árvore
static bool Remove_AVL(No_avl_tree**, tipo_avl_tree);    // Remove o elemento da árvore se existente
/* Inserção e Remoção */

/* Outras funções */
static void free_all_no_tree(No_avl_tree**);  // Libera a memória de todos os nós.
static void to_string_all_no_tree(No_avl_tree*, String*);  // Retorna no segundo parâmetro uma representação dos nós como String de forma básica
static void to_string_all_detailed_no_tree(No_avl_tree*, String*);  // Retorna no segundo parâmetro uma representação dos nós como String de forma detalhada
static void cvet_from_all_no_tree(No_avl_tree*, tipo_avl_tree*, int*);  // Retorna um vetor da linguagem no segundo parâmetro com todos os elementos da árvore 
/* Outras funções */

static int number_comparation(tipo_avl_tree a, tipo_avl_tree b) {     // Comparação enre números
    #if defined(TIPO_AVL_TREE_FLOAT)
        if (fabsf(a - b) < 1e-6f) return 0;
    #elif defined(TIPO_AVL_TREE_DOUBLE) || defined(TIPO_AVL_TREE_DOUBLE_G)
        if (fabs(a - b) < 1e-9) return 0;
    #endif
    
    if (a < b) return -1;
    else if (a > b) return 1;
    else return 0;
}



AvlTree avl_tree_new() {  // Inicializa um tipo AvlTree.
    AvlTree arvore;
    arvore.T = NULL;
    arvore.size = 0;
    return arvore;
}

bool avl_tree_is_empty(const AvlTree* arvore) {   // Verifica se é uma árvore vazia. 
    if (arvore == NULL || arvore->T == NULL || arvore->size <= 0)
        return true;
    return false;
}

int avl_tree_size(const AvlTree* arvore) {   // Retorna o número de elementos da árvore. 
    if (arvore == NULL || arvore->T == NULL)
        return 0;
    return arvore->size;
}

bool avl_tree_insert(AvlTree* arvore, tipo_avl_tree elemento) {  // Insere o elemento do segundo parâmetro se ele não existir na árvore.
    if (arvore == NULL)
        return false;
    if (Insere_AVL(&arvore->T, elemento)) {
        arvore->size++;
        return true;
    }
    return false;
}

bool avl_tree_search(const AvlTree* arvore, tipo_avl_tree elemento) {  // Busca se o elemento do segundo parâmetro está na árvore.
    if (avl_tree_is_empty(arvore))
        return false;
    No_avl_tree* p = arvore->T;
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

bool avl_tree_remove(AvlTree* arvore, tipo_avl_tree elemento) {   // Remove o elemento do terceiro parâmetro se ele estiver presente na árvore.
    if (avl_tree_is_empty(arvore))
        return false;
    if (Remove_AVL(&arvore->T, elemento)) {
        arvore->size--;
        return true;
    }
    return false;
}

void avl_tree_free(AvlTree* arvore) {  // Libera a memória da árvore.
    if (arvore == NULL || arvore->T == NULL)
        return;
    free_all_no_tree(&arvore->T);
    arvore->T = NULL;
    arvore->size = 0;
}

String avl_tree_to_string(const AvlTree* arvore) {   // Retorna uma representação básica dos elementos da árvore como String.
    if (avl_tree_is_empty(arvore))
        return string_new_with_cstr("NULL");
    String cadeia = string_new_with_size(6 * arvore->size);
    if (!string_is_valid(&cadeia))
        return string_new_with_cstr("NULL");
    to_string_all_no_tree(arvore->T, &cadeia);
    string_pop(&cadeia);   // remove o caractere " " adicionado ao final
    return cadeia;
}

String avl_tree_to_string_detailed(const AvlTree* arvore) {  // Retorna uma representação detalhada da árvore como String.
    if (avl_tree_is_empty(arvore))
        return string_new_with_cstr("NULL");
    String cadeia = string_new_with_size(47 * arvore->size);   // Um tamanho bem grande, mas necessário
    if (!string_is_valid(&cadeia))
        return string_new_with_cstr("NULL");
    to_string_all_detailed_no_tree(arvore->T, &cadeia);
    string_pop(&cadeia);   // remove um caractere "\n" adicionado ao final
    return cadeia;
}

void avl_tree_print(const AvlTree* arvore) {   // Imprime a String obtida com a função avl_tree_to_string().
    String cadeia = avl_tree_to_string(arvore);
    string_print(&cadeia);
    string_free(&cadeia);
}

void avl_tree_print_detailed(const AvlTree* arvore) {   // Imprime a String obtida com a função avl_tree_to_string_detailed().
    String cadeia = avl_tree_to_string_detailed(arvore);
    string_print(&cadeia);
    string_free(&cadeia);
}

void avl_tree_println(const AvlTree* arvore) {  // Usa a função avl_tree_print() e imprime o caractere '\n' ao final.
    avl_tree_print(arvore);
    printf("\n");
}

void avl_tree_println_detailed(const AvlTree* arvore) {   // Usa a função avl_tree_print_detailed() e imprime o caractere '\n' ao final.
    avl_tree_print_detailed(arvore);
    printf("\n");
}

int avl_tree_no_height(const AvlTree* arvore, tipo_avl_tree elemento) {   // Retorna a altura de um determinado nó, se existente.
    if (avl_tree_is_empty(arvore))
        return -1;
    No_avl_tree* p = arvore->T;
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
    return p->altura;
}

int avl_tree_height(const AvlTree* arvore) {   // Retorna a altura da árvore
    if (avl_tree_is_empty(arvore))
        return -1;
    return arvore->T->altura;
}

tipo_avl_tree* avl_tree_to_cvet(const AvlTree* arvore) {   // Retorna todos os elementos na árvore em um vetor da linguagem C de tamanho sendo o campo size da árvore
    if (avl_tree_is_empty(arvore))
        return NULL;
    tipo_avl_tree* vet = (tipo_avl_tree*) malloc(arvore->size * sizeof(tipo_avl_tree));
    if (vet == NULL)
        return NULL;
    int i = 0;
    cvet_from_all_no_tree(arvore->T, vet, &i);
    return vet;
}




/* Funções auxiliares para Inserção e Remoção de nó's */
static int alt_NO(No_avl_tree * Tlin) {   // Retorna a altura do atual nó
	if (Tlin == NULL)
		return -1;
	else
		return Tlin->altura;
}

static int fatorBalanceamento(No_avl_tree * Tlin) {    // Retorna um inteiro a depender de como estar o balanceamento
	return labs(alt_NO(Tlin->Esq) - alt_NO(Tlin->Dir));
}

static int maior(int x, int y) {    // Retorna qual é o maior inteiro entre os dois passados por parâmetro
	if (x > y)
		return x;
	else
		return y;
}

static No_avl_tree * ProcuraMenor(No_avl_tree * atual) {   // Procura o menor nó, isto é, o nó mais à esquerda
	No_avl_tree* no1 = atual;
	No_avl_tree* no2 = atual->Esq;
	while (no2 != NULL) {
		no1 = no2;
		no2 = no2->Esq;
	}
	return no1;
}

static void RotacaoLL(No_avl_tree ** raiz) {  // Rotação esquerda-esquerda
	No_avl_tree * no;
	no = (*raiz)->Esq;
	(*raiz)->Esq = no->Dir;
	no->Dir = *raiz;
	
	(*raiz)->altura = maior(alt_NO((*raiz)->Esq), alt_NO((*raiz)->Dir)) + 1;
	no->altura = maior(alt_NO(no->Esq), alt_NO(no->Dir)) + 1;
	
	*raiz = no;
}

static void RotacaoRR(No_avl_tree** raiz) {  // Rotação direita-direita
	No_avl_tree * no;
	no = (*raiz)->Dir;
	(*raiz)->Dir = no->Esq;
	no->Esq = *raiz;
	
	(*raiz)->altura = maior(alt_NO((*raiz)->Esq), alt_NO((*raiz)->Dir)) + 1;
	no->altura = maior(alt_NO(no->Esq), alt_NO(no->Dir)) + 1;

	*raiz = no;
}

static void RotacaoLR(No_avl_tree** raiz) {  // Rotação esquerda-direita
	RotacaoRR(&((*raiz)->Esq));
	RotacaoLL(raiz);
}

static void RotacaoRL(No_avl_tree** raiz) {  // Rotação direita-esquerda
	RotacaoLL(&((*raiz)->Dir));
	RotacaoRR(raiz);
} 
/* Funções auxiliares para Inserção e Remoção de nó's */



/* Inserção e Remoção */
static bool Insere_AVL(No_avl_tree** raiz, tipo_avl_tree valor) {  // Insere o elemento na árvore
        bool res;
	if (*raiz == NULL) {
		No_avl_tree * novo = (No_avl_tree*) malloc(sizeof(No_avl_tree));
		if (novo == NULL)
			return false;
		novo->E = valor;
		novo->Q = 1;
		novo->altura = 0;
		novo->Esq = NULL; novo->Dir = NULL;
		*raiz = novo;
		return true;
	}
	
	if (number_comparation(valor, (*raiz)->E) < 0) {
		res = Insere_AVL(&((*raiz)->Esq), valor);
		if (res) {
			if (fatorBalanceamento(*raiz) >= 2) {
				if (number_comparation(valor, (*raiz)->Esq->E) < 0)
					RotacaoLL(raiz);
		 		else
		 			RotacaoLR(raiz);
			}
		}
	}
	else {
		if (number_comparation(valor, (*raiz)->E) > 0) {
			res = Insere_AVL(&((*raiz)->Dir), valor);
			if (res) {
				if (fatorBalanceamento(*raiz) >= 2) {
					if (number_comparation(valor, (*raiz)->Dir->E) > 0)
						RotacaoRR(raiz);
					else
						RotacaoRL(raiz);
				
				}
			}
	
		}
		else {
			(*raiz)->Q++;
			return true;   
		}
	}
	
	(*raiz)->altura = maior(alt_NO((*raiz)->Esq), alt_NO((*raiz)->Dir)) + 1;
	return res;
	
}

static bool Remove_AVL(No_avl_tree** raiz, tipo_avl_tree valor) {    // Remove o elemento da árvore se existente
        bool res;
	if ((*raiz) == NULL) {
		return false;    // elemento não encontrado
	}
	
	if (number_comparation(valor, (*raiz)->E) < 0) {
		res = Remove_AVL(&((*raiz)->Esq), valor);
		if (res) {
			(*raiz)->altura = maior(alt_NO((*raiz)->Esq), alt_NO((*raiz)->Dir)) + 1;   
			
			if (fatorBalanceamento(*raiz) >= 2) {
				if (alt_NO((*raiz)->Dir->Esq) <= alt_NO((*raiz)->Dir->Dir))
					RotacaoRR(raiz);
				else
					RotacaoRL(raiz);
			}
		}
	}
	
	if (number_comparation(valor, (*raiz)->E) > 0) {
		res = Remove_AVL(&((*raiz)->Dir), valor);
		if (res) {
			(*raiz)->altura = maior(alt_NO((*raiz)->Esq), alt_NO((*raiz)->Dir)) + 1;   
			
			if (fatorBalanceamento(*raiz) >= 2) {	
				if (alt_NO((*raiz)->Esq->Dir) <= alt_NO((*raiz)->Esq->Esq))
					RotacaoLL(raiz);
				else
					RotacaoLR(raiz);
			}
		}
	}
	
	if (number_comparation(valor, (*raiz)->E) == 0) {
		if ((*raiz)->Q > 1) {
		    (*raiz)->Q--;
		    return true;
		}
		
		if (((*raiz)->Esq == NULL || (*raiz)->Dir == NULL)) {    // Verificando se um dos filhos é NULL pelo menos.
			No_avl_tree * AntigoNO = *raiz;
			if ((*raiz)->Esq != NULL)
				*raiz = (*raiz)->Esq;
			else
				*raiz = (*raiz)->Dir;
			free(AntigoNO);	
		}
		
		else {   // Então  *raiz  tem dois filhos!
			No_avl_tree * temp = ProcuraMenor((*raiz)->Dir);   // Procurando o menor nó de (*raiz)->Dir, que está a sua esquerda!
			(*raiz)->E = temp->E;
			Remove_AVL(&((*raiz)->Dir), (*raiz)->E);    // Remover o nó mais a direita, já que há dois nós iguais agora!
			
			if (fatorBalanceamento(*raiz) >= 2) {
				if (alt_NO((*raiz)->Esq->Dir) <= alt_NO((*raiz)->Esq->Esq)) 
					RotacaoLL(raiz);
				else
					RotacaoLR(raiz);
				
			}
		}	
		return true;
	}
	return res;
} 
/* Inserção e Remoção */

/* Outras funções */
static void free_all_no_tree(No_avl_tree** T) {  // Libera a memória de todos os nós.
    if (*T != NULL) {
        free_all_no_tree(&((*T)->Esq));
        free_all_no_tree(&((*T)->Dir));
        (*T)->Esq = (*T)->Dir = NULL;
        free(*T);
        *T = NULL;
    }
}

static void to_string_all_no_tree(No_avl_tree* T, String* cadeia) {  // Retorna no segundo parâmetro uma representação dos nós como String de forma básica
    if (T != NULL) {
        to_string_all_no_tree(T->Esq, cadeia);
        for (int i = 1; i <= T->Q; i++) { 
            string_append(cadeia, '[');
        
            String aux = TO_STRING_AVL_TREE(T->E);
            string_concat(cadeia, &aux);   // Assumo que sempre funcionará
            string_free(&aux);
        
            string_concat_cstr(cadeia, "] ");
        }
        to_string_all_no_tree(T->Dir, cadeia);
    }
}

static void to_string_all_detailed_no_tree(No_avl_tree* T, String* cadeia) {  // Retorna no segundo parâmetro uma representação dos nós como String de forma detalhada
    if (T != NULL) {
        
        String aux_raiz;
        String aux_esq;
        String aux_dir;
        String aux_q;
            
        aux_raiz = TO_STRING_AVL_TREE(T->E);
        aux_esq = T->Esq != NULL ? TO_STRING_AVL_TREE(T->Esq->E) : string_new_with_cstr("NULL");
        aux_dir = T->Dir != NULL ? TO_STRING_AVL_TREE(T->Dir->E) : string_new_with_cstr("NULL");
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
        /* Assumo que sempre funcionará */
            
        string_free(&aux_raiz);
        string_free(&aux_esq);
        string_free(&aux_dir);
        string_free(&aux_q);
        
        
        to_string_all_detailed_no_tree(T->Esq, cadeia);
        to_string_all_detailed_no_tree(T->Dir, cadeia);
    }
}

static void cvet_from_all_no_tree(No_avl_tree* T, tipo_avl_tree* array, int* i) {  // Retorna um vetor da linguagem C no segundo parâmetro com todos os elementos da árvore  
    if (T != NULL) {
        cvet_from_all_no_tree(T->Esq, array, i);   
        for (int j = 1; j <= T->Q; j++) {    
            array[*i] = T->E;  
            (*i)++;
        }
        cvet_from_all_no_tree(T->Dir, array, i);
    }
}
/* Outras funções */

