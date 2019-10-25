package homework1;

public class AlgorithmUtils {
    public static Integer calculateManhattanDistance(Tile tileA, Tile tileB) {
        int manhattanDistance = 0;
        manhattanDistance += Math.abs(tileA.getPosition().getX() - tileB.getPosition().getX());
        manhattanDistance += Math.abs(tileA.getPosition().getY() - tileB.getPosition().getY());
        return manhattanDistance;
    }

    public static Move getReverseMove(Move move) {
        switch (move) {
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
}
