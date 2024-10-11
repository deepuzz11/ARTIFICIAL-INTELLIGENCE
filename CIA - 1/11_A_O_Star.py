import networkx as nx
import matplotlib.pyplot as plt
from collections import defaultdict
import heapq

def ao_star_search(graph, start, goal, heuristic):
    frontier = [(0 + heuristic[start], start, [start])]
    visited = set()
    best_paths = defaultdict(lambda: float('inf'))
    best_paths[start] = 0

    while frontier:
        est_total_cost, node, path = heapq.heappop(frontier)
        
        if node == goal:
            return path
        
        if est_total_cost > best_paths[node]:
            continue
        
        for neighbor in graph.neighbors(node):
            edge_cost = graph[node][neighbor]['weight']
            new_cost = best_paths[node] + edge_cost
            
            if new_cost < best_paths[neighbor]:
                best_paths[neighbor] = new_cost
                est_total_cost = new_cost + heuristic[neighbor]
                heapq.heappush(frontier, (est_total_cost, neighbor, path + [neighbor]))
    
    print("No path found.")
    return None

# Input graph details and heuristic values
num_vertices = int(input("Enter the number of vertices: "))
edges = []
for _ in range(int(input("Enter the number of edges: "))):
    edge = input("Enter edge (format: source target weight): ").split()
    edges.append((edge[0], edge[1], int(edge[2])))

# Heuristic values for each node
heuristic = {}
for _ in range(num_vertices):
    vertex, value = input("Enter vertex and heuristic value (format: vertex value): ").split()
    heuristic[vertex] = int(value)

start_vertex = input("Enter the start vertex: ")
goal_vertex = input("Enter the goal vertex: ")

# Create a weighted graph using networkx
G = nx.Graph()
for edge in edges:
    G.add_edge(edge[0], edge[1], weight=edge[2])

# Perform AO* Search
path = ao_star_search(G, start_vertex, goal_vertex, heuristic)

# Draw the initial graph
pos = nx.spring_layout(G)
plt.figure(figsize=(10, 7))
nx.draw(G, pos, with_labels=True, node_size=700, node_color='lightblue', font_size=16, font_weight='bold', edge_color='gray')
edge_labels = nx.get_edge_attributes(G, 'weight')
nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)
plt.title("Initial Graph")
plt.show()

# If a path is found, display the path
if path:
    path_edges = list(zip(path, path[1:]))
    plt.figure(figsize=(10, 7))
    nx.draw(G, pos, with_labels=True, node_size=700, node_color='lightblue', font_size=16, font_weight='bold', edge_color='gray')
    nx.draw_networkx_edges(G, pos, edgelist=path_edges, edge_color='r', width=2)
    nx.draw_networkx_nodes(G, pos, nodelist=path, node_color='lightgreen')
    plt.title(f"AO* Path: {path}")
    plt.show()
else:
    print("No path found.")
