/*
Stefan Dierauf Oct 2012
This program prints an illusion based on circles and lines.
Makes heavy use of parameters. HEAVY.
fun side note, I wrote the base illusion method
so they would fully work with ovals as well. 
*/

import java.awt.*;

public class Illusion {
   
   public static final int WIDTH = 500; //not exactly necessary
   public static final int HEIGHT = 400;
   
   public static void main(String[] args) {
      
      //set up the panel and graphics
      DrawingPanel panel = new DrawingPanel(WIDTH,HEIGHT);
      Graphics g = panel.getGraphics();
      //background
      background(g);
      
      //single circles
      theIllusion(g, 0, 0, 90, 90, 3); //top-left
      theIllusion(g, 120, 10, 90, 90, 3); //top-second-left
      theIllusion(g, 250, 50, 80, 80, 5); //top-middles
      
      //boxes
      illusionBox(g, 10, 120, 100, 100, 2, 10);//bottom-left
      illusionBox(g, 350, 20, 40, 40, 3, 5);//top-right
      illusionBox(g, 230, 160, 50, 50, 4, 5);//bottom-right
      
   }
   
   //colors the background. Will change depending on panel size.
   public static void background(Graphics g) {
      g.setColor(Color.GRAY);
      g.fillRect(0, 0, WIDTH, HEIGHT);
   }
   
   //makes the circles and lines.
   //also works if you want to print ovals
   public static void theIllusion(Graphics g, int x, int y, int width, int height, int circleNumber) {
      g.setColor(Color.RED);
      g.fillOval(x, y, width, height);
      g.setColor(Color.BLACK);
      for (int i = 0; i < circleNumber; i++){
         g.drawOval(x + circleMath(i, width, 2, circleNumber),y + circleMath(i, height, 2, circleNumber),
         width - circleMath(i, width, 1, circleNumber),height - circleMath(i, height, 1, circleNumber));
      }//using a return for circlemath. cool!
      
      //the diamond part.
      g.drawLine(x, y + height / 2, x + width / 2 ,y);
      g.drawLine(x + width / 2, y, x + width, y + height / 2);
      g.drawLine(x , y + height / 2, x + width / 2, y + height);
      g.drawLine(x + width / 2, y + height, x + width, y + height / 2);
      
   }
   
   //returns the reduction calculation for the position and size of the circle
   public static int circleMath (int i, int width, int mult, int circleNumber) {
      return i*width/(mult*circleNumber);
   }
   
   //makes the square box of illusion
	public static void illusionBox(Graphics g, int x, int y, int subWidth, int subHeight, int square, int subCount){
   	g.setColor(Color.LIGHT_GRAY);
      g.fillRect(x, y, subWidth * square, subHeight * square);
      g.setColor(Color.RED);
      g.drawRect(x, y, subWidth * square, subHeight * square);
      for (int i = 0; i < square; i++){
         for (int j = 0; j < square;j++){
            theIllusion(g, x + subWidth * j, y, subWidth, subHeight, subCount);
         }
         y = y + subHeight;
         
      }
      
   }
   
}