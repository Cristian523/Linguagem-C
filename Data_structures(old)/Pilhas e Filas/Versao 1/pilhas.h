#ifndef PILHAS_H
#define PILHAS_H

typedef int tipo;  // Se quiser mudar o tipo, mude aqui.


typedef struct No {
	tipo E;
	struct No * Prox;
} No;


typedef struct Pilha {
	No * Topo;
	int N;              
} Pilha;

void Constroi_Pilha(Pilha*);
void Empilha(Pilha*, tipo);
tipo Desempilha(Pilha*);
tipo Topo(Pilha*);
int Tamanho_Pilha(Pilha*);

#endif
