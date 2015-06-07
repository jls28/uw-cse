package hw8;
import hw5.Edge;
import hw5.Graph;

import java.awt.geom.Point2D;
import java.io.*;
import java.util.*;

/**
 * Stefan Dierauf Nov 2014
 *
 * Parses the campus path data given a filepath
 *
 * As CampusPathsParser has only static methods and no state, it does
 * not have a representation invariant or abstraction function
 *
 */
public class CampusPathsParser {



  /**
   * A checked exception class for bad data files
   */
  @SuppressWarnings("serial")
  public static class MalformedDataException extends Exception {
    public MalformedDataException() { }

    public MalformedDataException(String message) {
      super(message);
    }

    public MalformedDataException(Throwable cause) {
      super(cause);
    }

    public MalformedDataException(String message, Throwable cause) {
      super(message, cause);
    }
  }

  /**
   * Reads the campus_buildings dataset.
   * Each line of the input file contains a building's short name,
   * long name, and pixel location on the map, in the form
   * BAG (NE)	Bagley Hall (Northeast Entrance)	1878.3786	1661.4083
   *
   * @requires filename is a valid file path
   * @param filename the file that will be read
   * @param shortToLong map in which all short names to long names will be stored;
   *                    typically empty when the routine is called
   * @param shortToPoint map from short names of buildings to their pixel location on the map;
   *                     typically empty when the routine is called
   * @modifies shortToLong, shortToPoint
   * @effects fills shortToLong with short name -> long name for each building
   * @effects fills shortToPoint with short name -> pixel location on the map
   * @throws MalformedDataException if the file is not well-formed:
   *          each line contains exactly two tokens separated by a tab,
   *          or else starting with a # symbol to indicate a comment line.
   */
  public static void parseBuildings(String filename, Map<String, String> shortToLong,
                                    Map<String, PixelPoint> shortToPoint ) throws MalformedDataException {
    BufferedReader reader = null;
    try {
      reader = new BufferedReader(new FileReader(filename));

      // Construct the collections of characters and books, one
      // <character, book> pair at a time.
      String inputLine;
      while ((inputLine = reader.readLine()) != null) {

        // Ignore comment lines.
        if (inputLine.startsWith("#")) {
          continue;
        }

        // Parse the data, stripping out quotation marks and throwing
        // an exception for malformed lines.
        inputLine = inputLine.replace("\"", "");
        String[] tokens = inputLine.split("\t");
        if (tokens.length != 4) {
          throw new MalformedDataException("Line should contain 3 tabs: "
              + inputLine);
        }

        String shortName = tokens[0];
        String longName = tokens[1];
        PixelPoint location = new PixelPoint(
            Double.parseDouble(tokens[2]),
            Double.parseDouble(tokens[3])
        );

        shortToLong.put(shortName, longName);
        shortToPoint.put(shortName, location);
      }

    } catch (IOException e) {
      System.err.println(e.toString());
      e.printStackTrace(System.err);
    } finally {
      if (reader != null) {
        try {
          reader.close();
        } catch (IOException e) {
          System.err.println(e.toString());
          e.printStackTrace(System.err);
        }
      }
    }
  }


  /**
   * Reads the campus_paths.dat data set
   *
   * fills the passed graph with PixelPoint nodes pointing to other PixelPoint nodes with Edges that are doubles
   * representing the distance betweent the two points.
   *
   * @requires the file at filename to be campus_paths.dat
   * @requires graph != null
   * @param filename the file that will be read
   * @param graph the graph of pixel locations to other pixel locations that will be created
   *
   * @throws MalformedDataException
   */
  public static void parsePoints (String filename, Graph<PixelPoint, Double> graph) throws MalformedDataException {

    BufferedReader reader = null;
    try {
      reader = new BufferedReader(new FileReader(filename));

      // Construct the collections of characters and books, one
      // <character, book> pair at a time.
      String inputLine;
      PixelPoint parent = null;
      while ((inputLine = reader.readLine()) != null) {

        // Ignore comment lines.
        if (inputLine.startsWith("#")) {
          continue;
        }

        // Parse the data, stripping out quotation marks and throwing
        // an exception for malformed lines.
        inputLine = inputLine.replace("\"", "");
        String[] tokens = inputLine.split("\t");
//        if (tokens.length > 3) {
//          throw new MalformedDataException("Line should contain 3 tabs: "
//              + inputLine);
//        }
        if (tokens[0].equals("")) {
          String[] pieces = tokens[1].split(":");
          PixelPoint child = parsePixelPoint(pieces[0]);
          Double distance = Double.parseDouble(pieces[1].trim());
          graph.addEdge(parent, distance, child);
        } else {
          parent = parsePixelPoint(tokens[0]);
          graph.addNode(parent);
        }

      }

    } catch (IOException e) {
      System.err.println(e.toString());
      e.printStackTrace(System.err);
    } finally {
      if (reader != null) {
        try {
          reader.close();
        } catch (IOException e) {
          System.err.println(e.toString());
          e.printStackTrace(System.err);
        }
      }
    }


  }


  /**
   * Parses a single PixelPoint as seen in campus_paths.dat
   * Expects a PixelPoint to be in the format 2063.0526,2009.5072
   * @param withComma the string of the PixelPoint to be parsed
   * @return a new PixelPoint constructed from the input
   */
  public static PixelPoint parsePixelPoint (String withComma) {
    String[] pieces = withComma.split(",");
    return new PixelPoint(
        Double.parseDouble(pieces[0]),
        Double.parseDouble(pieces[1])
    );
  }

}
