/** Projeto 1 - TAG TA
 * Autor: Gustavo Rodrigues dos Santos 
 * Matricula: 19/0014121
 * Materia: Teoria e Aplicaçao de Grafos - Turma A
 * Ano: 2021 - 1o semestre
 * Data: 04/03/2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "graph.h"
#include "file.h"
#include "bron-kerbosch.h"
int main() {
    Graph* graph = createGraph(62);
    int a, b;
    // Le os dados do arquivo e adiciona ao grafo
    FILE* file = readFile();
    while(fscanf(file, "%d %d", &a, &b) != EOF) {
        addEdge(graph, a, b);
    }
    closeFile(file);        // fecha o arquivo

    bronKerbosch(graph, 2);
    
    //printGraph(graph);

    destroyGraph(graph);
    return 0;
}