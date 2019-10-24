package homework1;

public class AlgorithmUtils {
    public static Integer calculateManhattanDistance(Tile tileA, Tile tileB) {
        int manhattanDistance = 0;
        manhattanDistance += Math.abs(tileA.getPosition().getX() - tileB.getPosition().getX());
        manhattanDistance += Math.abs(tileA.getPosition().getY() - tileB.getPosition().getY());
        return manhattanDistance;
    }
}
