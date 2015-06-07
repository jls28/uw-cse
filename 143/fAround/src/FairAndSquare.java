import java.util.Stack;


public class FairAndSquare {

	public static void main(String[] args){
		long begin = 0;
		long end = 10000000;
		long startTime = System.currentTimeMillis();
		//for each number in range, check if it's a palindrome.
		//then square it, and check if it's a palindrome again.
		long count = 0;
		for (long i = begin; i <= end; i++) {
			String num = i + "";
			if (isPalindrome(num)) {
				String dubNum = i*i +"";
				if (isPalindrome(dubNum)) {
					System.out.println(num + ": " + dubNum);
					count++;
				}
			}
		}
		long endTime = System.currentTimeMillis();
		System.out.println("Total fair-and-square: " + count + ". Time " + (endTime - startTime) + "ms");
	}
	
	public static boolean isPalindrome(String num) {
		if (num.length() < 2) {
			return true;
		} else {
			String first = num.substring(0, 1);
			String last = num.substring(num.length()-1);
			return first.equals(last) && isPalindrome(num.substring(1, num.length()-1));
		}
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
