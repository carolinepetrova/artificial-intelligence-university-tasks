package homework1;

import org.junit.jupiter.api.Assertions;
import org.testng.annotations.Test;

import java.util.ArrayList;
import java.util.List;

import static org.testng.Assert.assertTrue;

public class Tests {

    public static Node createTestInitialNode() {
        List<Tile> grid = new ArrayList<>();
        grid.add(new Tile(new Position(0, 0), 1, 1));
        grid.add(new Tile(new Position(0, 1), 2, 2));
        grid.add(new Tile(new Position(0, 2), 3, 3));
        grid.add(new Tile(new Position(1, 0), 4, 4));
        grid.add(new Tile(new Position(1, 1), 5, 5));
        grid.add(new Tile(new Position(1, 2), 6, 6));
        grid.add(new Tile(new Position(2, 0), 0, 7));
        grid.add(new Tile(new Position(2, 1), 7, 8));
        grid.add(new Tile(new Position(2, 2), 8, 0));

        return new Node(grid, 3);
    }

    public static Node createTestGoalNode() {
        List<Tile> grid = new ArrayList<>();
        grid.add(new Tile(new Position(0, 0), 1, 1));
        grid.add(new Tile(new Position(0, 1), 2, 2));
        grid.add(new Tile(new Position(0, 2), 3, 3));
        grid.add(new Tile(new Position(1, 0), 4, 4));
        grid.add(new Tile(new Position(1, 1), 5, 5));
        grid.add(new Tile(new Position(1, 2), 6, 6));
        grid.add(new Tile(new Position(2, 0), 7, 7));
        grid.add(new Tile(new Position(2, 1), 8, 8));
        grid.add(new Tile(new Position(2, 2), 0, 0));
        return new Node(grid, 3);
    }

    @Test
    public void testManhattanDistanceIsCalculatedCorrectly() {
        Tile tileA = new Tile(2, 0);
        Tile tileB = new Tile(0, 2);
        Assertions.assertEquals(4, AlgorithmUtils.calculateManhattanDistance(tileA, tileB));
    }

    @Test
    public void testIDAStarSearchGeneratesCorrectEndNode() {
        IDAStarSearch algorithm = new IDAStarSearch(Tests.createTestInitialNode());
        assertTrue(algorithm.search().isSolution());
    }
}
