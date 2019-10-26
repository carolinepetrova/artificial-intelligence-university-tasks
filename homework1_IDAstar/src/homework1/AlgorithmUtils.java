package homework1;

import java.util.ArrayList;
import java.util.List;

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

    public static List<Move> recreateMovesTo(Node node) {
        List<Move> moves = new ArrayList<>();
        while (node.getPreviousMove().isPresent()) {
            moves.add(node.getPreviousMove().get());
            node = node.getPreviousNode().get();
        }
        return moves;
    }

    public static List<Node> recreateNodesTo(Node node) {
        List<Node> nodes = new ArrayList<>();
        while (node.getPreviousNode().isPresent()) {
            nodes.add(node.getPreviousNode().get());
        }
        return nodes;
    }
}
