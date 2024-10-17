#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#define MAX 100

int adjMatrix[MAX][MAX], heuristic[MAX], numVertices;
char vertices[MAX];
int gCost[MAX];  // Actual cost from start to the current node
int fCost[MAX];  // Total cost (gCost + heuristic)
bool closedSet[MAX];  // Nodes that have been fully explored
bool openSet[MAX];    // Nodes that need to be explored
int cameFrom[MAX];    // For path reconstruction

// Function to get index of vertex with the lowest fCost in the openSet
int getLowestFIndex() {
    int lowestF = INT_MAX;
    int lowestIndex = -1;
    for (int i = 0; i < numVertices; i++) {
        if (openSet[i] && fCost[i] < lowestF) {
            lowestF = fCost[i];
            lowestIndex = i;
        }
    }
    return lowestIndex;
}

// Function to reconstruct the path from start to goal
void reconstructPath(int current) {
    if (cameFrom[current] != -1) {
        reconstructPath(cameFrom[current]);
        printf(" -> ");
    }
    printf("%c", vertices[current]);
}

// A* search algorithm
void aStar(int start, int goal) {
    for (int i = 0; i < numVertices; i++) {
        gCost[i] = INT_MAX;
        fCost[i] = INT_MAX;
        closedSet[i] = false;
        openSet[i] = false;
        cameFrom[i] = -1;
    }

    gCost[start] = 0;
    fCost[start] = heuristic[start];
    openSet[start] = true;

    while (true) {
        int current = getLowestFIndex();
        if (current == -1) {
            printf("No path found.\n");
            return;
        }

        if (current == goal) {
            printf("Path found: ");
            reconstructPath(current);
            printf("\nTotal cost: %d\n", gCost[goal]);
            return;
        }

        openSet[current] = false;
        closedSet[current] = true;

        for (int i = 0; i < numVertices; i++) {
            if (adjMatrix[current][i] != 0 && !closedSet[i]) {
                int tentativeGCost = gCost[current] + adjMatrix[current][i];

                if (!openSet[i]) {
                    openSet[i] = true;
                } else if (tentativeGCost >= gCost[i]) {
                    continue;
                }

                cameFrom[i] = current;
                gCost[i] = tentativeGCost;
                fCost[i] = gCost[i] + heuristic[i];
            }
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

    // Input heuristics
    printf("Enter heuristic values for each vertex:\n");
    for (i = 0; i < numVertices; i++) {
        printf("Heuristic for %c: ", vertices[i]);
        scanf("%d", &heuristic[i]);
    }

    // Taking start and goal inputs
    printf("Enter the start vertex: ");
    scanf(" %c", &start);
    printf("Enter the goal vertex: ");
    scanf(" %c", &goal);

    source = strchr(vertices, start) - vertices;
    destination = strchr(vertices, goal) - vertices;

    // Perform A* search
    aStar(source, destination);

    return 0;
}
