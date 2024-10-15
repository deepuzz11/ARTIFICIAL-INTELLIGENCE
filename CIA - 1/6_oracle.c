#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int adjMatrix[MAX][MAX], numVertices;
char vertices[MAX];

// Simulated Oracle path (predefined by the oracle)
int oraclePath[MAX], pathLength = 0;

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

// Oracle search function (simulated)
void oracleSearch(int source, int goal) {
    printf("Oracle knows the path from %c to %c:\n", vertices[source], vertices[goal]);
    for (int i = 0; i < pathLength; i++) {
        printf("%c ", vertices[oraclePath[i]]);
        if (i < pathLength - 1) {
            printf("-> ");
        }
    }
    printf("\nGoal %c reached by Oracle!\n", vertices[goal]);
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
        int source = strchr(vertices, s) - vertices;
        int destination = strchr(vertices, d) - vertices;
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

    // Simulate an Oracle knowing the path (predefined for simplicity)
    printf("Enter the length of the Oracle's known path: ");
    scanf("%d", &pathLength);
    printf("Enter the Oracle's known path (sequence of vertices):\n");
    for (i = 0; i < pathLength; i++) {
        char vertex;
        scanf(" %c", &vertex);
        oraclePath[i] = strchr(vertices, vertex) - vertices;
    }

    // Perform Oracle Search
    oracleSearch(source, destination);

    return 0;
}
