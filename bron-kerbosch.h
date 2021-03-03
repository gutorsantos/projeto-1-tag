void printNode(Node* n) {
    Node* temp = n;
    while(temp != NULL) {
        printf("%d ", temp->vertex);
        temp = temp->next;
    }
}

/**
 * Realiza-se a busca para ver se um vertice esta
 * contido numa lista (conjunto)
 */
int searchVertexSet(Node* n, int v) {
    Node* t = n;
    while(t != NULL) {
        if(t->vertex == v) {
            return 1;
        }
        t = t->next;
    }
    return 0;
}

/**
 * Realiza-se a uniao entre o conjunto R e conjunto
 * unitario {v}
 */
Node* RUnionV(Node* R, int v) {
    Node* r = R;
    Node* newSet = NULL;
    if(r == NULL) {
        newSet = createNode(v);
    }else {
        while(r != NULL) {
            Node* t = createNode(r->vertex);
            t->next = newSet;
            newSet = t;
            r = r->next;
        }
        Node* t = createNode(v);
        t->next = newSet;
        newSet = t;
    }
    return newSet;
}

/**
 * Realiza-se a uniao entre o conjunto X e conjunto
 * unitario {v}
 */
Node* XUnionV(Node* X, int v) {
    Node* x = X;
    Node* newSet = NULL;
    if(x == NULL) {
        newSet = createNode(v);
    }else {
        while(x != NULL) {
            Node* t = createNode(x->vertex);
            t->next = newSet;
            newSet = t;
            x = x->next;
        }
        Node* t = createNode(v);
        t->next = newSet;
        newSet = t;
    }
    return newSet;
}

/**
 * Realiza-se a uniao entre o conjunto X e conjunto
 * unitario {v}
 */
Node* PUnionX(Node* P, Node* X) {
    Node* p = P;
    Node* newSet = NULL;

    while(p != NULL) {
        if(searchVertexSet(X, p->vertex)) {
            Node* t = createNode(p->vertex);
            t->next = newSet;
            newSet = t;
        }else {
            Node* t = createNode(p->vertex);
            t->next = newSet;
            newSet = t;
        }
        p = p->next;
    }
    return newSet;
}

/**
 * Realiza-se a intersecao entre o conjunto P e conjunto
 * de vertices adjacentes de v
 */
Node* PIntersectNv(Node* P, Node* neighbors) {
    Node* p = P;
    Node* newSet = NULL;
    while(p != NULL) {
        if(searchVertexSet(neighbors, p->vertex)) {
            Node* t = createNode(p->vertex);
            t->next = newSet;
            newSet = t;
        }
        p = p->next;
    }
    return newSet;
}

/**
 * Realiza-se a intersecao entre o conjunto X e conjunto
 * de vertices adjacentes de v
 */
Node* XIntersectNv(Node* X, Node* neighbors) {
    Node* x = X;
    Node* newSet = NULL;
    while(x != NULL) {
        if(searchVertexSet(neighbors, x->vertex)) {
            Node* t = createNode(x->vertex);
            t->next = newSet;
            newSet = t;
        }
        x = x->next;
    }
    return newSet;
}

/**
 * Remove-se um vertice de uma lista
 */
Node* removeVertexNode(Node* P, int v) {
    Node* p = P;
    Node* newSet =  NULL;
    Node* prev = NULL;

    if(P == NULL) {
        newSet = NULL;
    }

    while(p != NULL) {
        Node* t = createNode(p->vertex);
        t->next = newSet;
        newSet = t;
        p = p->next;
    }
    p = newSet;
    while(p != NULL && p->vertex != v) {
        prev = p;
        p = p->next;
    }
    if(p == NULL)
        return newSet;

    if( prev == NULL) {
        newSet = p->next;
    }else {
        prev->next = p->next;
    }

    free(p);
    return newSet;
}

/**
 * Realiza a liberação da memoria alocada para o grafo, para isso
 * percorre-se todo a lista, liberando a memoria alocada para os nos
 * ate que nao haja mais alocacao
*/
void destroyList(Node* n) {
    Node* p = n;
    while(p != NULL) {
        Node* t = p->next;
        free(p);
        p = t;
    }
}

/** 
 * Algoritmo de Bron-Kerbosch sem pivotamento
*/
void BKv1(Graph* graph, Node* R, Node* P, Node* X) {
    if(P == NULL && X == NULL) {
        printf("\n\t|- Clique maximal achado: ");
        printNode(R);
        return;
    }
    Node* p = P;
    while(p != NULL) {
        Node* newR = RUnionV(R, p->vertex);
        Node* newP = PIntersectNv(P, neighborSet(graph, p->vertex));
        Node* newX = XIntersectNv(X, neighborSet(graph, p->vertex));

        BKv1(graph, newR, newP, newX);

        P = removeVertexNode(P, p->vertex);
        X = XUnionV(X, p->vertex);
        p = p->next;
    }
}

/** 
 * Algoritmo de Bron-Kerbosch com pivotamento
*/
void BKv2(Graph* graph, Node* R, Node* P, Node* X) {
    if(P == NULL && X == NULL) {
        printf("\n\t|- Clique maximal achado: ");
        printNode(R);
        return;
    }
    // Node* p = P;

    Node* pivot_list = PUnionX(P, X);

    while(pivot_list != NULL) {
        Node* newR = RUnionV(R, pivot_list->vertex);
        Node* newP = PIntersectNv(P, neighborSet(graph, pivot_list->vertex));
        Node* newX = XIntersectNv(X, neighborSet(graph, pivot_list->vertex));
        
        BKv2(graph, newR, newP, newX);
        
        P = removeVertexNode(P, pivot_list->vertex);
        X = XUnionV(X, pivot_list->vertex);
        pivot_list = pivot_list->next;
    }
}

/** 
 * Realiza a preparacao para o algoritmo, e
 * tambem seleciona se sera usado ou nao o pivotamento
*/
void findingCliques(Graph* graph, int pivot) {
    Node* R = NULL;
    Node* P = NULL;
    Node* X = NULL;
    
    // Cria o conjunto P o qual incialmente possui todos os vertices do grafo
    for(int i = 62; i > 0; i--) {
        Node* n = createNode(i);
        n->next = P;
        P = n;
    }
    
    if(pivot) {
        BKv2(graph, R, P, X);
    }else {
        BKv1(graph, R, P, X);
    }

    destroyList(R);
    destroyList(P);
    destroyList(X);

}