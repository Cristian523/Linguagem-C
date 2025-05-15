#ifndef PILHA_H
#define PILHA_H

typedef int tipo;

typedef struct No {
	tipo E;
	struct No * Prox;
} No;

typedef struct Pilha {
	No * Topo;
	int N;
} Pilha;

/* Funções da Pilha */
void Constroi_Pilha(Pilha *);
bool Empilha(Pilha *, tipo *);       
bool Desempilha(Pilha *, tipo *);  
bool Topo(Pilha *, tipo *);        
int Tamanho_Pilha(Pilha *);
/* Funções da Pilha */

#endif
