package homework2;

public enum CellFilling {
    EMPTY(0),
    QUEEN(1);

    private final int value;

    CellFilling(final int newValue) {
        value = newValue;
    }

    public int getValue() {
        return value;
    }
}
