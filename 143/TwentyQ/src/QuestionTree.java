/*Stefan Dierauf March 2013
 * TA: Molly Yoder
 * keeps track of a game of Twenty Questions
 * REQUIRES QuestionNode
 */

import java.io.*;
import java.util.*;

public class QuestionTree {
	
	private QuestionNode overallRoot;
	private UserInterface ui;
	private int gamesWon;
	private int totalGames;

	//constructs the QuestionTree
	//throws IllegalArgumentException if null passed in
	public QuestionTree(UserInterface ui) {
		if (ui == null) {
			throw new IllegalArgumentException();
		}
		this.ui = ui;
		overallRoot = new QuestionNode("computer");
		gamesWon = 0;
		totalGames = 0;
	}

	//Plays one complete 20 questions game with the user
	//if the computer fails to guess the player's object, 
	//it will add the object and a differing question to the QuestionTree
	public void play() {
		overallRoot = playHelper(overallRoot);
	}
	
	//updates the game if the computer failed to guess it
	//returns the game, regardless if it was updated or not
	private QuestionNode playHelper(QuestionNode root) {
		if (root.left == null && root.right == null) {
			totalGames++;
			ui.print("Would your object happen to be " + root.data + "?");
			if (ui.nextBoolean()) {
				gamesWon++;
				ui.println("I win!");
			} else {
				root = updateTree(root);
			}
		} else {
			ui.print(root.data);
			if (ui.nextBoolean()) {
				root.left = playHelper(root.left);
			} else {
				root.right = playHelper(root.right);
			}
		}
		return root;
	}
	
	//updates the game with the new object and a question that differs it 
	//from the computer's guessed object
	private QuestionNode updateTree(QuestionNode root) {
		ui.print("I lose. What is your object?");
		String newObject = ui.nextLine();
		ui.print("Type a yes/no question to distinguish your item from " + 
				root.data + ":");
		String newQuestion = ui.nextLine();
		ui.print("And what is the answer for your object?");
		if (ui.nextBoolean()) {
			root = new QuestionNode(newQuestion, new QuestionNode(newObject),
					new QuestionNode(root.data));
		} else {
			root = new QuestionNode(newQuestion, new QuestionNode(root.data), 
					new QuestionNode(newObject));
		}
		return root;
	}

	//returns the total number of games played
	public int totalGames() {
		return totalGames;
	}

	//populates the game with saved questions and answers
	//throws IllegalArgumentException if the passed scanner is null
	public void load(Scanner in) {
		if (in == null) {
			throw new IllegalArgumentException();
		}
		overallRoot = loadHelper(in); 
	}
	
	//updates the current game with saved game data
	private QuestionNode loadHelper(Scanner in) {
		String line = in.nextLine();
		boolean isQuestion = line.substring(0, 1).equals("Q");
		String phrase = line.substring(2);
		QuestionNode root = new QuestionNode(phrase);
		if (isQuestion) {
			root.left = loadHelper(in);
			root.right = loadHelper(in);
		}
		return root;
	}

	//returns the total number of games won
	public int gamesWon() {
		return gamesWon;
	}

	//Saves the current game data
	//throws IllegalArgumentException if passed PrintStream is null
	public void save(PrintStream out) {
		if (out == null) {
			throw new IllegalArgumentException();
		}
		save(out, overallRoot);
	}
	
	//Saves the current game data to a PrintStream
	private void save(PrintStream out, QuestionNode root) {
		if (root != null) {
			if(root.left != null || root.right != null) {
				out.println("Q:" + root.data);
			} else {
				out.println("A:" + root.data);
			}
			save(out, root.left);
			save(out, root.right);
		}
	}

}
