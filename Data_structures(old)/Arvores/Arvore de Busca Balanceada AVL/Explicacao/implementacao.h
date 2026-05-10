#ifndef IMPLEMENTACAO_H
#define IMPLEMENTACAO_H

typedef struct No {
	int E;
	int altura;
	struct No* Esq;
	struct No* Dir;
} No;

/* Funções auxiliares para Inserção e Remoção */
int alt_NO(No*);
int fatorBalanceamento(No*);
int maior(int, int);
void RotacaoLL(No**);
void RotacaoRR(No**);
void RotacaoLR(No**);
void RotacaoRL(No**);
No * ProcuraMenor(No*);
/* Funções auxiliares para Inserção e Remoção */


/* Inserção e Remoção */
int Insere_AVL(No**, int);
int Remove_AVL(No**, int);
/* Inserção e Remoção */



/* Funções de árvores de busca comum */
void ImprimirArvore_Detalhada(No*);
void Destroi(No**);
/* Funções de árvores de busca comum */
#endif
