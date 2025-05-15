#ifndef FILAS_H
#define FILAS_H

typedef int tipo;   // Se quiser mudar o tipo, mude aqui.


typedef struct No {
	tipo E;
	struct No * Prox;
} No;


typedef struct Fila {
	No * Inicio;
	No * Fim;
	int N;
} Fila;

void Constroi_Fila(Fila *);
void Enfileira(Fila *, tipo);
tipo Desenfileira(Fila *);
tipo Proximo(Fila *);
int Tamanho_Fila(Fila *);

#endif
