import networkx as nx
import matplotlib.pyplot as plt
import heapq

# Branch and Bound with Extended Lists (Dead Horse Principle)
def branch_and_bound_extended(graph, start, goal):
    frontier = [(0, start, [start])]
    visited = set()
    extended_lists = {}

    while frontier:
        cost, node, path = heapq.heappop(frontier)

        if node == goal:
            return path
        
        visited.add(node)
        
        if node not in extended_lists:
            extended_lists[node] = []
        
        for neighbor in graph.neighbors(node):
            if neighbor not in visited and neighbor not in extended_lists[node]:
                edge_cost = graph[node][neighbor]['weight']
                extended_lists[node].append(neighbor)
                heapq.heappush(frontier, (cost + edge_cost, neighbor, path + [neighbor]))

    print("No path found.")
    return None

# Input graph details
num_vertices = int(input("Enter the number of vertices: "))
edges = []
for _ in range(int(input("Enter the number of edges: "))):
    edge = input("Enter edge (format: source target weight): ").split()
    edges.append((edge[0], edge[1], int(edge[2])))

start_vertex = input("Enter the start vertex: ")
goal_vertex = input("Enter the goal vertex: ")

# Create a weighted graph using networkx
G = nx.Graph()
for edge in edges:
    G.add_edge(edge[0], edge[1], weight=edge[2])

# Perform Branch and Bound with Extended Lists
path = branch_and_bound_extended(G, start_vertex, goal_vertex)

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
    plt.title(f"Branch and Bound with Extended Lists Path: {path}")
    plt.show()
else:
    print("No path found.")
