package hw5.test;

import hw5.Edge;
import org.junit.Test;
import org.junit.rules.ExpectedException;
import static org.hamcrest.CoreMatchers.not;
import static org.junit.Assert.*;

/**
 * Created by Stefan Dierauf on 10/22/14.
 */
public class EdgeTest {

  private final String p1 = "parent";
  private final String c1 = "child";
  private final String c2 = "child2";
  private final Edge<String, String> edge = new Edge<String, String>(c1, "edge to child one");
  private final Edge<String, String> edge_copy = new Edge<String, String>(c1, "edge to child one");
  private final Edge<String, String> edge_trans = new Edge<String, String>(c1, "edge to child one");

  public ExpectedException exception = ExpectedException.none();

  //dest and data const
  @Test
  public void fullParamsTest() {
    Edge<String, String> e1 = new Edge<String, String>(c1, "pointing to child 1");
  }

  //expect throw
  @Test
  public void fullParamsTestThrows() {
    Edge<String, String> e1 = new Edge<String, String>(null, "I should dieeeee");
    exception.expect(IllegalArgumentException.class);
  }

  //getter
    //get dest
  @Test
  public void testGetDest() {
    assertEquals(edge.getDestination(), c1);
    assertFalse(edge.getDestination().equals(p1));
  }

    //get data
  @Test
  public void testGetData() {
    Edge<String, String> e1 = new Edge<String, String>(c1, "edge to child one");
    assertEquals(e1.getData(), edge.getData());
  }

  //equality test
    //symm
  @Test
  public void testEquivalenceSymmetry() {
    assertEquals(edge, edge);
    assertNotEquals(edge, new Edge<String, String>(c2, "random datataaaaa"));
  }

    //reflex
  @Test
  public void testEquivalenceReflexivity() {
    assertEquals(edge, edge_copy);
    assertEquals(edge_copy, edge);
  }

    //trans
  @Test
  public void testEquivalenceTransitivity() {
    assertEquals(edge, edge_copy);
    assertEquals(edge_copy, edge_trans);
    assertEquals(edge, edge_trans);
  }

  //hash test
  @Test
  public void testHashEquvalence() {
    Edge<String, String> e1 = new Edge<String, String>(c1, "child1");
    Edge<String, String> e2 = new Edge<String, String>(c1, "child1");
    assertEquals(e1.hashCode(), e2.hashCode());
  }

  @Test
  public void testHashDifference() {
    Edge<String, String> e1 = new Edge<String, String>(c1, "child1");
    Edge<String, String> e2 = new Edge<String, String>(c1, "I am totally different");
    assertNotEquals(e1.hashCode(), e2.hashCode());
    Edge<String, String> e3 = new Edge<String, String>(c2, "child1");
    assertNotEquals(e1.hashCode(), e3.hashCode());
  }

  @Test
  public void testComparable() {
    Edge<String, String> e1 = new Edge<String, String>(c1, "child1");
    Edge<String, String> e2 = new Edge<String, String>(c1, "I am totally different");
    assertTrue(e1.compareTo(e2) > 0);
  }

}
