
public class TriangularNumbers {
	
	public static void main(String[] args) {
		long startTime = System.currentTimeMillis();
		//make a triangular number
		//check number of divisors
		//if over 500, print
		int count = 1;
		long divisors = 0;
		long number = 0;
		while (divisors < 500) {
			//int tri = 0;
			number += count;
			count++;
			for (long i = 1; i < number/2; i++) {
				if (number % i == 0) {
					divisors++;
				}
			}
			divisors = divisors * 2;
			System.out.println(number + " " + divisors);
			if (divisors > 500) {
				System.out.println("YAY " + number);
			} else {
				divisors = 0;
			}
		}
		long endTime = System.currentTimeMillis();
		System.out.println(endTime - startTime);
		
	}

}
