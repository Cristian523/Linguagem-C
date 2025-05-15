#ifndef FILA_H
#define FILA_H

typedef int tipo;

typedef struct No {
	int E;
	struct No * Prox;
} No;

typedef struct Fila {
	No * Inicio;
	No * Fim;
	int N;
} Fila;

/* Funções para Fila */
void Constroi_Fila(Fila *);
bool Enfileira(Fila *, tipo *);    
bool Desenfileira(Fila *, tipo *);
bool Proximo(Fila *, tipo *);
int Tamanho_Fila(Fila *);
/* Funções para Fila */
#endif
