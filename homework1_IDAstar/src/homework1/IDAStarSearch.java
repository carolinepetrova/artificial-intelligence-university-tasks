package homework1;

public class IDAStarSearch {
    private Node initialState;
    private Node goalState;

    public IDAStarSearch(Node initialState, Node goalState) {
        this.initialState = initialState;
        this.goalState = goalState;
    }

    public Node search() {
        return ida_rec(this.initialState, 0, this.initialState.calculateCostToGoalState());
    }

    private Node ida_rec(Node node, int currentCost, int threshold) {
        int estimatedCost = currentCost + node.calculateCostToGoalState();
        if (node.isSolution() || estimatedCost > threshold) {
            node.setEstimatedMinimumCost(estimatedCost);
            return node;
        }

        int minimumCost = Integer.MAX_VALUE;
        for (Move move : Tile.getPossibleMoveDirectionsWithoutReversals(node, node.getBlankTile())) {
            Node childNode = Node.getChildOfNodeAndMove(node, move).get();
            Node childIda = ida_rec(childNode, currentCost + 1, threshold);
            if (childIda.isSolution()) {
                return childIda;
            }
            if (childIda.getEstimatedMinimumCost() < minimumCost) {
                minimumCost = childIda.getEstimatedMinimumCost();
            }
        }
        node.setEstimatedMinimumCost(minimumCost);
        return node;
    }
}
