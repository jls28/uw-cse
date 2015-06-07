package hw8.test;
import hw5.Edge;
import hw8.PixelPoint;
import org.junit.Test;
import org.junit.rules.ExpectedException;
import static org.hamcrest.CoreMatchers.not;
import static org.junit.Assert.*;

/**
 * Tests for PixelPoint
 */
public class PixelPointTest {

  @Test
  public void testInstantiation() {
    PixelPoint p = new PixelPoint(1.0, 1.0);
  }

  @Test
  public void testCompareToLess() {
    PixelPoint small = new PixelPoint(1.0, 1.0);
    PixelPoint big = new PixelPoint(4.0, 4.0);
    assertEquals(small.compareTo(big), -1);
  }

  @Test
  public void testCompareToGreater() {
    PixelPoint small = new PixelPoint(1.0, 1.0);
    PixelPoint big = new PixelPoint(4.0, 4.0);
    assertEquals(big.compareTo(small), 1);
  }
}
