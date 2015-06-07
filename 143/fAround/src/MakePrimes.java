
public class MakePrimes {
	
	public static void main(String[] args) {
		long startTime = System.currentTimeMillis();
		long start = 2;
		long end = 500000;
		long thenumber = 0;
		int count = 0;
		for (long i = start; i <= end; i++) {
			
			if (isPrime(i)) {
				System.out.println(i);
				count++;
				thenumber += i;
//				if (count == 10001) {
//					thenumber = i;
//					i = 1000000000;
//				}
			}
		}
		long endTime = System.currentTimeMillis();
		System.out.println("Total primes between " + start + " and " + end + ": " + count);
		System.out.println("Time elapsed: " + (endTime - startTime) + "ms");
		System.out.println(thenumber);
		
	}
	
	public static boolean isPrime(long num) {
		//general thinking: if you divide num by some l, integer division will chop off the decimal
		//so when you multiply that number by l, if you dont get num, that number wasnt a factor. 
		long l = 2;
		while (l < num / 2 + 1) {
			long j = num / l;
			if (j * l == num && l != num) {
				return false;
			}
			l++;
		}
		return true;
	}

}
