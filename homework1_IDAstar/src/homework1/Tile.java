package homework1;

import java.util.Objects;

public class Tile {
    private Position position; // x and y coordinates, (x=0, y=0) is top left
    private int value;
    private int targetValue;

    public Tile(Position position, int value, int targetValue) {
        this.position = position;
        this.value = value;
        this.targetValue = targetValue;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Tile tile = (Tile) o;
        return value == tile.value &&
                targetValue == tile.targetValue &&
                Objects.equals(position, tile.position);
    }

    @Override
    public String toString() {
        return String.valueOf(value);
    }

    public Tile(Position position) {
        this.position = position;
    }

    public Tile(int x, int y) {
        this(new Position(x, y));
    }

    public Tile(Tile other) {
        this(other.position, other.value, other.targetValue);
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
}
