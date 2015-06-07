import java.io.*;
import java.util.*;

public class DumpList {
	public static void main(String[] args) throws FileNotFoundException {
		Scanner input = new Scanner(System.in);
		System.out.println("Directory? ");
		File path = new File(input.next());
		if (path.isDirectory){
			System.out.println("d");
		}
	
	
	}

}