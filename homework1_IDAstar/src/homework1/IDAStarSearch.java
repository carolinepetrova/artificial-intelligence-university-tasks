package homework1;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class IDAStarSearch {
    private Node initialState;

    public IDAStarSearch(Node initialState) {
        this.initialState = initialState;
    }

    public Optional<List<Move>> findMovesToSolution() {
        Optional<Node> goalState = reachGoalState();
        if (goalState.isPresent()) {
            return Optional.of(AlgorithmUtils.recreateMovesTo(goalState.get()));
        }
        return Optional.empty();
    }

    private Optional<Node> reachGoalState() {
        List<Node> path = new ArrayList<>();
        path.add(initialState);
        int threshold = initialState.calculateCostToGoalState();
        int algorithm_result;

        do {
            algorithm_result = ida_rec(path, 0, threshold);

            final boolean goalIsFound = algorithm_result == 0;
            if (goalIsFound) {
                return Optional.of(path.get(path.size() - 1));
            }

            // set new threshold
            threshold = algorithm_result;
        } while (threshold != Integer.MAX_VALUE);

        return Optional.empty();
    }

    /**
     * @return 0 if goal is found; otherwise the minimum cost of all values that exceeded the current threshold
     */
    private int ida_rec(List<Node> currentPath, int currentCost, int threshold) {
        Node node = currentPath.get(currentPath.size() - 1);
        int estimatedCost = currentCost + node.calculateCostToGoalState();
        if (estimatedCost > threshold) {
            return estimatedCost;
        }
        if (node.isSolution()) {
            return 0;
        }

        int minimumCost = Integer.MAX_VALUE;
        for (Node successor : node.getSuccessors()) {
            if (!currentPath.contains(successor)) {
                currentPath.add(successor);
                int successorIda = ida_rec(currentPath, currentCost, threshold);
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
