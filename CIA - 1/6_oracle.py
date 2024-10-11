import networkx as nx
import matplotlib.pyplot as plt

# Oracle algorithm (direct knowledge of the best path)
def oracle_search(graph, start, goal, predefined_path):
    if predefined_path[0] == start and predefined_path[-1] == goal:
        return predefined_path
    else:
        print("Predefined path doesn't match the search goal.")
        return None

# Input graph details and predefined path
num_vertices = int(input("Enter the number of vertices: "))
edges = []
for _ in range(int(input("Enter the number of edges: "))):
    edge = input("Enter edge (format: source target weight): ").split()
    edges.append((edge[0], edge[1], int(edge[2])))

start_vertex = input("Enter the start vertex: ")
goal_vertex = input("Enter the goal vertex: ")
predefined_path = input("Enter predefined path as space-separated vertices: ").split()

# Create a weighted graph using networkx
G = nx.Graph()
for edge in edges:
    G.add_edge(edge[0], edge[1], weight=edge[2])

# Perform Oracle Search
path = oracle_search(G, start_vertex, goal_vertex, predefined_path)

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
    plt.title(f"Oracle Path: {path}")
    plt.show()
else:
    print("No path found.")
