// Demonstrates basics of using graphics.

// Advanced (Another) Windowing Toolkit
import java.awt.*;

public class GraphicsDemo {
	public static void main(String[] args) {
		//Type       name  = new Type        (params);
		DrawingPanel panel = new DrawingPanel(300, 500);
		
		// ask the panel for its graphics object
		Graphics g = panel.getGraphics();
		
		      //   x1  y1  x2  y2
		g.drawLine(40, 40, 70, 70);
		      //   x   y   width height
		g.drawRect(70, 70, 100,  100);
		g.setColor(Color.RED);
		g.fillOval(70, 70, 100, 100);
		
		// easier to use loops that start at 0 for coordinate math
		for (int i = 0; i <= 5; i++) {
			                     //   red        green blue (0-255)
			Color myColor = new Color(100 + 20 * i, 0, 100 + 20 * i);
			g.setColor(myColor);		
		
			g.fillRect(170 + 20 * i, 170 + 20 * i, 30, 30);
		}
		
		// can use for loop tables to figure out change
		//g.fillRect(170, 170, 30, 30);
		//g.fillRect(200, 200, 30, 30);
		//g.fillRect(230, 230, 30, 30);
		
	}
}