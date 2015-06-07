/*
Stefan Dierauf 2012
this program reads a java file then identifies which lines are over x chars
*/

import java.util.*;
import java.io.*;

public class OverHundred {
	
	public static void main(String[] args) throws FileNotFoundException{
		Scanner console = new Scanner(System.in);
		System.out.print("What is the name of the file? ");
		File input = new File(console.next());
		Scanner filescan = new Scanner(input);
		System.out.print("What is the max length of the line? ");
		int length = console.nextInt();
		boolean found = false;
		int lineNum = 1;
		while (filescan.hasNextLine()) {
			String line = filescan.nextLine();
			if (line.length() > length) {
				System.out.println("line: "+ lineNum + " " + line);
				found = true;
			}
			lineNum++;
		}
		if (!found) {
			System.out.println("No lines over " + length + " chars found.");
		}
		
	
	}

}