import java.util.*;

public class Gradanator {
	
	public static final int maxNumber = 100;
		public static void main(String[] args) {
		Random rand = new Random();
		Scanner scan = new Scanner(System.in);
		
		haiku();
		
		String word = "y";
		int games = 0;
		int totalGuesses = 0;
		int bestGame = 0;
		
		while (word.startsWith("y")) {
			games ++;
			System.out.printf("I'm thinking of a number between 1 and %d... \n", maxNumber);
			int numberOfGuesses = oneGame(rand, scan);
			bestGame = Math.min(numberOfGuesses, bestGame);
			totalGuesses =+ numberOfGuesses;
			System.out.print("Do you want to play again? ");
			word = scan.next();
			word = word.toLowerCase();
			System.out.println();
		}
		
		overall(totalGuesses, games, bestGame);
	}
	
	public static void haiku() {
		System.out.println("This took me longer");
		System.out.println("Than the rest of the project");
		System.out.println("English majors cray.");
		System.out.println();
	}
	
	public static int oneGame(Random rand, Scanner scan) {
		int number = rand.nextInt(maxNumber) + 1;
		int guess = number - 1;
		int numberOfGuesses = 0;
		while (guess != number) {
			System.out.print("Your guess? ");
			guess = scan.nextInt();
			numberOfGuesses ++;
			if (guess != number) {
				theyreWrong(guess, number);
			} else {
				theyreRight(numberOfGuesses);
			}
		}
		return numberOfGuesses;
	}
			
	public static void theyreWrong(int guess, int number) {
		if (guess > number) {
			System.out.println("It's lower");
		} else if (guess < number) {
			System.out.println("It's higher");
		}
	}
	
	public static void theyreRight(int numberOfGuesses) {
		if (numberOfGuesses == 1) {
			System.out.println("You got it right in 1 guess! \n");
		} else {
			System.out.printf("You got it right in %d guesses! \n", numberOfGuesses);
		}
	}	
	
	public static void overall(int totalGuesses, int games, int bestGame) {
		System.out.println("Overall results:");
		System.out.printf("Total games = %d \n", games);
		System.out.printf("Total guesses = %d \n", totalGuesses);
		System.out.printf("Guesses/game = %.1f \n", (double)totalGuesses / games);
		System.out.printf("Best game = %d \n", bestGame);	
	}
}