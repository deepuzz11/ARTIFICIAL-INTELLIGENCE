#include <stdio.h>
#include <stdlib.h>

#define MAX 20
#define BEAM_WIDTH 2  // Number of nodes to expand at each step

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

// Function to find the index of a vertex
int findVertexIndex(char vertex) {
    for (int i = 0; i < numVertices; i++) {
        if (vertices[i] == vertex) {
            return i;
        }
    }
    return -1; // Return -1 if the vertex is not found
}

// Beam Search
void beamSearch(int start, int goal) {
    printf("Starting Beam Search from %c\n", vertices[start]);

    int current = start;
    while (current != goal) {
        printf("At vertex %c\n", vertices[current]);
        
        int bestNext[MAX], bestHeuristics[MAX];
        for (int i = 0; i < BEAM_WIDTH; i++) {
            bestNext[i] = -1;
            bestHeuristics[i] = __INT_MAX__;
        }

        // Find BEAM_WIDTH best successors
        for (int i = 0; i < numVertices; i++) {
            if (adjMatrix[current][i] != 0 && heuristic[i] < bestHeuristics[BEAM_WIDTH - 1]) {
                // Insert in sorted order (ascending by heuristic)
                int j = BEAM_WIDTH - 1;
                while (j > 0 && heuristic[i] < bestHeuristics[j - 1]) {
                    bestHeuristics[j] = bestHeuristics[j - 1];
                    bestNext[j] = bestNext[j - 1];
                    j--;
                }
                bestHeuristics[j] = heuristic[i];
                bestNext[j] = i;
            }
        }

        if (bestNext[0] == -1) {
            printf("Stuck at local maximum or no further path from vertex %c\n", vertices[current]);
            return;
        }

        current = bestNext[0];  // Choose the best option from the beam
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
        source = findVertexIndex(s);
        destination = findVertexIndex(d);
        adjMatrix[source][destination] = weight;
        adjMatrix[destination][source] = weight; // Assuming undirected graph
    }

    displayGraph();

    // Taking start and goal inputs
    printf("Enter the start vertex: ");
    scanf(" %c", &start);
    printf("Enter the goal vertex: ");
    scanf(" %c", &goal);

    source = findVertexIndex(start);
    destination = findVertexIndex(goal);

    if (source == -1 || destination == -1) {
        printf("Invalid start or goal vertex.\n");
        return 1;
    }

    // Perform Beam Search
    beamSearch(source, destination);

    return 0;
}
