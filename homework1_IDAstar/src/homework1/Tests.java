package homework1;

import org.junit.jupiter.api.Assertions;
import org.testng.annotations.Test;

import javax.swing.text.html.Option;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import static org.testng.Assert.assertTrue;

public class Tests {

    public static Node createTestInitialNode() {
        List<Tile> grid = new ArrayList<>();

        Tile tile1 = new Tile(new Position(0, 0), 1, 1);
        Tile tile2 = new Tile(new Position(0, 1), 2, 2);
        Tile tile3 = new Tile(new Position(0, 2), 3, 3);
        Tile tile4 = new Tile(new Position(1, 0), 4, 4);
        Tile tile5 = new Tile(new Position(1, 1), 5, 5);
        Tile tile6 = new Tile(new Position(1, 2), 6, 6);
        Tile tile7 = new Tile(new Position(2, 0), 0, 7);
        Tile tile8 = new Tile(new Position(2, 1), 7, 8);
        Tile tile9 = new Tile(new Position(2, 2), 8, 0);

        tile1.setRightTile(Optional.of(tile2));
        tile1.setLowerTile(Optional.of(tile4));

        tile2.setLeftTile(Optional.of(tile1));
        tile2.setRightTile(Optional.of(tile3));
        tile2.setLowerTile(Optional.of(tile5));

        tile3.setLeftTile(Optional.of(tile2));
        tile3.setLowerTile(Optional.of(tile6));

        tile4.setUpperTile(Optional.of(tile1));
        tile4.setLowerTile(Optional.of(tile7));
        tile4.setRightTile(Optional.of(tile5));

        tile5.setUpperTile(Optional.of(tile2));
        tile5.setLowerTile(Optional.of(tile8));
        tile5.setLeftTile(Optional.of(tile4));
        tile5.setRightTile(Optional.of(tile6));

        tile6.setUpperTile(Optional.of(tile3));
        tile6.setUpperTile(Optional.of(tile9));
        tile6.setLeftTile(Optional.of(tile5));

        tile7.setUpperTile(Optional.of(tile4));
        tile7.setRightTile(Optional.of(tile8));

        tile8.setUpperTile(Optional.of(tile5));
        tile8.setLeftTile(Optional.of(tile7));
        tile8.setRightTile(Optional.of(tile9));

        tile9.setUpperTile(Optional.of(tile6));
        tile9.setLeftTile(Optional.of(tile8));

        grid.add(tile1);
        grid.add(tile2);
        grid.add(tile3);
        grid.add(tile4);
        grid.add(tile5);
        grid.add(tile6);
        grid.add(tile7);
        grid.add(tile8);
        grid.add(tile9);

        return new Node(grid, 3);
    }

    public static Node createTestGoalNode() {
        List<Tile> grid = new ArrayList<>();

        Tile tile1 = new Tile(new Position(0, 0), 1, 1);
        Tile tile2 = new Tile(new Position(0, 1), 2, 2);
        Tile tile3 = new Tile(new Position(0, 2), 3, 3);
        Tile tile4 = new Tile(new Position(1, 0), 4, 4);
        Tile tile5 = new Tile(new Position(1, 1), 5, 5);
        Tile tile6 = new Tile(new Position(1, 2), 6, 6);
        Tile tile7 = new Tile(new Position(2, 0), 7, 7);
        Tile tile8 = new Tile(new Position(2, 1), 8, 8);
        Tile tile9 = new Tile(new Position(2, 2), 0, 0);

        tile1.setRightTile(Optional.of(tile2));
        tile1.setLowerTile(Optional.of(tile4));

        tile2.setLeftTile(Optional.of(tile1));
        tile2.setRightTile(Optional.of(tile3));
        tile2.setLowerTile(Optional.of(tile5));

        tile3.setLeftTile(Optional.of(tile2));
        tile3.setLowerTile(Optional.of(tile6));

        tile4.setUpperTile(Optional.of(tile1));
        tile4.setLowerTile(Optional.of(tile7));
        tile4.setRightTile(Optional.of(tile5));

        tile5.setUpperTile(Optional.of(tile2));
        tile5.setLowerTile(Optional.of(tile8));
        tile5.setLeftTile(Optional.of(tile4));
        tile5.setRightTile(Optional.of(tile6));

        tile6.setUpperTile(Optional.of(tile3));
        tile6.setUpperTile(Optional.of(tile9));
        tile6.setLeftTile(Optional.of(tile5));

        tile7.setUpperTile(Optional.of(tile4));
        tile7.setRightTile(Optional.of(tile8));

        tile8.setUpperTile(Optional.of(tile5));
        tile8.setLeftTile(Optional.of(tile7));
        tile8.setRightTile(Optional.of(tile9));

        tile9.setUpperTile(Optional.of(tile6));
        tile9.setLeftTile(Optional.of(tile8));

        grid.add(tile1);
        grid.add(tile2);
        grid.add(tile3);
        grid.add(tile4);
        grid.add(tile5);
        grid.add(tile6);
        grid.add(tile7);
        grid.add(tile8);
        grid.add(tile9);

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
        Node endNode = algorithm.search();
        assertTrue(endNode.isSolution());
    }
}
