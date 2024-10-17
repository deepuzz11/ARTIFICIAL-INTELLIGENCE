import networkx as nx
import matplotlib.pyplot as plt

# Function to display the decision tree
def display_decision_tree(G, labels):
    pos = nx.spring_layout(G, seed=42)  # Set a fixed layout for consistent visualization
    plt.figure(figsize=(10, 8))
    nx.draw(G, pos, with_labels=True, node_color='lightblue', node_size=2000, font_size=10, font_weight='bold', arrows=False)
    nx.draw_networkx_edge_labels(G, pos, edge_labels=labels)
    plt.show()

# Alpha-Beta Pruning Algorithm with Tree Construction
def alpha_beta_pruning(depth, node_index, maximizing_player, values, alpha, beta, tree, parent=None):
    if depth == 3:  # Terminal node (leaf node)
        return values[node_index]

    if maximizing_player:
        best = float('-inf')
        for i in range(2):
            child_node = node_index * 2 + i
            if parent is not None:
                tree.add_edge(f'Depth {depth} Node {node_index}', f'Depth {depth+1} Node {child_node}')
            best = max(best, alpha_beta_pruning(depth + 1, child_node, False, values, alpha, beta, tree, f'Depth {depth} Node {node_index}'))
            alpha = max(alpha, best)
            if beta <= alpha:  # Prune
                tree.add_edge(f'Depth {depth} Node {node_index}', f'Pruned Node {depth+1} Node {child_node}')
                break
        return best
    else:
        best = float('inf')
        for i in range(2):
            child_node = node_index * 2 + i
            if parent is not None:
                tree.add_edge(f'Depth {depth} Node {node_index}', f'Depth {depth+1} Node {child_node}')
            best = min(best, alpha_beta_pruning(depth + 1, child_node, True, values, alpha, beta, tree, f'Depth {depth} Node {node_index}'))
            beta = min(beta, best)
            if beta <= alpha:  # Prune
                tree.add_edge(f'Depth {depth} Node {node_index}', f'Pruned Node {depth+1} Node {child_node}')
                break
        return best

def start_alpha_beta_pruning(values):
    tree = nx.DiGraph()  # Directed graph for the decision tree
    root_value = alpha_beta_pruning(0, 0, True, values, float('-inf'), float('inf'), tree, None)
    labels = nx.get_edge_attributes(tree, 'label')
    display_decision_tree(tree, labels)
    return root_value

# Main program for Alpha-Beta Pruning
def main_alpha_beta():
    num_leaves = int(input("Enter the number of leaf nodes (must be a power of 2): "))
    values = []
    for i in range(num_leaves):
        value = int(input(f"Enter value for leaf node {i + 1}: "))
        values.append(value)

    print("\nExecuting Alpha-Beta Pruning Algorithm...")
    optimal_value_ab = start_alpha_beta_pruning(values)
    print(f"The optimal value using Alpha-Beta Pruning is: {optimal_value_ab}")

if __name__ == "__main__":
    main_alpha_beta()
