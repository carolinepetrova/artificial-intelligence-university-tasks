package homework2;

import java.util.ArrayList;
import java.util.concurrent.ThreadLocalRandom;

public class Board {
    private int size;

    // [2,1,3,0] represents that on the 1st column the queen is at 2nd row,
    // on the 2nd column the queen is at 1st row and so on...
    private int[] cols;
    private int[] queensInRow;
    private int[] queensInMainDiagonal;
    private int[] queensInSecondaryDiagonal;

    // Creates n x n board with randomly placed queens in each column
    public Board(int n) {
        cols = new int[n];
        size = n;
        queensInRow = new int[n];
        queensInMainDiagonal = new int[2 * n - 1];
        queensInSecondaryDiagonal = new int[2 * n - 1];
        shuffle();
    }

    // Randomly fills the board with one queen in each column.
    private void shuffle() {
        for (int i = 0; i < 2 * size - 1; i++) {
            queensInMainDiagonal[i] = 0;
            queensInSecondaryDiagonal[i] = 0;

            if (i < size) {
                queensInRow[i] = 0;
            }
        }

        for (int i = 0; i < size; i++) {
            cols[i] = ThreadLocalRandom.current().nextInt(0, size);
            queensInRow[cols[i]] += 1;
            addToMainDiagonal(cols[i], i, 1);
            addToSecondaryDiagonal(cols[i], i, 1);
        }
    }

    private void addToMainDiagonal(int row, int col, int value) {
        if (row <= col) {
            queensInMainDiagonal[(size - 1) - Math.abs(row - col)] += value;
        } else {
            queensInMainDiagonal[(size - 1) + Math.abs(row - col)] += value;
        }
    }

    private void addToSecondaryDiagonal(int row, int col, int value) {
        queensInSecondaryDiagonal[row + col] += value;
    }

    // Returns the number of queens that conflict with (row,col), not
    // counting the queen in column col.
    private int numberOfConflicts(int row, int col) {
        int fix = 0; // we will count 3 additional conflicts if we are on a queen - those should be subtracted
        if (isPositionOccupiedByQueen(row, col)) {
            fix = 3;
        }

        int mainDiagonalIndex;
        if (row <= col) {
            mainDiagonalIndex = (size - 1) - Math.abs(row - col);
        } else {
            mainDiagonalIndex = (size - 1) + Math.abs(row - col);
        }

        int secondaryDiagonalIndex = row + col;

        return queensInRow[row] + queensInMainDiagonal[mainDiagonalIndex] + queensInSecondaryDiagonal[secondaryDiagonalIndex] - fix;
    }

    void solve() {
        int moves = 0;

        ArrayList<Integer> candidates = new ArrayList<Integer>();

        while (true) {
            // Find nastiest queen
            int maxConflicts = 0;
            candidates.clear();
            for (int col = 0; col < size; col++) {
                int numberOfConflicts = numberOfConflicts(cols[col], col);
                if (numberOfConflicts == maxConflicts) {
                    candidates.add(col);
                } else if (numberOfConflicts > maxConflicts) {
                    maxConflicts = numberOfConflicts;
                    candidates.clear();
                    candidates.add(col);
                }
            }

            if (maxConflicts == 0) {
                // Checked every queen and found no conflicts
                return;
            }

            // Pick a random queen from those that had the most conflicts
            int worstQueenColumn = candidates.get(ThreadLocalRandom.current().nextInt(0, candidates.size()));
            candidates.clear();

            // Move her to the place with the least conflicts.
            int minNumberOfConflicts = size;
            for (int row = 0; row < size; row++) {
                int numberOfConflicts = numberOfConflicts(row, worstQueenColumn);
                if (numberOfConflicts == minNumberOfConflicts) {
                    candidates.add(row);
                } else if (numberOfConflicts < minNumberOfConflicts) {
                    minNumberOfConflicts = numberOfConflicts;
                    candidates.clear();
                    candidates.add(row);
                }
            }

            if (!candidates.isEmpty()) {
                int oldRow = cols[worstQueenColumn];
                int newRow = candidates.get(ThreadLocalRandom.current().nextInt(0, candidates.size()));
                if (newRow != oldRow) {
                    cols[worstQueenColumn] = newRow;
                    queensInRow[oldRow] -= 1;
                    queensInRow[newRow] += 1;
                    addToMainDiagonal(oldRow, worstQueenColumn, -1);
                    addToMainDiagonal(newRow, worstQueenColumn, 1);
                    addToSecondaryDiagonal(oldRow, worstQueenColumn, -1);
                    addToSecondaryDiagonal(newRow, worstQueenColumn, 1);
                }
            }

            moves++;
            if (moves == size * 2) {
                // Trying too long... start over.
                shuffle();
                moves = 0;
            }
        }
    }

    public boolean isPositionOccupiedByQueen(int row, int col) {
        return cols[col] == row;
    }

    @Override
    public String toString() {
        StringBuilder str = new StringBuilder();
        for (int row = 0; row < size; row++) {
            for (int col = 0; col < size; col++) {
                str.append(isPositionOccupiedByQueen(row, col) ? "Q\t" : ".\t");
            }
            str.append('\n');
        }
        return str.toString();
    }

    public boolean isSolved() {
        for (int row = 0; row < size; row++) {
            for (int col = 0; col < size; col++) {
                int numConflicts = numberOfConflicts(row, col);
                if (isPositionOccupiedByQueen(row, col) && numConflicts > 0) {
                    return false;
                }
            }
        }
        return true;
    }

    public static void main(String[] args) {
        Board board = new Board(10000);
        long start = System.currentTimeMillis();
        board.solve();
        long stop = System.currentTimeMillis();
        System.out.println("Solution found in " + ((double) (stop - start)) / 1000 + "s.");
    }
}
