#ifndef ARVORE_H
#define ARVORE_H

typedef struct No {
	int E;
	struct No * Esq;
	struct No * Dir;
} No;

/* Funções para árvore de busca */
void DesalocarNo(No**);
bool Insere(No**, int);
No * Busca(No*, int);
bool Remove(No**, int);
void Destroi(No**);
void ImprimirArvore_Ordenado(No*);
void ImprimirArvore_Detalhada(No*);
int NumeroElementos(No*);
int Altura(No*);
/* Funções para árvore de busca */

#endif
