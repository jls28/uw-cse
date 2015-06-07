import java.io.*;
import java.util.*;

public class LineAdder {
	public static void main(String[] args) throws FileNotFoundException {
		Scanner n = new Scanner(new File("dictionary2.txt"));
		while (n.hasNextLine()) {
			System.out.print(n.nextLine() + "|");
		}
	}
}