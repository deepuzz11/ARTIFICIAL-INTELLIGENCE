#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX 100

int adjMatrix[MAX][MAX];
int visited[MAX];
int numVertices;
int heuristic[MAX]; // Heuristic values for each vertex

// Function to get the minimum heuristic node that has not been visited
int getMinHeuristicNode() {
    int min = INT_MAX;
    int minIndex = -1;

    for (int i = 0; i < numVertices; i++) {
        if (!visited[i] && heuristic[i] < min) {
            min = heuristic[i];
            minIndex = i;
        }
    }

    return minIndex;
}

// Best-First Search algorithm
void bestFirstSearch(int start, int goal) {
    int currentNode = start;
    printf("Path: %c ", currentNode + 'A');
    visited[currentNode] = 1;

    while (currentNode != goal) {
        int nextNode = getMinHeuristicNode();

        if (nextNode == -1) {
            printf("\nNo path found to goal!\n");
            return;
        }

        printf("-> %c ", nextNode + 'A');
        visited[nextNode] = 1;

        currentNode = nextNode;
    }

    printf("\nGoal reached: %c\n", goal + 'A');
}

int getVertexIndex(char vertices[], char vertex) {
    for (int i = 0; i < numVertices; i++) {
        if (vertices[i] == vertex) {
            return i;
        }
    }
    return -1;
}

int main() {
    int numEdges;
    char vertices[MAX];

    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    printf("Enter the names of the vertices:\n");
    for (int i = 0; i < numVertices; i++) {
        scanf(" %c", &vertices[i]);
    }

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    // Initialize adjacency matrix and visited array
    for (int i = 0; i < numVertices; i++) {
        visited[i] = 0;
        for (int j = 0; j < numVertices; j++) {
            adjMatrix[i][j] = 0;
        }
    }

    printf("Enter the edges (source destination weight):\n");
    for (int i = 0; i < numEdges; i++) {
        char s, d;
        int weight;
        scanf(" %c %c %d", &s, &d, &weight);
        int source = getVertexIndex(vertices, s);
        int destination = getVertexIndex(vertices, d);

        if (source == -1 || destination == -1) {
            printf("Invalid vertex name\n");
            return -1;
        }

        adjMatrix[source][destination] = weight;
        adjMatrix[destination][source] = weight;  // Assuming undirected graph
    }

    // Input heuristics
    printf("Enter heuristic values for each vertex:\n");
    for (int i = 0; i < numVertices; i++) {
        printf("Heuristic for %c: ", vertices[i]);
        scanf("%d", &heuristic[i]);
    }

    char startVertex, goalVertex;
    printf("Enter the start vertex: ");
    scanf(" %c", &startVertex);

    printf("Enter the goal vertex: ");
    scanf(" %c", &goalVertex);

    int start = getVertexIndex(vertices, startVertex);
    int goal = getVertexIndex(vertices, goalVertex);

    if (start == -1 || goal == -1) {
        printf("Invalid start or goal vertex\n");
        return -1;
    }

    // Run Best-First Search
    bestFirstSearch(start, goal);

    return 0;
}
