import networkx as nx
import matplotlib.pyplot as plt

# Beam Search algorithm
def beam_search(graph, start, goal, heuristic, beam_width):
    current_level = [(start, [start])]
    
    while current_level:
        next_level = []
        for node, path in current_level:
            if node == goal:
                return path
            
            neighbors = list(graph.neighbors(node))
            
            # Sort neighbors by heuristic and keep top `beam_width` candidates
            best_neighbors = sorted(neighbors, key=lambda n: heuristic[n])[:beam_width]
            
            for neighbor in best_neighbors:
                if neighbor not in path:  # Prevent cycles
                    next_level.append((neighbor, path + [neighbor]))
        
        if not next_level:
            print("No path found.")
            return None
        current_level = next_level
    
    print("No solution found.")
    return None

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
beam_width = int(input("Enter the beam width: "))

# Create a weighted graph using networkx
G = nx.Graph()
for edge in edges:
    G.add_edge(edge[0], edge[1], weight=edge[2])

# Perform Beam Search
path = beam_search(G, start_vertex, goal_vertex, heuristic, beam_width)

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
    plt.title(f"Beam Search Path: {path}")
    plt.show()
else:
    print("No path found.")
