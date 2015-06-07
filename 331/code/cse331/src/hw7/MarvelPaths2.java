package hw7;

import hw5.*;
import hw6.MarvelParser;

import java.math.BigDecimal;
import java.util.*;


/**
 * Created by Stefan Dierauf on 11/11/14.
 *
 * MarvelPaths2 builds graphs based on correctly formatted TSV files
 * and performs Dijkstra's algorithm to find the shortest path between two nodes
 */
public class MarvelPaths2 {

  /**
   * MarvelPaths2 has only static methods, so it has no state
   * to be represented and therefore no abstraction function
   */

  private static final String filePath = "src/hw7/data/";

  /**
   * Constructs a graph where each node is a superhero name and each Edge
   * is inversely proportional to the number of books superhero A has to superhero B
   * @param basename of the file
   * @requires filePath + basename = a validly formatted tsv file.
   * @return a new Graph<String, Double> that is correctly formatted
   */
  public static Graph<String, Double> loadGraph(String basename) {
    Graph<String, String> graph = new Graph<String, String>();
    Set<String> characters = new HashSet<String>();
    Map<String, List<String>> books = new HashMap<String, List<String>>();

    String fullPath = filePath + basename;
    try {
      MarvelParser.parseData(fullPath, characters, books);
    } catch (MarvelParser.MalformedDataException e) {
      e.printStackTrace();
    }

    for (String character : characters) {
      graph.addNode(character);
    }
    //each book is going to add two edges
    for (String book : books.keySet()) {
      for (String character : books.get(book)) {
        for (String char2 : books.get(book)) {
          if (!character.equals(char2)) {
            graph.addEdge(character, book, char2);
          }
        }
      }
    }

    Graph<String, Double> heroes = new Graph<String, Double>();
    //now calculate edges for each hero
    for (String hero : graph.listNodes()) {
      heroes.addNode(hero);
      for (String child : graph.listChildren(hero)) {
        int count = graph.getEdgesToChild(hero, child).size();
        if (count > 0) {
          heroes.addEdge(hero, Math.pow(count, -1), child);
        }
      }
    }

    return heroes;
  }

  /**
   * Takes a graph, a starting node, and an ending node,
   * and returns a list of shortest edges between the two nodes
   * @param graph
   * @param start
   * @param dest
   * @requires Graph be of type T, W where T extends Comparable and W extends Number
   * and Comparable
   * @return A List of Edges containing the shortest path between the two nodes
   */
  public static
    <T extends Comparable<T>, W extends Number & Comparable<W>>
    List<Edge<T, W>> findPath(Graph<T, W> graph, T start, T dest) {
    //Need a custom comparator for correctly comparing two lists of paths
    Comparator<List<Edge<T, W>>> totalWeightComparator = new Comparator<List<Edge<T, W>>>() {
      @Override
      public int compare(List<Edge<T, W>> o1, List<Edge<T, W>> o2) {
        BigDecimal l1Count = BigDecimal.ZERO;
        BigDecimal l2Count = BigDecimal.ZERO;
        for (Edge<T, W> edge : o1) {
          l1Count = l1Count.add(new BigDecimal(edge.getData().doubleValue()));
        }
        for (Edge<T, W> edge : o2) {
          l2Count = l2Count.add(new BigDecimal(edge.getData().doubleValue()));
        }
        return l1Count.compareTo(l2Count);
      }
    };

    PriorityQueue<ArrayList<Edge<T, W>>> active = new PriorityQueue<ArrayList<Edge<T,W>>>(40, totalWeightComparator);
    //Start off the PriorityQueue with a zero cost edge to itself
    ArrayList<Edge<T, W>> noCost = new ArrayList<Edge<T, W>>();
    noCost.add(new Edge<T, W>(start, (W) BigDecimal.ZERO));
    active.add(noCost);
    //Keep track of visited Nodes
    Set<T> visited = new HashSet<T>();

    while (!active.isEmpty()) {
      ArrayList<Edge<T, W>> minPath = active.remove();
      T minDest = minPath.get(minPath.size() - 1).getDestination();
      if (minDest.equals(dest)) {
        minPath.remove(0);
        return minPath;
      }
      if (!visited.contains(minDest)) {
        for (Edge<T, W> childEdge : graph.getEdges(minDest)) {
          if (!visited.contains(childEdge.getDestination())) {
            ArrayList<Edge<T, W>> newPath = new ArrayList<Edge<T, W>>();
            newPath.addAll(minPath);
            newPath.add(childEdge);
            active.add(newPath);
            visited.add(minDest);
          }
        }
      }
    }

    return null;
  }

}
