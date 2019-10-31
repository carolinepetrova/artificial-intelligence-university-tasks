package homework2;

import org.testng.annotations.Test;

import static org.testng.Assert.assertEquals;

public class Tests {
    public static Board createTestBoard(int size) {
        return new Board(size);
    }

    @Test
    public void testNewlyCreatedBoardHasOneQueenInEachColumn() {
        Board board = createTestBoard(1000);
        for (int col = 0; col < 1000; col++) {
            int numberOfQueensInColumn = 0;
            for (int row = 0; row < 1000; row++) {
                if (board.isPositionOccupiedByQueen(row, col)) {
                    numberOfQueensInColumn++;
                }
            }
            assertEquals(numberOfQueensInColumn, 1);
        }
    }
}
