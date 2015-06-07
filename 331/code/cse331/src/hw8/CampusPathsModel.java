package hw8;

import hw5.Edge;
import hw5.Graph;
import hw7.MarvelPaths2;

import java.util.*;

/**
 * Stefan Dierauf Nov 2014
 *
 * Represents the 'state' of the CampusPaths application
 * Finds the shortest path between two buildings
 *
 * Representation Invariant:
 * this.paths != null;
 * this.names != null;
 * this.shortNamesToPoints != null
 * this.observers != null
 * for all keys in shortNamesToPoints, their corresponding PixelPoint exists in this.paths
 *
 * Abstraction function:
 * CampusPathModel represents a map of campus and all possible paths to take between buildings on campus
 * this.paths contains all possible paths, shortNamesToPoints contains building short names to Points on the graph,
 * and then routes between two buildings can be computed.
 *
 */
public class CampusPathsModel {


  /**
   * @specfield paths = Graph of PixelPoints to other PixelPoints
   * @specfield names = map of building abbreviations to full names
   * @specfield shortNamesToPoints = map of building short names to their respective PixelPoint in this.paths
   * @specfield observers = List of all views registered to this
   */
  private Graph<PixelPoint, Double> paths;
  private Map<String, String> names;
  private Map<String, PixelPoint> shortNamesToPoints;
  private List<CampusPathsView> observers;

  /**
   * File paths for data files
   */
  public final String campusPathsFilePath = "src/hw8/data/campus_paths.dat";
  public final String campusBuildingsFilePath = "src/hw8/data/campus_buildings.dat";


  /**
   * Constructs a new CampusPathsModel
   * @requires the filepaths campusPathsFilePath and campusBuildingsFilePath point to the correct files
   * @effects this.paths with data from campusPathsFilePath, fills names and shortNamesToPoints with
   * with data from campusBuildingsFilePath.
   * @effects constructs a new CampusPathsModel
   */
  public CampusPathsModel() {
    paths = new Graph<PixelPoint, Double>();
    names = new TreeMap<String, String>();
    shortNamesToPoints = new HashMap<String, PixelPoint>();
    observers = new LinkedList<CampusPathsView>();
    try {
      CampusPathsParser.parsePoints(campusPathsFilePath, paths);
      CampusPathsParser.parseBuildings(campusBuildingsFilePath, names, shortNamesToPoints);
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

  /**
   * Adds a CampusPathView to this.observers
   * @param output
   * @modifies this.observers
   */
  public void addView(CampusPathsView output) {
    observers.add(output);
  }


  /**
   * @return an immutable version of this.observers
   */
  public List<CampusPathsView> getObservers() {
    return Collections.unmodifiableList(this.observers);
  }

  /**
   * Deletes the passed view from this.observers
   * @param output
   * @return @see List#remove(Object)
   */
  public boolean deleteView(CampusPathsView output) {
    return this.observers.remove(output);
  }

  /**
   * Calls outputBuildings on all views in this.observers
   */
  public void outputBuildings() {
    for (CampusPathsView view : observers) {
      view.displayBuildings(Collections.unmodifiableMap(names));
    }
  }

  /**
   * Computes a route between start and end
   * @param start building shortname
   * @param end building shortname
   */
  public void computeRoute(String start, String end) {
    if (checkBuildingsExist(start, end)) {
      PixelPoint startPoint = shortNamesToPoints.get(start) ;
      PixelPoint endPoint = shortNamesToPoints.get(end);
      //Thank you MarvelPaths2!
      List<Edge<PixelPoint, Double>> path = MarvelPaths2.findPath(paths, startPoint, endPoint);
      for (CampusPathsView view : observers) {
        view.displayPath(names.get(start), names.get(end), path, startPoint);
      }
    }
  }

  /**
   * Checks to make sure both start and end exist in CampusPathsModel
   * @param start building shortname
   * @param end building shortname
   * @return true if both buildings exist, otherwise false;
   */
  public boolean checkBuildingsExist(String start, String end) {
    boolean known = true;
    List<String> buildings = new LinkedList<String>();
    if (!shortNamesToPoints.containsKey(start)) {
      buildings.add(start);
      known = false;
    }
    if (!shortNamesToPoints.containsKey(end)) {
      buildings.add(end);
      known = false;
    }
    if (!known) {
      unknownBuildings(buildings);
    }
    return known;
  }

  /**
   * Informs all views that the passed buildings are unknown.
   * @param buildings list of unknown building names
   */
  public void unknownBuildings(List<String> buildings) {
    for (CampusPathsView view : observers) {
      view.unknownBuildings(buildings);
    }
  }

}
