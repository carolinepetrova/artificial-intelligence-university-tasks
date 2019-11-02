package homework2;

import java.io.PrintStream;
import java.util.ArrayList;
import java.util.concurrent.ThreadLocalRandom;

public class Board {
    // [2,1,3,0] represents that on the 1st column the queen is at 2nd row,
    // on the 2nd column the queen is at 1st row and so on...
    private int[] cols;

    // Creates n x n board with randomly placed queens in each column
    public Board(int n) {
        cols = new int[n];
        shuffle();
    }

    /**
     * Fills the board with a legal arrangement of queens.
     */
    void solve() {
        int moves = 0;

        // This would be a lot faster if we used arrays of ints instead.
        ArrayList<Integer> candidates = new ArrayList<Integer>();

        while (true) {
            // Find nastiest queen
            int maxConflicts = 0;
            candidates.clear();
            for (int col = 0; col < cols.length; col++) {
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
            int worstQueenColumn =
                    candidates.get(ThreadLocalRandom.current().nextInt(candidates.size()));

            // Move her to the place with the least conflicts.
            int minNumberOfConflicts = cols.length;
            candidates.clear();
            for (int row = 0; row < cols.length; row++) {
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
                cols[worstQueenColumn] =
                        candidates.get(ThreadLocalRandom.current().nextInt(candidates.size()));
            }

            moves++;
            if (moves == cols.length * 2) {
                // Trying too long... start over.
                shuffle();
                moves = 0;
            }
        }
    }

    public boolean isPositionOccupiedByQueen(int row, int col) {
        return cols[col] == row;
    }

    // Returns the number of queens that conflict with (row,col), not
    // counting the queen in column col.
    public int numberOfConflicts(int row, int col) {
        int numberOfConflicts = 0;
        for (int c = 0; c < cols.length; c++) {
            if (c == col) continue;
            int r = cols[c];
            if (r == row || Math.abs(r - row) == Math.abs(c - col)) numberOfConflicts++;
        }
        return numberOfConflicts;
    }

    // Randomly fills the board with one queen in each column.
    private void shuffle() {
        for (int col = 0; col < cols.length; col++) {
            // nextInt is normally exclusive of the top value,
            // so no need to subtract 1 from size
            int randomRow = ThreadLocalRandom.current().nextInt(0, cols.length);
            cols[col] = randomRow;
        }
    }

    /**
     * Prints the board, crudely, to a print stream.
     */
    void print(PrintStream stream) {
        for (int row = 0; row < cols.length; row++) {
            for (int col = 0; col < cols.length; col++) {
                stream.print(isPositionOccupiedByQueen(row, col) ? 'Q' : '.');
            }
            stream.println();
        }
    }

    public static void main(String[] args) {
        Board board = new Board(1000);
        long start = System.currentTimeMillis();
        board.solve();
        long stop = System.currentTimeMillis();
        System.out.println("Found in " + ((double)(stop-start))/1000 + "s.");
//        board.print(System.out);
    }
}
