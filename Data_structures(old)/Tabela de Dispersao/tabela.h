#ifndef TABELA_H
#define TABELA_H

typedef int tipo;
#define FORMATO "%d"

typedef struct No {
	tipo E;
	struct No * Prox;
} No;

typedef struct Tabela {
	No** H;
	int M;
	int N;
} Tabela;

/* Funções de Lista Encadeada */
void Imprimir_Lista(No*);
bool Insere_Lista(No**, tipo);
bool Insere_Ordenado_Lista(No**, tipo);
No* Busca_Lista(No*, tipo);
bool Remove_Lista(No**, tipo);
void Excluir_Lista(No**);
/* Funções de Lista Encadeada */


/* Funções de Tabela de Dispersão */
bool Constroi_Tabela(Tabela*, int);
int Dispersao(Tabela, tipo);
bool Insere(Tabela*, tipo);
bool Insere_Ordenado(Tabela*, tipo);
No* Busca(Tabela, tipo);
bool Remove(Tabela*, tipo);
void Excluir_Tabela(Tabela*);
void Imprimir_Tabela(Tabela);
int Tamanho_Tabela(Tabela);
/* Funções de Tabela de Dispersão */

#endif
