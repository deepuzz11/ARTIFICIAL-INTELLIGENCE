#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

int queue[MAX];
int front = -1, rear = -1;

void enqueue(int value) {
    if (rear == MAX - 1) return;
    if (front == -1) front = 0;
    queue[++rear] = value;
}

int dequeue() {
    if (front == -1) return -1;
    int value = queue[front];
    if (front == rear) front = rear = -1;
    else front++;
    return value;
}

bool is_empty() {
    return front == -1;
}

void bfs(int graph[][MAX], int start, int num_vertices) {
    int visited[MAX] = {0};
    enqueue(start);
    visited[start] = 1;

    while (!is_empty()) {
        int current = dequeue();
        printf("%d ", current);

        for (int i = 0; i < num_vertices; i++) {
            if (graph[current][i] && !visited[i]) {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }
}

int main() {
    int num_vertices = 4;
    int graph[MAX][MAX] = {
        {0, 1, 1, 0},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {0, 1, 1, 0}
    };
    
    bfs(graph, 0, num_vertices);
    return 0;
}
