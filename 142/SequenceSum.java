import java.util.*;

public class SequenceSum {

	public static void main (String[] args){
	Scanner s = new Scanner(System.in);
	
	String word = "y";
	while (!(word.equals("n"))){
		sequenceSum(s);
		System.out.print("Would you like to play again?: ");
		word = s.next();
	}
	
	
	
	}
	
	public static void sequenceSum(Scanner s) {
		System.out.print("What number would you like?: ");
		double a = s.nextDouble();
		if (a < 1.0) {
		}else{ 
			System.out.print("1 ");
			double total = 1.0;
			int counter = 2;
			while (total < a) {
				System.out.print("+ 1/"+ counter + " ");
				total += 1.0 / counter;
				counter++;
			}
			System.out.printf(" = %.3f\n", total);
		}
	} 
}