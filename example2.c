#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct Graph
{
    int number_of_vertices;
    int *visited;
    struct Node **adjacency_lists;
} Graph;

// functie pentru crearea unui nod nou
Node *create_node(int value)
{
    Node *new_node = malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

// functie pentru crearea unui grafic cu un numar de noduri specificat
Graph *create_graph(int number_of_vertices)
{
    Graph *graph = malloc(sizeof(Graph));
    graph->number_of_vertices = number_of_vertices;
    graph->adjacency_lists = malloc(number_of_vertices * sizeof(Node *));
    graph->visited = malloc(number_of_vertices * sizeof(int));

    for (int i = 0; i < number_of_vertices; i++)
    {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

// functie pentru adaugarea unei muchii intre doua noduri
void add_edge(Graph *graph, int src, int dest)
{
    Node *new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

// functie pentru citirea muchiilor din input
void insert_edges(int number_of_vertices, int number_of_edges, Graph *graph)
{
    int src, dest;

    printf("Adauga %d muchii (de la 1 la %d):\n", number_of_edges, number_of_vertices);

    for (int i = 0; i < number_of_edges; i++)
    {
        scanf("%d %d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

// functie pentru verificarea daca coada este goala
int is_empty(Node *queue)
{
    return queue == NULL;
}

// functie pentru adaugarea unui element in coada
void enqueue(Node **queue, int data)
{
    Node *new_node = create_node(data);

    if (is_empty(*queue))
    {
        *queue = new_node;
    }
    else
    {
        Node *temp = *queue;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

// functie pentru extragerea unui element din coada
int dequeue(Node **queue)
{
    int data = (*queue)->data;
    Node *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

// functie pentru afisarea graficului
void print_graph(Graph *graph)
{
    for (int i = 0; i < graph->number_of_vertices; i++)
    {
        Node *temp = graph->adjacency_lists[i];
        while (temp)
        {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

// functie pentru afisarea cozii
void print_queue(Node *queue)
{
    while (queue != NULL)
    {
        printf("%d ", queue->data);
        queue = queue->next;
    }
}

// functie pentru resetarea listei de vizitate
void reset_visited_list(Graph *graph, int number_of_vertices)
{
    for (int i = 0; i < number_of_vertices; i++)
    {
        graph->visited[i] = 0;
    }
}

// parcurgere DFS
void DFS(Graph *graph, int vertex)
{
    Node *adj_list = graph->adjacency_lists[vertex];
    Node *temp = adj_list;

    graph->visited[vertex] = 1;
    printf("%d->", vertex);

    while (temp != NULL)
    {
        int connected_vertex = temp->data;

        if (graph->visited[connected_vertex] == 0)
        {
            DFS(graph, connected_vertex);
        }

        temp = temp->next;
    }
}

// parcurgere BFS
void BFS(Graph *graph, int start)
{
    Node *queue = NULL;
    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!is_empty(queue))
    {
        int current = dequeue(&queue);
        printf("%d ", current);

        Node *temp = graph->adjacency_lists[current];
        while (temp)
        {
            int adj_vertex = temp->data;

            if (graph->visited[adj_vertex] == 0)
            {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }

            temp = temp->next;
        }
    }
}

// Funcție principală
int main()
{
    int number_of_vertices, number_of_edges, starting_vertex;

    printf("Cate noduri are graful?\n");
    scanf("%d", &number_of_vertices);

    printf("Cate muchii are graful?\n");
    scanf("%d", &number_of_edges);

    Graph *graph = create_graph(number_of_vertices);
    insert_edges(number_of_vertices, number_of_edges, graph);

    printf("De unde plecam in DFS?\n");
    scanf("%d", &starting_vertex);
    printf("Parcurgere cu DFS:\n");
    DFS(graph, starting_vertex);
    printf("\n");

    reset_visited_list(graph, number_of_vertices);

    printf("De unde plecam in BFS?\n");
    scanf("%d", &starting_vertex);
    printf("Parcurgere cu BFS:\n");
    BFS(graph, starting_vertex);
    printf("\n");

    return 0;
}
