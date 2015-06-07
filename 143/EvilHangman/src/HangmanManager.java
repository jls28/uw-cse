import java.util.*;

/* Stefan Dierauf 2013
 * TA: Molly Yoder
 * Manages an evil hangman game
 */
public class HangmanManager {
	
	private TreeSet<Character> guesses; //holds guesses not in word
	private TreeSet<String> words; //possible dictionary of words
	private int guessesLeft; //number of guesses left
	private String activePattern; //the current family described as a pattern
	private HashSet<Character> containedInWord; //holds guesses in the word
	
	//Constructs the HangmanManager
	//throws IllegalArgumentException if word length is less than 1 
	//or guesses allowed is less than 0
	public HangmanManager(List<String> dictionary, int length, int max) {
		if (length < 1 || max < 0) {
			throw new IllegalArgumentException();
		}
		containedInWord = new HashSet<Character>();
		words = new TreeSet<String>();
		guesses = new TreeSet<Character>();
		for (String i : dictionary) {
			if (i.length() == length) { //adds only words of the given length to the dictionary
				words.add(i);
			}
		}
		guessesLeft = max;
		activePattern = "";
		for (int i = 0; i < length; i++) {
			if (i != 0) {
				activePattern += " ";
			}
			activePattern += "-";
		}
	}

	//returns possible dictionary as a Set of Strings 
	public Set<String> words() {
		return words;
	}
	
	//returns the number of guesses the player has left
	public int guessesLeft() {
		return guessesLeft;
	}
	
	//returns previous guesses that were not contained 
	//in the final word as a SortedSet of Characters
	public SortedSet<Character> guesses() {
		return guesses;
	}
	
	//returns the pattern representation of the current family as a String
	//throws IllegalStateException if the pattern is empty
	public String pattern() {
		if (activePattern.length() == 0) {
			throw new IllegalStateException();
		}
		return activePattern;
	}
	
	//returns the number of times the letter appears in the family.
	//throws IllegalStateException if the number of guesses left is less than 1
	//or if the dictionary of words is empty
	//throws IllegalArguementException if the list of words is nonempty and the character guessed
	//was guessed previously 
	public int record(char guess) {
		if (guessesLeft < 1 || words.size() < 1) {
			throw new IllegalStateException();
		}
		if (words.size() > 0 && (guesses.contains(guess) ||
				containedInWord.contains(guess)) ) {
			throw new IllegalArgumentException();
		}
		TreeMap<String, TreeSet<String>> families = findFamilies(guess); 
		String largestFamily = "unassigned"; 
		for (String family : families.keySet()) { //gets the first largest family pattern
			if (largestFamily.equals("unassigned") || 
					families.get(family).size() > families.get(largestFamily).size()) {
				largestFamily = family;
			} 
		}
		int count = 0;
		for (int j = 0; j < largestFamily.length(); j++) {
			if (largestFamily.charAt(j) == guess) {
				count++;
			}
		}
		if (count > 0) {
			containedInWord.add(guess);
		}
		update(guess, largestFamily, families);
		return count;
	}
	
	//updates the HangmanManager for the next round of guessing
	private void update(char guess, String largestFamily, TreeMap<String, TreeSet<String>> families) {
		if (activePattern.equals(largestFamily)) {
			guessesLeft--;
		}
		activePattern = largestFamily;
		words = families.get(largestFamily);
		guesses.add(guess);
	}
	
	//returns a map of String of the family represented as the pattern
	//to all the words contained in that family
	private TreeMap<String, TreeSet<String>> findFamilies(char guess) {
		TreeMap<String, TreeSet<String>> families = new TreeMap<String, TreeSet<String>>();
		for (String word : words) {
			String family = familyBuilder(word, guess);
			if (families.containsKey(family)) {
				families.get(family).add(word);
			} else {
				TreeSet<String> a = new TreeSet<String>();
				a.add(word);
				families.put(family, a);
			}
		}
		return families;
	}
	
	//returns a String representation of a family
	private String familyBuilder(String word, char guess) {
		String family = "";
		for (int j = 0; j < word.length(); j++) {
			if (j != 0) {
				family += " ";
			}
			if(word.charAt(j) == guess) {
				family += guess;
			} else if (containedInWord.contains(word.charAt(j))) {
				family += word.charAt(j);
			} else {
				family += "-";
			}
		}
		return family;
	}
	
	
}
