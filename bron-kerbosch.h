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
    if(r == NULL) {
        r = createNode(v);
    }else {
        Node* t = createNode(v);
        t->next = r;
        r = t;
    }
    return r;
}

/**
 * Realiza-se a uniao entre o conjunto X e conjunto
 * unitario {v}
 */
Node* XUnionV(Node* X, int v) {
    Node* x = X;
    if(x == NULL) {
        x = createNode(v);
    }else {
        Node* t = createNode(v);
        t->next = x;
        x = t;
    }
    return x;
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
    return p;
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
    Node* prev = NULL;
    Node* next = NULL;
    while(p != NULL && p->vertex != v) {
        prev = p;
        p = p->next;
    }
    if(p == NULL)
        return P;

    if( prev == NULL) {
        P = p->next;
    }else {
        prev->next = p->next;
    }

    free(p);
    return P;
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

void BKv1(Graph* graph, Node* R, Node* P, Node* X) {
    printf("\n\n\n");
    printf("R: ");
    printNode(R);
    printf("\n");
    printf("P: ");
    printNode(P);
    printf("\n");
    printf("X: ");
    printNode(X);
    printf("\n\n\n");

    if(P == NULL && X == NULL) {
        printf("Clique maximal achado:\n");
        printNode(R);
        return;
    }
    Node* p = P;
    while(p != NULL) {
        BKv1(graph, RUnionV(R, p->vertex), PIntersectNv(P, neighborSet(graph, p->vertex)), XIntersectNv(X, neighborSet(graph, p->vertex)));
        P = removeVertexNode(P, p->vertex);
        X = XUnionV(X, p->vertex);
        p = p->next;
    }
    /* Print da volta da recursividade*/
    printf("\n\n\n");
    printf("R: ");
    printNode(R);
    printf("\n");
    printf("P: ");
    printNode(P);
    printf("\n");
    printf("X: ");
    printNode(X);
    printf("\n\n\n");

    return;
}

/*
void BKv2(Graph* graph, Node* R, Node* P, Node* X) {
    printf("\n\n\n");
    printf("R: ");
    printNode(R);
    printf("\n");
    printf("P: ");
    printNode(P);
    printf("\n");
    printf("X: ");
    printNode(X);
    printf("\n\n\n");

    if(P == NULL && X == NULL) {
        printf("Clique maximal achado:\n");
        printNode(R);
        return;
    }
    // Node* p = P;

    Node* pivot_list = PUnionX(P, X);
    // selecionar nessa lista os pivos com maiores graus 

        // P \ N(u)
    while(removeVertexNode(pivot_list, pivot->vertex) != NULL) {
        printf("VERTICE: %d\n", p->vertex);
        BKv1(graph, RUnionV(R, p->vertex), PIntersectNv(P, neighborSet(graph, p->vertex)), XIntersectNv(X, neighborSet(graph, p->vertex)));
        P = removeVertexNode(P, p->vertex);
        X = XUnionV(X, p->vertex);
        p = p->next;
    }
    /* Print da volta da recursividade
    printf("\n\n\n");
    printf("R: ");
    printNode(R);
    printf("\n");
    printf("P: ");
    printNode(P);
    printf("\n");
    printf("X: ");
    printNode(X);
    printf("\n\n\n");

    return;
}*/

void findingCliques(Graph* graph, int pivot) {
    Node* R = NULL;
    Node* P = NULL;
    Node* X = NULL;
    
    for(int i = 62; i > 0; i--) {
        Node* n = createNode(i);
        n->next = P;
        P = n;
    }
    
    if(pivot) {
        //BKv2(graph, R, P, X);
    }else {
        BKv1(graph, R, P, X);
    }

    destroyList(R);
    destroyList(P);
    destroyList(X);

}