package homework1;

import javax.swing.text.html.Option;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Optional;

public class Node {
    private List<Tile> grid;
    private int size;
    private Optional<Move> previousMove = Optional.empty();
    private Optional<Node> previousNode = Optional.empty();
    private Integer estimatedMinimumCost = Integer.MAX_VALUE;

    public Node(List<Tile> grid, int size) {
        this.grid = new ArrayList<>();
        for (Tile tile : grid) {
            this.grid.add(new Tile(tile));
        }
        this.size = size;
    }

    public static Optional<Node> getChildOfNodeAndMove(Node node, Move move) {
        if (!isMovePossible(node.getBlankTile(), move)) {
            return Optional.empty();
        }

        Node childNode = new Node(node.grid, node.size);
        childNode.setPreviousMove(Optional.of(move));
        childNode.setPreviousNode(Optional.of(node));

        Tile blankTile = childNode.getBlankTile();
        Tile neighborToSwap = getNeighborToSwap(blankTile, move).get();

        // update information in the node
        int firstTileValue = blankTile.getValue();
        int secondTileValue = neighborToSwap.getValue();
        neighborToSwap.setValue(firstTileValue);
        blankTile.setValue(secondTileValue);

        return Optional.of(childNode);
    }

    private static boolean isMovePossible(Tile blankTile, Move move) {
        return getNeighborToSwap(blankTile, move).isPresent();
    }

    private static Optional<Tile> getNeighborToSwap(Tile blankTile, Move move) {
        Optional<Tile> neighborToSwap = Optional.empty();
        switch (move) {
            case UP:
                neighborToSwap = blankTile.getLowerTile();
                break;
            case DOWN:
                neighborToSwap = blankTile.getUpperTile();
                break;
            case RIGHT:
                neighborToSwap = blankTile.getLeftTile();
                break;
            case LEFT:
                neighborToSwap = blankTile.getRightTile();
                break;
        }
        return neighborToSwap;
    }

    public Integer getEstimatedMinimumCost() {
        return estimatedMinimumCost;
    }

    public void setEstimatedMinimumCost(Integer estimatedMinimumCost) {
        this.estimatedMinimumCost = estimatedMinimumCost;
    }

    public Optional<Move> getPreviousMove() {
        return previousMove;
    }

    public void setPreviousMove(Optional<Move> previousMove) {
        this.previousMove = previousMove;
    }

    public Optional<Node> getPreviousNode() {
        return previousNode;
    }

    public void setPreviousNode(Optional<Node> previousNode) {
        this.previousNode = previousNode;
    }

    public Tile getBlankTile() {
        return grid.stream().filter(tile -> tile.getValue() == 0).findFirst().get();
    }

    public boolean isSolution() {
        return grid.stream().allMatch(tile -> tile.getTargetValue() == tile.getValue());
    }

    public Integer calculateCostToGoalState() {
        return calculateHeuristicValue();
    }

//  Since for every tile we are calculating the distance
//  from the current state to the final one (number of required moves),
//  the lower the heuristic value the better.
    private Integer calculateHeuristicValue() {
        int heuristicValue = 0;
        for(Tile tile: grid) {
            Tile targetTile = getTileFromTargetValue(tile.getTargetValue()).get();
            heuristicValue += AlgorithmUtils.calculateManhattanDistance(tile, targetTile);
        }
        return heuristicValue;
    }

    public Optional<Tile> getTileFromTargetValue(int targetValue) {
        return grid.stream().filter(tile -> tile.getTargetValue() == targetValue).findFirst();
    }

    private List<Move> recreatePathFrom(Node node) {
        List<Move> moves = getMovesFrom(node, new ArrayList<>());
        Collections.reverse(moves);
        return moves;
    }

    private List<Move> getMovesFrom(Node node, List<Move> moves) {
        if(node.previousMove.isPresent()) {
            moves.add(node.previousMove.get());
            return getMovesFrom(node.previousNode.get(), moves);
        } else {
            return moves;
        }
    }
}
