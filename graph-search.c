#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 10

// ���� ����Ʈ ��� ����ü ����
typedef struct AdjListNode {
    int dest;
    struct AdjListNode* next;
} AdjListNode;

// ���� ����Ʈ ����ü ����
typedef struct AdjList {
    AdjListNode* head;
} AdjList;

// �׷��� ����ü ����
typedef struct Graph {
    int numVertices;
    AdjList* array;
} Graph;

// ť ����ü ���� (BFS��)
typedef struct Queue {
    int items[MAX_VERTICES];
    int front, rear;
} Queue;

// ���ο� ���� ����Ʈ ��� ����
AdjListNode* newAdjListNode(int dest) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// �׷��� ����
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->array = (AdjList*)malloc(vertices * sizeof(AdjList));

    for (int i = 0; i < vertices; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// �׷����� ���� �߰�
void addEdge(Graph* graph, int src, int dest) {
    AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// �׷��� ���
void printGraph(Graph* graph) {
    for (int v = 0; v < graph->numVertices; ++v) {
        AdjListNode* pCrawl = graph->array[v].head;
        printf("\n ���� %d�� ���� ����Ʈ\n head ", v);
        while (pCrawl) {
            printf("-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

// ť ���� (BFS��)
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

// ť�� ��� �ִ��� Ȯ��
int isEmpty(Queue* queue) {
    return queue->rear == -1;
}

// ť�� ��� �߰�
void enqueue(Queue* queue, int value) {
    if (queue->rear == MAX_VERTICES - 1)
        printf("\nť�� ���� á���ϴ�!");
    else {
        if (queue->front == -1)
            queue->front = 0;
        queue->rear++;
        queue->items[queue->rear] = value;
    }
}

// ť���� ��� ����
int dequeue(Queue* queue) {
    int item;
    if (isEmpty(queue)) {
        printf("ť�� ��� �ֽ��ϴ�.");
        item = -1;
    } else {
        item = queue->items[queue->front];
        queue->front++;
        if (queue->front > queue->rear) {
            queue->front = queue->rear = -1;
        }
    }
    return item;
}

// ���� �켱 Ž�� (DFS)
void DFS(Graph* graph, int vertex, int* visited) {
    AdjListNode* adjList = graph->array[vertex].head;
    AdjListNode* temp = adjList;

    visited[vertex] = 1;
    printf("%d ", vertex);

    while (temp != NULL) {
        int connectedVertex = temp->dest;

        if (!visited[connectedVertex]) {
            DFS(graph, connectedVertex, visited);
        }
        temp = temp->next;
    }
}

// ���� �켱 Ž�� (DFS) ���� �Լ�
void depthFirstSearch(Graph* graph, int startVertex) {
    int visited[MAX_VERTICES] = {0};

    DFS(graph, startVertex, visited);
    printf("\n");
}

// ���� ����Ʈ�� �����ϴ� �Լ� (��������)
void sortAdjList(AdjList* adjList) {
    AdjListNode* sorted = NULL;
    AdjListNode* current = adjList->head;

    // ���� ����Ʈ�� ��� ��带 �� ����Ʈ�� �����ϸ� ����
    while (current != NULL) {
        AdjListNode* next = current->next;
        if (sorted == NULL || sorted->dest >= current->dest) {
            current->next = sorted;
            sorted = current;
        } else {
            AdjListNode* temp = sorted;
            while (temp->next != NULL && temp->next->dest < current->dest) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }

    adjList->head = sorted;
}

// �ʺ� �켱 Ž�� (BFS)
void breadthFirstSearch(Graph* graph, int startVertex) {
    int visited[MAX_VERTICES] = {0};
    Queue* queue = createQueue();

    visited[startVertex] = 1;
    enqueue(queue, startVertex);

    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);

        // ������ ���� ����Ʈ�� ������������ ����
        sortAdjList(&(graph->array[currentVertex]));

        AdjListNode* temp = graph->array[currentVertex].head;

        while (temp) {
            int adjVertex = temp->dest;

            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                enqueue(queue, adjVertex);
            }
            temp = temp->next;
        }
    }
    printf("\n");
}


// �޴� ��� ���α׷� ���� �Լ�
int main() {
    char command;
    int vertex, vertex2;
    Graph* graph = NULL;
    
    printf(" [----- [Josungjae] [2023078001]-----]");
    printf("---------------------------------------------------------------\n");
    printf("Graph Searches\n");
    printf("---------------------------------------------------------------\n");
    printf("Initialize Graph = z\n");
    printf("Insert Vertex = v Insert Edge = e\n");
    printf("Depth First Search = d Breadth First Search = b\n");
    printf("Print Graph = p Quit = q\n");
    printf("---------------------------------------------------------------\n");

    while (1) {
        printf("\n��ɾ� �Է�: ");
        scanf(" %c", &command);

        switch (command) {
            case 'z':
                graph = createGraph(MAX_VERTICES);
                printf("�׷����� %d���� �������� �ʱ�ȭ�Ǿ����ϴ�.\n", MAX_VERTICES);
                break;

            case 'v':
                printf("������ �ڵ����� �ִ� %d������ �����˴ϴ�.\n", MAX_VERTICES);
                break;

            case 'e':
                printf("���� �Է� (����: v1 v2): ");
                scanf("%d %d", &vertex, &vertex2);
                if (graph && vertex < MAX_VERTICES && vertex2 < MAX_VERTICES) {
                    addEdge(graph, vertex, vertex2);
                    printf("���� %d�� ���� %d ���̿� ������ �߰��Ǿ����ϴ�.\n", vertex, vertex2);
                } else {
                    printf("�߸��� �����̰ų� �׷����� �ʱ�ȭ���� �ʾҽ��ϴ�.\n");
                }
                break;

            case 'd':
                if (graph) {
                    printf("DFS ���� ���� �Է�: ");
                    scanf("%d", &vertex);
                    if (vertex < MAX_VERTICES) {
                        printf("���� %d���� �����ϴ� DFS Ž��: ", vertex);
                        depthFirstSearch(graph, vertex);
                    } else {
                        printf("�߸��� ���� �����Դϴ�.\n");
                    }
                } else {
                    printf("�׷����� �ʱ�ȭ���� �ʾҽ��ϴ�.\n");
                }
                break;

            case 'b':
                if (graph) {
                    printf("BFS ���� ���� �Է�: ");
                    scanf("%d", &vertex);
                    if (vertex < MAX_VERTICES) {
                        printf("���� %d���� �����ϴ� BFS Ž��: ", vertex);
                        breadthFirstSearch(graph, vertex);
                    } else {
                        printf("�߸��� ���� �����Դϴ�.\n");
                    }
                } else {
                    printf("�׷����� �ʱ�ȭ���� �ʾҽ��ϴ�.\n");
                }
                break;

            case 'p':
                if (graph) {
                    printGraph(graph);
                } else {
                    printf("�׷����� �ʱ�ȭ���� �ʾҽ��ϴ�.\n");
                }
                break;

            case 'q':
                printf("���α׷��� �����մϴ�.\n");
                return 0;

            default:
                printf("�߸��� ��ɾ��Դϴ�. �ٽ� �õ��ϼ���.\n");
        }
    }

    return 0;
}
