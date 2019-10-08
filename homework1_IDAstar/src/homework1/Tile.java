package homework1;

import java.util.Optional;

public class Tile {
    private Position position; // x and y coordinates, (x=0, y=0) is top left
    private int value;
    private int targetValue;

    private Optional<Tile> upperTile;
    private Optional<Tile> rightTile;
    private Optional<Tile> lowerTile;
    private Optional<Tile> leftTile;

    public Tile(Position position,
                int value,
                int targetValue, Optional<Tile> upperTile,
                Optional<Tile> rightTile,
                Optional<Tile> lowerTile,
                Optional<Tile> leftTile) {
        this.position = position;
        this.value = value;
        this.targetValue = targetValue;
        this.upperTile = upperTile;
        this.rightTile = rightTile;
        this.lowerTile = lowerTile;
        this.leftTile = leftTile;
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
