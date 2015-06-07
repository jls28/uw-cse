/* Stefan Dierauf Nov 2012
This program will take a name as input
and report the meaning of the name
and the popularity per year
with a helpful graph
*/

import java.util.*;
import java.io.*;
import java.awt.*;

public class BabyNames {
	
	public static final int STARTING_YEAR = 1890;
	public static final int DECADE_WIDTH = 60;
	public static final int LEGEND_RECT_HEIGHT = 30;
	public static final int Y_VAL = 500+2*LEGEND_RECT_HEIGHT;
	public static final String NAMES_FILE = "names.txt";
	public static final String MEANINGS_FILE = "meanings.txt";

	public static void main(String[] args) throws FileNotFoundException {
		printHeader();
		String yes = "yes";
		Scanner in = new Scanner(System.in);
		while (!(yes.equals("no"))) {
			String name = promptName();
		
			String namePopularity = searchFile(new File(NAMES_FILE), name);
			String nameMeaning = searchFile(new File(MEANINGS_FILE), name);
			printData(namePopularity, nameMeaning, name);
	
			if (doesNameExist(namePopularity)){
				printGraph(namePopularity, nameMeaning);
			}
			System.out.print("Again? ");
			yes = in.next();
		}	
	}
	
	//prints introduction of program
	public static void printHeader(){
		System.out.println("This program allows you to search through the");
		System.out.println("data from the Social Security Administration");
		System.out.println("to see how popular a particular name has been");
		System.out.println("since " + STARTING_YEAR + ".");
		System.out.println("");
	
	}
	
	//prompts user for a name
	public static String promptName() {
		System.out.print("Name: ");
		Scanner console = new Scanner(System.in);
		return console.next();	
	}
	
	//Builds scanner on a given file, returns line from findLine
	public static String searchFile(File fileName, String token) 
		throws FileNotFoundException{
		Scanner fileScan = new Scanner(fileName);
		return findLine(fileScan, token);
	}
	
	//searches for line containing the name, if no line is found returns empty string
	public static String findLine(Scanner fileScan, String token){
		while (fileScan.hasNextLine()){
			String line = fileScan.nextLine();
			Scanner lineScan = new Scanner(line);
			String nameID = lineScan.next();
			if (nameID.equalsIgnoreCase(token)){
				return line;
			}
		}
		return "";   
	}
	
	//prints the data passed in unless the name doesnt exist
	public static void printData(String namePopularity, String nameMeaning, String name){
		if (doesNameExist(namePopularity)){
			System.out.println(namePopularity);
			System.out.println(nameMeaning);
		}else{
			System.out.println("\"" + name + "\" not found.");
		}
	}
	
	//gets the number of data poitns on the line
	public static int getNumberOfDataPoints(String namePopularity){
		Scanner lineScan = new Scanner(namePopularity);
		int numberOfDataPoints = 0;
		while (lineScan.hasNext()){
			if (lineScan.hasNextInt()){
				numberOfDataPoints++;
			}
			lineScan.next();
		}
		return numberOfDataPoints;		
	}
	
	//draws the panel
	public static void printGraph(String namePopularity, String nameMeaning){
		DrawingPanel panel = new DrawingPanel(780,Y_VAL);
		Graphics g = panel.getGraphics();
		int numberOfDataPoints = getNumberOfDataPoints(namePopularity);
		drawFixed(g, nameMeaning, numberOfDataPoints);
		drawColumns(g, namePopularity);
	}
	
	//draws the fixed elements of the panel
	public static void drawFixed(Graphics g, String nameMeaning, int numberOfDataPoints){
		g.setColor(Color.LIGHT_GRAY);
		g.fillRect(0, 0, 780, LEGEND_RECT_HEIGHT);
		g.fillRect(0, Y_VAL - LEGEND_RECT_HEIGHT, 780, Y_VAL);
		g.setColor(Color.BLACK);
		g.drawLine(0, LEGEND_RECT_HEIGHT, 780, LEGEND_RECT_HEIGHT);
		g.drawLine(0, Y_VAL - LEGEND_RECT_HEIGHT, 780, Y_VAL - LEGEND_RECT_HEIGHT);
		g.drawString(nameMeaning, 0, 16);
		for (int i = 0; i < numberOfDataPoints; i++){
			g.drawString(STARTING_YEAR + i*10 + "", 0 + DECADE_WIDTH*i, Y_VAL - 8); 
		}
	}
	
	//draws columns based on the line of data passed in
	public static void drawColumns(Graphics g, String namePopularity){
		Scanner lineScan = new Scanner(namePopularity);
		boolean isMale = false;
		if (namePopularity.contains(" m ")){
			isMale = true;
		}			
		int count = 0;
		while (lineScan.hasNext()){
			int rank = 0;
			if (lineScan.hasNextInt()){
				rank = lineScan.nextInt();
				if (isMale){
					g.setColor(Color.BLUE);
				}else{
					g.setColor(Color.PINK);
				}
				drawColumn(g, rank, count);
				count++;	
			}else{
				lineScan.next();
			}		
		}	
	}
	
	//draws a single column of the chart
	public static void drawColumn(Graphics g, int rank, int count) {
		g.fillRect(DECADE_WIDTH * count, rankMath(rank), DECADE_WIDTH/2, 
		(Y_VAL - LEGEND_RECT_HEIGHT)-rankMath(rank));
		g.setColor(Color.BLACK);
		g.drawString(rank+ "", DECADE_WIDTH*count, rankMath(rank));
	}
	
	//does the ranking calculation. 
	public static int rankMath(int rank) {
		if (rank == 0){
			return Y_VAL-LEGEND_RECT_HEIGHT;
		}else{
			return rank/2 + LEGEND_RECT_HEIGHT;
		}
	}
	
	//checks if the name exists.
	public static boolean doesNameExist(String namePopularity){
		return !(namePopularity.equals(""));
	}
}