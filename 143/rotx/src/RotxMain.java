/* Stefan Dierauf 2013
 * rot13 is a ceserian cypher where each letter is rotated 13 characters to the next char
 * some words when cyphered in rot13 produce mirror words eg abjurer <-> nowhere
 * goal: find which amount of rotation produces the most mirror words
 * 
 */
import java.util.*;
import java.io.*;

public class RotxMain {
	private static final String DICTIONARY_FILE = "dict3.txt";
	
	public static void main(String[] args) throws FileNotFoundException {
		System.out.println("Rotx solver");
		System.out.println("Continue? (y/n)");
		
		//build dictionary
		Scanner input = new Scanner(new File(DICTIONARY_FILE));
        Set<String> dictionary = new TreeSet<String>();
        while (input.hasNextLine()) {
            dictionary.add(input.nextLine());
        }
        dictionary = Collections.unmodifiableSet(dictionary);   // read-only
		
        //new Rotx solver
        int level = 1;

        while (level != 14) {
        	System.out.println();
        	RotX solver = new RotX(dictionary, level);
        	solver.getMirrorWords();
        	solver.printMirrorWords();
        	level++;
        }
		
	}

}

/* basic algorithm
 * 	loop through dictionary
 * 	select word
 * 	rotate through it
 * 	if the dictionary contains it, stick it in map of mirror words
 * check for each rot(x)
 * find which has the largest size
 * 
 */
