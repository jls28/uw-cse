import java.util.*;


public class RotX {
	private Set<String> dictionary; //want hashset for fast access
	private TreeMap<String, String> mirrorWords;
	private int level;
	
	public RotX(Set<String> dictionary, int level) {
		this.dictionary = dictionary;
		mirrorWords = new TreeMap<String, String>();
		this.level = level;
		
		
	}
	
	public void getMirrorWords() {
		for (String i : dictionary) {
			String cyphered = rotCypher(i);
			if (dictionary.contains(cyphered)) {
				mirrorWords.put(i, cyphered);
			}
		}
	}
	
	public String rotCypher(String word) {
		String cyphered = "";
		for(int i = 0; i < word.length(); i++) {
			cyphered += shift(word.charAt(i));
		}
		return cyphered;
	}
	
	public char shift(char character) {
		char c = character;
		for (int i = 0; i < level; i++) {
			if (c == 'z') {
				c = 'a';
			} else {
				c += 1;
			}
		}
		return c;
	}
	
	public void printMirrorWords() {
		for (String i : mirrorWords.keySet()) {
			if (i.length() > 3 ) {
				System.out.println(level + ": " + i + " <-> " + mirrorWords.get(i));
			}
			
		}
	}
}
