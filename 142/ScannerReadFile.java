import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class ScannerReadFile {
 
    public static void main(String[] args) {
	 
	 Scanner s = new Scanner(System.in);
	 
	 String tag = promptTag(s);
	 System.out.print("Where is your file located? ");
	 String fileLocation = s.nextLine();
 
        // Location of file to read
        File file = new File(fileLocation);
 
        try {
 
            Scanner scanner = new Scanner(file);
 
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                System.out.println("<" + tag+ ">" + line + "</" + tag +"><br>");
            }
            scanner.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
 
    }
	 public static String promptTag(Scanner s) {
	 	System.out.print("What html tag would you like to add to each line? ");
		return s.nextLine();
	 }
}