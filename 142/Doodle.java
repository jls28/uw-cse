/*
Stefan Dierauf Oct 2012
this program produces a small graphics doodle
its a smiley face
*/

import java.awt.*;

public class Doodle {
	
	public static void main(String[] args) {
	
	DrawingPanel panel = new DrawingPanel(500,500);
	
	Graphics g = panel.getGraphics();
	drawFace(g);
	
	}
	
	public static void drawFace(Graphics g) {
	//draw circle
		g.setColor(Color.YELLOW);
		g.fillOval(0,0,500,500);

	//draw eyes
		g.setColor(Color.BLACK);
		g.fillOval(100,100,100,100);
		g.fillOval(300,100,100,100);
		
	//draw line for mouth
		g.fillRect(150,350,200,50);
		g.fillRect(100,300,50,50);
		g.fillRect(350,300,50,50);
	}
	
	
}
	
