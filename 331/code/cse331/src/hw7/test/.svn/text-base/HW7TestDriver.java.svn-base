package hw7.test;

import hw5.Edge;
import hw5.Graph;
import hw7.MarvelPaths2;

import java.io.*;
import java.util.*;

/**
 * This class implements a testing driver which reads test scripts
 * from files for testing Graph.
 **/
public class HW7TestDriver {

  public static void main(String args[]) {
    try {
      if (args.length > 1) {
        printUsage();
        return;
      }

      HW7TestDriver td;

      if (args.length == 0) {
        td = new HW7TestDriver(new InputStreamReader(System.in),
            new OutputStreamWriter(System.out));
      } else {

        String fileName = args[0];
        File tests = new File (fileName);

        if (tests.exists() || tests.canRead()) {
          td = new HW7TestDriver(new FileReader(tests),
              new OutputStreamWriter(System.out));
        } else {
          System.err.println("Cannot read from " + tests.toString());
          printUsage();
          return;
        }
      }

      td.runTests();

    } catch (IOException e) {
      System.err.println(e.toString());
      e.printStackTrace(System.err);
    }
  }

  private static void printUsage() {
    System.err.println("Usage:");
    System.err.println("to read from a file: java hw5.test.HW5TestDriver <name of input script>");
    System.err.println("to read from standard in: java hw5.test.HW5TestDriver");
  }

  /** String -> Graph: maps the names of graphs to the actual graph **/
  private final Map<String, Graph<String, Double>> graphs = new HashMap<String, Graph<String, Double>>();
  private final PrintWriter output;
  private final BufferedReader input;

  /**
   * @requires r != null && w != null
   *
   * @effects Creates a new HW5TestDriver which reads command from
   * <tt>r</tt> and writes results to <tt>w</tt>.
   **/
  public HW7TestDriver(Reader r, Writer w) {
    input = new BufferedReader(r);
    output = new PrintWriter(w);
  }

  /**
   * @effects Executes the commands read from the input and writes results to the output
   * @throws IOException if the input or output sources encounter an IOException
   **/
  public void runTests()
      throws IOException
  {
    String inputLine;
    while ((inputLine = input.readLine()) != null) {
      if ((inputLine.trim().length() == 0) ||
          (inputLine.charAt(0) == '#')) {
        // echo blank and comment lines
        output.println(inputLine);
      }
      else
      {
        // separate the input line on white space
        StringTokenizer st = new StringTokenizer(inputLine);
        if (st.hasMoreTokens()) {
          String command = st.nextToken().replaceAll("_", " ");
          //replace underscores with spaces

          List<String> arguments = new ArrayList<String>();
          while (st.hasMoreTokens()) {
            arguments.add(st.nextToken().replaceAll("_", " "));
          }

          executeCommand(command, arguments);
        }
      }
      output.flush();
    }
  }

  private void executeCommand(String command, List<String> arguments) {
    try {
      if (command.equals("CreateGraph")) {
        createGraph(arguments);
      } else if (command.equals("AddNode")) {
        addNode(arguments);
      } else if (command.equals("AddEdge")) {
        addEdge(arguments);
      } else if (command.equals("ListNodes")) {
        listNodes(arguments);
      } else if (command.equals("ListChildren")) {
        listChildren(arguments);
      } else if (command.equals("LoadGraph")) {
        loadGraph(arguments);
      } else if (command.equals("FindPath")) {
        findPath(arguments);
      } else {
        output.println("Unrecognized command: " + command);
      }
    } catch (Exception e) {
      output.println("Exception: " + e.toString());
    }
  }

  private void createGraph(List<String> arguments) {
    if (arguments.size() != 1) {
      throw new CommandException("Bad arguments to CreateGraph: " + arguments);
    }

    String graphName = arguments.get(0);
    createGraph(graphName);
  }

  private void createGraph(String graphName) {
    // Insert your code here.
    Graph<String, Double> g = new Graph<String, Double>();
    graphs.put(graphName, g);
    output.println("created graph " + graphName);
  }

  private void addNode(List<String> arguments) {
    if (arguments.size() != 2) {
      throw new CommandException("Bad arguments to addNode: " + arguments);
    }

    String graphName = arguments.get(0);
    String nodeName = arguments.get(1);

    addNode(graphName, nodeName);
  }

  private void addNode(String graphName, String nodeName) {
    // Insert your code here.

    Graph<String, Double> g = graphs.get(graphName);
    g.addNode(nodeName);
    output.println("added node " + nodeName + " to " + graphName);
  }

  private void addEdge(List<String> arguments) {
    if (arguments.size() != 4) {
      throw new CommandException("Bad arguments to addEdge: " + arguments);
    }

    String graphName = arguments.get(0);
    String parentName = arguments.get(1);
    String childName = arguments.get(2);
    Double edgeLabel = Double.parseDouble(arguments.get(3));

    addEdge(graphName, parentName, childName, edgeLabel);
  }

  private void addEdge(String graphName, String parentName, String childName,
                       Double edgeLabel) {
    // Insert your code here.

    Graph<String, Double> g = graphs.get(graphName);
    g.addEdge(parentName, edgeLabel, childName);
    output.println("added edge " + String.format("%.3f", edgeLabel) + " from " + parentName + " to " + childName + " in " + graphName);
  }

  private void listNodes(List<String> arguments) {
    if (arguments.size() != 1) {
      throw new CommandException("Bad arguments to listNodes: " + arguments);
    }

    String graphName = arguments.get(0);
    listNodes(graphName);
  }

  private void listNodes(String graphName) {
    // Insert your code here.

    Graph<String, Double> g = graphs.get(graphName);
    Set<String> nodes = g.listNodes();
    String nodesString = "";
    for (String node : nodes) {
      nodesString += " " + node;
    }
    output.println(graphName + " contains:" + nodesString);
  }

  private void listChildren(List<String> arguments) {
    if (arguments.size() != 2) {
      throw new CommandException("Bad arguments to listChildren: " + arguments);
    }

    String graphName = arguments.get(0);
    String parentName = arguments.get(1);
    listChildren(graphName, parentName);
  }

  private void listChildren(String graphName, String parentName) {
    Graph<String, Double> g = graphs.get(graphName);
    String wazzup = "";
    for (Edge<String, Double> e : g.getSortedEdges(parentName)) {
      wazzup += " " + e.getDestination() + "(" + e.getData() + ")";
    }
    output.println("the children of " + parentName + " in " + graphName + " are:" + wazzup);
  }

  private void loadGraph(List<String> arguments) {
    if (arguments.size() != 2) {
      throw new CommandException("Bad arguments to listChildren: " + arguments);
    }
    String graphName = arguments.get(0);
    String fileName = arguments.get(1);
    loadGraph(graphName, fileName);
  }

  private void loadGraph(String graphName, String fileName) {
    graphs.put(graphName, MarvelPaths2.loadGraph(fileName));
    output.println("loaded graph " + graphName);
  }

  private void findPath(List<String> arguments) {
    if (arguments.size() != 3) {
      throw new CommandException("Bad arguments to listChildren: " + arguments);
    }
    String graphName = arguments.get(0);
    String char1 = arguments.get(1);
    String char2 = arguments.get(2);
    findPath(graphName, char1, char2);
  }

  private void findPath(String graphName, String char1, String char2) {
    Graph<String, Double> g = graphs.get(graphName);
    if (!g.contains(char1) || !g.contains(char2)) {
      if (!g.contains(char1)) {
        output.println("Unknown character " + char1);
      }
      if (!g.contains(char2)) {
        output.println("Unknown character " + char2);
      }
    } else {

      List<Edge<String, Double>> foundPath = MarvelPaths2.findPath(g, char1, char2);
      output.println("path from " + char1 + " to " + char2 + ":");
      if (foundPath == null) {
        output.println("no path found");
      } else {
        String parent = char1;
        double totalWeight = 0;
        for (Edge<String, Double> e : foundPath) {
          totalWeight += e.getData();
          String weight = String.format("%.3f", e.getData());
          output.println(parent + " to " + e.getDestination() + " with weight " + weight);
          parent = e.getDestination();
        }
        output.println("total cost: " + String.format("%.3f", totalWeight));
      }
    }
  }

  /**
   * This exception results when the input file cannot be parsed properly
   **/
  static class CommandException extends RuntimeException {

    public CommandException() {
      super();
    }
    public CommandException(String s) {
      super(s);
    }

    public static final long serialVersionUID = 3495;
  }
}
