package hw6;

import java.util.*;
import hw5.*;

/**
 * Created by Stefan Dierauf on 10/28/14.
 * Builds graphs with correctly formatted TSVs
 * And performs BFS between two nodes in the graph
 */
public class MarvelPaths {

  //File path prefix for .tsv files
  private final static String pathPrefix = "src/hw6/data/";

  /**
   * MarvelPaths only contains static methods, so it has no state and therefore
   * no AF or RepInvariant
   */

  /**
   * Prompts the user for which two marvel characters they want to find the shortest path
   */
  public static void main(String[] args) {
    System.out.println("Loading data...");
    Scanner in = new Scanner(System.in);
    final Graph<String, String> heroes = baseNameBuild("marvel.tsv");
    String promptAgain = "yes";

    //Get a list of nodes in the graph sorted by popularity
    List<String> nodes = new LinkedList<String>();
    nodes.addAll(heroes.listNodes());
    Comparator<String> popularNodes = new Comparator<String>() {
      public int compare(String o1, String o2) {
        return heroes.getEdges(o2).size() - heroes.getEdges(o1).size();
      }
    };
    Collections.sort(nodes, popularNodes);

    System.out.println();
    System.out.println("===<< S.H.I.E.L.D >>===");
    System.out.println();
    System.out.println("Welcome back to the Marvel characters relation finder, Director Fury.");
    System.out.println("This program will let you find the closest relation between two characters in the Marvel universe");


    while (!promptAgain.equals("no")) {
      System.out.println();
      System.out.print("Who should the starting character be? ");
      String char1 = tryFindCharacter(in, nodes);
      System.out.print("Who should the ending character be? ");
      String char2 = tryFindCharacter(in, nodes);
      List<Edge<String, String>> foundPath = MarvelPaths.findPath(heroes, char1, char2);
      System.out.println();
      System.out.println("path from " + char1 + " to " + char2 + ":");
      if (foundPath == null) {
        System.out.println("no path found");
      } else {
        String parent = char1;
        for (Edge<String, String> e : foundPath) {
          System.out.println(parent + " to " + e.getDestination() + " via " + e.getData());
          parent = e.getDestination();
        }
      }
      System.out.println();
      System.out.print("Find another character? (yes or no) ");
      promptAgain = in.next().trim();
    }
    System.out.println();
    System.out.println("===<< S.H.I.E.L.D >>===");
  }

  /**
   * Returns the first node that contains the search term
   * @param nodes list of nodes to find
   * @param characterName search string
   * @return a node that has characterName as a substring or null if one doesn't exist
   */
  public static String softFind(List<String> nodes, String characterName) {
    for (String node : nodes) {
      if (node.toLowerCase().contains(characterName.toLowerCase())) {
        return node;
      }
    }
    return null;
  }

  /**
   * Continuously prompts the reader from in until it finds a node in the list
   * @param in
   * @param nodes
   * @requires nodes != null & in != null
   * @return a String of a character that is in nodes
   */
  public static String tryFindCharacter(Scanner in, List<String> nodes) {
    String foundCharacter = null;
    while (foundCharacter == null) {
      String input = in.nextLine().trim();
      foundCharacter = softFind(nodes, input);
      if (foundCharacter == null) {
        System.out.print("Oops! I couldn't find anything for " + input + ", try again: ");
      }
    }
    return foundCharacter;
  }

  /**
   * Builds a new graph based on the .tsv specification
   * @param fullPath full path to the file
   * @return a new graph based on the .tsv
   */
  public static Graph<String, String> build(String fullPath) {
    Graph<String, String> graph = new Graph<String, String>();
    //Build the graph
    Set<String> characters = new HashSet<String>();
    Map<String, List<String>> books = new HashMap<String, List<String>>();

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
    return graph;
  }

  public static Graph<String, String> baseNameBuild(String baseName) {
    return build(pathPrefix + baseName);
  }

  /**
   * Finds the shortest path between two nodes in the passed graph
   * @param data
   * @param start
   * @param end
   * @requires MarvelPaths to be constructed either with a graph or basename
   * @requires start and end are both nodes in Graph data
   * @return
   */
  public static List<Edge<String, String>> findPath(Graph<String, String> data, String start, String end) {

    Queue<String> searchQueue = new LinkedList<String>();
    Map<String, List<Edge<String, String>>> paths = new HashMap<String, List<Edge<String, String>>>();
    paths.put(start, new LinkedList<Edge<String, String>>());
    searchQueue.add(start);

    while (!searchQueue.isEmpty()) {
      String currentNode = searchQueue.remove();
      if (currentNode.equals(end)) {
        List<Edge<String, String>> path = paths.get(currentNode);
        return path;
      }
      //sort by edge.dest then by edge.name
      List<Edge<String, String>> edges = new LinkedList<Edge<String, String>>();
      edges.addAll(data.getEdges(currentNode));
      Collections.sort(edges);

      for (Edge<String, String> e : edges) {
        if (!paths.containsKey(e.getDestination())) {
          List<Edge<String, String>> path = new LinkedList<Edge<String, String>>();
          path.addAll(paths.get(currentNode));
          searchQueue.add(e.getDestination());
          path.add(e);
          paths.put(e.getDestination(), path);
        }
      }
    }

    //never found a path
    return null;
  }

}
