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


//  Since for every tile we are calculating the distance
//  from the current state to the final one (number of required moves),
//  the lower the heuristic value the better.
    public Integer calculateHeuristicValue() {
        int heuristicValue = 0;
        for(Tile tile: grid) {
            Tile targetTile = getTileFromTargetValue(tile.getTargetValue()).get();
            heuristicValue += AlgorithmUtils.calculateManhattanDistance(tile, targetTile);
        }
        return heuristicValue;
    }

    public Optional<Tile> getTileFromTargetValue(int targetValue) {
        return grid.stream().filter(tile -> tile.getTargetValue() == targetValue).findFirst();
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
