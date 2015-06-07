import java.awt.*;
import javax.swing.*;

/**
 * Basic Java graphics demo: JPanel with a face drawn in it. 
 * CSE 331 12au, 13wi, 13au.  Based on old examples from CSE 143.
 * 
 * @author Hal Perkins 
 */
public class Face extends JPanel {

  // number of times paintComponent has been called
  private int ncalls = 0;    

  /** Paint a smiley face centered in this JPanel */
  @Override
  public void paintComponent(Graphics g) {
    
    // Trace: print a message showing number of times paintComponent called
    ncalls++;
    System.err.println("paintComponent call " + ncalls);
    
    Graphics2D g2 = (Graphics2D) g;
    // Note: The drawing code here uses the old AWT procedural interface to 
    // draw shapes.  A version taking full advantage of Graphics2D would
    // create actual shape objects and add them to the picture.
    
    // paint background
    super.paintComponent(g);
    
    // get width and height of drawing area
    int height = getHeight();
    int width  = getWidth();
    
    // draw face that takes up 80% of the JPanel
    int faceTop  = height/10;
    int faceLeft = width/10;
    int faceHeight = height - height/5;
    int faceWidth  = width  - width/5;
    
    // outline
    g2.setColor(Color.yellow);
    g2.fillOval(faceLeft, faceTop, faceWidth, faceHeight);
    
    // eyes
    g2.setColor(Color.black);
    g2.fillOval(faceLeft+(int)(width*0.2), faceTop+(int)(height*0.2),
                width/10, height/10);
    g2.fillOval(faceLeft+(int)(width*0.5), faceTop+(int)(height*0.2),
                width/10, height/10);
    
    // nose
    Polygon nose = new Polygon();
    nose.addPoint(faceLeft+(int)(width*0.40), faceTop+(int)(height*0.35));
    nose.addPoint(faceLeft+(int)(width*0.45), faceTop+(int)(height*0.50));
    nose.addPoint(faceLeft+(int)(width*0.35), faceTop+(int)(height*0.50));
    g2.fillPolygon(nose);
    
    // mouth
    g2.fillArc(faceLeft+(int)(width*0.25), faceTop+(int)(height*0.5),
               (int)(width*0.3), (int)(height*0.2),
               0, -180);
    
  }
}
