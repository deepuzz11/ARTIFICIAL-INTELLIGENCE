# Minimax algorithm with table visualization
def minimax(depth, nodeIndex, maximizingPlayer, values, path):
    if depth == max_depth:
        print(f"{' | '.join(path)} | Leaf node reached with value: {values[nodeIndex]}")
        return values[nodeIndex]

    if maximizingPlayer:
        best = float('-inf')
        print(f"{' | '.join(path)} | Maximizing player at depth {depth}, node {nodeIndex}")
        for i in range(2):
            val = minimax(depth + 1, nodeIndex * 2 + i, False, values, path + [f"Node {nodeIndex * 2 + i}"])
            best = max(best, val)
        print(f"{' | '.join(path)} | Maximizing player best at depth {depth} is {best}")
        return best
    else:
        best = float('inf')
        print(f"{' | '.join(path)} | Minimizing player at depth {depth}, node {nodeIndex}")
        for i in range(2):
            val = minimax(depth + 1, nodeIndex * 2 + i, True, values, path + [f"Node {nodeIndex * 2 + i}"])
            best = min(best, val)
        print(f"{' | '.join(path)} | Minimizing player best at depth {depth} is {best}")
        return best

# Driver code for Minimax
if __name__ == "__main__":
    # Taking input from user
    num_leaves = int(input("Enter the number of leaf nodes (must be a power of 2): "))
    values = []
    
    for i in range(num_leaves):
        val = int(input(f"Enter value for leaf node {i+1}: "))
        values.append(val)

    max_depth = (num_leaves.bit_length() - 1)  # Calculate tree depth from number of leaves

    # Print table header for better visualization
    print("\nTable of Decisions (Minimax):")
    print("-" * 50)
    print("Node Path | Decision Process")
    print("-" * 50)

    # Call the minimax function
    optimal_value = minimax(0, 0, True, values, ["Root"])
    print("\nThe optimal value is:", optimal_value)
