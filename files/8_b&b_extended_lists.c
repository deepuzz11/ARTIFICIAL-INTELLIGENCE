#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#define MAX 100

int adjMatrix[MAX][MAX], numVertices;
char vertices[MAX];
int bestCost = INT_MAX;
bool visited[MAX];
bool extendedList[MAX];
int currentPath[MAX];

// Function to display the graph as adjacency matrix
void displayGraph() {
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < numVertices; i++) {
        printf("%c: ", vertices[i]);
        for (int j = 0; j < numVertices; j++) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// Recursive Branch and Bound function with extended lists
void branchAndBoundExtended(int current, int goal, int cost, int depth) {
    if (cost >= bestCost) {
        return; // Prune branch if the current cost exceeds the best found
    }

    if (current == goal) {
        if (cost < bestCost) {
            bestCost = cost;
            printf("New best path with cost %d: ", bestCost);
            for (int i = 0; i < depth; i++) {
                printf("%c -> ", vertices[currentPath[i]]);
            }
            printf("%c\n", vertices[goal]);
        }
        return;
    }

    for (int i = 0; i < numVertices; i++) {
        if (adjMatrix[current][i] != 0 && !visited[i] && !extendedList[i]) {
            visited[i] = true;
            extendedList[i] = true; // Mark in extended list to avoid revisiting
            currentPath[depth] = i;
            branchAndBoundExtended(i, goal, cost + adjMatrix[current][i], depth + 1);
            visited[i] = false;
        }
    }
}

// Main function
int main() {
    int i, j, source, destination;
    char start, goal;

    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    printf("Enter the names of the vertices:\n");
    for (i = 0; i < numVertices; i++) {
        scanf(" %c", &vertices[i]);
    }

    printf("Enter the number of edges: ");
    int numEdges;
    scanf("%d", &numEdges);

    // Initialize adjacency matrix
    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < numVertices; j++) {
            adjMatrix[i][j] = 0;
        }
    }

    printf("Enter the edges (source destination weight):\n");
    for (i = 0; i < numEdges; i++) {
        char s, d;
        int weight;
        scanf(" %c %c %d", &s, &d, &weight);
        source = strchr(vertices, s) - vertices;
        destination = strchr(vertices, d) - vertices;
        adjMatrix[source][destination] = weight;
        adjMatrix[destination][source] = weight; // Assuming undirected graph
    }

    displayGraph();

    // Taking start and goal inputs
    printf("Enter the start vertex: ");
    scanf(" %c", &start);
    printf("Enter the goal vertex: ");
    scanf(" %c", &goal);

    source = strchr(vertices, start) - vertices;
    destination = strchr(vertices, goal) - vertices;

    // Initialize visited and extended lists
    for (i = 0; i < numVertices; i++) {
        visited[i] = false;
        extendedList[i] = false;
    }

    visited[source] = true;
    extendedList[source] = true;
    currentPath[0] = source;

    // Perform Branch and Bound Search with extended list (Dead Horse Principle)
    branchAndBoundExtended(source, destination, 0, 1);

    printf("Best cost found: %d\n", bestCost);

    return 0;
}
