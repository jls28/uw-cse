import java.io.*;
import java.util.*;

public class LineAdder {
	public static void main(String[] args) throws FileNotFoundException {
		Scanner n = new Scanner(new File("stuff.txt"));
		while (n.hasNextLine()) {
			System.out.print(n.nextLine() + "|");
		}
	}
}