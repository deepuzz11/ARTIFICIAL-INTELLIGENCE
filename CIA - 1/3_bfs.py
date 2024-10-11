import networkx as nx
import matplotlib.pyplot as plt
from collections import deque

def breadth_first_search(graph, start, goal):
    visited = set()
    queue = deque([[start]])
    while queue:
        path = queue.popleft()
        node = path[-1]
        if node in visited:
            continue
        visited.add(node)
        for neighbor in graph[node]:
            new_path = list(path)
            new_path.append(neighbor)
            queue.append(new_path)
            if neighbor == goal:
                return new_path
    return None

# Input graph details
num_vertices = int(input("Enter the number of vertices: "))
edges = []
for _ in range(num_vertices):
    edges.append(input("Enter edge (format: source target weight): ").split())

start_vertex = input("Enter the start vertex: ")
goal_vertex = input("Enter the goal vertex: ")

# Create graph
G = nx.Graph()
for edge in edges:
    source, target, weight = edge
    G.add_edge(source, target, weight=int(weight))

# Perform Breadth First Search
path = breadth_first_search(G, start_vertex, goal_vertex)

# Draw initial graph
pos = nx.spring_layout(G)
nx.draw(G, pos, with_labels=True, node_size=700, node_color='lightblue', font_size=16, font_weight='bold', edge_color='gray')
edge_labels = nx.get_edge_attributes(G, 'weight')
nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)
plt.title("Initial Graph")
plt.show()

# Display path
if path:
    path_edges = list(zip(path, path[1:]))
    plt.figure(figsize=(10, 7))
    nx.draw(G, pos, with_labels=True, node_size=700, node_color='lightblue', font_size=16, font_weight='bold', edge_color='gray')
    nx.draw_networkx_edges(G, pos, edgelist=path_edges, edge_color='r', width=2)
    nx.draw_networkx_nodes(G, pos, nodelist=path, node_color='lightgreen')
    plt.title("Path Taken")
    plt.show()
else:
    print("No path found.")
