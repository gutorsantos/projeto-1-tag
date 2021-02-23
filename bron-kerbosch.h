void printNode(Node* n) {
    Node* temp = n;
    while(temp != NULL) {
        printf("%d ", temp->vertex);
        temp = temp->next;
    }
}

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

void destroyList(Node* n) {
    Node* p = n;
    while(p != NULL) {
        Node* t = p->next;
        free(p);
        p = t;
    }
}

void BKv1(Graph* graph, Node* R, Node* P, Node* X) {
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
        printf("VERTICE: %d\n", p->vertex);
        BKv1(graph, RUnionV(R, p->vertex), PIntersectNv(P, neighborSet(graph, p->vertex)), XIntersectNv(X, neighborSet(graph, p->vertex)));
        P = removeVertexNode(P, p->vertex);
        X = XUnionV(X, p->vertex);
        p = p->next;
    }
}

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