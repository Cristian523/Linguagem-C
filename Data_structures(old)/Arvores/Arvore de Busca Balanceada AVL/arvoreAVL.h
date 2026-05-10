#ifndef ARVOREAVL_H
#define ARVOREAVL_H

typedef struct No {
	int E;
	int altura;
	struct No * Esq;
	struct No * Dir;
} No;

/* Funções auxiliares para Inserção e Remoção */
int alt_NO(No*);
int fatorBalanceamento(No*);
int maior(int, int);
No * ProcuraMenor(No*);
void RotacaoLL(No**);
void RotacaoRR(No**);
void RotacaoLR(No**);
void RotacaoRL(No**);
/* Funções auxiliares para Inserção e Remoção */


/* Inserção e Remoção */
bool Insere_AVL(No**, int);
bool Remove_AVL(No**, int);
/* Inserção e Remoção */


/* Funções de árvore de busca comum */
void ImprimirArvore_Ordenado(No*);
void ImprimirArvore_Detalhada(No*);
void Destroi(No**);
No * Busca(No*, int);
int NumeroElementos(No*);
/* Funções de árvore de busca comum */

#endif
