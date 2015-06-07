public class Midterm {

	public static void main (String[] args){
	
	sequenceSum(10);
	printGrid(3, 6);
	
	}
	
	public static void sequenceSum(double a) {
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
	
	public static void printGrid(int rows, int cols) {
		for (int i = 1; i <= rows; i++){
			System.out.print(i);
			for (int j = 1; j<= cols - 1; j++) {
				System.out.print(", " + (j*rows+i));
			}
			System.out.println();
		}
	
	} 
}