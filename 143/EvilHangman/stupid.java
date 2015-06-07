import java.util.Scanner;
import java.io.*;


public class stupid {
	public static void main(String[] args) throws FileNotFoundException {
		Scanner poop = new Scanner(new File("dictionary.txt"));
		System.out.println("[ \"" + poop.nextLine() + "\",");
		while(poop.hasNextLine()) {
			System.out.println("\"" + poop.nextLine() + "\",");
		}
	}
}