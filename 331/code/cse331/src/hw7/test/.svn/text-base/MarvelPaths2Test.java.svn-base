package hw7.test;

import hw5.Edge;
import hw5.Graph;
import hw6.*;
import hw7.MarvelPaths2;
import org.junit.Test;
import org.junit.Before;
import org.junit.rules.ExpectedException;

import java.util.Set;

/**
 * Created by Stefan Dierauf on 11/17/14.
 *
 * Implementation tests for MarvelPaths2
 */
public class MarvelPaths2Test {

  public static final String dataPath = "src/data/";
  public Graph<String, String> g = MarvelPaths.baseNameBuild("marvel.tsv");
  public Graph<String, Double> g2;

  @Test
  public void testBuildGraph() {
    g2 = MarvelPaths2.loadGraph("marvel.tsv");
  }

  @Test
  public void testGraphContainsAllCorrectNodes() {
    g2 = MarvelPaths2.loadGraph("marvel.tsv");
    assert(g.listNodes().containsAll(g2.listNodes()));
    assert(g2.listNodes().containsAll(g.listNodes()));
  }
}
