import java.awt.*;

public class Squares {

	public static void main(String[] args){
	DrawingPanel panel = new DrawingPanel(800,800);
	panel.setBackground(Color.CYAN);
	
	Graphics g = panel.getGraphics();
	
	//squareA(g,50,50,20,5,100);
	//squareA(g,250,10,20,5,50);
	//squareA(g,180,115,20,5,180);
	//squareA(g,300,300,50,3,120);
	//squareA(g,500,200,10,10,200);
	squareA(g,panel,0,0,5,800,100);
	
	}
	
	public static void squareA(Graphics g,DrawingPanel panel, int x, int y, int spacing, int max, int size){
		g.setColor(Color.RED);
		
		for (int i = 0; i < max; i++) {
			panel.sleep(100);
			g.drawRect(x,y,(int)(spacing*(i+1)*(size/100.0)),(int)(spacing*(i+1)*(size/100.0)));
		}
		
		g.setColor(Color.BLACK);
		g.drawLine(x,y,(int)(x+spacing*max*(size/100.0)),(int)(y+spacing*max*(size/100.0)));
	
	}

}