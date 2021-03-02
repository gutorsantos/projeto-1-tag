typedef struct Graph{
    int numVertices;
    struct Node **adjLists;
} Graph;

typedef struct Node{
    int vertex;
    struct Node *next;
} Node;

/**
 * Cria um novo no, para encadear a lista de adjacencias
 * e retorna o endereço de memoria onde esta alocado
 */
Node* createNode(int v) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->vertex = v;
    newNode ->next = NULL;
    return newNode;
}

/** 
 * Cria o grafo, inicializando todas as listas de adjacencias 
 * com NULL, e retorna o endereço de memoria alocado para o grafo
 */
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = (Node**) malloc(vertices * sizeof(Node*));
    
    int i;
    for(i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }

    return graph;
    
}

/** 
 * Procura na lista de adjacencia do vertice pivo se já existe 
 * o outro vertice que se deseja adicionar pois caso exista
 * nao sera possivel adicionar novamente este vertice
 */
int searchVertex(Graph* graph, int v, int w) {
    Node* list = graph->adjLists[v];
    while(list != NULL) {
        if(list->vertex == w) {
            return 1;
        }
        list = list->next;
    }
    return 0;
}

/**
 * Adiciona-se uma aresta ao grafo, como o grafo é não direcional
 * cria-se o segmento v->w e depois cria-se o w->v. Cria-se o no que apontara
 * para NULL após isso aponta-se o proximo elemento da lista para o 
 */
void addEdge(Graph* graph, int v, int w) {
    if(!searchVertex(graph, v, w)) {
        Node* newNode = createNode(w);
        newNode->next = graph->adjLists[v];
        graph->adjLists[v] = newNode;
        
        newNode = createNode(v);
        newNode->next = graph->adjLists[w];
        graph->adjLists[w] = newNode;
    } else {
        printf("The graph already contains this edge!\n");
    }
}

/** 
 * Realiza-se a impressão da lista de adjacencia na tela
 */
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

/**
 * Verifica se o grafo está vazio, verificando se todas as
 * listas de adjacencias estao vazias, caso contenha pelo menos 1
 * não vazia significa que o grafo não é vazio
*/
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

/**
 * Realiza a liberação da memoria alocada para o grafo, para isso
 * percorre-se todo o array de lista de adjacencias, liberando a memoria
 * alocada para os nos das listas, após todas as listas serem liberadas
 * finalmente libera-se o grafo
*/
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

/**
 * Retorna os vertices adjacentes de um vertice dado v
 */
Node* neighborSet(Graph* graph, int v) {
    return graph->adjLists[v];
}

int getListSize(Node* list) {
    Node* l = list;
    if(l == NULL) {
        return 0;
    }
    int size = 1;
    while(l->next != NULL) {
        size++;
        l = l->next;
    }
    //printf("%d", size);
    return size;
}

int visited[63];
int DFS(Graph* graph, Node** list, int i) {
    int ti = 0;
    Node* p = list[i];
    while( p != NULL) {
        Node* tmp = p->next;
        while(tmp != NULL) {
            if(searchVertex(graph, p->vertex, tmp->vertex)) {
                ti++;
            }
            tmp = tmp->next;
        }
        p = p->next;
    }
    return ti;
}

double clusteringCoefficient(Graph* graph) {
    int numVertices = graph->numVertices;
    double nodeCoeffs[numVertices];
    double summation = 0;
    double C = 0;

    for(int i = 1; i < numVertices; i++) {
        int t = DFS(graph, graph->adjLists, i);
        if((getListSize(graph->adjLists[i])-1) > 1 ) {
            nodeCoeffs[i] = (double) 2 * t / (getListSize(graph->adjLists[i]) * (getListSize(graph->adjLists[i])-1));
        }
        summation += nodeCoeffs[i];
    }

    C = (double) (1.0 / numVertices) * summation;

    return C;
}