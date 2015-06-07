import java.util.ArrayList;


public class Primes {
	
	public static ArrayList<Integer> primes;
	
	public static void main(String[] args) {
		primes = new ArrayList<Integer>();
		long currentTime = System.currentTimeMillis();
		long sum = 0;
		int max = 2000000;
		for (int i = 2; i < max; i++) {
			if (isPrime(i)) {
				System.out.println(i);
				sum += i;
			}
		}
		System.out.println(primes.size());
		System.out.println("This took " + (System.currentTimeMillis() - currentTime)/1000.0 + " seconds");
		System.out.println(sum);
	}
	
	public static boolean isPrime(int num) {
		if (primes.isEmpty()) {
			primes.add(num);
			return true;
		} else {
			for (int i = 0; i < primes.size(); i++) {
				if (num % primes.get(i) == 0) {
					return false;
				}
			}
			primes.add(num);
			return true;
		}
	}

}
