#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int adjMatrix[MAX][MAX]; // Adjacency Matrix
char vertices[MAX];      // Names of vertices
int numVertices;         // Number of vertices
int heuristic[MAX];      // Heuristic values

// Function to print the graph
void displayGraph() {
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// Hill Climbing Search
void hillClimbing(int start, int goal) {
    int current = start;
    
    printf("Starting Hill Climbing from %c\n", vertices[start]);

    while (current != goal) {
        printf("At vertex %c\n", vertices[current]);
        
        int bestNext = -1;
        int bestHeuristic = heuristic[current];
        
        for (int i = 0; i < numVertices; i++) {
            if (adjMatrix[current][i] != 0 && heuristic[i] < bestHeuristic) {
                bestHeuristic = heuristic[i];
                bestNext = i;
            }
        }
        
        if (bestNext == -1 || bestNext == current) {
            printf("Stuck at local maximum or plateau at vertex %c\n", vertices[current]);
            return;
        }
        
        current = bestNext;
    }
    
    printf("Reached goal %c\n", vertices[goal]);
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

    // Initialize adjacency matrix and heuristic array
    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < numVertices; j++) {
            adjMatrix[i][j] = 0;
        }
    }

    printf("Enter the heuristic values for each vertex:\n");
    for (i = 0; i < numVertices; i++) {
        printf("Heuristic for %c: ", vertices[i]);
        scanf("%d", &heuristic[i]);
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

    // Perform Hill Climbing Search
    hillClimbing(source, destination);

    return 0;
}
