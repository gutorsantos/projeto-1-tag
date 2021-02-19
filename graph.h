typedef struct{
    int numVertices;
    struct Node **adjLists;
} Graph;

typedef struct {
    int vertex;
    struct Node *next;
} Node;

Node* createNode(int v) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = v;
    newNode ->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = (Node*) malloc(vertices * sizeof(Node*));
    
    int i;
    for(i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }

    return graph;
    
}

void addEdge(Graph* graph, int v, int w) {
    Node* newNode = createNode(w);
    newNode->next = (Node*) graph->adjLists[v];

    newNode = createNode(v);
    newNode->next = graph->adjLists[w];
    graph->adjLists[w] = newNode;
}

void printGraph(Graph* graph) {
  int v;
  for (v = 0; v < graph->numVertices; v++) {
    Node* temp = graph->adjLists[v];
    printf("\n%d: ", v);
    while (temp) {
      printf("%d -> ", temp->vertex);
      temp = temp->next;
    }
    printf("\n");
  }
}

int isGraphEmpty(Graph* graph) {
    int vertices = graph->numVertices;

    int i;
    for(i = 0; i < vertices; i++) {
        if(graph->adjLists[i] != NULL){
            return 0;
        }
    }

    return 1;
}

void destroyGraph(Graph* graph) {
    int vertices = graph->numVertices;

    int i;
    for(i = 0; i < vertices; i++) {
        Node* n = graph->adjLists[i];
        while(n != NULL){
            Node* temp = n->next;
            free(n);
            n = temp;
        }
    }

    free(graph);
}
