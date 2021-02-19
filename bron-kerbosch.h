int bronKerbosch(Graph* graph, int pivot) {
    
    Node* temp = graph->adjLists[pivot];
    printf("Conjunto P={");
    while (temp) {
        
        printf("%d, ", temp->vertex);
        temp = temp->next;
    }
    printf("}");
}