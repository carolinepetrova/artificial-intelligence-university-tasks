package homework1;

import javax.swing.text.html.Option;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Optional;

public class BoardState {
    private List<Tile> grid = new ArrayList<>();
    private Optional<ShiftDirection> previousMove;
    private Optional<BoardState> previousBoardState;
    private Integer estimatedMinimumCost = Integer.MAX_VALUE;

    public boolean isSolution() {
        return true;
    }

    private Integer countManhattanDistance(Tile tileA, Tile tileB) {
        int manhattanDistance = 0;
        manhattanDistance += Math.abs(tileA.getPosition().getX() - tileB.getPosition().getX());
        manhattanDistance += Math.abs(tileA.getPosition().getY() - tileB.getPosition().getY());
        return manhattanDistance;
    }

    private List<ShiftDirection> recreatePathFrom(BoardState boardState) {
        List<ShiftDirection> moves = getMovesFrom(boardState, new ArrayList<>());
        Collections.reverse(moves);
        return moves;
    }

    private List<ShiftDirection> getMovesFrom(BoardState boardState, List<ShiftDirection> moves) {
        if(boardState.previousMove.isPresent()) {
            moves.add(boardState.previousMove.get());
            return getMovesFrom(boardState.previousBoardState.get(), moves);
        } else {
            return moves;
        }
    }
}
