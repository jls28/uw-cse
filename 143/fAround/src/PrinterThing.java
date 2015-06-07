import java.io.*;
import java.util.*;


public class PrinterThing {
	
	public static final InputStream IN = System.in;
	
	public static void main(String[] args) throws FileNotFoundException {
		ArrayList<Printer> printers = new ArrayList<Printer>(); 
		System.out.print("File path: ");
		Scanner input = new Scanner(IN);
		File sample = new File(input.next());
		//get an inventory of its lines
		Scanner readFile = new Scanner(sample);
		int counter = 0;
		String header = "";
		while (readFile.hasNextLine()) {
			//look at each line
			String line = readFile.nextLine();
			if (counter <= 4) {
				header += line; 
				if (counter != 4) {
					header += "\n";
				}
			}
			//if its a printer line, make a new Printer.
			if (line.contains("ps")) {
				String name = line.substring(38, 46);
				String lastActive = line.substring(49, 59);
				printers.add(new Printer(line));
			}
			counter++;
			
		}

		for (Printer i : printers) {
			System.out.println(i);
			if (!i.isComplete()) {
				if (i.slides > -2) {
					System.out.print("Reams/Slides/Comments(optional)");
				} else if (i.slides == -2) {
					System.out.print("Reams/Comments(optional)");
				}
				String[] data = input.nextLine().split("/");
				try {
					i.procInput(data);
				} catch (Exception e) {
					System.out.println("please try again: ");
					String[] again = input.nextLine().split("/");
				}
			
			}
		}
		System.out.println(header);
		for (Printer i : printers) {
			System.out.println(i);
			System.out.println("--------------------------------------------------------------------------------------");
		}
		System.out.println("</pre>");
		//if there are unfilled printers, prompt user for paper count, (slide count), and comments
		//dump data to standard layout with pre tags etc
		//save data to a new sheet.  
	}

}
