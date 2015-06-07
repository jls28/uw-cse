import java.util.*;
import java.io.*;

public class LineReverser {

	public static void main(String[] args) throws FileNotFoundException{
		Scanner input = new Scanner(System.in);
		System.out.print("Filename? ");
		Scanner in = new Scanner(new File(input.next()));
		while (in.hasNextLine()) {
			String line = in.nextLine();
			String rev = "";
			for (int i = line.length() - 1; i > 0; i--) {
				rev = rev + line.charAt(i);
			}
			System.out.println(rev);
		}
	}
}
			