#include <stdio.h>
#include <stdlib.h>
#include "implementacao.h"

/* Funções auxiliares para Inserção e Remoção */
int alt_NO(No * Tlin) {
	if (Tlin == NULL)
		return -1;
	else
		return Tlin->altura;
}

int fatorBalanceamento(No* Tlin) {
	return labs(alt_NO(Tlin->Esq) - alt_NO(Tlin->Dir)); 
}

int maior(int x, int y) {
	if (x > y)
		return x;
	else
		return y;
}

void RotacaoLL(No ** raiz) {
	No * no;
	no = (*raiz)->Esq;
	(*raiz)->Esq = no->Dir;
	no->Dir = *raiz;
	
	(*raiz)->altura = maior(alt_NO((*raiz)->Esq), alt_NO((*raiz)->Dir)) + 1;
	
	no->altura = maior(alt_NO(no->Esq), alt_NO(no->Dir)) + 1;   
	
	*raiz = no;
}

void RotacaoRR(No ** raiz) {
	No* no;
	no = (*raiz)->Dir;
	(*raiz)->Dir = no->Esq;
	no->Esq = *raiz;
	
	(*raiz)->altura = maior(alt_NO((*raiz)->Esq), alt_NO((*raiz)->Dir)) + 1;
	
	no->altura = maior(alt_NO(no->Esq), alt_NO(no->Dir)) + 1;	
	
	*raiz = no;
}

void RotacaoLR(No ** raiz) {
	RotacaoRR(&(*raiz)->Esq);
	RotacaoLL(raiz);
}

void RotacaoRL(No ** raiz) {
	RotacaoLL(&(*raiz)->Dir);
	RotacaoRR(raiz);
}

No * ProcuraMenor(No* atual) {    // Procura pelo nó mais à esquerda
	No * no1 = atual;
	No * no2 = atual->Esq;
	while (no2 != NULL) {
		no1 = no2;
		no2 = no2->Esq;
	} 
	return no1;
} 
/* Funções auxiliares para Inserção e Remoção */



/* Inserção e Remoção */
int Insere_AVL(No** raiz, int valor) {
	int res;
	if (*raiz == NULL) {
		No* novo =(No*)malloc(sizeof(No));
		if (novo == NULL)  
			return 0; 
		novo->E = valor;
		novo->altura = 0;
		novo->Esq = NULL;
		novo->Dir = NULL;
		*raiz = novo;
	    return 1;
	}
	No * atual = *raiz;
	if (valor < atual->E) {
		if (res = Insere_AVL(&(atual->Esq), valor) == 1) {  // Inserindo ao lado esquerdo e verificando se deu certo!
			if (fatorBalanceamento(atual) >= 2) {
				if (valor < (*raiz)->Esq->E) 
					RotacaoLL(raiz);
				else
					RotacaoLR(raiz);
			}
		}
	}
	else {
		if (valor > atual->E) {
			if (res = Insere_AVL(&(atual->Dir), valor) == 1) {   // Inserindo ao lado direito e verificando se deu certo!
				if (fatorBalanceamento(atual) >= 2) {
					if (valor > (*raiz)->Dir->E) 
						RotacaoRR(raiz);
					else
						RotacaoRL(raiz);
				}
			}
		}
		else {
			printf("Valor duplicado!\n");
			return 0;
		} 
	}	
	atual->altura = maior(alt_NO(atual->Esq), alt_NO(atual->Dir)) + 1;
	return res;
}

int Remove_AVL(No** raiz, int valor) {
	if (*raiz == NULL) {
		printf("Valor não existe!!\n");
		return 0;
	} 
	int res;
	if (valor < (*raiz)->E) {
		if ((res = Remove_AVL(&((*raiz)->Esq), valor)) == 1) {
			 (*raiz)->altura = maior(alt_NO((*raiz)->Esq), alt_NO((*raiz)->Dir)) + 1;   /* Atente-se aqui */
			
			if (fatorBalanceamento(*raiz) >= 2) {
				if (alt_NO((*raiz)->Dir->Esq) <= alt_NO((*raiz)->Dir->Dir))
					RotacaoRR(raiz);
				else
					RotacaoRL(raiz);
			}
	
		}
	}
	if (valor > (*raiz)->E) {
		if ((res = Remove_AVL(&((*raiz)->Dir), valor)) == 1) {
			(*raiz)->altura = maior(alt_NO((*raiz)->Esq), alt_NO((*raiz)->Dir)) + 1;   /* Atente-se aqui */
			
			if (fatorBalanceamento(*raiz) >= 2) {
		 		if (alt_NO((*raiz)->Esq->Dir) <= alt_NO((*raiz)->Esq->Esq)) 
					RotacaoLL(raiz);
				else
					RotacaoLR(raiz);
			}
		}
	}
	if ((*raiz)->E == valor) {
		if (((*raiz)->Esq == NULL || (*raiz)->Dir == NULL)) {   // Situação em que tem apenas 1 filho ou nenhum filho!
			No * NoAntigo = *raiz;
			if ((*raiz)->Esq != NULL)                              
				*raiz = (*raiz)->Esq;
			else
				*raiz = (*raiz)->Dir;
			free(NoAntigo); 
		}
		else {      // Situação em que tem 2 filhos!
			No* temp = ProcuraMenor((*raiz)->Dir);  // Procura o menor nó a direita de *raiz, que é o nó mais a esquerda de (*raiz)->Dir.
			(*raiz)->E = temp->E;
			Remove_AVL(&((*raiz)->Dir), (*raiz)->E);   // Remove o nó maid a direita de (*raiz), pois agora tem dois nós iguais!
			if (fatorBalanceamento(*raiz) >= 2) {
				if (alt_NO((*raiz)->Esq->Dir) <= alt_NO((*raiz)->Esq->Esq))
					RotacaoLL(raiz);
				else
					RotacaoLR(raiz);
			}
		}
		return 1;
	}
	return res;
}
/* Inserção e Remoção */



/* Funções de árvores de busca comum */
void ImprimirArvore_Detalhada(No *T) {   
    if (T != NULL) {
        if (T->Esq != NULL)
            printf("No %d -> Esquerdo: %d ;     Altura : %d\n", T->E, T->Esq->E, T->altura);
        else
            printf("No %d -> Esquerdo: NULL ;     Altura : %d\n", T->E, T->altura);
        
        if (T->Dir != NULL)
            printf("No %d -> Direito: %d ;      Altura : %d\n", T->E, T->Dir->E, T->altura);
        else
            printf("No %d -> Direito: NULL ;      Altura : %d\n", T->E, T->altura);
        
        // Recursão nos filhos
        ImprimirArvore_Detalhada(T->Esq);
        ImprimirArvore_Detalhada(T->Dir);
    }
}

void Destroi(No ** T) {
	if (*T != NULL) {
		Destroi(&((*T)->Esq));	
		Destroi(&((*T)->Dir));	
		(*T)->Esq = NULL; (*T)->Dir = NULL;
		free(*T);
		*T = NULL;
	}
}
/* Funções de árvores de busca comum */

