import networkx as nx
import matplotlib.pyplot as plt

def create_Graph():
    n = int(input("Enter number of nodes: "))
    nodes = []
    Heuristic = {}

    G = nx.DiGraph()

    for i in range(n):
        node = input(f'Enter node {i+1}: ')
        nodes.append(node)

    start = input('Enter Starting node: ')
    goal = input('Enter Goal node: ')

    for i in range(n):
        neighbours = int(input(f"Enter number of neighbours of {nodes[i]}: "))
        for j in range(neighbours):
            neighbour = input(f"Enter neighbour {j+1}: ")
            G.add_edge(nodes[i], neighbour)

    for node in nodes:
        if node == goal:
            Heuristic.update({goal: 0})
        else:
            h = int(input(f"Enter Heuristic from {node} to {goal}: "))
            Heuristic.update({node: h})

    return G, start, goal, Heuristic

G, start, goal, Heuristic = create_Graph()

nx.draw(G, with_labels=True, node_size=1000, node_color='purple', font_size=10, pos=nx.circular_layout(G))
plt.show()

def beam_search(graph, start, goal, beam_width, heuristic):
    initial_path = [start]
    beam = [(initial_path, heuristic[start])]
    beam_paths = []

    while beam:
        candidates = []
        for path, cost in beam:
            current_node = path[-1]
            for neighbour in graph.neighbors(current_node):
                if neighbour not in path:
                    new_path = path + [neighbour]
                    new_cost = heuristic[neighbour]
                    candidates.append((new_path, new_cost))

        candidates.sort(key=lambda x: x[1])
        beam = candidates[:beam_width]

        for path, cost in beam:
            if path[-1] == goal:
                return path

    return None

width = int(input("Enter beam width: "))

beam_path = beam_search(G, start, goal, width, Heuristic)

if beam_path:
    edges_in_beam_path = [(beam_path[i], beam_path[i+1]) for i in range(len(beam_path) - 1)]

    pos = nx.circular_layout(G)

    node_labels = {node: node for node in G.nodes()}
    nx.draw(G, pos, node_size=1000, node_color='purple', font_size=10)
    nx.draw_networkx_labels(G, pos, labels=node_labels, font_size=10)
    nx.draw_networkx_edges(G, pos, edgelist=edges_in_beam_path, edge_color='orange', width=2)
    plt.title("Beam Search Visualization")
    plt.show()
else:
    print("No path found")
