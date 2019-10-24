package homework1;

import org.junit.jupiter.api.Assertions;
import org.testng.annotations.Test;

public class Tests {
    @Test
    public void testManhattanDistanceIsCalculatedCorrectly() {
        Tile tileA = new Tile(2, 0);
        Tile tileB = new Tile(0, 2);
        Assertions.assertEquals(4, AlgorithmUtils.calculateManhattanDistance(tileA, tileB));
    }
}
