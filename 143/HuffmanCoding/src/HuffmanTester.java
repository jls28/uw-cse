import java.io.File;
import java.io.IOException;
import java.util.Scanner;


public class HuffmanTester  {

	public static void main(String[] args) throws IOException {
		Scanner console = new Scanner(System.in);
		System.out.print("file a? ");
		String codeFile = console.nextLine();
		
		System.out.print("file b? ");
		String file2 = console.nextLine();
		
		Scanner a = new Scanner(new File(codeFile));
		Scanner b = new Scanner(new File(file2));
		String fuck = a.next();
		String you = b.next();
		for (int i = 0; i < fuck.length(); i++) {
			if (fuck.charAt(i) != you.charAt(i)) {
				System.out.println("fucked!: " + i);
				System.out.println(fuck.substring(i));
				System.out.println(you.substring(i));
			}
			
		}
		
	}
	
	public static void checkfiles(Scanner a, Scanner b) {
		
	}
	
}
