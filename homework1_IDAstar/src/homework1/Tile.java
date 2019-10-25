package homework1;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class Tile {
    private Position position; // x and y coordinates, (x=0, y=0) is top left
    private int value;
    private int targetValue;

    private Optional<Tile> upperTile = Optional.empty();
    private Optional<Tile> rightTile = Optional.empty();
    private Optional<Tile> lowerTile = Optional.empty();
    private Optional<Tile> leftTile = Optional.empty();

    public Tile(Position position, int value, int targetValue) {
        this.position = position;
        this.value = value;
        this.targetValue = targetValue;
    }

    public Tile(Position position) {
        this.position = position;
    }

    public Tile(int x, int y) {
        this(new Position(x, y));
    }

    public Tile(Tile other) {
        this(other.position, other.value, other.targetValue);
        this.upperTile = other.upperTile;
        this.leftTile = other.leftTile;
        this.rightTile = other.rightTile;
        this.lowerTile = other.lowerTile;
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
        switch(move) {
            case UP:
                return Move.DOWN;
            case DOWN:
                return Move.UP;
            case LEFT:
                return Move.RIGHT;
            case RIGHT:
                return Move.LEFT;
            default:
                return null;
        }
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
