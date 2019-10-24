package homework1;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class Tile {
    private Position position; // x and y coordinates, (x=0, y=0) is top left
    private int value;
    private int targetValue;

    private Optional<Tile> upperTile;
    private Optional<Tile> rightTile;
    private Optional<Tile> lowerTile;
    private Optional<Tile> leftTile;

    public Tile(Position position, int value, int targetValue) {
        this.position = position;
        this.value = value;
        this.targetValue = targetValue;
    }

    public Tile(Tile other) {
        this(other.position, other.value, other.targetValue);
    }

    public static List<Move> getPossibleMoveDirectionsWithoutReversals(Node node, Tile blankTile) {
        List<Move> possibleMoves = Tile.getPossibleMoveDirections(blankTile);
        if (node.getPreviousMove().isPresent()) {
            Move reverseMove = getReverseMove(node.getPreviousMove().get());
            possibleMoves.removeIf(move -> move == reverseMove);
        }
        return possibleMoves;
    }

    private static Move getReverseMove(Move move) {
        Move reverseMove = null;
        switch(move) {
            case UP:
                reverseMove = Move.DOWN;
            case DOWN:
                reverseMove = Move.UP;
            case LEFT:
                reverseMove = Move.RIGHT;
            case RIGHT:
                reverseMove = Move.LEFT;
        }
        return reverseMove;
    }

    // should be called only on the blank tile
    private static List<Move> getPossibleMoveDirections(Tile blankTile) {
        List<Move> possibleMoveDirections = new ArrayList<>();
        if (blankTile.getUpperTile().isPresent()) {
            possibleMoveDirections.add(Move.DOWN);
        }
        if (blankTile.getRightTile().isPresent()) {
            possibleMoveDirections.add(Move.LEFT);
        }
        if (blankTile.getLeftTile().isPresent()) {
            possibleMoveDirections.add(Move.RIGHT);
        }
        if (blankTile.getLowerTile().isPresent()) {
            possibleMoveDirections.add(Move.UP);
        }
        return possibleMoveDirections;
    }

    public Tile(Position position) {
        this.position = position;
    }

    public Tile(int x, int y) {
        this(new Position(x, y));
    }

    public Position getPosition() {
        return position;
    }

    public void setPosition(Position position) {
        this.position = position;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

    public int getTargetValue() {
        return targetValue;
    }

    public void setTargetValue(int targetValue) {
        this.targetValue = targetValue;
    }

    public Optional<Tile> getUpperTile() {
        return upperTile;
    }

    public void setUpperTile(Optional<Tile> upperTile) {
        this.upperTile = upperTile;
    }

    public Optional<Tile> getRightTile() {
        return rightTile;
    }

    public void setRightTile(Optional<Tile> rightTile) {
        this.rightTile = rightTile;
    }

    public Optional<Tile> getLowerTile() {
        return lowerTile;
    }

    public void setLowerTile(Optional<Tile> lowerTile) {
        this.lowerTile = lowerTile;
    }

    public Optional<Tile> getLeftTile() {
        return leftTile;
    }

    public void setLeftTile(Optional<Tile> leftTile) {
        this.leftTile = leftTile;
    }
}
