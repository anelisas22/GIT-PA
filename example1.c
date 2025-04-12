#include <stdio.h>
#include <stdlib.h>

// structura pt lista de adiacenta
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// structura pt graf
typedef struct Graph {
    int vertices;
    int *visited;
    Node **adjList;
} Graph;

// structura pt stiva
typedef struct Stack {
    int top;
    int capacity;
    int *array;
} Stack;

// creeaza un nod nou
Node *create_node(int value) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// adauga o muchie in graf
void add_edge(Graph *graph, int src, int dest) {
    Node *newNode = create_node(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    newNode = create_node(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// creeaza un graf cu v varfuri
Graph *create_graph(int vertices) {
    Graph *graph = malloc(sizeof(Graph));
    graph->vertices = vertices;

    graph->adjList = malloc(vertices * sizeof(Node *));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

// creează o stiva
Stack *create_stack(int capacity) {
    Stack *stack = malloc(sizeof(Stack));
    stack->array = malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

// adauga un element in stiva
void push(Stack *stack, int value) {
    stack->array[++stack->top] = value;
}

// DFS recursiv
void dfs(Graph *graph, Stack *stack, int vertex) {
    graph->visited[vertex] = 1;
    printf("%d ", vertex);
    push(stack, vertex);

    Node *adjList = graph->adjList[vertex];
    while (adjList != NULL) {
        int connectedVertex = adjList->data;
        if (graph->visited[connectedVertex] == 0) {
            dfs(graph, stack, connectedVertex);
        }
        adjList = adjList->next;
    }
}

// introduce muchii in graf
void insert_edges(Graph *graph, int edgeCount, int nodeCount) {
    int src, dest;
    printf("Adauga %d muchii (de la 0 la %d):\n", edgeCount, nodeCount - 1);
    for (int i = 0; i < edgeCount; i++) {
        scanf("%d %d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

// reseteaza vectorul de vizite
void reset_visited(Graph *graph) {
    for (int i = 0; i < graph->vertices; i++) {
        graph->visited[i] = 0;
    }
}

// verifica daca exista drum direct intre doua noduri
int has_direct_path(Graph *graph, int src, int dest) {
    Node *adjList = graph->adjList[src];
    while (adjList != NULL) {
        if (adjList->data == dest) {
            return 1;
        }
        adjList = adjList->next;
    }
    return 0;
}

int main() {
    int nodeCount, edgeCount;
    int src, dest;

    printf("Cate noduri are graful? ");
    scanf("%d", &nodeCount);

    printf("Cate muchii are graful? ");
    scanf("%d", &edgeCount);

    Graph *graph = create_graph(nodeCount);
    insert_edges(graph, edgeCount, nodeCount);

    printf("Introduceti doua noduri pentru a verifica daca exista drum direct intre ele: ");
    scanf("%d %d", &src, &dest);

    if (has_direct_path(graph, src, dest)) {
        printf("Exista un drum direct intre %d si %d.\n", src, dest);
    } else {
        printf("Nu exista drum direct intre %d si %d.\n", src, dest);
    }

    return 0;
}
