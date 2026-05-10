#ifndef ENCADEADA_H
#define ENCADEADA_H

// Está incompleto!

typedef struct No {
	int E;
	struct No* Prox;
	struct No* Ant;
} No;

bool Insere(No**, int);
void Imprimir_Lista(No*);
void Excluir_Lista(No**);

#endif
