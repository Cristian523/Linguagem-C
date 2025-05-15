#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arvoreAVL.h"

/* Funções auxiliares para Inserção e Remoção */
int alt_NO(No * Tlin) {
	if (Tlin == NULL)
		return -1;
	else
		return Tlin->altura;
}

int fatorBalanceamento(No * Tlin) {
	return labs(alt_NO(Tlin->Esq) - alt_NO(Tlin->Dir));
}

int maior(int x, int y) {
	if (x > y)
		return x;
	else
		return y;
}

No * ProcuraMenor(No * atual) {
	No* no1 = atual;
	No* no2 = atual->Esq;
	while (no2 != NULL) {
		no1 = no2;
		no2 = no2->Esq;
	}
	return no1;
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

void RotacaoRR(No** raiz) {
	No * no;
	no = (*raiz)->Dir;
	(*raiz)->Dir = no->Esq;
	no->Esq = *raiz;
	
	(*raiz)->altura = maior(alt_NO((*raiz)->Esq), alt_NO((*raiz)->Dir)) + 1;
	no->altura = maior(alt_NO(no->Esq), alt_NO(no->Dir)) + 1;

	*raiz = no;
}

void RotacaoLR(No** raiz) {
	RotacaoRR(&((*raiz)->Esq));
	RotacaoLL(raiz);
}

void RotacaoRL(No** raiz) {
	RotacaoLL(&((*raiz)->Dir));
	RotacaoRR(raiz);
} 
/* Funções auxiliares para Inserção e Remoção */



/* Inserção e Remoção */
bool Insere_AVL(No ** raiz, int valor) {
	bool res;
	if (*raiz == NULL) {
		No * novo = (No * )malloc(sizeof(No));
		if (novo == NULL)
			return false;
		novo->E = valor;
		novo->altura = 0;
		novo->Esq = NULL; novo->Dir = NULL;
		*raiz = novo;
		return true;
	}
	
	if (valor < (*raiz)->E) {
		res = Insere_AVL(&((*raiz)->Esq), valor);
		if (res) {
			if (fatorBalanceamento(*raiz) >= 2) {
				if (valor < (*raiz)->Esq->E)
					RotacaoLL(raiz);
		 		else
		 			RotacaoLR(raiz);
			}
		}
	}
	else {
		if (valor > (*raiz)->E) {
			res = Insere_AVL(&((*raiz)->Dir), valor);
			if (res) {
				if (fatorBalanceamento(*raiz) >= 2) {
					if (valor > (*raiz)->Dir->E)
						RotacaoRR(raiz);
					else
						RotacaoRL(raiz);
				
				}
			}
	
		}
		else {
			printf("Já existe esse valor na árvore!\n");
			return false;
		}
	}
	
	(*raiz)->altura = maior(alt_NO((*raiz)->Esq), alt_NO((*raiz)->Dir)) + 1;
	return res;
	
}

bool Remove_AVL(No ** raiz, int valor) {
	bool res;
	if ((*raiz) == NULL) {
		printf("Elemento não encontrado!!\n");
		return false;
	}
	
	if (valor < (*raiz)->E) {
		res = Remove_AVL(&((*raiz)->Esq), valor);
		if (res) {
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
		res = Remove_AVL(&((*raiz)->Dir), valor);
		if (res) {
			(*raiz)->altura = maior(alt_NO((*raiz)->Esq), alt_NO((*raiz)->Dir)) + 1;   /* Atente-se aqui */
			
			if (fatorBalanceamento(*raiz) >= 2) {	
				if (alt_NO((*raiz)->Esq->Dir) <= alt_NO((*raiz)->Esq->Esq))
					RotacaoLL(raiz);
				else
					RotacaoLR(raiz);
			}
		}
	}
	
	if (valor == (*raiz)->E) {
		if (((*raiz)->Esq == NULL || (*raiz)->Dir == NULL)) {    // Verificando se um dos filhos é NULL pelo menos.
			No * AntigoNO = *raiz;
			if ((*raiz)->Esq != NULL)
				*raiz = (*raiz)->Esq;
			else
				*raiz = (*raiz)->Dir;
			free(AntigoNO);	
		}
		
		else {   // Então  *raiz  tem dois filhos!
			No * temp = ProcuraMenor((*raiz)->Dir);   // Procurando o menor nó de (*raiz)->Dir, que está a sua esquerda!
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




/* Funções de árvore de busca comum */
void ImprimirArvore_Ordenado(No * T) {
	if (T != NULL) {
		ImprimirArvore_Ordenado(T->Esq);
		printf("%d\n", T->E); 
		ImprimirArvore_Ordenado(T->Dir);
	}
}

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

No * Busca(No * T, int x) {
	while (T != NULL && T->E != x) {
		if (x < T->E)
			T = T->Esq;
		else
			T = T->Dir;
	}
	return T;
}

int NumeroElementos(No * T) {
	if (T == NULL)
		return 0;
	else {
		int e = NumeroElementos(T->Esq);
		int d = NumeroElementos(T->Dir);
		return (e + d + 1);
	}
}
/* Funções de árvore de busca comum */



