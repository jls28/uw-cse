/* Stefan Dierauf 2013
 * TA: Molly Yoder
 * Solves possible anagrams
 * based on given phrase and dictionary.
 * REQUIRES LetterInventory
 */

import java.util.*;

public class Anagrams {
	private Set<String> dictionary;
	private SortedSet<String> possibleWords;

	//constructs Anagram solver
	//throws IllegalArgumentException if dictionary passed is null
	public Anagrams(Set<String> dictionary) {
		if (dictionary == null) {
			throw new IllegalArgumentException();
		}
		this.dictionary = dictionary;
		possibleWords = new TreeSet<String>();
	}

	//returns Set of possible words contained in the phrase passed in
	//populates possibleWords dictionary
	//throws IllegalArgumentException if the passed phrase is null
	public Set<String> getWords(String phrase) {
		if (phrase == null) {
			throw new IllegalArgumentException();
		}
		possibleWords.clear();
		LetterInventory letters = new LetterInventory(phrase);
		for (String word : dictionary) {
			if (letters.contains(word)) {
				possibleWords.add(word);
			}
		}
		return possibleWords;
	}

	//prints all possible anagrams of the phrase
	//throws IllegalArgumentException if phrase is null
	public void print(String phrase) {
		print(phrase, 0);	
	}
	
	//prints all possible anagrams of the given phrase 
	//with up to the given max amount of words
	//if max is 0, prints all possible anagrams
	//throws IllegalArgumentException if phrase is null or if max < 0
	public void print(String phrase, int max) {
		if (phrase == null || max < 0) {
			throw new IllegalArgumentException();
		}
		getWords(phrase); //updates the possible words
		List<String> soFar = new LinkedList<String>();
		print(new LetterInventory(phrase), max, soFar);
	}

	//private recursive method that does the work for print(String, int)
	private void print(LetterInventory phraseInventory, int max, List<String> soFar) {
		if (phraseInventory.size() == 0 && 
				(max == 0 || (max > 0 && soFar.size() <= max) ) ) {
				System.out.println(soFar);
		} else if (max == 0 || !(soFar.size() > max - 1)) {
			for (String word : possibleWords) {
				if (phraseInventory.contains(word)) {
					soFar.add(word); //choose a word
					phraseInventory.subtract(word);
					print(phraseInventory, max, soFar); //recurse
					soFar.remove(soFar.size() - 1);//unchoose
					phraseInventory.add(word);
				}
			}
		}	
	}
}
