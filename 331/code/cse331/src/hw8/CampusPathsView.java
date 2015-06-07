package hw8;

import hw5.Edge;

import java.util.List;
import java.util.Map;

/**
 * Stefan Dierauf Nov 2014
 *
 * General interface for a view of CampusPaths
 */
public interface CampusPathsView {

  /**
   * Starts the view
   */
  public void start();

  /**
   * Outputs a list of the available buildings
   * @param buildings
   */
  public void displayBuildings(Map<String, String> buildings);

  /**
   * Outputs the path from start to end
   * @param start building long name
   * @param end building long name
   * @param path list of Edges that make up the path
   * @param startPoint starting PixelPoint of the path
   */
  public void displayPath(String start, String end, List<Edge<PixelPoint, Double>> path, PixelPoint startPoint);

  /**
   * Informs the user that they have made an unknown option
   */
  public void unknownOption();

  /**
   * Informs the user that they have given unknown building inputs
   * @param buildings a list of unknown building names
   */
  public void unknownBuildings(List<String> buildings);

  /**
   * Displays the menu
   */
  public void showMenu();

  /**
   * Prompts the user for the starting building
   */
  public void promptStartBuilding();

  /**
   * prompts the user for the ending building
   */
  public void promptEndBuilding();

  /**
   * Displays the passed output
   * @param output
   */
  public void println(String output);

}
