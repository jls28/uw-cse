import java.util.*;

public class FavoriteLetter {

	public static void main(String[] args) {
		Scanner console = new Scanner(System.in);
		favoriteLetter(console, "y");
	}
	
	public static void favoriteLetter(Scanner console, String letter){
		System.out.println("Looking for two \"" + letter + "\" words in a row.");
		int numberOf = 0 ;
		String lastWord = "";
		while (numberOf < 2){
			System.out.print("Type a word: ");
			lastWord = console.next();
			if (lastWord.startsWith(letter)){
				numberOf++;
			} else {
				numberOf = 0;
			}
		}
		System.out.println("\"" + letter + "\" is for \""+lastWord+"\"");
	}
}