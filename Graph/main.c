#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "data_structures.h"
#include "auxiliares.h"
#include "graph.h"
#define BOOL(x) ((x) ? "true" : "false")

static Graph grafo_casinha();
static void imprimir_grau_min_max(const Graph*);
static void imprimir_grafo(const Graph*);

int main() {
    
    /*
    Graph g = graph_path(4);
    Graph g_ao_quadrado = graph_square(&g);
    
    graph_println_alternative(&g);
    printf("\n");
    graph_println_alternative(&g_ao_quadrado);
    
    graph_free(&g);
    graph_free(&g_ao_quadrado);
    */
 
    
    
    return 0;
}



static Graph grafo_casinha() {
    Graph grafo = graph_new();
    
    graph_add_vertex(&grafo, "a");
    graph_add_vertex(&grafo, "b");
    graph_add_vertex(&grafo, "c");
    graph_add_vertex(&grafo, "d");
    graph_add_vertex(&grafo, "e");
    
    graph_add_edge(&grafo, "a", "b");
    graph_add_edge(&grafo, "a", "c");
    graph_add_edge(&grafo, "b", "c");
    graph_add_edge(&grafo, "d", "e");
    graph_add_edge(&grafo, "a", "e");
    graph_add_edge(&grafo, "c", "d");
    
    return grafo;
}

static void imprimir_grau_min_max(const Graph* grafo) {
    printf("\nδ = %d  ;  Δ = %d\n", graph_min_degree(grafo), graph_max_degree(grafo));
}

static void imprimir_grafo(const Graph* grafo) {
    printf("\n");
    graph_println(grafo);
    printf("\n");
    graph_println_alternative(grafo);
    printf("\n");
}
