/** Projeto 1 - TAG TA
 * Autor: Gustavo Rodrigues dos Santos 
 * Matricula: 19/0014121
 * Materia: Teoria e Aplicaçao de Grafos - Turma A
 * Ano: 2020 - 2o semestre 
 * Data: 04/03/2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "graph.h"
#include "file.h"
#include "bron-kerbosch.h"

int main() {
    Graph* graph = createGraph(63);
    int a, b;

    // Le os dados do arquivo e adiciona ao grafo
    FILE* file = readFile();
    while(fscanf(file, "%d %d", &a, &b) != EOF) {
        addEdge(graph, a, b);
    }
    closeFile(file);        // fecha o arquivo

    /* 
    printf("Lista de Adjacencia do Grafo");
    printGraph(graph);*/

    printf("+ Bron-Kerbosch sem pivotamento");
    findingCliques(graph, 0);
    printf("\n\n");
    printf("+ Bron-Kerbosch com pivotamento");
    findingCliques(graph, 1);

    printf("\n\n");
    printf("\nCoeficiente de Aglomeracao do Grafo: %lf",clusteringCoefficient(graph));

    printf("\n\n");
    destroyGraph(graph);
    return 0;
}