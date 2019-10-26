package homework1;

import org.junit.jupiter.api.Assertions;
import org.testng.annotations.Test;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import static org.testng.Assert.assertEquals;
import static org.testng.Assert.assertTrue;

public class Tests {

    /**
     * Creates
     * 1 2 3
     * 4 5 6
     * 0 7 8
     * <p>
     * Expected solution is LEFT LEFT
     */
    public static Node createTestInitialNode1() {
        List<List<Tile>> grid = new ArrayList<>();

        Tile tile1 = new Tile(new Position(0, 0), 1, 1);
        Tile tile2 = new Tile(new Position(0, 1), 2, 2);
        Tile tile3 = new Tile(new Position(0, 2), 3, 3);
        Tile tile4 = new Tile(new Position(1, 0), 4, 4);
        Tile tile5 = new Tile(new Position(1, 1), 5, 5);
        Tile tile6 = new Tile(new Position(1, 2), 6, 6);
        Tile tile7 = new Tile(new Position(2, 0), 0, 7);
        Tile tile8 = new Tile(new Position(2, 1), 7, 8);
        Tile tile9 = new Tile(new Position(2, 2), 8, 0);

        List<Tile> row1 = new ArrayList<>();
        row1.add(tile1);
        row1.add(tile2);
        row1.add(tile3);

        List<Tile> row2 = new ArrayList<>();
        row2.add(tile4);
        row2.add(tile5);
        row2.add(tile6);

        List<Tile> row3 = new ArrayList<>();
        row3.add(tile7);
        row3.add(tile8);
        row3.add(tile9);

        grid.add(row1);
        grid.add(row2);
        grid.add(row3);

        return new Node(grid, 3);
    }

    /**
     * Creates
     * 1 2 3
     * 0 4 6
     * 7 5 8
     * <p>
     * Expected solution is LEFT UP LEFT
     */
    public static Node createTestInitialNode2() {
        List<List<Tile>> grid = new ArrayList<>();

        Tile tile1 = new Tile(new Position(0, 0), 1, 1);
        Tile tile2 = new Tile(new Position(0, 1), 2, 2);
        Tile tile3 = new Tile(new Position(0, 2), 3, 3);
        Tile tile4 = new Tile(new Position(1, 0), 0, 4);
        Tile tile5 = new Tile(new Position(1, 1), 4, 5);
        Tile tile6 = new Tile(new Position(1, 2), 6, 6);
        Tile tile7 = new Tile(new Position(2, 0), 7, 7);
        Tile tile8 = new Tile(new Position(2, 1), 5, 8);
        Tile tile9 = new Tile(new Position(2, 2), 8, 0);

        List<Tile> row1 = new ArrayList<>();
        row1.add(tile1);
        row1.add(tile2);
        row1.add(tile3);

        List<Tile> row2 = new ArrayList<>();
        row2.add(tile4);
        row2.add(tile5);
        row2.add(tile6);

        List<Tile> row3 = new ArrayList<>();
        row3.add(tile7);
        row3.add(tile8);
        row3.add(tile9);

        grid.add(row1);
        grid.add(row2);
        grid.add(row3);

        return new Node(grid, 3);
    }

    @Test
    public void testManhattanDistanceIsCalculatedCorrectly() {
        Tile tileA = new Tile(2, 0);
        Tile tileB = new Tile(0, 2);
        Assertions.assertEquals(4, AlgorithmUtils.calculateManhattanDistance(tileA, tileB));
    }

    @Test
    public void testAlgorithmGeneratesCorrectMoves1() {
        IDAStarSearch algorithm = new IDAStarSearch(Tests.createTestInitialNode1());

        List<Move> expectedMoves = new ArrayList<>();
        expectedMoves.add(Move.LEFT);
        expectedMoves.add(Move.LEFT);

        Optional<List<Move>> optMovesToSolution = algorithm.findMovesToSolution();
        assertTrue(optMovesToSolution.isPresent());
        assertEquals(optMovesToSolution.get(), expectedMoves);
    }

    @Test
    public void testAlgorithmGeneratesCorrectMoves2() {
        IDAStarSearch algorithm = new IDAStarSearch(Tests.createTestInitialNode2());

        List<Move> expectedMoves = new ArrayList<>();
        expectedMoves.add(Move.LEFT);
        expectedMoves.add(Move.UP);
        expectedMoves.add(Move.LEFT);

        Optional<List<Move>> optMovesToSolution = algorithm.findMovesToSolution();
        assertTrue(optMovesToSolution.isPresent());
        assertEquals(optMovesToSolution.get(), expectedMoves);
    }
}
