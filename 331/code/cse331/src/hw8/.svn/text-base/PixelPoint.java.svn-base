package hw8;

import java.awt.geom.Point2D;

/**
 * Stefan Dierauf Nov 2014
 *
 * Essentially a Comparable Point2D.Double, needed for Graph to be happy
 * Compares by distance from 0,0
 */
public class PixelPoint extends Point2D.Double implements Comparable<PixelPoint> {

  /**
   * Constructs a new PixelPoint
   * @param x
   * @param y
   */
  public PixelPoint(double x, double y) {
    super(x, y);
  }

  /**
   * Compares based on distance from 0,0
   * @param o
   * @return -1 if this distance is shorter, +1 if greater, 0 if equal
   */
  public int compareTo(PixelPoint o) {
    double d1 = this.distance(0.0, 0.0);
    double d2 = o.distance(0.0, 0.0);
    if (d1 < d2) {
      return -1;
    } else if (d1 > d2) {
      return 1;
    } else {
      return 0;
    }
  }
}
