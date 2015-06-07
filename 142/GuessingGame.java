/* Stefan Dierauf Oct 2012
Plays guessing game and gives a score.
*/

import java.util.*;

public class GuessingGame {

public static final int MAXNUMBER = 100; //sets the maximum range of the game. 

	public static void main(String[] args){
	
	Scanner s = new Scanner(System.in);
	Random rand = new Random();
	
	//intro haiku
	introHaiku();
	
	//initiallizes variables needed for the final output.
	int totalGuesses = 0;
	int gameCount = 0;
	int bestGame = Integer.MAX_VALUE;

	//do game until aything that doesnt start with y is entered
	String keepPlaying = "y";
	while (keepPlaying.toLowerCase().startsWith("y")){
		gameCount++;
		int guesses = playGame(s, rand);
		if (guesses < bestGame){ //finds the best game of games played
			bestGame = guesses;
		}
		totalGuesses += guesses;
		System.out.print("Do you want to play again? ");
		keepPlaying = s.next();
		System.out.println();
		
	}
	
	//prints the final score footer. 
	printFooter(totalGuesses, gameCount, bestGame);
	
	
	
	}
	
	//prints the Haiku
	public static void introHaiku() {
		System.out.println("Welcome to my game");
		System.out.println("You will be guessing numbers");
		System.out.println("I hope you wont suck.");
		System.out.println();
	
	}
	
	//plays one game and returns the number of guesses. 
	public static int playGame(Scanner s, Random rand) {
		int numberGuesses = 0;
		System.out.println("I'm thinking of a number between 1 and " + MAXNUMBER + "...");
		int randomNumber = rand.nextInt(MAXNUMBER) + 1;
		int guess = -1;
		while (guess != randomNumber) {
			System.out.print("Your guess? ");
			guess = s.nextInt();
			if (guess > randomNumber){
				System.out.println("It's lower.");
			} else if (guess < randomNumber) {
				System.out.println("It's higher.");
			}
			numberGuesses++;
		}
		System.out.println("You got it right in " + numberGuesses + " guesses!");
		
		return numberGuesses;
	}
	
	//prints the final output
	public static void printFooter(int totalGuesses, int gameCount, int bestGame) {
		System.out.println("Overall results:");
		System.out.println("Total games\t= " + gameCount);
		System.out.println("Total guesses\t= " + totalGuesses);
		System.out.println("Guesses/game\t= " + Math.round((totalGuesses) * 10.0 / gameCount)/10.0);
		System.out.println("Best game\t= " + bestGame);
	}

}