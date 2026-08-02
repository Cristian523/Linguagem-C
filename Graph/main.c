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
    Graph grafo = graph_new();
    
    graph_add_vertex(&grafo, "u");
    graph_add_vertex(&grafo, "v");
    graph_add_vertex(&grafo, "w");
    graph_add_vertex(&grafo, "x");
    graph_add_vertex(&grafo, "y");
    graph_add_vertex(&grafo, "z");
    
    graph_add_edge_weight_direction(&grafo, "u", "v", 0, true);
    graph_add_edge_weight_direction(&grafo, "u", "x", 0, true);
    graph_add_edge_weight_direction(&grafo, "v", "y", 0, true);
    graph_add_edge_weight_direction(&grafo, "w", "y", 0, true);
    graph_add_edge_weight_direction(&grafo, "w", "z", 0, true);
    graph_add_edge_weight_direction(&grafo, "x", "v", 0, true);
    graph_add_edge_weight_direction(&grafo, "y", "x", 0, true);
    graph_add_edge_weight_direction(&grafo, "z", "z", 0, true);
 
    
    dfs(&grafo); 
    
    graph_free(&grafo);
    
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
