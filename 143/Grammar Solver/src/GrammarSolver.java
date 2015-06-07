/*Stefan Dierauf Feb 2013
 * TA: Molly Yoder
 * Generates sentences based on given rules
 */

import java.util.*;


public class GrammarSolver {
	private Map<String, String> grammarRules = new TreeMap<String, String>();
	private Random rand = new Random();
	
	//Populates map with given rules and their data
	//throws IllegalArguementException if passed list contains two of the same rule
	//or if the grammar contains more than one line for the same non terminal
	public GrammarSolver(List<String> rulesList) {
		if(rulesList == null || rulesList.size() == 0) {
			throw new IllegalArgumentException();
		}
		for (String rule : rulesList) {
			String[] pieces = rule.split("::=");
			if (!this.contains(pieces[0])) {
				grammarRules.put(pieces[0], pieces[1].replaceAll("[ \t]+", " ").trim());
			} else {
				throw new IllegalArgumentException();
			}
		}
	}
	
	//returns true if string is a non terminal
	//throws IllegalArgumentException if passed string is 0 or null.
	public boolean contains(String symbol) {
		stringCheck(symbol);
		return getSymbols().contains(symbol);
	}

	//returns true if string contains a non terminal, otherwise returns false
	//throws IllegalArgumentException if passed string is 0 or null.
	private boolean containsASymbol(String symbol) {
		stringCheck(symbol);
		String[] pieces = symbol.split("[ \t]+");
		boolean bool = false;
		for (int i = 0; i < pieces.length; i++) {
			if (contains(pieces[i])) {
				bool = true;
			}
		}
		return bool;
	}
	
	//checks if a string is valid,
	//throws IllegalArgumentException if passed string is 0 or null.
	private void stringCheck(String symbol) {
		if (symbol.length() == 0 || symbol == null) {
			throw new IllegalArgumentException();
		}
	}

	//returns the grammar rules as a set of strings. 
	public Set<String> getSymbols() {
		return grammarRules.keySet();
	}

	//Generates strings based on given rules
	//throws IllegalArgumentException if passed string is 0 or null.
	public String generate(String symbol) {
		stringCheck(symbol);
		String line = "";
		if (symbol.contains("|") || containsASymbol(symbol)) { //breaks up rule if contains more than one option
			String[] chunk = symbol.split("[|]");
			String[] pieces = chunk[rand.nextInt(chunk.length)].trim().split("[ \t]+");
			for (int i = 0; i < pieces.length - 1; i++) {
				line += subGenerate(pieces[i]) + " ";
			}
			line += subGenerate(pieces[pieces.length-1]);
		} else if (contains(symbol)) { //if its a symbol, get its data
			line += generate(grammarRules.get(symbol));
		} else { //if its terminal, add it
			line += symbol;
		}
		return line;
	}
	
	//calls generate depending on if its a symbol or a terminal
	//throws IllegalArgumentException if passed string is 0 or null.
	private String subGenerate(String gen) {
		stringCheck(gen);
		if (containsASymbol(gen)) {
			return generate(grammarRules.get(gen).trim());
		} else {
			return generate(gen.trim());
		}
	}
}
