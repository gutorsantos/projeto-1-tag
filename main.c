#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "file.h"
/**
 * Autor: Gustavo Rodrigues dos Santos 
 * Matricula: 19/0014121
 * Materia: Teoria e Aplicaçao de Grafos - Turma A
 * Ano: 2021 - 1o semestre
 * Data: 04/03/2021
 */

int main() {/*
    readFile();
    */
    Graph* graph = createGraph(4);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 0, 3);
    addEdge(graph, 0, 3);
    addEdge(graph, 1, 2);/*
    addEdge(graph, 1, 0);
    addEdge(graph, 2, 0);
    addEdge(graph, 3, 0);*/

    printGraph(graph);

    destroyGraph(graph);
    return 0;
}