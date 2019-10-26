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

    /**
     * Creates 4x4 grid
     */
    public static Node createTestInitialNode3() {
        List<List<Tile>> grid = new ArrayList<>();

        Tile tile1 = new Tile(new Position(0, 0), 4, 1);
        Tile tile2 = new Tile(new Position(0, 1), 10, 2);
        Tile tile3 = new Tile(new Position(0, 2), 15, 3);
        Tile tile4 = new Tile(new Position(0, 3), 9, 4);
        Tile tile5 = new Tile(new Position(1, 0), 6, 5);
        Tile tile6 = new Tile(new Position(1, 1), 2, 6);
        Tile tile7 = new Tile(new Position(1, 2), 5, 7);
        Tile tile8 = new Tile(new Position(1, 3), 3, 8);
        Tile tile9 = new Tile(new Position(2, 0), 7, 9);
        Tile tile10 = new Tile(new Position(2, 1), 14, 10);
        Tile tile11 = new Tile(new Position(2, 2), 1, 11);
        Tile tile12 = new Tile(new Position(2, 3), 8, 12);
        Tile tile13 = new Tile(new Position(3, 0), 12, 13);
        Tile tile14 = new Tile(new Position(3, 1), 13, 14);
        Tile tile15 = new Tile(new Position(3, 2), 11, 15);
        Tile tile16 = new Tile(new Position(3, 3), 0, 0);

        List<Tile> row1 = new ArrayList<>();
        row1.add(tile1);
        row1.add(tile2);
        row1.add(tile3);
        row1.add(tile4);

        List<Tile> row2 = new ArrayList<>();
        row2.add(tile5);
        row2.add(tile6);
        row2.add(tile7);
        row2.add(tile8);


        List<Tile> row3 = new ArrayList<>();
        row3.add(tile9);
        row3.add(tile10);
        row3.add(tile11);
        row3.add(tile12);

        List<Tile> row4 = new ArrayList<>();
        row4.add(tile13);
        row4.add(tile14);
        row4.add(tile15);
        row4.add(tile16);

        grid.add(row1);
        grid.add(row2);
        grid.add(row3);
        grid.add(row4);

        return new Node(grid, 4);
    }

    public static Node createTestInitialNode4() {
        List<List<Tile>> grid = new ArrayList<>();

        Tile tile1 = new Tile(new Position(0, 0), 6, 1);
        Tile tile2 = new Tile(new Position(0, 1), 1, 2);
        Tile tile3 = new Tile(new Position(0, 2), 0, 3);
        Tile tile4 = new Tile(new Position(1, 0), 8, 4);
        Tile tile5 = new Tile(new Position(1, 1), 5, 5);
        Tile tile6 = new Tile(new Position(1, 2), 7, 6);
        Tile tile7 = new Tile(new Position(2, 0), 4, 7);
        Tile tile8 = new Tile(new Position(2, 1), 2, 8);
        Tile tile9 = new Tile(new Position(2, 2), 3, 0);

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

        System.out.println(grid);

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

    @Test
    public void testAlgorithmGeneratesCorrectMoves3() {
        IDAStarSearch algorithm = new IDAStarSearch(Tests.createTestInitialNode3());

//        List<Move> expectedMoves = new ArrayList<>();
//        expectedMoves.add(Move.LEFT);
//        expectedMoves.add(Move.UP);
//        expectedMoves.add(Move.LEFT);

        Optional<List<Move>> optMovesToSolution = algorithm.findMovesToSolution();
        assertTrue(optMovesToSolution.isPresent());
//        assertEquals(optMovesToSolution.get(), expectedMoves);
    }

    @Test
    public void testAlgorithmGeneratesCorrectMoves4() {
        IDAStarSearch algorithm = new IDAStarSearch(Tests.createTestInitialNode4());

//        List<Move> expectedMoves = new ArrayList<>();
//        expectedMoves.add(Move.LEFT);
//        expectedMoves.add(Move.UP);
//        expectedMoves.add(Move.LEFT);

        Optional<List<Move>> optMovesToSolution = algorithm.findMovesToSolution();
        assertTrue(optMovesToSolution.isPresent());
//        assertEquals(optMovesToSolution.get(), expectedMoves);
    }
}
