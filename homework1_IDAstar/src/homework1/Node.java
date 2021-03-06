package homework1;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class Node {
    private List<List<Tile>> grid;
    private int size;
    private Optional<Move> previousMove = Optional.empty();
    private Optional<Node> previousNode = Optional.empty();

    public Node(List<List<Tile>> grid, int size) {
        this.size = size;
        this.grid = new ArrayList<>();
        for (List<Tile> row : grid) {
            List<Tile> newRow = new ArrayList<>();
            for (Tile tile : row) {
                newRow.add(new Tile(tile));
            }
            this.grid.add(newRow);
        }
    }

    public List<Move> getPossibleMoveDirectionsWithoutReversals() {
        List<Move> possibleMoves = getPossibleMoveDirections();
        if (getPreviousMove().isPresent()) {
            Move reverseMove = AlgorithmUtils.getReverseMove(getPreviousMove().get());
            possibleMoves.removeIf(move -> move == reverseMove);
        }
        return possibleMoves;
    }

    public List<Move> getPossibleMoveDirections() {
        Position blankTilePosition = getBlankTile().getPosition();

        List<Move> possibleMoveDirections = new ArrayList<>();
        Position up = new Position(blankTilePosition.getX() - 1, blankTilePosition.getY());
        Position down = new Position(blankTilePosition.getX() + 1, blankTilePosition.getY());
        Position right = new Position(blankTilePosition.getX(), blankTilePosition.getY() + 1);
        Position left = new Position(blankTilePosition.getX(), blankTilePosition.getY() - 1);
        if (isInsideGrid(up)) {
            possibleMoveDirections.add(Move.DOWN);
        }
        if (isInsideGrid(down)) {
            possibleMoveDirections.add(Move.UP);
        }
        if (isInsideGrid(right)) {
            possibleMoveDirections.add(Move.LEFT);
        }
        if (isInsideGrid(left)) {
            possibleMoveDirections.add(Move.RIGHT);
        }
        return possibleMoveDirections;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Node node = (Node) o;
        if (size != node.size) return false;

        for (int row = 0; row < size; row++) {
            if (!grid.get(row).equals(node.grid.get(row))) return false;
        }
        return true;
    }

    @Override
    public String toString() {
        String str = "";
        for (List<Tile> row : this.grid) {
            str += row + "\n";
        }

        return str;
    }

    public List<Node> getSuccessors() {
        List<Node> successors = new ArrayList<>();
        for (Move move : getPossibleMoveDirectionsWithoutReversals()) {
            successors.add(getChildAfterMove(move).get());
        }
        return successors;
    }

    public Optional<Node> getChildAfterMove(Move move) {
        if (!isMovePossible(getBlankTile(), move)) {
            return Optional.empty();
        }

        Node childNode = new Node(grid, size);
        childNode.setPreviousMove(Optional.of(move));
        childNode.setPreviousNode(Optional.of(this));
        childNode.doMove(move);
        return Optional.of(childNode);
    }

    private void doMove(Move move) {
        Tile blankTile = getBlankTile();
        Tile tileToMove = getTileToMove(move).get();

        // swap values of blank tile and the moved tile
        int firstTileValue = blankTile.getValue();
        int secondTileValue = tileToMove.getValue();
        tileToMove.setValue(firstTileValue);
        blankTile.setValue(secondTileValue);
    }

    private boolean isMovePossible(Tile blankTile, Move move) {
        return getTileToMove(move).isPresent();
    }

    private Optional<Tile> getTileToMove(Move move) {
        Position blankTilePosition = getBlankTile().getPosition();
        switch (move) {
            case UP: {
                Position lower = new Position(blankTilePosition.getX() + 1, blankTilePosition.getY());
                if (isInsideGrid(lower)) {
                    return Optional.of(getTileFromPosition(lower));
                }
            }
            case DOWN: {
                Position upper = new Position(blankTilePosition.getX() - 1, blankTilePosition.getY());
                if (isInsideGrid(upper)) {
                    return Optional.of(getTileFromPosition(upper));
                }
            }
            case RIGHT: {
                Position left = new Position(blankTilePosition.getX(), blankTilePosition.getY() - 1);
                if (isInsideGrid(left)) {
                    return Optional.of(getTileFromPosition(left));
                }
            }
            case LEFT: {
                Position right = new Position(blankTilePosition.getX(), blankTilePosition.getY() + 1);
                if (isInsideGrid(right)) {
                    return Optional.of(getTileFromPosition(right));
                }
            }
        }
        return Optional.empty();
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
        for (List<Tile> row : grid) {
            Optional<Tile> optBlank = row.stream().filter(tile -> tile.getValue() == 0).findFirst();
            if (optBlank.isPresent()) {
                return optBlank.get();
            }
        }
        return null;
    }

    public boolean isSolution() {
        for (List<Tile> row : grid) {
            if (row.stream().anyMatch(tile -> tile.getTargetValue() != tile.getValue())) {
                return false;
            }
        }
        return true;
    }

    public Integer calculateCostToGoalState() {
        return calculateHeuristicValue();
    }

    //  Since for every tile we are calculating the distance
    //  from the current state to the final one (number of required moves),
    //  the lower the heuristic value the better.
    private Integer calculateHeuristicValue() {
        int heuristicValue = 0;
        for (List<Tile> row : grid) {
            for (Tile tile : row) {
                Tile targetTile = getTileFromTargetValue(tile.getTargetValue()).get();
                heuristicValue += AlgorithmUtils.calculateManhattanDistance(tile, targetTile);
            }
        }
        return heuristicValue;
    }

    public Optional<Tile> getTileFromTargetValue(int targetValue) {
        Optional<Tile> optTile = Optional.empty();
        for (List<Tile> row : grid) {
            optTile = row.stream().filter(tile -> tile.getValue() == targetValue).findFirst();
            if (optTile.isPresent()) {
                break;
            }
        }
        return optTile;
    }

    private Tile getTileFromPosition(Position position) {
        return grid.get(position.getX()).get(position.getY());
    }

    private boolean isInsideGrid(Position position) {
        return 0 <= position.getX() && position.getX() < size &&
                0 <= position.getY() && position.getY() < size;
    }

    private List<Tile> getNeighbors(Tile tile) {
        Position tilePosition = tile.getPosition();
        List<Tile> neighbors = new ArrayList<>();
        Position position1 = new Position(tilePosition.getX() + 1, tilePosition.getY());
        Position position2 = new Position(tilePosition.getX() - 1, tilePosition.getY());
        Position position3 = new Position(tilePosition.getX(), tilePosition.getY() + 1);
        Position position4 = new Position(tilePosition.getX(), tilePosition.getY() - 1);
        if (isInsideGrid(position1)) {
            neighbors.add(getTileFromPosition(position1));
        }
        if (isInsideGrid(position2)) {
            neighbors.add(getTileFromPosition(position2));
        }
        if (isInsideGrid(position3)) {
            neighbors.add(getTileFromPosition(position3));
        }
        if (isInsideGrid(position4)) {
            neighbors.add(getTileFromPosition(position4));
        }
        return neighbors;
    }
}
