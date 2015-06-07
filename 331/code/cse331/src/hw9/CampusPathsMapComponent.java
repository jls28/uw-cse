package hw9;

import hw5.Edge;
import hw8.PixelPoint;
import java.util.List;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.awt.image.ImageObserver;
import java.io.File;
import java.io.IOException;

/**
 * Stefan Dierauf Nov 2014
 *
 * CampusPathsMapComponent represents a map of Campus, and draws paths between two given locations
 *
 * layout:
 * ---------------------------
 * |                         |
 * |                         |
 * |      map w/ possible    |
 * |      red path           |
 * |                         |
 * |                         |
 * ---------------------------
 *
 * Where the map is a picture of campus.
 *
 * CampusPathsMapComponent has no abstraction function or representation invariant, because it does
 * not represent an ADT
 *
 */
public class CampusPathsMapComponent extends JPanel {

  /**
   * @specfield mapPicFilePath Filepath pointing to the location of the map image
   * @specfield parent The parent panel of this
   * @specfield mapImg The image this uses
   * @specfield startingPoint The starting point the path starts from
   * @specfield path List of points that specifies the path. If null, no path will be drawn
   */
  private final String mapPicFilePath = "src/hw8/data/campus_map.jpg";
  private JPanel parent;
  BufferedImage mapImg = null;
  private PixelPoint startingPoint;
  private List<Edge<PixelPoint, Double>> path;


  /**
   * @param parent Parent panel of this
   * @effects Constructs a new CampusPathsMapComponent
   */
  public CampusPathsMapComponent(JPanel parent) {
    this.parent = parent;
    try {
      mapImg = ImageIO.read(new File(mapPicFilePath));
    } catch (IOException e) {
      System.out.println("Image path bad!");
      e.printStackTrace();
    }
    clearPath();
    this.setPreferredSize(new Dimension(1024, 768));
  }

  /**
   * Resets this.path and this.startingPoint
   */
  public void clearPath() {
    this.startingPoint = null;
    this.path = null;
  }

  /**
   * Draws the map image and path if it exists on the panel, and will scale the map
   * and path correctly if resized.
   * @param g Graphcs component used for drawing
   */
  @Override
  public void paintComponent(Graphics g) {
    super.paintComponent(g);
    //draw the map
    g.drawImage(mapImg, 0, 0, parent.getWidth(), parent.getHeight(), null);
    Graphics2D g2 = (Graphics2D) g;
    double wRatio = parent.getWidth() * 1.0 / mapImg.getWidth();
    double hRatio = parent.getHeight() * 1.0 /  mapImg.getHeight();
    //Draw path if it exists
    PixelPoint last = this.startingPoint;
    if (this.startingPoint != null && this.path != null) {
      //draw a circle at the starting
      g2.setStroke(new BasicStroke(3));
      g2.setColor(Color.ORANGE);
      g2.drawOval((int) (last.getX() * wRatio) - 5,
          (int) (last.getY() * hRatio) - 5, 10, 10);
      for (Edge<PixelPoint, Double> e : this.path) {
        int x1 = (int) (last.getX() * wRatio);
        int y1 = (int) (last.getY() * hRatio);
        int x2 = (int) (e.getDestination().getX() * wRatio);
        int y2 = (int) (e.getDestination().getY() * hRatio);
        g2.setColor(Color.RED);
        g2.drawLine(x1, y1, x2, y2);
        last = e.getDestination();
      }
      g2.setColor(Color.BLUE);
      g2.drawOval((int) (last.getX() * wRatio) - 5,
          (int) (last.getY() * hRatio) - 5, 10, 10);
      //draw circle at end
    }
  }

  /**
   * Sets this.startingPoint and this.path so they can be drawn
   * @param start point to start at
   * @param path List of points to draw lines between
   */
  public void setPath(PixelPoint start, List<Edge<PixelPoint, Double>> path) {
    this.startingPoint = start;
    this.path = path;
  }

}
