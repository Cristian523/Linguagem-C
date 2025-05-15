#ifndef ENCADEADA_H
#define ENCADEADA_H

typedef int tipo;             // Quando quiser mudar o tipo mude aqui
#define TIPO_FORMATO "%d"     // Quando quiser mudar o formato mude aqui

typedef struct No {
	tipo E;
	struct No * Prox;
} No;

void Imprimir(No*);
bool Insere(No**, tipo);
bool Insere_Final(No**, tipo);
bool Insere_Final_F(No**, tipo, No**); // Cuidado com isso na hora de remover um elemento ou excluir a lista! (não está 100% ajustado)
bool Insere_Ordenado(No**, tipo);
bool Remove(No**, tipo);
void Excluir_Lista(No**);
No* Busca(No*, tipo);   
int Tamanho(No*);

#endif
