import networkx as nx
import matplotlib.pyplot as plt

# Hill Climbing Search algorithm
def hill_climbing_search(graph, start, goal, heuristic):
    current = start
    path = [current]
    
    while current != goal:
        neighbors = list(graph.neighbors(current))
        
        # If no neighbors exist, return failure
        if not neighbors:
            print("No solution found (local maxima or dead end).")
            return None
        
        # Find neighbor with the best (lowest) heuristic
        next_node = min(neighbors, key=lambda n: heuristic[n])
        
        # If no improvement is possible, stop (local maxima)
        if heuristic[next_node] >= heuristic[current]:
            print("No better neighbors found, stopped at a local maximum.")
            return None
        
        # Move to the next node
        path.append(next_node)
        current = next_node
    
    return path

# Input graph details
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

# Perform Hill Climbing Search
path = hill_climbing_search(G, start_vertex, goal_vertex)

# Draw the initial graph
pos = nx.spring_layout(G)  # Layout for visualizing graph
plt.figure(figsize=(10, 7))
nx.draw(G, pos, with_labels=True, node_size=700, node_color='lightblue', font_size=16, font_weight='bold', edge_color='gray')
edge_labels = nx.get_edge_attributes(G, 'weight')
nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)
plt.title("Initial Graph")
plt.show()

# If a path is found, display the path
if path:
    path_edges = list(zip(path, path[1:]))
    
    # Draw the graph again with the path highlighted
    plt.figure(figsize=(10, 7))
    nx.draw(G, pos, with_labels=True, node_size=700, node_color='lightblue', font_size=16, font_weight='bold', edge_color='gray')
    nx.draw_networkx_edges(G, pos, edgelist=path_edges, edge_color='r', width=2)
    nx.draw_networkx_nodes(G, pos, nodelist=path, node_color='lightgreen')
    plt.title(f"Hill Climbing Path: {path}")
    plt.show()
else:
    print("No path found.")
