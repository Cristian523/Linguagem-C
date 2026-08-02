#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include "data_structures.h"
#include "auxiliares.h"
#include "graph.h"

static int number_comparation(float a, float b) {   // Comparador entre dois números float
    if (fabsf(a - b) < 1e-6f) 
        return 0;
    else if (a < b) 
        return -1;
    else 
        return 1;
}

static void next_string(String* cadeia, int* i) {   // Função auxiliar para vértices
    String number_str = string_new_empty();
    
    char c = (char) 'a' - 1;
    if (string_is_empty(cadeia)) {
        string_append(cadeia, c);
    }
    c = string_get(cadeia, 0);
    string_clear(cadeia);
    c++;
    if (c < 'a' || c > 'z') {
        (*i)++;
        c = 'a';
    }
    if (*i > 0) {
        string_free(&number_str);
        number_str = string_from_int(*i);
    }
    
    string_append(cadeia, c);
    string_concat(cadeia, &number_str);
    string_free(&number_str);
}





/* Implementação de algoritmos da matéria de otimizações em grafos */

typedef struct DFS {
    String vertice;
    int color;
    int d;   // tempo de descoberta
    int f;   // tempo de término
    String* ant;  // representa o vértice anterior
} DFS;


static void dfs_visit(const Graph* grafo, int* tempo, DFS* vet, DFS* u, const HashTable_sn* tabela) {  // Função recursiva de dfs
    #define WHITE 1
    #define GRAY 2
    #define BLACK 3
    
    *tempo = *tempo + 1;
    u->d = *tempo;
    u->color = GRAY;
    

    Vector_str vizinhos = graph_vertex_neighbors_str(grafo, u->vertice);
    int n = vector_str_size(&vizinhos);

    for (int i = 0; i < n; i++) {
        tipo_value_number aux;
        hash_table_sn_get(tabela, vizinhos.vet[i], &aux);
        int pos_em_vet = aux;
        
        if (vet[pos_em_vet].color == WHITE) {
            vet[pos_em_vet].ant = &(u->vertice);
            dfs_visit(grafo, tempo, vet, &vet[pos_em_vet], tabela);
        }

    }
    vector_str_free(&vizinhos);

    u->color = BLACK;
    *tempo = *tempo + 1;
    u->f = *tempo;

    #undef WHITE
    #undef GRAY
    #undef BLACK
}



static DFS* dfs_auxiliar(const Graph* grafo, int* tempo) {   // função padrão da DFS
    #define WHITE 1

    *tempo = 0;
    
    if (graph_is_empty(grafo))
        return NULL;
    
    int n = graph_vertex_size(grafo);
    DFS* vet = (DFS*) malloc(n * sizeof(DFS));
    HashTable_sn tabela = hash_table_sn_new_with_size(n);

    for (int i = 0; i < n; i++) {   // Inicializando cada vértice
        vet[i].vertice = grafo->vertices.vet[i];     // não uso cópias
        vet[i].color = WHITE;
        vet[i].d = vet[i].f = 0;
        vet[i].ant = NULL;
        hash_table_sn_put(&tabela, vet[i].vertice, i);
    }   

    
    for (int i = 0; i < n; i++) {
        if (vet[i].color == WHITE)
            dfs_visit(grafo, tempo, vet, &vet[i], &tabela);

    }


    #undef WHITE
    
    hash_table_sn_free(&tabela);
    return vet;
}  


void dfs(const Graph* grafo) {
    int tempo = 0;
    if (graph_is_empty(grafo)) {
        printf("\ngrafo vazio!!!\n\n");
        return;
    }

    DFS* vet = dfs_auxiliar(grafo, &tempo);
    int n = graph_vertex_size(grafo);
    
    // Imprimindo o resultado final
    printf("\nTempo total: %d\n", tempo);
    for (int i = 0; i < n; i++)
        printf("\nVertex: %s\nAnt: %s\nd: %d\nf: %d\n\n", string_cstr(&vet[i].vertice), vet[i].ant == NULL ? "NULL" : string_cstr(vet[i].ant), vet[i].d, vet[i].f);
    free(vet);   // Não libero a memória dos campos String pois não foi feito no código uma cópia profunda, o que resultaria em problemas na estrutura do grafo
    

}




Graph graph_square(const Graph* grafo) {     // Retorna o grafo ao quadrado.
    Graph grafo_retorno = graph_new();
    if (graph_is_empty(grafo))
        return grafo_retorno;
    
    Vector_str vertices = graph_get_vertices(grafo);
    int tamanho = vector_str_length(&vertices);
    String aux = string_new_empty();
    
    for (int i = 0; i < tamanho; i++) {   // Mantendo os mesmos vértices do grafo original no novo
        vector_str_at(&vertices, i, &aux);
        graph_add_vertex_str(&grafo_retorno, aux);
    }
    string_free(&aux);
    vector_str_free(&vertices);
    
    
    
    
    
    Vector_edge arestas = graph_get_edges(grafo);
    tamanho = vector_edge_length(&arestas);
    Vector_str vizinhos;
    
    Edge aresta_aux = edge_new_empty();
    String vertice_aux = string_new_empty();
    
    for (int i = 0; i < tamanho; i++) {    // adicionando as mesmas arestas e arestas de distância 2
        vector_edge_at(&arestas, i, &aresta_aux);
        graph_add_edge_edge(&grafo_retorno, aresta_aux);
        
        vizinhos = graph_vertex_neighbors_str(grafo, aresta_aux.v);
        for (int j = 0; j < vector_str_size(&vizinhos); j++) {
            vector_str_at(&vizinhos, j, &vertice_aux);
            if (!string_equals(&vertice_aux, &aresta_aux.u))
                graph_add_edge_str_str(&grafo_retorno, aresta_aux.u, vertice_aux);   // se a aresta já existir
        }
        
        vector_str_free(&vizinhos);
    }
    
    
    string_free(&vertice_aux);
    edge_free(&aresta_aux);
    vector_edge_free(&arestas);
    
    return grafo_retorno;
}

Graph graph_transposed(const Graph* grafo) {    // Retorna um grafo transposto, isto é, com os mesmos vértices, mas as arestas são de direções opostas.
    
    Graph grafo_retorno = graph_new();
    if (graph_is_empty(grafo))
        return grafo_retorno;
    
    Vector_str vertices = graph_get_vertices(grafo);
    int tamanho = vector_str_length(&vertices);
    String aux = string_new_empty();
    
    for (int i = 0; i < tamanho; i++) {   // Mantendo os mesmos vértices do grafo original no novo
        vector_str_at(&vertices, i, &aux);
        graph_add_vertex_str(&grafo_retorno, aux);
    }
    string_free(&aux);
    vector_str_free(&vertices);
    
    
    Vector_edge arestas = graph_get_edges(grafo);
    tamanho = vector_edge_length(&arestas);
    Edge aresta_aux = edge_new_empty();
    
    for (int i = 0; i < tamanho; i++) {    // Mantendo as arestas, mas com as direções opostas
        vector_edge_at(&arestas, i, &aresta_aux);
        if (aresta_aux.direcionado == true) {    // trocando de ordem as arestas
            aux = aresta_aux.u;
            aresta_aux.u = aresta_aux.v;
            aresta_aux.v = aux;
        }
        graph_add_edge_edge(&grafo_retorno, aresta_aux);
    }
    
    
    
    edge_free(&aresta_aux);
    vector_edge_free(&arestas);
    
    return grafo_retorno;
    
}




/* Implementação de algoritmos da matéria de algoritmos em grafos */
// Obs: as funções aqui usaram grafos com arestas sem peso e sem direção.

int graph_min_degree(const Graph* grafo) {   // Retorna o grau mínimo do grafo
    if (graph_is_empty(grafo))
        return -1;
    int deltinha = INT_MAX;
    String aux = string_new_empty();
    for (int i = 0; i < vector_str_size(&grafo->vertices); i++) {
        vector_str_at(&grafo->vertices, i, &aux);
        int grau = graph_vertex_degree_str(grafo, aux);
        if (deltinha > grau)
            deltinha = grau;
    }
    string_free(&aux);
    return deltinha;
}

int graph_max_degree(const Graph* grafo) {   // Retorna o grau máximo do grafo
    if (graph_is_empty(grafo))
        return -1;
    int delta = 0;
    String aux = string_new_empty();
    for (int i = 0; i < vector_str_size(&grafo->vertices); i++) {
        vector_str_at(&grafo->vertices, i, &aux);
        int grau = graph_vertex_degree_str(grafo, aux);
        if (delta < grau)
            delta = grau;
    }
    string_free(&aux);
    return delta;
}

Graph graph_complement(const Graph* grafo) {  // @ Retorna o grafo complementar ao grafo do parâmetro fornecido.
    if (grafo == NULL)
        return graph_new();
    
    int n = graph_vertex_size(grafo);
    Graph complementar = graph_new();
    String aux = string_new_empty();
    String aux2 = string_new_empty();
    
    for (int i = 0; i < n; i++) {   // Copiando os vértices para o grafo complementar
        vector_str_at(&grafo->vertices, i, &aux);
        graph_add_vertex_str(&complementar, aux);
    }
    
    for (int i = 0; i < n - 1; i++) {   // Adicionando arestas no grafo complementar inexistentes do grafo original
        for (int j = i + 1; j < n; j++) {
            vector_str_at(&grafo->vertices, i, &aux);
            vector_str_at(&grafo->vertices, j, &aux2);
            
            if (!graph_contains_edge_n_str_str(grafo, aux, aux2))
                graph_add_edge_str_str(&complementar, aux, aux2);
        }
    }
    string_free(&aux);
    string_free(&aux2);
    return complementar;
}






typedef struct BFS {
        String vertice;
        int color;
        int d;   // representa distância
        String* ant;  // representa o vértice anterior
    } BFS;

static BFS* bfs_auxiliar(const Graph* grafo, const char* a) {    // Busca em largura
    #define WHITE 0
    #define GRAY 1
    #define BLACK 2
    
    if (graph_is_empty(grafo) || !graph_contains_vertex(grafo, a)) 
        return NULL;
    
    
    // OBS: ESSA FUNÇÃO EU ACESSO DIRETAMENTE OS CAMPOS DE VECTOR_STR. COMO EU OUTRAS ESTRUTURAS, NÃO RECOMENDO ESSA PRÁTICA.
    
    int n = graph_vertex_size(grafo);
    HashTable_sn vertice_numero = hash_table_sn_new_with_size(n);
    
    // Inicializando o vetor vet
    BFS* vet = (BFS*) malloc(n * sizeof(BFS));
    
    // Preenchimendo inicial diferente para o vértice passado por parâmetro
    int posicao = vector_str_search_cstr(&grafo->vertices, a);
    vet[posicao].vertice = grafo->vertices.vet[posicao];   // só estou fazendo isso para não usar cópias
    vet[posicao].color = GRAY;
    vet[posicao].d = 0;   
    vet[posicao].ant = NULL;   // só estou fazendo isso para não usar cópias
    hash_table_sn_put(&vertice_numero, vet[posicao].vertice, posicao);
    
    // Demais preenchimento dos vértices
    for (int i = 0; i < n; i++) {
         if (i != posicao) {
              vet[i].vertice = grafo->vertices.vet[i];   // só estou fazendo isso para não usar cópias
              vet[i].color = WHITE;
              vet[i].d = INT_MAX;   // Equivalente a várias implementações quando se usa o símbolo do infinito
              vet[i].ant = NULL;   // só estou fazendo isso para não usar cópias
              hash_table_sn_put(&vertice_numero, vet[i].vertice, i);
         }
    }
    
    // Implementação da BFS:
    Vector_str vizinhos = vector_str_new_with_size(1);
    Queue Q = queue_new();
    queue_enqueue(&Q, posicao);
    
    while (!queue_is_empty(&Q)) {
        vector_str_free(&vizinhos);
        
        tipo_linked_list posicao_retorno;
        queue_dequeue(&Q, &posicao_retorno);
        posicao = posicao_retorno;
        
        vizinhos = graph_vertex_neighbors_str(grafo, vet[posicao].vertice);
        int num_vizinhos = vector_str_length(&vizinhos);
        for (int i = 0; i < num_vizinhos; i++) {   // Vendo os vizinhos do vértice corrente
            tipo_value_number aux;
            hash_table_sn_get(&vertice_numero, vizinhos.vet[i], &aux);
            int posicao_no_grafo = aux;
            
            if (vet[posicao_no_grafo].color == WHITE) {
                vet[posicao_no_grafo].color = GRAY;
                vet[posicao_no_grafo].ant = &vet[posicao].vertice;
                vet[posicao_no_grafo].d = vet[posicao].d + 1;
                
                
                queue_enqueue(&Q, posicao_no_grafo);
            }
        }
        vet[posicao].color = BLACK;
        
    }
    
    vector_str_free(&vizinhos);
    queue_free(&Q);
    hash_table_sn_free(&vertice_numero);

    #undef WHITE
    #undef GRAY
    #undef BLACK
    
    return vet;

}

void bfs(const Graph* grafo, const char* a) {  // Usa o resultado da Busca em largura e imprime-o
    BFS* vet = bfs_auxiliar(grafo, a);
    if (vet == NULL) {
        printf("\nVértice não encontrado\n\n");
        return;
    }
    
    int n = graph_vertex_size(grafo);
    // Imprimindo o resultado final
    for (int i = 0; i < n; i++)
        printf("\nVertex: %s\nd: %d\nAnt: %s\n\n", string_cstr(&vet[i].vertice), vet[i].d, vet[i].ant == NULL ? "NULL" : string_cstr(vet[i].ant));
    free(vet);   // Não libero a memória dos campos String pois não foi feito no código uma cópia profunda, o que resultaria em problemas na estrutura do grafo
}

bool graph_is_connected(const Graph* grafo) {  // Usa o algoritmo de busca em largura para verificar se o grafo é conexo
    if (graph_is_empty(grafo) || graph_edge_size(grafo) < graph_vertex_size(grafo) - 1)
        return false;
    String aux = string_new_empty();
    vector_str_at(&grafo->vertices, 0, &aux);
    BFS* vet = bfs_auxiliar(grafo, string_cstr(&aux));
    string_free(&aux);
    
    int n = graph_vertex_size(grafo);
    for (int i = 0; i < n; i++) {
        if (vet[i].d == INT_MAX) {
            free(vet);
            return false;
        }
    }
    
    free(vet);
    return true;
}

void graph_greedy_coloring(const Graph* grafo) {   // Coloração gulosa de vértices de um grafo
    // OBS: ESSA FUNÇÃO EU ACESSO DIRETAMENTE OS CAMPOS DE VECTOR_STR. COMO EU OUTRAS ESTRUTURAS, NÃO RECOMENDO ESSA PRÁTICA.
    
    if (graph_is_empty(grafo))
        printf("NULL\n");
    else {
        int n = graph_vertex_size(grafo);
        HashTable_sn cores = hash_table_sn_new_with_size(n);
        int grau_max = graph_max_degree(grafo);
        bool* tabela = (bool*) calloc(grau_max + 1, sizeof(bool));   // Sei que o tamanho de bool é apenas 1, mas assim é melhor
        
        // Preenchendo o primeiro vértice com 0 e os demais com um valor menor que 0 para representar que ainda não for colorido
        hash_table_sn_put(&cores, grafo->vertices.vet[0], 0);
        for (int i = 1; i < n; i++)
            hash_table_sn_put(&cores, grafo->vertices.vet[i], -1);
  
        Vector_str vizinhos = vector_str_new_with_size(1);
        
        for (int i = 1; i < n; i++) {
            vector_str_free(&vizinhos);
            vizinhos = graph_vertex_neighbors_str(grafo, grafo->vertices.vet[i]);
                                      
            int m = vector_str_length(&vizinhos);
            tipo_value_number cor_usada;
            for (int j = 0; j < m; j++) {   // Descobrindo as cores usadas e armazenando na tabela de acesso direto
                hash_table_sn_get(&cores, vizinhos.vet[j], &cor_usada);
                if (cor_usada >= 0)
                    tabela[(int) cor_usada] = true;
            }
            
            for (int j = 0; j <= grau_max; j++) {   // Colorindo finalmente o vértice atual
                if (tabela[j] == false) {   // A primeira cor não usada será colocada no vértice atual
                    hash_table_sn_put(&cores, grafo->vertices.vet[i], j);
                    break;
                }
            }
            
            for (int j = 0; j < m; j++) {   // Excluindo os elementos da tabela de acesso direto que foram usados
                hash_table_sn_get(&cores, vizinhos.vet[j], &cor_usada);
                if (cor_usada >= 0)
                    tabela[(int) cor_usada] = false;
            }
        }
        free(tabela);
        hash_table_sn_println(&cores);
        vector_str_free(&vizinhos);
        hash_table_sn_free(&cores);
        
    }
}





Graph graph_complete(int n) {  // Retorna um grafo k-completo.
    if (n <= 0)
        return graph_new();
    
    String vertice = string_new_with_size(3);
    String aux = string_new_empty();
    int k = 0;
    Graph grafo = graph_new();
    
    for (int i = 0; i < n; i++) {   // adicionando vértices
        next_string(&vertice, &k);
        graph_add_vertex_str(&grafo, vertice);
    }
    
    for (int i = 0; i < n - 1; i++) {   // adicionando arestas
        for (int j = i + 1; j < n; j++) {
            vector_str_at(&grafo.vertices, i, &vertice);
            vector_str_at(&grafo.vertices, j, &aux);
            graph_add_edge_str_str(&grafo, vertice, aux);
        }
    }
    
    string_free(&vertice);
    string_free(&aux);
    return grafo;
}

Graph graph_bipartite_complete(int n1, int n2) {  // Retorna um grafo bipartido completo
    if (n1 <= 0 || n2 <= 0)
        return graph_new();
    
    String vertice;
    String aux;
    Graph grafo = graph_new();
    
    for (int i = 1; i <= n1; i++) {  // Adicionando vértices
        aux = string_from_int(i);
        vertice = string_concat_new_cstr_str("u", &aux);
        graph_add_vertex_str(&grafo, vertice);
        string_free(&vertice);
        string_free(&aux);
    }
    
    for (int i = 1; i <= n2; i++) {  // Adicionando vértices
        aux = string_from_int(i);
        vertice = string_concat_new_cstr_str("v", &aux);
        graph_add_vertex_str(&grafo, vertice);
        string_free(&vertice);
        string_free(&aux);
    }
    
    for (int i = 0; i < n1; i++) {   // Adicionando arestas
        for (int j = n1; j < n1 + n2; j++) {
            vector_str_at(&grafo.vertices, i, &vertice);
            vector_str_at(&grafo.vertices, j, &aux);
            graph_add_edge_str_str(&grafo, vertice, aux);
        }
    }
    
    string_free(&vertice);
    string_free(&aux);
    return grafo;
}

Graph graph_path(int n) {   // Retorna um grafo caminho. 
    if (n <= 0)
        return graph_new();
    
    String vertice = string_new_with_size(3);
    String aux = string_new_empty();
    int k = 0;
    Graph grafo = graph_new();
    
    for (int i = 0; i < n; i++) {   // adicionando vértices
        next_string(&vertice, &k);
        graph_add_vertex_str(&grafo, vertice);
    }
    
    for (int i = 0; i < n - 1; i++) {  // adicionando arestas
        vector_str_at(&grafo.vertices, i, &vertice);
        vector_str_at(&grafo.vertices, i + 1, &aux);
        graph_add_edge_str_str(&grafo, vertice, aux);
    }
    
    string_free(&aux);
    string_free(&vertice);
    return grafo;
}

Graph graph_cycle(int n) {  // Retorna um grafo ciclo.
    if (n < 3)
        return graph_new();
        
    String vertice = string_new_with_size(3);
    String aux = string_new_empty();
    int k = 0;
    Graph grafo = graph_new();
    
    for (int i = 0; i < n; i++) {   // adicionando vértices
        next_string(&vertice, &k);
        graph_add_vertex_str(&grafo, vertice);
    }
    
    for (int i = 0; i < n - 1; i++) {  // adicionando arestas
        vector_str_at(&grafo.vertices, i, &vertice);
        vector_str_at(&grafo.vertices, i + 1, &aux);
        graph_add_edge_str_str(&grafo, vertice, aux);
    }
    vector_str_at(&grafo.vertices, 0, &vertice);
    vector_str_at(&grafo.vertices, n - 1, &aux);
    graph_add_edge_str_str(&grafo, vertice, aux);
    
    string_free(&aux);
    string_free(&vertice);
    return grafo;
}

Graph graph_whell(int n) {  // Retorna um grafo roda
    if (n < 3)
        return graph_new();
    
    /* ciclo */
    String vertice = string_new_with_size(3);
    String aux = string_new_empty();
    int k = 0;
    Graph grafo = graph_new();
    
    for (int i = 0; i < n; i++) {   // adicionando vértices
        next_string(&vertice, &k);
        graph_add_vertex_str(&grafo, vertice);
    }
    
    for (int i = 0; i < n - 1; i++) {  // adicionando arestas
        vector_str_at(&grafo.vertices, i, &vertice);
        vector_str_at(&grafo.vertices, i + 1, &aux);
        graph_add_edge_str_str(&grafo, vertice, aux);
    }
    vector_str_at(&grafo.vertices, 0, &vertice);
    vector_str_at(&grafo.vertices, n - 1, &aux);
    graph_add_edge_str_str(&grafo, vertice, aux);
    /* ciclo */
    
    
    next_string(&aux, &k);
    graph_add_vertex_str(&grafo, aux);
    for (int i = 0; i < n; i++) {
        vector_str_at(&grafo.vertices, i, &vertice);
        graph_add_edge_str_str(&grafo, vertice, aux);
    }
    
    string_free(&aux);
    string_free(&vertice);
    return grafo;
}





/* Implementação de algoritmos da matéria de algoritmos em grafos */




/* Funções básicas de grafos */

Graph graph_new() {  // Inicializa um tipo Graph
    Graph grafo;
    grafo.adjacencia = hash_table_sls_new();
    grafo.vertices = vector_str_new();
    grafo.arestas = vector_edge_new();
    grafo.peso_aresta = hash_table_ew_new();
    return grafo;
}

bool graph_is_empty(const Graph* grafo) {  // Verifica se o grafo está vazio
    if (grafo == NULL || vector_str_is_empty(&grafo->vertices))
        return true;
    return false;
}

Vector_str graph_get_vertices(const Graph* grafo) {   // Retorna uma cópia do Vector_str interno de vértices. 
    if (graph_is_empty(grafo))
        return vector_str_new_with_size(1);
    Vector_str vetor = vector_str_new_with_size(1);
    vector_str_copy(&vetor, &grafo->vertices);
    return vetor;
}

Vector_edge graph_get_edges(const Graph* grafo) {  // Retorna uma cópia do Vector_edge interno de arestas. 
    if (graph_is_empty(grafo) || graph_edge_size(grafo) == 0)
        vector_edge_new_with_size(1);
    Vector_edge vetor = vector_edge_new_with_size(1);
    vector_edge_copy(&vetor, &grafo->arestas);
    return vetor;
}

int graph_vertex_degree(const Graph* grafo, const char* vertice) {  // Retorna o grau de um determinado vértice.
    if (graph_is_empty(grafo) || !graph_contains_vertex(grafo, vertice))
        return -1;
    return hash_table_sls_value_size_cstr(&grafo->adjacencia, vertice);
}

int graph_vertex_degree_str(const Graph* grafo, const String vertice) {  // Retorna o grau de um determinado vértice.
    return graph_vertex_degree(grafo, string_cstr(&vertice));
}

Vector_str graph_vertex_neighbors(const Graph* grafo, const char* vertice) {  // Retorna todos os vizinhos de um determinado vértice. 
    if (graph_is_empty(grafo) || !graph_contains_vertex(grafo, vertice))
        return vector_str_new_with_size(1);
    LinkedList_str lista = linked_list_str_new();
    hash_table_sls_get_cstr(&grafo->adjacencia, vertice, &lista);
    linked_list_str_reset(&lista);
    
    Vector_str vetor = vector_str_new_with_size(linked_list_str_size(&lista));
    String aux = string_new_empty();
    if (!linked_list_str_is_empty(&lista)) {
        do {
            linked_list_str_current(&lista, &aux);
            vector_str_append(&vetor, aux);
        } while (linked_list_str_next(&lista));
    }
    linked_list_str_free(&lista);
    string_free(&aux);
    return vetor;
}

Vector_str graph_vertex_neighbors_str(const Graph* grafo, const String vertice) {   // Retorna todos os vizinhos de um determinado vértice. 
    return graph_vertex_neighbors(grafo, string_cstr(&vertice));
}

float graph_get_edge_weight(const Graph* grafo, const char* u, const char* v) {  // Retorna o peso da aresta se estiver presente no grafo.
    if (graph_is_empty(grafo) || u == NULL || v == NULL)
        return -1;
    float peso;
    if (!hash_table_ew_get_cstr_cstr(&grafo->peso_aresta, u, v, &peso))
        return -1;
    return peso;
}

float graph_get_edge_weight_str_str(const Graph* grafo, const String u, const String v) {  // Retorna o peso da aresta se estiver presente no grafo.
    return graph_get_edge_weight(grafo, string_cstr(&u), string_cstr(&v));
}

float graph_get_edge_weight_edge(const Graph* grafo, const Edge aresta) {  // Retorna o peso da aresta se estiver presente no grafo.
    if (graph_is_empty(grafo))
        return -1;
    
    float peso;
    if (!hash_table_ew_get(&grafo->peso_aresta, aresta, &peso))
        return -1;
    return peso;
   
   
}

bool graph_update_edge_weight(Graph* grafo, const char* u, const char* v, float novo_peso) {  // Atualiza o peso de uma aresta do grafo.
    if (graph_is_empty(grafo) || u == NULL || v == NULL)
        return false;
    
    if (!hash_table_ew_contains_key_cstr_cstr(&grafo->peso_aresta, u, v))
        return false;
    Edge aux_aresta = edge_new_cstr_cstr(u, v, 0, false);
    hash_table_ew_put(&grafo->peso_aresta, aux_aresta, novo_peso);
    edge_free(&aux_aresta);
    
    int posicao = vector_edge_search_n_cstr_cstr(&grafo->arestas, u, v);
    grafo->arestas.vet[posicao].peso = novo_peso;
    
    return true;
    
}

bool graph_update_edge_weight_str_str(Graph* grafo, const String u, const String v, float novo_peso) {  // Atualiza o peso de uma aresta do grafo.
    return graph_update_edge_weight(grafo, string_cstr(&u), string_cstr(&v), novo_peso);
}

bool graph_update_edge_weight_edge(Graph* grafo, const Edge aresta, float novo_peso) {  // Atualiza o peso de uma aresta do grafo.
    if (graph_is_empty(grafo))
        return false;
    
    if (!hash_table_ew_contains_key(&grafo->peso_aresta, aresta))
        return false;
    
    hash_table_ew_put(&grafo->peso_aresta, aresta, novo_peso);
    int posicao = vector_edge_search_n(&grafo->arestas, aresta);
    grafo->arestas.vet[posicao].peso = novo_peso;
    
    return true;
}

int graph_vertex_size(const Graph* grafo) {   // @ Retorna o número de vértices do grafo. 
    return grafo != NULL ? vector_str_size(&grafo->vertices) : 0;
}

int graph_edge_size(const Graph* grafo) {  // Retorna o número de arestas do grafo.
    return grafo != NULL ? vector_edge_size(&grafo->arestas) : 0;
}

bool graph_add_vertex(Graph* grafo, const char* vertice) {   // Adiciona um vértice ao grafo. 
    if (grafo == NULL || vertice == NULL || hash_table_sls_contains_key_cstr(&grafo->adjacencia, vertice))
        return false;
    
    String aux = string_new_with_cstr(vertice);
    LinkedList_str list = linked_list_str_new();
    
    hash_table_sls_put_key_value(&grafo->adjacencia, aux, list);
    vector_str_append_cstr(&grafo->vertices, vertice);
    
    string_free(&aux);
    linked_list_str_free(&list);
    return true;
}

bool graph_add_vertex_str(Graph* grafo , const String vertice) {    // Adiciona um vértice ao grafo.
    return graph_add_vertex(grafo, string_cstr(&vertice));
}

bool graph_add_edge(Graph* grafo, const char* u, const char* v) {  // Adiciona uma aresta ao grafo com peso sendo 0 e sem ser direcionado.
    return graph_add_edge_weight_direction(grafo, u, v, 0, false);
}

bool graph_add_edge_str_str(Graph* grafo, const String u, const String v) {  // Adiciona uma aresta ao grafo com peso sendo 0 e sem ser direcionado.
    return graph_add_edge_weight_direction(grafo, string_cstr(&u), string_cstr(&v), 0, false);
}

bool graph_add_edge_edge(Graph* grafo, const Edge aresta) {  // Adiciona uma aresta com o tipo Edge.
    if (grafo == NULL)
        return false;
    else if (!hash_table_sls_contains_key(&grafo->adjacencia, aresta.u) || !hash_table_sls_contains_key(&grafo->adjacencia, aresta.v))
        return false;
    else if (hash_table_ew_contains_key(&grafo->peso_aresta, aresta))
        return false;
    
    hash_table_sls_put_cstr_cstr(&grafo->adjacencia, string_cstr(&aresta.u), string_cstr(&aresta.v));
    if (!aresta.direcionado)    
        hash_table_sls_put_cstr_cstr(&grafo->adjacencia, string_cstr(&aresta.v), string_cstr(&aresta.u));
        
    hash_table_ew_put(&grafo->peso_aresta, aresta, aresta.peso);
    vector_edge_append(&grafo->arestas, aresta);
    return true;
}

bool graph_add_edge_weight_direction(Graph* grafo, const char* u, const char* v, float peso, bool dir) {   // Adiciona uma aresta ao grafo
    if (grafo == NULL || u == NULL || v == NULL)
        return false;
    else if (!hash_table_sls_contains_key_cstr(&grafo->adjacencia, u) || !hash_table_sls_contains_key_cstr(&grafo->adjacencia, v))
        return false;
    else if (hash_table_ew_contains_key_cstr_cstr(&grafo->peso_aresta, u, v) || (!dir && hash_table_ew_contains_key_cstr_cstr(&grafo->peso_aresta, v, u)))
        return false;
        
    if (dir)
        hash_table_sls_put_cstr_cstr(&grafo->adjacencia, u, v);
    else {
        hash_table_sls_put_cstr_cstr(&grafo->adjacencia, u, v);
        hash_table_sls_put_cstr_cstr(&grafo->adjacencia, v, u);
    }
    
    Edge aresta_aux = edge_new_cstr_cstr(u, v, peso, dir);
    hash_table_ew_put(&grafo->peso_aresta, aresta_aux, peso);
    edge_free(&aresta_aux);
    vector_edge_append_cstr_cstr_weight_direction(&grafo->arestas, u, v, peso, dir);
    return true;
}

bool graph_add_edge_str_str_weight_direction(Graph* grafo, const String u, const String v, float peso, bool dir) {  // Adiciona uma aresta ao grafo
    return graph_add_edge_weight_direction(grafo, string_cstr(&u), string_cstr(&v), peso, dir);
}

bool graph_contains_vertex(const Graph* grafo, const char* vertice) {   // Verifica se um dado vértice existe no grafo. 
    if (graph_is_empty(grafo) || vertice == NULL)
        return false;
    return hash_table_sls_contains_key_cstr(&grafo->adjacencia, vertice);
}

bool graph_contains_vertex_str(const Graph* grafo, const String vertice) {  // Verifica se um dado vértice existe no grafo.
    return graph_contains_vertex(grafo, string_cstr(&vertice));
}

bool graph_contains_edge_n(const Graph* grafo, const char* u, const char* v) {  // Verifica se existe a aresta passada no grafo. 
    if (graph_is_empty(grafo) || u == NULL || v == NULL || !hash_table_sls_contains_key_cstr(&grafo->adjacencia, u) || !hash_table_sls_contains_key_cstr(&grafo->adjacencia, v))
        return false;
    return hash_table_ew_contains_key_cstr_cstr(&grafo->peso_aresta, u, v);  
}

bool graph_contains_edge_n_str_str(const Graph* grafo, const String u, const String v) {  // Verifica se existe a aresta passada no grafo. 
    return graph_contains_edge_n(grafo, string_cstr(&u), string_cstr(&v));
}

bool graph_contains_edge_n_edge(const Graph* grafo, const Edge aresta) {   // Verifica se existe a aresta passada no grafo. 
    if (graph_is_empty(grafo))
        return false;
    return hash_table_ew_contains_key(&grafo->peso_aresta, aresta);
}

bool graph_contains_edge_w(const Graph* grafo, float peso) {  // Verifica se existe uma aresta com o peso passado no segundo parâmetro. 
    if (graph_is_empty(grafo))
        return false;
    return vector_edge_search_w_weight(&grafo->arestas, peso) >= 0;
}

bool graph_contains_edge_w_edge(const Graph* grafo, const Edge aresta) {  // Verifica se o peso do tipo Edge passado existe no grafo. 
    return graph_contains_edge_w(grafo, aresta.peso);
}

bool graph_remove_vertex(Graph* grafo, const char* vertice) {  // Remove o vértice do grafo. 
    if (graph_is_empty(grafo) || vertice == NULL || !hash_table_sls_contains_key_cstr(&grafo->adjacencia, vertice))
        return false;
    
    // 1) Removendo na lista de adjacencia o vértice
    int n = vector_str_length(&grafo->vertices);
    String aux = string_new_empty();
    for (int i = 0; i < n; i++) {
        vector_str_at(&grafo->vertices, i, &aux);
        if (string_compare_cstr(&aux, vertice) == 0)
            continue;  // pula o próprio vértice
        
        LinkedList_str lista = linked_list_str_new();
        hash_table_sls_get(&grafo->adjacencia, aux, &lista);
        
        hash_table_sls_remove_cstr_cstr(&grafo->adjacencia, string_cstr(&aux), vertice);
        if (linked_list_str_size(&lista) == 1) {
            LinkedList_str list = linked_list_str_new();
            hash_table_sls_put_key_value(&grafo->adjacencia, aux, list);
            linked_list_str_free(&list);
        }
        
        linked_list_str_free(&lista);
    }
    string_free(&aux);
    hash_table_sls_remove_key_value_cstr(&grafo->adjacencia, vertice);
    
    // 2) Removendo as arestas com esse vértice na extremidade
    Vector_edge arestas = vector_edge_get_edges_of(&grafo->arestas, vertice);
    for (int i = 0; i < vector_edge_length(&arestas); i++) {
        Edge aux_aresta = edge_new_empty();
        vector_edge_at(&arestas, i, &aux_aresta);
        vector_edge_remove_n(&grafo->arestas, aux_aresta);
        hash_table_ew_remove(&grafo->peso_aresta, aux_aresta);
        edge_free(&aux_aresta);
    }
    vector_edge_free(&arestas);
    
    // 3) Removendo o vértice na lista de vértices
    vector_str_remove_cstr(&grafo->vertices, vertice);
    
    return true;
}

bool graph_remove_vertex_str(Graph* grafo, const String vertice) { // Remove o vértice do grafo.
    return graph_remove_vertex(grafo, string_cstr(&vertice));
}

bool graph_remove_edge(Graph* grafo, const char* u, const char* v) {  // Remove uma aresta do grafo.
    if (graph_is_empty(grafo) || !graph_contains_edge_n(grafo, u, v))
        return false;
    
    // 1) Removendo as arestas da lista de adjacência
   
    LinkedList_str lista = linked_list_str_new();
    String aux = string_new_empty();   string_free(&aux);
    
    Edge aresta = edge_new_empty();
    int i = vector_edge_search_n_cstr_cstr(&grafo->arestas, u, v);
    vector_edge_at(&grafo->arestas, i, &aresta);
    
    hash_table_sls_get_cstr(&grafo->adjacencia, u, &lista);
    hash_table_sls_remove_cstr_cstr(&grafo->adjacencia, u, v);
    if (linked_list_str_size(&lista) == 1) {
        LinkedList_str list = linked_list_str_new();
        string_copy_cstr(&aux, u);
        hash_table_sls_put_key_value(&grafo->adjacencia, aux, list);
        linked_list_str_free(&list);
    }
    
    if (!aresta.direcionado) {
        hash_table_sls_get_cstr(&grafo->adjacencia, v, &lista);
        hash_table_sls_remove_cstr_cstr(&grafo->adjacencia, v, u);
        if (linked_list_str_size(&lista) == 1) {
            LinkedList_str list = linked_list_str_new();
            string_copy_cstr(&aux, v);
            hash_table_sls_put_key_value(&grafo->adjacencia, aux, list);
            linked_list_str_free(&list);
        }
    }
    
    string_free(&aux);
    edge_free(&aresta);
    linked_list_str_free(&lista);
    
    
    // 2) Removendo a aresta do Vector de arestas
    vector_edge_remove_n_cstr_cstr(&grafo->arestas, u, v);
    aresta = edge_new_cstr_cstr(u, v, 0, false);
    hash_table_ew_remove(&grafo->peso_aresta, aresta);
    edge_free(&aresta);
    return true;
    
}

bool graph_remove_edge_str_str(Graph* grafo, const String u, const String v) {  // Remove uma aresta do grafo.
    return graph_remove_edge(grafo, string_cstr(&u), string_cstr(&v));
}

bool graph_remove_edge_edge(Graph* grafo, const Edge aresta) {  // Remove uma aresta do grafo.
    if (graph_is_empty(grafo) || !graph_contains_edge_n_edge(grafo, aresta))
        return false;
    
    // 1) Removendo as arestas da lista de adjacência
    LinkedList_str lista = linked_list_str_new();
    String aux = string_new_empty();   string_free(&aux);
    
    Edge aresta_aux = edge_new_empty();
    int i = vector_edge_search_n(&grafo->arestas, aresta);
    vector_edge_at(&grafo->arestas, i, &aresta_aux);
    
    hash_table_sls_get(&grafo->adjacencia, aresta.u, &lista);
    hash_table_sls_remove_cstr_cstr(&grafo->adjacencia, string_cstr(&aresta.u), string_cstr(&aresta.v));
    if (linked_list_str_size(&lista) == 1) {
        LinkedList_str list = linked_list_str_new();
        string_copy_cstr(&aux, string_cstr(&aresta.u));
        hash_table_sls_put_key_value(&grafo->adjacencia, aux, list);
        linked_list_str_free(&list);hash_table_ew_remove(&grafo->peso_aresta, aresta);
    }
    
    if (!aresta_aux.direcionado) {
        hash_table_sls_get(&grafo->adjacencia, aresta.v, &lista);
        hash_table_sls_remove_cstr_cstr(&grafo->adjacencia, string_cstr(&aresta.v), string_cstr(&aresta.u));
        if (linked_list_str_size(&lista) == 1) {
            LinkedList_str list = linked_list_str_new();
            string_copy_cstr(&aux, string_cstr(&aresta.v));
            hash_table_sls_put_key_value(&grafo->adjacencia, aux, list);
            linked_list_str_free(&list);
        }
    }
    
    string_free(&aux);
    edge_free(&aresta_aux);
    linked_list_str_free(&lista);
    
    // 2) Removendo a aresta do Vector de arestas
    vector_edge_remove_n(&grafo->arestas, aresta);
    hash_table_ew_remove(&grafo->peso_aresta, aresta);
    return true;
    
}



void graph_free(Graph* grafo) {  // Libera a memória de um grafo
    if (grafo != NULL) {
        hash_table_sls_free(&grafo->adjacencia);
        hash_table_ew_free(&grafo->peso_aresta);
        vector_str_free(&grafo->vertices);
        vector_edge_free(&grafo->arestas);
    }
}

String graph_to_string(const Graph* grafo) {      // Retorna como String uma representação do grafo. A representação aqui será o Vector_str interno de vértices e o Vector_edge interno de arestas
    if (graph_is_empty(grafo))
        return string_new_with_cstr("EMPTY");
    String cadeia = string_new_with_cstr("Vertices:  ");
    String aux;
    
    Vector_str vector_aux = vector_str_new_with_size(1);
    vector_str_copy(&vector_aux, &grafo->vertices);
    vector_str_sort(&vector_aux);
    
    aux = vector_str_to_string(&vector_aux);
    string_concat(&cadeia, &aux);
    string_free(&aux);
    string_concat_cstr(&cadeia, "\nEdges:  ");
    
    vector_str_free(&vector_aux);
    Vector_edge vector_edge_aux = vector_edge_new_with_size(1);
    vector_edge_copy(&vector_edge_aux, &grafo->arestas);
    vector_edge_sort_n(&vector_edge_aux);
    
    aux = vector_edge_to_string(&vector_edge_aux);
    string_concat(&cadeia, &aux);
    string_free(&aux);
    vector_edge_free(&vector_edge_aux);
     
    return cadeia;
} 



static String linked_list_str_to_string_ordered(const LinkedList_str* list) {
    String cadeia;
    if (list == NULL || list->inicio == NULL)
        return string_new_with_cstr("NULL");
    cadeia = string_new_with_size(6 * list->length + 4);   // um tamanho não muito grande, mas não muito pequeno para uma possível realocação
    String elemento = string_new_empty(); 
    
    if (string_is_valid(&cadeia)) {
        string_append(&cadeia, '[');
        
        No_str* L = list->inicio;
        PriorityQueue_str fila = priority_queue_str_new_with_size(linked_list_str_size(list));
        
        while (L != NULL) {
            priority_queue_str_enqueue(&fila, L->E);
            L = L->Prox;
        }
        
        while (!priority_queue_str_is_empty(&fila)) {
            priority_queue_str_dequeue(&fila, &elemento);
        
            if (!string_is_empty(&elemento)) {
                string_concat(&cadeia, &elemento);
                if (!priority_queue_str_is_empty(&fila))
                    string_concat_cstr(&cadeia, "]->[");
            }
        }
        string_concat_cstr(&cadeia, "]->NULL");
        priority_queue_str_free(&fila);
    }
    else
        cadeia = string_new_with_cstr("NULL");

    string_free(&elemento);
    return cadeia;
}

static String hash_table_sls_to_string_ordered(const HashTable_sls* tabela) {  // Retorna uma representação da tabela como String
    if (hash_table_sls_is_empty(tabela))
        return string_new_with_cstr("EMPTY");
    String cadeia = string_new_with_size(8 * tabela->size);   // Um tamanho razoável para uma possível realocação
    
    if (string_is_valid(&cadeia)) {
        String* pares = hash_table_sls_get_keys(tabela);
        if (pares == NULL) {
            string_free(&cadeia);
            return string_new_with_cstr("EMPTY");
        }
        Vector_str chaves = vector_str_new_with_cvet((const String*) pares, tabela->size);
        for (int i = 0; i < tabela->size; i++) {  // liberando a memória do vetor de chave
            string_free(&pares[i]);
        }
        free(pares);
        vector_str_sort(&chaves);
        
        
        String aux_valor = string_new_empty();
        LinkedList_str valor = linked_list_str_new();
        for (int i = 0; i < tabela->size; i++) {
            string_concat(&cadeia, &chaves.vet[i]);   
            string_concat_cstr(&cadeia, ": ");
            
            hash_table_sls_get(tabela, chaves.vet[i], &valor);
    
            string_free(&aux_valor);  
            aux_valor = linked_list_str_to_string_ordered(&valor);   
            string_concat(&cadeia, &aux_valor);   // assumo que vai sempre funciona
            if (i < tabela->size - 1)
                string_append(&cadeia, '\n');
        }
        string_free(&aux_valor);
        linked_list_str_free(&valor);
        vector_str_free(&chaves);
    }
    else
        cadeia = string_new_with_cstr("EMPTY");
    return cadeia;
}




String graph_to_string_alternative(const Graph* grafo) {  // Retorna como String uma representação do grafo. A representação aqui será a tabela adjacencia interna, isto é, cada vértice e seus respectivos vizinhos
    if (graph_is_empty(grafo))
        return string_new_with_cstr("EMPTY");
    return hash_table_sls_to_string_ordered(&grafo->adjacencia); 
}

void graph_print(const Graph* grafo) {  // Imprime um grafo com a String obtida em graph_to_string()
    String cadeia = graph_to_string(grafo);
    string_print(&cadeia);
    string_free(&cadeia);
}

void graph_println(const Graph* grafo) {  // Usa a função anterior graph_print() e imprime um caractere '\n' ao final.
    graph_print(grafo);
    printf("\n");
}

void graph_print_alternative(const Graph* grafo) {  // Imprime um grafo com a String obtida em graph_to_string_alternative()
    String cadeia = graph_to_string_alternative(grafo);
    string_print(&cadeia);
    string_free(&cadeia);
}

void graph_println_alternative(const Graph* grafo) {   // Usa a função anterior graph_print_alternative() e imprime um caractere '\n' ao final.
    graph_print_alternative(grafo);
    printf("\n");
}

/* Funções básicas de grafos */

