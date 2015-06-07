/* Stefan Dierauf CSE 142 9/26/2012

This program prints out a song where parts of the song build and repeat
assingment #1 requisites can be found at http://www.cs.washington.edu/education/courses/cse142/12au/homework/1/spec.pdf
+checked with output comparison
+checked with indenter tool
*/
public class Song {
	public static void main(String[] args){
		
		//prints out the main body of the song that doesn't repeat.
		System.out.println("I once wrote a program that wouldn't compile");
		theEnd();
		
		System.out.println("My program did nothing");
		System.out.println("So I started typing.");
		stanzaOne();
		
		System.out.println("\"Parse error,\" cried the compiler");
		System.out.println("Luckily I'm such a code baller.");
		stanzaTwo();
		
		System.out.println("Now the compiler wanted an identifier");
		System.out.println("And I thought the situation was getting dire.");
		stanzaThree();
		
		System.out.println("Java complained it expected an enum");
		System.out.println("Boy, these computers really are dumb!");
		stanzaFour();
		
		System.out.println("Wow this song");
		System.out.println("Is getting really tiring.");
		stanzaFive();
	
	}
	
	//prints the last two lines present in every stanza plus a space
	//I think of this stanza as "stanza zero"
	public static void theEnd() {
		System.out.println("I don't know why it wouldn't compile,");
		System.out.println("My TA just smiled.");
		System.out.println("");
	}
	
	//prints the new line present in stanza one, and then calls the last two lines and space
	public static void stanzaOne() {
		System.out.println("I added System.out.println(\"I <3 coding\"),");
		theEnd();
	}
	
	//prints the new line present in stanza two, then calls stanza one (at least the part common to each stanza)
	public static void stanzaTwo() {
		System.out.println("I added a backslash to escape the quotes,");
		stanzaOne();
	}
	
	//prints the new line present in stanza three, then calls stanza two
	public static void stanzaThree() {
		System.out.println("I added a main method with its String[] args,");
		stanzaTwo();
	}
	
	//prints the new line present in stanza four, then calls stanza three
	public static void stanzaFour() {
		System.out.println("I added a public class and called it Scum,");
		stanzaThree();
	}
	
	//prints the new line present in stanza five, then calls stanza four
	public static void stanzaFive() {
		System.out.println("So I put on the final curly brace");
		stanzaFour();
	}
}
