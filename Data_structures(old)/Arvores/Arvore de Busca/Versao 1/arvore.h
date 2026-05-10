#ifndef ARVORE_H
#define ARVORE_H

typedef struct No {
	int E;	
	struct No * Esq;
	struct No * Dir;
} No;

// Observação: as funções aqui implantadas são para árvores de busca.

int Numero_Elementos(No*);
void Insere(No**, int); // Insere apenas elementos que não estão na árvore (sem repetição). 
No* Busca(No*, int);  
void Destroi(No**);
void ImprimirArvore(No*);
void ImprimirArvore_Detalhada(No*);  // Não fui eu quem fiz! Foi o ChatGPT.
void RemoveNo(No**);  // Não fui eu quem fiz!
void Remove(No**, int);   // Não fui eu quem fiz! Só remove se o nó estiver existente.

#endif
