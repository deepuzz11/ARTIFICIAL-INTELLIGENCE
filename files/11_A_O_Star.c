#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#define MAX 100

int adjMatrix[MAX][MAX], heuristic[MAX], numVertices;
char vertices[MAX];
bool solved[MAX];      // Marks nodes that have already been solved
bool partOfSolution[MAX];  // Tracks the optimal solution path
int minCost[MAX];      // Minimum cost to reach the goal from each node

// Function to update the minimum cost of the AND nodes (subproblems)
int updateCost(int current) {
    int cost = heuristic[current];

    // If the current node is a leaf node, return the heuristic cost
    if (current == numVertices - 1) {
        minCost[current] = cost;
        return cost;
    }

    int totalCost = INT_MAX;
    for (int i = 0; i < numVertices; i++) {
        if (adjMatrix[current][i] != 0) {
            int tempCost = adjMatrix[current][i] + updateCost(i);
            if (tempCost < totalCost) {
                totalCost = tempCost;
            }
        }
    }

    minCost[current] = cost + totalCost;
    return minCost[current];
}

// Function to run AO* search
void aoStar(int current) {
    if (solved[current]) {
        return;
    }

    printf("Processing %c\n", vertices[current]);

    int bestChild = -1;
    int bestCost = INT_MAX;

    // Select the best node to expand
    for (int i = 0; i < numVertices; i++) {
        if (adjMatrix[current][i] != 0) {
            int tempCost = adjMatrix[current][i] + heuristic[i];
            if (tempCost < bestCost) {
                bestCost = tempCost;
                bestChild = i;
            }
        }
    }

    if (bestChild != -1) {
        partOfSolution[current] = true;
        aoStar(bestChild);
    }

    solved[current] = true;
}

// Main function
int main() {
    int i, j, source;
    char start;

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
        int destination = strchr(vertices, d) - vertices;
        adjMatrix[source][destination] = weight;
    }

    // Input heuristics
    printf("Enter heuristic values for each vertex:\n");
    for (i = 0; i < numVertices; i++) {
        printf("Heuristic for %c: ", vertices[i]);
        scanf("%d", &heuristic[i]);
    }

    printf("Enter the start vertex: ");
    scanf(" %c", &start);

    source = strchr(vertices, start) - vertices;

    // Run AO* search
    aoStar(source);

    // Display solution path
    printf("Optimal path in the solution:\n");
    for (i = 0; i < numVertices; i++) {
        if (partOfSolution[i]) {
            printf("%c ", vertices[i]);
        }
    }
    printf("\n");

    return 0;
}
