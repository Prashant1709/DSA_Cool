#include <stdio.h>
#include <stdlib.h>
struct node //denotes a node in the Ad. List
{
    int node_index;
    struct node *next;
};
struct AdjacencyList
{
    int no_of_nodes;   //number of nodes in the graph
    struct node **arr; //holds the list
};
//queue
int *queue;
int front = -1, rear = -1, queue_size;
void enqueue(int elem)
{
    if (rear == -1)
    {
        front = 0;
        rear = 0;
    }
    else
    {
        rear++;
        rear %= queue_size;
    }
    queue[rear] = elem;
}
int dequeue()
{
    int temp = queue[front];
    if (front == rear)
    {
        front = -1;
        rear = -1;
    }
    else
    {
        front++;
        front %= queue_size;
    }
    return temp;
}
void init(struct AdjacencyList *a, int no_of_nodes) //initialises the Ad. List with the number of nodes
{
    a->no_of_nodes = no_of_nodes;
    a->arr = (struct node **)malloc(no_of_nodes * sizeof(struct node *));
    for (int i = 0; i < no_of_nodes; ++i)
    {
        a->arr[i] = NULL;
    }
    queue = (int *)malloc(sizeof(int) * no_of_nodes);
    queue_size = no_of_nodes;
}
void createEdge(struct AdjacencyList *a, int node_1, int node_2) //creates an edge between two nodes
{
    if (a->arr[node_1] == NULL)
    {
        a->arr[node_1] = (struct node *)malloc(sizeof(struct node));
        a->arr[node_1]->next = NULL;
        a->arr[node_1]->node_index = node_2;
    }
    else
    {
        struct node *temp = a->arr[node_1];
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = (struct node *)malloc(sizeof(struct node));
        temp = temp->next;
        temp->next = NULL;
        temp->node_index = node_2;
    }
    if (a->arr[node_2] == NULL)
    {
        a->arr[node_2] = (struct node *)malloc(sizeof(struct node));
        a->arr[node_2]->next = NULL;
        a->arr[node_2]->node_index = node_1;
    }
    else
    {
        struct node *temp = a->arr[node_2];
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = (struct node *)malloc(sizeof(struct node));
        temp = temp->next;
        temp->next = NULL;
        temp->node_index = node_1;
    }
}
void bfs(struct AdjacencyList a, int start_node)
{
    //visited
    int *visited = (int *)malloc(sizeof(int) * a.no_of_nodes);
    for (int i = 0; i < a.no_of_nodes; ++i)
    {
        visited[i] = 0;
    }
    //enqueueing start_node
    enqueue(start_node);
    visited[start_node] = 1;
    printf("%d ", start_node);
    while (front != -1) //front == -1 means and empty queue and the nodes connected to the start_node have been traversed
    {
        struct node *temp = a.arr[queue[front]];
        while (temp != NULL)
        {
            if (visited[temp->node_index] == 0)
            {
                visited[temp->node_index] = 1;
                enqueue(temp->node_index);
                printf("%d ", temp->node_index);
            }
            temp = temp->next;
        }
        dequeue();
    }
}
void dfs(struct AdjacencyList a, int start_node)
{
    //stack
    int *node_stack = (int *)malloc(sizeof(int) * a.no_of_nodes);
    int top = -1;
    //visited
    int *visited = (int *)malloc(sizeof(int) * a.no_of_nodes);
    for (int i = 0; i < a.no_of_nodes; ++i)
    {
        visited[i] = 0;
    }
    node_stack[++top] = start_node; //pushing start_node
    visited[start_node] = 1;        //visited start_node
    printf("%d ", start_node);
    while (top != -1) //top == -1 means that the start_node was popped and the graph connected with the start_node has been fully traversed
    {
        //finding unvisited node connected to the stack top node
        struct node *temp = a.arr[node_stack[top]];
        while (temp != NULL)
        {
            if (visited[temp->node_index] == 0) //found an unvisited node
            {
                visited[temp->node_index] = 1;
                printf("%d ", temp->node_index);
                node_stack[++top] = temp->node_index;
                break;
            }
            temp = temp->next;
        }
        if (temp == NULL) //no unvisited node
        {
            top--; //popping the top
        }
    }
}
int main()
{
    struct AdjacencyList a;
    init(&a, 6);
    createEdge(&a, 0, 1);
    createEdge(&a, 0, 2);
    createEdge(&a, 1, 3);
    createEdge(&a, 2, 3);
    createEdge(&a, 2, 4);
    createEdge(&a, 3, 4);
    createEdge(&a, 3, 5);
    printf("DFS: ");
    dfs(a, 2);
    printf("\nBFS: ");
    bfs(a, 2);
}