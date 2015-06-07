import java.util.*;
import java.io.*;
import java.util.concurrent.*;


public class LolRandom {

	public static void main(String[] args){
		Random r = new Random();
		
		int x = r.nextInt(50);
		System.out.print(x + " = ");
		while (x % printPrimes(50) == 0){
			System.out.print(printPrimes(50) + " * ");
		}
	
		/*while(true){
		int x = r.nextInt(100000);
		System.out.print(x + " = ");
		int twoCount  = 0;
			while ( x % 2 == 0) {
				System.out.print("2 * ");
				x = x/2;
				twoCount++;
		
			}
			System.out.println(x+" | " +twoCount);
	
	
		}*/
		
		
	
	}
	
	public static int factors(int value) {
		int factors = 0;
		for (int i = 1; i <= value; i++) {
			if (value % i == 0) {
				factors++;
			}
		}
		return factors;
	}
	
	
	// prints all primes up to and including the max
	// precondition: max >= 1	
	public static int printPrimes(int max) {
		System.out.print(1);
		for (int i = 2; i <= max; i++) {
			if (factors(i) == 2) {
				return i;
			}
		}
		return 0;
	}
}