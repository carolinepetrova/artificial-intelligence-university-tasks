package homework1;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class IDAStarSearch {
    private Node initialState;

    public IDAStarSearch(Node initialState) {
        this.initialState = initialState;
    }

    public Node search() {
        int initialThreshold = initialState.calculateCostToGoalState();
        List<Node> path = new ArrayList<>();
        Set<Node> visited = new HashSet<>();
        path.add(initialState);
        visited.add(initialState);

        // Keep Retrying With Larger F Bound Until One Of The Follow:
        // 0 Is Returned     - The Goal Node Is Found So Path Contains Optimal Path
        // Integer.MAX_Value - No Node Was Found With A F Higher Than F Boundary So Goal Node Does Not Exist
        int smallestEstimatedCost;
        do {
            // Start Search
            smallestEstimatedCost = ida_rec(path, visited, 0, initialThreshold);

            // Check If Goal Node Was Found
            if (smallestEstimatedCost == 0) {
                return path.get(path.size() - 1);
            }

            // Set New F Boundary
            initialThreshold = smallestEstimatedCost;
        } while (initialThreshold != Integer.MAX_VALUE);

        return null;
    }

    private int ida_rec(List<Node> currentPath, Set<Node> visited, int currentCost, int threshold) {
        Node node = currentPath.get(currentPath.size() - 1);
        System.out.println("GRID:\n" + node + "------------------------------\n");
        int estimatedCost = currentCost + node.calculateCostToGoalState();
        if (estimatedCost > threshold) {
            return estimatedCost;
        }
        if (node.isSolution()) {
            return 0;
        }

        int minimumCost = Integer.MAX_VALUE;
        for (Node successor : node.getSuccessors()) {
            if (!visited.contains(successor)) {
                visited.add(successor);
                currentPath.add(successor);
                int successorIda = ida_rec(currentPath, visited, currentCost, threshold);
                if (successorIda == 0) {
                    return 0; // goal is found
                }
                if (successorIda < minimumCost) {
                    minimumCost = successorIda;
                }

                // remove successor from path before exploring next successor
                currentPath.remove(currentPath.size() - 1);
            }
        }
        return minimumCost;
    }
}
