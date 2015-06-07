package hw8;

import hw5.Edge;

import java.io.PrintStream;
import java.util.List;
import java.util.Map;

/**
 * Stefan Dierauf Nov 2014
 *
 * A console based view for CampusPaths
 *
 * Representation invariant:
 * this.out != null
 *
 * Abstraction function:
 * out is the output stream on all things that will be dsiplayed
 */
public class CampusPathsTextView implements CampusPathsView {

  private PrintStream out;

  /**
   * Creates a new CampusPathsTextView
   * @requires out != null
   * @param out
   */
  public CampusPathsTextView(PrintStream out) {
    this.out = out;
  }

  /**
   * @see CampusPathsView#start()
   */
  @Override
  public void start() {
    showMenu();
  }

  /**
   * @see CampusPathsView#showMenu()
   */
  @Override
  public void showMenu() {
    out.println("Menu:");
    out.println("\tr to find a route");
    out.println("\tb to see a list of all buildings");
    out.println("\tq to quit");
    prompt();
  }

  /**
   * @see hw8.CampusPathsView#displayBuildings(java.util.Map)
   * @param buildings
   */
  @Override
  public void displayBuildings(Map<String, String> buildings) {
    for (String key : buildings.keySet()) {
      out.println(key + ": "  + buildings.get(key));
    }
    prompt();
  }

  /**
   * @see hw8.CampusPathsView#displayPath(String, String, java.util.List, PixelPoint)
   * @param start building long name
   * @param end building long name
   * @param path list of Edges that make up the path
   * @param startPoint starting PixelPoint of the path
   */
  @Override
  public void displayPath(String start, String end, List<Edge<PixelPoint, Double>> path, PixelPoint startPoint) {
    out.println("Path from " + start + " to " + end + ":");
    Double sum = 0.0;
    PixelPoint startingPoint = startPoint;
    for (Edge<PixelPoint, Double> edge : path) {
      long roundedDistance = Math.round(edge.getData());
      long roundedX = Math.round(edge.getDestination().getX());
      long roundedY = Math.round(edge.getDestination().getY());
      String direction = calcDirection(startingPoint, edge.getDestination());
      out.println("\tWalk " + roundedDistance + " feet " + direction + " to (" + roundedX + ", " + roundedY + ")");
      sum += edge.getData();
      startingPoint = edge.getDestination();
    }
    out.println("Total distance: " + Math.round(sum) + " feet");
    prompt();
  }

  /**
   * Calculates cardinal direction of the end point from the start point
   * @param start starting point
   * @param end ending point
   * @return A String representing the cardinal direction
   */
  private String calcDirection(PixelPoint start, PixelPoint end) {
    String dir = "";
    double calcX = end.getX() - start.getX();
    double calcY = start.getY() - end.getY();
    double angle = Math.atan2(calcY, calcX);
    double roundVal = angle/Math.PI * 8.0;
    if (roundVal < 3 && roundVal > 1) {
      dir = "NE";
    } else if (roundVal <= 5 && roundVal >= 3) {
      dir = "N";
    } else if (roundVal < 7 && roundVal > 5 ) {
      dir = "NW";
    } else if (roundVal <= -7 || roundVal >= 7) {
      dir = "W";
    } else if (roundVal < -5 && roundVal > -7) {
      dir = "SW";
    } else if (roundVal <= -3 && roundVal >= -5) {
      dir = "S";
    } else if (roundVal < -1 && roundVal > -3) {
      dir = "SE";
    } else if (roundVal <= 1 && roundVal >= -1) {
      dir = "E";
    }
    return dir;
  }

  /**
   * Prints to this.out
   * @param output
   */
  @Override
  public void println(String output) {
    out.println(output);
  }

  /**
   * Prompts the user for input
   */
  public void prompt() {
    out.println();
    out.print("Enter an option ('m' to see the menu): ");
  }


  /**
   * @see CampusPathsView#unknownOption()
   */
  @Override
  public void unknownOption() {
    out.println("Unknown option.");
    prompt();
  }

  /**
   * @see CampusPathsView#promptStartBuilding()
   */
  @Override
  public void promptStartBuilding() {
    out.print("Abbreviated name of starting building: ");
  }

  /**
   * @see CampusPathsView#promptEndBuilding()
   */
  @Override
  public void promptEndBuilding(){
    out.print("Abbreviated name of ending building: ");
  }

  /**
   * @see hw8.CampusPathsView#unknownBuildings(java.util.List)
   * @param buildings a list of unknown building names
   */
  @Override
  public void unknownBuildings(List<String> buildings) {
    for (String building : buildings) {
      out.println("Uknown building " + building);
    }
    prompt();
  }
}
