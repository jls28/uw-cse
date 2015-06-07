public class Loops {

	public static void main(String[] args) {
		int number = 69;
		for (int i = 0; i < 10; i++) {
			System.out.print("*");
			if (i % 2 == 0) {
				if (i % 6 == 0) {
					System.out.print("SIXXXXX");
				}
				System.out.print("EVEN!");
			}
		}
		
		System.out.println();
		
		while (number != 0) {
			System.out.print("*");
			number--;
		}
		
	}
		
}